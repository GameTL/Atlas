/* 
I used an inexpensive nano board v3 ATmega 328p 
the pins used are: 
VIN(+)and GND(-) 
you can feed the power from your bec (5-9 volt) 
D7 throttle signal input. 
D8 front steering input signal. 
D10 rear steering signal output.
D4 blinking dx leds
D5 blinking sx leds
-----------------------------------------
basic setup instructions: 
first you must obtain the best mechanical setup from your front and rear servos and linkage.
best without subtrims or radio adjustements. 
the values you find default should make the controller work quite right away.
however if you want to be sure about what are your real radio signal inputs, or if they are reversed check them before starting this sketch. 
create a new tab and check your input signals with this program (7 for steering - 8 for throttle gas)

int rxpulse;
void setup () {
Serial.begin (9600);
}
void loop () {
rxpulse = pulseIn (7, HIGH); // - 7 to know  front steering signal values, change to 8 and load again to check  throttle values in serial monitor
Serial.println (rxpulse);

you can read the values in the serial monitor by turning the steering wheel of the radio control or moving the throttle.
write the values obtained ann fill  the first define part of the controller setup, replace the default ones with yours custom values.
-------------------------------------------------- ------
the user driving setup consists of 2 main functions: 
first you can choose how much throttle allow at low speed 
before the width of the rear servo starts to close (Speedlimit function).

the second function allows you to determine rear servo width at maximum throttle (Max_gain).
you can choose to close it completely to 2ws or keep 4ws available even at maximum speed

the other functions are: 
tolerance give stepper movement to servo (set it to zero).
Blinkpoint allow steering travel before led start to blink. 

-----------
somethimes it can happen that you exceed with the values the direction result inverted, be careful to find the best suitable values for your model.
to get the servo reverse you just have to exchange the Postsx Postdx rear steering values and put a sign (-) in front of the Max_gain value
there is a relationship between Slowlimit and Max_gain, it can happen that if you lower one you will have to raise the other
however I am sure that it will take you little time to understand how controller works
*/

//----------- signal setup -------------------------------------
#define Neutral 1500 // -- default 1500//minimum throttle forward signal or neutral position
#define Maxspeed 2000 // -- default 2000//maximum throttle forward signal 
#define Antsx 1000 // -- default 1000//in front servo signal sx
#define Antdx 2000 // -- default 2000//in front servo signal dx
#define Streight 1500 //-- default 1500//neutral signal steering centered position for blinking arrow light (if seering center is not zero: add or subtract half of Center value)

#define Postsx 1000 //-- default 1000//out rear servo sx end point (if inverted with postdx it reverse)
#define Postdx 2000 //-- default 2000//out rear servo dx endpoint (if inverted with postsx it reverse)
#define Center 0 //-- default 0//add or subtract your value to center steering (+- 50 or more)
 
//--------- user driving setup ------------------------------
 
#define Max_gain 400 //-- default 400//gain steering reduction width at max throttle (if work reverse add (-) before value)
#define Slowlimit 1600 //-- default 1600//slow forward percentage without endpoint correction
#define Blinkpoint 300 //-- default 300//steering value where led start to blink, small values  start led blink close near to center
#define Tolerance 0 //-- default 0//add/remove stepper servo steering movement

//----------------------------
#include <Servo.h>
Servo myservo; 
#define N_STST  7 //--default7//if servo response is slow low this value to 4 values less 4 may give servo vibration            
#define N_STGAS 7 //--default7//if servo response is slow low this value to 4 values less 4 may give servo vibration 
unsigned int stSt[ N_STST ];  
unsigned int stGas[ N_STGAS ];       
long toStSt = 0;           
long toStGas = 0;         
int inSt = 0;                                         
int inGas = 0;           
unsigned int Rxpulse;
unsigned int Gaspulse ;
unsigned int Gain;
unsigned int NewPos, OldPos;
int led1 = 4;//--led dx
int led2 = 5;//-- led sx
void setup() {
for ( int i=0; i<N_STST; i++ ) stSt[ i ] = 0;
for ( int i=0; i<N_STGAS; i++ ) stGas[ i ] = 0;
myservo.attach(10); //--  rear servo signal out pin 10
pinMode(8, INPUT); //--  front servo signal in pin 8
pinMode(7, INPUT); //-- throttle signal in pin 7
pinMode(led1, OUTPUT);
pinMode(led2, OUTPUT);
}
void loop(){

 
    noInterrupts();   
Rxpulse = pulseIn(8, HIGH);
Gaspulse = pulseIn(7, HIGH);
     interrupts();     
delay(5);
if (Gaspulse > Slowlimit) { //-- default >// if your throttle signal is reverse must change "<" 
Gain = map(Gaspulse, Slowlimit, Maxspeed, 0, Max_gain );
NewPos = map(Rxpulse, Antsx, Antdx, (Postsx + Gain), (Postdx - Gain));
  }
else {
NewPos = map(Rxpulse, Antsx, Antdx, Postsx, Postdx);
  }
if (abs(NewPos - OldPos)> Tolerance) {
OldPos = NewPos;
myservo.write(NewPos + Center);

if (OldPos > Streight+Blinkpoint) digitalWrite(led1, (millis() / 100) % 2); //--default 100 is led blink speed 
              
 else   digitalWrite(led1, LOW);  
if (OldPos < Streight-Blinkpoint) digitalWrite(led2, (millis() / 100) % 2); //--default 100 is led blink speed 
               
  else  digitalWrite(led2, LOW);  

}
}