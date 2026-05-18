#include <graphics.h>
#include <conio.h>
#include "control.h" 
#include "string.h"  
#include <stdio.h>
//控件显示函数 
void control_show(CONTROL_T ctr1) 
{   
	//框的绘制 
	int i = 0;
	char str[20] = {0}; 
	if(ctr1.type == BUTTON || ctr1.type == EDIT || ctr1.type == EDIT_PWD || ctr1.type == SELECT || ctr1.type == SELECTED) 
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
		outtextxy(ctr1.x, ctr1.y + 15, ctr1.text); //此处可设置xy的偏移（效果待定） 
		 
	}
	else if(ctr1.type == BUTTON) 
	{
		settextstyle(16, 10, _T("黑体"));
		int center = ctr1.x + (ctr1.width - strlen(ctr1.text) * 10) / 2;
		outtextxy(center, ctr1.y + 15, ctr1.text) ;
	}
	else if(ctr1.type == EDIT_PWD)
	{
	    strcpy(str, ctr1.text);
	    int len = strlen(str);
	    for(i = 0; i < len; i++)
	    {
	        str[i] = '*';
	    }
	    str[len] = '\0'; 
	    outtextxy(ctr1.x, ctr1.y + 15, str);
	}
	else if(ctr1.type == SELECT || ctr1.type == SELECTED)
	{
	    char buf[20]={0};
	    // 截取第一个逗号前的文本（默认选中项）
	    sscanf(ctr1.text,"%[^,]",buf);     
	    outtextxy(ctr1.x+5, ctr1.y+15, buf);  // 显示选中值
	    outtextxy(ctr1.x+ctr1.width-15, ctr1.y+15, "V");	// 显示下拉箭头（替换v更直观）
	}
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
		if(ch1 == '\r')    //确认enter 
		{
			if(win.controls[i].type == BUTTON || win.controls[i].type==SELECT || win.controls[i].type==SELECTED) 
			{
				win.current = i;  
				return win; 
			}
		}
		else if (win.controls[i].type == SELECT || win.controls[i].type == SELECTED)
		{
		    static WINDOW_T selectWin = {
		        win.controls[i].x,
		        win.controls[i].y + win.controls[i].hight, 
		        win.controls[i].width,
		        win.controls[i].hight,                     
		        WHITE,
		        0,
		        {0}
		    };
		}
		if (win.controls[i].type == SELECT)
		{
			static WINDOW_T selectWin = {
		        win.controls[i].x,
		        win.controls[i].y + win.controls[i].hight,  
		        win.controls[i].width,
		        win.controls[i].hight,                    
		        WHITE,
		        0,
		        {0}
		    };
		    char *buf[10] ={0};
		    int k = 0;
		    char text_copy[100] ={0};
		    strcpy(text_copy, win.controls[i].text);
		    char *token = strtok(text_copy, ",");
		    while (token != NULL && k < 10)
		    {
		        buf[k++] = token;
		        token = strtok(NULL,",");
		    }
		    selectWin.count = k;  
		
		    // j从0开始，全部选项都加载
		    for (int j = 0; j < k; j++)
		    {
		        CONTROL_T tmpCtrl = {
		            win.controls[i].x,
		            win.controls[i].y + 50 * j,
		            win.controls[i].width,
		            win.controls[i].hight,
		            "",
		            CYAN, LIGHTCYAN, WHITE,
		            BUTTON,
		            0
		        };
		        strcpy(tmpCtrl.text, buf[j]);
		        selectWin.controls[j] = tmpCtrl;
		
		        // 默认选中第一个
		        if (j == 0)
		        {
		            selectWin.controls[j].state = 1;
		        }
		    }
		    win.controls[i].type = SELECTED;
		
		    window_show(selectWin);
		    selectWin = window_run(selectWin);
		
		    char selText[20]={0};
		    strcpy(selText, selectWin.controls[selectWin.current].text);
		    Background_display();
		    window_show(win);
		
		    i = 6;
		    win.controls[5].state = 0;
		    win.controls[6].state = 1;
		
		    Background_display();
		    window_show(win);
		}
		else if(ch1 >= '0' && ch1 <= '9' || ch1 >= 'a' && ch1 <= 'z' || ch1 >= 'A' && ch1 <= 'Z')
		{
			printf("%d\n",ch1) ;
			if(win.controls[i].type == EDIT || win.controls[i].type == EDIT_PWD) 
			{
				int len = strlen(win.controls[i].text);
				printf("%d\n",i) ;
				if(len < win.controls[i].maxStr)
				{
					win.controls[i].text[len] = ch1;
					win.controls[i].text[len + 1] = '\0';
					control_show(win.controls[i]) ; 
				}				
			}
		}
		else if(ch1 == '\b') 
		{
			if(win.controls[i].type == EDIT || win.controls[i].type == EDIT_PWD) 
			{
				win.controls[i].text[strlen(win.controls[i].text)-1] = '\0';
				control_show(win.controls[i]) ; 
			}			
		}
		else if(ch1 == -32) 
		{
			ch2 =  getch() ;
			if(ch2 == KEY_DOWN) 
			{
				//将自己的颜色改成未选中 
				win.controls[i].state = 0;
				printf("此时的下标是：%d\n",i);
				control_show(win.controls[i]);
				//移动到下一个可停留控件 （不是LABLE） 
				do
				{
					i++;
					if(i == win.count + 1) 
					{
						i = 0; 
					}
				}while(win.controls[i].type == LABEL) ;
				printf("%d\n",ch2) ;
				printf("正在绘制控件: 类型=%d, 文本=%s, 坐标=(%d,%d)\n", 
	           	win.controls[i].type, win.controls[i].text, win.controls[i].x,win.controls[i].y);				
				//将自己的颜色改成未选中 
				win.controls[i].state = 1;
//				control_show(win.controls[i]);  //！！！！！！！！！！ 
				window_show(win);				
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
						i = win.count - 1;   //注意不能越界
					}
					
				}while(win.controls[i].type == LABEL) ;
				//将自己的颜色改成未选中 
				printf("正在绘制控件: 类型=%d, 文本=%s, 坐标=(%d,%d)\n", 
	           	win.controls[i].type, win.controls[i].text, win.controls[i].x,win.controls[i].y);
				win.controls[i].state = 1;
//				control_show(win.controls[i]);	
				window_show(win);				
			}
			else if(ch2 == KEY_LEFT) 
			{
				win.current = -1;
				return win;
			}
			else if(ch2 == KEY_RIGHT) 
			{
				win.current = -2;
				return win;				
			}
		}
	}
	
}

void Background_display()
{
	IMAGE img;
	loadimage(&img, "./imge/LMS.jpg",800,600);
	putimage(0, 0, &img);
	setbkmode(TRANSPARENT);
	settextcolor(CYAN);
	outtextxy(200,530,"操作说明：上下键移动切换菜单，按下回车键选择菜单");
}

void table_show(TABLE_T table,int pageNum,int pageNow)
{
    int i,j;
    int w=table.width/table.col;
    int h=table.height/table.row;

    setfillcolor(WHITE);
    setlinecolor(CYAN);
    settextcolor(CYAN);

    // 画格子
    for(i=0;i<table.row;i++)
	{
        for(j=0;j<table.col;j++)
		{
            fillrectangle(table.x+w*j,table.y+h*i,table.x+w*j+w,table.y+h*i+h);
            rectangle(table.x+w*j,table.y+h*i,table.x+w*j+w,table.y+h*i+h);
        }
    }

	//2显示首行的内容
	for(j=0;j<table.col;j++)
	{
	    outtextxy(table.x+w*j+5,table.y+15,table.text[j]);
	}
	
	//3显示表格内容
	for(i=1;i<table.row;i++)
	{
	    for(j=0;j<table.col;j++)
		{
	        outtextxy(table.x+w*j+5,table.y+h*i+15,table.data[i-1][j]);
	    }
	}
	
	//4显示底下那条页数
	char str[50]={0};
	sprintf(str,"<-上页    共%d页/当前第%d页    ->下页",pageNum,pageNow);
	outtextxy(table.x+50,table.y+table.height+5,str);
}

















