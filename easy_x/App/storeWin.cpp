





int storeWin()  //进入前的条件是你是仓储员或者管理员 
{
    WINDOW_T win={290,155,220,330,WHITE,4,{
        {300,160,200,40,"1.货物入库",LIGHTCYAN,CYAN,WHITE,BUTTON,1,0},
        {300,200,200,40,"2.货物出库",LIGHTCYAN,CYAN,WHITE,BUTTON,0,0},
        {300,240,200,40,"3.库存查询",LIGHTCYAN,CYAN,WHITE,BUTTON,0,0},
        {300,280,200,40,"4.返回上级",LIGHTCYAN,CYAN,WHITE,BUTTON,0,0},
    },0};

    IMAGE img;
    loadimage(&img, "./imge/LMS.jpg",800,600);
    putimage(0, 0, &img);
    setbkmode(TRANSPARENT);
    settextcolor(CYAN);
    outtextxy(200,530,"操作说明：上下键移动切换菜单，按下回车键选择菜单");
    
    window_show(win);
    win = window_run(win);
    
int goodIn()
{
	
}
	 
int goodOut() 
{
	
}

int goodseacha()
{
	
}
    
    
    
