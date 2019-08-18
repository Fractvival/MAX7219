#include "LedControl.h"

// DATA(DIN), CLOCK(CLK), CS
// Digital piny bez oznaceni D ! pouze cisla
// Defaultni hodnoty: 12,11,10
// Posledni hodnota je pocet segmentu
// Cislo segmentu je v kodu pod oznacenim "adress/addr"
LedControl lc=LedControl(12,11,10,4);

unsigned long delaytime=500;
int j = 3;


void setup() 
{
  int devices=lc.getDeviceCount();
  for( int address = 0; address < devices; address++ ) 
  {
    lc.shutdown(address,false);
    lc.setIntensity(address,4);
    ShowNumber(address,10);
    delay(1000);
    lc.clearDisplay(address);
  }
}

char NUMBER_X[] = 
{B11111111,
B11111111,
B11111111,
B11111111,
B11111111,
B11111111,
B11111111,
B11111111};


char NUMBER_0[] = 
{B00111100,
B00100100,
B00100100,
B00100100,
B00100100,
B00100100,
B00100100,
B00111100};


char NUMBER_1[] = 
{B00000100,
B00000100,
B00000100,
B00000100,
B00000100,
B00000100,
B00000100,
B00000100};


char NUMBER_2[] = 
{B00111100,
B00000100,
B00000100,
B00111100,
B00100000,
B00100000,
B00100000,
B00111100};

char NUMBER_3[] = 
{B00111100,
B00000100,
B00000100,
B00111100,
B00000100,
B00000100,
B00000100,
B00111100};

char NUMBER_4[] = 
{B00100100,
B00100100,
B00100100,
B00111100,
B00000100,
B00000100,
B00000100,
B00000100};

char NUMBER_5[] = 
{B00111100,
B00100000,
B00100000,
B00111100,
B00000100,
B00000100,
B00000100,
B00111100};

char NUMBER_6[] = 
{B00111100,
B00100000,
B00100000,
B00111100,
B00100100,
B00100100,
B00100100,
B00111100};

char NUMBER_7[] = 
{B00111100,
B00000100,
B00000100,
B00000100,
B00000100,
B00000100,
B00000100,
B00000100};

char NUMBER_8[] = 
{B00111100,
B00100100,
B00100100,
B00111100,
B00100100,
B00100100,
B00100100,
B00111100};

char NUMBER_9[] = 
{B00111100,
B00100100,
B00100100,
B00111100,
B00000100,
B00000100,
B00000100,
B00000100};

void SetDigit( int addr, char * digit )
{
   for ( int i = 0; i < 8; i++ )
   {
      lc.setRow(addr,i,(byte)digit[i]);
   }
}


void ShowNumber(int addr, int number)
{
  switch( number )
  {
    case 0:
    {
      SetDigit(addr,NUMBER_0);
      break;
    }
    case 1:
    {
      SetDigit(addr,NUMBER_1);
      break;
    }
    case 2:
    {
      SetDigit(addr,NUMBER_2);
      break;
    }
    case 3:
    {
      SetDigit(addr,NUMBER_3);
      break;
    }
    case 4:
    {
      SetDigit(addr,NUMBER_4);
      break;
    }
    case 5:
    {
      SetDigit(addr,NUMBER_5);
      break;
    }
    case 6:
    {
      SetDigit(addr,NUMBER_6);
      break;
    }
    case 7:
    {
      SetDigit(addr,NUMBER_7);
      break;
    }
    case 8:
    {
      SetDigit(addr,NUMBER_8);
      break;
    }
    case 9:
    {
      SetDigit(addr,NUMBER_9);
      break;
    }
    case 10:
    {
      SetDigit(addr,NUMBER_X);
      break;
    }
    break; 
  }
}



void loop() 
{
  
   for ( int i = 0; i < 10; i++ )
   {
     ShowNumber(j,i);
     delay(delaytime);
   }
   
   j--;

   if ( j == -1 )
    j = 3;

}
