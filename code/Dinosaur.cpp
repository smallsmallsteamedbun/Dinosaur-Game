#include"function_and_state.h"

void Show_Dinosaur(int x, int y, IMAGE model) {
	//putimage(x, y, &model);
	transparentimage3(NULL, x, y, &model);
}

//这个有问题，要判断的应该是碰撞
int Check_Dinosaur(int x, int y, Plant plants[]) {//碰撞为1，无碰撞为0
	for (int i = 0; i < PLANT_COUNT; i++) {
		if (x + Dinosaur_width - 14 > plants[i].x && x < plants[i].x + Plant_width - 14)//水平撞上了
			if (y + Dinosaur_height - 14 > plants[i].y)//竖直撞上了
				return 1;//额外的调整是为了细化边界
		//此处可以更改碰撞检测
	}
	return 0;//无碰撞
}

void Show_Magic_Array(int x, int y) {
	IMAGE Magic_Array, Magic_Array1, Dinosaur_Img;
	loadimage(&Magic_Array, "Data/Magic_Array.png");//100 x 100 魔法阵贴图
	loadimage(&Magic_Array1, "Data/Magic_Array.png", 150, 150);//150 x 150 魔法阵贴图
	loadimage(&Dinosaur_Img, "Data/Dinosaur.png");
	setbkcolor(WHITE);
	//transparentimage3(NULL, x, y, &Dinosaur_Img);
	transparentimage3(NULL, x - 25, y - 20, &Magic_Array);
	FlushBatchDraw();
	Sleep(500);
	cleardevice();
	transparentimage3(NULL, x, y, &Dinosaur_Img);
	transparentimage3(NULL, x - 50, y - 45, &Magic_Array1);
	FlushBatchDraw();
	Sleep(1000);
}

void x2(int& x, int& y, int Dinosaur_Y) {
	y = x * x + Dinosaur_Y - 100;
	x++;
}

void Show_Collision(int Dinosaur_X, int Dinosaur_Y, int score, struct Button* pause, struct ASH* ash, int Bg_X, int Bg_Y, int Ground_X[]) {
	int x = -12, y = Dinosaur_Y;
	while (y < face_height + 100) {
		cleardevice();
		Show_background(Bg_X, Bg_Y, BackGround_Img);//输出背景
		Show_Dinosaur(Dinosaur_X, y, Dinosaur_Img);//打印小恐龙
		Show_Ground(Ground_X, Ground_Y, Ground_Img);
		Show_Score(score);
		Show_Ash(ash);
		Draw_Button(pause);
		FlushBatchDraw();
		x2(x, y, Dinosaur_Y);
		Sleep(5);
	}
	settextcolor(RGB(255, 53, 205));
	setbkmode(TRANSPARENT);
	settextstyle(25, 0, "楷体");
	outtextxy(100, 160, "小恐龙在跑步的时候被绊倒了，摔死了 ");
	outtextxy(100, 190, "跑步不规范，亲人两行泪");
	outtextxy(100, 220, "你的分数：");
	char OUT_score[10];
	sprintf(OUT_score, "%d", score);
	outtextxy(250, 220, OUT_score);//输出变量
}

void Move_Dinosaur(int& x, int& y, int& flag, int& a) {
	y -= a * 3;//由加速度改变速度
	//注意加速度是反过来的，正是往上，y是减小
	a--;
	//加速度肯定是一直往下的嘛
	if (y > face_height - Dinosaur_height - Ground_height) {//落地
		a = 0;
		flag = 0;
		y = face_height - Dinosaur_height - Ground_height;
	}
}

void Change_Dinosaur(int x, int y, IMAGE& Dinosaur_Img, int& flag) {
	flag = flag % 2 + 1; //2 变 1， 1 变 2
	if (flag == 1)
		loadimage(&Dinosaur_Img, "Data/Dinosaur_1.png");//1920 x 480 背景贴图
	else if (flag == 2)
		loadimage(&Dinosaur_Img, "Data/Dinosaur_2.png");//1920 x 480 背景贴图
}

void Up_Dinosaur(int& x, int& y, int& flag, int& a) {
	if (flag != 0)
		return;//你都不在地上，你跳个鬼你跳
	else if (flag == 0) {//在地上，可以起跳
		//PlaySound("Data/jump.wav", NULL, SND_SYNC);//很卡
		mciSendString("close Data/jump.mp3", 0, 0, 0);
		mciSendString("open Data/jump.mp3", 0, 0, 0);
		mciSendString("play Data/jump.mp3", 0, 0, 0);// 播放音频文件
		a = 12;//向上跳赋予向上10的加速度
		flag = 1;//状态标为不在地面
	}
}

void Down_Dinosaur(int& x, int& y, int& flag) {

}

void Left_Dinosaur(int& x) {
	if (x > 0)
		x -= 1;
}

void Right_Dinosaur(int& x) {
	if (x < face_width - Dinosaur_width)
		x += 1;
}

void Show_First_Dinosaur(int& Dinosaur_X, int Dinosaur_Y, int flag, int Dinosaur_a, int& Dinosaur_flag,
	int& Bg_X, int& Bg_Y, IMAGE BackGround_Img, IMAGE Dinosaur_Img, int* Ground_X, IMAGE Ground_Img,
	int score, struct ASH* ash, int currentPlant) {
	BeginBatchDraw();
	while (Dinosaur_X < Dinosaur_site) {
		cleardevice();
		if (Timer(18, 0) == 1)
			Move_Dinosaur(Dinosaur_X, Dinosaur_Y, flag, Dinosaur_a);//小恐龙的位置更新函数，可能要改变flag的值
		if (Timer(8, 1) == 1)
			Move_Ground(Ground_X);
		if (Timer(30, 2) == 1)
			Move_BackGround(Bg_X, Bg_Y);
		if (Timer(20, 3) == 1)
			Move_Ash(ash, currentPlant);
		if (Timer(50, 4) == 1)
			Change_Dinosaur(Dinosaur_X, Dinosaur_Y, Dinosaur_Img, Dinosaur_flag);
		Show_background(Bg_X, Bg_Y, BackGround_Img);//输出背景
		Show_Dinosaur(Dinosaur_X, Dinosaur_Y, Dinosaur_Img);//打印小恐龙
		Show_Ground(Ground_X, Ground_Y, Ground_Img);
		Show_Score(score);
		Show_Ash(ash);
		Show_Name(currentPlant);
		FlushBatchDraw();
		Dinosaur_X++;
	}
	EndBatchDraw();
}
void Show_Score(int score) {
	setbkmode(TRANSPARENT);
	settextcolor(RGB(255, 255, 255));
	settextstyle(30, 0, "Old English Text MT");
	outtextxy(20, 20, "Score:");
	char OUT_score[10];
	sprintf(OUT_score, "%d", score);
	outtextxy(95, 20, OUT_score);//输出变量
}

bool IsChange(int& New_Plant,int &currentPlant, int x, int y) {
	if (New_Plant % New_Plant_Frequency == 0) {
		if (x + Dinosaur_width < New_Plant_X || x > New_Plant_width + New_Plant_X)//水平方向没撞到
			return 0;
		if (y + Dinosaur_height < New_Plant_Y || y > New_Plant_Y + New_Plant_height)//竖直方向没撞到
			return 0;
		currentPlant += 1;//currentPlant 从-1,0,1一直轮换，代表三种植物状态
		/*if (currentPlant == 2)
			currentPlant = -1;*/
		//更改了游戏结局
		//currentPlant从-1,0,1到2，就结束了
		New_Plant++;
		return 1;
	}
	return 0;
}

bool Check_Dinosaur_meteorites(int x, int y, Meteorite meteorites[]) {
	for (int i = 0; i < METEORITE_COUNT; i++) {
		if (x + Dinosaur_width - 14 > meteorites[i].x && x < meteorites[i].x + Meteorite_width - 50)//水平撞上了
			if (y + Dinosaur_height - 14 > meteorites[i].y && y < meteorites[i].y + Meteorite_height - 14)//竖直撞上了
				return 1;//额外的调整是为了细化边界
	}
	return 0;//无碰撞
}

void FlushInput(ExMessage& m, bool& w, bool& a, bool& s, bool& d) {//真的把细节优化到极致了
	//防止 "自动操控" 的情况
	m.message = 257;//让按键抬起
	m.vkcode = 0;//不给输入
	w = a = s = d = false;//重置按键
}

void Change_Speed(int score, int& speed) {//四秒增加一次移速
	speed = score / 5000;
	if (speed > 5)//速度上限为 5
		speed = 5;
}