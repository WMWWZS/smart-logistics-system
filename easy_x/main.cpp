#include <iostream>
#include <graphics.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	initgraph(1024, 680) ;	//1.创建绘图窗口 
	IMAGE img;   //2.创建存放图片指针的变量 
	loadimage(&img, "imge/LMS.jpg", 1024, 680) ;  //3.找到图片文件指针，设定图片的显示规格 
	putimage(0, 0, &img) ;  //4.显示图片
	while(1)
	{
		
	}
	return 0;
}
