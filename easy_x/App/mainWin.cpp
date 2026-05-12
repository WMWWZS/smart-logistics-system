#include "../View/control.h" 
int mainWin()
{
    WINDOW_T win={290,155,220,330,WHITE,8,{
        {300,160,200,40,"1.系统管理",LIGHTCYAN,CYAN,WHITE,BUTTON,0,0},
        {300,200,200,40,"2.订单管理",LIGHTCYAN,CYAN,WHITE,BUTTON,0,0},
        {300,240,200,40,"3.仓储管理",LIGHTCYAN,CYAN,WHITE,BUTTON,0,0},
        {300,280,200,40,"4.运输管理",LIGHTCYAN,CYAN,WHITE,BUTTON,0,0},
        {300,320,200,40,"5.统计分析",LIGHTCYAN,CYAN,WHITE,BUTTON,0,0},
        {300,360,200,40,"6.客户服务",LIGHTCYAN,CYAN,WHITE,BUTTON,0,0},
        {300,400,200,40,"7.密码修改",LIGHTCYAN,CYAN,WHITE,BUTTON,0,0},
        {300,440,200,40,"8.返回上级",LIGHTCYAN,CYAN,WHITE,BUTTON,0,0},
    }};
	IMAGE img;
	loadimage(&img, "./imge/LMS.jpg",800,600);
	putimage(0, 0, &img);  
	setbkmode(TRANSPARENT);
	settextcolor(CYAN);
	outtextxy(200,530,"操作说明：上下键移动切换菜单，按下回车键选择菜单");
	window_show(win);
	win=window_run(win);
	if(win.current==0)
	{
	    return 3;
	}
	else if(win.current==7)
	{
	    return 1;
	}
}
