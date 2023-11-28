/*
This program turns on and off a LED on pin 13 based on LM35 temperature sensor values
*/

int timer=0;
bool state=0;
int lm35_pin=A0;

void setup() {
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  pinMode(lm35_pin,INPUT);
  TCCR0A=(1<<WGM01);    //Set the CTC mode   
  OCR0A=0xF9; //Value for ORC0A for delay 1 seconds 
  TIMSK0|=(1<<OCIE0A);   //Set  the interrupt request
  sei(); //Enable interrupt
  TCCR0B|=(1<<CS01);    //Set the prescale 1/64 clock
  TCCR0B|=(1<<CS00);
}

void  loop() {
  //in this way you can count the time
  int temp_adc_val;
  float temp_val;
  if(timer==0)
  {
  temp_adc_val = analogRead(lm35_pin);  /* Read Temperature */
  temp_val = (temp_adc_val * 4.88); /* Convert adc value to equivalent voltage */
  temp_val = (temp_val/10); /* LM35 gives output of 10mv/°C */
  Serial.print("Temperature = ");
  Serial.print(temp_val);
  Serial.print(" Degree Celsius\n");
  }
 
  if(temp_val>30)
  {
  if(timer>=500){
    state=!state;
    timer=0;
  }
  }
  else 
  {
    if(timer>=250){
    state=!state;
    timer=0;
  }
  }
  
  digitalWrite(13,state);
  
}
ISR(TIMER0_COMPA_vect){    //This  is the interrupt request
  timer++;
}
