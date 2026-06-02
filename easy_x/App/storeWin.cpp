#include "data.h"
#include "../public/list.h"
#include "../View/control.h"
#include <string.h>
#include <windows.h>
#include <time.h>
#include "../public/list.h"
int goodIn()
{
    static int pageNow = 1;
    const int pageCount = 3;
    int count = 0;
    ORDER_T *p;

    //入库窗口（只显示"待审核"的订单）
    WINDOW_T win = {
        0, 100, 850, 450, CYAN, 6,
        {
            {50, 120, 120, 40, "订单号：", CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
            {190, 120, 200, 40, "", CYAN, LIGHTCYAN, WHITE, EDIT, 0, 30}, // 订单号输入框
            {400, 120, 120, 40, "货位编号：", CYAN, LIGHTCYAN, WHITE, LABEL, 0, 2},
            {540, 120, 150, 40, "", CYAN, LIGHTCYAN, WHITE, EDIT, 0, 30}, // 货位编号输入框
            {350, 200, 120, 40, "确认入库", LIGHTCYAN, CYAN, WHITE, BUTTON, 0, 4},
            {500, 200, 120, 40, "返回", LIGHTCYAN, CYAN, WHITE, BUTTON, 0, 5},
        }
    };

    TABLE_T orderTable = {
        0, 180, 850, 220,
        4, 6,
        {"订单号", "客户姓名", "货物名", "数量", "状态", "期望时间"}
    };

		printf("DEBUG: 总订单数=%d\n", count);
	for(int i=0; i<count; i++) {
	    ORDER_T *t = (ORDER_T *)findNode(orderList, i);
	    if(t) {
	        printf("订单号=%s, 状态=%d\n", t->orderId, t->orderStatus);
	    }
	}
    memset(orderTable.data, 0, sizeof(orderTable.data));
    count = getListNodeCount(orderList);
    int pageNum = (count + pageCount - 1) / pageCount;
    int start = (pageNow - 1) * pageCount;

    for(int i=0; i<pageCount; i++)
    {
        if(start + i >= count) break;
        p = (ORDER_T*)findNode(orderList, start + i);
        if(p == NULL || p->orderStatus != 1) continue; // 只显示已通过的订单

        int j=0;
        strcpy(orderTable.data[i][j++], p->orderId);
        strcpy(orderTable.data[i][j++], p->cusName);
        strcpy(orderTable.data[i][j++], p->goodsName);
        sprintf(orderTable.data[i][j++], "%d", p->goodsNum);
        strcpy(orderTable.data[i][j++], "已通过");
        strcpy(orderTable.data[i][j++], p->expectTime);
    }

    Background_display();
    window_show(win);
    table_show(orderTable, pageNum, pageNow);
    win = window_run(win);

    if(win.current == 4)
    {
        char orderId[25], storageLoc[10];
        strcpy(orderId, win.controls[1].text);
        strcpy(storageLoc, win.controls[3].text);

        ORDER_T* targetOrder = NULL;
        LNode* cur = orderList->next;
        while(cur != NULL)
        {
            ORDER_T* ord = (ORDER_T*)cur->data;
            if(strcmp(ord->orderId, orderId) == 0 && ord->orderStatus == 1)
            {
                targetOrder = ord;
                break;
            }
            cur = cur->next;
        }

        if(targetOrder == NULL)
        {
            CONTROL_T errWin={245,300,200,80,"订单不存在或状态不符",CYAN, LIGHTCYAN,WHITE,BUTTON,0};
            control_show(errWin);
            Sleep(1500);
            return goodIn();
        }

        //1.更新订单状态为"待运输"
        targetOrder->orderStatus = 3;

        //2.创建货物信息，写入文件和链表
        GOODS_T* goods = (GOODS_T*)malloc(sizeof(GOODS_T));
        memset(goods, 0, sizeof(GOODS_T));

        strcpy(goods->orderId, targetOrder->orderId);
        strcpy(goods->goodsName, targetOrder->goodsName);
        strcpy(goods->goodsType, targetOrder->goodsType);
        goods->goodsWeight = targetOrder->goodsWeight;
        goods->goodsNum = targetOrder->goodsNum;
        strcpy(goods->storageLoc, storageLoc);

        //    获取当前时间作为入库时间
        time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        sprintf(goods->inTime, "%04d-%02d-%02d %02d:%02d:%02d",
                tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday,
                tm->tm_hour, tm->tm_min, tm->tm_sec);

        //     写入文件
        fwrite(goods, sizeof(GOODS_T), 1, goods_fp);
        insertAtTail(goodsList, goods);

        CONTROL_T succWin={245,300,200,80,"入库成功！",CYAN, LIGHTCYAN,WHITE,BUTTON,0};
        control_show(succWin);
        Sleep(1500);
        return goodIn();
    }
    else if(win.current == 5)
    {
        return 10;
    }
    // 翻页逻辑
    else if(win.current == -1)
    {
        if(pageNow > 1) pageNow--;
        return goodIn();
    }
    else if(win.current == -2)
    {
        if(pageNow < pageNum) pageNow++;
        return goodIn();
    }
    return goodIn();
}

int goodOut()
{
    static int pageNow = 1;
    int pageNum;
    const int pageCount = 3;
    int count = 0;
    GOODS_T* p;

    //   出 库窗口
    WINDOW_T win = {
        0, 100, 850, 450, CYAN, 6,
        {
            {50, 120, 120, 40, "订单号：",CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
            {180, 120, 200, 40, "", CYAN, LIGHTCYAN, WHITE, EDIT, 0, 40}, // 订单号输入框
            {400, 120, 120, 40, "经办人：", CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
            {530, 120, 150, 40, "", CYAN, LIGHTCYAN, WHITE, EDIT, 0, 20}, // 经办人输入框
            {350, 200, 120, 40, "确认出库",CYAN, LIGHTCYAN, WHITE, BUTTON, 0, 0},   //4
            {500, 200, 120, 40, "返回", CYAN, LIGHTCYAN, WHITE, BUTTON, 0, 1}, //5
        }
    };

    TABLE_T goodsTable = {
        0, 180, 850, 220,
        3, 6,
        {"货物ID", "订单号", "货物名", "数量", "货位", "入库时间"}
    };

    //      显示所有库存中的货物
    memset(goodsTable.data, 0, sizeof(goodsTable.data));
    count = getListNodeCount(goodsList);
    pageNum = (count + pageCount - 1) / pageCount;
    int start = (pageNow - 1) * pageCount;

    for(int i=0; i<pageCount; i++)
    {
        if(start + i >= count) break;
        p = (GOODS_T*)findNode(goodsList, start + i);
        if(p == NULL) continue;

        int j=0;
        strcpy(goodsTable.data[i][j++], p->goodsId);
        strcpy(goodsTable.data[i][j++], p->orderId);
        strcpy(goodsTable.data[i][j++], p->goodsName);
        sprintf(goodsTable.data[i][j++], "%d", p->goodsNum);
        strcpy(goodsTable.data[i][j++], p->storageLoc);
        strcpy(goodsTable.data[i][j++], p->inTime);
    }

    Background_display();
    window_show(win);
    table_show(goodsTable, pageNum, pageNow);
    win = window_run(win);

      //     确认出库
    if(win.current == 4)
    {
        char orderId[25], handler[20];
        strcpy(orderId, win.controls[1].text);
        strcpy(handler, win.controls[3].text);

        //   找到对应货物和订单
        GOODS_T* targetGoods = NULL;
        LNode* cur = goodsList->next;
        while(cur != NULL)
        {
            GOODS_T* g = (GOODS_T*)cur->data;
            if(strcmp(g->orderId, orderId) == 0)
            {
                targetGoods = g;
                break;
            }
            cur = cur->next;
        }

        if(targetGoods == NULL)
        {
            CONTROL_T errWin={245,300,200,80,"货物不存在",CYAN, LIGHTCYAN,WHITE,BUTTON,0};
            control_show(errWin);
            Sleep(1500);
            return goodOut();
        }

              //1.更新订单状态为"运输中"
        ORDER_T* targetOrder = NULL;
        LNode* ordCur = orderList->next;
        while(ordCur != NULL)
        {
            ORDER_T* ord = (ORDER_T*)ordCur->data;
            if(strcmp(ord->orderId, orderId) == 0)
            {
                targetOrder = ord;
                break;
            }
            ordCur = ordCur->next;
        }
        if(targetOrder != NULL)
        {
            targetOrder->orderStatus = 4; //运输中
        }

              //2.更新货物信息
        strcpy(targetGoods->handler, handler);
        time_t t = time(NULL);
        struct tm* tm = localtime(&t);
        sprintf(targetGoods->outTime, "%04d-%02d-%02d %02d:%02d:%02d",
                tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday,
                tm->tm_hour, tm->tm_min, tm->tm_sec);

        //出库成功提示
        CONTROL_T succWin={245,300,200,80,"出库成功！",CYAN, LIGHTCYAN,WHITE,BUTTON,0};
        control_show(succWin);
        Sleep(1500);
        return goodOut();
    }

    //翻页逻辑
    else if(win.current == -1)
    {
        if(pageNow > 1)
		pageNow--;
        return goodOut();
    }
    else if(win.current == -2)
    {
        if(pageNow < pageNum) pageNow++;
        return goodOut();
    }

    // 返回
    else if(win.current == 5)
    {
        return 10;
    }

}

int goodSeach()
{
    static int pageNow = 1;
    const int pageCount = 5;
    int pageNum;
    int count = 0;
    static char buf[50] = {0};
    static LNode* tempList = NULL;
    GOODS_T* p;

    WINDOW_T win = {
        0, 100, 850, 450, WHITE, 4,
        {
            {50, 120, 100, 40, "搜索：", LIGHTCYAN, CYAN, WHITE, LABEL, 0, 0},
            {160, 120, 200, 40, "", CYAN, LIGHTCYAN, WHITE, EDIT, 0, 40},
            {380, 120, 100, 40, "搜索", LIGHTCYAN, CYAN, WHITE, BUTTON, 0, 0},
            {700, 120, 100, 40, "返回", LIGHTCYAN, CYAN, WHITE, BUTTON, 0, 1},
        }
    };

    // 【优化】统一表格尺寸和列宽
    TABLE_T table = {
        20, 180, 810, 280,
        6, 9,
        {"订单号", "客户姓名", "电话", "货物名", "重量", "数量", "状态", "期望时间", "驳回原因"}
    };

    memset(table.data, 0, sizeof(table.data));

    if(strlen(buf) == 0)
    {
        count = getListNodeCount(goodsList);
        pageNum = (count + pageCount - 1) / pageCount;
        int start = (pageNow - 1) * pageCount;

        for(int i=0; i<pageCount; i++)
        {
            int idx = start + i;
            if(idx >= count) break;

            p = (GOODS_T*)findNode(goodsList, idx);
            if(p == NULL) continue;

            int j = 0;
            strcpy(table.data[i][j++], p->goodsName);
            strcpy(table.data[i][j++], p->goodsType);
            sprintf(table.data[i][j++], "%d", p->goodsNum);
            strcpy(table.data[i][j++], p->storageLoc);
            strcpy(table.data[i][j++], p->inTime);

            //显示状态:已入库/已出库
            if(strlen(p->outTime) == 0)
                strcpy(table.data[i][j++], "在库");
            else
                strcpy(table.data[i][j++], "已出库");
        }
    }
    else
    {
        count = getListNodeCount(tempList);
        pageNum = (count + pageCount - 1) / pageCount;
        int start = (pageNow - 1) * pageCount;

        for(int i=0; i<pageCount; i++)
        {
            int idx = start + i;
            if(idx >= count) break;

            GOODS_T* t = (GOODS_T*)findNode(tempList, idx);
            if(t == NULL) continue;

            int j = 0;
            strcpy(table.data[i][j++], t->goodsName);
            strcpy(table.data[i][j++], t->goodsType);
            sprintf(table.data[i][j++], "%d", t->goodsNum);
            strcpy(table.data[i][j++], t->storageLoc);
            strcpy(table.data[i][j++], t->inTime);
            if(strlen(t->outTime) == 0)
                strcpy(table.data[i][j++], "在库");
            else
                strcpy(table.data[i][j++], "已出库");
        }
    }

    Background_display();
    window_show(win);
    table_show(table, pageNum, pageNow);
    win = window_run(win);

    // 搜索按钮:模糊查询货物名称 类型 货位编号 订单号
    if(win.current == 2)
    {
        strcpy(buf, win.controls[1].text);
        pageNow = 1;

        if(tempList != NULL)
        {
            // 释放临时链表中的数据节点
            LNode* cur = tempList->next;
            while(cur != NULL)
            {
                LNode* next = cur->next;
                free(cur->data);
                free(cur);
                cur = next;
            }
            free(tempList);
        }
        tempList = initList();

        int total = getListNodeCount(goodsList);
        for(int k=0; k<total; k++)
        {
            GOODS_T* t = (GOODS_T*)findNode(goodsList, k);
            if(t == NULL) continue;

                        //模糊查询:支持货物名称  货物类型 货位编号  订单号
            if(strstr(t->goodsName, buf) != NULL ||
               strstr(t->goodsType, buf) != NULL ||
               strstr(t->storageLoc, buf) != NULL ||
               strstr(t->orderId, buf) != NULL)
            {
                    //创建新的数据副本，避免双重释放问题,!!!!!!!!!!!!!z这li进行标记bug！！！！！！！！！！！！！！！！ 
                GOODS_T* newGoods = (GOODS_T*)malloc(sizeof(GOODS_T));
                memcpy(newGoods, t, sizeof(GOODS_T));
                insertAtTail(tempList, newGoods);
            }
        }
        return goodSeach();
    }

    //上一页
    else if(win.current == -1)
    {
        if(pageNow > 1) pageNow--;
        return goodSeach();
    }

    //下一页
    else if(win.current == -2)
    {
        if(pageNow < pageNum) pageNow++;
        return goodSeach();
    }

    //返回
    else if(win.current == 3)
    {
        if(tempList != NULL)
        {
            //释放临时链表中的数据节点
            LNode* cur = tempList->next;
            while(cur != NULL)
            {
                LNode* next = cur->next;
                free(cur->data);
                free(cur);
                cur = next;
            }
            free(tempList);
            tempList = NULL;
        }
        memset(buf, 0, sizeof(buf));
        pageNow = 1;
        return 10;
    }

    return goodSeach();
}

int storeWin()
{
    WINDOW_T win={290,155,220,330,WHITE,4,{
        {300,160,200,40,"1.货物入库",LIGHTCYAN,CYAN, WHITE,BUTTON,1,0},    //0
        {300,200,200,40,"2.货物出库",LIGHTCYAN,CYAN,WHITE,BUTTON,0,0},  //1
        {300,240,200,40,"3.库存查询",LIGHTCYAN,CYAN,WHITE,BUTTON,0,0},  //2
        {300,280,200,40,"4.返回上级",LIGHTCYAN,CYAN,WHITE,BUTTON,0,0},  //3
    },0};

	Background_display();

    window_show(win);
    win = window_run(win);

    if(win.current==0)   //{goodIn,goodOut,goodSeach}; //存储区块11 12 13
    {
    	return 11; //货物入库
	}
	else if(win.current==1)
	{
		return 12; //货物出库
	}
    else if(win.current==2)
    {
    	return 13;    //货物查询
	}
	else if(win.current==3)
	{
		return 2;
	}
}


