/*Word Clock 2018*/


#include <Wire.h>
#include "RTClib.h"
RTC_DS3231 rtc;

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
void calc_time_hrs()
{
  updateBitVauess(IT,1); /* IT=1; */
  updateBitVauess(IS,1); /* IS=1; */
  if(hrs>12)
    {
      hrs-=12;
      updateBitVauess(PM,1); /* PM =1; */
    }
  else
    {
      updateBitVauess(AM,1); /* AM =1; */
    }

    switch(hrs){
      case 0  : updateBitVauess(TWELVE,1); /*TWELVE=1; */
                break;
              
      case 1: updateBitVauess(ONE,1); /*ONE=1; */
              break;
              
      case 2: updateBitVauess(TWO,1); /*TWO=1; */
              break;
              
      case 3: updateBitVauess(THREE,1); /*THREE=1; */
              break;
              
      case 4: updateBitVauess(FOUR,1); /*FOUR=1; */
              break;
              
      case 5: updateBitVauess(FIVE_H,1); /*FIVE_H=1; */
              break;
              
      case 6: updateBitVauess(SIX,1); /*SIX=1;  */
              break;
              
      case 7: updateBitVauess(SEVEN,1); /*SEVEN=1;  */
              break;
              
      case 8: updateBitVauess(EIGHT,1); /*EIGHT=1; */
              break;
              
      case 9: updateBitVauess(NINE,1); /*NINE=1; */
              break;
              
      case 10: updateBitVauess(TEN_H,1); /*TEN_H=1; */
              break;
              
      case 11: updateBitVauess(ELEVEN,1); /*ELEVEN=1; */
              break;
              
      case 12 :updateBitVauess(TWELVE,1); /*TWELVE=1; */
               /* 
                AM=0;
                PM=1; 
                
                maybe not required not sure
                */
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
  PAST=1;
  MINUTES = 1;

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
        updateBitVauess(FIVE_M,1); /*FIVE_M = 1; */
        updateBitVauess(PAST,1); /* PAST = 1; */
        updateBitVauess(MINUTES,1); /* MINUTES = 1;  */
        }
       else if(mins<15)
      {
        updateBitVauess(TEN_M,1); /*TEN_M = 1; */
        updateBitVauess(PAST,1); /* PAST = 1; */
        updateBitVauess(MINUTES,1); /* MINUTES = 1;  */
        }
       else if(mins<20)
      {
        updateBitVauess(QUARTER,1); /*QUARTER=1; */
        updateBitValues(MINUTES,0); /*  MINUTES=0; */
        }
       else if(mins<25)
      {
        updateBitVauess(TWENTY); /*TWENTY = 1; */
        updateBitVauess(PAST); /* PAST = 1; */
        updateBitVauess(MINUTES); /* MINUTES = 1;  */
        }
       else if(mins<30)
      {
        updateBitVauess(TWENTY,1); /*TWENTY_M = 1; */
        updateBitVauess(FIVE_M,1); /*FIVE_M = 1; */
        updateBitVauess(PAST,1); /* PAST = 1; */
        updateBitVauess(MINUTES,1); /* MINUTES = 1;  */
        
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
        updateBitVauess(TWENTY,1); /*TWENTY_M = 1; */
        updateBitVauess(FIVE_M,1); /*FIVE_M = 1; */
        updateBitVauess(MINUTES,1); /* MINUTES = 1;  */
        
       }
       else if(mins<15)      {
        updateBitVauess(TWENTY); /*TWENTY = 1; */
        updateBitVauess(MINUTES); /* MINUTES = 1;  */
        }
       else if(mins<20)
      {
        updateBitVauess(QUARTER,1); /*QUARTER=1; */
        updateBitValues(MINUTES,0); /*  MINUTES=0; */
        }
       else if(mins<25) 
       {
        updateBitVauess(TEN_M,1); /*TEN_M = 1; */
        updateBitVauess(MINUTES,1); /* MINUTES = 1;  */
        }
       else if(mins<30)
      {
        updateBitVauess(FIVE_M,1); /*FIVE_M = 1; */
        updateBitVauess(MINUTES,1); /* MINUTES = 1;  */
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
      updateBitValues(birthdayName1);  /* AKASH=1; */
      updateBitValues(HAPPY);  /* HAPPY=1; */
      updateBitValues(BIRTHDAY); /* BIRTHDAY=1; */
     }
   else if(cur_time.day()== birthdayDay2)
   {
      updateBitValues(birthdayName2); /*ABHISHEK=1;*/
      updateBitValues(HAPPY);  /* HAPPY=1; */
      updateBitValues(BIRTHDAY); /* BIRTHDAY=1; */
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
  updateBitValues(0); 
  calc_time_mins();
  calc_time_hrs();
  birthday_check();
  serialOut();

}
