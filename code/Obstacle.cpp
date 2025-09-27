#include"function_and_state.h"
void initializePlants(Plant* plants)//初始化植物
{
	plants[0].x = face_width;
	plants[0].y = face_height - Plant_height - Ground_height;;
	// 初始化植物的随机位置
	for (int i = 1; i < PLANT_COUNT; ++i)
	{
		plants[i].x = plants[i - 1].x + rand() % 600 + 310;
		plants[i].y = face_height - Plant_height - Ground_height;
	}
}

void Change_Plant(IMAGE& Plant_Img, int flag) {
	//flag = flag % 2 + 1; //2 变 1， 1 变 2
	if (flag == -1)
		loadimage(&Plant_Img, "Data/Plant_-1.png");
	else if (flag == 1)
		loadimage(&Plant_Img, "Data/Plant_1.png");
}

void Move_Plant(Plant* plants) {
	for (int i = 0; i < PLANT_COUNT; ++i)
		plants[i].x = plants[i].x - 3;
}

void drawRandomPlants(int currentPlant, Plant plants[], IMAGE Plant_Img)//绘制植物
{
	if (currentPlant) {//currentPlant才输出植物
		for (int i = 0; i < PLANT_COUNT; ++i)
			// 判断当前标志并调用相应的植物绘制函数
			transparentimage3(NULL, plants[i].x, plants[i].y, &Plant_Img);//输出图像
	}
}

//绘制穿越
void Draw_Plant(int x, int y, int New_Plant, IMAGE Plant_Img) // 打印植物
{
	if (New_Plant % 2 == 0)
		transparentimage3(NULL, x, y, &Plant_Img);
}

bool allOffScreen_Plants(Plant plants[]) {
	if (plants[PLANT_COUNT - 1].x > -110) //判断一组中最后一个植物的位置
		return false;
	return true;
}

void drawMeteorites(int currentPlant, Meteorite meteorites[], IMAGE Meteorite_Img, IMAGE Boom_Img)//绘制陨石
{
	if (!currentPlant) {//currentPlant才显示陨石
		for (int i = 0; i < METEORITE_COUNT; ++i)
		{
			transparentimage3(NULL, meteorites[i].x, meteorites[i].y, &Meteorite_Img);//输出图像
			if (meteorites[i].y < 420 && meteorites[i].y>380)
			{
				transparentimage3(NULL, meteorites[i].x, meteorites[i].y, &Boom_Img);//输出图像
			}
			if (meteorites[i].y < 40 && meteorites[i].y>0)
			{
				mciSendString("close Data/boom.mp3", 0, 0, 0);
				mciSendString("open Data/boom.mp3", 0, 0, 0);
				mciSendString("play Data/boom.mp3", 0, 0, 0);// 播放音频文件
			}
		}
	}
}

void initializeMeteorite(Meteorite *meteorites, double* slope)//初始化陨石
{
	meteorites[0].x = 640 + rand() % 300; //右上角
	meteorites[0].y = 0;

	for (int i = 0; i < METEORITE_COUNT; ++i)//随机斜率
	{
		slope[i] = 1 + ((double)rand() / RAND_MAX) * (2 - 1);//生成 1 到 2 之间的随机浮点数 
	}

	for (int i = 1; i < METEORITE_COUNT; ++i)//随机x，y坐标
	{
		meteorites[i].x = meteorites[i - 1].x + rand() % 300 + 110;
		meteorites[i].y = meteorites[i - 1].y + 480;
	}

}

void Move_Meteorites(Meteorite* meteorites, double slope[]) {
	for (int i = 0; i < METEORITE_COUNT; ++i)
	{
		meteorites[i].x = meteorites[i].x - 3;
		meteorites[i].y = -slope[i] * meteorites[i].x + 600.0;
	}
}

bool allOffScreen_Meteorite(Meteorite meteorites[]) {
	for (int i = 0; i < METEORITE_COUNT; ++i)
	{
		if (meteorites[METEORITE_COUNT - 1].x > -110) //判断一组中最后一个陨石的位置
		{
			return 0;
		}
	}
	return 1;
}