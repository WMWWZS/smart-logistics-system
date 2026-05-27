#include <windows.h>
#include <wininet.h>
#include <stdio.h>
#include <string.h>
#include <graphics.h>
#include <conio.h>
#include "../View/control.h" 
#include "data.h"
#include "../public/file.h" 

#define API_KEY "sk-befb4662876d42359a64d3d58428815a"

void getAIReply(const char *question, char *reply)
{
    memset(reply, 0, 256);
    HINTERNET hInternet = InternetOpenA("LMS", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    HINTERNET hConnect = InternetConnectA(hInternet, "api.deepseek.com", INTERNET_DEFAULT_HTTPS_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
    HINTERNET hRequest = HttpOpenRequestA(hConnect, "POST", "/v1/chat/completions", NULL, NULL, NULL, INTERNET_FLAG_SECURE, 0);

    char header[256];
    sprintf(header, "Content-Type: application/json\r\nAuthorization: Bearer %s\r\n", API_KEY);

    char data[1024];
    sprintf(data, "{\"model\":\"deepseek-chat\",\"messages\":[{\"role\":\"user\",\"content\":\"%s\"}]}", question);

    HttpSendRequestA(hRequest, header, strlen(header), data, strlen(data));

    char buffer[4096] = {0};
    DWORD read;
    InternetReadFile(hRequest, buffer, sizeof(buffer)-1, &read);

    char *start = strstr(buffer, "\"content\":\"");
    if (start)
    {
        start += 10;
        char *end = strstr(start, "\"");
        if (end)
        {
            *end = 0;
            strcpy(reply, start);
        }
    }

    InternetCloseHandle(hRequest);
    InternetCloseHandle(hConnect);
    InternetCloseHandle(hInternet);
}
int customerService()
{
    char question[100] = {0};
    char answer[256] = {"欢迎使用智能物流AI客服，请输入问题~"};

    WINDOW_T chatWin = {180,100,560,440,WHITE,5,{
        {200,110,300,40,"AI智能客服",CYAN,LIGHTCYAN,WHITE,LABEL,0,0},
        {200,170,320,80,"",CYAN,LIGHTCYAN,WHITE,LABEL,0,0},    // AI回答展示框
        {200,270,320,40,"",CYAN,LIGHTCYAN,WHITE,EDIT,1,100},   // 输入框
        {200,340,120,40,"发送",CYAN,LIGHTCYAN,WHITE,BUTTON,0,2},
        {340,340,120,40,"返回",CYAN,LIGHTCYAN,WHITE,BUTTON,0,3},
    }};

BACK:
    Background_display();
    window_show(chatWin);
    // 把AI回答直接显示到标签上
    strcpy(chatWin.controls[1].text, answer);
    chatWin = window_run(chatWin);

    // 发送问题，调用大模型
	// 发送问题，调用大模型
	if (chatWin.current == 3)
	{
	    strcpy(question, chatWin.controls[2].text);
	    if (strlen(question) == 0) goto BACK;
	
	    getAIReply(question, answer);
	
	    // 把AI回答安全地复制到 LABEL 控件
	    strncpy(chatWin.controls[1].text, answer, sizeof(chatWin.controls[1].text) - 1);
	    chatWin.controls[1].text[sizeof(chatWin.controls[1].text) - 1] = '\0';
	
	    // 刷新界面，让新文本显示出来
	    Background_display();
	    window_show(chatWin);
	
	    // 清空输入框
	    memset(chatWin.controls[2].text, 0, sizeof(chatWin.controls[2].text));
	    goto BACK;
	}

    // 返回主菜单
    if (chatWin.current == 4)
    {
        return 2;
    }
}
