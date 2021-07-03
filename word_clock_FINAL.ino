#define data_pin 8
#define clk 11
#define oe 10
#define strobe 13

#define IT          (1<<31) 
#define IS          (1<<30) 
#define TEN_M       (1<<29) 
#define HALF        (1<<28)  
#define QUARTER     (1<<27)
#define TWENTY      (1<<26)
#define FIVE_M      (1<<25)
#define MINUTES     (1<<24)
#define HAPPY       (1<<23)  
#define PAST        (1<<22)
#define TO          (1<<21)
#define ONE         (1<<20) 
#define BIRTHDAY    (1<<19) 
#define ELEVEN      (1<<18)
#define FOUR        (1<<17) 
#define SIX         (1<<16)
#define TWO         (1<<15) 
#define AKASH       (1<<14) 
#define EIGHT       (1<<13)
#define NINE        (1<<12)
#define SEVEN       (1<<11) 
#define FIVE_H      (1<<10)
#define THREE       (1<<9)
#define TEN_H       (1<<8)
#define TWELVE      (1<<7)
#define OCLOCK      (1<<6)
#define ABHISHEK    (1<<5) 
#define AM          (1<<4) 
#define PM          (1<<3) 
/* 
 #define AM data_bits[2] 
#define AM data_bits[1] 
#define AM data_bits[0] 
*/
unsigned long powa(int base, int expo);
unsigned long nume;
unsigned long data_num = 0;
int j,l,hrs,mins,i,data_bits[32];
char words[32][10]={"NONE","NONE","NONE",
                    "PM","AM","ABHISHEK",
                    "OCLOCK","TWELVE",
                    "TEN_H","THREE",
                    "FIVE_H","SEVEN","NINE",
                    "EIGHT","AKASH","TWO",
                    "SIX", "FOUR","ELEVEN",
                    "BDAY","ONE",
                    "TO","PAST","HAPPY",
                    "MINUTES","FIVE_M",
                    "TWENTY","QUARTER",
                    "HALF","TEN_M","IS","IT"};
void check(){
  int i;
  Serial.print("data_bits\t");Serial.println("Words");
  for(i=31;i>=0;i--){
    Serial.print(data_bits[i]);Serial.print("\t\t");Serial.println(words[i]);
  }
}
#include <Wire.h>
#include "RTClib.h"

RTC_DS3231 rtc;

void clr_all()
{
  data_num = 0;
// for(i=0;i<32;i++)
//    data_bits[i]=0;  
}


void calc_time_hrs()
{ 
  IT=1;
  IS=1;
  AM=1;
  if(hrs>12)
    {
      hrs-=12;
      PM= 1;
      AM=0;
    }

    switch(hrs){
      case 0  : TWELVE=1;
                break;
              
      case 1: ONE=1;
              break;
              
      case 2: TWO=1;
              break;
              
      case 3: THREE=1;
              break;
              
      case 4: FOUR=1;
              break;
              
      case 5: FIVE_H=1;
              break;
              
      case 6: SIX=1;
              break;
              
      case 7: SEVEN=1;
              break;
              
      case 8: EIGHT=1;
              break;
              
      case 9: NINE=1;
              break;
              
      case 10: TEN_H=1;
              break;
              
      case 11: ELEVEN=1;
              break;
              
      case 12 :TWELVE=1;
                AM=0;
                PM=1;
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
      TO=1;
      PAST=0;
      hrs++;
   }

    if(greater_than_30==0)
    {
      if(mins<5)
      {
        PAST=0;
        MINUTES=0;
        } 
      else if(mins<10)
      {
        FIVE_M=1;
        }
       else if(mins<15)
      {
        TEN_M=1;
        }
       else if(mins<20)
      {
        QUARTER=1;
        MINUTES=0;
        }
       else if(mins<25)
      {
        TWENTY=1;
        }
       else if(mins<30)
      {
        TWENTY=1;
        FIVE_M=1;
        }
       else if(mins<35)
      {
        HALF=1;
        TO=0;
        PAST=1;
        MINUTES=0;
        }  
     }
    if(greater_than_30==1)
    {
      if(mins<10)
      {   
          TWENTY=1;
          FIVE_M=1;
        }
       else if(mins<15)
      {
        TWENTY=1;
        }
       else if(mins<20)
      {
        QUARTER=1;
        MINUTES=0;
        }
       else if(mins<25)
      {
        TEN_M=1;
        }
       else if(mins<30)
      {
        FIVE_M=1;
        }
     }
}

void birthday_check(){
 DateTime cur_time = rtc.now();
if(cur_time.month()==9)
{
  if(cur_time.day()==29)
    {
      AKASH=1;
      HAPPY=1;
      BIRTHDAY=1;
      }
    else if(cur_time.day()==30)
    {
      ABHISHEK=1;
      HAPPY=1;
      BIRTHDAY=1;
      }
  }

}

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
//rtc.adjust(DateTime(2017,9,30,1,35,0));

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

pinMode(data_pin,OUTPUT);
pinMode(clk,OUTPUT);
pinMode(oe,OUTPUT);
pinMode(strobe,OUTPUT);
}

void conv_num(){
num=0;
for(j=0;j<32;j++){

  num= num+ (data_bits[j]*powa(2,j));
}
for(i=0;i<32;i++)
Serial.print(data_bits[i]);
Serial.println();
Serial.print("num=  ");
Serial.println(num,HEX);

}

void ser_out2(){
  digitalWrite(oe,LOW);
 int pattern[4];  //patter[i] goes to 4094-i ie i th 4094
 for (int i=0 ; i< 4; i++){
  pattern[i]=((num>>(8*i)) & 0xFF);
 Serial.println(pattern[i],HEX);
 }
 
for(int i=0;i<4;i++){
 shiftOut(data_pin, clk, LSBFIRST, (byte) pattern[i]);
  digitalWrite(strobe, 1); // flick the latch to put the data on the output pins
 delay(1);
 digitalWrite(strobe, 0);
}
digitalWrite(oe,HIGH);

}


void loop() {
  // put your main code here, to run repeatedly:
  clr_all();
  calc_time_mins();
  calc_time_hrs();
  birthday_check(); 
 /* Only uncomment above 2 lines if output is wrong and need to check the number against words
    check will output data_bits along with corresponding word*/
       
  conv_num();
   ser_out2();
  
 // check();  
 // delay(10000); 
}

unsigned long powa(int base,int expo){

    if(expo==0)
    return(1);
    else
    return((unsigned long)base<<expo-1);  
  }
