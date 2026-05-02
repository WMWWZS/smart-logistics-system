#include <iostream>
#include <graphics.h>
#include "View/control.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	//1.创建绘图窗口 
	initgraph(1024, 680) ;	
	
	//2.显示图片背景 
	IMAGE img;   
	loadimage(&img, "imge/LMS.jpg", 1024, 680) ;  
	putimage(0, 0, &img) ;  
	
	//3.绘制按钮
	CONTROL_T lab1 = {200, 200, 100, 50, WHITE, WHITE, CYAN} ;
	
	while(1)
	{
		
	}
	return 0;
}
