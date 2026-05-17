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
#include "App/adminWin.h" 
//展开后，相关的h文件不要少分号或者参数， 一般头文件应该在cpp中 
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

LNode* userList = NULL;  //用户链表：用于保存file中用户信息 
FILE* user_fp = NULL; 
FILE* order_fp = NULL; 

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
	
	//它的格式是返回值 (*fun[nums])(参数) 
	int (*fun[10])() = {startWin,loginWin,mainWin,adminWin,addUserWin,selectUserWin,carWin,orderWin,storeWin,};   //startWin进入 由loginWin验证 mainWin展开 ： 
	int win_id = 0; 																						//顺序是： 1.odrderWin 2.storeWin 3.RunWin 4.*统计分析   
	while(1)																					//5.*客服服务（考虑接入大模型，当前无实质作用(不知到AI能不能读取到链表或者文件信息)） 6.*密码修改  7.*密码修改 
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


