#include <conio.h> 
#include <graphics.h> 
#include "../View/control.h" 




int adminWin()
{
	WINDOW_T win={290,155,220,330,WHITE,8,{
	{300,160,200,40,"1、创建用户",CYAN, LIGHTCYAN, WHITE,LABEL,1,0},//0
	{300,200,200,40,"2、用户查询",CYAN, LIGHTCYAN, WHITE,LABEL,0,0},//1
	{300,240,200,40,"3、密码重置",CYAN, LIGHTCYAN, WHITE,LABEL,0,0}, //2
	{300,280,200,40,"4、角色管理",CYAN, LIGHTCYAN, WHITE,LABEL,0,0}, //3
	{300,320,200,40,"5、仓库配置",CYAN, LIGHTCYAN, WHITE,LABEL,0,0}, //4
	{300,360,200,40,"6、路线配置",CYAN, LIGHTCYAN, WHITE,LABEL,0,0}, //5
	{300,400,200,40,"7、数据备份",CYAN, LIGHTCYAN, WHITE,LABEL,0,0}, //6
	{300,440,200,40,"8、返回上级",CYAN, LIGHTCYAN, WHITE,LABEL,0,0}, //7
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
	    return 2;
	}
}


int addUserWin()
{
    WINDOW_T addUserWin={240,240,290,230,WHITE,8,{
        {245,250,80,50,"用户名：",CYAN, LIGHTCYAN, WHITE,LABEL,0,0},  //0
        {245,305,80,50,"密  码：",CYAN, LIGHTCYAN, WHITE,LABEL,0,0},//1
        {245,360,80,50,"角  色：",CYAN, LIGHTCYAN, WHITE,LABEL,0,0},//2
        {320,250,200,50,"",CYAN,LIGHTCYAN,WHITE,EDIT,1,0},//3
        {320,305,200,50,"",CYAN,LIGHTCYAN,WHITE,EDIT_PWD,0,0},//4
        {320,360,200,50,"请选择：管理员,仓储员,调度员,客服",CYAN,LIGHTCYAN,WHITE,SELECT,0,0},//5
        {245,415,130,50,"创建",CYAN,LIGHTCYAN,WHITE,BUTTON,0,0},//6
        {390,415,130,50,"返回",CYAN,LIGHTCYAN,WHITE,BUTTON,0,0},//7
    }};
	IMAGE img;
	loadimage(&img, "./imge/LMS.jpg",800,600);
	putimage(0, 0, &img);  
	setbkmode(TRANSPARENT);
	settextcolor(CYAN);
	outtextxy(200,530,"操作说明：上下键移动切换菜单，按下回车键选择菜单");
	window_show(addUserWin);
	addUserWin=window_run(addUserWin);
	if(addUserWin.current==0)
	{
	    return 3;
	}
	else if(addUserWin.current==7)
	{
	    return 1;
	}
}


