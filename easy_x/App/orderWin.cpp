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
//工具 


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
            {230, 555, 120, 40, "确认创建",    CYAN, LIGHTCYAN, WHITE, BUTTON, 0, 0},    //20
            {370, 555, 120, 40, "返回",        CYAN, LIGHTCYAN, WHITE, BUTTON, 0, 1},  //21
        }
    };

    Background_display();
    window_show(win);
    win = window_run(win);

    if(win.current == 20) 
    {
		ORDER_T* ord = (ORDER_T*)malloc(sizeof(ORDER_T)); 
	    memset(ord, 0, sizeof(ORDER_T));
	
	    int seq = getListNodeCount(orderList) + 1;
	    genOrderId(ord->orderId, seq);
	
	    strcpy(ord->cusName, win.controls[1].text);
	    strcpy(ord->cusPhone, win.controls[3].text);
	    strcpy(ord->cusAddr, win.controls[5].text);
	    strcpy(ord->sendAddr, win.controls[7].text);
	    strcpy(ord->goodsName, win.controls[9].text);
	    strcpy(ord->goodsType, win.controls[11].text);
	    sscanf(win.controls[13].text, "%d", &ord->goodsWeight);
	    sscanf(win.controls[15].text, "%d", &ord->goodsNum);
	    sscanf(win.controls[17].text, "%d", &ord->goodsVolume);
	    strcpy(ord->expectTime, win.controls[19].text);
	    ord->orderStatus = 0;
		
		fwrite(ord, sizeof(ORDER_T), 1, order_fp);
		fflush(order_fp);  //读取的是链表的数据 ，但是ord在这里的生命周期 ，出了if就结束 ，用堆
        insertAtTail(orderList, ord);
    	fflush (order_fp);
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
        {220,240,120,40,"通过",CYAN,LIGHTCYAN,WHITE,BUTTON,0,0},  //2
        {360,240,120,40,"驳回",CYAN,LIGHTCYAN,WHITE,BUTTON,0,1},  //3
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

    char oid[25] = {0};
    strcpy(oid, win.controls[1].text);

    LNode* cur = orderList->next;
    while(cur)
    {
        ORDER_T* p = (ORDER_T*)cur->data;
        if(strcmp(p->orderId, oid)==0 && p->orderStatus==0)
        {
            if(win.current == 2)
            {
                p->orderStatus = 1;
            }
            if(win.current == 3)
            {
                p->orderStatus = 2;
                strcpy(p->rejectReason, win.controls[5].text);
            }
            return 6;
        }
        cur = cur->next;
    }
    return 6;
} 
     

int orderSearchWin()
{
    static int pageNow = 1;
    int pageNum;
    int pageCount=3;
    int count=0;
    static char buf2[100]={0};
    static LNode* tempList=NULL;
    ORDER_T* p;
    int allCount;
	
    WINDOW_T win = {
        0, 100, 850, 450, WHITE, 4,
        {
            {50, 120, 120, 40, "搜索关键词：", CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
            {180, 120, 200, 40, "", CYAN, LIGHTCYAN, WHITE, EDIT, 0, 40},
            {400, 120, 120, 40, "搜索", CYAN, LIGHTCYAN, WHITE, BUTTON, 0, 0},
            {550, 120, 120, 40, "返回", CYAN, LIGHTCYAN, WHITE, BUTTON, 0, 1},
        }
    };

    TABLE_T table = {
        0, 120, 800, 220,
        4, 9,
        {"订单号", "客户姓名", "电话", "货物名", "重量", "数量", "状态", "期望时间", "驳回原因"}
    };
	memset(&table.data, 0, sizeof(table.data));
    // 1. 全量查询
    if(strlen(buf2)==0)
    {
        int i=0, j=0;
        count=getListNodeCount(orderList);	
        allCount = count;
        pageNum = (count + pageCount - 1) / pageCount;
        int start=(pageNow-1)*pageCount;

		memset(table.data, 0, sizeof(table.data));
		for(i=0; i<pageCount; i++)
		{
		    if(start + i >= count) break;
		    p = (ORDER_T *)findNode(orderList, start + i);
		    if(p == NULL) 
			continue;
		
		    j = 0;
		    strcpy(table.data[i][j++], p->orderId);
		    strcpy(table.data[i][j++], p->cusName);
		    strcpy(table.data[i][j++], p->cusPhone);
		    strcpy(table.data[i][j++], p->goodsName);
		    sprintf(table.data[i][j++], "%d", p->goodsWeight);
		    sprintf(table.data[i][j++], "%d", p->goodsNum);
		    if(p->orderStatus == 0)
		        strcpy(table.data[i][j++], "待审核");
		    else if(p->orderStatus == 1)
		        strcpy(table.data[i][j++], "已通过");
		    else if(p->orderStatus == 2)
		        strcpy(table.data[i][j++], "已驳回");
		    strcpy(table.data[i][j++], p->expectTime);
		    strcpy(table.data[i][j++], p->rejectReason);
		}
    }
    // 2. 筛选查询
    else
    {
        int i=0, j=0;
        count = getListNodeCount(tempList);
        pageNum = (count + pageCount - 1) / pageCount;
        int start = (pageNow - 1) * pageCount;

		// 筛选查询里的表格填充
		memset(table.data, 0, sizeof(table.data));
		for(i=0; i<pageCount; i++)
		{
		    if(start + i >= count) break;
		    ORDER_T *t = (ORDER_T *)findNode(tempList, start + i);
		    if(t == NULL) continue;
		    j = 0;
		    strcpy(table.data[i][j++], t->orderId);
		    strcpy(table.data[i][j++], t->cusName);
		    strcpy(table.data[i][j++], t->cusPhone);
		    strcpy(table.data[i][j++], t->goodsName);
		    sprintf(table.data[i][j++], "%d", t->goodsWeight);
		    sprintf(table.data[i][j++], "%d", t->goodsNum);
		    if(t->orderStatus == 0)
		        strcpy(table.data[i][j++], "待审核");
		    else if(t->orderStatus == 1)
		        strcpy(table.data[i][j++], "已通过");
		    else if(t->orderStatus == 2)
		        strcpy(table.data[i][j++], "已驳回");
		    strcpy(table.data[i][j++], t->expectTime);
		    strcpy(table.data[i][j++], t->rejectReason);
		}
    }

    Background_display();
    window_show(win);
    table_show(table, pageNum, pageNow);
    win = window_run(win);

    if(win.current == 2) // 搜索
    {
        if(strlen(win.controls[1].text) > 0)
        {
            strcpy(buf2, win.controls[1].text);
            if(tempList != NULL)
            {
                freeList(tempList);
                tempList = NULL;
            }
            tempList=initList();

            for(int k=0;k<allCount;k++)
            {
                ORDER_T *t = (ORDER_T *)findNode(orderList, k);
                if(t == NULL) continue;

                if(strstr(t->orderId, buf2) != NULL || strstr(t->cusName, buf2) != NULL)
                {
                    insertAtTail(tempList, t);
                }
            }
            pageNow=1;
        }
        else
        {
            memset(buf2,0,sizeof(buf2));
            pageNow=1;
        }
        return orderSearchWin();
    }
    else if(win.current == -1) // 上一页
    {
        if(pageNow > 1)
            pageNow--;
        else
        {
            CONTROL_T miniWin={245,300,200,80,"已经是第一页",CYAN,LIGHTCYAN,WHITE,BUTTON,0};
            control_show(miniWin);
            Sleep(1500);
        }
        return orderSearchWin();
    }
    else if(win.current == -2) // 下一页
    {
        if(pageNow < pageNum)
            pageNow++;
        else
        {
            CONTROL_T miniWin={245,300,200,80,"已经是最后一页",CYAN,LIGHTCYAN,WHITE,BUTTON,0};
            control_show(miniWin);
            Sleep(1500);
        }
        return orderSearchWin();
    }
    else if(win.current == 3) // 返回
    {
        if(tempList != NULL) 
        {
            freeList(tempList);
            tempList = NULL;
        }
        memset(buf2,0,sizeof(buf2));
        pageNow=1;
        return 6;
    }
    return orderSearchWin();
}

int trackOrderWin()
{
    WINDOW_T win = {
        70, 100, 520, 400, WHITE, 6,
        {
            {220, 120, 150, 40, "订单号", CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
            {380, 120, 120, 40, "", CYAN, LIGHTCYAN, WHITE, EDIT, 1, 25}, // 订单号输入框
            {220, 180, 150, 40, "跟踪信息", CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
            {220, 230, 280, 80, "", CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0}, // 显示跟踪信息
            {220, 330, 120, 40, "更新跟踪", CYAN, LIGHTCYAN, WHITE, BUTTON, 0, 0},  //4
            {380, 330, 120, 40, "返回", CYAN, LIGHTCYAN, WHITE, BUTTON, 0, 1},    //5
        }
    };

    // 初始化跟踪信息显示
    char trackDisplay[500] = "请输入订单号查询";

    Background_display();
    window_show(win);
    win = window_run(win);

    while (1)
    {
        // 更新跟踪信息显示
        setcolor(WHITE);
        setfillcolor(WHITE);
        solidrectangle(220, 230, 500, 310); // 清除旧信息
        setcolor(CYAN);
        outtextxy(220, 230, trackDisplay);

        win = window_run(win);

        // 1. 查询跟踪信息 
        if (strlen(win.controls[1].text) > 0)
        {
            char orderId[25];
            strcpy(orderId, win.controls[1].text);

            // 查找订单
            ORDER_T* targetOrder = NULL;
            LNode* cur = orderList->next;
            while (cur != NULL)
            {
                ORDER_T* ord = (ORDER_T*)cur->data;
                if (strcmp(ord->orderId, orderId) == 0)
                {
                    targetOrder = ord;
                    break;
                }
                cur = cur->next;
            }
            if (targetOrder == NULL)
            {
                strcpy(trackDisplay, "订单不存在");
            }
            else
            {
                // 显示订单状态和跟踪信息
                char statusStr[20];
                switch(targetOrder->orderStatus)
                {
                    case 0: strcpy(statusStr, "待审核"); 
					break;
                    case 1: strcpy(statusStr, "已通过");
					break;
                    case 2: strcpy(statusStr, "已驳回"); 
					break;
                    case 3: strcpy(statusStr, "待出库"); 
					break;
                    case 4: strcpy(statusStr, "运输中"); 
					break;
                    case 5: strcpy(statusStr, "已送达"); 
					break;
                    case 6: strcpy(statusStr, "已完成"); 
					break;
                    default: strcpy(statusStr, "未知状态");
                }
                	sprintf(trackDisplay, "订单状态：%s\n跟踪记录：\n%s", 
                    statusStr, targetOrder->trackInfo);
            }
        }

        // 2. 更新跟踪信息按钮
        if (win.current == 4)
        {
            char orderId[25];
            strcpy(orderId, win.controls[1].text);

            if (strlen(orderId) == 0)
            {
                CONTROL_T errWin={245,300,200,80,"请先输入订单号",CYAN,LIGHTCYAN,WHITE,BUTTON,0};
                control_show(errWin);
                Sleep(1500);
                continue;
            }

            ORDER_T* targetOrder = NULL;
            LNode* cur = orderList->next;
            while (cur != NULL)
            {
                ORDER_T* ord = (ORDER_T*)cur->data;
                if (strcmp(ord->orderId, orderId) == 0)
                {
                    targetOrder = ord;
                    break;
                }
                cur = cur->next;
            }

            if (targetOrder == NULL)
            {
                CONTROL_T errWin={245,300,200,80,"订单不存在",CYAN,LIGHTCYAN,WHITE,BUTTON,0};
                control_show(errWin);
                Sleep(1500);
                continue;
            }

            // 打开更新跟踪信息的窗口
            WINDOW_T updateWin = {
                0, 200, 400, 250, WHITE, 4,
                {
                    {320, 220, 150, 40, "输入新跟踪信息", CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
                    {320, 270, 200, 40, "", CYAN, LIGHTCYAN, WHITE, EDIT, 0, 100},
                    {350, 330, 100, 40, "确认", CYAN, LIGHTCYAN, WHITE, BUTTON, 0, 0},
                    {480, 330, 100, 40, "取消", CYAN, LIGHTCYAN, WHITE, BUTTON, 0, 1},
                }
            };

            Background_display();
            window_show(updateWin);
            updateWin = window_run(updateWin);

            if (updateWin.current == 0)
            {
                // 追加跟踪信息，带时间戳
                char newInfo[150];
                strcpy(newInfo, updateWin.controls[1].text);
                if (strlen(newInfo) == 0) 
				continue;

                time_t t = time(NULL);
                struct tm* tm = localtime(&t);
                char timeStr[30];
                sprintf(timeStr, "[%04d-%02d-%02d %02d:%02d] ",
                        tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday,
                        tm->tm_hour, tm->tm_min);

                // 追加到跟踪信息中
                char fullInfo[200];
                sprintf(fullInfo, "%s%s%s\n", targetOrder->trackInfo, timeStr, newInfo);
                strcpy(targetOrder->trackInfo, fullInfo);

                //同步更新文件
                fseek(order_fp, -sizeof(ORDER_T), SEEK_CUR);
                fwrite(targetOrder, sizeof(ORDER_T), 1, order_fp);
                fflush(order_fp);

                CONTROL_T succWin={245,300,200,80,"跟踪信息更新成功！",CYAN,LIGHTCYAN,WHITE,BUTTON,0};
                control_show(succWin);
                Sleep(1500);
            }
        }

        // 3. 返回按钮
        if (win.current == 5)
        {
            return 6;
        }
    }
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
