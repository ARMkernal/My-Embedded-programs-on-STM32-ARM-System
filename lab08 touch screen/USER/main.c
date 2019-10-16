#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "key.h"
#include "24cxx.h"
#include "myiic.h"
#include "touch.h"
void Load_Draw_Dialog(void)
{
    LCD_Clear(WHITE);//??
    POINT_COLOR=BLUE;//???????
    LCD_ShowString(0,0,200,16,16,"Draw circular");
    LCD_ShowString(lcddev.width-100,0,200,16,16,"Draw line");//??????
    LCD_ShowString(0,lcddev.height-24,200,16,16,"Sign Name");
    LCD_ShowString(lcddev.width-100,lcddev.height-24,200,16,16,"Draw Triangle");
    POINT_COLOR=RED;//??????
}
////////////////////////////////////////////////////////////////////////////////
//?????????
//????
//x0,y0:??
//len:???
//color:??
void gui_draw_hline(u16 x0,u16 y0,u16 len,u16 color)
{
    if(len==0)return;
    LCD_Fill(x0,y0,x0+len-1,y0,color);
}
void gui_draw_triangle(u16 x0, u16 y0,u16 x1, u16 y1,u16 x2, u16 y2,u16 color){
    LCD_DrawLine(x0,y0,x1,y1);
    LCD_DrawLine(x1,y1,x2,y2);
    LCD_DrawLine(x0,y0,x2,y2);}
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
u16 my_abs(u16 x1,u16 x2)
{
    if(x1>x2)return x1-x2;
    else return x2-x1;
}
//?????
//(x1,y1),(x2,y2):???????
//size:???????
//color:?????
void lcd_draw_bline(u16 x1, u16 y1, u16 x2, u16 y2,u8 size,u16 color)
{
    u16 t;
    int xerr=0,yerr=0,delta_x,delta_y,distance;
    int incx,incy,uRow,uCol;
    if(x1<size|| x2<size||y1<size|| y2<size)return;
    delta_x=x2-x1; //??????
    delta_y=y2-y1;
    uRow=x1;
    uCol=y1;
    if(delta_x>0)incx=1; //??????
    else if(delta_x==0)incx=0;//???
    else {incx=-1;delta_x=-delta_x;}
    if(delta_y>0)incy=1;
    else if(delta_y==0)incy=0;//???
    else{incy=-1;delta_y=-delta_y;}
    if( delta_x>delta_y)distance=delta_x; //?????????
    else distance=delta_y;
    for(t=0;t<=distance+1;t++ )
    {
        gui_fill_circle(uRow,uCol,size,color);//??
        xerr+=delta_x ;
        yerr+=delta_y ;
        if(xerr>distance)
        {
            xerr-=distance;
            uRow+=incx;
        }
        if(yerr>distance)
        {
            yerr-=distance;
            uCol+=incy;
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
//5???????
//?????????
void rtp_test(void)
{
    u8 key;
    u8 i=0;
    u8 key1 =0;
    u8 key2=0;
    u8 key3=0;
    u8 key4=0;
    u8 x=0;
    u8 y=0; while(1)
    {
        key=KEY_Scan(0);
        tp_dev.scan(0);
        if(tp_dev.sta&TP_PRES_DOWN) //??????
        {
            if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height)
            {
                x= tp_dev.x[0];
                y= tp_dev.y[0];

                if(tp_dev.x[0]<30&&tp_dev.y[0]<30){

                    Load_Draw_Dialog();
                    gui_fill_circle(50,50,10,YELLOW);
                    key1=1;
                    key2=0;
                    key3=0;
                    key4=0;

                    delay_ms(1000);
                    continue;
                }

                if(tp_dev.x[0]>(lcddev.width-30)&&tp_dev.y[0]<30){

                    Load_Draw_Dialog();

                    key1=0;
                    key2=1;
                    key3=0;
                    key4=0;
                    LCD_ShowString(60,150,200,16,16,"Write your name");
                    delay_ms(1000);
                    continue;
                }




                if (tp_dev.x[0]<30&&tp_dev.y[0]>(lcddev.height-30)){
                    Load_Draw_Dialog();
                    key1=0;
                    key2=0;key3 =1;
                    key4=0;

                    LCD_Fill( 0,lcddev.height-30,100,lcddev.height-20,YELLOW );
                    LCD_ShowString(60,150,200,16,16,"I am Qiu Wei");

                    delay_ms(1000);
                    continue;
                }
                if (tp_dev.x[0]>(lcddev.width-30)&&tp_dev.y[0]>(lcddev.height-30)){
                    Load_Draw_Dialog();
                    key1=0;
                    key2=0;key3 =0;
                    key4=1;
                    LCD_Fill( lcddev.width-100,lcddev.height-30,lcddev.width, lcddev.height
                                                                              -20,YELLOW );
                    gui_draw_triangle(50,50,100,100,50,100,RED);

                    delay_ms(1000);
                    continue;
                }

                // if(tp_dev.x[0]>(lcddev.width-24)&&tp_dev.y[0]<16)Load_Draw_Dialog();//
                // else TP_Draw_Big_Point(tp_dev.x[0],tp_dev.y[0],YELLOW); //
                //delay_ms(1);
            }
        }else delay_ms(10); //
        if(key==KEY0_PRES) //
        {
            LCD_Clear(WHITE);//
            TP_Adjust(); //
            TP_Save_Adjdata();
            Load_Draw_Dialog();
        }
        i++;
        if(i%20==0)LED0=!LED0;
    }
}
const u16 POINT_COLOR_TBL[CT_MAX_TOUCH]={RED,GREEN,BLUE,BROWN,GRED};
void ctp_test(void)
{
    u8 t=0;
    u8 i=0;
    u16 lastpos[5][2]; //
    while(1)
    {
        tp_dev.scan(0);
        for(t=0;t<CT_MAX_TOUCH;t++)//
        {
            if((tp_dev.sta)&(1<<t))//
            {
                if(tp_dev.x[t]<lcddev.width&&tp_dev.y[t]<lcddev.height)//
                {
                    if(lastpos[t][0]==0XFFFF)
                    {
                        lastpos[t][0] = tp_dev.x[t];
                        lastpos[t][1] = tp_dev.y[t];
                    }

                    lcd_draw_bline(lastpos[t][0],lastpos[t][1],tp_dev.x[t],tp_dev.y[t],2,POINT_COLOR_TBL[t]
                    );//
                    lastpos[t][0]=tp_dev.x[t];
                    lastpos[t][1]=tp_dev.y[t];
                    if(tp_dev.x[t]>(lcddev.width-24)&&tp_dev.y[t]<16)
                    {
                        Load_Draw_Dialog();//
                    }
                }
            }else lastpos[t][0]=0XFFFF;
        }

        delay_ms(5);i++; if(i%20==0)LED0=!LED0;
    }
}
int main(void)
{
    delay_init(); //
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //
    uart_init(9600); //
    LED_Init(); //
    LCD_Init(); //
    KEY_Init(); //
    tp_dev.init(); //
    POINT_COLOR=RED;//???????
    LCD_ShowString(60,50,200,16,16,"Mini STM32");
    LCD_ShowString(60,70,200,16,16,"TOUCH TEST");
    LCD_ShowString(60,90,200,16,16,"CSE@SUSTech");
    LCD_ShowString(60,110,200,16,16,"2018/10/30");
    if(tp_dev.touchtype!=0XFF)LCD_ShowString(60,180,200,16,16,"Press KEY0 to Adjust");//
    if(tp_dev.touchtype!=0XFF) LCD_ShowString(60,130,200,16,16,"This is a ");
    if(tp_dev.touchtype&0X80) LCD_ShowString(200,130,200,16,16,"CTP");//
    else LCD_ShowString(200,130,200,16,16,"RTP");//




    delay_ms(1500); Load_Draw_Dialog();
    if(tp_dev.touchtype&0X80) ctp_test(); //
    else
        rtp_test(); //
}