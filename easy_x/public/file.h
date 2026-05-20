#ifndef _FILE_H_  //头文件保护 
#define _FILE_H_
#include <stdio.h>
#include "list.h"
#include "../App/data.h"
/*函数名：file_open 
函数功能：打开指定文件并获取文件指针 
参数：fp：文件路径 
返回值：返回文件指针
*/ 
FILE* file_open(const char* fileName); 

/*函数名：file_write
函数功能：读文件写入相应的数组中
参数：fp：文件指针
	size：写入的字节数（结构体数组de） 
	head：结构体数组首地址
	count：写入几次 
返回值：返回文件指针
*/ 
void file_write(FILE* fp,int size,void* head,int count) ;

/*函数名：file_getSize
函数功能：注册后更新文件内容 
参数：fp：文件指针
	size：写入的字节数（结构体数组de） 
	head：结构体数组首地址
	count：写入几次 
返回值：返回文件指针
*/ 
int	file_getSize(FILE* fp); 

/*函数名：file_read
函数功能：读取文件用户数据 
参数：fp：文件指针
	size：写入的字节数（结构体数组de） 
	head：结构体数组首地址
	count：写入几次 
返回值：文件指针
*/ 

void file_add(FILE* fp,int size,void* data); 
/*函数名：file_updata
函数功能：指定文件位置修改数据 
参数：fp：文件指针
	size：写入的字节数（结构体数组de） 
	head：结构体数组首地址
	index：结构体的索引 
返回值：无 
*/ 
int file_user_read(FILE* fp,int size,void* userList) ;

/*函数名：file_updata
函数功能：读取文件货物数据 
参数：fp：文件指针
	size：数据大小 
	data：数据地址 
	index：文件偏移位置 
返回值：文件指针
*/ 
void file_read_list(FILE*fp,int size,void* head);

//int DSL_file_read(FILE* fp,int size,void* List) ;

//void DSL_write_list(FILE* fp,int size,void* head) ;

void list_write_file(FILE* fp,int size,LNode* head);

LNode* order_data_init(FILE* fp); 

void order_add(ORDER_T order); 




#endif 
