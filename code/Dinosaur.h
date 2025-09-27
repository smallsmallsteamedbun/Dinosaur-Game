#pragma once
//Dinosaur
void Show_Dinosaur(int x, int y, IMAGE model);
int Check_Dinosaur(int x, int y, Plant plants[]);
void Show_Collision(int Dinosaur_X, int Dinosaur_Y, int score, struct Button* pause, struct ASH* ash, int Bg_X, int Bg_Y, int Ground_X[]);
void Move_Dinosaur(int& x, int& y, int& flag, int& a);
void Up_Dinosaur(int& x, int& y, int& flag, int& a);
void Down_Dinosaur(int& x, int& y, int& flag);
void Left_Dinosaur(int& x);
void Right_Dinosaur(int& x);
void Change_Dinosaur(int x, int y, IMAGE& Dinosaur_Img, int& flag);
void Show_Score(int score);
void Show_Magic_Array(int x, int y);
void Change_Speed(int score, int& speed);

bool IsChange(int& New_Plant, int& currentPlant, int x, int y);
bool Check_Dinosaur_meteorites(int x, int y, Meteorite meteorites[]);
void Show_First_Dinosaur(int& Dinosaur_X, int Dinosaur_Y, int flag, int Dinosaur_a, int& Dinosaur_flag,
	int& Bg_X, int& Bg_Y, IMAGE BackGround_Img, IMAGE Dinosaur_Img, int* Ground_X, IMAGE Ground_Img,
	int score, struct ASH* ash, int currentPlant);

void FlushInput(ExMessage& m, bool& w, bool& a, bool& s, bool& d);

extern int Dinosaur_X, Dinosaur_Y;//小恐龙位置坐标参数

extern int Dinosaur_a;//小恐龙当前竖直方向加速度，数值代表离开地面的时间长短
//正代表加速度向上，负代表加速度向下
extern int flag;//判断小恐龙是否在地面，0表示在地面，非0表示不在地面
//优化时间的方法（不用每次都判断）

#define Dinosaur_height 86
#define Dinosaur_width 80
#define Dinosaur_site 100

extern IMAGE Dinosaur_Img;