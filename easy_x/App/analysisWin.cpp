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
            {220, 120, 200, 40, "订单统计", LIGHTCYAN, CYAN, WHITE, BUTTON, 0, 0},
            {220, 180, 200, 40, "仓储统计", LIGHTCYAN, CYAN, WHITE, BUTTON, 0, 1},
            {220, 240, 200, 40, "生成报表", LIGHTCYAN, CYAN, WHITE, BUTTON, 0, 2},
            {220, 300, 200, 40, "返回",     LIGHTCYAN, CYAN, WHITE, BUTTON, 0, 3}
        }
    };

    Background_display();
    window_show(win);
    win = window_run(win);

    if(win.current == 0)
		return 17;
    if(win.current == 1)
		return 18;
    if(win.current == 2) 
		return 19;
    if(win.current == 3)
		return 16;		
    return 16;
}

int orderStatWin()
{
    // 真实统计订单数据
    int total = 0;
    int completed = 0;
    int rejected = 0;

    LNode *cur = orderList->next;
    while(cur != NULL)
    {
        ORDER_T *o = (ORDER_T*)cur->data;
        total++;
        if(o->orderStatus == 6) completed++;
        if(o->orderStatus == 2) rejected++;
        cur = cur->next;
    }

    WINDOW_T win = {
        200, 100, 500, 350, WHITE, 8,
        {
            {220, 120, 200, 30, "订单统计",     CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
            {220, 150, 200, 30, "订单总数",     CYAN, LIGHTCYAN, WHITE, LABEL, 0, 1},
            {350, 150, 100, 30, "0",            CYAN, LIGHTCYAN, WHITE, LABEL, 0, 2},
            {220, 180, 200, 30, "完成订单",     CYAN, LIGHTCYAN, WHITE, LABEL, 0, 3},
            {350, 180, 100, 30, "0",            CYAN, LIGHTCYAN, WHITE, LABEL, 0, 4},
            {220, 210, 200, 30, "驳回订单",     CYAN, LIGHTCYAN, WHITE, LABEL, 0, 5},
            {350, 210, 100, 30, "0",            CYAN, LIGHTCYAN, WHITE, LABEL, 0, 6},
            {300, 270, 120, 40, "返回",         LIGHTCYAN, CYAN, WHITE, BUTTON, 0, 7}
        }
    };

    // 把真实数字填进去
    sprintf(win.controls[2].text, "%d", total);
    sprintf(win.controls[4].text, "%d", completed);
    sprintf(win.controls[6].text, "%d", rejected);

    Background_display();
    window_show(win);
    win = window_run(win);

    if(win.current == 7) 
		return 16;   //analysis是16 
    return orderStatWin();
}

int storeStatWin()
{
    int inCnt = 0;
    int outCnt = 0;
    int stock = 0;

    LNode *cur = goodsList->next;
    while(cur != NULL)
    {
        GOODS_T *g = (GOODS_T*)cur->data;
        inCnt++;
        if(strlen(g->outTime) > 0) outCnt++;
        else stock += g->goodsNum;
        cur = cur->next;
    }

    WINDOW_T win = {
        200, 100, 500, 350, WHITE, 8,
        {
            {220, 120, 200, 30, "仓储统计",     CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
            {220, 150, 200, 30, "入库总量",     CYAN, LIGHTCYAN, WHITE, LABEL, 0, 1},
            {350, 150, 100, 30, "0",            CYAN, LIGHTCYAN, WHITE, LABEL, 0, 2},
            {220, 180, 200, 30, "出库总量",     CYAN, LIGHTCYAN, WHITE, LABEL, 0, 3},
            {350, 180, 100, 30, "0",            CYAN, LIGHTCYAN, WHITE, LABEL, 0, 4},
            {220, 210, 200, 30, "当前库存",     CYAN, LIGHTCYAN, WHITE, LABEL, 0, 5},
            {350, 210, 100, 30, "0",            CYAN, LIGHTCYAN, WHITE, LABEL, 0, 6},
            {300, 270, 120, 40, "返回",         LIGHTCYAN, CYAN, WHITE, BUTTON, 0, 7}
        }
    };

    sprintf(win.controls[2].text, "%d", inCnt);
    sprintf(win.controls[4].text, "%d", outCnt);
    sprintf(win.controls[6].text, "%d", stock);

    Background_display();
    window_show(win);
    win = window_run(win);

    if(win.current == 7) 
    {
    	return 16;
	}
    return storeStatWin();
} 
int exportReportWin()
{
    // 统计订单
    int totalOrder = 0, okOrder = 0, noOrder = 0;
    LNode *oCur = orderList->next;
    while(oCur)
    {
        ORDER_T *o = (ORDER_T*)oCur->data;
        totalOrder++;
        if(o->orderStatus == 6) okOrder++;
        if(o->orderStatus == 2) noOrder++;
        oCur = oCur->next;
    }

    // 统计仓储
    int inTotal = 0, outTotal = 0, stockTotal = 0;
    LNode *gCur = goodsList->next;
    while(gCur)
    {
        GOODS_T *g = (GOODS_T*)gCur->data;
        inTotal++;
        if(strlen(g->outTime) > 0) outTotal++;
        else stockTotal += g->goodsNum;
        gCur = gCur->next;
    }

    // 生成报表文件
    if(exports_fp)
    {
        fprintf(exports_fp, "===== 物流报表 =====\n");
        fprintf(exports_fp, "订单总数：%d\n", totalOrder);
        fprintf(exports_fp, "完成订单：%d\n", okOrder);
        fprintf(exports_fp, "驳回订单：%d\n", noOrder);
        fprintf(exports_fp, "入库总量：%d\n", inTotal);
        fprintf(exports_fp, "出库总量：%d\n", outTotal);
        fprintf(exports_fp, "当前库存：%d\n", stockTotal);
        fclose(exports_fp);
    }

    CONTROL_T tip = {245,300,200,80,"报表已生成",CYAN,LIGHTCYAN,WHITE,BUTTON,0};
    control_show(tip);
    Sleep(1500);
    return analysisWin();
}
