/**********************
   Input Sensor Pins
**********************/
#define in 2             //IR sensor1(Outside the door)
#define out 3            //IR sensor2(Inside the door) 
#define tempPin 0        //Temperature pin (LM35)

/**********************
      OUTPUT PINS 
**********************/
#define fan1 4           //fan's 1 to 3
#define fan2 5           //fan's 4 to 6
#define fan3 6           //fan's 7 to 9
#define fan4 7           //fan's 10 to 12

#define ac1 8           //first ac 
#define ac2 9           //second ac
#define ac3 10          //third ac
#define ac4 11          //fourth ac

/**********************
Ac trigger temperature
**********************/
#define trigtemp 30

/**********************
       Variables
**********************/
int count = 0;           //stores the number of people currently in the room
int pstatein=2;          //stores the previous state of IR sensor1(default 2)
int pstateout=2;         //stores the previous state of IR sensor2(default 2)
float temp;              //stores the value of temperature 
long int i=0;            //for time delay

/********************** 
       Functions  
**********************/

void IN()                 
{
    if(digitalRead(in)!=pstatein)           //increments count only if the current state is not the same as previous state.
    {
      count++;
      Serial.print("Person In Room:");      //This is done to prevent the code from continuously incrementing the count if signal is blocked.
      Serial.println(count);
      delay(2000);
    }
}
void OUT()
{
    if(digitalRead(out)!=pstateout)         //increments count only if the current state is not the same as previous state.
    {
      count--;
      if(count<0)
      count=0;
      Serial.print("Person In Room:");      //This is done to prevent the code from continuously decrementing the count if signal is blocked.
      Serial.println(count);
      delay(2000);
    }
}

/*********************
 Temperature Function
*********************/
void TEMP()
{
  temp = analogRead(tempPin);              //Reads the sensor value                     
  temp = temp * 0.45528125;                //Converts it to Celsius 
  Serial.print("TEMPERATURE = ");
  Serial.print(temp);
  Serial.print("*C");
  Serial.println();
}

/*********************
 Setup Function
*********************/

void setup()
{
  Serial.begin(9600);
  pinMode(in, INPUT);                     
  pinMode(out, INPUT);
  pinMode(fan1, OUTPUT);
  pinMode(fan2, OUTPUT);
  pinMode(fan3, OUTPUT);
  pinMode(fan3, OUTPUT);
  pinMode(ac1, OUTPUT);
  pinMode(ac2, OUTPUT);
  pinMode(ac3, OUTPUT);
  pinMode(ac4, OUTPUT);
  TEMP();
  Serial.print("Person In Room:");
  Serial.println(count);
}

/*********************
    Loop Function
*********************/
void loop()
{  
  if(digitalRead(in))                 //IF IR sensor1 is high call IN function
  IN();
  if(digitalRead(out))                //IF IR sensor2 is high call OUT function
  OUT();
  pstatein=digitalRead(in);           //assigning the value of their current state to a variable.
  pstateout=digitalRead(out);
  if(i==20000000)                     //calls the temp function once approximately every 10 min.
  {
    TEMP();
    i=0;
  }
  i++;
  if(count>0 && count <= 25)          //IF no of people in room are less than 25    
 {
  digitalWrite(fan1,HIGH);            //turn on Fans 1 to 3
  digitalWrite(fan2,LOW);             //turn off other Fans
  digitalWrite(fan3,LOW);
  digitalWrite(fan4,LOW);
  if(temp>trigtemp)                   //if temperature more than the defined trigger temperature.
    {
      digitalWrite(ac1, HIGH);        //turn on AC 1
      digitalWrite(ac2, LOW);         //turn off other AC's
      digitalWrite(ac3, LOW);
      digitalWrite(ac4, LOW);    
    }
    else
    digitalWrite(ac1, LOW);           //turn off all AC's
    digitalWrite(ac2, LOW);
    digitalWrite(ac3, LOW);
    digitalWrite(ac4, LOW);
 }
 else if(count > 25 && count <=50)    //if more than 25 and less than 50 people are there
 {
   digitalWrite(fan1,HIGH);           //turn on fans 1 to 6
   digitalWrite(fan2,HIGH);
   digitalWrite(fan3, LOW);           //turn off other fans
   digitalWrite(fan4, LOW);
   if(temp>trigtemp)                  //if temperature more than the defined trigger temperature.
    {
      digitalWrite(ac1, HIGH);        //turn on AC's 1 & 2
      digitalWrite(ac2, HIGH);
      digitalWrite(ac3, LOW);         //turn off other AC's
      digitalWrite(ac4, LOW);    
    }
    else
    {
      digitalWrite(ac1, LOW);         //turn off all AC's
      digitalWrite(ac2, LOW);
      digitalWrite(ac3, LOW);
      digitalWrite(ac4, LOW);       
    } 
 }
 else if(count > 50 && count <=75)    //if more than 50 and less than 75 people are there
 {
   digitalWrite(fan1,HIGH);           //turn on fans 1 to 9
   digitalWrite(fan2,HIGH);
   digitalWrite(fan3,HIGH);           
   digitalWrite(fan4, LOW);           //turn off other fans
   if(temp>trigtemp)                  //if temperature more than the defined trigger temperature.
    {
      digitalWrite(ac1, HIGH);        //turn on AC's 1 , 2 & 3
      digitalWrite(ac2, HIGH);
      digitalWrite(ac3, HIGH);
      digitalWrite(ac4, LOW);         //turn off other AC
    }
    else
    {
      digitalWrite(ac1, LOW);         //turn off all AC's
      digitalWrite(ac2, LOW);
      digitalWrite(ac3, LOW);
      digitalWrite(ac4, LOW);       
    } 
 }
 else if(count > 75 && count <=100)    //if more than 75 and less than 100 people are there
 {
   digitalWrite(fan1,HIGH);            //turn on all fans
   digitalWrite(fan2,HIGH);
   digitalWrite(fan3,HIGH);            
   digitalWrite(fan4,HIGH);
   if(temp>trigtemp)                   //if temperature more than the defined trigger temperature.
    {
      digitalWrite(ac1, HIGH);         //turn on all AC's
      digitalWrite(ac2, HIGH);
      digitalWrite(ac3, HIGH);
      digitalWrite(ac2, HIGH);
    }
    else
    {
      digitalWrite(ac1, LOW);      //turn off all AC's
      digitalWrite(ac2, LOW);
      digitalWrite(ac3, LOW);
      digitalWrite(ac4, LOW);       
    } 
 }

 else
 {
  digitalWrite(ac1,LOW);     //turn off all ac's and fans
  digitalWrite(ac2,LOW);
  digitalWrite(ac3,LOW);
  digitalWrite(ac4,LOW);
  digitalWrite(fan1,LOW);
  digitalWrite(fan2,LOW);
  digitalWrite(fan3,LOW);
  digitalWrite(fan4,LOW);
 }
}
