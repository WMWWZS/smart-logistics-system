#include "data.h"
#include "../public/list.h"
#include "../View/control.h"
#include <string.h>
#include <windows.h>
#include <time.h> 
//
//int orderStatWin()
//{
//    WINDOW_T win = {
//        200, 100, 500, 400, WHITE, 3,
//        {
//            {220, 120, 200, 40, "1.按时间统计", CYAN, LIGHTCYAN, WHITE, BUTTON, 0, 0},
//            {220, 180, 200, 40, "2.按货物类型统计", CYAN, LIGHTCYAN, WHITE, BUTTON, 0, 1},
//            {220, 240, 200, 40, "3.返回", CYAN, LIGHTCYAN, WHITE, BUTTON, 0, 2},
//        }
//    };
//
//    Background_display();
//    window_show(win);
//    win = window_run(win);
//
//    if(win.current == 2) 
//    {
//    	
//	}
//
//    // 按时间统计
//    if(win.current == 0)
//    {
//        int choice;
//        WINDOW_T rangeWin = {
//            250, 150, 400, 300, WHITE, 3,
//            {
//                {270, 170, 150, 40, "1.今日", CYAN, LIGHTCYAN, WHITE, BUTTON, 0, 0},
//                {270, 220, 150, 40, "2.本周", CYAN, LIGHTCYAN, WHITE, BUTTON, 0, 1},
//                {270, 270, 150, 40, "3.本月", CYAN, LIGHTCYAN, WHITE, BUTTON, 0, 2},
//            }
//        };
//        Background_display();
//        window_show(rangeWin);
//        rangeWin = window_run(rangeWin);
//        choice = rangeWin.current;
//
//        int total=0, completed=0, rejected=0;
//        LNode* cur = orderList->next;
//        while(cur != NULL)
//        {
//            ORDER_T* ord = (ORDER_T*)cur->data;
//            total++;
//            if(ord->orderStatus == 6) completed++;
//            if(ord->orderStatus == 2) rejected++;
//            cur = cur->next;
//        }
//
//        float completionRate = total > 0 ? (float)completed/total*100 : 0;
//        float rejectionRate = total > 0 ? (float)rejected/total*100 : 0;
//
//        char info[500];
//        sprintf(info,
//            "订单总数：%d\n"
//            "完成订单：%d\n"
//            "驳回订单：%d\n"
//            "完成率：%.2f%%\n"
//            "驳回率：%.2f%%",
//            total, completed, rejected, completionRate, rejectionRate);
//
//        WINDOW_T resWin = {200, 100, 500, 350, WHITE, 2,
//        {
//            {220, 150, 250, 150, info, CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
//            {300, 330, 120, 40, "返回", CYAN, LIGHTCYAN, WHITE, BUTTON, 0, 1},
//        }};
//        Background_display();
//        window_show(resWin);
//        resWin = window_run(resWin);
//        return orderStatWin();
//    }
//
//    // 按货物类型统计
//    else if(win.current == 1)
//    {
//        int typeA=0, typeB=0, typeC=0;
//        LNode* cur = orderList->next;
//        while(cur != NULL)
//        {
//            ORDER_T* ord = (ORDER_T*)cur->data;
//            if(strcmp(ord->goodsType, "A类") == 0) typeA++;
//            else if(strcmp(ord->goodsType, "B类") == 0) typeB++;
//            else typeC++;
//            cur = cur->next;
//        }
//
//        char info[300];
//        sprintf(info, "A类订单：%d\nB类订单：%d\n其他订单：%d", typeA, typeB, typeC);
//        WINDOW_T resWin = {200, 100, 400, 300, WHITE, 2,
//        {
//            {220, 150, 200, 100, info, CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
//            {300, 280, 120, 40, "返回", CYAN, LIGHTCYAN, WHITE, BUTTON, 0, 1},
//        }};
//        Background_display();
//        window_show(resWin);
//        resWin = window_run(resWin);
//        return orderStatWin();
//    }
//    return orderStatWin();
//}
//
int analysisWin()
{
	
}
//{
//    WINDOW_T win = {
//        0, 100, 500, 400, WHITE, 5,
//        {
//            {220, 120, 200, 40, "1.订单统计", CYAN, LIGHTCYAN, WHITE, BUTTON, 0, 0},
//            {220, 180, 200, 40, "2.仓储统计", CYAN, LIGHTCYAN, WHITE, BUTTON, 0, 1},
//            {220, 240, 200, 40, "3.运输统计", CYAN, LIGHTCYAN, WHITE, BUTTON, 0, 2},
//            {220, 300, 200, 40, "4.生成报表", CYAN, LIGHTCYAN, WHITE, BUTTON, 0, 3},
//            {220, 360, 200, 40, "5.返回", CYAN, LIGHTCYAN, WHITE, BUTTON, 0, 4},
//        }
//    };
//
//    Background_display();
//    window_show(win);
//    win = window_run(win);
//
//    if(win.current == 0) 
//		return orderStatWin();
//    else if(win.current == 1) 
//		return storageStatWin();
//    else if(win.current == 2)
//		return transStatWin();
//    else if(win.current == 3) 
//		return exportReportWin();
//    else if(win.current == 4) 
//		return 2;
//    return analysisWin();
//}
