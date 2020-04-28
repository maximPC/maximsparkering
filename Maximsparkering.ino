#include <Servo.h>
Servo myservo;
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

const int place[]={13,12,11,10,9,8,7};
byte val[7];
const int in    =4;
const int ut   =3;

int count=0;
int valin=0;
int valut=0;
int pos = 0; 
int y=0; 

void setup() 
{
  Serial.begin(9600);
  for(int i=0;i<7;i++)
     {pinMode(place[i], INPUT);}  
     
  pinMode(in, INPUT);
  pinMode(ut, INPUT);
  
  myservo.attach(5); 
  lcd.begin(20, 4);
  myservo.write(0);
 
  lcd.clear();
  lcd.setCursor(0, 0);
  count=0;
}

void loop() 
{
  lcd.setCursor(0, 0);
  lcd.print("Lediga platser:");
  lcd.setCursor(0, 1);
  for( y=0;y<7;y++)
     {      
      val[y]=digitalRead(place[y]);
      if(val[y]==1){
        lcd.print(y+1);
        lcd.print(" ");}            
      }
       
      lcd.print("       ");        
  valin=digitalRead(in);
  valut=digitalRead(ut);
 
  if(count>=7){count=7;myservo.write(0);delay(1000);myservo.detach();
              lcd.setCursor(5, 4);
              lcd.print("      fullt");}
  
  if(valut==LOW){
      
    for (pos = 0; pos <= 40; pos += 1) { myservo.write(pos);delay(40);}
    
        while(valut==LOW){valut=digitalRead(ut);}
        count++;
               
        if(count<8){ }
        
    delay(1000);     
    for (pos = 40; pos >= 0; pos -= 1) { myservo.write(pos);delay(40);}
       }
      
  if(valin ==LOW){
    
  myservo.attach(5);   
  for (pos = 0; pos <= 40; pos += 1) { myservo.write(pos);delay(40);}
  
        while(valin ==LOW){valin=digitalRead(in);}
        count--;
        
        if(count<=0){count=0;}
        
  delay(1000);      
  for (pos = 40; pos >= 0; pos -= 1) { myservo.write(pos);delay(40);}        
        }
     
  lcd.setCursor(8, 4);
  lcd.print(" antal:");
  lcd.print(count);  
  if(count>=7){lcd.setCursor(5, 4);lcd.print("      fullt  ");}
}
