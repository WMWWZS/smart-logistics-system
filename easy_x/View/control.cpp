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
{   //框的绘制 
	int i = 0;
	char str[20] = {0}; 
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
	
	//显示文本 
	
	if(ctr1.type == LABEL || ctr1.type == EDIT) 
	{
		outtextxy(ctr1.x, ctr1.y, ctr1.text); //此处可设置xy的偏移（效果待定） 
		
	}
	else if(ctr1.type == BUTTON) 
	{
		settextstyle(16, 10, _T("黑体"));
		int center = ctr1.x + (ctr1.width - strlen(ctr1.text) * 2 * 10) ;
		outtextxy(center, ctr1.y + 15, ctr1.text) ;
	}
	else if(ctr1.type == EDIT_PWD)	
	{
		for(i = 0; i < strlen(str); i++) 
		{
			str[i] = '*';
			
		}
	}
	outtextxy(ctr1.x + 5, ctr1.y + 15, str)	;
}

