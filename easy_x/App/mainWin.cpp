#include "../View/control.h" 
int mainWin()   //登录成功后页面 
{
    WINDOW_T win={290,155,220,330,WHITE,8,{
        {300,160,200,40,"1.系统管理",LIGHTCYAN,CYAN,WHITE,BUTTON,1,0},   //0
        {300,200,200,40,"2.订单管理",LIGHTCYAN,CYAN,WHITE,BUTTON,0,0},  //1
        {300,240,200,40,"3.仓储管理",LIGHTCYAN,CYAN,WHITE,BUTTON,0,0}, //2
        {300,280,200,40,"4.运输管理",LIGHTCYAN,CYAN,WHITE,BUTTON,0,0}, //3
        {300,320,200,40,"5.统计分析",LIGHTCYAN,CYAN,WHITE,BUTTON,0,0},  ///4
        {300,360,200,40,"6.客户服务",LIGHTCYAN,CYAN,WHITE,BUTTON,0,0}, //5
        {300,400,200,40,"7.密码修改",LIGHTCYAN,CYAN,WHITE,BUTTON,0,0},  //6
        {300,440,200,40,"8.返回上级",LIGHTCYAN,CYAN,WHITE,BUTTON,0,0},   //7
    }};
    
	Background_display();
	
	window_show(win); 
	win = window_run(win); 
	if(win.current == 0)     //想象到了switch，AI通过分析汇编说小型分支if和switch性能几乎无差别，但是大量（上百个）分支， 
	{									//但是大量（上百个）分支，switch会更快，后续有待进行重构,这里有个思路，后面试试实现一下 5.16
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
	    return 8;        //运输管理界面 
	}
	else if(win.current==4)
	{
	    return 16;  //统计分析界面 
	}
	else if(win.current==5)
	{
	    return 15;      //客服服务界面 
	}
	else if(win.current==6)
	{
	    return 14;    //密码修改界面
	}
	else if(win.current==7)
	{
	    return 1;       //返回上级 
	}   
}
