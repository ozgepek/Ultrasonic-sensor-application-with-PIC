sbit LCD_RS at RD2_bit;
sbit LCD_EN at RD3_bit;
sbit LCD_D4 at RD4_bit;
sbit LCD_D5 at RD5_bit;
sbit LCD_D6 at RD6_bit;
sbit LCD_D7 at RD7_bit;

sbit LCD_RS_Direction at TRISD2_bit;
sbit LCD_EN_Direction at TRISD3_bit;
sbit LCD_D4_Direction at TRISD4_bit;
sbit LCD_D5_Direction at TRISD5_bit;
sbit LCD_D6_Direction at TRISD6_bit;
sbit LCD_D7_Direction at TRISD7_bit;

void main()
{
  int i;
  char txt[7];
  Lcd_Init();
  Lcd_Cmd(_LCD_CLEAR);
  Lcd_Cmd(_LCD_CURSOR_OFF);

  TRISB = 0b00010000;
  T1CON = 0b00100000;

  while(1)
  {
   TMR1H = 0;
   TMR1L = 0;

    PORTB.RB0 = 1;
    Delay_us(10);
    PORTB.RB0 = 0;

    while(PORTB.RB4==0);
    T1CON.F0 = 1;
    while(PORTB.RB4==1);
    T1CON.F0 = 0;

    i = (TMR1L | (TMR1H<<8));
    i = i/58;
    if(i>=2 && i<=400)
    {
      IntToStr(i,txt);
      Ltrim(txt);
      Lcd_Cmd(_LCD_CLEAR);
      Lcd_Out(1,1,"Mesafe = ");
      Lcd_Out(1,12,txt);
      Lcd_Out(1,15,"cm");
    }
    else
    {
      Lcd_Cmd(_LCD_CLEAR);
      Lcd_Out(1,1,"Aralik disi");
    }
    Delay_ms(500);
  }
}