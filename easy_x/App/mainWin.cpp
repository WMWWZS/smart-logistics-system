#include "../View/control.h"
int mainWin()   //登录成功后页面
{
    WINDOW_T win={290,155,220,305,CYAN,7,{
        {300,160,200,40,"1.系统管理",LIGHTCYAN,CYAN,WHITE,BUTTON,1,0},   //0     5.4标记 
        {300,200,200,40,"2.订单管理",LIGHTCYAN,CYAN,WHITE,BUTTON,0,0},  //1
        {300,240,200,40,"3.仓储管理",LIGHTCYAN,CYAN,WHITE,BUTTON,0,0}, //2
        {300,280,200,40,"4.运输管理",LIGHTCYAN,CYAN,WHITE,BUTTON,0,0}, //3
        {300,320,200,40,"5.统计分析",LIGHTCYAN,CYAN,WHITE,BUTTON,0,0},  //4
        {300,360,200,40,"6.密码修改",LIGHTCYAN,CYAN,WHITE,BUTTON,0,0},  //5
        {300,400,200,40,"7.返回上级",LIGHTCYAN,CYAN,WHITE,BUTTON,0,0},   //6
    }};

	Background_display();

	window_show(win);
	win = window_run(win);
	if(win.current == 0)
	{
	    return 3;   //adminWin界面
	}
	else if(win.current==1)
	{
	    return 6;       //订单管理界面
	}
	else if(win.current==2)
	{
	    return 10;   //仓储管理界面
	}
	else if(win.current==3)
	{
	    return 24;        //运输管理界面carWin
	}
	else if(win.current==4)
	{
	    return 15;  //统计分析界面
	}
	else if(win.current==5)
	{
	    return 14;    //密码修改界面
	}
	else if(win.current==6)
	{
	    return 1;       //返回上级
	}
}

