#include <htc.h>
//__CONFIG (FOSC_XT & WDTE_OFF & LVP_OFF);
__CONFIG (FOSC_INTRC_NOCLKOUT & WDTE_OFF & LVP_OFF & PWRTE_OFF);

#define _XTAL_FREQ 8000000

#define PIR RA1
#define CO2 RA0
#define EYE RD0
#define CALL RC2
#define ALCOHOL RD7

#define ENGINE RD6

#define VIBRATION RD1
#define KEY RC0
#define LCD_RS RB0
#define LCD_E RB1

bit sendGPS = 0, recEn = 0;
char welcome[]= "VEHICLE SECURITY";
char assistance[]="     SYSTEM     ";
char window[]="WINDOW OPEN     ";
char alcohol[]="NO DRUNK n DRIVE";
char eng_on1[]="   ENGINE ON    ";
char eng_on[]=" HAPPY DRIVING!   ";
char BLANK[]="                  ";
char no_one[]="  NOBODY INSIDE  ";
char eng_off[]="  ENGINE OFF      ";

char sleep[]="DO NOT SLEEP     ";
char sleep1[]="WHILE DRIVING    ";
char speed[]="SPEED LIMITED     ";
char gps[]="";
char accident1[]="ACCIDENT OCCURED @ ";

char no_gas[]="NO EXCESS CO2   ";
char AT1[]="AT+CMGF=1";
char AT2[]="AT+CMGS=\"+918281596573\"\r";
char AT4[]="952.8631N,7682.12693E";

int flag = 0;
int j,i=0,msg_sent = 0;
void lcd_func(int rs,int dat)
{
    LCD_RS = rs;
    PORTB = PORTB & 0xC3;
    PORTB  = PORTB | ((dat & 0xF0)>>2);
    LCD_E =1;
    __delay_ms(1);
    LCD_E =0;
    __delay_ms(1);

    LCD_RS = rs;
    PORTB = PORTB & 0xC3;
    PORTB  = PORTB | ((dat<<4 & 0xF0)>>2);
    LCD_E =1;
    __delay_ms(1);
    LCD_E =0;
    __delay_ms(1);

    }

void lcd_initialise(void)
{
       __delay_ms(20); // wait for more than 15ms
       lcd_func(0,0x03);
       __delay_ms(5); //wait for more than 4 ms
       lcd_func(0,0x03);
       __delay_ms(1); //wait for more than 100micro seconds
       lcd_func(0,0x03);
       __delay_ms(40);

       lcd_func(0,0x02); // 4 bit enable
       lcd_func(0,0x28);
       lcd_func(0,0x01); // clear screen
       lcd_func(0,0x0C); // display on cursor off



}
void main(void)
{
    IRCF0 = 1;
    IRCF1 = 1;
    IRCF2 = 1;
    OSTS = 0;
    SCS = 1;

    

    ANSELH = 0X00;
    TRISB = 0x00;
    PORTB = 0x00;

     TRISC6 = 0;
    TRISC7 = 1;
//    GIE = 1;
//    PEIE = 1;
    RCIE = 1;
    SPEN = 1;
    TXEN = 1;
    CREN = 1;
    SYNC = 0;
    BRGH = 1;
    BRG16 = 0;
    SPBRG = 51;

    ANSEL = 0x00;

    ANS1=0;
    TRISA1 = 1;
    RA1 = 0;
    TRISE2 = 0;
    RE2 =0;
    TRISD0 = 1;
    RD0=0;
    TRISD7 = 1;
    RD7 = 0;
    TRISD1 = 1;
    RD1 = 0;
    TRISC0 = 1;
    RC0 = 0;
    TRISD6 = 0;
    RD6 =0;
    TRISD5 = 0;
    RD5=0;
    TRISD7 = 1;
    RD7= 0;
    TRISA2 = 0;
    TRISC2 = 1;
    RA2 =0;
    RC2 = 0;
    TRISA3 =0;
    RA3=0;




    lcd_initialise();
    lcd_func(0,0x01);
    lcd_func(0,0x80);
    for(j=0;  welcome[j] != '\0' ; j++)
    lcd_func(1,welcome[j] );

    lcd_func(0,0xC0);
    for(j=0;  assistance[j] != '\0' ; j++)
    lcd_func(1,assistance[j] );

    __delay_ms(1500);
    while(1)
    {
        if(KEY == 0)
        {
            RD6 = 0;
            if(RA1 == 1)
            {
               if(CO2 == 1)
               {
                   RA2 = 1;
                   RA3 = 0;
                   lcd_func(0,0x80);
                   for(j=0;  window[j] != '\0' ; j++)
                   lcd_func(1,window[j] );
                   lcd_func(0,0xC0);

                     for(j=0;  BLANK[j] != '\0' ; j++)
                    lcd_func(1,BLANK[j] );
                    __delay_ms (1500);
               }
               else if(CO2  == 0)
               {

                   RA3 = 0;
                   RA2 = 0;
//                   lcd_func(0,0x01);
                   lcd_func(0,0x80);
                   for(j=0;  no_gas[j] != '\0' ; j++)
                   lcd_func(1,no_gas[j] );
                   lcd_func(0,0xC0);

                   for(j=0;  BLANK[j] != '\0' ; j++)
                    lcd_func(1,BLANK[j] );
                    __delay_ms (1500);
               }

           
            }
            else if(RA1 == 0)
            {
               lcd_func(0,0x80);
                for(j=0;  no_one[j] != '\0' ; j++)
                lcd_func(1,no_one[j] );

                lcd_func(0,0xC0);
                for(j=0;  eng_off[j] != '\0' ; j++)
                lcd_func(1,eng_off[j] );
                    __delay_ms (1500);
 
            }

        }
        else if (KEY == 1)
        {
            if(ALCOHOL == 0)
            {
                RD6 = 1;
                if(VIBRATION == 1)
                {
                    lcd_func(0,0x80);
                    for(j=0;  accident1[j] != '\0' ; j++)
                    lcd_func(1,accident1[j] );

                    lcd_func(0,0xC0);
                    for(j=0;  BLANK[j] != '\0' ; j++)
                    lcd_func(1,BLANK[j] );
                    
//================================
                    for(j=0;  AT1[j] != '\0' ; j++)
                    {
                        TXREG = AT1[j];
                        while(TRMT == 0);
                    }
                    TXREG = 0x0D;
                    while(TRMT == 0);
                    TXREG = 0x0A;
                    while(TRMT == 0);
                    __delay_ms(100);

                    RE2 = 1;
                    __delay_ms(100);
                    RE2=0;

                    for(j=0;  AT2[j] != '\0' ; j++)
                    {
                        TXREG = AT2[j];
                        while(TRMT == 0);
                    }
                    TXREG = 0x0D;
                    while(TRMT == 0);
                    TXREG = 0x0A;
                    while(TRMT == 0);
                    __delay_ms(100);

                    RE2 = 1;
                    __delay_ms(100);
                    RE2=0;

                    for(j=0;  accident1[j] != '\0' ; j++)
                    {
                        TXREG = accident1[j];
                        while(TRMT == 0);
                    }
                    for(j=0;  AT4[j] != '\0' ; j++)
                    {
                        TXREG = AT4[j];
                        while(TRMT == 0);
                    }

                    TXREG = 0x0D;
                    while(TRMT == 0);
                    TXREG = 0x0A;
                    while(TRMT == 0);
                    __delay_ms(100);

                    TXREG = 0x1A;
                    while(TRMT == 0);
                    __delay_ms(100);

                    RE2 = 1;
                    __delay_ms(100);
                    RE2=0;

                    msg_sent = 1;
                    while (msg_sent == 1);
//        sendGPS = 1;
//
//        while (sendGPS == 1)
//        {
//            if (RCIF == 1)
//            {
//                if (RCREG == 'L')
//                {
//                    recEn = 1;
//                }
//                if(RCREG == 'E')
//                {
//                    recEn = 0;
//                    sendGPS = 0;
//                }
//                if (recEn == 1)
//                {
//                    if (RCREG != 'L' || RCREG != ',')
//                    {
//                        TXREG = RCREG;
//                        while (!TRMT);
//                    }
//                }
//                RCIF = 0;
//            }
//        }
                }
//          ==============================================
                if(EYE == 1)
                    {
                        RE2 = 1;
                        __delay_ms(100);
                        RE2=0;
                        __delay_ms(100);
                         lcd_func(0,0x80);
                        for(j=0;  sleep[j] != '\0' ; j++)
                         lcd_func(1,sleep[j] );
                          lcd_func(0,0xC0);
                     for(j=0;  sleep1[j] != '\0' ; j++)
                     lcd_func(1,sleep1[j] );
                    __delay_ms (1500);
                    }
                    else if (EYE == 0)
                    {
                        RE2 = 0;

                    }
                if(CALL ==1)
                {
                    RD5 = 1;
                 lcd_func(0,0x80);
                     for(j=0;  speed[j] != '\0' ; j++)
                     lcd_func(1,speed[j] );
                 lcd_func(0,0xC0);
                     for(j=0;  BLANK[j] != '\0' ; j++)
                     lcd_func(1,BLANK[j] );
                    __delay_ms (1500);
                }
                else if(CALL == 0)
                {
                    RD5 = 0;
                }
                if((CALL == 0)&& (VIBRATION ==0) && (EYE == 0))
                {
                    lcd_func(0,0x80);
                     for(j=0;  eng_on[j] != '\0' ; j++)
                     lcd_func(1,eng_on[j] );
                 lcd_func(0,0xC0);
                     for(j=0;  eng_on1[j] != '\0' ; j++)
                     lcd_func(1,eng_on1[j] );
                    __delay_ms (1500);
                }
            }
            else if(ALCOHOL == 1)
            {
                RD6 = 0;
                 lcd_func(0,0x80);
                for(j=0;  alcohol[j] != '\0' ; j++)
                lcd_func(1,alcohol[j] );

                lcd_func(0,0xC0);
                for(j=0;  BLANK[j] != '\0' ; j++)
                lcd_func(1,BLANK[j] );
                    __delay_ms (1500);

            }


        }

    }
}
