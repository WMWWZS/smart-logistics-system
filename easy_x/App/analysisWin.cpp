#include "analysisWin.h"
#include "../public/list.h"
#include "../View/control.h"
#include <string.h>
#include <stdio.h>
#include <windows.h>

extern LNode* orderList;
extern LNode* goodsList;
extern FILE* exports_fp;

StatOrder stat_order()
{
    StatOrder s;
    s.total  = 0;
    s.done   = 0;
    s.reject = 0;

    LNode *cur = orderList->next;
    while (cur != NULL)
    {
        ORDER_T *o = (ORDER_T *)cur->data;
        s.total++;
        if (o->orderStatus == 6) s.done++;
        if (o->orderStatus == 2) s.reject++;
        cur = cur->next;
    }
    return s;
}

StatStore stat_store()
{
    StatStore s;
    s.in    = 0;
    s.out   = 0;
    s.stock = 0;

    LNode *cur = goodsList->next;
    while (cur != NULL)
    {
        GOODS_T *g = (GOODS_T *)cur->data;
        s.in++;
        if (strlen(g->outTime) > 0)
            s.out++;
        else
            s.stock += g->goodsNum;
        cur = cur->next;
    }
    return s;
}

StatTransport stat_transport()
{
    StatTransport s;
    s.transport = 0;
    s.delivered = 0;
    s.totalTransport = 0;

    LNode *cur = orderList->next;
    while (cur != NULL)
    {
        ORDER_T *o = (ORDER_T *)cur->data;
        if (o->orderStatus == 4)
        {
            s.transport++;
            s.totalTransport++;
        }
        else if (o->orderStatus == 5)
        {
            s.delivered++;
            s.totalTransport++;
        }
        cur = cur->next;
    }
    return s;
}

void stat_export(FILE *fp)
{
    if (fp == NULL) 
	return;

    StatOrder os = stat_order();
    StatStore  ss = stat_store();
    StatTransport ts = stat_transport();

    fprintf(fp, "物流报表 \n\n");
    fprintf(fp, "【订单统计】\n");
    fprintf(fp, "订单总数：%d\n", os.total);
    fprintf(fp, "完成订单：%d\n", os.done);
    fprintf(fp, "驳回订单：%d\n\n", os.reject);
    fprintf(fp, "【仓储统计】\n");
    fprintf(fp, "入库总量：%d\n", ss.in);
    fprintf(fp, "出库总量：%d\n", ss.out);
    fprintf(fp, "当前库存：%d\n\n", ss.stock);
    fprintf(fp, "【运输统计】\n");
    fprintf(fp, "运输中：%d\n", ts.transport);
    fprintf(fp, "已送达：%d\n", ts.delivered);
    fprintf(fp, "总运输订单：%d\n", ts.totalTransport);

    fclose(fp);
}

int analysisWin()
{
    WINDOW_T win = {
        290, 155, 220, 410, CYAN, 5,
        {
            {300, 160, 200, 40, "1.订单统计", LIGHTCYAN, CYAN, WHITE, BUTTON, 1, 0},
            {300, 210, 200, 40, "2.仓储统计", LIGHTCYAN, CYAN, WHITE, BUTTON, 0, 0},
            {300, 260, 200, 40, "3.运输统计", LIGHTCYAN, CYAN, WHITE, BUTTON, 0, 0},
            {300, 310, 200, 40, "4.生成报表", LIGHTCYAN, CYAN, WHITE, BUTTON, 0, 0},
            {300, 360, 200, 40, "5.返回上级", LIGHTCYAN, CYAN, WHITE, BUTTON, 0, 0}
        }
    };

    Background_display();
    window_show(win);
    win = window_run(win);

    if(win.current == 0)
        return 16;
    if(win.current == 1)
        return 17;
    if(win.current == 2)
        return 19;
    if(win.current == 3)
        return 18;
    if(win.current == 4)
        return 2;
}

int orderStatWin()
{
    StatOrder os = stat_order();

    WINDOW_T win = {
        200, 100, 500, 350, CYAN, 8,
        {
            {220, 120, 200, 30, "订单统计",     LIGHTCYAN, CYAN, WHITE, LABEL, 0, 0},
            {220, 160, 200, 30, "订单总数：",   CYAN, LIGHTCYAN, WHITE, LABEL, 0, 1},
            {350, 160, 100, 30, "0",            CYAN, LIGHTCYAN, WHITE, LABEL, 0, 2},
            {220, 200, 200, 30, "完成订单：",   CYAN, LIGHTCYAN, WHITE, LABEL, 0, 3},
            {350, 200, 100, 30, "0",            CYAN, LIGHTCYAN, WHITE, LABEL, 0, 4},
            {220, 240, 200, 30, "驳回订单：",   CYAN, LIGHTCYAN, WHITE, LABEL, 0, 5},
            {350, 240, 100, 30, "0",            CYAN, LIGHTCYAN, WHITE, LABEL, 0, 6},
            {300, 290, 120, 40, "返回",         LIGHTCYAN, CYAN, WHITE, BUTTON, 0, 7}
        }
    };

    sprintf(win.controls[2].text, "%d", os.total);
    sprintf(win.controls[4].text, "%d", os.done);
    sprintf(win.controls[6].text, "%d", os.reject);

    Background_display();
    window_show(win);
    win = window_run(win);

    if(win.current == 7)
        return 15;
    return orderStatWin();
}

int storeStatWin()
{
    StatStore ss = stat_store();

    WINDOW_T win = {
        200, 100, 500, 350, CYAN, 8,
        {
            {220, 120, 200, 30, "仓储统计",     LIGHTCYAN, CYAN, WHITE, LABEL, 0, 0},
            {220, 160, 200, 30, "入库总量：",   CYAN, LIGHTCYAN, WHITE, LABEL, 0, 1},
            {350, 160, 100, 30, "0",            CYAN, LIGHTCYAN, WHITE, LABEL, 0, 2},
            {220, 200, 200, 30, "出库总量：",   CYAN, LIGHTCYAN, WHITE, LABEL, 0, 3},
            {350, 200, 100, 30, "0",            CYAN, LIGHTCYAN, WHITE, LABEL, 0, 4},
            {220, 240, 200, 30, "当前库存：",   CYAN, LIGHTCYAN, WHITE, LABEL, 0, 5},
            {350, 240, 100, 30, "0",            CYAN, LIGHTCYAN, WHITE, LABEL, 0, 6},
            {300, 290, 120, 40, "返回",         LIGHTCYAN, CYAN, WHITE, BUTTON, 0, 7}
        }
    };

    sprintf(win.controls[2].text, "%d", ss.in);
    sprintf(win.controls[4].text, "%d", ss.out);
    sprintf(win.controls[6].text, "%d", ss.stock);

    Background_display();
    window_show(win);
    win = window_run(win);

    if(win.current == 7)
        return 15;
    return storeStatWin();
}

int transportStatWin()
{
    StatTransport ts = stat_transport();

    WINDOW_T win = {
        200, 100, 500, 380, CYAN, 9,
        {
            {220, 120, 200, 30, "运输统计",         LIGHTCYAN, CYAN, WHITE, LABEL, 0, 0},
            {220, 160, 200, 30, "运输中订单：",     CYAN, LIGHTCYAN, WHITE, LABEL, 0, 1},
            {350, 160, 100, 30, "0",                CYAN, LIGHTCYAN, WHITE, LABEL, 0, 2},
            {220, 200, 200, 30, "已送达订单：",     CYAN, LIGHTCYAN, WHITE, LABEL, 0, 3},
            {350, 200, 100, 30, "0",                CYAN, LIGHTCYAN, WHITE, LABEL, 0, 4},
            {220, 240, 200, 30, "总运输订单：",     CYAN, LIGHTCYAN, WHITE, LABEL, 0, 5},
            {350, 240, 100, 30, "0",                CYAN, LIGHTCYAN, WHITE, LABEL, 0, 6},
            {300, 290, 120, 40, "查看详情",         LIGHTCYAN, CYAN, WHITE, BUTTON, 0, 7},
            {300, 340, 120, 40, "返回",             LIGHTCYAN, CYAN, WHITE, BUTTON, 0, 8}
        }
    };

    sprintf(win.controls[2].text, "%d", ts.transport);
    sprintf(win.controls[4].text, "%d", ts.delivered);
    sprintf(win.controls[6].text, "%d", ts.totalTransport);

    Background_display();
    window_show(win);
    win = window_run(win);

    if(win.current == 7)
        return 27;
    else if(win.current == 8)
        return 15;
    return transportStatWin();
}

int exportReportWin()
{
    stat_export(exports_fp);

    CONTROL_T tip = {245, 300, 200, 80, "报表已生成", LIGHTCYAN,CYAN,  WHITE, BUTTON, 0};
    control_show(tip);
    Sleep(1500);
    return 15;
}

