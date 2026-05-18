#include <graphics.h>
#include <conio.h>
#include "../View/control.h" 
#include "string.h"  
#include <stdio.h>
#include "data.h"
#include "../public/file.h" 

int orderCreate()//单号生成 信息输入 7
{
    WINDOW_T orderwin={200,120,400,400,WHITE,6,{
        {220,140,180,40,"订单号",CYAN, LIGHTCYAN, WHITE ,EDIT,1,20},  //0
        {220,190,180,40,"下单人",CYAN, LIGHTCYAN, WHITE ,EDIT,0,20},   //1
        {220,240,180,40,"货物名称",CYAN, LIGHTCYAN, WHITE ,EDIT,0,30},  //2
        {220,290,180,40,"数量",CYAN, LIGHTCYAN, WHITE ,EDIT,0,10},  //3
        {220,340,180,40,"确认提交",LIGHTGREEN,GREEN,WHITE,BUTTON,0,0},   //4
        {220,390,180,40,"返回订单",LIGHTRED,RED,WHITE,BUTTON,0,0},   //5
    },0};

    Background_display();

    window_show(orderwin);
    orderwin = window_run(orderwin);

	if(orderwin.current == 4)
	{
	    ORDER_T *p = (ORDER_T *)malloc(sizeof(ORDER_T));
	    memset(p, 0, sizeof(ORDER_T));
	
	    strcpy(p->orderId, orderwin.controls[0].text);
	    strcpy(p->userName, orderwin.controls[1].text);
	    strcpy(p->goodsName, orderwin.controls[2].text);
	    sscanf(orderwin.controls[3].text, "%d", &p->num);
	    p->auditFlag = 0;
	    strcpy(p->backState, "待审核");
	    insertAtTail(orderList, p);
	    file_add(order_fp, sizeof(ORDER_T), p);
	    return 6;
	}
    if(orderwin.current == 5) 
	{
		return 6;
	}
    return 7;  
}

int orderAudit()//驳回 通过 8
{
    WINDOW_T orderwin={200,120,400,400,WHITE,5,{
        {220,140,180,40,"输入订单号",CYAN, LIGHTCYAN, WHITE ,EDIT,1,20},
        {220,190,180,40,"驳回备注",CYAN, LIGHTCYAN, WHITE ,EDIT,0,50},
        {220,260,180,40,"审核通过",CYAN, LIGHTCYAN, WHITE,BUTTON,0,0},
        {220,310,180,40,"驳回订单",CYAN, LIGHTCYAN, WHITE,BUTTON,0,0},
        {220,360,180,40,"返回",CYAN, LIGHTCYAN, WHITE,BUTTON,0,0},
    },0};

    Background_display();

    window_show(orderwin);
    orderwin = window_run(orderwin);
	if(orderwin.current == 2) //审核通过
	{
	    LNode* cur = orderList->next;
	    while(cur != NULL)
	    {
	        ORDER_T* o = (ORDER_T*)cur->data;
	        if(strcmp(o->orderId, orderwin.controls[0].text) == 0)
	        {
	            o->auditFlag = 1;
	            strcpy(o->backState, "审核通过");
	            break;
	        }
	        cur = cur->next;
	    }
	    list_write_file(order_fp, sizeof(ORDER_T), orderList);
	    return 6;
	}
	if(orderwin.current == 3) //驳回
	{
	    LNode* cur = orderList->next;
	    while(cur != NULL)
	    {
	        ORDER_T* o = (ORDER_T*)cur->data;
	        if(strcmp(o->orderId, orderwin.controls[0].text) == 0)
	        {
	            o->auditFlag = 2;
	            strcpy(o->backState, orderwin.controls[1].text);
	            break;
	        }
	        cur = cur->next;
	    }
	    list_write_file(order_fp, sizeof(ORDER_T), orderList);
	    return 6;
	}
}
      
int orderSerch()//订单查询 修改 订单查询包括:分页 精确 模糊 9
{
    static int pageNow = 1;
    char buf[30] = {0};
    LNode* tempList = initList();
    TABLE_T table;
    strcpy(table.text[0],"订单编号");
    strcpy(table.text[1],"下单用户");
    strcpy(table.text[2],"货物名称");
    strcpy(table.text[3],"审核状态");
    table.row = 5;
    table.col = 4;

    WINDOW_T orderwin={150,80,500,480,WHITE,5,{
        {170,100,200,40,"查询关键词",CYAN,LIGHTCYAN,WHITE,EDIT,1,30},
        {380,100,100,40,"模糊查询",CYAN,LIGHTCYAN,WHITE,BUTTON,0,0},
        {490,100,100,40,"精确查询",CYAN,LIGHTCYAN,WHITE,BUTTON,0,0},
        {170,420,120,40,"上一页",CYAN,LIGHTCYAN,WHITE,BUTTON,0,-1},
        {300,420,120,40,"下一页",CYAN,LIGHTCYAN,WHITE,BUTTON,0,-2},
    },0};

    Background_display();
    setbkmode(TRANSPARENT);

    //===== 核心逻辑 完全照抄你的用户查询 =====
    if(strlen(orderwin.controls[0].text)==0)
    {
        //全部查询
        int i=0,j=0;
        int count=getListNodeCount(orderList);//获取总订单数
        int pageCount=5;
        int pageNum=count%pageCount==0?count/pageCount:count/pageCount+1;
        int start=(pageNow-1)*pageCount;//计算当前页开始是第几个节点
        memset(table.data,0,sizeof(table.data));
        for(i=0;i<pageCount;i++)
        {
            if(start+i>=count)
            {
                break;
            }
            ORDER_T *p=(ORDER_T *)findNode(orderList, start+i);
            j=0;
            strcpy(table.data[i][j++], p->orderId);
            strcpy(table.data[i][j++], p->userName);
            strcpy(table.data[i][j++], p->goodsName);
            sprintf(table.data[i][j++],"%d",p->auditFlag);
        }
    }
    else
    {
        //模糊/精确查询
        int i=0,j=0;
        int pageCount=5;
        strcpy(buf,orderwin.controls[0].text);

        //清空临时链表
        if(tempList != NULL)
        {
            freeList(tempList);
        }
        tempList=initList();

        int allCount = getListNodeCount(orderList);
        for(int k=0;k<allCount;k++)
        {
            ORDER_T *t = (ORDER_T *)findNode(orderList, k);
            if(t == NULL)
                continue;
            //精确：完全匹配订单号 | 模糊：货物名包含关键词
            if(orderwin.current==1 ? strcmp(t->orderId, buf)==0 : strstr(t->goodsName, buf)!=NULL)
            {
                insertAtTail(tempList, t);
            }
        }

        int count = getListNodeCount(tempList);
        int pageNum = (count + pageCount - 1) / pageCount;
        int start = (pageNow - 1)*pageCount;
        memset(table.data,0,sizeof(table.data));
        for(i=0;i<pageCount;i++)
        {
            if(start+i >= count) break;
            ORDER_T *t = (ORDER_T *)findNode(tempList, start+i);
            j=0;
            strcpy(table.data[i][j++], t->orderId);
            strcpy(table.data[i][j++], t->userName);
            strcpy(table.data[i][j++], t->goodsName);
            sprintf(table.data[i][j++],"%d",t->auditFlag);
        }
    }

    table_show(table,pageNow,4);
    orderwin=window_run(orderwin);

    //向上翻页
    if(orderwin.current==-1)
    {
        if(pageNow > 1)
        {
            pageNow--;
        }
        else
        {
            //弹窗
            CONTROL_T miniWin={245,300,200,80,"已经是第一页",CYAN,LIGHTCYAN,WHITE,BUTTON,0,0};
            control_show(miniWin);
            Sleep(1500);
        }
        return 9;
    }
    //向下翻页
    else if(orderwin.current==-2)
    {
        int total = strlen(orderwin.controls[0].text)?getListNodeCount(tempList):getListNodeCount(orderList);
        int pageCount=5;
        int pageNum = (total + pageCount - 1) / pageCount;
        if(pageNow<pageNum)
        {
            pageNow++;
        }
        else
        {
            //弹窗
            CONTROL_T miniWin={245,300,200,80,"已经是最后一页",CYAN,LIGHTCYAN,WHITE,BUTTON,0,0};
            control_show(miniWin);
            Sleep(1500);
        }
        return 9;
    }
    //返回
    else
    {
        pageNow=1;
        return 6;
    }
}

int orderTracking()    //没思路   10
{
	
}

int orderWin()   //主窗口（形式展示）->分窗口（真正的功能实现） 
{
    WINDOW_T win={290,155,220,330,WHITE,5,{
        {300,160,200,40,"1.创建订单",LIGHTCYAN,CYAN,WHITE,BUTTON,1,0},  //0
        {300,200,200,40,"2.订单审核",LIGHTCYAN,CYAN,WHITE,BUTTON,0,0},  //1
        {300,240,200,40,"3.订单查询",LIGHTCYAN,CYAN,WHITE,BUTTON,0,0},  //2
        {300,280,200,40,"4.订单跟踪",LIGHTCYAN,CYAN,WHITE,BUTTON,0,0},  //3
        {300,320,200,40,"5.返回上级",LIGHTCYAN,CYAN,WHITE,BUTTON,0,0},  //4
    },0};
    
	Background_display();

    //必要的函数编译完成，再进行驱动 
    
    window_show(win);
    win = window_run(win);

    if(win.current == 0)
    {
        return 7;    //创建订单
    }
    else if(win.current== 1)
    { 
        return 8;    //审核订单 
    }
    else if(win.current == 2)
    {
        return 9;   //查询订单 
    }
    else if(win.current == 3)
    {
        return 10; //跟踪订单 
    }
    else if (win.current == 4)
    {
    	return 2;  //mianWin 
	}
}
