#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "../App/data.h"

FILE* file_open(const char* fileName)
	{
		FILE* fp; 
		fp = fopen(fileName,"rb+") ;  //注意+r和r+ 
		if (fp == NULL)
		{
			perror("文件打开失败");
			fp = fopen(fileName,"wb+") ; //文件不存在就创建 
		} 
		return fp;
	} 
	
int	file_getSize(FILE* fp)
{
	fseek(fp,0,SEEK_END);
	return ftell(fp); 
}

void file_write(FILE* fp,int size,void* head,int g_count) 
{
	int i=0;
	char* p= (char*)head; 
	rewind(fp);//重置文件指针偏移量
	for(i=0;i<g_count;i++) 
	{
		fwrite(p,size,1,fp);
		p=p+size;
	}
}

//int file_read(FILE* fp,int size,void* head) 
//{
//	char *p=head;
//	int count=0;
//	rewind(fp);//重置文件指针 
//	while((fread(p,size,1,fp))>0)      //fread的返回值是数据单元个数 ，而不是字节 ，从 fp 指向的文件中，
//    {
//    	p=p+size;              // 1个单元size字节大小，要读一个1个size字节大小的单元             
//    	count++;
//	}			//读取 1 个大小为 size 字节的数据单元，并把这个单元的数据写入到 ptr 指向的内存地址中 
//	return count; 
//} 

/*
fread 接收内存缓冲区指针ptr、单个数据单元大小size、
读取单元个数count、文件指针stream四个参数，
核心效果是从stream指向的文件中读取最多count个大小为size的二进制数据单元，
存入ptr指向的内存缓冲区，并返回实际成功读取的单元个数
*/ 
//int DSL_file_read(FILE* fp,int size,void* List) 
//{
//	void* tmp;
//	int i=0;
//	rewind(fp);
//	tmp=malloc(size) ;
//	while(fread(tmp, size, 1, fp) > 0 ) 
//	{
//		InserDSL(List,i,tmp,size);
//		i++; 
//	} 
//	return i;
//	free(tmp);
//}


void file_add(FILE* fp,int size,void* data)
{
	if(fp!=NULL)
	{
		fseek(fp,0,SEEK_END);
		fwrite(data,size,1,fp) ;
	} 
} 


void file_upDate(FILE *fp, int size, void *data, int index) 
{
    // 1. 参数合法性检查
    if (fp == NULL || data == NULL || size <= 0) 
	{
        return;
    }

    fseek(fp, index, SEEK_SET);
    fwrite(data, 1, size, fp);
    fflush(fp);
}

void file_read_list(FILE* fp, int size, void* head)
{
    rewind(fp); // 文件指针回到开头
    while (1)
    {
        // 每次读取都新建节点内存
        void* data = malloc(size);
        if (fread(data, size, 1, fp) != 1)
        {
            free(data);
            break;
        }
        insertAtTail((LNode*)head, data);
    }
}

void list_write_file(FILE* fp,int size,LNode* head) 
{
	LNode* p=head;
	rewind(fp);
	while(p->next!=NULL)
	{
		p=p->next;
		fwrite(p->data,size,1,fp);
		fflush(fp);
	}
}

void dsl_write_list(FILE* fp,int size,LNode* head) 
{
	LNode* p=head;
	rewind(fp);
	while(p->next!=NULL)
	{
		p=p->next;
		fwrite(p->data,size,1,fp);
		fflush(fp);
	}
}



