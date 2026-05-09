#include <iostream>
#include <graphics.h>
#include "public/list.h"
#include "public/file.h"
#include "App/data.h" 
#include "App/loginWin.h"
#include "View/control.h" 
#include "App/startWin.h" 
#include "App/mainWin.h"
#include "App/startWin.h"
//展开后，相关的h文件不要少分号或者参数， 
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

LNode* userList = NULL;
FILE* user_fp = NULL; 

int main(int argc, char** argv) {
	//1.打开文件 
	user_fp = file_open("data/user.txt");
	//2.初始化用户链表 
	userList = user_data_init(user_fp); 
	
	//1.创建绘图窗口 
	initgraph(800, 600) ;	
	
	//2.显示图片背景 
	IMAGE img;   
	loadimage(&img, "imge/LMS.jpg", 800, 600) ;  
	putimage(0, 0, &img) ;  
	
	int (*fun[10])() = {startWin, loginWin, mainWin} ;
	int win_id = 0; 
	while(1)
	{
		win_id = fun[win_id]() ;
	}
	
	
	
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

//	WINDOW_T startWin = {290, 240 , 220 ,180, WHITE, 3,{
//	{300, 250, 200, 50, "登录",CYAN, LIGHTCYAN, WHITE,//	WINDOW_T loginWin = {240,240,290,180, WHITE, 6,{
//	{245, 250, 80, 50, "用户名：",CYAN, LIGHTCYAN, WHITE,LABEL, 0, 0 },  //
//	{245, 305, 80, 50, "密 码：",CYAN, LIGHTCYAN, WHITE ,LABEL, 0, 0 },
//	{320, 250, 200, 50, "",CYAN, LIGHTCYAN, WHITE ,EDIT, 1, 8} ,     //用户名 
//	{320, 305, 200, 50, "",CYAN, LIGHTCYAN, WHITE ,EDIT_PWD, 0, 12},  //密码 
//	{245, 360, 130,50, "登 录",CYAN, LIGHTCYAN, WHITE ,BUTTON, 0, 0},
//	{390,360,130,50, "返 回",CYAN, LIGHTCYAN, WHITE, BUTTON, 0, 0}}} ;   
//	
//	window_show(loginWin) ;
//	window_run(loginWin);BUTTON, 1},
//	{300, 305, 200, 50, "忘记密码",CYAN, LIGHTCYAN, WHITE ,BUTTON, 0},
//	{300, 365, 200, 50, "退出",CYAN, LIGHTCYAN, WHITE, BUTTON, 0}}} ; 
	
//	window_show(startWin) ;
//	window_run(startWin);
	

	
}


