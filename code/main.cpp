#include"function_and_state.h"
//记得做音乐
int main() {
	initface();
	while (1) {
		switch (MainFace()) {  //主菜单页面，返回选择的项
		case 1:  //进入游戏
			Game();
			break;
		case 2://查看背景介绍
			Show_Main_Sketchpad();
			break;
		case 3:  //退出游戏
			closegraph();
			return 0;
			break;
		}
	}
}