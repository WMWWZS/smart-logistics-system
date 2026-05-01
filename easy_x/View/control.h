#ifndef _CONTROL_H_ 
#define _CONTROL_H_ 

#define BUTTON   1
#define EDIT     2
#define EDIT_PWD 3 
#define LABEL    4
//定义控件结构体 
typedef struct control_t 
{
	int x;
	int y;
	int width;
	int hight; 
	char text[100];
	COLORREF bgColor1;  //默认颜色 
	COLORREF bgColor2;   //被选中的颜色 
	COLORREF textCloor;  //文本颜色 
	int type; //控件类型
	int state;  //控件状态 
}CONTROL_T; 

//控件显示函数
void control_show(CONTROL_T ctr1) ;


#endif
