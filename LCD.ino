// VERZE 19.8.2019
// 
// sestrojeno pro segmenty 8x8 pixelu !
//
// LEDControl
// Eberhard Fahle
// 1.0.6
#include "LedControl.h"

// DATA(DIN), CLOCK(CLK), CS
// Digital piny bez oznaceni D ! pouze cisla
// Defaultni hodnoty: 12(DIN),11(CLK),10(CS)
// Posledni hodnota je pocet segmentu! pocitano od 1
//
LedControl lc = LedControl(12,11,10,4);

/////////////////////////////////////////
// DEFINICE (pomocnych) PROMENNYCH
//

// Pauza mezi testem segmentu
//
int delayTest = 150;
//
// Pauza mezi ctenim tlacitka
//
int delayButton = 80;
//
// Pauza fce loop
//
int delayLoop = 40;


// Hlavni pocitadlo ( materialu, tedy flasek :) )
//
int Count = 0;

// Intenzita svitivosti
//
int Light = 8;


// Pocitaci "tlacitko"
// Klasicke zapojeni tlacitka s 10k odporem na digital pin 
//
int Button = 4;
//
// RESET tlacitko
//
int resetButton = 3;


// Zarovnani vypisu
// 0=leva, 1=prava    strana
//
int Align = 0;


///////////////////////////
// NASTAVENI SEGMENTU
//
void setup() 
{
  delay(300);
  Serial.begin(9600);
  // Do promenne "devices" zjistim pocet segmentu (nastaveno vyse)
  //
  int devices=lc.getDeviceCount();

  // Abychom mohli pracovat s vice segmenty, je potreba je
  // nejprve vsechny inicializovat a pri te prilezitosti i
  // otestovat, zda-li sviti vsechny pixely
  //
  for( int address = 0; address < devices; address++ ) 
  {
    // Nad segmentem pozastavime fci pro zapinani sporice
    lc.shutdown(address,false);
    // Intenzita svitivosti 0..15
    lc.setIntensity(address,Light);
    // Zapne vsechny pixely segmentu ADDRESS
    ShowNumber(address,10);
    delay(delayTest);
    // Nyni segment "zhasneme"
    lc.clearDisplay(address);
  }

  pinMode(Button,INPUT_PULLUP);
  digitalWrite(Button,LOW);
  
  ///// PRO AKTIVACI RESET TLACITKA NUTNO TUTO CAST ODKOMENTOVAT ! 
  /*
  pinMode(resetButton,INPUT_PULLUP);
  digitalWrite(resetButton,LOW);
  */

  
  Show( 0 );
  
}

////////////////////////////////
// DEFINICE CISEL SEGMENTU
//


// NUMBER_X je pouzit pro test pixelu
// Dojde tedy k aktivaci vsech pixelu
//
byte NUMBER_X[] = 
{B11111111,
B11111111,
B11111111,
B11111111,
B11111111,
B11111111,
B11111111,
B11111111};


byte NUMBER_0[] = 
{B00111100,
B00100100,
B00100100,
B00100100,
B00100100,
B00100100,
B00100100,
B00111100};


byte NUMBER_1[] = 
{B00000100,
B00000100,
B00000100,
B00000100,
B00000100,
B00000100,
B00000100,
B00000100};


byte NUMBER_2[] = 
{B00111100,
B00000100,
B00000100,
B00111100,
B00100000,
B00100000,
B00100000,
B00111100};

byte NUMBER_3[] = 
{B00111100,
B00000100,
B00000100,
B00111100,
B00000100,
B00000100,
B00000100,
B00111100};

byte NUMBER_4[] = 
{B00100100,
B00100100,
B00100100,
B00111100,
B00000100,
B00000100,
B00000100,
B00000100};

byte NUMBER_5[] = 
{B00111100,
B00100000,
B00100000,
B00111100,
B00000100,
B00000100,
B00000100,
B00111100};

byte NUMBER_6[] = 
{B00111100,
B00100000,
B00100000,
B00111100,
B00100100,
B00100100,
B00100100,
B00111100};

byte NUMBER_7[] = 
{B00111100,
B00000100,
B00000100,
B00000100,
B00000100,
B00000100,
B00000100,
B00000100};

byte NUMBER_8[] = 
{B00111100,
B00100100,
B00100100,
B00111100,
B00100100,
B00100100,
B00100100,
B00111100};

byte NUMBER_9[] = 
{B00111100,
B00100100,
B00100100,
B00111100,
B00000100,
B00000100,
B00000100,
B00000100};




// Primo zobrazi, radek po radku, zvolene cislo
// z predchozich definic cisel..
//
void SetDigit( int addr, byte * digit )
{
  // plati pro segment 8x8 pixelu
  for ( int i = 0; i < 8; i++ )
  {
    lc.setRow(addr,i,(byte)digit[i]);
  }
}

// Protrideni pozadavku pro zobrazeni cisla
//
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
    // ZDE pri splneni "10" dojde k rozsviceni vsech pixelu
    case 10:
    {
      SetDigit(addr,NUMBER_X);
      break;
    }
    // break switche
    break; 
  }
  // fce je "void" tudiz nic nevraci..
}



///////////////////////////////
// ZOBRAZUJE CISLA NA DISPLEJI
//
void Show( int count )
{
  int devices = lc.getDeviceCount();

  for ( int i = 0; i < devices; i++ )
  {
    lc.clearDisplay(i);
  }

  if ( Align == 0 )
  {
    if ( Count < 10 )
    {
      ShowNumber( devices-1, Count );
    }
    if ( (Count > 9) && (Count < 100) )
    {
      String buffNumber = (String)Count;
      buffNumber.c_str();
      String buff1Number = (String)buffNumber[0];
      String buff2Number = (String)buffNumber[1];
      ShowNumber( devices-1, buff1Number.toInt() );
      ShowNumber( devices-2, buff2Number.toInt() );
    }
    if ( (Count > 99) && (Count < 1000) )
    {
      String buffNumber = (String)Count;
      buffNumber.c_str();
      String buff1Number = (String)buffNumber[0];
      String buff2Number = (String)buffNumber[1];
      String buff3Number = (String)buffNumber[2];
      ShowNumber( devices-1, buff1Number.toInt() );
      ShowNumber( devices-2, buff2Number.toInt() );
      ShowNumber( devices-3, buff3Number.toInt() );
    }
    if ( (Count > 999) && (Count < 10000) )
    {
      String buffNumber = (String)Count;
      buffNumber.c_str();
      String buff1Number = (String)buffNumber[0];
      String buff2Number = (String)buffNumber[1];
      String buff3Number = (String)buffNumber[2];
      String buff4Number = (String)buffNumber[3];
      ShowNumber( devices-1, buff1Number.toInt() );
      ShowNumber( devices-2, buff2Number.toInt() );
      ShowNumber( devices-3, buff3Number.toInt() );
      ShowNumber( devices-4, buff4Number.toInt() );
    }
  }
  else
  {
    if ( Count < 10 )
    {
      ShowNumber( 0, Count );
    }
    if ( (Count > 9) && (Count < 100) )
    {
      String buffNumber = (String)Count;
      buffNumber.c_str();
      String buff1Number = (String)buffNumber[0];
      String buff2Number = (String)buffNumber[1];
      ShowNumber( 1, buff1Number.toInt() );
      ShowNumber( 0, buff2Number.toInt() );
    }
    if ( (Count > 99) && (Count < 1000) )
    {
      String buffNumber = (String)Count;
      buffNumber.c_str();
      String buff1Number = (String)buffNumber[0];
      String buff2Number = (String)buffNumber[1];
      String buff3Number = (String)buffNumber[2];
      ShowNumber( 2, buff1Number.toInt() );
      ShowNumber( 1, buff2Number.toInt() );
      ShowNumber( 0, buff3Number.toInt() );
    }
    if ( (Count > 999) && (Count < 10000) )
    {
      String buffNumber = (String)Count;
      buffNumber.c_str();
      String buff1Number = (String)buffNumber[0];
      String buff2Number = (String)buffNumber[1];
      String buff3Number = (String)buffNumber[2];
      String buff4Number = (String)buffNumber[3];
      ShowNumber( 3, buff1Number.toInt() );
      ShowNumber( 2, buff2Number.toInt() );
      ShowNumber( 1, buff3Number.toInt() );
      ShowNumber( 0, buff4Number.toInt() );
    }
  }
}




void loop() 
{

  // Detekce stisknuti tlacitka pro pocitani
  // Operace s pocitanim
  // Zobrazeni vysledku na displej
  if ( digitalRead(Button) == HIGH )
  {
    Count++;
    if ( Count > 9999 )
    {
      Count = 0;
    }
    digitalWrite(Button,LOW);
    Show( Count );
    delay(delayButton);
  }

  ///////////////////////
  /*  ZDE JE POTREBA OPET ODKOMENTOVAT PRO AKTIVACI RESET TLACITKA !  
  if ( digitalRead(resetButton) == HIGH )
  {
    Count = 0;
    digitalWrite(resetButton,LOW);
    Show( Count );
    delay(delayButton);
  }
  digitalWrite(resetButton,LOW);
  */

  digitalWrite(Button,LOW);

  delay(delayLoop);
}
