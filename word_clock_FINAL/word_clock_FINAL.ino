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
unsigned long num;
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
  data_num|=IT;
  data_num|=IS;
  data_num|=AM;
  if(hrs>12)
    {
      hrs-=12;
      data_num|=PM;
      data_num&=~AM;
    }

    switch(hrs){
      case 0  : data_num|=TWELVE;
                break;
              
      case 1: data_num|=ONE;
              break;
              
      case 2: data_num|=TWO;
              break;
              
      case 3: data_num|=THREE;
              break;
              
      case 4: data_num|=FOUR;
              break;
              
      case 5: data_num|=FIVE_H;
              break;
              
      case 6: data_num|=SIX;
              break;
              
      case 7: data_num|=SEVEN;
              break;
              
      case 8: data_num|=EIGHT;
              break;
              
      case 9: data_num|=NINE;
              break;
              
      case 10: data_num|=TEN_H;
              break;
              
      case 11: data_num|=ELEVEN;
              break;
              
      case 12 :data_num|=TWELVE;
                data_num&=~AM;
                data_num|=PM;
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
  data_num|=PAST;
  data_num|=MINUTES;

  if(mins>34)
  {
      greater_than_30=1;
      mins-=30;
      data_num|=TO;
      data_num&=~PAST;
      hrs++;
   }

    if(greater_than_30==0)
    {
      if(mins<5)
      {
        data_num&=~PAST;
        data_num&=~MINUTES;
        } 
      else if(mins<10)
      {
        data_num|=FIVE_M;
        }
       else if(mins<15)
      {
        data_num|=TEN_M;
        }
       else if(mins<20)
      {
        data_num|=QUARTER;
        data_num&=~MINUTES;
        }
       else if(mins<25)
      {
        data_num|=TWENTY;
        }
       else if(mins<30)
      {
        data_num|=TWENTY;
        data_num|=FIVE_M;
        }
       else if(mins<35)
      {
        data_num|=HALF;
        data_num&=~TO;
        data_num|=PAST;
        data_num&=~MINUTES;
        }  
     }
    if(greater_than_30==1)
    {
      if(mins<10)
      {   
          data_num|=TWENTY;
          data_num|=FIVE_M;
        }
       else if(mins<15)
      {
        data_num|=TWENTY;
        }
       else if(mins<20)
      {
        data_num|=QUARTER;
        data_num&=~MINUTES;
        }
       else if(mins<25)
      {
        data_num|=TEN_M;
        }
       else if(mins<30)
      {
        data_num|=FIVE_M;
        }
     }
}

void birthday_check(){
 DateTime cur_time = rtc.now();
if(cur_time.month()==9)
{
  if(cur_time.day()==29)
    {
      data_num|=AKASH;
      data_num|=HAPPY;
      data_num|=BIRTHDAY;
      }
    else if(cur_time.day()==30)
    {
      data_num|=ABHISHEK;
      data_num|=HAPPY;
      data_num|=BIRTHDAY;
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
