#include "stdio.h"
#include "stdlib.h" 
#include "list.h" 
#include "../App/data.h" 
LNode* initList()
{
	LNode* head=(LNode*)malloc(sizeof(LNode));
	if(head==NULL)
	{
		printf("空间申请失败！");
		exit(1); 
	}
	head->next=NULL;
	head->data=NULL;
	return head;
}
LNode* createNode(void* data)
{
	LNode* newNode=(LNode*)malloc(sizeof(LNode));
	if(newNode==NULL)
	{
		printf("空间申请失败！");
		exit(1); 
	}
	newNode->data=data;
	newNode->next=NULL;
	return newNode; 
}
void insertAtTail(LNode* head, void* data)  //node //p 
{
	LNode* p=head;    
	if(p==NULL)
	{
		printf("链表为空！");
		exit(1); 
	}
	while(p->next!=NULL)
	{
		p=p->next;
	}
	LNode* newNode=createNode(data) ;
	p->next=newNode;
}
void insertAtPosition(LNode* head, void* data, int position)
{
	LNode* p=head;
	LNode* newNode=createNode(data);
	int i=0;
	if(position<0)
	{
		printf("位置不合法！");
	}
	while(p->next!=NULL && i<position)
	{
		p=p->next;
		i++;
	}
	
	if(i==position)
	{
		newNode->next=p->next;
		p->next=newNode;
	}
}
void deleteNode(LNode* head, int position)
{
	LNode* p=head;
	LNode* q=head->next;
	if(position<0)
	{
		printf("位置不合法！");
	}
	int i=0;
	while(p->next!=NULL)
	{
		p=p->next;
		q=q->next;
		i++;
		if(i==position)
		{
			p->next=q->next;
			free(q->next);
			free(q);
			break;
		}
	}
}
void* findNode(LNode* head, int position)   //从0开始 
{
	LNode* p=head->next;
	int i=0;
	while(p!=NULL)
	{
		if(i==position)
		{
			return p->data;
		}
		p = p->next;
		i++;
	}
	return NULL;
}
void freeList(LNode* head)
{
    LNode* p = head;
    while(p != NULL)
    {
        LNode* tmp = p;
        p = p->next;
        free(tmp->data);
        free(tmp);
    }
}
int getListNodeCount(LNode* head)
{
	if(head==NULL)
	{
		printf("链表为空！1111"); 
		return 0; 
	}
	LNode* p=head->next;
	int count=0;
	while(p!=NULL)
	{
		count++;
		p=p->next;
	} 
	return count; 
}

void freeOrList(LNode* head)
{
    LNode* p = head;
    while (p != NULL) {
        LNode* next = p->next;
        ORDER_T* data = (ORDER_T*)p->data;
        if (data != NULL) {
            free(data->orderId);
            free(data->cusName);
            free(data->cusPhone);
            free(data->goodsName);
            free(data->expectTime);
            free(data->rejectReason);
            free(data);
        }
        free(p);
        p = next;
    }	
} 
//int printList(LNode* head,void (*fun)(void* p)) 
//{
//	LNode* p=head->next;
//	int count=0; 
//	while(p!=NULL)
//	{
//		fun(p->data);
//		p=p->next; 
//	}
//	return count;
//}
