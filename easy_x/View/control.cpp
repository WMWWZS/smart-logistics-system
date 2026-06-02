#include <graphics.h>
#include <conio.h>
#include "control.h"
#include "string.h"
#include <stdio.h>


void control_show(CONTROL_T ctr1)
{
    int i = 0;
    char str[100] = {0};
    
    // 框的绘制（按钮、编辑框、密码框、下拉框）
    if(ctr1.type == BUTTON || ctr1.type == EDIT || ctr1.type == EDIT_PWD || ctr1.type == SELECT || ctr1.type == SELECTED)
    {
        // 根据选中状态设置背景色
        if(ctr1.state == 1)
        {
            setfillcolor(ctr1.bgColor2);  // 高亮颜色
        }
        else
        {
            setfillcolor(ctr1.bgColor1);  // 默认颜色
        }
        fillrectangle(ctr1.x, ctr1.y, ctr1.x + ctr1.width, ctr1.y + ctr1.hight);
    }
    
    // 显示文本
    setbkmode(TRANSPARENT);
    settextstyle(16, 0, _T("黑体"));  // 统一设置字体
    
    if(ctr1.type == LABEL)
    {
        // 标签：设置文本颜色并显示文本
        settextcolor(ctr1.textCloor);
        outtextxy(ctr1.x, ctr1.y + 15, ctr1.text);
    }
    else if(ctr1.type == EDIT)
    {
        // 编辑框：设置文本颜色并显示文本
        settextcolor(ctr1.textCloor);
        outtextxy(ctr1.x + 5, ctr1.y + 15, ctr1.text);
    }
    else if(ctr1.type == BUTTON)
    {
        // 按钮：居中显示文本（使用更大字体）
        settextstyle(18, 0, _T("黑体"));
        int textWidth = strlen(ctr1.text) * 9;
        int centerX = ctr1.x + (ctr1.width - textWidth) / 2;
        int centerY = ctr1.y + (ctr1.hight - 18) / 2;
        outtextxy(centerX, centerY, ctr1.text);
    }
    else if(ctr1.type == EDIT_PWD)
    {
        // 密码框：设置文本颜色并显示星号
        settextcolor(ctr1.textCloor);
        strcpy(str, ctr1.text);
        int len = strlen(str);
        for(i = 0; i < len; i++)
        {
            str[i] = '*';
        }
        str[len] = '\0';
        outtextxy(ctr1.x + 5, ctr1.y + 15, str);
    }
    else if(ctr1.type == SELECT || ctr1.type == SELECTED)
    {
        // 下拉框：设置文本颜色并显示当前选项 + 下箭头
        settextcolor(ctr1.textCloor);
        char buf[20] = {0};
        sscanf(ctr1.text, "%[^,]", buf);
        outtextxy(ctr1.x + 5, ctr1.y + 15, buf);
        outtextxy(ctr1.x + ctr1.width - 20, ctr1.y + 15, "▼");
    }
}


void window_show(WINDOW_T win)
{
    int i = 0;
    setfillcolor(win.bgColor);
    fillrectangle(win.x, win.y, win.width + win.x, win.y + win.hight);
    for(i = 0; i < win.count; i++)
    {
        control_show(win.controls[i]);
    }
}


WINDOW_T window_run(WINDOW_T win)
{
    char ch1, ch2;
    int i = 0;
    
    // 找到第一个可停留控件（跳过LABEL）
    while(win.controls[i].type == LABEL)
    {
        i++;
        if(i == win.count)
        {
            i = 0;
        }
    }
    
    // 初始化选中状态
    for(int j = 0; j < win.count; j++)
    {
        win.controls[j].state = 0;
    }
    win.controls[i].state = 1;
    
    // 只重绘选中控件，避免覆盖表格
    control_show(win.controls[i]);
    
    while(1)
    {
        ch1 = getch();
        
        // 回车确认
        if(ch1 == '\r')
        {
            if(win.controls[i].type == BUTTON || win.controls[i].type == SELECT || win.controls[i].type == SELECTED)
            {
                win.current = i;
                return win;
            }
        }
        // 下拉框选择逻辑
        else if(win.controls[i].type == SELECT)
        {
            static WINDOW_T selectWin = {
                win.controls[i].x,
                win.controls[i].y + win.controls[i].hight,
                win.controls[i].width,
                win.controls[i].hight,
                WHITE,
                0,
                {0}
            };
            
            char *buf[10] = {0};
            int k = 0;
            char text_copy[100] = {0};
            strcpy(text_copy, win.controls[i].text);
            char *token = strtok(text_copy, ",");
            while(token != NULL && k < 10)
            {
                buf[k++] = token;
                token = strtok(NULL, ",");
            }
            selectWin.count = k;
            
            // 【优化】使用控件实际高度而非硬编码50
            int itemH = win.controls[i].hight;
            for(int j = 0; j < k; j++)
            {
                CONTROL_T tmpCtrl = {
                    win.controls[i].x,
                    win.controls[i].y + itemH * j,
                    win.controls[i].width,
                    itemH,
                    "",
                    CYAN, LIGHTCYAN, WHITE,
                    BUTTON,
                    0
                };
                strcpy(tmpCtrl.text, buf[j]);
                selectWin.controls[j] = tmpCtrl;
                
                if(j == 0)
                {
                    selectWin.controls[j].state = 1;
                }
            }
            win.controls[i].type = SELECTED;
            
            window_show(selectWin);
            selectWin = window_run(selectWin);
            
            // 【关键】将选中结果回写到控件
            char selText[20] = {0};
            strcpy(selText, selectWin.controls[selectWin.current].text);
            strcpy(win.controls[i].text, selText);
            
            Background_display();
            window_show(win);
            
            int nextIdx = i + 1;
            if(nextIdx >= win.count) nextIdx = 0;
            while(win.controls[nextIdx].type == LABEL)
            {
                nextIdx++;
                if(nextIdx >= win.count) nextIdx = 0;
            }
            win.controls[i].state = 0;
            win.controls[nextIdx].state = 1;
            
            Background_display();
            window_show(win);
            i = nextIdx;
        }
        // 字符输入（编辑框）
        else if(ch1 >= '0' && ch1 <= '9' || ch1 >= 'a' && ch1 <= 'z' || ch1 >= 'A' && ch1 <= 'Z')
        {
            if(win.controls[i].type == EDIT || win.controls[i].type == EDIT_PWD)
            {
                int len = strlen(win.controls[i].text);
                if(len < win.controls[i].maxStr)
                {
                    win.controls[i].text[len] = ch1;
                    win.controls[i].text[len + 1] = '\0';
                    control_show(win.controls[i]);
                }
            }
        }
        // 退格删除
        else if(ch1 == '\b')
        {
            if(win.controls[i].type == EDIT || win.controls[i].type == EDIT_PWD)
            {
                int len = strlen(win.controls[i].text);
                if(len > 0)
                {
                    win.controls[i].text[len - 1] = '\0';
                    control_show(win.controls[i]);
                }
            }
        }
        // 方向键
        else if(ch1 == -32)
        {
            ch2 = getch();
            
            // 下键：移动到下一个可停留控件
            if(ch2 == KEY_DOWN)
            {
                win.controls[i].state = 0;
                control_show(win.controls[i]);
                
                do
                {
                    i++;
                    if(i >= win.count)
                    {
                        i = 0;
                    }
                } while(win.controls[i].type == LABEL);
                
                win.controls[i].state = 1;
                window_show(win);
            }
            // 上键：移动到上一个可停留控件
            else if(ch2 == KEY_UP)
            {
                win.controls[i].state = 0;
                control_show(win.controls[i]);
                
                do
                {
                    i--;
                    if(i < 0)
                    {
                        i = win.count - 1;
                    }
                } while(win.controls[i].type == LABEL);
                
                win.controls[i].state = 1;
                window_show(win);
            }
            // 左键：上一页
            else if(ch2 == KEY_LEFT)
            {
                win.current = -1;
                return win;
            }
            // 右键：下一页
            else if(ch2 == KEY_RIGHT)
            {
                win.current = -2;
                return win;
            }
        }
    }
}


void Background_display()
{
    IMAGE img;
    loadimage(&img, "./imge/LMS.jpg", 800, 600);
    putimage(0, 0, &img);
    setbkmode(TRANSPARENT);
    settextcolor(CYAN);
    settextstyle(16, 0, _T("黑体"));
    outtextxy(200, 530, "操作说明：上下键移动切换菜单，按下回车键选择菜单");
}


void table_show(TABLE_T table, int pageNum, int pageNow)
{
    int i, j;
    int w = table.width / table.col;
    int h = table.height / table.row;
    
    // 设置表格样式
    setfillcolor(WHITE);
    setlinecolor(CYAN);
    settextcolor(CYAN);
    settextstyle(16, 0, _T("黑体"));
    
    // 画格子
    for(i = 0; i < table.row; i++)
    {
        for(j = 0; j < table.col; j++)
        {
            fillrectangle(table.x + w * j, table.y + h * i, table.x + w * j + w, table.y + h * i + h);
            rectangle(table.x + w * j, table.y + h * i, table.x + w * j + w, table.y + h * i + h);
        }
    }
    
    // 显示表头
    settextcolor(LIGHTCYAN);
    for(j = 0; j < table.col; j++)
    {
        int centerX = table.x + w * j + (w - strlen(table.text[j]) * 8) / 2;
        outtextxy(centerX, table.y + 10, table.text[j]);
    }
    
    // 显示表格内容
    settextcolor(CYAN);
    for(i = 1; i < table.row; i++)
    {
        for(j = 0; j < table.col; j++)
        {
            int centerX = table.x + w * j + 5;
            outtextxy(centerX, table.y + h * i + 10, table.data[i - 1][j]);
        }
    }
    
    // 显示页数信息
    char str[50] = {0};
    sprintf(str, "<-上页    共%d页/当前第%d页    ->下页", pageNum, pageNow);
    outtextxy(table.x + 50, table.y + table.height + 10, str);
}
