#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include "control.h" 

/*
#define BUTTON   1 按钮 
#define EDIT     2 编辑框 
#define EDIT_PWD 3   
#define LABEL    4 标签 
*/

//空间显示函数 
void control_show(CONTROL_T ctr1) 
{   //框的绘制 
	int i = 0;
	char str[20] = {0}; 
	if(ctr1.type == BUTTON || ctr1.type == EDIT || ctr1.type == EDIT_PWD) 
	{
		if(ctr1.state == 1)  //说明被选中 
		{
			setfillcolor(ctr1.bgColor2) ;
		}
		else
		{
			setfillcolor(ctr1.bgColor1) ;
		} 
		fillrectangle(ctr1.x, ctr1.y, ctr1.x + ctr1.width, ctr1.y + ctr1.hight); 
	} 
	
	//显示文本 
	
	if(ctr1.type == LABEL || ctr1.type == EDIT) 
	{
		outtextxy(ctr1.x, ctr1.y, ctr1.text); //此处可设置xy的偏移（效果待定） 
		
	}
	else if(ctr1.type == BUTTON) 
	{
		settextstyle(16, 10, _T("黑体"));
		int center = ctr1.x + (ctr1.width - strlen(ctr1.text) * 2 * 10) ;
		outtextxy(center, ctr1.y + 15, ctr1.text) ;
	}
	else if(ctr1.type == EDIT_PWD)	
	{
		for(i = 0; i < strlen(str); i++) 
		{
			str[i] = '*';
			
		}
	}
	outtextxy(ctr1.x + 5, ctr1.y + 15, str)	;
}


# 初始化
mouse = Controller()
# 加载YOLOv8 官方预训练模型（你以后可以换成自己训练的模型）
model = YOLO("yolov8n.pt")

# 屏幕中心
SCREEN_W = 1920
SCREEN_H = 1080
CENTER_X = SCREEN_W / 2
CENTER_Y = SCREEN_H / 2

# 平滑系数 0~1 越小越慢越静默
SMOOTH_FACTOR = 0.08

def smooth_aim(dx, dy):
    """平滑插值 只做原理演示"""
    move_x = dx * SMOOTH_FACTOR
    move_y = dy * SMOOTH_FACTOR
    return move_x, move_y

# 截屏循环
with mss.mss() as sct:
    monitor = sct.monitors[1]
    while True:
        # 截全屏
        sct_img = sct.grab(monitor)
        frame = np.array(sct_img)
        frame = cv2.cvtColor(frame, cv2.COLOR_BGRA2BGR)

        # YOLO推理
        results = model(frame, conf=0.5)

        for res in results:
            boxes = res.boxes
            if boxes is None:
                continue

            for box in boxes:
                # 框坐标 x1 y1 x2 y2
                x1, y1, x2, y2 = box.xyxy[0]
                # 目标中心
                tar_x = (x1 + x2) / 2
                tar_y = (y1 + y2) / 2

                # 计算偏移
                dx = tar_x - CENTER_X
                dy = tar_y - CENTER_Y

                # 平滑位移
                mx, my = smooth_aim(dx, dy)

                # 移动鼠标（原理调用）
                mouse.move(mx, my)

                # 画框看效果
                cv2.rectangle(frame, (int(x1), int(y1)), (int(x2), int(y2)), (0,255,0), 2)

        # 显示画面
        cv2.imshow("YOLO Vision Demo", frame)
        if cv2.waitKey(1) & 0xFF == ord("q"):
            break

cv2.destroyAllWindows()
