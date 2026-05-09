#ifndef DATA_H
#define DATA_H

#include <stdio.h>
#include "../public/list.h"

typedef struct user_t
{
    char ID[9];
    char name[10];
    char passwd[10];
    int role;   // 1.管理员 2.仓储员 3.调度员 4.客服
    int state;  // 0.不可用 1.可用
} USER_T;

extern LNode* userList;
extern FILE* user_fp;

LNode* user_data_init(FILE* user_fp);

#endif
