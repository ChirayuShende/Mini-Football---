#include <iostream>
#include <raylib.h>

using namespace std;

int screen_width = 1280;
int screen_height = 800;
int player_score = 0;
int cpu_score = 0;

class Ball{
public:
float x,y;
int speed_x, speed_y;
float radius;

void Draw(){
    DrawCircle(x, y, radius, WHITE);

}
void ResetBall(){ 
    x = screen_width/2;
    y = screen_height/2;

    int Random_Speed[2] = {-1,1}; 
    speed_x *= Random_Speed[GetRandomValue(0,1)];
    speed_y *= Random_Speed[GetRandomValue(0,1)];
}
void Update(){
    x += speed_x;
    y += speed_y; 

    
    
    if(y + radius >=GetScreenHeight() || y - radius <= 0){
        speed_y *=-1;
    }
    if(x + radius >=GetScreenWidth())
    {
        player_score++;
        ResetBall();
    }
    
    if(x - radius <=0){
        cpu_score++; 
        ResetBall();
    }
   
}


};
class Goal{
protected:
    void LimitMovement()
    {
        if(y <= 0)
        {
        y = 0;
        }
    if(y + height >= GetScreenHeight())
        {
        y = GetScreenHeight() - height;
        }
    }
public:
float x, y;
int width, height;
float speed;

void Draw(){
    DrawRectangle(x, y, width, height, RED);
}
void Update(){
    if(IsKeyDown(KEY_UP)){
        y -= speed;
    }
    if(IsKeyDown(KEY_DOWN))
    {
        y += speed;
    }
    LimitMovement();

}
};

class CPU: public Goal{
public:
    void Draw()
    {
    DrawRectangle(x, y, width, height, BLACK);
    }
    void Update(int ball_y)
    {
        if(y + height > ball_y)
        {
            y -= speed;
        }
        if(y + height < ball_y)
        {
            y += speed;
        }
        LimitMovement();
    }

};

 Ball ball;
 Goal player;
 CPU cpu;

 int main () {
    cout << "Starting the game" << endl;

    InitWindow(screen_width, screen_height, "Mini Football!!!");
    SetTargetFPS(60);

    ball.radius = 20;
    ball.x = screen_width/2;
    ball.y = screen_height/2;
    ball.speed_x = 6;
    ball.speed_y = 6;
    
    player.width = 25;
    player.height = 180;
    player.x = 70;
    player.y = screen_height/2 - player.height/2;
    player.speed = 5;

    cpu.width = 25;
    cpu.height = 180;
    cpu.x = screen_width - player.width - 75;
    cpu.y = screen_height/2 - player.height/2;
    cpu.speed = 5;

    while(WindowShouldClose() == false){
        BeginDrawing();

        //update
        ball.Update();
        player.Update();
        cpu.Update(ball.y);

        //check collision
        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player.x, player.y, player.width, player.height}))
        {
            ball.speed_x *= -1;
        }
        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{cpu.x, cpu.y, cpu.width, cpu.height}))
        {
            ball.speed_x *= -1;
        }

         if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{0, 0, 15, 175}))
        {
            ball.speed_x *= -1;
        }
        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{0, screen_height -175, 15, 175}))
        {
            ball.speed_x *= -1;
        }
         if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{screen_width - 15, 0, 15, 175}))
        {
            ball.speed_x *= -1;
        }
        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{screen_width - 15, screen_height - 175, 15, 175}))
        {
            ball.speed_x *= -1;
        }
        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{0, 0, screen_width, 15}))
        {
            ball.speed_y *= -1;
        }
        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{0, screen_height -15, screen_width, 15}))
        {
            ball.speed_y *= -1;
        }

        //drawing
        ClearBackground(GREEN);
        DrawCircle(screen_width/2, screen_height/2, 200, WHITE);
        DrawCircle(screen_width/2, screen_height/2, 194, GREEN);
        DrawRectangle(screen_width/2 -3, 0, 6, screen_height, WHITE);
        DrawRectangle(0, 0, screen_width, 15, WHITE);
        DrawRectangle(0, screen_height -15, screen_width, 15, WHITE);
        DrawRectangle(0, 0, 15, 175, WHITE);
        DrawRectangle(0, screen_height -175, 15, 175, WHITE);
        DrawRectangle(screen_width - 15, 0, 15, 175, WHITE);
        DrawRectangle(screen_width - 15, screen_height - 175, 15, 175, WHITE);

        ball.Draw();
        player.Draw();
        cpu.Draw();
        DrawText(TextFormat("%i", player_score), screen_width/2 - 320, 20, 80, WHITE);
        DrawText(TextFormat("%i", cpu_score), screen_width/2 + 320, 20, 80, WHITE);

        EndDrawing();
    }
    

    CloseWindow();
    
    return 0;
}