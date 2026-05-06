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

typedef struct window_t 
{
	int x;
	int y;
	int width;
	int hight;
	COLORREF bgColor;
	int count;
	CONTROL_T controls[10] ;
	int current;
} WINDOW_T; 

//控件显示函数
void control_show(CONTROL_T ctr1) ;

//窗口显示 
void window_show(WINDOW_T win) ;

//窗口运行 
WINDOW_T window_run(WINDOW_T) ;















#endif
