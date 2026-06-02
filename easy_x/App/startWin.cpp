#include <conio.h> 
#include <graphics.h> 
#include "../View/control.h" 
#include "data.h"

int startWin() 
{
	WINDOW_T startWin = {290, 240 , 220 ,180, WHITE, 3,{
	{300, 250, 200, 50, "登 录",LIGHTCYAN,CYAN, WHITE,BUTTON, 1,0},
	{300, 305, 200, 50, "忘记密码",LIGHTCYAN,CYAN,WHITE,BUTTON, 0,0},
	{300, 365, 200, 50, "退出",LIGHTCYAN,CYAN,WHITE,BUTTON, 0,0}}} ; 
	
	Background_display();
	
	window_show(startWin) ;
	startWin = window_run(startWin);
	if(startWin.current == 0)  //这里我将 == 写成 =  标记bug 
	{
		return 1; 
	} 
	else if(startWin.current == 1 )
	{
		return 22; 
	}
	else if(startWin.current == 2)
	{
		exit(1); 
	}	
}

int resetPwdWin()
{
    WINDOW_T win = {
        200, 150, 450, 280, CYAN, 6,
        {
            // 用户名
            {220, 180, 120, 30, "用户名：",CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
            {350, 180, 180, 30, "", CYAN, LIGHTCYAN, WHITE, EDIT, 0, 9},
            
            // 新密码
            {220, 230, 120, 30, "新密码：",CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
            {350, 230, 180, 30, "", CYAN, LIGHTCYAN, WHITE, EDIT, 0, 9},
            
            // 按钮
            {250, 300, 120, 40, "确认重置",LIGHTCYAN,CYAN, WHITE, BUTTON, 0, 4},
            {400, 300, 120, 40, "返回",LIGHTCYAN,CYAN, WHITE, BUTTON, 0, 5}
        }
    };

    Background_display();
    window_show(win);
    win = window_run(win);

    //返回登录界面
    if(win.current == 5)
    {
        return 0;  
    }

    //确认重置
    if(win.current == 4)
    {
        char username[20] = {0};
        char newPwd[20] = {0};
        
        strcpy(username, win.controls[1].text);
        strcpy(newPwd, win.controls[3].text);

        // 非空判断
        if(strlen(username) == 0 || strlen(newPwd) == 0)
        {
            CONTROL_T tip = {245,300,220,70,"请输入完整信息",CYAN,LIGHTCYAN,WHITE,BUTTON,0};
            control_show(tip);
            Sleep(1500);
            return resetPwdWin();
        }

        if(user_fp == NULL)
        {
            CONTROL_T tip = {245,300,220,70,"用户文件不存在",CYAN,LIGHTCYAN,WHITE,BUTTON,0};
            control_show(tip);
            Sleep(1500);
            return resetPwdWin();
        }
		rewind(user_fp);
		clearerr(user_fp);
		
		USER_T user; 
		int find = 0;
		
		while(fread(&user, sizeof(USER_T), 1, user_fp) == 1)
		{
		    if(strcmp(user.name, username) == 0)
		    {
		        strcpy(user.passwd, newPwd);
		        fseek(user_fp, -sizeof(USER_T), SEEK_CUR);   //-sizeof(USER_T)负数，意味回退，再覆盖写入 
		        fwrite(&user, sizeof(USER_T), 1, user_fp); 
		        fflush(user_fp);
		        find = 1;
		        break;
		    }
		}
		
        if(find == 1)
        {
            CONTROL_T tip = {245,300,220,70,"密码重置成功",LIGHTCYAN,CYAN,WHITE,BUTTON,0};
            control_show(tip);
            Sleep(1500);
            return 0;
        }
        else
        {
            CONTROL_T tip = {245,300,220,70,"用户名不存在",LIGHTCYAN,CYAN,WHITE,BUTTON,0};
            control_show(tip);
            Sleep(1500);
            return 21;
        }
    }

}









      



















