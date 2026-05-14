#ifndef DATA_H
#define DATA_H

#include <stdio.h>
#include "../public/list.h"
//用户结构体 
typedef struct user_t
{
    char ID[9];
    char name[10];
    char passwd[10];
    int role;   // 1.管理员 2.仓储员 3.调度员 4.客服
    int state;  // 0.不可用 1.可用
} USER_T;

//订单结构体
typedef struct ORDER_T
{
    char orderId[20];
    char userName[20];
    char goodsName[50];
    int num;
    int auditFlag;   //0待审核 1通过 2驳回
    char backMsg[50];
    struct ORDER_T *next;
}ORDER_T;


extern LNode* userList;
extern FILE* user_fp;

LNode* user_data_init(FILE* user_fp);

#endif
