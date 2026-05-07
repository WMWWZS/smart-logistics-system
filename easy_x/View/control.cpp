#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include "control.h" 



//控件显示函数 
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
		int center = ctr1.x + (ctr1.width - strlen(ctr1.text) *10) / 2;
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

void window_show(WINDOW_T win)
{
	int i = 0;
	//显示窗口背景颜色 
	setfillcolor (win.bgColor);
	fillrectangle (win.x, win.y, win.width + win.x, win.y + win.hight ) ;
	
	for(i = 0; i < win.count ; i++) 
	{
		control_show(win.controls[i]);
	}
}

WINDOW_T window_run(WINDOW_T win) 
{
	char ch1,ch2; 
	int i = 0;
	while(win.controls[i].type == LABEL) 
	{
		i++;
		if(i == win.count) 
		{
			i = 0; 
		}
	}
	while(1) 
	{
		ch1 = getch() ; 
		if(ch1 == '\r') 
		{
			
		}
		else if(ch1 >= '0' && ch1 <= '9' || ch1 >= 'a' && ch1 <= 'z' || ch1 >= 'A' && ch1 <= 'Z')
		{
			
		}
		else if(ch1 == '\b') 
		{
			
		}
		else if(ch1 == -32) 
		{
			ch2 =  getch() ;
			printf("%d\n",ch2) ;
			if(ch2 == KEY_DOWN) 
			{
				//将自己的颜色改成未选中 
				win.controls[i].state = 0;
				control_show(win.controls[i]);
				//移动到下一个可停留控件 （不是LABLE） 
				do
				{
					i++;
					if(i == win.count) 
					{
						i = 0; 
					}
					
				}while(win.controls[i].type == LABEL) ;
				//将自己的颜色改成未选中 
				win.controls[i].state = 1;
				control_show(win.controls[i]);				
			}
			else if(ch2 == KEY_UP) 
			{
				win.controls[i].state = 0;
				control_show(win.controls[i]);
				//移动到下一个可停留控件 （不是LABLE） 
				do
				{
					i--;
					if(i == -1)      
					{
						i = win.count;   //注意不能越界3 
					}
					
				}while(win.controls[i].type == LABEL) ;
				//将自己的颜色改成未选中 
				win.controls[i].state = 1;
				control_show(win.controls[i]);					
			}
			else if(ch2 == KEY_LEFT) 
			{
				
			}
			else if(ch2 == KEY_RIGHT) 
			{
				
			}
		}
	}
	
}





















