#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "usmart.h"
#include "rtc.h"
#include "key.h"  
#include "24cxx.h" 
#include "myiic.h"
#include "touch.h" 
#include <math.h>
//ALIENTEK Mini STM32开发板范例代码13
//RTC实时时钟实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司
 	
int times = 0;
u8 t;	
u8 key = 0;
u8 key2 = 0;


void ShowTime(u8 key){
	
		//這個是寧文韜調整時間的時候用的
    tp_dev.scan(0);
    if(tp_dev.sta&TP_PRES_DOWN) 
    {
        if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height)
        {
            if(tp_dev.y[0]<lcddev.height/2)
							RTC_Set(calendar.w_year,calendar.w_month,calendar.w_date,calendar.hour,calendar.min,calendar.sec+1);
            else 
						  RTC_Set(calendar.w_year,calendar.w_month,calendar.w_date,calendar.hour,calendar.min,calendar.sec-1);
        }
    }else delay_ms(10); //?????????
		
		
    if(key==KEY0_PRES) //KEY0 ??,???????
    {
         times += 1;
    }		
	//	printf("%d\n", times);

			switch(times)
			{
				case 1:
					LCD_ShowString(10,200,200,16,12,"Press WKUP to increase year. ");
				  LCD_ShowString(10,220,200,16,12,"Or touch screen to change. ");
					if(key==WKUP_PRES || (tp_dev.sta&TP_PRES_DOWN)) 
					RTC_Set(calendar.w_year + 1,calendar.w_month,calendar.w_date,calendar.hour,calendar.min,calendar.sec);
					break;
				case 2:
					LCD_ShowString(10,200,200,16,12,"Press WKUP to decrease year. ");
				  LCD_ShowString(10,220,200,16,12,"Or touch screen to change. ");
					if(key==WKUP_PRES || (tp_dev.sta&TP_PRES_DOWN)) 
					RTC_Set(calendar.w_year - 1,calendar.w_month,calendar.w_date,calendar.hour,calendar.min,calendar.sec);
					break;
				case 3:
					LCD_ShowString(10,200,200,16,12,"Press WKUP to increase month. ");
				  LCD_ShowString(10,220,200,16,12,"Or touch screen to change. ");
					if(key==WKUP_PRES || (tp_dev.sta&TP_PRES_DOWN))  
					RTC_Set(calendar.w_year,calendar.w_month + 1,calendar.w_date,calendar.hour,calendar.min,calendar.sec);
					break;
				case 4:
					LCD_ShowString(10,200,200,16,12,"Press WKUP to decrease month. ");
				  LCD_ShowString(10,220,200,16,12,"Or touch screen to change. ");
					if(key==WKUP_PRES || (tp_dev.sta&TP_PRES_DOWN)) 
					RTC_Set(calendar.w_year,calendar.w_month - 1,calendar.w_date,calendar.hour,calendar.min,calendar.sec);
					break;
				case 5:
					LCD_ShowString(10,200,200,16,12,"Press WKUP to increase date. ");
				  LCD_ShowString(10,220,200,16,12,"Or touch screen to change. ");
					if(key==WKUP_PRES || (tp_dev.sta&TP_PRES_DOWN)) 
					RTC_Set(calendar.w_year,calendar.w_month,calendar.w_date + 1,calendar.hour,calendar.min,calendar.sec);
					break;
				case 6:
					LCD_ShowString(10,200,200,16,12,"Press WKUP to decrease date. ");
				  LCD_ShowString(10,220,200,16,12,"Or touch screen to change. ");
					if(key==WKUP_PRES || (tp_dev.sta&TP_PRES_DOWN)) 
					RTC_Set(calendar.w_year,calendar.w_month,calendar.w_date - 1,calendar.hour,calendar.min,calendar.sec);
					break;
				case 7:
					LCD_ShowString(10,200,200,16,12,"Press WKUP to increase hour. ");
				  LCD_ShowString(10,220,200,16,12,"Or touch screen to change. ");
					if(key==WKUP_PRES || (tp_dev.sta&TP_PRES_DOWN)) 
					RTC_Set(calendar.w_year,calendar.w_month,calendar.w_date,calendar.hour + 1,calendar.min,calendar.sec);
					break;
				case 8:
					LCD_ShowString(10,200,200,16,12,"Press WKUP to decrease hour. ");
				  LCD_ShowString(10,220,200,16,12,"Or touch screen to change. ");
					if(key==WKUP_PRES || (tp_dev.sta&TP_PRES_DOWN)) 
					RTC_Set(calendar.w_year,calendar.w_month,calendar.w_date,calendar.hour - 1,calendar.min,calendar.sec);
					break;
				case 9:
					LCD_ShowString(10,200,200,16,12,"Press WKUP to increase minute. ");
				  LCD_ShowString(10,220,200,16,12,"Or touch screen to change. ");
					if(key==WKUP_PRES || (tp_dev.sta&TP_PRES_DOWN)) 
					RTC_Set(calendar.w_year,calendar.w_month,calendar.w_date,calendar.hour,calendar.min + 1,calendar.sec);
					break;
				case 10:
					LCD_ShowString(10,200,200,16,12,"Press WKUP to decrease minute. ");
				  LCD_ShowString(10,220,200,16,12,"Or touch screen to change. ");
					if(key==WKUP_PRES || (tp_dev.sta&TP_PRES_DOWN)) 
					RTC_Set(calendar.w_year,calendar.w_month,calendar.w_date,calendar.hour,calendar.min - 1,calendar.sec);
					break;
				case 11:
					LCD_ShowString(10,200,200,16,12,"Press WKUP to increase second. ");
				  LCD_ShowString(10,220,200,16,12,"Or touch screen to change. ");
					if(key==WKUP_PRES || (tp_dev.sta&TP_PRES_DOWN)) 
					RTC_Set(calendar.w_year,calendar.w_month,calendar.w_date,calendar.hour,calendar.min,calendar.sec + 1);
					break;		
				case 12:
					LCD_ShowString(10,200,200,16,12,"Press WKUP to decrease second. ");
				  LCD_ShowString(10,220,200,16,12,"Or touch screen to change. ");
					if(key==WKUP_PRES || (tp_dev.sta&TP_PRES_DOWN))  
					RTC_Set(calendar.w_year,calendar.w_month,calendar.w_date,calendar.hour,calendar.min,calendar.sec - 1);
					break;		
				case 13:
					LCD_ShowString(10,200,200,16,12,"            Already Adjusted!              ");
				  LCD_ShowString(10,220,200,16,12,"                                           ");
					times = 0;
				  break;
				default:
					break;
			
         
    }		
		if(t!=calendar.sec)
		{
			t=calendar.sec;
			LCD_ShowNum(60,130,calendar.w_year,4,16);									  
			LCD_ShowNum(100,130,calendar.w_month,2,16);									  
			LCD_ShowNum(124,130,calendar.w_date,2,16);	 
			switch(calendar.week)
			{
				case 0:
					LCD_ShowString(150,130,200,16,16,"Sunday   ");
					break;
				case 1:
					LCD_ShowString(150,130,200,16,16,"Monday   ");
					break;
				case 2:
					LCD_ShowString(150,130,200,16,16,"Tuesday  ");
					break;
				case 3:
					LCD_ShowString(150,130,200,16,16,"Wednesday");
					break;
				case 4:
					LCD_ShowString(150,130,200,16,16,"Thursday ");
					break;
				case 5:
					LCD_ShowString(150,130,200,16,16,"Friday   ");
					break;
				case 6:
					LCD_ShowString(150,130,200,16,16,"Saturday ");
					break;  
			}
			if(calendar.hour>=10){
	int shi = calendar.hour/10;
	LCD_ShowxNum(60,162,shi,2,16,0);
	LCD_ShowxNum(77,162,calendar.hour-shi*10,2,16,0);	
	 }else{
	LCD_ShowxNum(60,162,0,2,16,0);
	LCD_ShowxNum(77,162,calendar.hour,2,16,0);}
	LCD_ShowString(97,162,200,16,16,":");		
	if(calendar.min>=10){
	int shi = calendar.min/10;
	LCD_ShowxNum(117,162,shi,2,16,0);  
	LCD_ShowxNum(134,162,calendar.min-shi*10,2,16,0);	
	 }else{
	LCD_ShowxNum(117,162,0,2,16,0);
	LCD_ShowxNum(134,162,calendar.min,2,16,0);}
	LCD_ShowString(154,162,200,16,16,":");		
		if(calendar.sec>=10){
	int shi = calendar.sec/10;
	LCD_ShowxNum(174,162,shi,2,16,0); 
	LCD_ShowxNum(191,162,calendar.sec-shi*10,2,16,0);	
	 }else{
	LCD_ShowxNum(174,162,0,2,16,0);
	LCD_ShowxNum(191,162,calendar.sec,2,16,0);}	
	LED0=!LED0;
	     }	
		delay_ms(10);		
	
}

void countdownshow(int minute_countdown,int second_countdown,int hundred ){
if(minute_countdown>=10){
	int shi = minute_countdown/10;
	LCD_ShowxNum(90,50,shi,2,16,0);
	LCD_ShowxNum(105,50,minute_countdown-shi*10,2,16,0);	
	 }else{
	LCD_ShowxNum(90,50,0,2,16,0);
	LCD_ShowxNum(105,50,minute_countdown,2,16,0);}
	LCD_ShowString(125,50,200,16,16,":");	//分鐘
	
	if(second_countdown>=10){
	int shi = second_countdown/10;
	LCD_ShowxNum(145,50,shi,2,16,0);
	LCD_ShowxNum(160,50,second_countdown-shi*10,2,16,0);	
	 }else{
	LCD_ShowxNum(145,50,0,2,16,0);
	LCD_ShowxNum(160,50,second_countdown,2,16,0);} 
LCD_ShowString(180,50,200,16,16,".");	 //秒
	 
	if(hundred>=10){
	int shi = hundred/10;
	LCD_ShowxNum(190,50,shi,2,16,0);
	LCD_ShowxNum(210,50,hundred-shi*10,2,16,0);	
	 }else{
	LCD_ShowxNum(190,50,0,2,16,0);
	LCD_ShowxNum(210,50,hundred,2,16,0);}  //百分之一秒
}


int minute_countdown=0;
int second_countdown=0;
int hundred =0;
int ccstate =0;
void countdown(void){



       
			LCD_ShowString(10,200,200,16,12,"Begin to countdown. ");
			LCD_ShowString(10,220,200,16,12,"Press on key0 to start counting down. ");
			LCD_ShowString(10,260,200,16,12,"Touch on the top to adjust the minute and secondyou want,left lower, right higher ");
			countdownshow(minute_countdown,second_countdown,hundred);
    
	    tp_dev.scan(0);
    if(tp_dev.sta&TP_PRES_DOWN) 
    {
			 if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height)
        {
					if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<30)
					{ ccstate+=1;    
if(ccstate%2==0){LCD_ShowString(10,160,200,16,12,"Adjust minute. ");}
if(ccstate%2==1){LCD_ShowString(10,160,200,16,12,"Adjust second. ");}
					}
				
				if(tp_dev.x[0]<60&&tp_dev.y[0]>lcddev.height-60&&ccstate%2==0){
			if(minute_countdown>=1)	minute_countdown-=1;
				countdownshow(minute_countdown,second_countdown,hundred);}
				if(tp_dev.x[0]>lcddev.width -60&&tp_dev.y[0]>lcddev.height-60&&ccstate%2==0){
				  minute_countdown+=1  ; 
				countdownshow(minute_countdown,second_countdown,hundred);}
				
				if(tp_dev.x[0]<60&&tp_dev.y[0]>lcddev.height-60&&ccstate%2==1){
			if(second_countdown>=1)	second_countdown-=1;
				countdownshow(minute_countdown,second_countdown,hundred);}
				if(tp_dev.x[0]>lcddev.width -60&&tp_dev.y[0]>lcddev.height-60&&ccstate%2==1){
				  second_countdown+=1  ; 
				countdownshow(minute_countdown,second_countdown,hundred);}
				
				
				}
		}
	//調整倒計時時間長短
		if(key2 == KEY0_PRES){
		while (1){
			delay_ms(10); 
			if(minute_countdown==0&second_countdown==0&hundred==0) {break;
				LCD_ShowString(10,200,200,16,12,"Countdown ends. Press on key1 to return.");
			  //if(key2 == KEY0_PRES)LCD_Clear(WHITE);state-=1;
			}
		
				if(second_countdown==0&hundred==0){minute_countdown-=1;second_countdown=59;hundred =99;}
			/*	if(second_countdown==0){minute_countdown-=1;
		second_countdown=59;}  */
	else	if(hundred==0){
		second_countdown-=1;
		hundred =99;}else{hundred-=1;}
		
			
			
		
			countdownshow(minute_countdown,second_countdown,hundred);
		                  }
		
		}
	  				//倒計時部分結束	
}

u16 oldxs=0;;
u16 oldys=0;
u16 oldxm=0;
u16 oldym=0;
u16 oldxh=0;
u16 oldyh=0;
void sec_move(u16 a,u16 b) //???
{
	POINT_COLOR=WHITE;
	LCD_DrawLine(lcddev.width/2,lcddev.height/2,oldxs,oldys);
	POINT_COLOR=BLUE;
   LCD_DrawLine(lcddev.width/2,lcddev.height/2,a,b);
    oldxs=a;
    oldys=b;
}

void min_move(u16 a,u16 b) //???
{
	POINT_COLOR=WHITE;
	LCD_DrawLine(lcddev.width/2,lcddev.height/2,oldxm,oldym);
	POINT_COLOR=BLUE;
    LCD_DrawLine(lcddev.width/2,lcddev.height/2,a,b);
    oldxm=a;
    oldym=b;
}

void hou_move(u16 a,u16 b) //???
{
	POINT_COLOR=WHITE;
	LCD_DrawLine(lcddev.width/2,lcddev.height/2,oldxh,oldyh);
	POINT_COLOR=BLUE;
   LCD_DrawLine(lcddev.width/2,lcddev.height/2,a,b);
    oldxh=a;
    oldyh=b;
}

void time_set(u16 sec,u16 min,u16 hour) //??????
{
	int xs,ys,xm,ym,xh,yh;
	double temp;
	xs= (int) (lcddev.width/2 + 90*sin(sec*0.10472) );
	ys= (int) (lcddev.height/2 - 90*cos(sec*0.10472)  ); 
	sec_move(xs,ys); //???
          
    xm= (int) (lcddev.width/2 + 60*sin(min*0.10472) );
	ym= (int) (lcddev.height/2 - 60*cos(min*0.10472) ); 
    min_move(xm,ym); //???
	
	if(hour<=12) //???
	{
		temp=(5*hour)+(min/12);
        xh= (int) (lcddev.width/2 + 30*sin(temp*0.10472) );
        yh= (int) (lcddev.height/2 - 30*cos(temp*0.10472) ); 
        hou_move(xh,yh);
	}
	else
	{
		temp=(5*(hour-12))+(min/12);
		xh= (int) (lcddev.width/2 + 30*sin(temp*0.10472) );
		yh= (int) (lcddev.height/2 - 30*cos(temp*0.10472) ); 
		hou_move(xh,yh);
	}
}
void gui_draw_hline(u16 x0,u16 y0,u16 len,u16 color)
{
	if(len==0)return;
	LCD_Fill(x0,y0,x0+len-1,y0,color);	
}
void gui_fill_circle(u16 x0,u16 y0,u16 r,u16 color)
{											  
	u32 i;
	u32 imax = ((u32)r*707)/1000+1;
	u32 sqmax = (u32)r*(u32)r+(u32)r/2;
	u32 x=r;
	gui_draw_hline(x0-r,y0,2*r,color);
	for (i=1;i<=imax;i++) 
	{
		if ((i*i+x*x)>sqmax)// draw lines from outside  
		{
 			if (x>imax) 
			{
				gui_draw_hline (x0-i+1,y0+x,2*(i-1),color);
				gui_draw_hline (x0-i+1,y0-x,2*(i-1),color);
			}
			x--;
		}
		// draw lines from inside (center)  
		gui_draw_hline(x0-x,y0+i,2*x,color);
		gui_draw_hline(x0-x,y0-i,2*x,color);
	}
}  
 
int state =0;
int main(void)
 { 
	u8 m = 0;
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	delay_init();	    	 //延时函数初始化	  
	uart_init(9600);	 	//串口初始化为9600
	LED_Init();				//初始化与LED连接的硬件接口
 	LCD_Init();				//初始化LCD
	usmart_dev.init(72);	//初始化USMART		
  KEY_Init();				//?????		 	
	tp_dev.init();			//??????	 
	POINT_COLOR=RED;//设置字体为红色 
	while(RTC_Init())		//RTC初始化	，一定要初始化成功
	{ 
		LCD_ShowString(60,130,200,16,16,"RTC ERROR!   ");	
		delay_ms(800);
		LCD_ShowString(60,130,200,16,16,"RTC Trying...");	
	}		    						
	//显示时间
	POINT_COLOR=BLUE;//设置字体为蓝色					 
//	LCD_ShowString(60,130,200,16,16,"    -  -     ");	   
	
	
	
	    
	while(1)
	{
		key2=KEY_Scan(0);//這個被用在倒計時裡面
	
		
    if(key2==KEY1_PRES) 
    {
         state +=1;LCD_Clear(WHITE);}
     
    
		
		if(state%3==0){ POINT_COLOR=BLUE;ShowTime(key2);}



     else if (state%3==1){ POINT_COLOR=BLUE;countdown();}
		 
		 else{ time_set( calendar.sec,calendar.min,calendar.hour); 
			 POINT_COLOR=RED;
		 LCD_ShowxNum(lcddev.width/2,lcddev.height/2-90-16,12,2,16,0);
		 LCD_ShowxNum(lcddev.width/2,lcddev.height/2+90,6,2,16,0);
		 LCD_ShowxNum(lcddev.width/2-90-16,lcddev.height/2,9,2,16,0);
		 LCD_ShowxNum(lcddev.width/2+90,lcddev.height/2,3,2,16,0);
		 }
		 
		if(LED1 == 0)
		{
		  LED1 = 1;
			delay_ms(200);
			LED1 = 0;
			m += 1;
		}
		delay_ms(10);	
		if(KEY0==0)
		{
			LED1=1;
		}
    //printf("%d", count);
    if(m > 50)            //只会亮10s,跟时钟是同步走的
		{
			LED1 = 1;
			m = 0;
		}
		 
		 
}	


}
