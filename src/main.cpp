#include "main.h"
#include "timer.h"
#include "ball.h"
#include "airplane.h"
#include "dashboard.h"
#include "missile.h"
#include "hills.h"
#include "checkpoint.h"
#include "background.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

std::vector<Hills> Hillpos;
std::vector<Missile> Missilepos;
Ball ball1;
Airplane airplane;
Dashboard dashboard;
Background background;
Checkpoint checkpoint;

float screen_zoom = 2.0, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0.0;
float eyex, eyey, eyez, targetx, targety, targetz, upx, upy, upz;
bool cam[5];
int current_camera = 0, gameOver = 0;
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
        eyex = airplane.position.x - 2*sin(airplane.they);
        eyey = airplane.position.y + 2 + 2*sin(airplane.thex);
        eyez = airplane.position.z - 2*cos(airplane.they);
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
        // eye = eye*yrotate*xrotate*zrotate;
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
   
    for (int i = int(Missilepos.size()) - 1; i >= 0 ; --i)
    {
        if(Missilepos[i].position.y <= 0.3)
        {
            Missilepos.erase(Missilepos.begin() + i);
            continue;
        }
    }
    // ball1.draw(VP);
    airplane.draw(VP);
    checkpoint.draw(VP);
    background.draw(VP);
    for(auto &x:Hillpos)
    {
        x.draw(VP);
        if(detect_collision(x.BoundingBox(), airplane.BoundingBox()))
            gameOver = 1;
    }
    for(auto &x:Missilepos)x.draw(VP);
    // dashboard.draw(VP);
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    int camera = glfwGetKey(window, GLFW_KEY_C);
    int missile = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
   
    airplane.moving = 0;
    if (left) {
        // airplane.position.x += 0.1;
        airplane.roll += 0.01;
        if (airplane.yaw>-0.5)
        airplane.yaw -= 0.01;
        // for (auto &x: Hillpos)
            // x.draw();
        airplane.they += 0.01;
        airplane.moving = 1;
    }
    // else if(!right)airplane.yaw = min(airplane.yaw+0.0001f,0.0f);

    if(right){
        // airplane.position.x -= 0.1;
        if (airplane.yaw<0.5)
        airplane.yaw += 0.01;
        airplane.roll-=0.01;
        // for (auto &x: Hillpos)x.roll += 0.5;
        airplane.they -= 0.01;
        airplane.moving = 1;
    }
    // else if(!left)airplane.yaw = max(airplane.yaw-0.0001f,0.0f);

    if(up){
        // airplane.position.z += 0.1;
         airplane.position.z += 0.1*cos(-airplane.they);
        airplane.position.x -= 0.1*sin(-airplane.they);
        airplane.position.y += 0.1*sin(-airplane.thex);
        airplane.moving = 1;
    }
    if(down){
       airplane.position.y -= 0.1;
        airplane.position.y -= 0.1*sin(-airplane.thex);
        airplane.moving = 1;
        if(airplane.pitch < 0.5)
        {
            airplane.pitch += 0.01;
            airplane.thex += 0.01;
        }
    }
    if(space){
        airplane.position.y += 0.1;
        airplane.moving = 1;
        if(airplane.pitch > -0.5)
        {
            airplane.pitch -= 0.01;
            airplane.thex -= 0.01;
        }
        // airplane.thex -= 0.1;
    }
    else
    {
        // airplane.pitch = min(airplane.pitch+0.1f,0.0f);
        // airplane.thex = min(airplane.thex+0.1f,0.0f);
        // airplane.position.y = max(airplane.position.y-0.1,0.0);
    }
    if(camera && time(NULL) - cam_change_time > 1.0)
    {
        cam[current_camera] = 0;
        current_camera++;
        current_camera%=5;
        cam[current_camera] = 1;
        cam_change_time = time(NULL);
    }
     if(missile){
        Missile missile = Missile(airplane.position.x,airplane.position.y,airplane.position.z, COLOR_BLACK);
        Missilepos.push_back(missile);
    }
}

void tick_elements() {
    airplane.tick();
    dashboard.tick();
    background.tick();
    checkpoint.tick();
    for (auto&x:Hillpos)
    {
        x.tick();
    }
     for (auto&x:Missilepos)
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
    airplane       = Airplane(0.0, 0.0,0, COLOR_RED);
    dashboard       = Dashboard(0.0, 0.0,0, COLOR_RED);
    background  = Background(0, 0,0, COLOR_WATER);
    checkpoint = Checkpoint(0,0,0);
    Hills hills;
    for (int i = 0; i < 1000; ++i)
    {
        float posx = -200.0f + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(400.0)));
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
    return (abs(a.x - b.x) * 2 < (a.xlength + b.xlength)) &&
           (abs(a.y - b.y) * 2 < (a.ylength + b.ylength)) &&
           (abs(a.z - b.z) * 2 < (a.zlength + b.zlength));
    // return abs(a.y - b.y) <= airplane.ylength;
}

void reset_screen() {
    float width = 800;
    float height = 600;
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    // Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
     // gluPerspective(1.0f, width/height, 0.1f, 500.0f);
    // glMatrixMode(GL_MODELVIEW);
    // glViewport(0, 0, width, height);
//     float top    = 10 / screen_zoom;
//     float bottom = 0;
//     float left   = 0;
//     float right  = 10 / screen_zoom;
    Matrices.projection = glm::perspective(float(90*M_PI/180), width/height, 0.1f, 5000.0f);
}
