#include "raylib.h"
#include <string.h>
#include <string>
#include <cstring>
#include <stdio.h>
#include <iostream>
#include <fstream> 
#include <sstream> 
#include <math.h>
#include <iterator>
#include <bits/stdc++.h>
#include <algorithm>
#include <iterator>
using namespace std;    

#define screenWidth 500
#define screenHeight 500
#define mapWidth 10
#define mapHeight 10
int mapArray[mapWidth][mapHeight] = {
    
            {1,1,1,1,1,1,1,1,1,1},
            {1,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,1},
            {1,1,1,1,1,1,1,1,1,1} 

    };

//Player Info---------------------------------
struct {
    float x,y; //Player position
    float dx,dy; //Player delta
    float a; //Player angle
} player;

//Draw the player-------------------------------
void drawPlayer(){
    DrawRectangle(player.x-5, player.y-5, 10, 10, WHITE);
}

//Draw the Map-----------------------------------
void drawMap(bool debugMode){ 

    //Initiate the functions variables
    int x = 0;
    int y = 0;
    int iterations = 0;

    for (int i = 0; i <= mapWidth*mapHeight; i++){
    
        //Draw the squares
        if(mapArray[x][y] == 1){
            DrawRectangle(x*50, y*50, 50, 50, WHITE);
            DrawRectangleLines(x*50, y*50, 100, 100, GRAY);
        } else if(mapArray[x][y] == 0) {
            DrawRectangleLines(x*50, y*50, 100, 100, GRAY);
        }


        //Debug info  
        ++iterations;
        if(debugMode == true){
            cout << "Coords: " + to_string(x) + " " + to_string(y) + " Map data: " + to_string(mapArray[x][y]) + " Iterations: " + to_string(iterations) + "\n";
        }

        //Increment the appropriate coordinates        
        if(y == mapHeight-1 && x == mapWidth-1){
            break;
        } else if(x == mapWidth-1){
            ++y;
            x = 0;
        } else {
            ++x;
        }

    }
    
}

float endPosX,endPosY;
int linesIndex;
int lines[500];
Vector2 startPos;
Vector2 rayDir;

//Draw the player angle----------------------------------
void drawPlayerAngle(bool draw){

    for(int t = -250; t < 250; t++){
    player.dx=cos(player.a + (t/(PI*250)))*10;
    player.dy=sin(player.a + (t/(PI*250)))*10;
    linesIndex = t+250;
    
        for(int i = 0; i < 50; i++){
        
            int rayLength = i;
            endPosX = player.x+player.dx*rayLength;
            endPosY = player.y+player.dy*rayLength;
            int endPosGridX = round(endPosX/10);
            int endPosGridY = round(endPosY/10);

            if(endPosGridX%5 == 0 || endPosGridY%5 == 0){ 
                if(mapArray[(endPosGridX) / 5][(endPosGridY) / 5] != 0){
                    startPos = {player.x,player.y};
                    rayDir = {endPosX, endPosY};
                    lines[linesIndex] = i;
                    break;
                }
            }
        }
        if(draw == true){
            DrawLineV(startPos, rayDir, YELLOW);
        }
    }
}

//Draw rays------------------------------------------------------------
void drawRays(){
    for(int i = 0; i < 500; i++){
        char unsigned shading = 255 - lines[i];
        Color wallColor = {shading, shading, shading, 255}; 
        DrawLine(i, (500 - lines[i]), i, 10+lines[i], wallColor);
    }
}

//Draw map view------------------------------------
void drawMapView(){
    drawMap(false);
    DrawFPS(0, 0);
    drawPlayer();
    drawPlayerAngle(true);
}

//Draw player view--------------------------------------------------
void drawPlayerView(){
    drawPlayerAngle(false);
    drawRays();
}

void init(){
    //Initialize window---------------------------
    InitWindow(screenWidth, screenHeight, "Cool Game");
    SetTargetFPS(60);
    //Initialize cursor--------------------
    EnableCursor();  
    //Initialize player--------------------
    player.x = 250;
    player.y = 250;
    player.dx=cos(player.a)*5;
    player.dy=sin(player.a)*5;
    player.a = 0;
}

int main(){
  //Initialize
  init();


  //While window is active -------------------
  while (!WindowShouldClose()){

    //Keyboard Input---------------------------------
    bool wPressed;
    bool sPressed;
    bool aPressed;
    bool dPressed;

    if(IsKeyDown(KEY_W)==true){
        wPressed = true;
    } else {
        wPressed = false;
    }
    if(IsKeyDown(KEY_S)==true){
        sPressed = true;
    } else {
        sPressed = false;
    }
    if(IsKeyDown(KEY_A)==true){
        aPressed = true;
    } else {
        aPressed = false;
    }
    if(IsKeyDown(KEY_D)==true){
        dPressed = true;
    } else {
        dPressed = false;
    }
    //Mouse Input-----------------------------------
    int mouseX = GetMouseX();
    int mouseY = GetMouseY();
    if (GetMouseX() >= screenWidth - 1){
        SetMousePosition(1, mouseY);
    } else if (GetMouseX() <= 0){
        SetMousePosition(screenWidth - 1, mouseY);
    }
    //Movement-------------------------
    if(wPressed == true){
        player.y = player.y - 1;
    } else if (sPressed == true){
        player.y = player.y + 1;
    }
    if(dPressed == true){
        player.x = player.x + 1;
    } else if (aPressed == true){
        player.x = player.x - 1;
    }

    //Mouse movement---------------------------
    int t = mouseX*360;
    int t2 = t/screenWidth;
    player.a = t2*PI/180;
    //Draws the screen---------------------
    BeginDrawing();

    drawMapView();
    //drawPlayerView();

    ClearBackground(BLACK);  
    EndDrawing();

    }

  CloseWindow();
  return 0;
}
