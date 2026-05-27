#include <iostream>
#include <graphics.h>
#include "public/list.h"
#include "public/file.h"
#include "App/data.h" 
#include "App/loginWin.h"
#include "View/control.h" 
#include "App/startWin.h" 
#include "App/mainWin.h"
#include "App/startWin.h"
#include "App/adminWin.h" 
#include "App/orderWin.h" 
#include "App/storeWin.h"
#include "App/storeWin.h"
#include "App/changePasswordWin.h" 
#include "App/serviceWin.h" 
#include "App/analysisWin.h"
#include "App/CustomerServiceWin.h"
//所有的控件运行都依赖Windows_show运行 
//展开后，相关的h文件不要少分号或者参数,一般头文件应该在cpp中 
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
LNode* goodsList = NULL; 
LNode* userList = NULL;  
LNode* orderList = NULL; 
FILE* user_fp = NULL; 
FILE* order_fp = NULL; 
FILE* goods_fp = NULL;
FILE* exports_fp = NULL; 
int main(int argc, char** argv) {
	
	//1.打开文件 
	user_fp = file_open("data/user.txt");
	order_fp = file_open("data/order.txt") ;
	goods_fp = file_open("data/goods.txt") ;
	exports_fp = file_open("data/exports.txt") ;
	//2.初始化用户链表 
	userList = user_data_init(user_fp); 
	orderList = order_data_init(order_fp);
	goodsList = goods_data_init(goods_fp);
	//1.创建绘图窗口 
	initgraph(800, 600) ;	
	
	//2.显示图片背景 
	IMAGE img;   
	loadimage(&img, "imge/LMS.jpg", 800, 600) ;  
	putimage(0, 0, &img) ;  
	//它的格式是返回值 (*fun[nums])(参数) :函数名本身就是地址，代表函数代码在内存里的起始位置
	int (*fun[25])() = {startWin,loginWin,mainWin,           //0 1 2
	adminWin,addUserWin,selectUserWin,   // 3 4 5
	orderWin,createOrderWin,checkOrderWin,orderSearchWin,  //订单区块6 7 8 9 
	storeWin,goodIn,goodOut,goodSeach,  // //货物区块 10 11 12 13 	
	changePasswordWin,  //  14 密码修改区块	  
	customerService,//15 智能客服 
	analysisWin, orderStatWin, storeStatWin,exportReportWin,  //16 17 18 19统计分析模块 
	init1,init2,  // //20 21	 路线和仓库数据初始化
	resetPwdWin};   //22	//忘记密码	         //startWin进入 由loginWin验证 mainWin展开 ： 
	int win_id = 0; 																						//顺序是： 1.odrderWin 2.storeWin 3.RunWin 4.*统计分析   
	while(1)																					//5.*客服服务（考虑接入大模型，当前无实质作用(不知到AI能不能读取到链表或者文件信息)） 6.*密码修改  7.*密码修改 
	{																								
		win_id = fun[win_id]() ;
	}
	


	
}


