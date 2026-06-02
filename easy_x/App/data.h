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

// 订单状态：0待审核 1待出库 2已驳回 3运输中 4已送达 5已完成
typedef struct 
{
    char orderId[25];       //OR+年月日+6位序号
    char cusName[20];       //客户姓名
    char cusPhone[15];      //联系电话
    char cusAddr[60];       //收货地址
    char sendAddr[60];      //发货地址
    char goodsName[20];     //货物名称
    char goodsType[20];     //货物类型
    int goodsWeight;      //重量
    int goodsNum;           //数量
    int goodsVolume;      //体积
    char expectTime[20];    // 期望送达
    int orderStatus;        // 订单状态
    char rejectReason[60];  // 驳回原因
    char trackInfo[200];    // 跟踪信息
} ORDER_T;      

// 货物信息结构体
typedef struct {
    char goodsId[20];      
    char orderId[25];      //关联的订单号
    char goodsName[20];    //货物名称
    char goodsType[20];   //货物类型
    float goodsWeight;     //重量
    int goodsNum;          //数量
    char storageLoc[10];   //货位编号（如A01、B02）
    char inTime[20];       //入库时间
    char outTime[20];      //出库时间
    char handler[20];      //经办人
} GOODS_T;

// 统计结果结构体
typedef struct {
    int total;           //总订单
    int audit;           //待审核
    int pass;            //已通过
    int reject;          //已驳回
    int out;             //待出库
    int trans;           //运输中
    int arrive;          //已送达
    int complete;        //已完成
    int weightSum;       //总重量（用于简单统计）
    int typeCount[5];    //假设最多5种货物类型，记录每种类型订单数
} OrderStat;

// 全局链表（放到你的全局变量区）
extern FILE* exports_fp; 
extern FILE* goods_fp;
extern FILE* order_fp;
extern FILE* user_fp;
extern LNode* goodsList;
extern LNode* userList;
extern LNode* orderList;
LNode* user_data_init(FILE* user_fp);


#endif
