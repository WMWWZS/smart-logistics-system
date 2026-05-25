#include "data.h"
#include "../public/list.h"
#include "../View/control.h"
#include <string.h>
#include <windows.h>
#include <time.h> 
int analysisWin()
{
    WINDOW_T win = {
        200, 100, 500, 400, WHITE, 4,
        {
            {220, 120, 200, 40, "1.订单统计", LIGHTCYAN, CYAN, WHITE, BUTTON, 0, 0},
            {220, 180, 200, 40, "2.仓储统计", LIGHTCYAN, CYAN, WHITE, BUTTON, 0, 1},
            {220, 240, 200, 40, "3.生成报表", LIGHTCYAN, CYAN, WHITE, BUTTON, 0, 2},
            {220, 300, 200, 40, "4.返回", LIGHTCYAN, CYAN, WHITE, BUTTON, 0, 3},
        }
    };

    Background_display();
    window_show(win);
    win = window_run(win);

    if(win.current == 0) 
	return 17;
    else if(win.current == 1) 
	return 18;
    else if(win.current == 2) 
	return 19;
    else if(win.current == 3) 
	return 2;
    return analysisWin();
}

int orderStatWin()
{
    WINDOW_T win = {
        200, 100, 500, 400, WHITE, 3,
        {
            {220, 120, 200, 40, "1.按时间统计", LIGHTCYAN, CYAN, WHITE, BUTTON, 0, 0},
            {220, 180, 200, 40, "2.按货物类型统计", LIGHTCYAN, CYAN, WHITE, BUTTON, 0, 1},
            {220, 240, 200, 40, "3.返回", LIGHTCYAN, CYAN, WHITE, BUTTON, 0, 2},
        }
    };

    Background_display();
    window_show(win);
    win = window_run(win);

    if(win.current == 2) return analysisWin();

    //按时间统计（日/周/月，简化为全部订单统计）
    if(win.current == 0)
    {
        int total=0, completed=0, rejected=0;
        LNode* cur = orderList->next;
        while(cur != NULL)
        {
            ORDER_T* ord = (ORDER_T*)cur->data;
            total++;
            if(ord->orderStatus == 6) completed++; // 已完成
            if(ord->orderStatus == 2) rejected++;   // 已驳回
            cur = cur->next;
        }

        float completionRate = total > 0 ? (float)completed/total*100 : 0;
        float rejectionRate = total > 0 ? (float)rejected/total*100 : 0;

        char text[500];
        sprintf(text,
            "订单总数：%d\n"
            "完成订单：%d\n"
            "驳回订单：%d\n"
            "完成率：%.2f%%\n"
            "驳回率：%.2f%%",
            total, completed, rejected, completionRate, rejectionRate);

        WINDOW_T resWin = {200, 100, 500, 350, WHITE, 2,
        {
            {220, 150, 250, 150, text, CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
            {300, 330, 120, 40, "返回", LIGHTCYAN, CYAN, WHITE, BUTTON, 0, 1},
        }};
        Background_display();
        window_show(resWin);
        resWin = window_run(resWin);
        return orderStatWin();
    }

    // 按货物类型统计
    else if(win.current == 1)
    {
        int typeA=0, typeB=0, typeC=0;
        LNode* cur = orderList->next;
        while(cur != NULL)
        {
            ORDER_T* ord = (ORDER_T*)cur->data;
            if(strcmp(ord->goodsType, "A类") == 0) typeA++;
            else if(strcmp(ord->goodsType, "B类") == 0) typeB++;
            else typeC++;
            cur = cur->next;
        }

        char text[300];
        sprintf(text, "A类订单：%d\nB类订单：%d\n其他订单：%d", typeA, typeB, typeC);
        WINDOW_T resWin = {200, 100, 400, 300, WHITE, 2,
        {
            {220, 150, 200, 100, text, CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
            {300, 280, 120, 40, "返回", LIGHTCYAN, CYAN, WHITE, BUTTON, 0, 1},
        }};
        Background_display();
        window_show(resWin);
        resWin = window_run(resWin);
        return orderStatWin();
    }
    return orderStatWin();
}

int storageStatWin()
{
    int inCount=0, outCount=0, currentStock=0, warningGoods=0;
    LNode* cur = goodsList->next;
    while(cur != NULL)
    {
        GOODS_T* g = (GOODS_T*)cur->data;
        inCount++; // 入库总量
        if(strlen(g->outTime) > 0) outCount++; // 已出库
        else currentStock += g->goodsNum;     // 当前库存
        if(g->goodsNum < 10 && strlen(g->outTime) == 0) warningGoods++; // 库存预警
        cur = cur->next;
    }

    char text[500];
    sprintf(text,
        "入库总量：%d\n"
        "出库总量：%d\n"
        "当前库存总量：%d\n"
        "预警货物数量：%d",
        inCount, outCount, currentStock, warningGoods);

    WINDOW_T win = {200, 100, 500, 350, WHITE, 2,
    {
        {220, 150, 250, 150, text, CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
        {300, 330, 120, 40, "返回", LIGHTCYAN, CYAN, WHITE, BUTTON, 0, 1},
    }};
    Background_display();
    window_show(win);
    win = window_run(win);
    if(win.current == 1) return analysisWin();
    return storageStatWin();
}

int exportReportWin()
{
    FILE* fp = fopen("物流统计报表.txt", "w");
    if(fp == NULL)
    {
        CONTROL_T errWin={245,300,200,80,"报表创建失败",CYAN,LIGHTCYAN,WHITE,BUTTON,0};
        control_show(errWin);
        Sleep(1500);
        return analysisWin();
    }

    // 1. 订单统计数据
    int totalOrders=0, completed=0, rejected=0;
    LNode* cur = orderList->next;
    while(cur != NULL)
    {
        ORDER_T* ord = (ORDER_T*)cur->data;
        totalOrders++;
        if(ord->orderStatus == 6) completed++;
        if(ord->orderStatus == 2) rejected++;
        cur = cur->next;
    }
    float completionRate = totalOrders > 0 ? (float)completed/totalOrders*100 : 0;

    // 2. 仓储统计数据
    int inCount=0, outCount=0, currentStock=0;
    cur = goodsList->next;
    while(cur != NULL)
    {
        GOODS_T* g = (GOODS_T*)cur->data;
        inCount++;
        if(strlen(g->outTime) > 0) outCount++;
        else currentStock += g->goodsNum;
        cur = cur->next;
    }

    // 写入报表内容
    fprintf(fp, "===== 智能物流管理系统统计报表 =====\n\n");
    fprintf(fp, "【一、订单统计】\n");
    fprintf(fp, "订单总数：%d\n", totalOrders);
    fprintf(fp, "已完成订单：%d\n", completed);
    fprintf(fp, "已驳回订单：%d\n", rejected);
    fprintf(fp, "订单完成率：%.2f%%\n\n", completionRate);

    fprintf(fp, "【二、仓储统计】\n");
    fprintf(fp, "入库总量：%d\n", inCount);
    fprintf(fp, "出库总量：%d\n", outCount);
    fprintf(fp, "当前库存总量：%d\n", currentStock);
    fprintf(fp, "库存预警货物数：%d\n\n", 
        ({int cnt=0; LNode* c=goodsList->next; while(c){GOODS_T* g=(GOODS_T*)c->data; if(g->goodsNum<10 && strlen(g->outTime)==0)cnt++; c=c->next;} cnt;}));

    fprintf(fp, "=====================================\n");
    fclose(fp);

    CONTROL_T succWin={245,300,200,80,"报表已生成：物流统计报表.txt",CYAN,LIGHTCYAN,WHITE,BUTTON,0};
    control_show(succWin);
    Sleep(1500);
    return analysisWin();
}
