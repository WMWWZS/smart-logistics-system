#include <graphics.h>
#include <conio.h>
#include "../View/control.h"
#include "string.h"
#include <stdio.h>
#include "data.h"
#include "../public/file.h"
#include <time.h>

extern LNode* orderList;
extern FILE* order_fp;

void genDispatchId(char* outId, int seq)
{
    time_t t = time(NULL);
    struct tm* tm = localtime(&t);
    sprintf(outId, "DD%04d%02d%02d%03d",
        tm->tm_year + 1900,
        tm->tm_mon + 1,
        tm->tm_mday,
        seq);
}

int createDispatch()
{
    WINDOW_T win = {
        200, 30, 520, 600, CYAN, 16,
        {
            {220,  60, 120, 35, "订单号：",    CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
            {350,  60, 150, 35, "",           CYAN, LIGHTCYAN, WHITE, EDIT,  1, 25},

            {220, 110, 120, 35, "车牌号：",    CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
            {350, 110, 150, 35, "",           CYAN, LIGHTCYAN, WHITE, EDIT,  0, 15},

            {220, 160, 120, 35, "车辆类型：",  CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
            {350, 160, 150, 35, "",           CYAN, LIGHTCYAN, WHITE, EDIT,  0, 20},

            {220, 210, 120, 35, "司机ID：",    CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
            {350, 210, 150, 35, "",           CYAN, LIGHTCYAN, WHITE, EDIT,  0, 15},

            {220, 260, 120, 35, "司机姓名：",  CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
            {350, 260, 150, 35, "",           CYAN, LIGHTCYAN, WHITE, EDIT,  0, 20},

            {220, 310, 120, 35, "线路信息：",  CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
            {350, 310, 150, 35, "",           CYAN, LIGHTCYAN, WHITE, EDIT,  0, 60},

            {220, 360, 120, 35, "出发时间：",  CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
            {350, 360, 150, 35, "",           CYAN, LIGHTCYAN, WHITE, EDIT,  0, 20},

            {230, 410, 120, 40, "确认调度",   LIGHTCYAN,CYAN, WHITE, BUTTON, 0, 0},
            {370, 410, 120, 40, "返回",       LIGHTCYAN,CYAN, WHITE, BUTTON, 0, 1},
        }
    };

    Background_display();
    window_show(win);
    win = window_run(win);

    if(win.current == 14)
    {
        char orderId[25] = {0};
        strcpy(orderId, win.controls[1].text);

        LNode* cur = orderList->next;
        int found = 0;
        while(cur)
        {
            ORDER_T* p = (ORDER_T*)cur->data;
            if(strcmp(p->orderId, orderId) == 0)
            {
                if(p->orderStatus == 3)
                {
                    p->orderStatus = 4;
                    found = 1;

                    int index = 0;
                    LNode* tmp = orderList->next;
                    while(tmp != cur)
                    {
                        index++;
                        tmp = tmp->next;
                    }
                    file_upDate(order_fp, sizeof(ORDER_T), p, index * sizeof(ORDER_T));
                }
                break;
            }
            cur = cur->next;
        }

        if(found)
        {
            CONTROL_T succWin = {245, 300, 200, 80, "调度成功", CYAN, LIGHTCYAN,  WHITE, BUTTON, 0};
            control_show(succWin);
            Sleep(1500);
        }
        else
        {
            CONTROL_T errWin = {245, 300, 200, 80, "订单不存在或状态不符", CYAN, LIGHTCYAN,  WHITE, BUTTON, 0};
            control_show(errWin);
            Sleep(1500);
        }
        return 25;
    }
    else if(win.current == 15)
    {
        return 24;
    }
}

int viewDispatch()
{
    static int pageNow = 1;
    int pageNum;
    int pageCount = 5;
    int count = 0;
    ORDER_T* p;

    WINDOW_T win = {
        0, 100, 850, 450, CYAN, 4,
        {
            {50, 120, 100, 40, "搜索：", CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
            {160, 120, 200, 40, "", CYAN, LIGHTCYAN, WHITE, EDIT, 0, 25},
            {380, 120, 100, 40, "查询", LIGHTCYAN, CYAN, WHITE, BUTTON, 0, 0},
            {700, 120, 100, 40, "返回", LIGHTCYAN, CYAN, WHITE, BUTTON, 0, 1},
        }
    };

    TABLE_T table = {
        20, 180, 810, 280,
        6, 6,
        {"订单号", "客户姓名", "货物名", "状态", "期望时间", "跟踪信息"}
    };
    memset(&table.data, 0, sizeof(table.data));

    count = getListNodeCount(orderList);
    int transportCount = 0;
    for(int i = 0; i < count; i++)
    {
        p = (ORDER_T*)findNode(orderList, i);
        if(p && (p->orderStatus == 4 || p->orderStatus == 5))
            transportCount++;
    }

    pageNum = (transportCount + pageCount - 1) / pageCount;
    if(pageNum < 1) pageNum = 1;

    int displayed = 0;
    int start = (pageNow - 1) * pageCount;

    for(int i = 0; i < count && displayed < start + pageCount; i++)
    {
        p = (ORDER_T*)findNode(orderList, i);
        if(p == NULL || (p->orderStatus != 4 && p->orderStatus != 5))
            continue;

        if(displayed >= start)
        {
            int j = 0;
            int row = displayed - start;
            strcpy(table.data[row][j++], p->orderId);
            strcpy(table.data[row][j++], p->cusName);
            strcpy(table.data[row][j++], p->goodsName);
            if(p->orderStatus == 4)
                strcpy(table.data[row][j++], "运输中");
            else if(p->orderStatus == 5)
                strcpy(table.data[row][j++], "已送达");
            strcpy(table.data[row][j++], p->expectTime);
            strcpy(table.data[row][j++], p->trackInfo);
        }
        displayed++;
    }

    Background_display();
    window_show(win);
    table_show(table, pageNum, pageNow);
    win = window_run(win);

    if(win.current == 2)
    {
        char orderId[25] = {0};
        strcpy(orderId, win.controls[1].text);
        if(strlen(orderId) > 0)
        {
            LNode* cur = orderList->next;
            while(cur)
            {
                ORDER_T* order = (ORDER_T*)cur->data;
                if(strcmp(order->orderId, orderId) == 0)
                {
                    const char* statusStr = "未知";
                    if(order->orderStatus == 4) statusStr = "运输中";
                    else if(order->orderStatus == 5) statusStr = "已送达";

                    char info[100] = {0};
                    sprintf(info, "订单:%s 客户:%s 状态:%s",
                        order->orderId, order->cusName, statusStr);
                    CONTROL_T infoWin = {200, 250, 400, 100, "", CYAN, LIGHTCYAN, WHITE, BUTTON, 0};
                    strcpy(infoWin.text, info);
                    control_show(infoWin);
                    Sleep(2000);
                    break;
                }
                cur = cur->next;
            }
        }
        return viewDispatch();
    }
    else if(win.current == -1)
    {
        if(pageNow > 1) pageNow--;
        else
        {
            CONTROL_T miniWin = {245, 300, 200, 80, "已经是第一页", LIGHTCYAN,CYAN,  WHITE, BUTTON, 0};
            control_show(miniWin);
            Sleep(1500);
        }
        return viewDispatch();
    }
    else if(win.current == -2)
    {
        if(pageNow < pageNum) pageNow++;
        else
        {
            CONTROL_T miniWin = {245, 300, 200, 80, "已经是最后一页", LIGHTCYAN,CYAN,  WHITE, BUTTON, 0};
            control_show(miniWin);
            Sleep(1500);
        }
        return viewDispatch();
    }
    else if(win.current == 3)
    {
        pageNow = 1;
        return 24;
    }
    return viewDispatch();
}

int carSearchWin()
{
    static int pageNow = 1;
    int pageNum;
    int pageCount = 5;
    int count = 0;
    static char buf2[100] = {0};
    static LNode* tempList = NULL;
    ORDER_T* p;
    int allCount;

    WINDOW_T win = {
        0, 100, 850, 450, WHITE, 4,
        {
            {50, 120, 100, 40, "搜索：", CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
            {160, 120, 200, 40, "", CYAN, LIGHTCYAN, WHITE, EDIT, 0, 40},
            {380, 120, 100, 40, "搜索", LIGHTCYAN, CYAN, WHITE, BUTTON, 0, 0},
            {700, 120, 100, 40, "返回", LIGHTCYAN, CYAN, WHITE, BUTTON, 0, 1},
        }
    };

    TABLE_T table = {
        20, 180, 810, 280,
        6, 6,
        {"订单号", "客户姓名", "电话", "货物名", "状态", "期望时间"}
    };
    memset(&table.data, 0, sizeof(table.data));

    if(strlen(buf2) == 0)
    {
        int transportCount = 0;
        allCount = getListNodeCount(orderList);

        for(int k = 0; k < allCount; k++)
        {
            p = (ORDER_T*)findNode(orderList, k);
            if(p && (p->orderStatus == 4 || p->orderStatus == 5))
                transportCount++;
        }

        pageNum = (transportCount + pageCount - 1) / pageCount;
        if(pageNum < 1) pageNum = 1;

        int start = (pageNow - 1) * pageCount;
        int displayed = 0;

        for(int k = 0; k < allCount && displayed < start + pageCount; k++)
        {
            p = (ORDER_T*)findNode(orderList, k);
            if(p == NULL || (p->orderStatus != 4 && p->orderStatus != 5))
                continue;

            if(displayed >= start)
            {
                int j = 0;
                int row = displayed - start;
                strcpy(table.data[row][j++], p->orderId);
                strcpy(table.data[row][j++], p->cusName);
                strcpy(table.data[row][j++], p->cusPhone);
                strcpy(table.data[row][j++], p->goodsName);
                if(p->orderStatus == 4)
                    strcpy(table.data[row][j++], "运输中");
                else if(p->orderStatus == 5)
                    strcpy(table.data[row][j++], "已送达");
                strcpy(table.data[row][j++], p->expectTime);
            }
            displayed++;
        }
    }
    else
    {
        count = getListNodeCount(tempList);
        pageNum = (count + pageCount - 1) / pageCount;
        if(pageNum < 1) pageNum = 1;

        int start = (pageNow - 1) * pageCount;

        memset(table.data, 0, sizeof(table.data));
        for(int i = 0; i < pageCount; i++)
        {
            if(start + i >= count) break;
            ORDER_T* t = (ORDER_T*)findNode(tempList, start + i);
            if(t == NULL) continue;
            int j = 0;
            strcpy(table.data[i][j++], t->orderId);
            strcpy(table.data[i][j++], t->cusName);
            strcpy(table.data[i][j++], t->cusPhone);
            strcpy(table.data[i][j++], t->goodsName);
            if(t->orderStatus == 4)
                strcpy(table.data[i][j++], "运输中");
            else if(t->orderStatus == 5)
                strcpy(table.data[i][j++], "已送达");
            strcpy(table.data[i][j++], t->expectTime);
        }
    }

    Background_display();
    window_show(win);
    table_show(table, pageNum, pageNow);
    win = window_run(win);

    if(win.current == 2)
    {
        if(strlen(win.controls[1].text) > 0)
        {
            strcpy(buf2, win.controls[1].text);
            if(tempList != NULL)
            {
                freeList(tempList);
                tempList = NULL;
            }
            tempList = initList();

            allCount = getListNodeCount(orderList);
            for(int k = 0; k < allCount; k++)
            {
                ORDER_T* t = (ORDER_T*)findNode(orderList, k);
                if(t == NULL) continue;
                if(t->orderStatus != 4 && t->orderStatus != 5) continue;

                if(strstr(t->orderId, buf2) != NULL ||
                   strstr(t->cusName, buf2) != NULL ||
                   strstr(t->goodsName, buf2) != NULL ||
                   strstr(t->cusPhone, buf2) != NULL)
                {
                    ORDER_T* newOrder = (ORDER_T*)malloc(sizeof(ORDER_T));
                    memcpy(newOrder, t, sizeof(ORDER_T));
                    insertAtTail(tempList, newOrder);
                }
            }
            pageNow = 1;
        }
        else
        {
            memset(buf2, 0, sizeof(buf2));
            pageNow = 1;
        }
        return carSearchWin();
    }
    else if(win.current == -1)
    {
        if(pageNow > 1) pageNow--;
        else
        {
            CONTROL_T miniWin = {245, 300, 200, 80, "已经是第一页", LIGHTCYAN,CYAN,  WHITE, BUTTON, 0};
            control_show(miniWin);
            Sleep(1500);
        }
        return carSearchWin();
    }
    else if(win.current == -2)
    {
        if(pageNow < pageNum) pageNow++;
        else
        {
            CONTROL_T miniWin = {245, 300, 200, 80, "已经是最后一页", LIGHTCYAN,CYAN,  WHITE, BUTTON, 0};
            control_show(miniWin);
            Sleep(1500);
        }
        return carSearchWin();
    }
    else if(win.current == 3)
    {
        if(tempList != NULL)
        {
            freeList(tempList);
            tempList = NULL;
        }
        memset(buf2, 0, sizeof(buf2));
        pageNow = 1;
        return 24;
    }
    return carSearchWin();
}

int carWin()
{
    WINDOW_T win = {290, 155, 220, 370, WHITE, 4, {
        {300, 160, 200, 40, "1.创建调度", LIGHTCYAN, CYAN, WHITE, BUTTON, 1, 0},
        {300, 200, 200, 40, "2.运输跟踪", LIGHTCYAN, CYAN, WHITE, BUTTON, 0, 0},
        {300, 240, 200, 40, "3.运输查询", LIGHTCYAN, CYAN, WHITE, BUTTON, 0, 0},
        {300, 280, 200, 40, "4.返回上级", LIGHTCYAN, CYAN, WHITE, BUTTON, 0, 0},
    }, 0};

    Background_display();
    window_show(win);
    win = window_run(win);

    if(win.current == 0)
        return 25;
    else if(win.current == 1)
        return 26;
    else if(win.current == 2)
        return 27;
    else if(win.current == 3)
        return 2;
}

