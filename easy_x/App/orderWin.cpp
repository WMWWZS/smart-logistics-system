#include <graphics.h>
#include <conio.h>
#include "../View/control.h" 
#include "string.h"  
#include <stdio.h>
#include "data.h"
#include "../public/file.h" 
#include <time.h> 
//辅助订单创建 
void genOrderId(char* outId, int seq)
{
    time_t t = time(NULL);
    struct tm* tm = localtime(&t);
    sprintf(outId, "WL%04d%02d%02d%06d",
        tm->tm_year + 1900,
        tm->tm_mon + 1,
        tm->tm_mday,
        seq);
}



int createOrderWin()
{
    // 窗口整体下移，扩大高度，保证按钮完全可见
    WINDOW_T win = {
        200, 30, 520, 600, WHITE, 22,
        {
            // 客户姓名（标签+输入框）
            {220,  60, 120, 35, "客户姓名：",  CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
            {350,  60, 150, 35, "",           CYAN, LIGHTCYAN, WHITE, EDIT,  1, 20},

            // 联系电话
            {220, 110, 120, 35, "联系电话：", CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
            {350, 110, 150, 35, "",           CYAN, LIGHTCYAN, WHITE, EDIT,  0, 15},

            // 收货地址
            {220, 160, 120, 35, "收货地址：", CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
            {350, 160, 150, 35, "",           CYAN, LIGHTCYAN, WHITE, EDIT,  0, 60},

            // 发货地址
            {220, 210, 120, 35, "发货地址：", CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
            {350, 210, 150, 35, "",           CYAN, LIGHTCYAN, WHITE, EDIT,  0, 60},

            // 货物名称
            {220, 260, 120, 35, "货物名称：", CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
            {350, 260, 150, 35, "",           CYAN, LIGHTCYAN, WHITE, EDIT,  0, 20},

            // 货物类型
            {220, 310, 120, 35, "货物类型：", CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
            {350, 310, 150, 35, "",           CYAN, LIGHTCYAN, WHITE, EDIT,  0, 20},

            // 重量
            {220, 360, 120, 35, "重量：",      CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
            {350, 360, 150, 35, "",           CYAN, LIGHTCYAN, WHITE, EDIT,  0, 10},

            // 数量
            {220, 410, 120, 35, "数量：",      CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
            {350, 410, 150, 35, "",           CYAN, LIGHTCYAN, WHITE, EDIT,  0, 10},

            // 体积
            {220, 460, 120, 35, "体积：",      CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
            {350, 460, 150, 35, "",           CYAN, LIGHTCYAN, WHITE, EDIT,  0, 10},

            // 期望送达
            {220, 510, 120, 35, "期望送达：",  CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
            {350, 510, 150, 35, "",           CYAN, LIGHTCYAN, WHITE, EDIT,  0, 20},  //19

            // 按钮（居中、下移到底部）
            {230, 555, 120, 40, "确认创建",    CYAN, LIGHTCYAN, WHITE, BUTTON, 0, 0},    //21
            {370, 555, 120, 40, "返回",        CYAN, LIGHTCYAN, WHITE, BUTTON, 0, 1},  //22
        }
    };

    Background_display();
    window_show(win);
    win = window_run(win);

    if(win.current == 20) 
    {
    	ORDER_T ord;
        memset(&ord,0,sizeof(ord));

        int seq = getListNodeCount(orderList)+1;
        genOrderId(ord.orderId, seq);

        strcpy(ord.cusName, win.controls[1].text);
        strcpy(ord.cusPhone, win.controls[3].text);
        strcpy(ord.cusAddr, win.controls[5].text);
        strcpy(ord.sendAddr, win.controls[7].text);
        strcpy(ord.goodsName, win.controls[9].text);
        strcpy(ord.goodsType, win.controls[11].text);
		sscanf(win.controls[13].text, "%lf", &ord.goodsWeight);
		sscanf(win.controls[15].text, "%d",  &ord.goodsNum);
		sscanf(win.controls[17].text, "%lf", &ord.goodsVolume);
        strcpy(ord.expectTime, win.controls[19].text);
        ord.orderStatus = 0;  

        file_add(order_fp, sizeof(ORDER_T), &ord);
        insertAtTail(orderList, &ord);
    	return 7;
	}
	else if(win.current == 21) 
	{
		return 6;   //回到订单总界面 
	}
}

int checkOrderWin()
{
    WINDOW_T win = {200,100,500,400,WHITE,7,{
        {220,120,150,40,"输入待审核订单号",CYAN,LIGHTCYAN,WHITE,LABEL,0,0},
        {220,170,200,40,"",CYAN,LIGHTCYAN,WHITE,EDIT,1,25},
        {220,240,120,40,"通过",CYAN,LIGHTCYAN,WHITE,BUTTON,0,0},
        {360,240,120,40,"驳回",CYAN,LIGHTCYAN,WHITE,BUTTON,0,1},
        {220,300,200,40,"驳回原因",CYAN,LIGHTCYAN,WHITE,LABEL,0,0},
        {220,350,200,40,"",CYAN,LIGHTCYAN,WHITE,EDIT,0,60},
        {220,400,120,40,"返回",CYAN,LIGHTCYAN,WHITE,BUTTON,0,2},  //6
    }};

    Background_display();
    window_show(win);
    win = window_run(win);

    if(win.current == 6) 
	{
		return 6;
	}

    char oid[25];
    strcpy(oid, win.controls[1].text);

    LNode* cur = orderList->next;
    while(cur)
    {
        ORDER_T* p = (ORDER_T*)cur->data;
        if(strcmp(p->orderId, oid)==0 && p->orderStatus==0)
        {
            if(win.current == 0)
            {
                p->orderStatus = 1;
            }
            if(win.current == 1)
            {
                p->orderStatus = 2;
                strcpy(p->rejectReason, win.controls[5].text);
            }
            break;
        }
        cur = cur->next;
    }
    return 9;   
} 
  

int orderSerch()
{
    WINDOW_T win = {200,100,500,450,WHITE,4,{
        {220,120,120,40,"订单号：",CYAN,LIGHTCYAN,WHITE,LABEL,0,0},
        {350,120,150,40,"",CYAN,LIGHTCYAN,WHITE,EDIT,1,25},
        {220,180,120,40,"客户姓名：",CYAN,LIGHTCYAN,WHITE,LABEL,0,0},
        {350,180,150,40,"",CYAN,LIGHTCYAN,WHITE,EDIT,0,20},
        {220,240,120,40,"状态查询：",CYAN,LIGHTCYAN,WHITE,LABEL,0,0},
        {350,240,150,40,"",CYAN,LIGHTCYAN,WHITE,EDIT,0,10},
        {220,300,120,40,"修改电话：",CYAN,LIGHTCYAN,WHITE,LABEL,0,0},
        {350,300,150,40,"",CYAN,LIGHTCYAN,WHITE,EDIT,0,15},
        {220,360,120,40,"查询",CYAN,LIGHTCYAN,WHITE,BUTTON,0,0},
        {360,360,120,40,"修改",CYAN,LIGHTCYAN,WHITE,BUTTON,0,1},
        {220,420,120,40,"返回",CYAN,LIGHTCYAN,WHITE,BUTTON,0,2},
    }};

    Background_display();
    window_show(win);
    win = window_run(win);
    return 9;
}

int trackOrderWin()
{
    WINDOW_T win = {200,100,520,400,WHITE,4,{
        {220,120,150,40,"订单号",CYAN,LIGHTCYAN,WHITE,LABEL,0,0},
        {380,120,120,40,"",CYAN,LIGHTCYAN,WHITE,EDIT,1,25},
        {220,180,150,40,"跟踪信息",CYAN,LIGHTCYAN,WHITE,LABEL,0,0},
        {220,230,280,80,"",CYAN,LIGHTCYAN,WHITE,LABEL,0,0},
        {220,330,120,40,"返回",CYAN,LIGHTCYAN,WHITE,BUTTON,0,0},
    }};

    Background_display();
    window_show(win);
    win = window_run(win);
    return 9;
}

int orderWin()   //主窗口（形式展示）->分窗口（真正的功能实现） 
{
    WINDOW_T win={290,155,220,330,WHITE,5,{
        {300,160,200,40,"1.创建订单",LIGHTCYAN,CYAN,WHITE,BUTTON,1,0},  //0
        {300,200,200,40,"2.订单审核",LIGHTCYAN,CYAN,WHITE,BUTTON,0,0},  //1
        {300,240,200,40,"3.订单查询",LIGHTCYAN,CYAN,WHITE,BUTTON,0,0},  //2
        {300,280,200,40,"4.订单跟踪",LIGHTCYAN,CYAN,WHITE,BUTTON,0,0},  //3
        {300,320,200,40,"5.返回上级",LIGHTCYAN,CYAN,WHITE,BUTTON,0,0},  //4
    },0};
    
	Background_display();

    //必要的函数编译完成，再进行驱动 
    
    window_show(win);
    win = window_run(win);

    if(win.current == 0)
    {
        return 7;    //创建订单
    }
    else if(win.current== 1)
    { 
        return 8;    //审核订单 
    }
    else if(win.current == 2)
    {
        return 9;   //查询订单 
    }
    else if(win.current == 3)
    {
        return 10; //跟踪订单 
    }
    else if (win.current == 4)
    {
    	return 2;  //mianWin 
	}
}
