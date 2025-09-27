#pragma once
#include<stdio.h>
#include<windows.h> 
#include<time.h>
#include<math.h>
#include<Easyx.h>
#include <graphics.h>
#include <iostream>
#include<assert.h>
#pragma comment(lib,"winmm.lib")
#pragma comment( lib, "MSIMG32.LIB")

extern int Game_Start_Time;//游戏开始时间
extern int score;//游戏分数

//Game
void Game();
int Timer(int duration, int id);

//引入其他三个部分头文件
#include"Obstacle.h"
#include"Face.h"
#include"Dinosaur.h"