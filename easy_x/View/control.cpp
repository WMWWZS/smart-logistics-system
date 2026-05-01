#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include "control.h" 

/*
#define BUTTON   1 按钮 
#define EDIT     2 编辑框 
#define EDIT_PWD 3   
#define LABEL    4 标签 
*/

//空间显示函数 
void control_show(CONTROL_T ctr1) 
{//框的绘制 
	if(ctr1.type == BUTTON || ctr1.type == EDIT || ctr1.type == EDIT_PWD) 
	{
		if(ctr1.state == 1)  //说明被选中 
		{
			setfillcolor(ctr1.bgColor2) ;
		}
		else
		{
			setfillcolor(ctr1.bgColor1) ;
		} 
		fillrectangle(ctr1.x, ctr1.y, ctr1.x + ctr1.width, ctr1.y + ctr1.hight); 
	} 
	if(ctr1.type == LABEL || ctr1.type == EDIT) 
	{
		outtextxy(ctr1.x, ctr1.y, ctr1.text) //此处可设置xy的偏移（效果待定） 
		
	}
}

