#include<reg51.h>
#define lcd P1

sbit M_a=P3^0; //MOTOR DRIVER PINS
sbit M_b=P3^1;

sbit sensorIN=P2^0; //INPUT FROM ACOHOL SENSOR

sbit buzz=P0^0; // OUTPUT PIN TO BUZZER

sbit rs =P2^5; //SETTING UP LCD PINS
sbit e=P2^7;
sbit rw=P2^6;

void Delay (unsigned int t) ;

void cmd (unsigned int c) //TO SET the location on LCD
{
  lcd=c;
  rs=0; //'register select' if low,lcd will act as 'location/memory'
  rw=0;//pin should be low to write "data"
  e=1; //enable writing "data"
  Delay(10);
  e=0; //disabled
}

void ldata(unsigned int c) //TO DISPLAY THE RECIEVED DATA IN LCD
{
    lcd=c;
    rs=1;  //lcd will act as "data"
    rw=0;  //write mode
    e=1;	//enabled
    Delay(10);
    e=0;  //disabled
}
 
void String(unsigned char *s) //TO SEND THE REQUIRED DATA TO LCD
{
    while(*s)
    {
        ldata(*s); 
        ++s;
        Delay(10);
    }
}

void Delay (unsigned int t) //FOR DELAY
{
    unsigned int i,j;
    for(i=0; i<t;i++)
        for(j=0;j<750;j++);
}

void motorRun() //TO RUN THE MOTOR
{
    M_a=1; //input 1 of motor driver
    M_b=0; //input 2 of motor driver
    M_a=1;
    M_b=0;
}

void motorStop() //TO STOP THE MOTOR
{
    M_a=0; //input 1 of motor driver
    M_b=0; //input 2 of motor driver
    M_a=0;
    M_b=0;
}

void main () //MAIN FUNCTION OF OUR PROJECT
{
    unsigned char alert=0x00; // assigning a variable to store the sensor output
    //lcd setup
    cmd(0x38);
    cmd(0x0c);
    cmd(0x01);

    while(1) //infinte loop
    {
        alert=sensorIN; //STORING THE OUTPUT OF SENSOR
			
        if(alert!=1) //WHEN ALCOHOL IS NOT SENSED
        {
            motorRun();
					  buzz=0;
            cmd (0x80);
            String ("Alcohol Free    ");
        }
        else        //WHEN ALCOHOL IS SENSED
        {
            motorStop();
            buzz=1;
            cmd (0x80);
            String ("Alcohol Detected");

        }
 
    }

}