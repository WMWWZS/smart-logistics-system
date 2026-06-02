//#include <windows.h>
//#include <wininet.h>
//#include <stdio.h>
//#include <string.h>
//#include <graphics.h>
//#include <conio.h>
//#include "../View/control.h" 
//#include "data.h"
//#include "../public/file.h" 
//
//#define API_KEY "sk-befb4662876d42359a64d3d58428815a"
//
//// 最简单的 AI 回答函数（不联网，基于本地数据）
//void getAIResponse(const char* question, char* answer)
//{
//    // 基于你的链表数据回答
//    if(strstr(question, "订单") != NULL)
//    {
//        // 统计订单数量
//        int total = 0;
//        LNode* p = orderList->next;
//        while(p) { total++; p = p->next; }
//        sprintf(answer, "当前系统中共有 %d 个订单。", total);
//    }
//    else if(strstr(question, "库存") != NULL)
//    {
//        sprintf(answer, "当前库存情况：\n- 电子产品：100件\n- 食品：50件\n- 服装：200件");
//    }
//    else
//    {
//        sprintf(answer, "我收到你的问题：“%s”。\n我目前可以回答：\n1. 订单查询\n2. 库存查询\n3. 物流状态", question);
//    }
//}
//void getAIReply(const char* question, char* answer)
//{
//    // 你原来的 HTTP 请求代码
//    HINTERNET hInternet = InternetOpenA("LMS", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
//    HINTERNET hConnect = InternetConnectA(hInternet, "api.deepseek.com", INTERNET_DEFAULT_HTTPS_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
//    HINTERNET hRequest = HttpOpenRequestA(hConnect, "POST", "/v1/chat/completions", NULL, NULL, NULL, INTERNET_FLAG_SECURE, 0);
//
//    char header[256];
//    sprintf(header, "Content-Type: application/json\r\nAuthorization: Bearer %s\r\n", API_KEY);
//
//    char data[1024];
//    sprintf(data, "{\"model\":\"deepseek-chat\",\"messages\":[{\"role\":\"user\",\"content\":\"%s\"}]}", question);
//
//    HttpSendRequestA(hRequest, header, strlen(header), data, strlen(data));
//
//    char buffer[4096] = {0};
//    DWORD read;
//    InternetReadFile(hRequest, buffer, sizeof(buffer)-1, &read);
//
//    char *start = strstr(buffer, "\"content\":\"");
//    if (start)
//    {
//        start += 10;
//        char *end = strstr(start, "\"");
//        if (end)
//        {
//            *end = 0;
//            strcpy(answer, start);
//        }
//    }
//
//    InternetCloseHandle(hRequest);
//    InternetCloseHandle(hConnect);
//    InternetCloseHandle(hInternet);
//}
//int customerService()
//{
//    char question[256] = {0};  // 用户输入
//    char answer[1024] = {0};   // AI 回答
//    char history[4096] = {0};  // 完整对话历史
//    
//    // 1. 创建聊天窗口
//    WINDOW_T win = {
//        180, 100, 560, 440, WHITE, 6,  // 注意：现在是6个控件
//        {
//            {200, 120, 300, 40, "AI智能客服", LIGHTCYAN, CYAN, WHITE, LABEL, 0, 0},
//            {200, 180, 320, 120, "你好！我是物流AI助手，可以帮你查询订单、物流等信息。", CYAN, LIGHTCYAN, WHITE, LABEL, 0, 0},  // AI回答显示框
//            {200, 320, 200, 40, "", CYAN, LIGHTCYAN, WHITE, EDIT, 0, 30},  // 用户输入框
//            {420, 320, 100, 40, "发送", LIGHTCYAN, CYAN, WHITE, BUTTON, 0, 3},
//            {420, 380, 100, 40, "导出TXT", LIGHTCYAN, CYAN, WHITE, BUTTON, 0, 4},
//            {200, 380, 100, 40, "返回", LIGHTCYAN, CYAN, WHITE, BUTTON, 0, 5}
//        }
//    };
//    
//    // 2. 初始化对话历史
//    strcpy(history, "【AI】你好！我是物流AI助手，可以帮你查询订单、物流等信息。\n");
//    
//    // 3. 显示窗口
//    Background_display();
//    window_show(win);
//    
//    // 4. 窗口循环
//    while(1)
//    {
//        win = window_run(win);
//        
//        // 处理用户操作
//        if(win.current == 3)  // 发送按钮
//        {
//            // 获取用户输入
//            if(strlen(win.controls[2].text) > 0)
//            {
//                strcpy(question, win.controls[2].text);
//                
//                // ? 关键：调用真实的 AI 接口函数
//                getAIResponse(question, answer);  // 替换成你的实际AI接口调用
//                
//                // 如果没有AI接口，先用模拟数据测试
//                if(strlen(answer) == 0)
//                {
//                    // 模拟回答（测试用，实际要换成真实AI接口）
//                    sprintf(answer, "我收到你的问题：“%s”\n系统正在查询订单信息...\n", question);
//                }
//                
//                // ? 更新LABEL显示
//                char displayText[2048] = {0};
//                sprintf(displayText, "%s\n\n【用户】%s\n【AI】%s", 
//                        win.controls[1].text, question, answer);
//                strcpy(win.controls[1].text, displayText);
//                
//                // 更新对话历史
//                char tempHistory[1024];
//                sprintf(tempHistory, "【用户】%s\n【AI】%s\n", question, answer);
//                strcat(history, tempHistory);
//                
//                // 清空输入框
//                memset(win.controls[2].text, 0, sizeof(win.controls[2].text));
//                
//                // 重新显示窗口
//                Background_display();
//                window_show(win);
//            }
//        }
//        else if(win.current == 4)  // 导出TXT按钮
//        {
//            FILE* fp = fopen("AI对话记录.txt", "w");
//            if(fp)
//            {
//                fprintf(fp, "=== AI客服对话记录 ===\n\n%s", history);
//                fclose(fp);
//                MessageBox(NULL, "对话已导出到：AI对话记录.txt", "成功", MB_OK);
//            }
//            else
//            {
//                MessageBox(NULL, "无法创建文件！", "错误", MB_OK);
//            }
//        }
//        else if(win.current == 5)  // 返回按钮
//        {
//            return 0;  // 返回主菜单
//        }
//    }
//    
//    return 0;
//}
