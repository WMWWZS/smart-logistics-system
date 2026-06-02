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
    sprintf(outId, "OR%04d%02d%02d%03d",
        tm->tm_year + 1900,
        tm->tm_mon + 1,
        tm->tm_mday,
        seq);
}

int createOrderWin()
{
    WINDOW_T win = {
        200, 30, 520, 600, CYAN, 22,
        {
            {220,  60, 120, 35, "客户姓名：",  CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
            {350,  60, 150, 35, "",           CYAN, LIGHTCYAN, WHITE, EDIT,  1, 20},
            {220, 110, 120, 35, "联系电话：", CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
            {350, 110, 150, 35, "",           CYAN, LIGHTCYAN, WHITE, EDIT,  0, 15},
            {220, 160, 120, 35, "收货地址：", CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
            {350, 160, 150, 35, "",           CYAN, LIGHTCYAN, WHITE, EDIT,  0, 60},
            {220, 210, 120, 35, "发货地址：", CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
            {350, 210, 150, 35, "",           CYAN, LIGHTCYAN, WHITE, EDIT,  0, 60},
            {220, 260, 120, 35, "货物名称：", CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
            {350, 260, 150, 35, "",           CYAN, LIGHTCYAN, WHITE, EDIT,  0, 20},
            {220, 310, 120, 35, "货物类型：", CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
            {350, 310, 150, 35, "",           CYAN, LIGHTCYAN, WHITE, EDIT,  0, 20},
            {220, 360, 120, 35, "重量：",      CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
            {350, 360, 150, 35, "",           CYAN, LIGHTCYAN, WHITE, EDIT,  0, 10},
            {220, 410, 120, 35, "数量：",      CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
            {350, 410, 150, 35, "",           CYAN, LIGHTCYAN, WHITE, EDIT,  0, 10},
            {220, 460, 120, 35, "体积：",      CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
            {350, 460, 150, 35, "",           CYAN, LIGHTCYAN, WHITE, EDIT,  0, 10},
            {220, 510, 120, 35, "期望送达：",  CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
            {350, 510, 150, 35, "",           CYAN, LIGHTCYAN, WHITE, EDIT,  0, 20},
            {230, 555, 120, 40, "确认创建",    CYAN, LIGHTCYAN, WHITE, BUTTON, 0, 0},
            {370, 555, 120, 40, "返回",        CYAN, LIGHTCYAN, WHITE, BUTTON, 0, 1},
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
		fflush(order_fp);
        insertAtTail(orderList, ord);
    	return 7;
	}
	else if(win.current == 21)
	{
		return 6;
	}
}

int checkOrderWin()
{
    WINDOW_T win = {200,100,500,400,CYAN,7,{
        {220,120,150,40,"输入待审核订单号",CYAN, LIGHTCYAN,WHITE,LABEL,0,0},
        {220,170,200,40,"",CYAN,LIGHTCYAN,WHITE,EDIT,1,25},
        {220,240,120,40,"通过",CYAN, LIGHTCYAN,WHITE,BUTTON,0,0},
        {360,240,120,40,"驳回",CYAN, LIGHTCYAN,WHITE,BUTTON,0,1},
        {220,300,200,40,"驳回原因",CYAN, LIGHTCYAN,WHITE,LABEL,0,0},
        {220,350,200,40,"",CYAN,LIGHTCYAN,WHITE,EDIT,0,60},
        {220,400,120,40,"返回",CYAN, LIGHTCYAN,WHITE,BUTTON,0,2},
    }};

    Background_display();
    window_show(win);
    win = window_run(win);

    if(win.current == 6) return 6;

    char oid[25] = {0};
    strcpy(oid, win.controls[1].text);

    LNode* cur = orderList->next;
    int index = 0;
    while(cur)
    {
        ORDER_T* p = (ORDER_T*)cur->data;
        if(strcmp(p->orderId, oid)==0 && p->orderStatus==0)
        {
            if(win.current == 2) p->orderStatus = 1;
            if(win.current == 3)
            {
                p->orderStatus = 2;
                strcpy(p->rejectReason, win.controls[5].text);
            }
            file_upDate(order_fp, sizeof(ORDER_T), p, index * sizeof(ORDER_T));
            CONTROL_T succWin = {245, 300, 200, 80, "审核成功", CYAN, LIGHTCYAN,  WHITE, BUTTON, 0};
            control_show(succWin);
            Sleep(1500);
            return 6;
        }
        cur = cur->next;
        index++;
    }
    CONTROL_T errWin = {245, 300, 200, 80, "订单不存在或已审核",LIGHTCYAN, CYAN,  WHITE, BUTTON, 0};
    control_show(errWin);
    Sleep(1500);
    return 6;
}

//订单修改功能
int modifyOrderWin()
{
    //     第一步：输入订单号
    WINDOW_T win1 = {200,100,500,300,CYAN,4,{
        {220,120,150,40,"输入订单号",CYAN, LIGHTCYAN,WHITE,LABEL,0,0},
        {220,170,200,40,"",CYAN,LIGHTCYAN,WHITE,EDIT,1,25},
        {220,230,120,40,"查找",CYAN, LIGHTCYAN,WHITE,BUTTON,0,0},
        {360,230,120,40,"返回",CYAN, LIGHTCYAN,WHITE,BUTTON,0,1},
    }};

    Background_display();
    window_show(win1);
    win1 = window_run(win1);

    if(win1.current == 3) return 6;  //         返回

    //      查找订单
    char oid[25] = {0};
    strcpy(oid, win1.controls[1].text);

    ORDER_T* target = NULL;
    int targetIndex = 0;
    LNode* cur = orderList->next;
    int idx = 0;
    while(cur)
    {
        ORDER_T* p = (ORDER_T*)cur->data;
        if(strcmp(p->orderId, oid) == 0)
        {
            target = p;
            targetIndex = idx;
            break;
        }
        cur = cur->next;
        idx++;
    }

    if(target == NULL)
    {
        CONTROL_T errWin = {245,300,200,80,"订单不存在",CYAN, LIGHTCYAN,WHITE,BUTTON,0};
        control_show(errWin);
        Sleep(1500);
        return modifyOrderWin();
    }

    //根据状态判断可修改内容
    if(target->orderStatus == 2)  //已驳回
    {
        CONTROL_T errWin = {245,300,200,80,"已驳回订单不可修改",CYAN, LIGHTCYAN,WHITE,BUTTON,0};
        control_show(errWin);
        Sleep(1500);
        return 6;
    }


    int canEditAll = (target->orderStatus == 0);

    WINDOW_T win2 = {200,30,520,600,CYAN,22,{
        {220,  60, 120, 35, "订单号：",  CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
        {350,  60, 150, 35, "",          CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},  //显示订单号
        {220, 110, 120, 35, "客户姓名：", CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
        {350, 110, 150, 35, "",          CYAN, LIGHTCYAN, WHITE, EDIT, 0, 20},
        {220, 160, 120, 35, "联系电话：", CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
        {350, 160, 150, 35, "",          CYAN, LIGHTCYAN, WHITE, EDIT, 1, 15},  //电话始终可改
        {220, 210, 120, 35, "收货地址：", CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
        {350, 210, 150, 35, "",          CYAN, LIGHTCYAN, WHITE, EDIT, 0, 60},
        {220, 260, 120, 35, "货物名称：", CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
        {350, 260, 150, 35, "",          CYAN, LIGHTCYAN, WHITE, EDIT, 0, 20},
        {220, 310, 120, 35, "货物类型：", CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
        {350, 310, 150, 35, "",          CYAN, LIGHTCYAN, WHITE, EDIT, 0, 20},
        {220, 360, 120, 35, "重量：",     CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
        {350, 360, 150, 35, "",          CYAN, LIGHTCYAN, WHITE, EDIT, 0, 10},
        {220, 410, 120, 35, "数量：",     CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
        {350, 410, 150, 35, "",          CYAN, LIGHTCYAN, WHITE, EDIT, 0, 10},
        {220, 460, 120, 35, "体积：",     CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
        {350, 460, 150, 35, "",          CYAN, LIGHTCYAN, WHITE, EDIT, 0, 10},
        {220, 510, 120, 35, "期望送达：", CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
        {350, 510, 150, 35, "",          CYAN, LIGHTCYAN, WHITE, EDIT, 0, 20},
        {230, 555, 120, 40, "确认修改",   LIGHTCYAN,CYAN, WHITE, BUTTON, 0, 0},
        {370, 555, 120, 40, "返回",       LIGHTCYAN,CYAN, WHITE, BUTTON, 0, 1},
    }};

    // 填充现有数据
    strcpy(win2.controls[1].text, target->orderId);
    strcpy(win2.controls[3].text, target->cusName);
    strcpy(win2.controls[5].text, target->cusPhone);
    strcpy(win2.controls[7].text, target->cusAddr);
    strcpy(win2.controls[9].text, target->goodsName);
    strcpy(win2.controls[11].text, target->goodsType);
    sprintf(win2.controls[13].text, "%d", target->goodsWeight);
    sprintf(win2.controls[15].text, "%d", target->goodsNum);
    sprintf(win2.controls[17].text, "%d", target->goodsVolume);
    strcpy(win2.controls[19].text, target->expectTime);

    Background_display();
    window_show(win2);
    win2 = window_run(win2);

    if(win2.current == 21) return 6;  // 返回

    if(win2.current == 20)  //确认修改
    {
        //更新数据
        if(canEditAll)
        {
            strcpy(target->cusName, win2.controls[3].text);
            strcpy(target->cusAddr, win2.controls[7].text);
            strcpy(target->goodsName, win2.controls[9].text);
            strcpy(target->goodsType, win2.controls[11].text);
            sscanf(win2.controls[13].text, "%d", &target->goodsWeight);
            sscanf(win2.controls[15].text, "%d", &target->goodsNum);
            sscanf(win2.controls[17].text, "%d", &target->goodsVolume);
            strcpy(target->expectTime, win2.controls[19].text);
        }
    //   电话始终可改
        strcpy(target->cusPhone, win2.controls[5].text);

        //     更新文件
        file_upDate(order_fp, sizeof(ORDER_T), target, targetIndex * sizeof(ORDER_T));

        CONTROL_T succWin = {245,300,200,80,"修改成功",LIGHTCYAN,CYAN,WHITE,BUTTON,0};
        control_show(succWin);
        Sleep(1500);
        return 6;
    }
    return 6;
}

int orderSearchWin()
{
    static int pageNow = 1;
    int pageNum;
    int pageCount=5;   //这里可以操纵每页显示数据个数 
    int count=0;
    static char buf2[100]={0};
    static LNode* tempList=NULL;
    ORDER_T* p;
    int allCount;

    WINDOW_T win = {
        0, 100, 850, 450, WHITE, 4,
        {
            {50, 120, 100, 40, "搜索：", LIGHTCYAN, CYAN, WHITE, LABEL, 0, 0},
            {160, 120, 200, 40, "", CYAN, LIGHTCYAN, WHITE, EDIT, 0, 40},
            {380, 120, 100, 40, "搜索", LIGHTCYAN, CYAN, WHITE, BUTTON, 0, 0},
            {700, 120, 100, 40, "返回", LIGHTCYAN, CYAN, WHITE, BUTTON, 0, 1},
        }
    };


    TABLE_T table = {
        1, 180, 810, 280,
        6, 9,
        {"订单号", "客户姓名", "电话", "货物名", "重量", "数量", "状态", "期望时间", "驳回原因"}
    };
	memset(&table.data, 0, sizeof(table.data));

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
		    if(p == NULL) continue;
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
    else
    {
        int i=0, j=0;
        count = getListNodeCount(tempList);
        pageNum = (count + pageCount - 1) / pageCount;
        int start = (pageNow - 1) * pageCount;

		memset(table.data, 0, sizeof(table.data));
		for(i=0; i<pageCount; i++)
		{
		    if(start + i >= count) break;
		    ORDER_T *t = (ORDER_T *)findNode(tempList, start + i);
		    if(t == NULL) continue;
		    j = 0;
		    strcpy(table.data[i][j++], t->orderId);
		    strcpy(table.data[i][j++], t->cusName);
		    strcpy(table.data[i][j++],t->cusPhone);
		    strcpy(table.data[i][j++],t->goodsName);
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

    if(win.current == 2)
    {
        if(strlen(win.controls[1].text) > 0)
        {
            strcpy(buf2, win.controls[1].text);
            if(tempList != NULL) 
			{
				freeList(tempList); tempList = NULL; 
			}
            tempList=initList();
			allCount = getListNodeCount(orderList);
			for(int k=0; k<allCount; k++)
			{
			    ORDER_T *t = (ORDER_T *)findNode(orderList, k);
			    if(t == NULL) continue;
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
            pageNow=1;
        }
        else 
		{ 
			memset(buf2,0,sizeof(buf2)); pageNow=1; 
		}
        return orderSearchWin();
    }
    else if(win.current == -1)
    {
        if(pageNow > 1) pageNow--;
        else 
		{ 
			CONTROL_T miniWin={245,300,200,80,"已经是第一页",LIGHTCYAN,CYAN,WHITE,BUTTON,0}; 
			control_show(miniWin); Sleep(1500); 
		}
        return orderSearchWin();
    }
    else if(win.current == -2)
    {
        if(pageNow < pageNum) pageNow++;
        else 
		{ 
			CONTROL_T miniWin={245,300,200,80,"已经是最后一页",LIGHTCYAN,CYAN,WHITE,BUTTON,0}; 
			control_show(miniWin); Sleep(1500); 
		}
        return orderSearchWin();
    }
    else if(win.current == 3)
    {
        if(tempList != NULL) 
		{
			freeList(tempList); tempList = NULL; 
		}
        memset(buf2,0,sizeof(buf2));
        pageNow=1;
        return 6;
    }
    return orderSearchWin();
}

int orderWin()
{
    WINDOW_T win={290,155,220,370,WHITE,5,{
        {300,160,200,40,"1.创建订单",LIGHTCYAN,CYAN,WHITE,BUTTON,0,0},
        {300,200,200,40,"2.订单审核",LIGHTCYAN,CYAN,WHITE,BUTTON,0,0},
        {300,240,200,40,"3.订单查询",LIGHTCYAN,CYAN,WHITE,BUTTON,0,0},
        {300,280,200,40,"4.订单修改",LIGHTCYAN,CYAN,WHITE,BUTTON,0,0}, 
        {300,320,200,40,"5.返回上级",LIGHTCYAN,CYAN,WHITE,BUTTON,0,0},
    },0};

	Background_display();
    window_show(win);
    win = window_run(win);

    if(win.current == 0) 
	return 7;         //创建订单
    else if(win.current == 1) 
	return 8;     //审核订单
    else if(win.current == 2) 
	return 9;          //查询订单
    else if(win.current == 3) 
	return 23;              //返回上级
	else if(win.current == 4) 
	return 2;      //返回上级
}
