#include <iostream>
#include <graphics.h>
#include "View/control.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	//1.创建绘图窗口 
	initgraph(800, 600) ;	
	
	//2.显示图片背景 
	IMAGE img;   
	loadimage(&img, "imge/LMS.jpg", 800, 600) ;  
	putimage(0, 0, &img) ;  
	
	//3.绘制按钮
//	CONTROL_T lab1 = {200, 200, 100, 50, "用户名：",WHITE, WHITE, CYAN ,LABEL, 0} ;
//	CONTROL_T edit1 = {260, 180, 100, 50, " ",LIGHTCYAN, CYAN, WHITE ,EDIT, 1} ;
//	
//	CONTROL_T lab2 = {200, 300, 100, 50, "密码：",WHITE, WHITE, CYAN ,LABEL, 0} ;
//	CONTROL_T edit2 = {260, 280, 100, 50, " ",LIGHTCYAN, CYAN, WHITE ,EDIT, 1} ;
//	
//	CONTROL_T bun1 = {300, 350, 130, 50, "登录",CYAN, LIGHTCYAN, WHITE, BUTTON, 0} ;
	
//	control_show(lab1) ;
//	control_show(edit1) ;
//	control_show(lab2) ;
//	control_show(edit2) ;
//	control_show(bun1) ;

//typedef struct window_t  参考: 
//{
//	int x;
//	int y;
//	int width;
//	int hight;
//	COLORREF bgColor;
//	int count;
//	CONTROL_T controls[10] ;
//	int current;
//} WINDOW_T; 

	WINDOW_T startWin = {290, 240 , 220 ,180, WHITE, 3,{
	{300, 250, 200, 50, "用户名：",CYAN, LIGHTCYAN, WHITE,BUTTON, 1},
	{300, 305, 200, 50, "密码：",CYAN, LIGHTCYAN, WHITE ,BUTTON, 0},
	{300, 365, 200, 50, "登录",CYAN, LIGHTCYAN, WHITE, BUTTON, 0}}} ; 
	
	window_show(startWin) ;
	while(1)
	{
		
	}
	return 0;
	
}


