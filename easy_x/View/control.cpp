#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include "control.h" 
#include "string.h" 
//控件显示函数 
void control_show(CONTROL_T ctr1) 
{   //框的绘制 
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
	
	if(ctr1.type == LABEL || ctr1.type == EDIT || ctr1.type == SELECTED) 
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
    sscanf(ctr1.text,"%[^,]",buf);     //截取text字符串从开头到逗号
    outtextxy(ctr1.x+5,ctr1.y+15,buf);
    outtextxy(ctr1.x+ctr1.width-15,ctr1.y+15,"v");	
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
	win.controls[2].text[0] = '\0';
	win.controls[3].text[0] = '\0';   //初始化，防止strlen崩溃 
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
			if(win.controls[i].type == BUTTON) 
			{
				win.current = i;  
				return win; 
			}
		}
	else if(win.controls[i].type==SELECT || win.controls[i].type==SELECTED){
	
	    //1.定义一个窗口,static 只会被初始化一次
	    static WINDOW_T selectWin={win.controls[i].x,win.controls[i].y+win.controls[i].hight,win.controls[i].width,
	    win.controls[i].hight,WHITE};	
	    if(win.controls[i].type==SELECT){
	        //2. 分割字符串
	        //分割字符串    //"请选择数据,管理员,仓储员,调度员,客服"
	        char *buf[10]={0};
	        int k=0;
	        char *token = strtok(win.controls[i].text, ",");
	        while (token != NULL) {
	            printf("子串：%s\n", token); // 输出分割后的子串
	            buf[k++]=token;
	            token = strtok(NULL, ","); // 后续调用：传入 NULL
	        }
	
	        //3. 构建下拉框组合
	        for(int j=1;j<=k-1;j++){
	            CONTROL_T tmpCtrl={win.controls[i].x,win.controls[i].y+50*j,win.controls[i].width,
	            win.controls[i].hight,"",CYAN,LIGHTCYAN,WHITE,BUTTON,0};
	            strcpy(tmpCtrl.text,buf[j]);
	
	            selectWin.controls[j-1]=tmpCtrl;
	            //第一个选项为选中状态，为1
	            if(j==1){
	                selectWin.controls[j-1].state=1;
	            }
	        }
	    }
	
	    //改变下拉框的类型
	    win.controls[i].type=SELECTED;
	
	    //4.显示下拉框
	    window_show(selectWin);
	    //5.下拉框驱动
	    selectWin=window_run(selectWin);
	
	    //6.选项按下回车后选中，要吧选项的值拷贝原来的下拉框文本
	    strcpy(win.controls[i].text,selectWin.controls[selectWin.current].text);
	    //背景重刷
		IMAGE img;
		loadimage(&img, "./imge/LMS.jpg",800,600);
		putimage(0, 0, &img);  
		setbkmode(TRANSPARENT);
		settextcolor(CYAN);
		outtextxy(200,530,"操作说明：上下键移动切换菜单，按下回车键选择菜单");
		window_show(selectWin);
	    //界面重刷
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
						i = win.count - 1;   //注意不能越界
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





















