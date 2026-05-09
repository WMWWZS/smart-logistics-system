#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include "../public/file.h" 
#include "../public/list.h"
#include "data.h" 
LNode* user_data_init(FILE* user_fp)
{
	//1.创建链表 
	userList = initList();
	//2.判断文件是否为空 
	if(file_getSize(user_fp) == 0) 
	{
		//3.对用户结构体的处理 
		USER_T* p;
		p = (USER_T*)malloc(sizeof(USER_T));
		memset(p, 0, sizeof(USER_T)) ;
		//如果p->ID = "1001"; "1001"是存在于只读数据段，后续修改即崩溃，所以用strcpy或者sprintf效果更好，strcpy它还会添'\0'
		sprintf(p->ID,"%d",1001 + getListNodeCount(userList)) ;  
		strcpy(p->name, "admin") ;
		strcpy(p->passwd, "123") ;
		p->role = 1;
		p->state = 1;    
		insertAtTail(userList, p); //添加进链表 
		list_write_file(user_fp,sizeof(USER_T),userList); //写入文件 
	}
	return userList; 
}






















