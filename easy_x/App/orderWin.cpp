int orderWin()
{
    WINDOW_T win={290,155,220,330,WHITE,5,{
        {300,160,200,40,"1.创建订单",LIGHTCYAN,CYAN,WHITE,BUTTON,1,0},  //0
        {300,200,200,40,"2.订单审核",LIGHTCYAN,CYAN,WHITE,BUTTON,0,0},  //1
        {300,240,200,40,"3.订单查询",LIGHTCYAN,CYAN,WHITE,BUTTON,0,0},  //2
        {300,280,200,40,"4.订单跟踪",LIGHTCYAN,CYAN,WHITE,BUTTON,0,0},  //3
        {300,320,200,40,"5.返回上级",LIGHTCYAN,CYAN,WHITE,BUTTON,0,0},  //4
    },0};

    IMAGE img;
    loadimage(&img, "./imge/LMS.jpg",800,600);
    putimage(0, 0, &img);
    setbkmode(TRANSPARENT);
    settextcolor(CYAN);
    outtextxy(200,530,"操作说明：上下键移动切换菜单，按下回车键选择菜单");

    window_show(win);
    win = window_run(win);

    if(win.current == 0)
    {
        return 9; //创建订单
    }
    if(win.current== 1)
    {
        if(curRole == 1) return 10; //只有管理员能审核，后续权限还待考虑 
        return 6;
    }
    if(win.current == 2)
    {
        return 11; //订单查询
    }
    if(win.current == 4)
    {
        return 2; //返回主菜单
    }
    return 6;
