#include"function_and_state.h"

//定时器，可以分别控制每个东西刷新的时间
int Timer(int duration, int id) {
	static int startTime[10];
	int endTime = clock();
	if (endTime - startTime[id] > duration) {
		startTime[id] = endTime;
		return 1;
	}
	return 0;
}

IMAGE Dinosaur_Img;
IMAGE BackGround_Img;
IMAGE Ground_Img;//交替贴图
IMAGE Plant_Img;
IMAGE imgNew_Plant;
IMAGE Meteorite_Img;
IMAGE Boom_Img;

void Game() {
	int Dinosaur_X = 0, Dinosaur_Y = face_height - Dinosaur_height - Ground_height;//小恐龙位置坐标参数
	int Dinosaur_flag = 1;//小恐龙换脚
	int Bg_X = 0, Bg_Y = 0;
	int Ground_X[2] = { 0,Ground_width };
	int Ground_Flag = 0;//交替贴图操作
	int Dinosaur_a = 0;//小恐龙当前竖直方向加速度，数值代表离开地面的时间长短
	//正代表加速度向上，负代表加速度向下
	int flag = 0;//判断小恐龙是否在地面，0表示在地面，非0表示不在地面
	//优化时间的方法（不用每次都判断）
	int Game_Start_Time = clock();//游戏开始时间
	int score = 0;//游戏分数

	struct ASH ash[MAXASH];
	srand(time(NULL));
	InitAshFirst(ash, -1);

	struct Button* pause = createButton(540, 0, 100, 66, "Pause", RGB(254, 233, 82), RGB(247, 172, 70));//暂停按钮

	loadimage(&Dinosaur_Img, "Data/Dinosaur_1.png");//47 x 50 恐龙贴图
	loadimage(&BackGround_Img, "Data/bg_-1.jpg");//1920 x 480 背景贴图
	loadimage(&Ground_Img, "Data/ground.png");//1905 x 93 地面贴图

	Plant plants[PLANT_COUNT];
	loadimage(&imgNew_Plant, "Data/new_plant.png");//新植物路径
	loadimage(&Plant_Img, "Data/Plant_-1.png");//70 x 100 植物贴图
	initializePlants(plants);//初始化植物位置
	int currentPlant = -1;  // 用于标志当前显示的植物，初始为-1，共2个植物，为0则表示为陨石,在-1,0,1循环
	int New_Plant = 1;

	Meteorite meteorites[METEORITE_COUNT];
	double slope[METEORITE_COUNT];//斜率数组
	initializeMeteorite(meteorites, slope);//初始化陨石
	loadimage(&Meteorite_Img, "Data/meteorite.png");
	loadimage(&Boom_Img, "Data/boom.png");
	Show_First_Dinosaur(Dinosaur_X, Dinosaur_Y, flag, Dinosaur_a, Dinosaur_flag,
		Bg_X, Bg_Y, BackGround_Img, Dinosaur_Img, Ground_X, Ground_Img,
		score, ash, currentPlant);

	int speed = 0;//随时间移动越来越快

	BeginBatchDraw();//一帧内输出的东西
	ExMessage m;
	bool w = 0, a = 0, s = 0, d = 0, f = 0;//识别按键
	while (1) {
		if ((currentPlant && Check_Dinosaur(Dinosaur_X, Dinosaur_Y, plants) == 1)//植物碰撞
			|| (!currentPlant && Check_Dinosaur_meteorites(Dinosaur_X, Dinosaur_Y, meteorites) == 1)) {//陨石碰撞
			//碰撞检测，进入分支说明发生碰撞
			Show_Collision(Dinosaur_X, Dinosaur_Y, score, pause, ash, Bg_X, Bg_Y, Ground_X);//碰撞动画
			Show_Game_Sketchpad(Bg_X, Bg_Y, BackGround_Img, Dinosaur_X, Dinosaur_Y, Dinosaur_Img,
				currentPlant, plants, Plant_Img, Ground_X, Ground_Img, score, ash,
				New_Plant, imgNew_Plant, meteorites, Meteorite_Img, Boom_Img, 2);//死亡状态
			return;//游戏结束，退出程序
		}

		//各个东西的更新计时器
		if (Timer(18 - speed, 0) == 1)
			Move_Dinosaur(Dinosaur_X, Dinosaur_Y, flag, Dinosaur_a);//小恐龙的位置更新函数，可能要改变flag的值
		if (Timer(8 - speed, 1) == 1) {
			Move_Plant(plants);
			Move_Ground(Ground_X);
			Move_Meteorites(meteorites, slope);
		}
		if (Timer(30 - speed, 2) == 1)
			Move_BackGround(Bg_X, Bg_Y);
		if (Timer(20 - speed, 3) == 1)
			Move_Ash(ash, currentPlant);
		if (Timer(50 - speed, 4) == 1)
			Change_Dinosaur(Dinosaur_X, Dinosaur_Y, Dinosaur_Img, Dinosaur_flag);
		Change_Speed(score, speed);

		score = clock() - Game_Start_Time;

		cleardevice();
		Show_background(Bg_X, Bg_Y, BackGround_Img);//输出背景
		Show_Dinosaur(Dinosaur_X, Dinosaur_Y, Dinosaur_Img);//打印小恐龙
		drawRandomPlants(currentPlant, plants, Plant_Img);//打印每一个障碍物
		Show_Ground(Ground_X, Ground_Y, Ground_Img);
		Show_Score(score);
		Show_Ash(ash);
		Draw_Plant(New_Plant_X, New_Plant_Y, New_Plant, imgNew_Plant);
		drawMeteorites(currentPlant, meteorites, Meteorite_Img, Boom_Img);
		Draw_Button(pause);
		Show_Name(currentPlant);
		Show_Score(score);
		FlushBatchDraw();
		while (peekmessage(&m, EX_MOUSE | EX_KEY));//鼠标检测//检测按键
		if (m.message == 256)//按键按下
			switch (m.vkcode) {
			case VK_UP:
			case 'W':		w = true;		break;
			case VK_DOWN:
			case 'S':		s = true;		break;
			case VK_LEFT:
			case 'A':		a = true;		break;
			case VK_RIGHT:
			case 'D':		d = true;		break;
			}
		if (m.message == 257)//按键抬起
			switch (m.vkcode) {
			case VK_UP:
			case ' ':
			case 'W':		w = false;		break;
			case VK_DOWN:
			case 'S':		s = false;		break;
			case VK_LEFT:
			case 'A':		a = false;		break;
			case VK_RIGHT:
			case 'D':		d = false;		break;
			}

		if (w)
			Up_Dinosaur(Dinosaur_X, Dinosaur_Y, flag, Dinosaur_a);//需要传递位置和障碍物位置，跳跃首先要判断在不在地面
		if (s)
			Down_Dinosaur(Dinosaur_X, Dinosaur_Y, flag);//需要传递位置和障碍物位置，趴下首先也要判断在不在地面
		if (a)
			Left_Dinosaur(Dinosaur_X);
		if (d)
			Right_Dinosaur(Dinosaur_X);

		if (IsChange(New_Plant, currentPlant, Dinosaur_X, Dinosaur_Y)) {
			Change_BackGround(currentPlant, Dinosaur_X, Dinosaur_Y, BackGround_Img);
			Change_Plant(Plant_Img, currentPlant);
			initializePlants(plants);
			initializeMeteorite(meteorites, slope);//避免一转换场景就去世
			InitAshFirst(ash, currentPlant);//重新转换粒子效果
			FlushInput(m, w, a, s, d);
		}
		//printf("%d: %d %d %d %d\n", clock(), m.x, m.y, m.message, m.vkcode);
		//检测状态用的
		if (isClickButton(pause, m)) {//按到暂停
			FlushInput(m, w, a, s, d);
			switch (Show_Pause(Bg_X, Bg_Y, BackGround_Img, Dinosaur_X, Dinosaur_Y, Dinosaur_Img,
				currentPlant, plants, Plant_Img, Ground_X, Ground_Img, score, ash,
				New_Plant, imgNew_Plant, meteorites, Meteorite_Img, Boom_Img)) {
			case 1://继续游戏
				break;
			case 2://游戏操作
				Show_Game_Sketchpad(Bg_X, Bg_Y, BackGround_Img, Dinosaur_X, Dinosaur_Y, Dinosaur_Img,
					currentPlant, plants, Plant_Img, Ground_X, Ground_Img, score, ash,
					New_Plant, imgNew_Plant, meteorites, Meteorite_Img, Boom_Img, 1);//暂停状态
				break;
			case 3://返回主页
				return;
			}
		}

		if (currentPlant == 2) {//游戏结束
			Show_Game_Sketchpad(Bg_X, Bg_Y, BackGround_Img, Dinosaur_X, Dinosaur_Y, Dinosaur_Img,
				currentPlant, plants, Plant_Img, Ground_X, Ground_Img, score, ash,
				New_Plant, imgNew_Plant, meteorites, Meteorite_Img, Boom_Img, 3);
			return;//游戏结束
		}

		if (allOffScreen_Plants(plants))
		{
			initializePlants(plants);
			New_Plant++;//计数器，判断生成了几组植物
		}
		if (allOffScreen_Meteorite(meteorites)) {
			initializeMeteorite(meteorites, slope);
		}
	}
	EndBatchDraw();
}