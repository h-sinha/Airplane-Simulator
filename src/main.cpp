#include "main.h"
#include "timer.h"
#include "ball.h"
#include "airplane.h"
#include "hills.h"
#include "background.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

std::vector<Hills> Hillpos;
Ball ball1;
Airplane airplane;
Background background;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0.0;
float eyex, eyey, eyez, targetx, targety, targetz;
bool cam[5];
int current_camera = 0;
Timer t60(1.0 / 60);
time_t cam_change_time = 0.0;

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);
    // 0 follow_cam
    // 1 plane_view
    // 2 top_view
    // 3 tower_view
    // 4 helicopter_cam
    
    //followcam
    if(cam[0])
    {
         targetx = airplane.position.x;
        targety = airplane.position.y;
        targetz = airplane.position.z;
        eyex = airplane.position.x ;
        eyey = airplane.position.y + 3;
        eyez = airplane.position.z - 2;
    }
    // 1 plane_view
    else if(cam[1])
    {
         targetx = airplane.position.x;
        targety = 0.0f;
        targetz = 1000.0f;
        eyex = airplane.position.x ;
        eyey = airplane.position.y ;
        eyez = airplane.position.z + 3;
    }
     // 2 top_view
     else if(cam[2])
    {
        targetx = airplane.position.x;
        targety = airplane.position.y;
        targetz = airplane.position.z;
        eyex = airplane.position.x ;
        eyey = airplane.position.y + 15;
        eyez = airplane.position.z - 2;
    }
     // 3 tower_view
     else if(cam[3])
    {
        targetx = airplane.position.x;
        targety = airplane.position.y;
        targetz = airplane.position.z;
        eyex = airplane.position.x + 10;
        eyey = airplane.position.y + 10;
        eyez = airplane.position.z ;
    }
    // 4 helicopter_cam
     else if(cam[4])
    {
        targetx = airplane.position.x;
        targety = airplane.position.y;
        targetz = airplane.position.z;
        eyex = airplane.position.x ;
        eyey = airplane.position.y + 3;
        eyez = airplane.position.z - 2;
    }
    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye (eyex, eyey, eyez );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (targetx, targety, targetz);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    ball1.draw(VP);
    airplane.draw(VP);
    background.draw(VP);
    for(auto &x:Hillpos)x.draw(VP);

}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    int camera = glfwGetKey(window, GLFW_KEY_C);
    airplane.moving = 0;
    if (left) {
        airplane.position.x += 0.1;
        airplane.moving = 1;
    }
    if(right){
        airplane.position.x -= 0.1;
        airplane.moving = 1;
    }
    if(up){
        airplane.position.z += 0.1;
        airplane.moving = 1;
    }
    if(down){
        airplane.position.z -= 0.1;
        airplane.moving = 1;
    }
    if(space){
        airplane.position.y += 0.1;
        airplane.moving = 1;
    }
    if(camera && time(NULL) - cam_change_time > 1.0)
    {
        cam[current_camera] = 0;
        current_camera++;
        current_camera%=5;
        cam[current_camera] = 1;
        cam_change_time = time(NULL);
    }
}

void tick_elements() {
    airplane.tick();
    background.tick();
    for (auto&x:Hillpos)
    {
        x.tick();
    }
    // background.set_position(ball1.position.x,ball1.position.y,ball1.position.z );
    // camera_rotation_angle += 1;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    cam[0] = 1;
    ball1       = Ball(3.0, 3.0,0, COLOR_RED);
    airplane       = Airplane(6.0, 2.0,2, COLOR_RED);
    background  = Background(0, 0,0, COLOR_WATER);
    Hills hills;
    for (int i = 0; i < 1000; ++i)
    {
        float posx = -100.0f + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(200.0)));
        float posz = -1000.0f + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(2000.0)));
        hills = Hills(posx,0.0, posz);
        Hillpos.push_back(hills);
    }

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 1000;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float width = 1000;
    float height = 600;
    // float top    = screen_center_y + 4 / screen_zoom;
    // float bottom = screen_center_y - 4 / screen_zoom;
    // float left   = screen_center_x - 4 / screen_zoom;
    // float right  = screen_center_x + 4 / screen_zoom;
    // Matrices.projection = glm::perspective(left, right, bottom, top, 0.1f, 500.0f);
     gluPerspective(1.0f, 1000.0/600.0,0.1f, 500.0f);
    // glMatrixMode(GL_MODELVIEW);
    // glViewport(0, 0, width, height);
//     float top    = 10 / screen_zoom;
//     float bottom = 0;
//     float left   = 0;
//     float right  = 10 / screen_zoom;
//     Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
