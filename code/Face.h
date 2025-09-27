#pragma once
//Face
void transparentimage3(IMAGE* dstimg, int x, int y, IMAGE* srcimg); //新版png，透明贴图
void initface();
void Play_Button_Music();
int MainFace();
int Show_Main_Sketchpad();
void Show_background(int x, int y, IMAGE model);//输出背景
void Move_BackGround(int& Bg_X, int& Bg_Y);

void Show_Ground(int x[], int y, IMAGE model);
void Move_Ground(int* x);

void Change_BackGround(int currentPlant, int x, int y, IMAGE& BackGround_Img);
int Show_Pause(int Bg_X, int Bg_Y, IMAGE BackGround_Img, int Dinosaur_X, int Dinosaur_Y, IMAGE Dinosaur_Img,
	int currentPlant, Plant plants[], IMAGE Plant_Img, int* Ground_X, IMAGE Ground_Img, int score, struct ASH* ash,
	int New_Plant, IMAGE imgNew_Plant, Meteorite* meteorites, IMAGE Meteorite_Img, IMAGE Boom_Img);
int Show_Game_Sketchpad(int Bg_X, int Bg_Y, IMAGE BackGround_Img, int Dinosaur_X, int Dinosaur_Y, IMAGE Dinosaur_Img,
	int currentPlant, Plant plants[], IMAGE Plant_Img, int* Ground_X, IMAGE Ground_Img, int score, struct ASH* ash,
	int New_Plant, IMAGE imgNew_Plant, Meteorite* meteorites, IMAGE Meteorite_Img, IMAGE Boom_Img, int Game_Status);
void Show_Name(int currentPlant);

struct Button* createButton(int x, int y, int width, int height, const char* str, COLORREF inColor, COLORREF outColor);
void Draw_Button(struct Button* pB);
bool isInButton(struct Button* pB, ExMessage m);
bool isClickButton(struct Button* pB, ExMessage m);

void InitAshFirst(struct ASH* ash, int currentPlant);
void Move_Ash(struct ASH* ash, int currentPlant);
void Show_Ash(struct ASH* ash);

#define Menu_X 220
#define Menu_Y 100
#define Menu_width 180
#define Menu_height 250
#define Button_width 180
#define Button_height 60
#define Button_X 220
#define Button_Y_1 100
#define Button_Y_2 190
#define Button_Y_3 285

#define Sketchpad_X 50
#define Sketchpad_Y 50
#define Sketchpad_width 540
#define Sketchpad_height 375
#define Button_Back_X 335
#define Button_Back_Y 335
#define Button_Back_width 90
#define Button_Back_height 30

#define Text_size 17
#define Text_X 120
#define Text_Y_1 160
#define Text_Y_2 Text_Y_1+Text_size
#define Text_Y_3 Text_Y_1+Text_size*2
#define Text_Y_4 Text_Y_1+Text_size*3
#define Text_Y_5 Text_Y_1+Text_size*4
#define Text_Y_6 Text_Y_1+Text_size*5
#define Text_Y_7 Text_Y_1+Text_size*6
#define Text_Y_8 Text_Y_1+Text_size*7

extern int Bg_X, Bg_Y;

#define BackGround_height 480
#define BackGround_width 1920

#define Ground_height 37
#define Ground_width 1095
#define Ground_width_1 250
#define Ground_width_2 290
#define Ground_width_3 290
#define Ground_width_4 274
#define Ground_Y 387
//Ground_Y = face_height - Ground_height

extern int Ground_X[2];
extern int Ground_Flag;//交替贴图操作

//尺寸设置
#define face_height 480
#define face_width 640

extern IMAGE BackGround_Img;
extern IMAGE Ground_Img;//交替贴图
extern IMAGE Menu_Img;

#define MAXASH 70	//微粒个数

extern struct ASH {
	double	x;//x坐标
	int		y;//y坐标
	double	step;//移动速度
	int		color;//颜色
};

extern struct Button {
	int x, y, width, height;
	COLORREF inColor, outColor, curColor;
	char* text;
};