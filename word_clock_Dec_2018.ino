#define data_pin 8
#define clk 11
#define oe 10
#define strobe 13

#define IT          data_bits[31] 
#define IS          data_bits[30] 
#define TEN_M       data_bits[29] 
#define HALF        data_bits[28]  
#define QUARTER     data_bits[27]
#define TWENTY      data_bits[26]
#define FIVE_M      data_bits[25]
#define MINUTES     data_bits[24]
#define HAPPY       data_bits[23]  
#define PAST        data_bits[22]
#define TO          data_bits[21]
#define ONE         data_bits[20] 
#define BIRTHDAY    data_bits[19] 
#define ELEVEN      data_bits[18]
#define FOUR        data_bits[17] 
#define SIX         data_bits[16]
#define TWO         data_bits[15] 
#define AKASH       data_bits[13] 
#define EIGHT       data_bits[12]
#define NINE        data_bits[10]
#define SEVEN       data_bits[9] 
#define FIVE_H      data_bits[7]
#define THREE       data_bits[6]
#define TEN_H       data_bits[5]
#define TWELVE      data_bits[4]
#define OCLOCK      data_bits[3]
#define ABHISHEK    data_bits[2] 
#define AM          data_bits[0] 
#define PM          data_bits[1] 
/* 
 #define AM data_bits[2] 
#define AM data_bits[1] 
#define AM data_bits[0] 
*/
unsigned long powa(int base, int expo);
unsigned long num;
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
  for(i=0;i<32;i++)
    data_bits[i]=0;  
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
  OCLOCK=1;
Serial.println(mins);
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
        //Serial.println("in 20");
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
        MINUTES =0;
        OCLOCK =0;
        }  
     }
    if(greater_than_30==1)
    {
     // Serial.println("Greater than 30 is true");  
      //Serial.println(mins);
      if(mins<10)
      {   
          TWENTY=1;
          FIVE_M=1;
        //  Serial.println("25");
        }
       else if(mins<15)
      {
        TWENTY=1;
          //Serial.println("20");
        }
       else if(mins<20)
      {
        QUARTER=1;
          //Serial.println("15");
        MINUTES=0;
        }
       else if(mins<25)
      {
        TEN_M=1;
          //Serial.println("10");
        }
       else if(mins<30)
      {
        FIVE_M=1;
          //Serial.println("5");
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
//rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
 //rtc.adjust(DateTime(2018,8,29,8,36,0));

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
//TWENTY =1;
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
 
 digitalWrite(strobe,0);
for(int i=0;i<4;i++){
 shiftOut(data_pin, clk, LSBFIRST, (byte) pattern[i]);
  digitalWrite(strobe, HIGH); // flick the latch to put the data on the output pins
 delay(5);
 digitalWrite(strobe, LOW);
}
digitalWrite(oe,HIGH);

}


void loop() {
  // put your main code here, to run repeatedly:
  clr_all();
  calc_time_mins();
  calc_time_hrs();
  birthday_check();  
  check();  
  delay(10000);  
 /* Only uncomment above 2 lines if output is wrong and need to check the number against words
    check will output data_bits along with corresponding word*/
  //digitalWrite(oe,HIGH);
  conv_num();
   ser_out2();
digitalWrite(oe,HIGH);
}

unsigned long powa(int base,int expo){

    if(expo==0)
    return(1);
    else
    return((unsigned long)base<<expo-1);  
  }
