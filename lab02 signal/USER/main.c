#include   "stm32f10x.h"
#include   "sys.h"
#include   "delay.h"
int i =0;
// ��Ӧ��ϵ �� PA8 ���� led0      PD2 ���� led1        IO״̬Ϊ��ʱ������Ϊ��ʱ��
int main()
{		 

	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOD, ENABLE);	 //ʹ��PA,PD�˿�ʱ��

	delay_init();	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				 //LED0-->PA.8 �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOA.8	

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
    
		} //�����ƽ�������������ʾ������
	     GPIO_SetBits(GPIOD,GPIO_Pin_2);
		
	 for ( i =0;i<6;i++)
	{  
	   delay_ms(20);
		GPIO_SetBits(GPIOA,GPIO_Pin_8);
		 
		 delay_ms(20);			 
		  GPIO_ResetBits(GPIOA,GPIO_Pin_8);
		 	
   
		}  //�̵�������ʾ��������
	      GPIO_SetBits(GPIOA,GPIO_Pin_8);
		       
	             for ( i =0;i<6;i++)
	            {  
	   delay_ms(20);
		 GPIO_ResetBits(GPIOD,GPIO_Pin_2);
		 
		 delay_ms(20);			 
		 GPIO_SetBits(GPIOD,GPIO_Pin_2); 
			
		              } //��Ƶ���������ʾ����
	       for ( i =0;i<6;i++)
	{  
	    delay_ms(5);
		  GPIO_SetBits(GPIOD,GPIO_Pin_2);
		 
		  delay_ms(5);			 
		  GPIO_ResetBits(GPIOD,GPIO_Pin_2);
		
		} //��ƿ���������ʾ�������ش���ϵͳ��������
	                         }
 
//void delay(void)
//{
//	int i = 0,j = 0;
//	for(i=0;i<2000;i++)
//		for(j=0;j<2000;j++);
//}
