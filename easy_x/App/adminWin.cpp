#include <conio.h> 
#include <graphics.h> 
#include "../View/control.h" 
#include <stdio.h> 
#include "../public/file.h"
#include "../public/list.h"
#include "../App/data.h"


const char* getRoleName(int role)
{
    switch(role)
    {
        case 1:
		 return "管理员";
        case 2:
		 return "仓储员";  // 统一使用"仓储员"
        case 3:
		 return "调度员";
        case 4:
		 return "客服";
        default: return "";
    }
}


const char* getStateName(int state)  //补丁 
{
    return state == 1 ? "可用" : "不可用";
}


int init1()
{
    WINDOW_T win = {
        50, 50, 600, 400, WHITE, 9,
        {
            {120,  50, 200, 30, "路线：R001", CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
            {120,  80, 200, 30, "起点：中心仓库", CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
            {120, 110, 200, 30, "终点：城西配送点", CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
            {120, 140, 200, 30, "距离：120km", CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
            {120, 170, 200, 30, "预计耗时：3小时", CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
            {120, 200, 200, 30, "车辆数：2辆", CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
            {120, 230, 200, 30, "司机：张师傅", CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
            {120, 270, 200, 30, "状态：运行中", CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
            {120, 320, 120, 40, "返回", LIGHTCYAN,CYAN,  WHITE, BUTTON, 0, 1},
        }
    };

    Background_display();
    window_show(win);
    win = window_run(win);

    if(win.current == 8)
    {
        return 3;
    }
    return init1();
}


int init2()
{
    WINDOW_T win = {
        50, 50, 600, 400, WHITE, 9,
        {
            {50, 50, 300, 200, "仓库：A01 中心仓库", CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
            {50, 80, 300, 200, "仓库编号: A01", CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
            {50, 110, 300, 200, "仓库容量: 10000", CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
            {50, 140, 300, 200, "已用容量: 3500", CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
            {50, 170, 300, 200, "货位数量: 500", CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
            {50, 200, 300, 200, "可用货位: 320", CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
            {50, 230, 300, 200, "状态: 正常", CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
            {50, 260, 300, 200, "负责人: 管理员", CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
            {80, 300, 120, 40, "返回", LIGHTCYAN,CYAN, WHITE, BUTTON, 0, 1},
        }
    };

    Background_display();
    window_show(win);
    win = window_run(win);

    if(win.current == 8)
    {
        return 3;
    }
    return init2();
}


int adminWin()
{
    WINDOW_T win = {
        290, 155, 220, 330, WHITE, 8, {
            {300, 160, 200, 40, "1、创建用户", LIGHTCYAN,CYAN, WHITE, BUTTON, 1, 0},
            {300, 200, 200, 40, "2、用户查询", LIGHTCYAN,CYAN, WHITE, BUTTON, 0, 0},
            {300, 240, 200, 40, "3、密码重置", LIGHTCYAN,CYAN,WHITE, BUTTON, 0, 0},
            {300, 280, 200, 40, "4、角色管理", LIGHTCYAN,CYAN,WHITE, BUTTON, 0, 0},
            {300, 320, 200, 40, "5、仓库配置", LIGHTCYAN,CYAN, WHITE, BUTTON, 0, 0},
            {300, 360, 200, 40, "6、路线配置", LIGHTCYAN,CYAN, WHITE, BUTTON, 0, 0},
            {300, 400, 200, 40, "7、数据备份", LIGHTCYAN,CYAN, WHITE, BUTTON, 0, 0},
            {300, 440, 200, 40, "8、返回上级", LIGHTCYAN,CYAN, WHITE, BUTTON, 0, 0},
        }
    };
    
    Background_display();
    window_show(win);
    win = window_run(win);
    
    if(win.current == 0)
    {
        return 4;  // 创建用户
    }
    else if(win.current == 1)
    {
        return 5;  // 用户查询
    }
    else if(win.current == 2)
    {
        return 6;  // 密码重置（修复：原来是返回1）
    }
    else if(win.current == 3)
    {
        CONTROL_T tip = {245, 300, 240, 70, "功能尚未实装", LIGHTCYAN,CYAN, WHITE, BUTTON, 0, 0};
        control_show(tip);
        Sleep(1500);
        return 3;
    }
    else if(win.current == 4)
    {
        return 23;  // 仓库配置 init2
    }
    else if(win.current == 5)
    {
        return 22;  // 路线配置 init1
    }
    else if(win.current == 6)
    {
        CONTROL_T tip = {245, 300, 240, 70, "功能尚未实装", LIGHTCYAN,CYAN, WHITE, BUTTON, 0, 0};
        control_show(tip);
        Sleep(1500);
        return 3;
    }
    else if(win.current == 7)
    {
        return 2;  // 返回上级
    }
    return 3;
}


int addUserWin()
{
    WINDOW_T addUserWin = {
        240, 240, 290, 230, CYAN, 8, {
            {245, 250, 80, 50, "用户名：", CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
            {245, 305, 80, 50, "密  码：", CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
            {245, 360, 80, 50, "角  色：", CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},
            {320, 250, 200, 50, "", CYAN, LIGHTCYAN, WHITE, EDIT, 1, 15},
            {320, 305, 200, 50, "", CYAN, LIGHTCYAN, WHITE, EDIT_PWD, 0, 15},
            {320, 360, 200, 50, "管理员,仓储员,调度员,客服", LIGHTCYAN,CYAN, WHITE, SELECT, 0, 0},
            {245, 415, 130, 50, "创建", LIGHTCYAN,CYAN, WHITE, BUTTON, 0, 0},
            {390, 415, 130, 50, "返回", LIGHTCYAN,CYAN, WHITE, BUTTON, 0, 0},
        }
    };
    
    Background_display();
    window_show(addUserWin);
    addUserWin = window_run(addUserWin);
    
    if(addUserWin.current == 6)  // 创建
    {
        char newName[20] = {0};
        strcpy(newName, addUserWin.controls[3].text);
        
        // 校验：用户名不能为空
        if(strlen(newName) == 0)
        {
            CONTROL_T tip = {245, 300, 220, 70, "用户名不能为空", LIGHTCYAN,CYAN, WHITE, BUTTON, 0, 0};
            control_show(tip);
            Sleep(1500);
            return 4;
        }
        
        // 校验：密码不能为空
        if(strlen(addUserWin.controls[4].text) == 0)
        {
            CONTROL_T tip = {245, 300, 220, 70, "密码不能为空", LIGHTCYAN,CYAN, WHITE, BUTTON, 0, 0};
            control_show(tip);
            Sleep(1500);
            return 4;
        }
        
        // 校验：用户名唯一性
        int isRepeat = 0;
        for(int i = 0; i < getListNodeCount(userList); i++)
        {
            USER_T *t = (USER_T*)findNode(userList, i);
            if(t && strcmp(t->name, newName) == 0)
            {
                isRepeat = 1;
                break;
            }
        }
        
        if(isRepeat == 1)
        {
            CONTROL_T tip = {245, 300, 220, 70, "用户名已存在", LIGHTCYAN,CYAN, WHITE, BUTTON, 0, 0};
            control_show(tip);
            Sleep(1500);
            return 4;
        }
        
        // 创建用户
        USER_T *p = (USER_T *)malloc(sizeof(USER_T));
        memset(p, 0, sizeof(USER_T));
        
        sprintf(p->ID, "%d", 1001 + getListNodeCount(userList));
        strcpy(p->name, addUserWin.controls[3].text);
        strcpy(p->passwd, addUserWin.controls[4].text);
        p->state = 1;
        
        if(strcmp(addUserWin.controls[5].text, "管理员") == 0)
        {
            p->role = 1;
        }
        else if(strcmp(addUserWin.controls[5].text, "仓储员") == 0)
        {
            p->role = 2;
        }
        else if(strcmp(addUserWin.controls[5].text, "调度员") == 0)
        {
            p->role = 3;
        }
        else if(strcmp(addUserWin.controls[5].text, "客服") == 0)
        {
            p->role = 4;
        }
        else
        {
            p->role = 2;  // 默认仓储员
        }
        
        insertAtTail(userList, p);
        file_add(user_fp, sizeof(USER_T), p);
        
        CONTROL_T miniWin = {245, 300, 200, 80, "创建用户成功", LIGHTCYAN,CYAN, WHITE, BUTTON, 0, 0};
        control_show(miniWin);
        Sleep(1500);
        return 4;
    }
    else if(addUserWin.current == 7)  // 返回
    {
        return 3;
    }
    return 4;
}


int selectUserWin()
{
    WINDOW_T selectUserWin = {
        0, 100, 850, 450, WHITE, 4, {
            {50, 120, 100, 40, "搜索：", LIGHTCYAN, CYAN, WHITE, LABEL, 0, 0},
            {160, 120, 200, 40, "", CYAN, LIGHTCYAN, WHITE, EDIT, 1, 20},
            {380, 120, 100, 40, "搜索", LIGHTCYAN, CYAN, WHITE, BUTTON, 0, 0},
            {700, 120, 100, 40, "返回", LIGHTCYAN, CYAN, WHITE, BUTTON, 0, 0},
        }
    };
    
    Background_display();
    window_show(selectUserWin);
    TABLE_T table = {
        20, 180, 810, 280,
        6, 5,
        {"用户ID", "用户名", "姓名", "角色", "状态"}
    };
    
    static int pageNow = 1;
    int pageNum;
    int pageCount = 3;
    static LNode* tempList = NULL;
    static char buf[20] = {0};
    
    int count = 0;
    int start = 0;
    USER_T* p;
    
    // 全部查询
    if(strlen(buf) == 0)
    {
        count = getListNodeCount(userList);
        pageNum = (count + pageCount - 1) / pageCount;
        start = (pageNow - 1) * pageCount;
        
        memset(table.data, 0, sizeof(table.data));
        for(int i = 0; i < pageCount; i++)
        {
            if(start + i >= count) break;
            p = (USER_T *)findNode(userList, start + i);
            if(p == NULL) continue;
            
            int j = 0;
            strcpy(table.data[i][j++], p->ID);
            strcpy(table.data[i][j++], p->name);
            strcpy(table.data[i][j++], getRoleName(p->role));  // 【修复】统一使用getRoleName
            strcpy(table.data[i][j++], getStateName(p->state));
        }
    }
    else
    {
        count = getListNodeCount(tempList);
        pageNum = (count + pageCount - 1) / pageCount;
        start = (pageNow - 1) * pageCount;
        
        memset(table.data, 0, sizeof(table.data));
        for(int i = 0; i < pageCount; i++)
        {
            if(start + i >= count) break;
            USER_T *t = (USER_T *)findNode(tempList, start + i);
            if(t == NULL) continue;
            
            int j = 0;
            strcpy(table.data[i][j++], t->ID);
            strcpy(table.data[i][j++], t->name);
            strcpy(table.data[i][j++], getRoleName(t->role));  // 【修复】统一使用getRoleName
            strcpy(table.data[i][j++], getStateName(t->state));
        }
    }
    
    table_show(table, pageNum, pageNow);
    selectUserWin = window_run(selectUserWin);
    
    if(selectUserWin.current == 2)  // 查询
    {
        if(strlen(selectUserWin.controls[1].text) > 0)
        {
            strcpy(buf, selectUserWin.controls[1].text);
            if(tempList != NULL)
            {
                freeList(tempList);
            }
            tempList = initList();
            
            int allCount = getListNodeCount(userList);
            for(int k = 0; k < allCount; k++)
            {
                USER_T *t = (USER_T *)findNode(userList, k);
                if(t && strstr(t->name, buf) != NULL)
                {
                    insertAtTail(tempList, t);
                }
            }
            pageNow = 1;
        }
        else
        {
            memset(buf, 0, sizeof(buf));
            pageNow = 1;
        }
        return 5;
    }
    else if(selectUserWin.current == -1)  // 上页
    {
        if(pageNow > 1)
        {
            pageNow--;
        }
        else
        {
            CONTROL_T miniWin = {245, 300, 200, 80, "已经是第一页", LIGHTCYAN,CYAN, WHITE, BUTTON, 0, 0};
            control_show(miniWin);
            Sleep(1200);
        }
        return 5;
    }
    else if(selectUserWin.current == -2)  // 下页
    {
        if(pageNow < pageNum)
        {
            pageNow++;
        }
        else
        {
            CONTROL_T miniWin = {245, 300, 200, 80, "已经是最后一页", LIGHTCYAN,CYAN, WHITE, BUTTON, 0, 0};
            control_show(miniWin);
            Sleep(1200);
        }
        return 5;
    }
    else if(selectUserWin.current == 3)  // 返回
    {
        if(tempList != NULL)
        {
            freeList(tempList);
            tempList = NULL;
        }
        memset(buf, 0, sizeof(buf));
        pageNow = 1;
        return 3;
    }
}
