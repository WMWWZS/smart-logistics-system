#include <conio.h> 
#include <graphics.h> 
#include "../View/control.h" 
#include <stdio.h> 
#include "../public/file.h"
#include "../public/list.h"
#include "../App/data.h"

int adminWin()
{
	WINDOW_T win={290,155,220,330,WHITE,8,{
	{300,160,200,40,"1、创建用户",CYAN, LIGHTCYAN, WHITE,BUTTON,1,0},//0
	{300,200,200,40,"2、用户查询",CYAN, LIGHTCYAN, WHITE,BUTTON,0,0},//1
	{300,240,200,40,"3、密码重置",CYAN, LIGHTCYAN, WHITE,BUTTON,0,0}, //2
	{300,280,200,40,"4、角色管理",CYAN, LIGHTCYAN, WHITE,BUTTON,0,0}, //3
	{300,320,200,40,"5、仓库配置",CYAN, LIGHTCYAN, WHITE,BUTTON,0,0}, //4
	{300,360,200,40,"6、路线配置",CYAN, LIGHTCYAN, WHITE,BUTTON,0,0}, //5
	{300,400,200,40,"7、数据备份",CYAN, LIGHTCYAN, WHITE,BUTTON,0,0}, //6
	{300,440,200,40,"8、返回上级",CYAN, LIGHTCYAN, WHITE,BUTTON,0,0}, //7
	}};
	IMAGE img;
	loadimage(&img, "./imge/LMS.jpg",800,600);
	putimage(0, 0, &img);  
	setbkmode(TRANSPARENT);
	settextcolor(CYAN);
	outtextxy(200,530,"操作说明：上下键移动切换菜单，按下回车键选择菜单");
	window_show(win);
	win=window_run(win);
	printf("当前%d\n",win.current) ;
	if(win.current==0)
	{
	    return 4;
	}
	else if(win.current==7) 
	{
	    return 2;
	}
	else if(win.current==1) 
	{
		return 5; 
	}
}


int addUserWin()
{
    WINDOW_T addUserWin={240,240,290,230,WHITE,8,{
        {245,250,80,50,"用户名：",CYAN, LIGHTCYAN, WHITE,LABEL,0,0},  //0
        {245,305,80,50,"密  码：",CYAN, LIGHTCYAN, WHITE,LABEL,0,0},//1
        {245,360,80,50,"角  色：",CYAN, LIGHTCYAN, WHITE,LABEL,0,0},//2
        {320,250,200,50,"",CYAN,LIGHTCYAN,WHITE,EDIT,1,8},//3
        {320,305,200,50,"",CYAN,LIGHTCYAN,WHITE,EDIT_PWD,0,12},//4
        {320,360,200,50,"请选择：管理员,仓储员,调度员,客服",CYAN,LIGHTCYAN,WHITE,SELECT,0,0},//5
        {245,415,130,50,"创建",CYAN,LIGHTCYAN,WHITE,BUTTON,0,0},//6
        {390,415,130,50,"返回",CYAN,LIGHTCYAN,WHITE,BUTTON,0,0},//7
    }};
	IMAGE img;
	loadimage(&img, "./imge/LMS.jpg",800,600);
	putimage(0, 0, &img);  
	setbkmode(TRANSPARENT);
	settextcolor(CYAN);
	outtextxy(200,530,"操作说明：上下键移动切换菜单，按下回车键选择菜单");
	window_show(addUserWin);
	addUserWin=window_run(addUserWin);
	if(addUserWin.current==6)
	{
	    char newName[20];  //lin时 
	    strcpy(newName, addUserWin.controls[3].text);
	
	    // 2.遍历所有用户，检测是否重名
	    int isRepeat = 0;
	    for(int i=0;i<getListNodeCount(userList);i++)
	    {
	        USER_T *t = (USER_T*)findNode(userList,i);
	        if(strcmp(t->name, newName) == 0)
	        {
	            isRepeat = 1;
	            break;
	        }
	    }
	    
		//重名 
	    if(isRepeat == 1)
	    {
	        bground();
	        CONTROL_T tip={245,300,220,70,"用户名已存在，无法创建",CYAN,LIGHTCYAN,WHITE,BUTTON,0,0};
	        control_show(tip);
	        Sleep(1500);
	        return 3;
	    }
	
	    // 4. 不重名，正常创建用户
	    USER_T *p = (USER_T *)malloc(sizeof(USER_T));
	    memset(p, 0, sizeof(USER_T));
	
	    // ID自动生成 1001+count
	    sprintf(p->ID, "%d", 1001 + getListNodeCount(userList));
	    strcpy(p->name, addUserWin.controls[3].text);
	    strcpy(p->passwd, addUserWin.controls[4].text);
	    p->state = 1; // 账号默认可用
	
	    if(strcmp(addUserWin.controls[5].text,"管理员")==0)
	    {
	        p->role=1;
	    }
	    else if(strcmp(addUserWin.controls[5].text,"仓储员")==0)
	    {
	        p->role=2;
	    }
	    else if(strcmp(addUserWin.controls[5].text,"调度员")==0)
	    {
	        p->role=3;
	    }
	    else if(strcmp(addUserWin.controls[5].text,"客服")==0)
	    {
	        p->role=4;
	    }
	
	    insertAtTail(userList, p); // 添加结点
	    file_add(user_fp,sizeof(USER_T),p);
	
	    CONTROL_T miniWin={245, 300, 200, 80, "创建用户成功", CYAN, LIGHTCYAN, WHITE, BUTTON, 0,0};
	    control_show(miniWin);
	    Sleep(1500);
	    return 3;
	}
	else if(addUserWin.current==7)
	{
	    return 3;
	}
}

int selectUserWin()
{
	WINDOW_T selectUserWin={200,200,450,250,WHITE,3,{
	    {205,205,120,50,"用户名搜索：",WHITE,WHITE,CYAN,LABEL,0,0},    //0
	    {325,205,160,50,"",CYAN,LIGHTCYAN,WHITE,EDIT,1,20},            //1 最大长度20
	    {490,205,130,50,"查询",CYAN,LIGHTCYAN,WHITE,BUTTON,0,0},       //2
	}};
	window_show(selectUserWin);
	
	//加载数据到表格
	static int pageNow=1;//当前第几页
	int pageNum; //共几页
	int pageCount=3;//每页显示3条数据
	int count=0; 
	//显示表格
	static LNode* tempList= initList();
	static char buf[20]={0};
	char roles[5][20]={"","管理员","仓管员","调度员","客服"};
	char states[2][10]={"不可用","可用"};
	TABLE_T table={220,270,400,140,4,4,{"ID","姓名","角色","状态"}};
	int start=0;
	USER_T* p;
	//1全部查询
	if(strlen(buf)==0)
	{
		int i=0;
		int j=0;
	    count=getListNodeCount(userList);//获取总用户数
	    int pageCount=3;
	    pageNum=count%pageCount==0?count/pageCount:count/pageCount+1;
	    start=(pageNow-1)*pageCount;//计算当前页开始是第几个节点
	    // 清空data
		memset(table.data,0,sizeof(table.data));
	    for(i=0;i<count;i++)
		{
			if(start+i>=count) 
			{
				break;
			}
	        p=(USER_T *)findNode(userList, start+i);
	        j=0;
	        strcpy(table.data[i][j++], p->ID);
	        strcpy(table.data[i][j++],p->name );
	        strcpy(table.data[i][j++],roles[p->role] );
	        strcpy(table.data[i][j++],states[p->state] );
	    }
	}
	else
	{
	    int i=0,j=0;
	    int pageCount=3;
	
	    //分ye：用临时链表的数量
	    count = getListNodeCount(tempList);
	    pageNum = (count + pageCount - 1) / pageCount;
	    start = (pageNow - 1)*pageCount;
	
	    memset(table.data,0,sizeof(table.data));
	    for(i=0;i<pageCount;i++)
	    {
	        if(start+i >= count) break;
	        USER_T *t = (USER_T *)findNode(tempList, start+i);
	        j=0;
	        strcpy(table.data[i][j++], t->ID);
	        strcpy(table.data[i][j++], t->name);
	        strcpy(table.data[i][j++], roles[t->role]);
	        strcpy(table.data[i][j++], states[t->state]);
	    }
	}
	table_show(table, pageNow, pageNum);
	selectUserWin=window_run(selectUserWin);
	
	if(selectUserWin.current==2)
	{
	    if(strlen(selectUserWin.controls[1].text)>0)
		{
	        strcpy(buf,selectUserWin.controls[1].text);
	        if(tempList != NULL)
	        {
	        	freeList(tempList);	
			}
	        tempList=initList();
	
	        int allCount = getListNodeCount(userList);
	        for(int k=0;k<allCount;k++)
			{
	            USER_T *t = (USER_T *)findNode(userList, k);
	            if(t == NULL) 
				continue;
	
	            if(strstr(t->name, buf) != NULL)
				{
	                insertAtTail(tempList, t);
	            }
	        }
	        pageNow=1;
	    }
	    else
		{
	        memset(buf,0,sizeof(buf));
	        pageNow=1;
	    }
	    return 5;
	}
	//向上翻页
	else if(selectUserWin.current==-1)
	{
	    if(pageNow > 1)
	    {
	        pageNow--;	
		}
	    else
	    {
	    	//弹窗
	        CONTROL_T miniWin={245,300,200,80,"已经是第一页",CYAN,LIGHTCYAN,WHITE,BUTTON,0};
	        control_show(miniWin);
	        //延时
	        Sleep(1500);
		}
		return 5;
	}	
	//向下翻页
	else if(selectUserWin.current==-2)
	{
	    if(pageNow<pageNum)
		{
	        pageNow++;
	    }
	    else
		{
	        //弹窗
	        CONTROL_T miniWin={245,300,200,80,"已经是最后一页",CYAN,LIGHTCYAN,WHITE,BUTTON,0};
	        control_show(miniWin);
	        //延时
	        Sleep(1500);
	    }
	    return 5; 
	}
	 
} 

