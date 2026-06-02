#include <conio.h> 
#include <graphics.h> 
#include "../View/control.h" 
#include <stdio.h> 
#include "../App/data.h"

int changePasswordWin()
{

    WINDOW_T pwdWin = { 200,120,400,400,CYAN,8,{
        {220,140,180,40,"原密码:",CYAN,LIGHTCYAN,WHITE,LABEL,1,20},
        {220,180,180,40,"",CYAN,LIGHTCYAN,WHITE,EDIT,1,20},

        {220,220,180,40,"新密码:",CYAN,LIGHTCYAN,WHITE,LABEL,0,20},
        {220,260,180,40,"",CYAN,LIGHTCYAN,WHITE,EDIT,0,20},

        {220,300,180,40,"确认密码:",CYAN,LIGHTCYAN,WHITE,LABEL,0,20},
        {220,340,180,40,"",CYAN,LIGHTCYAN,WHITE,EDIT,0,20},

        {220,380,180,40,"确认修改",LIGHTCYAN,CYAN,WHITE,BUTTON,0,0},
        {220,420,180,40,"返回",LIGHTCYAN,CYAN,WHITE,BUTTON,0,0},
    }};

    Background_display();
    window_show(pwdWin);
    pwdWin = window_run(pwdWin);

    //返回
    if (pwdWin.current == 7)
    {
        return 1; // 菜单页
    }

    //确认修改
    if (pwdWin.current == 6)
    {
        char oldPwd[50] = {0};
        char newPwd[50] = {0};
        char confirmPwd[50] = {0};

        //读取输入框内容
        strcpy(oldPwd, pwdWin.controls[1].text);
        strcpy(newPwd, pwdWin.controls[3].text);
        strcpy(confirmPwd, pwdWin.controls[5].text);

        //二次校验 
        if (strcmp(newPwd, confirmPwd) != 0)
        {
            printf("两次新密码不一致！\n");
            return 5;
        }

        LNode* cur = userList->next;
        while (cur != NULL)
        {
            USER_T* u = (USER_T*)cur->data;

            //匹配：当前用户的密码正确
            if (strcmp(u->passwd, oldPwd) == 0)
            {
                //修改密码
                strcpy(u->passwd, newPwd);

                //保存到文件 user.txt
                FILE* fp = fopen("data/user.txt", "wb");
                LNode* p = userList->next;
                while (p != NULL)
                {
                    fwrite(p->data, sizeof(USER_T), 1, fp);
                    p = p->next;
                }
                fclose(fp);

                printf("密码修改成功！\n");
                return 5;
            }
            cur = cur->next;
        }

        printf("原密码错误！\n");
    }

    return 1;
}
