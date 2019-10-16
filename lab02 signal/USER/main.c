#include   "stm32f10x.h"
#include   "sys.h"
#include   "delay.h"
int i =0;
// 对应关系 ： PA8 —— led0      PD2 —— led1        IO状态为低时灯亮，为高时灭
int main()
{		 

	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOD, ENABLE);	 //使能PA,PD端口时钟

	delay_init();	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				 //LED0-->PA.8 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.8	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	
  GPIO_Init(GPIOD, &GPIO_InitStructure);	
	GPIO_SetBits(GPIOD,GPIO_Pin_2); 
	  
    for ( i =0;i<6;i++)
	{  
	   delay_ms(20);
		 GPIO_ResetBits(GPIOA,GPIO_Pin_8);
		 GPIO_SetBits(GPIOD,GPIO_Pin_2);
		 delay_ms(20);			 
		 GPIO_ResetBits(GPIOD,GPIO_Pin_2);
		 GPIO_SetBits(GPIOA,GPIO_Pin_8);	
    
		} //两个灯交替慢速亮，表示启动中
	     GPIO_SetBits(GPIOD,GPIO_Pin_2);
		
	 for ( i =0;i<6;i++)
	{  
	   delay_ms(20);
		GPIO_SetBits(GPIOA,GPIO_Pin_8);
		 
		 delay_ms(20);			 
		  GPIO_ResetBits(GPIOA,GPIO_Pin_8);
		 	
   
		}  //绿灯闪，表示正常运行
	      GPIO_SetBits(GPIOA,GPIO_Pin_8);
		       
	             for ( i =0;i<6;i++)
	            {  
	   delay_ms(20);
		 GPIO_ResetBits(GPIOD,GPIO_Pin_2);
		 
		 delay_ms(20);			 
		 GPIO_SetBits(GPIOD,GPIO_Pin_2); 
			
		              } //红灯低速闪，表示出错
	       for ( i =0;i<6;i++)
	{  
	    delay_ms(5);
		  GPIO_SetBits(GPIOD,GPIO_Pin_2);
		 
		  delay_ms(5);			 
		  GPIO_ResetBits(GPIOD,GPIO_Pin_2);
		
		} //红灯快速闪，表示出现严重错误，系统即将崩溃
	                         }
 
//void delay(void)
//{
//	int i = 0,j = 0;
//	for(i=0;i<2000;i++)
//		for(j=0;j<2000;j++);
//}
