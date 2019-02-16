#include "main.h"
#include "timer.h"
#include "ball.h"
#include "airplane.h"
#include "dashboard.h"
#include "missile.h"
#include "hills.h"
#include "checkpoint.h"
#include "arrow.h"
#include "compass.h"
#include "speedometer.h"
#include "background.h"
#include "parachute.h"
#include "functions.h"
#include "volcano.h"
#include "fuel.h"
#include "smoke.h"
#include "freeze.h"
using namespace std;

GLMatrices Matrices, MatricesScore, MatricesArrow;
GLuint     programID;
GLFWwindow *window;
glm::mat4 MatrixRotPlain;

/**************************
* Customizable functions *
**************************/

std::vector<Hills> Hillpos;
std::vector<Missile> Missilepos;
std::vector<Dashboard> DashboardPos;
std::vector<Checkpoint> CheckpointPos;
std::vector<Volcano> VolcanoPos;
std::vector<Fuel> FuelPos;
std::vector<Smoke> SmokePos;
std::vector<Freeze> FreezePos;
Ball ball1;
Arrow arrow;
Airplane airplane;
Background background;
Compass compass;
Speed speed;
std::vector<Parachute> ParachutePos;
bool frozen;
float screen_zoom = 2.0, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0.0;
float eyex, eyey, eyez, targetx, targety, targetz, upx, upy, upz;
bool cam[5];
int current_camera = 0, gameOver = 0;
Timer t60(1.0 / 60);
int score = 0, current_checkpoint;
time_t cam_change_time = 0.0, fuel_change_time = 0.0;
time_t checkpoint_missile_time = 0.0, freeze_time = 0.0, loop_start_time = 0.0;
int fuelvolume = 12, barrel_roll_flag, loop_roll_flag;
string ScoreBoard = "SCORE-", AltitudeBoard = "A-", FuelBoard = "F-";
double helcamxpos = 0.0, helcamypos = 0.0;
/* Render the scene with openGL */
/* Edit this function according to your assignment */
void gameover(){
    cout<<"-----GAME OVER-----\n";
    cout<<"Final Score - "<<score<<endl;
    quit(window);

}
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
    upx = 0;
    upy = 1;
    upz = 0;
    //followcam
    if(cam[0])
    {
         targetx = airplane.position.x;
        targety = airplane.position.y;
        targetz = airplane.position.z;
        eyex = airplane.position.x + 2*MatrixRotPlain[1][0] - 2*MatrixRotPlain[2][0];
        eyey = airplane.position.y + 2*MatrixRotPlain[1][1] - 2*MatrixRotPlain[2][1];
        eyez = airplane.position.z + 2*MatrixRotPlain[1][2] - 2*MatrixRotPlain[2][2];
        upx = MatrixRotPlain[1][0];
        upy = MatrixRotPlain[1][1];
        upz = MatrixRotPlain[1][2];
    }
    // 1 plane_view
    else if(cam[1])
    {
         targetx = 1000.0f*sin(airplane.they);
        targety = sin(airplane.thex);
        targetz = 1000.0f*cos(airplane.they) ;
         eyex = airplane.position.x  + 3*MatrixRotPlain[2][0];
        eyey = airplane.position.y  + 3*MatrixRotPlain[2][1];
        eyez = airplane.position.z + 3*MatrixRotPlain[2][2];
        upx = MatrixRotPlain[1][0];
        upy = MatrixRotPlain[1][1];
        upz = MatrixRotPlain[1][2];
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
        eyez = airplane.position.z + 10;
    }
    // 4 helicopter_cam
     else if(cam[4])
    {
        if(Mousexpos > helcamxpos)eyex -= 0.1;
        if(Mousexpos < helcamxpos)eyex+=0.1;
        if(Mouseypos > helcamypos)eyey-=0.1;
        if(Mouseypos < helcamypos)eyey+=0.1;
        eyez += MouseScroll;
        MouseScroll = 0;
        helcamxpos = Mousexpos;
        helcamypos = Mouseypos;
    }
    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye (eyex, eyey, eyez );
        // eye = eye*yrotate*xrotate*zrotate;
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (targetx, targety, targetz);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (upx, upy, upz);
     glm::vec3 eyeScore (0,0,1);
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 targetScore (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 upScore (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    MatricesScore.view = glm::lookAt( eyeScore, targetScore, upScore ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;
    glm::mat4 VPScore = MatricesScore.projection * MatricesScore.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model
    glm::mat4 MVPScore;  // MVP = Projection * View * Model
    glm::mat4 MVPArrow;  // MVP = Projection * View * Model

    // Scene render
   
    for (int i = int(Missilepos.size()) - 1; i >= 0 ; --i)
    {
        if(Missilepos[i].position.y <= 0 || Missilepos[i].time >= 2.0)
        {
            // Missilepos.erase(Missilepos.begin() + i);
            continue;
        }
    }
    for (auto &x:Missilepos)
    {
        if(current_checkpoint < 10 && (x.bomb == 0 || x.bomb == 1) && detect_collision(x.BoundingBox(), CheckpointPos[current_checkpoint].BoundingBox()))
        {
            current_checkpoint++;
            score += 10;
        }
        if(x.bomb == 2 && detect_collision(x.BoundingBox(), airplane.BoundingBox()))
        {
            fuelvolume--;
            x.bomb = 5;
        }
        for (auto &y:ParachutePos)
        {
            if(detect_collision(x.BoundingBox(), y.BoundingBox()))
            {
                y.position.y = -100.0;
                score += 5;
            }
        }
    }
    if(current_checkpoint < 10){
        arrow.position.x= CheckpointPos[current_checkpoint].position.x;
        arrow.position.y= std::max(airplane.position.y - 1, 2.0f);
        arrow.position.z= CheckpointPos[current_checkpoint].position.z;
        arrow.draw(VP);
    }
    airplane.draw(VP);
    if(current_checkpoint < 10)
    {
        if(time(NULL) - checkpoint_missile_time > 2.0)
        {
            float posx = CheckpointPos[current_checkpoint].position.x;
            float posy = CheckpointPos[current_checkpoint].position.y;
            float posz = CheckpointPos[current_checkpoint].position.z;
            float anglex, angley = 0, anglez = 0;
            float diffx = airplane.position.x - CheckpointPos[current_checkpoint].position.x;
            float diffy = airplane.position.y - CheckpointPos[current_checkpoint].position.y;
            float diffz = airplane.position.z - CheckpointPos[current_checkpoint].position.z;
            float dist = sqrt(diffx*diffx + diffy*diffy + diffz*diffz);
            anglex = atan(-diffy / dist);
            angley = atan(diffx/diffz);
            Missile missile = Missile(2,posx, posy, posz, anglex ,angley,anglez, COLOR_HOT_PINK);
            Missilepos.push_back(missile);
            checkpoint_missile_time = time(NULL);
        }
        CheckpointPos[current_checkpoint].draw(VP);
    }
    background.draw(VP);
    for (auto &x:ParachutePos)
    {
        x.draw(VP);
        if(detect_collision(x.BoundingBox(), airplane.BoundingBox()))
            gameOver = 1;
    }
    for(auto &x:Hillpos)
    {
        x.draw(VP);
        if(detect_collision(x.BoundingBox(), airplane.BoundingBox()))
            gameOver = 1;
    }
    for(auto &x:VolcanoPos)
    {
        x.draw(VP);
        if(detect_collision(x.BoundingBox(), airplane.BoundingBox()))
            gameOver = 1;
    }
    Fuel x;
    for (int i = int(FuelPos.size()) - 1; i >= 0; --i)
    {
        x = FuelPos[i];
        x.draw(VP);
        if(detect_collision(x.BoundingBox(), airplane.BoundingBox()))
        {
            FuelPos.erase(FuelPos.begin() + i);
            fuelvolume = 12;
        }
    }
    Smoke smk;
    for (int i = int(SmokePos.size()) - 1; i >= 0; --i)
    {
        smk = SmokePos[i];
        smk.draw(VP);
        if(detect_collision(smk.BoundingBox(), airplane.BoundingBox()))
        {
            SmokePos.erase(SmokePos.begin() + i);
            score += 5;
        }
    }
    Freeze freeze;
    for (int i = int(FreezePos.size()) - 1; i >= 0; --i)
    {
        freeze = FreezePos[i];
        freeze.draw(VP);
        if(detect_collision(freeze.BoundingBox(), airplane.BoundingBox()))
        {
            FreezePos.erase(FreezePos.begin() + i);
            freeze_time = time(NULL);
            frozen = 1;
        }
    }
    for(auto &x:Missilepos)x.draw(VP);
    string digit;
    int aux_score = score;

    for (int i = 0; i < 63 ; ++i)
    {
        if(i < 42)
        {
            if(i%7 == 0)digit = sevenSegment(ScoreBoard[i/7]);
            if(digit[i%7] == '1')
            {
                DashboardPos[i].draw(VPScore);
            }
        }
        else
        {
            if(i == 42)
            {
                digit = sevenSegment(aux_score/100 + 48);
                aux_score%=100;
            }
            else if(i == 49)
            {
                digit = sevenSegment(aux_score/10 + 48);
                aux_score%=10;
            }
            else if(i == 56)
            {
                digit = sevenSegment(aux_score + 48);
                aux_score = 0;
            }
            if(digit[(i-42)%7] == '1')
            {
                DashboardPos[i].draw(VPScore);
            }
        }
    }
    for (int i = 63; i < 89; ++i)
    {
        if(i < 77)
        {
            if(i%7 == 0)digit = sevenSegment(AltitudeBoard[(i-63)/7]);
            if(digit[i%7] == '1')
            {
                DashboardPos[i].draw(VPScore);
            }
        }
        else
        {
            if(airplane.position.y < (i-77)*10)break;
            DashboardPos[i].draw(VPScore);
        }
    }
    for (int i = 89; i < int(DashboardPos.size()); ++i)
    {
        if(i < 103)
        {
            if(i == 89)digit = sevenSegment('F');
            if(i == 95)digit = sevenSegment('-');
            if(digit[(i+2)%7] == '1')
            {
                DashboardPos[i].draw(VPScore);
            }
        }
        else
        {
            if(i - 102 > fuelvolume)break;
            DashboardPos[i].draw(VPScore);
        }
    }
    speed.rotation = (10*M_PI*airplane.speed);
    compass.draw(VPScore);
    speed.draw(VPScore);
    if(airplane.y < 0.0 || gameOver || fuelvolume <= 0)
        gameover();
}
void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_A);
    int right = glfwGetKey(window, GLFW_KEY_D);
    int up = glfwGetKey(window, GLFW_KEY_W);
    int down = glfwGetKey(window, GLFW_KEY_S);
    int clock = glfwGetKey(window, GLFW_KEY_E);
    int anticlock = glfwGetKey(window, GLFW_KEY_Q);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    int camera = glfwGetKey(window, GLFW_KEY_C);
    int barrel_roll = glfwGetKey(window, GLFW_KEY_B);
    int loop_roll = glfwGetKey(window, GLFW_KEY_L);
    int missile = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    int bomb = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
    airplane.moving = 0;
    if(barrel_roll){
        barrel_roll_flag = 1;
    }
    if(loop_roll){
        loop_roll_flag = 1;
        loop_start_time = time(NULL);
    }
    if(barrel_roll_flag){
        up = 1;
        clock = 1;
    }else airplane.y = 0;
    if(loop_roll_flag){
        up = 1;
        airplane.speed = 0.2;
        airplane.pitch -= (M_PI)/120;
        airplane.p++;
    }
    if(airplane.p > 240)
    {
        airplane.pitch += M_PI*2;
        airplane.p = 0;
        loop_roll_flag =0;
    }
    if(clock){
        airplane.yaw += 0.01;
        airplane.y++;
        if(barrel_roll_flag && airplane.y >= 200*M_PI)barrel_roll_flag = 0;
    }
    if(anticlock){
        airplane.yaw -= 0.01;
        airplane.y--;
    }
    if (left) {
        // airplane.position.x += 0.1;
        airplane.roll += 0.01;
        airplane.r++;
        // arrow.roll += 0.01;
        airplane.they += 0.01;
        compass.rotation -= 0.01;
        airplane.moving = 1;
    }
    // else if(!right)airplane.yaw = min(airplane.yaw+0.0001f,0.0f);

    if(right){
        airplane.roll-=0.01;
        airplane.r--;
        // arrow.roll -= 0.01;
        compass.rotation += 0.01;
        airplane.they -= 0.01;
        airplane.moving = 1;
    }

    if(up){
        // airplane.position.z += 0.1;
         airplane.position.z += airplane.speed*cos(-airplane.they);
        airplane.position.x -= airplane.speed*sin(-airplane.they);
        airplane.position.y += airplane.speed*sin(-airplane.thex);
        airplane.moving = 1;
    }
    if(down){
       airplane.position.y -= airplane.speed;
        airplane.position.y -= airplane.speed*sin(-airplane.thex);
        airplane.moving = 1;
        if(airplane.p < 5)
        {
            airplane.p++;
            airplane.pitch += 0.01;
            airplane.thex += 0.01;
        }
    }
    if(space){
        airplane.position.y += airplane.speed;
        airplane.moving = 1;
        if(airplane.p > -5)
        {
            airplane.pitch -= 0.01;
            airplane.p--;
            // arrow.pitch -= 0.01;
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
    if(camera && time(NULL) - cam_change_time > 0.5)
    {
        cam[current_camera] = 0;
        current_camera++;
        current_camera%=5;
        if(current_camera == 4)
        {
            helcamxpos = Mousexpos;
            helcamypos = Mouseypos;
             targetx = airplane.position.x;
            targety = airplane.position.y;
            targetz = airplane.position.z;
            eyex = airplane.position.x - 2*sin(airplane.they);
            eyey = airplane.position.y + 2 + 2*sin(airplane.thex);
            eyez = airplane.position.z - 2*cos(airplane.they);
        }
        cam[current_camera] = 1;
        cam_change_time = time(NULL);
    }
     if(missile){
        float posx, posy, posz;
        posx = airplane.position.x;
        posy = airplane.position.y;
        posz = airplane.position.z ;
        Missile missile = Missile(0,posx, posy, posz, MatrixRotPlain[2][0],-MatrixRotPlain[2][1],MatrixRotPlain[2][2] , COLOR_NEON_GREEN);
        Missilepos.push_back(missile);
    }
     if(bomb){
        float posx, posy, posz;
        posx = airplane.position.x;
        posy = airplane.position.y;
        posz = airplane.position.z ;
        Missile missile = Missile(1,posx, posy, posz, float(M_PI/2), 0 , airplane.they, COLOR_BLACK);
        Missilepos.push_back(missile);
    }
}

void tick_elements() {
    if(time(NULL) - fuel_change_time > 5.0)
    {
        fuelvolume--;
        fuel_change_time = time(NULL);
    }
    if(frozen && time(NULL) - freeze_time > 10.0)frozen =0;
    if(current_checkpoint < 10)
    CheckpointPos[current_checkpoint].active = 1;
    airplane.tick();
    background.tick();
    arrow.tick();
    for (auto&x:Missilepos)
    {
        if(frozen && x.bomb == 2)continue;
        x.tick();
    }
     for (auto &x:CheckpointPos)
    {
        x.tick();
    }
    if(frozen)return;
    for (auto &x:ParachutePos)
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
    background  = Background(0, 0,0, COLOR_WATER);
    arrow = Arrow(airplane.position.x, airplane.position.y + 0.2, airplane.position.z + 3.5);
    Checkpoint checkpoint;
    for (int i = 0; i < 10; ++i)
    {
        float posx = -100.0f + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(100.0)));
        float posz = -100.0f + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(100.0)));
        checkpoint = Checkpoint(posx,0,posz);
        CheckpointPos.push_back(checkpoint);
    }
    compass = Compass(0.4,0.4,0.4);
    speed = Speed(0.7,0.7,0.2);
    Hills hills;
    for (int i = 0; i < 200; ++i)
    {
        float posx = -200.0f + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(400.0)));
        float posz = -1000.0f + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(2000.0)));
        hills = Hills(posx,0.0, posz);
        Hillpos.push_back(hills);
    }
    Volcano volcano;
    for (int i = 0; i < 10; ++i)
    {
        float posx = -200.0f + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(400.0)));
        float posz = -100.0f + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(200.0)));
        volcano = Volcano(posx,0.0, posz);
        VolcanoPos.push_back(volcano);
    }
    Fuel fuel;
    for (int i = 0; i < 10; ++i)
    {
        float posx = -100.0f + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(100.0)));
        float posy = 0.0f + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(20.0)));
        float posz = -100.0f + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(100.0)));
        fuel = Fuel(posx,posy, posz);
        FuelPos.push_back(fuel);
    }
    Smoke smoke;
    for (int i = 0; i < 10; ++i)
    {
        float posx = -100.0f + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(100.0)));
        float posy = 0.0f + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(20.0)));
        float posz = -100.0f + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(100.0)));
        smoke = Smoke(posx,posy, posz);
        SmokePos.push_back(smoke);
    }
    Freeze freeze;
    for (int i = 0; i < 10; ++i)
    {
        float posx = -100.0f + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(100.0)));
        float posy = 0.0f + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(20.0)));
        float posz = -100.0f + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(100.0)));
        freeze = Freeze(posx,posy, posz);
        FreezePos.push_back(freeze);
    }
    Parachute parachute;
    for (int i = 0; i < 10; ++i)
    {
        parachute = Parachute(0,0,0);
        ParachutePos.push_back(parachute);
    }
    float current = 0.0,currenty = -0.9, diff = 0.02, xx = 0.02, yy = 0.08;
    Dashboard dashboard;
    int limit;
    for(int j = 0; j< 3; ++j)
    {
        current = 0.0,currenty += 0.3, diff = 0.02, xx = 0.02, yy = 0.08;
        if(j == 0)limit = 9;
        else limit = 2;
        for(int i =0 ;i<limit;++i)
        {   
            dashboard = Dashboard(current,currenty +  3.94f - xx - 2*yy - 2*diff, xx, yy, COLOR_GREEN);
            DashboardPos.push_back(dashboard);
            dashboard = Dashboard(current+ diff,currenty + 3.94f - 2*yy - xx -3*diff, yy, xx, COLOR_GREEN);
            DashboardPos.push_back(dashboard);
            dashboard = Dashboard(current + xx + yy,currenty + 3.94f - xx - 2*yy - 2*diff, xx, yy,  COLOR_GREEN);
            DashboardPos.push_back(dashboard);
            dashboard = Dashboard(current + xx + yy ,currenty + 3.94f - xx - yy - diff, xx, yy, COLOR_GREEN);
            DashboardPos.push_back(dashboard);
            dashboard = Dashboard(current + diff,currenty + 3.94f - xx, yy, xx, COLOR_GREEN);
            DashboardPos.push_back(dashboard);
            dashboard = Dashboard(current,currenty + 3.94f - xx - yy - diff, xx, yy,  COLOR_GREEN);
            DashboardPos.push_back(dashboard);
            dashboard = Dashboard(current + diff,currenty +  3.94f - xx - yy - 2*diff, yy, xx, COLOR_GREEN);
            DashboardPos.push_back(dashboard);
            current += (2*xx + yy + diff);
        }
        if(j>0)
        {
            color_t col;
            float offset = 20;
            for (int i = 0; i < 12; ++i)
            {
                col.r = 35 + offset*i;
                col.g = 0;
                col.b = 0;
                dashboard = Dashboard(current,currenty +  3.94f - xx - 2*yy - 3*diff, xx*4, yy*3, col);
                current += (yy + 0.000001);
                DashboardPos.push_back(dashboard);
            }
        }
    }
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");
    MatricesScore.MatrixID = glGetUniformLocation(programID, "MVPScore");
    MatricesArrow.MatrixID = glGetUniformLocation(programID, "MVPArrow");


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
    MatricesScore.projection = glm::ortho(0.0f, 4.0f, 4.0f, 0.0f, 0.1f, 500.0f);
    MatricesArrow.projection = glm::perspective(float(90*M_PI/180), width/height, 0.1f, 5000.0f);
    MatrixRotPlain = glm::mat4(1.0f);
}
