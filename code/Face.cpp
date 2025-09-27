#include"function_and_state.h"

void transparentimage3(IMAGE* dstimg, int x, int y, IMAGE* srcimg) //新版png，透明贴图
{
	HDC dstDC = GetImageHDC(dstimg);
	HDC srcDC = GetImageHDC(srcimg);
	int w = srcimg->getwidth();
	int h = srcimg->getheight();
	BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
	AlphaBlend(dstDC, x, y, w, h, srcDC, 0, 0, w, h, bf);
}

void Draw_Out_Button(int x, int y, int w, int h, char* text)//画鼠标不在里面的矩形样子
{
	setbkmode(TRANSPARENT);
	setfillcolor(RGB(184, 70, 11));
	fillroundrect(x, y, x + w, y + h, 10, 10);
	settextstyle(30, 0, "黑体");
	settextcolor(RGB(255, 240, 224));

	int tx = x + (w - textwidth(text)) / 2;
	int ty = y + (h - textheight(text)) / 2;

	outtextxy(tx, ty, text);
}

void Draw_All_Out_Button(char* Begin_Game, char* Game_Story, char* Exit_Game) {
	Draw_Out_Button(Button_X, Button_Y_1, Button_width, Button_height, Begin_Game);
	Draw_Out_Button(Button_X, Button_Y_2, Button_width, Button_height, Game_Story);
	Draw_Out_Button(Button_X, Button_Y_3, Button_width, Button_height, Exit_Game);//绘制鼠标不在里面的样子
}

void Draw_In_Button(int x, int y, int w, int h, char* text) {//画鼠标在矩形里面的样子（其实只有颜色区别）
	setbkmode(TRANSPARENT);
	setfillcolor(RGB(244, 164, 96));
	fillroundrect(x, y, x + w, y + h, 10, 10);
	settextcolor(RGB(rand() % 256, rand() % 256, rand() % 256));
	settextstyle(30, 0, "黑体");

	int tx = x + (w - textwidth(text)) / 2;
	int ty = y + (h - textheight(text)) / 2;

	outtextxy(tx, ty, text);
}

void Play_Button_Music() {
	mciSendString("close Data/click.mp3 ", 0, 0, 0);
	mciSendString("open Data/click.mp3", 0, 0, 0);
	mciSendString("play Data/click.mp3", 0, 0, 0);
}

void initface() {//初始化界面
	initgraph(640, 480);
	mciSendString("open data/Bg_music.mp3", 0, 0, 0);
	mciSendString("play data/Bg_music.mp3 repeat", 0, 0, 0);
	setbkcolor(WHITE);
}
void Draw_Menu(IMAGE Menu_Img) {
	transparentimage3(NULL, Menu_X, Menu_Y, &Menu_Img);
}
int MainFace() {//主页页面
	settextcolor(RGB(255, 240, 224));
	setbkmode(TRANSPARENT);
	IMAGE Menu_Img;
	loadimage(&Menu_Img, "Data/Menu.png");
	char Begin_Game[20] = "1.开始游戏";
	char Game_Story[20] = "2.游戏背景";
	char Exit_Game[20] = "3.退出游戏";
	ExMessage msg;
	int currentPlant = -1;
	int Bg_X = 0, Bg_Y = 0;
	int Ground_X[2] = { 0,Ground_width };
	struct ASH ash[MAXASH];
	srand(time(NULL));
	InitAshFirst(ash, -1);
	loadimage(&BackGround_Img, "Data/bg_-1.jpg");//1920 x 480 背景贴图
	loadimage(&Ground_Img, "Data/ground.png");//1905 x 93 地面贴图
	BeginBatchDraw();
	while (true) {
		cleardevice();
		Show_background(Bg_X, Bg_Y, BackGround_Img);//输出背景
		Show_Ground(Ground_X, Ground_Y, Ground_Img);
		Show_Ash(ash);
		transparentimage3(NULL, Menu_X, Menu_Y, &Menu_Img);
		Draw_All_Out_Button(Begin_Game, Game_Story, Exit_Game);//绘制鼠标不在里面的样子
		if (Timer(8, 1) == 1) {
			Move_Ground(Ground_X);
		}
		if (Timer(30, 2) == 1)
			Move_BackGround(Bg_X, Bg_Y);
		if (Timer(20, 3) == 1)
			Move_Ash(ash, currentPlant);
		peekmessage(&msg, EM_MOUSE);
		if (msg.x >= Button_X && msg.x <= Button_X + Button_width && msg.y >= Button_Y_1 && msg.y <= Button_Y_1 + Button_height)
		{
			Draw_In_Button(Button_X, Button_Y_1, Button_width, Button_height, Begin_Game);//绘制鼠标在里面的样子
			if (msg.message == WM_LBUTTONUP) {
				Play_Button_Music();
				return 1;
			}
		}
		else if (msg.x >= Button_X && msg.x <= Button_X + Button_width && msg.y >= Button_Y_2 && msg.y <= Button_Y_2 + Button_height)
		{
			Draw_In_Button(Button_X, Button_Y_2, Button_width, Button_height, Game_Story);//绘制鼠标在里面的样子
			if (msg.message == WM_LBUTTONUP) {
				Play_Button_Music();
				return 2;
			}
		}
		else if (msg.x >= Button_X && msg.x <= Button_X + Button_width && msg.y >= Button_Y_3 && msg.y <= Button_Y_3 + Button_height)
		{
			Draw_In_Button(Button_X, Button_Y_3, Button_width, Button_height, Exit_Game);//绘制鼠标在里面的样子
			if (msg.message == WM_LBUTTONUP) {
				Play_Button_Music();
				return 3;
			}
		}
		FlushBatchDraw();
	}
	EndBatchDraw();
}

void Show_background(int x, int y, IMAGE model) {//输出背景
	putimage(x, y, &model);
}

void Move_BackGround(int& Bg_X, int& Bg_Y) {//背景移动
	Bg_X -= 1;
	if (Bg_X + BackGround_width <= face_width)
		Bg_X = 0;
}

void Show_Ground(int x[], int y, IMAGE model) {//输出背景
	transparentimage3(NULL, x[0], y, &model);
	transparentimage3(NULL, x[1], y, &model);//输出两张贴图，轮流输出
}

void Change_BackGround(int currentPlant, int x, int y, IMAGE& BackGround_Img) {
	Show_Magic_Array(x, y);
	if (currentPlant == -1)
		loadimage(&BackGround_Img, "Data/bg_-1.jpg", 1920, 480);//1920 x 480 背景贴图
	else if (currentPlant == 0)
		loadimage(&BackGround_Img, "Data/bg_0.jpg", 1920, 480);//1920 x 480 背景贴图
	else if (currentPlant == 1)
		loadimage(&BackGround_Img, "Data/bg_1.jpg");//1920 x 480 背景贴图
}

void Move_Ground(int* x) {//移动地面
	x[0] -= 3;
	x[1] -= 3;
	if (x[0] + Ground_width < 0) 
		x[0] = x[1] + Ground_width;//重置位置
	if (x[1] + Ground_width < 0)
		x[1] = x[0] + Ground_width;//重置位置
}

int Show_Pause(int Bg_X, int Bg_Y, IMAGE BackGround_Img, int Dinosaur_X, int Dinosaur_Y, IMAGE Dinosaur_Img,
	int currentPlant, Plant plants[], IMAGE Plant_Img, int* Ground_X, IMAGE Ground_Img, int score, struct ASH* ash,
	int New_Plant, IMAGE imgNew_Plant, Meteorite* meteorites, IMAGE Meteorite_Img, IMAGE Boom_Img) {
	IMAGE Menu_Img;
	loadimage(&Menu_Img, "Data/Menu.png");
	char Resume_Game[20] = "1.继续游戏";
	char Game_Key[20] = "2.游戏按键";
	char Back_Face[20] = "3.返回主页";
	ExMessage msg;
	BeginBatchDraw();
	while (true) {
		cleardevice();
		Show_background(Bg_X, Bg_Y, BackGround_Img);//输出背景
		Show_Dinosaur(Dinosaur_X, Dinosaur_Y, Dinosaur_Img);//打印小恐龙
		drawRandomPlants(currentPlant, plants, Plant_Img);//打印每一个障碍物
		Show_Ground(Ground_X, Ground_Y, Ground_Img);
		Show_Ash(ash);
		Draw_Plant(New_Plant_X, New_Plant_Y, New_Plant, imgNew_Plant);
		drawMeteorites(currentPlant, meteorites, Meteorite_Img, Boom_Img);
		Show_Name(currentPlant);
		Show_Score(score);
		transparentimage3(NULL, Menu_X, Menu_Y, &Menu_Img);
		Draw_All_Out_Button(Resume_Game, Game_Key, Back_Face);//绘制鼠标不在里面的样子
		if (Timer(20, 3) == 1)
			Move_Ash(ash, currentPlant);
		peekmessage(&msg, EM_MOUSE);
		if (msg.x >= Button_X && msg.x <= Button_X + Button_width && msg.y >= Button_Y_1 && msg.y <= Button_Y_1 + Button_height)
		{
			Draw_In_Button(Button_X, Button_Y_1, Button_width, Button_height, Resume_Game);//绘制鼠标在里面的样子
			if (msg.message == WM_LBUTTONUP) {//继续游戏
				Play_Button_Music();
				return 1;
			}
		}
		else if (msg.x >= Button_X && msg.x <= Button_X + Button_width && msg.y >= Button_Y_2 && msg.y <= Button_Y_2 + Button_height)
		{
			Draw_In_Button(Button_X, Button_Y_2, Button_width, Button_height, Game_Key);//绘制鼠标在里面的样子
			if (msg.message == WM_LBUTTONUP) {
				Play_Button_Music();//游戏操作
				return 2;
			}
		}
		else if (msg.x >= Button_X && msg.x <= Button_X + Button_width && msg.y >= Button_Y_3 && msg.y <= Button_Y_3 + Button_height)
		{
			Draw_In_Button(Button_X, Button_Y_3, Button_width, Button_height, Back_Face);//绘制鼠标在里面的样子
			if (msg.message == WM_LBUTTONUP) {
				Play_Button_Music();//返回主页
				return 3;
			}
		}

		FlushBatchDraw();
		//printf("%d,%d,%d\n", clock(), msg.x, msg.y);//获取鼠标坐标
		//Sleep(200);
	}
	EndBatchDraw();
}

void Show_Name(int currentPlant) {
	settextcolor(RGB(255, 255, 255));
	settextstyle(30, 0, "楷体");
	setbkmode(TRANSPARENT);
	if (currentPlant == -1)
		outtextxy(200, 20, "炎炎沙漠");
	if (currentPlant == 0)
		outtextxy(200, 20, "灼灼火山");
	if (currentPlant == 1)
		outtextxy(200, 20, "静谧夜晚");
}

int Show_Main_Sketchpad() {//游戏背景
	setbkmode(TRANSPARENT);
	IMAGE Sketchpad_Img;
	loadimage(&Sketchpad_Img, "Data/Sketchpad.png");
	char Back[10] = "返回";
	ExMessage msg;
	int currentPlant = 1;
	int Bg_X = 0, Bg_Y = 0;
	int Ground_X[2] = { 0,Ground_width };
	struct ASH ash[MAXASH];
	srand(time(NULL));
	InitAshFirst(ash, -1);
	loadimage(&BackGround_Img, "Data/bg_1.jpg");//1920 x 480 背景贴图
	loadimage(&Ground_Img, "Data/ground.png");//1905 x 93 地面贴图
	BeginBatchDraw();
	while (true) {
		cleardevice();
		Show_background(Bg_X, Bg_Y, BackGround_Img);//输出背景
		Show_Ground(Ground_X, Ground_Y, Ground_Img);
		Show_Ash(ash);
		transparentimage3(NULL, Sketchpad_X, Sketchpad_Y, &Sketchpad_Img);
		Draw_Out_Button(Button_Back_X, Button_Back_Y, Button_Back_width, Button_Back_height, Back);
		settextstyle(Text_size, 0, "黑体");// 设置文字
		settextcolor(RGB(244, 164, 96));
		outtextxy(Text_X, Text_Y_1, "    在史前时代的某个角落，有一只可爱的小恐龙，");
		outtextxy(Text_X, Text_Y_2, "它的家园正受到巨大的威胁。原本安宁的恐龙世界");
		outtextxy(Text_X, Text_Y_3, "因为一场灾难而面临灭绝的危机。火山爆发和陨石");
		outtextxy(Text_X, Text_Y_4, "撞击将整个地区变成了一片混乱和危险的地带。");//逐行输入
		outtextxy(Text_X, Text_Y_5, "    小恐龙必须勇敢地踏上逃生之旅，通过各种考");//逐行输入
		outtextxy(Text_X, Text_Y_6, "验和障碍来寻求生存。");//逐行输入
		outtextxy(Text_X, Text_Y_7, "    玩家将操作小恐龙，帮助它跳跃、奔跑、躲避");//逐行输入
		outtextxy(Text_X, Text_Y_8, "障碍物，尽可能远离灾难，找到新的安全之地。");//逐行输入
		if (Timer(8, 1) == 1) {
			Move_Ground(Ground_X);
		}
		if (Timer(30, 2) == 1)
			Move_BackGround(Bg_X, Bg_Y);
		if (Timer(20, 3) == 1)
			Move_Ash(ash, currentPlant);
		peekmessage(&msg, EM_MOUSE);
		if (msg.x >= Button_Back_X && msg.x <= Button_Back_X + Button_Back_width && msg.y >= Button_Back_Y && msg.y <= Button_Back_Y + Button_Back_height)
		{
			Draw_In_Button(Button_Back_X, Button_Back_Y, Button_Back_width, Button_Back_height, Back);
			if (msg.message == WM_LBUTTONUP) {
				Play_Button_Music();
				return 1;
			}
		}
		FlushBatchDraw();
	}
	EndBatchDraw();
}

int Show_Game_Sketchpad(int Bg_X, int Bg_Y, IMAGE BackGround_Img, int Dinosaur_X, int Dinosaur_Y, IMAGE Dinosaur_Img,
	int currentPlant, Plant plants[], IMAGE Plant_Img, int* Ground_X, IMAGE Ground_Img, int score, struct ASH* ash,
	int New_Plant, IMAGE imgNew_Plant, Meteorite* meteorites, IMAGE Meteorite_Img, IMAGE Boom_Img, int Game_Status) {
	//暂停,死亡和通关都有，只有字不一样
	//Game_Status 为1，暂停
	//Game_Status 为2，死亡
	//Game_Status 为3，通关
	IMAGE Sketchpad_Img;
	loadimage(&Sketchpad_Img, "Data/Sketchpad.png");
	char Back[10] = "返回";
	ExMessage msg;
	BeginBatchDraw();
	while (true) {
		cleardevice();
		Show_background(Bg_X, Bg_Y, BackGround_Img);//输出背景
		Show_Dinosaur(Dinosaur_X, Dinosaur_Y, Dinosaur_Img);//打印小恐龙
		drawRandomPlants(currentPlant, plants, Plant_Img);//打印每一个障碍物
		Show_Ground(Ground_X, Ground_Y, Ground_Img);
		Show_Ash(ash);
		Draw_Plant(New_Plant_X, New_Plant_Y, New_Plant, imgNew_Plant);
		drawMeteorites(currentPlant, meteorites, Meteorite_Img, Boom_Img);
		Show_Name(currentPlant);
		Show_Score(score);
		transparentimage3(NULL, Sketchpad_X, Sketchpad_Y, &Sketchpad_Img);
		Draw_Out_Button(Button_Back_X, Button_Back_Y, Button_Back_width, Button_Back_height, Back);
		settextstyle(Text_size, 0, "黑体");// 设置文字
		settextcolor(RGB(244, 164, 96));
		if (Game_Status == 1) {//暂停,显示游戏操作
			outtextxy(Text_X, Text_Y_2, "  跳跃：w W ↑");
			outtextxy(Text_X, Text_Y_3, "  左移：a A ←");
			outtextxy(Text_X, Text_Y_4, "  右移：d D →");//逐行输入
			outtextxy(Text_X, Text_Y_5, "  请让鼠标保持稳定");//逐行输入
		}
		else if (Game_Status == 2) {//死亡
			outtextxy(Text_X, Text_Y_2, "  很遗憾，小恐龙没有逃离威胁");
			outtextxy(Text_X, Text_Y_3, "  你的分数：");
			char OUT_score[10];
			sprintf(OUT_score, "%d", score);
			outtextxy(Text_X + 130, Text_Y_3, OUT_score);//输出变量
		}
		else if (Game_Status == 3) {//通关
			outtextxy(Text_X, Text_Y_1, "  你的分数：");
			char OUT_score[10];
			sprintf(OUT_score, "%d", score);
			outtextxy(Text_X + 130, Text_Y_1, OUT_score);//输出变量
			outtextxy(Text_X, Text_Y_2, "    小恐龙们成功逃离了自然灾害，进入了人类时");
			outtextxy(Text_X, Text_Y_3, "代。然而，人类对恐龙充满了好奇和贪婪，开始大");
			outtextxy(Text_X, Text_Y_4, "规模猎杀。");
			outtextxy(Text_X, Text_Y_5, "    小恐龙们不断躲藏，但人类的技术和策略越发");//逐行输入
			outtextxy(Text_X, Text_Y_6, "先进。终究，它们没能逃脱人类的捕获而灭绝，化");//逐行输入
			outtextxy(Text_X, Text_Y_7, "作了历史的尘埃。");//逐行输入
			outtextxy(Text_X, Text_Y_8, "    灭绝生物的，真的是自然灾害吗？");//逐行输入
		}
		
		if (Timer(20, 3) == 1)
			Move_Ash(ash, currentPlant);
		peekmessage(&msg, EM_MOUSE);
		if (msg.x >= Button_Back_X && msg.x <= Button_Back_X + Button_Back_width && msg.y >= Button_Back_Y && msg.y <= Button_Back_Y + Button_Back_height)
		{
			Draw_In_Button(Button_Back_X, Button_Back_Y, Button_Back_width, Button_Back_height, Back);
			if (msg.message == WM_LBUTTONUP) {
				Play_Button_Music();
				return 1;//唯一的返回键操作
			}
		}
		FlushBatchDraw();
	}
	EndBatchDraw();
}

struct Button* createButton(int x, int y, int width, int height, const char* str, COLORREF inColor, COLORREF outColor) {
	struct Button* pB = new struct Button;
	//assert(pB);
	pB->x = x;
	pB->y = y;
	pB->width = width;
	pB->height = height;
	pB->inColor = inColor;
	pB->outColor = outColor;
	pB->curColor = outColor;
	int textLength = strlen(str) + 1;
	pB->text = new char[textLength];
	//assert(pB->text);
	strcpy_s(pB->text, textLength, str);
	return pB;
}

void Draw_Button(struct Button* pB) {
	setfillcolor(pB->curColor);
	fillrectangle(pB->x, pB->y, pB->x + pB->width, pB->y + pB->height);
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(30, 0, "楷体");
	outtextxy(pB->x + (pB->width - textwidth(pB->text)) / 2, pB->y + (pB->height - textheight(pB->text)) / 2, pB->text);
}

bool isInButton(struct Button* pB, ExMessage m) {
	if (m.x > pB->x && m.x<pB->x + pB->width && m.y>pB->y && m.y < pB->y + pB->height) {
		pB->curColor = pB->inColor;
		return true;
	}
	pB->curColor = pB->outColor;
	return false;
}

bool isClickButton(struct Button* pB, ExMessage m) {
	if (isInButton(pB, m) && m.message == 514) {//WM_LBUTTONDBLCLK 左键按下就是 514的信息，莫名其妙的BUG
		Play_Button_Music();
		return true;
	}
	return false;
}

void InitAshFirst(struct ASH* ash, int currentPlant) {
	for (int i = 0; i < MAXASH; i++) {
		ash[i].x = face_width;//x初始坐标为0
		ash[i].y = rand() % face_height;//随机产生y坐标
		ash[i].step = (rand() % 5000) / 1000.0 + 1;
		if (currentPlant == -1)//第一个场景
			ash[i].color = RGB(200, rand() % 85 + 115, rand() % 45);//设置颜色棕色
		if (currentPlant == 0)//第二个场景
			ash[i].color = RGB(255, rand() % 230, rand() % 90);//设置颜色红色
		if (currentPlant == 1)//第三个场景
			ash[i].color = RGB(rand() % 255, rand() % 255, rand() % 255);//设置颜色彩色
	}
}

void InitAsh(struct ASH* ash, int i, int currentPlant) {
	ash[i].x = face_width;//x初始坐标为0
	ash[i].y = rand() % face_height;//随机产生y坐标
	ash[i].step = (rand() % 5000) / 1000.0 + 1;
	if (currentPlant == -1)//第一个场景
		ash[i].color = RGB(200, rand() % 85 + 115, rand() % 45);//设置颜色棕色
	if (currentPlant == 0)//第二个场景
		ash[i].color = RGB(255, rand() % 230, rand() % 90);//设置颜色红色
	if (currentPlant == 1)//第三个场景
		ash[i].color = RGB(rand() % 255, rand() % 255, rand() % 255);//设置颜色彩色
}

void Move_Ash(struct ASH* ash, int currentPlant) {
	for (int i = 0; i < MAXASH; i++) {
		ash[i].x -= ash[i].step;//获取位置
		if (ash[i].x < 0)
			InitAsh(ash, i, currentPlant);//越界后重新生成星星
	}
}

void Show_Ash(struct ASH* ash) {
	for (int i = 0; i < MAXASH; i++) {
		putpixel((int)ash[i].x, ash[i].y, ash[i].color);
		putpixel((int)ash[i].x + 1, ash[i].y + 1, ash[i].color);
		putpixel((int)ash[i].x + 1, ash[i].y, ash[i].color);
		putpixel((int)ash[i].x, ash[i].y + 1, ash[i].color);
	}
}