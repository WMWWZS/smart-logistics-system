#include "data.h"
#include "../public/list.h"
#include "../View/control.h"
#include <string.h>
#include <windows.h>
int goodIn()
{
	
}
	 
int goodOut() 
{
	
}

int goodSeach()
{
	
}

int storeWin()  //进入前的条件是你是仓储员或者管理员 
{
    WINDOW_T win={290,155,220,330,WHITE,4,{
        {300,160,200,40,"1.货物入库",LIGHTCYAN,CYAN,WHITE,BUTTON,1,0},    //0
        {300,200,200,40,"2.货物出库",LIGHTCYAN,CYAN,WHITE,BUTTON,0,0},  //1
        {300,240,200,40,"3.库存查询",LIGHTCYAN,CYAN,WHITE,BUTTON,0,0},  //2
        {300,280,200,40,"4.返回上级",LIGHTCYAN,CYAN,WHITE,BUTTON,0,0},  //3
    },0};

	Background_display();
    
    window_show(win);
    win = window_run(win);
    if(win.current==0)   //{goodIn,goodOut,goodSeach}; //存储区块11 12 13 
    {
    	return 12; //货物入库 
	}
	else if(win.current==1)
	{
		return 13; //货物出库 
	} 
    else if(win.current==2)
    {
    	return 14;    //货物查询 
	}
	else if(win.current==3)
	{
		return 2; 
	} 
}
    
