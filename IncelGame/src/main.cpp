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

#define mapWidth 10
#define mapHeight 10
int mapArray[mapWidth][mapHeight] = {
    
            {1,1,1,1,1,1,1,1,1,1},
            {1,1,0,0,0,0,0,0,1,1},
            {1,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,1},
            {1,1,0,0,0,0,0,0,1,1},
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
    player.dx=cos(player.a)*5;
    player.dy=sin(player.a)*5;
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
        //cout << "Coords: " + to_string(x) + " " + to_string(y) + " Map data: " + to_string(mapArray[x][y]) + " Iterations: " + to_string(iterations) + "\n";

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

//Draw the player angle----------------------------------
void drawPlayerAngle(){
    float endPosX,endPosY;
    Vector2 startPos = {player.x,player.y};
    Vector2 rayDir = {player.x+player.dx*10,player.y+player.dy*10};
    DrawLineV(startPos, rayDir, WHITE);
}

//Draw rays------------------------------------------------------------
void drawRays(){
    float endPosX,endPosY;
    Vector2 startPos = {player.x,player.y};
    Vector2 rayDir = {player.x+player.dx*10,player.y+player.dy*10};

}

//Draw map view-----------------------------------
void drawMapView(){
    drawMap(true);
    DrawFPS(0, 0);
    drawPlayer();
    drawPlayerAngle();
}

//Draw player view--------------------------------------------------
void drawPlayerView(){
    drawRays();
    
}

void init(){
    //Initialize window---------------------------
    InitWindow(500, 500, "Cool Game");
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
  
  int screenWidth = GetScreenWidth();
  int screenHeight = GetScreenHeight();


  //While window is active -------------------
  while (!WindowShouldClose()){

    //Keyboard Input---------------------------------
    bool wPressed;
    bool sPressed;
    bool aPressed;
    bool dPressed;
    bool spacePressed;

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
    player.a =t2*PI/180;
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
