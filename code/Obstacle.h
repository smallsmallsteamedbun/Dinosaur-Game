#pragma once
//Obstacle
extern int Plant_X;//植物从右边出来
extern int Plant_Y;

extern int currentPlant;  // 用于标志当前显示的植物，初始为1，共2个植物，为0表示为陨石

#define METEORITE_COUNT 1// 定义陨石数量
#define Meteorite_width 110
#define Meteorite_height 110

extern double slope[METEORITE_COUNT];//斜率数组
extern double nodal[METEORITE_COUNT];//截距数组

extern struct Meteorite {
	int x;
	int y;
};

#define PLANT_COUNT 2// 定义一组植物数量
#define Plant_height 100
#define Plant_width 65
#define New_Plant_width 50
#define New_Plant_height 50
#define New_Plant_X 300
#define New_Plant_Y 300

#define New_Plant_Frequency 2
//更改转换场景的刷新频率

extern struct Plant
{
	int x;
	int y;
};

extern IMAGE Plant_Img;
extern IMAGE imgNew_Plant;
extern IMAGE Meteorite_Img;
extern IMAGE Boom_Img;//定义爆炸图片

void initializePlants(Plant* plants);
void drawRandomPlants(int currentPlant, Plant plants[], IMAGE Plant_Img);
void Move_Plant(Plant* plants);
void Change_Plant(IMAGE& Plant_Img, int flag);
void Draw_Plant(int x, int y, int New_Plant, IMAGE Plant_img);
bool allOffScreen_Plants(Plant plants[]);
void drawMeteorites(int currentPlant, Meteorite meteorites[], IMAGE Meteorite_Img, IMAGE Boom_Img);
void initializeMeteorite(Meteorite* meteorites, double* slope);
void Move_Meteorites(Meteorite* meteorites, double slope[]);
bool allOffScreen_Meteorite(Meteorite meteorites[]);