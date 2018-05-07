/*Word Clock 2018*/
//github
#include <Wire.h>
#include "RTClib.h"
RTC_DS3231 rtc;
 /*
 #define TEST_MODE
  */
  /*
   * Only uncomment above #define when testing code 
   */
#define data_pin 8  /* Pin to send data over */
#define clk 11      /* Pin to send clock signal */
#define oe 10      /* Set to high when data has been sent completly */
#define strobe 13  /* Make high and low after each bit of data sent */

#define birthdayMon1 9
#define birthdayDay1 29
#define birthdayName1 AKASH

#define birthdayMon2 9
#define birthdayDay2 30
#define birthdayName2 ABHISHEK

#define IT          28 
#define IS          27 
#define TEN_M       26 
#define HALF        25  
#define QUARTER     24
#define TWENTY      23
#define FIVE_M      22
#define MINUTES     21
#define HAPPY       20  
#define PAST        19
#define TO          18
#define ONE         17 
#define BIRTHDAY    16 
#define ELEVEN      15
#define FOUR        14 
#define SIX         13
#define TWO         12 
#define AKASH       11 
#define EIGHT       10
#define NINE        9
#define SEVEN       8 
#define FIVE_H      7
#define THREE       6
#define TEN_H       5
#define TWELVE      4
#define OCLOCK      3
#define ABHISHEK    2 
#define AM          1 
#define PM          0 

int data_bits,hrs,mins;
typedef struct   
{
  uint8_t row_00 :13;
  uint8_t row_01 :13;
  uint8_t row_02 :13;
  uint8_t row_03 :13;
  uint8_t row_04 :13;
  uint8_t row_05 :13;
  uint8_t row_06 :13;
  
  uint8_t row_07 :13;
  uint8_t row_08 :13;
  uint8_t row_09 :13;
  uint8_t row_10 :13;
  
} Screen;
Screen screen;
#ifdef TEST_MODE
char words[32][10]={"PM","AM","ABHISHEK",
                    "OCLOCK","TWELVE",
                    "TEN_H","THREE",
                    "FIVE_H","SEVEN","NINE",
                    "EIGHT","AKASH","TWO",
                    "SIX", "FOUR","ELEVEN",
                    "BDAY","ONE",
                    "TO","PAST","HAPPY",
                    "MINUTES","FIVE_M",
                    "TWENTY","QUARTER",
                    "HALF","TEN_M","IS","IT",
                    "NONE","NONE","NONE"};
void check()
{
  int i;
  bool mybit;
  Serial.print("data_bits\t");Serial.println("Words");
  for(i=0;i<32;i++)
  {
      mybit = data_bits>>i & 1;
      Serial.print(mybit);Serial.print("\t\t");Serial.println(words[i]);
  }
}
#endif

void calc_time_hrs()
{
  updateBitValues(IT,1); /* IT=1; */
  updateBitValues(IS,1); /* IS=1; */
  if(hrs>12)
    {
      hrs-=12;
      updateBitValues(PM,1); /* PM =1; */
    }
  else
    {
      updateBitValues(AM,1); /* AM =1; */
    }

    switch(hrs){
      case 0  : updateBitValues(TWELVE,1); /*TWELVE=1; */
                break;
              
      case 1: updateBitValues(ONE,1); /*ONE=1; */
              break;
              
      case 2: updateBitValues(TWO,1); /*TWO=1; */
              break;
              
      case 3: updateBitValues(THREE,1); /*THREE=1; */
              break;
              
      case 4: updateBitValues(FOUR,1); /*FOUR=1; */
              break;
              
      case 5: updateBitValues(FIVE_H,1); /*FIVE_H=1; */
              break;
              
      case 6: updateBitValues(SIX,1); /*SIX=1;  */
              break;
              
      case 7: updateBitValues(SEVEN,1); /*SEVEN=1;  */
              break;
              
      case 8: updateBitValues(EIGHT,1); /*EIGHT=1; */
              break;
              
      case 9: updateBitValues(NINE,1); /*NINE=1; */
              break;
              
      case 10: updateBitValues(TEN_H,1); /*TEN_H=1; */
              break;
              
      case 11: updateBitValues(ELEVEN,1); /*ELEVEN=1; */
              break;
              
      case 12 :updateBitValues(TWELVE,1); /*TWELVE=1; */
                updateBitValues(AM,0); /* AM =0; */
                updateBitValues(PM,1); /*Pm =1;*/
                break;
                
    

      default: break;
              
        }
}
void calc_time_mins()
{
  DateTime cur_time = rtc.now();
  mins= cur_time.minute();
  hrs= cur_time.hour();
  bool greater_than_30=0;
  updateBitValues(PAST,1); /* PAST=1; */
  updateBitValues(MINUTES,1);/* MINUTES = 1; */

  if(mins>34)
  {
      greater_than_30=1;
      mins-=30;
      updateBitValues(TO,0); /* TO=1;  */
      updateBitValues(PAST,0);/* PAST=0; */
      hrs++;
   }

    if(greater_than_30==0)
    {
      if(mins<5)
      {
        updateBitValues(PAST,0); /*PAST=0; */
        updateBitValues(MINUTES,0); /* MINUTES=0; */
        } 
      else if(mins<10)
      {
        updateBitValues(FIVE_M,1); /*FIVE_M = 1; */
        updateBitValues(PAST,1); /* PAST = 1; */
        updateBitValues(MINUTES,1); /* MINUTES = 1;  */
        }
       else if(mins<15)
      {
        updateBitValues(TEN_M,1); /*TEN_M = 1; */
        updateBitValues(PAST,1); /* PAST = 1; */
        updateBitValues(MINUTES,1); /* MINUTES = 1;  */
        }
       else if(mins<20)
      {
        updateBitValues(QUARTER,1); /*QUARTER=1; */
        updateBitValues(MINUTES,0); /*  MINUTES=0; */
        updateBitValues(PAST,1); /* PAST=1; */
        }
       else if(mins<25)
      {
        updateBitValues(TWENTY,1); /*TWENTY = 1; */
        updateBitValues(PAST,1); /* PAST = 1; */
        updateBitValues(MINUTES,1); /* MINUTES = 1;  */
        }
       else if(mins<30)
      {
        updateBitValues(TWENTY,1); /*TWENTY_M = 1; */
        updateBitValues(FIVE_M,1); /*FIVE_M = 1; */
        updateBitValues(PAST,1); /* PAST = 1; */
        updateBitValues(MINUTES,1); /* MINUTES = 1;  */
        
        }
       else if(mins<35)
      {
       updateBitValues(HALF,1); /* HALF=1; */
        updateBitValues(TO,0); /* TO=0; */
        updateBitValues(PAST,1); /* PAST=1; */
        }  
     }
    if(greater_than_30==1)
    {
      if(mins<10)
      {
        updateBitValues(TWENTY,1); /*TWENTY_M = 1; */
        updateBitValues(FIVE_M,1); /*FIVE_M = 1; */
        updateBitValues(MINUTES,1); /* MINUTES = 1;  */
        
       }
       else if(mins<15)      {
        updateBitValues(TWENTY,1); /*TWENTY = 1; */
        updateBitValues(MINUTES,1); /* MINUTES = 1;  */
        }
       else if(mins<20)
      {
        updateBitValues(QUARTER,1); /*QUARTER=1; */
        updateBitValues(MINUTES,0); /*  MINUTES=0; */
        }
       else if(mins<25) 
       {
        updateBitValues(TEN_M,1); /*TEN_M = 1; */
        updateBitValues(MINUTES,1); /* MINUTES = 1;  */
        }
       else if(mins<30)
      {
        updateBitValues(FIVE_M,1); /*FIVE_M = 1; */
        updateBitValues(MINUTES,1); /* MINUTES = 1;  */
        }
       }

}
/* Function used to update bit values corresponding to certain word */
void updateBitValues(int bitNumber, int valueToUpdate)
{
  if(bitNumber != 31)
  {
    if (valueToUpdate)
      data_bits |= 1 << bitNumber;  /* Update bit which corresponds to certain letter to 1*/
    else
      data_bits &= ~(1<<bitNumber);
  }
  else 
    data_bits = 0;

  }
void updateScreenRows(int wordnumber, int valuetoupdate)
{
  if(valuetoupdate){
    switch(wordnumber)
    {
      case 0:
              screen.row_10|=0b0000000000011;
              break;
      case 1:
              screen.row_10|=0b0000000001100;
              break;
      case 2:
              screen.row_10|=0b1111111100000;
              break;
      case 3:
          screen.row_09|=0b0000000011111;    
              break;
      case 4:
               screen.row_09|=0b111111000000;
              break;
      case 5: 
              screen.row_08|=0b0000011100000;    
              break;
      case 6:
              screen.row_08|=0b1111100000000;    
              break;
      case 7:
              screen.row_07|=0b0000000001111;    
              break;
      case 8:
              screen.row_07|=0b0000111110000;    
              break;
      case 9:
              screen.row_07|=0b1111000000000;    
              break;
      case 10:
              screen.row_06|=0b0000000011111;    
              break;
      case 11:
              screen.row_06|=0b0001111100000;    
              break;
      case 12:
              screen.row_06|=0b1110000000000;    
              break;
      case 13:
              screen.row_05|=0b0000000000111;    
              break;
      case 14:
              screen.row_05|=0b0000001111000;    
              break;
      case 15:
              screen.row_05|=0b1111110000000;    
              break;
      case 16:
              screen.row_04|=0b0000011111111;    
              break;
      case 17:
              screen.row_04|=0b1110000000000;    
              break;
      case 18:
              screen.row_03|=0b0000000000011;    
              break;
      case 19:
              screen.row_03|=0b0000000111100;    
              break;
      case 20:
              screen.row_03|=0b0111110000000;    
              break;
      case 21:
              screen.row_02|=0b000011111110;    
              break;
      case 22:
              screen.row_02|=0b1111000000000;    
              break;
      case 23:
              screen.row_01|=0b0000000111111;    
              break;
      case 24:
              screen.row_01|=0b1111111000000;    
              break;
      case 25:
              screen.row_00|=0b0000000001111;    
              break;
      case 26:
              screen.row_00|=0b0000001110000;    
              break;
      case 27:
              screen.row_00|=0b0001100000000;    
              break;
      case 28:
              screen.row_00|=0b1100000000000;    
              break;
      case 29:
      case 30:
      case 31:   
              break;
      default:
              break;
              
    
    }
  }
 else
 {
     switch(wordnumber)
    {
       case 0:
              screen.row_10&=0b1111111111100;
              break;
      case 1:
              screen.row_10&=0b1111111110011;
              break;
      case 2:
              screen.row_10&=0b0000000011111;
              break;
      case 3:
          screen.row_09&=0b1111111100000;    
              break;
      case 4:
               screen.row_09&=0b000000111111;
              break;
      case 5: 
              screen.row_08&=0b1111100011111;    
              break;
      case 6:
              screen.row_08&=0b0000011111111;    
              break;
      case 7:
              screen.row_07&=0b1111111110000;    
              break;
      case 8:
              screen.row_07&=0b1111000001111;    
              break;
      case 9:
              screen.row_07&=0b0000111111111;    
              break;
      case 10:
              screen.row_06&=0b1111111100000;    
              break;
      case 11:
              screen.row_06&=0b1110000011111;    
              break;
      case 12:
              screen.row_06&=0b0001111111111;    
              break;
      case 13:
              screen.row_05&=0b1111111111000;    
              break;
      case 14:
              screen.row_05&=0b1111110000111;    
              break;
      case 15:
              screen.row_05&=0b0000001111111;    
              break;
      case 16:
              screen.row_04&=0b1111100000000;    
              break;
      case 17:
              screen.row_04&=0b0001111111111;    
              break;
      case 18:
              screen.row_03&=0b1111111111100;    
              break;
      case 19:
              screen.row_03&=0b1111111000011;    
              break;
      case 20:
              screen.row_03&=0b1000001111111;    
              break;
      case 21:
              screen.row_02&=0b111100000001;    
              break;
      case 22:
              screen.row_02&=0b0000111111111;    
              break;
      case 23:
              screen.row_01&=0b1111111000000;    
              break;
      case 24:
              screen.row_01&=0b0000000111111;    
              break;
      case 25:
              screen.row_00&=0b1111111110000;    
              break;
      case 26:
              screen.row_00&=0b1111110001111;    
              break;
      case 27:
             screen.row_00&=0b1110011111111;    
              break;
      case 28:
              screen.row_00&=0b0011111111111;    
              break;
      case 29:
      case 30:
      case 31:   
              break;
      default:
              break;
              
    
    }
 }
}
/* Function outputs data bitwise on dataPin and clocks clock pin 
   and strobe pin */
void serialOut(void)
{
  int counter; /* Counter Varible */
  byte pattern[4]; /* Stores 8 bit data corresponding to one 
                    4094 IC */
  
  digitalWrite(strobe,0); /* Initialize strobe to send data */ 
  digitalWrite(oe, LOW); /* Do not display flashing on the clockface */
  
  for(counter = 0;counter < 4;counter++)
  {
    /* Read data_bits into pattern[i] and send it out on data_pin */
    pattern[counter] = ((data_bits>>(8*counter)) & 0xFF);  
    shiftOut(data_pin, clk, LSBFIRST, pattern[counter]);
    /*
     * shiftOut(data_pin, clk, LSBFIRST, pattern[counter]);
     */
     /*
      * MSBFIRST or LSBFIRST not sure 
      * 22-4-2018 Most probably LSBFIRST is correct
     */
    digitalWrite(strobe,1);
    delay(1);
    digitalWrite(strobe,0);
  }
    
  
}

/* Own power function as pow() was not returning correct values 
* Only works when base is 2 
* not Currently required *
unsigned long powa(int base,int expo){

    if(expo==0)
    return(1);
    else
    return((unsigned long)base<<expo-1);  
  }
*/

/* Check if today is birthday to light up those words*/
void birthday_check()
{
  DateTime cur_time = rtc.now();
  if(cur_time.month() == birthdayMon1 || cur_time.month() == birthdayMon2)
  {
    if(cur_time.day() == birthdayDay1)
    {
      updateBitValues(birthdayName1,1);  /* AKASH=1; */
      updateBitValues(HAPPY,1);  /* HAPPY=1; */
      updateBitValues(BIRTHDAY,1); /* BIRTHDAY=1; */
     }
   else if(cur_time.day()== birthdayDay2)
   {
      updateBitValues(birthdayName2,1); /*ABHISHEK=1;*/
      updateBitValues(HAPPY,1);  /* HAPPY=1; */
      updateBitValues(BIRTHDAY,1); /* BIRTHDAY=1; */
    }
  }

}

void setup() 
{
  Serial.begin(9600);
  if (!rtc.begin()) 
  {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // rtc.adjust(DateTime(2016,9,30,12,10,0));

  if (rtc.lostPower())
  {
    Serial.println("RTC lost power, lets set the time!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  pinMode(data_pin,OUTPUT);
  pinMode(clk,OUTPUT);
  pinMode(oe,OUTPUT);
  pinMode(strobe,OUTPUT);
}

void loop() 
{
  updateBitValues(0,0); 
  calc_time_mins();
  calc_time_hrs();
  birthday_check();
  serialOut();

  #ifdef TEST_MODE
  check();
  delay(10000);
  #endif

}
