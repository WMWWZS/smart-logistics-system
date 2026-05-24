#include "loginWin.h"
#include "data.h"
#include "../public/list.h"
#include "../View/control.h"
#include <string.h>
#include <windows.h>
int loginWin()
{
	WINDOW_T loginWin = {240,240,290,180, WHITE, 6,{
	{245, 250, 80, 50, "用户名：",CYAN, LIGHTCYAN, WHITE,LABEL, 0, 0 },  //
	{245, 305, 80, 50, "密 码：",CYAN, LIGHTCYAN, WHITE ,LABEL, 0, 0 },
	{320, 250, 200, 50, "",CYAN, LIGHTCYAN, WHITE ,EDIT, 1, 8} ,     //2用户名  
	{320, 305, 200, 50, "",CYAN, LIGHTCYAN, WHITE ,EDIT_PWD, 0, 12},  //3密码 
	{245, 360, 130,50, "登 录",LIGHTCYAN,CYAN,WHITE,BUTTON, 0, 0},
	{390,360,130,50, "返 回",LIGHTCYAN,CYAN,WHITE,BUTTON, 0, 0}}} ;   
	
	window_show(loginWin) ;
	loginWin = window_run(loginWin);
	if(loginWin.current == 4)	
	{
		//登录验证 
		char pwd[20];
		char name[20];
		strcpy(name, loginWin.controls[2].text) ;
		strcpy(pwd, loginWin.controls[3].text) ;
		int i = 0; 
		int flag = 0;  
		
		//遍历链表 
		for(i = 0; i < getListNodeCount(userList); i++)   
		{
			USER_T* p = (USER_T*)findNode(userList, i) ;
			if(strcmp(name,p->name) == 0 && strcmp(pwd,p->passwd) == 0)
			{
				CONTROL_T ctl= {245, 360, 150, 70, "登录成功",LIGHTCYAN,CYAN, WHITE,BUTTON, 0, 0 };
				control_show(ctl);
				Sleep(2000) ;
				flag = 1; 
				return 2; 
			}
		}
		if(flag == 0) 
		{
			CONTROL_T ctl= {245, 360, 150, 70, "登录失败",LIGHTCYAN,CYAN, WHITE,BUTTON, 0, 0 };
			control_show(ctl);	
			Sleep(2000) ;
			return 1; 		
		}			
	}
	else if(loginWin.current == 5) 
	{
		return 0;
	}
}
