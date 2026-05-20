#include <conio.h> 
#include <graphics.h> 
#include "../View/control.h" 
int startWin() 
{
	WINDOW_T startWin = {290, 240 , 220 ,180, WHITE, 3,{
	{300, 250, 200, 50, "µÇ Â¼",LIGHTCYAN,CYAN,WHITE,BUTTON, 1,0},
	{300, 305, 200, 50, "Íü¼ÇÃÜÂë",LIGHTCYAN,CYAN,WHITE,BUTTON, 0,0},
	{300, 365, 200, 50, "ÍË³ö",LIGHTCYAN,CYAN,WHITE,BUTTON, 0,0}}} ; 
	
	Background_display();
	
	window_show(startWin) ;
	startWin = window_run(startWin);
	if(startWin.current = 0)
	{
		return 1; 
	}
	else if(startWin.current = 1)
	{
		
	}
	else if(startWin.current = 2)
	{
		exit(1); 
	}	
}






      



















