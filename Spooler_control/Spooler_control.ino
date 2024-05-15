//This sketch governs the behaviour of a filament spooler to be used in conjuction with Tuggbo [add link].
//The spooler uses a simple DC motor that generates a pesudo-clutch effect by attaching a MOSFET motor controller to the DC engine and cycling the motor off very briefly (ChokeTime) in between longer intervals of driving the motor.
//The ChokeTime and motor speed can be adjusted until the spooler pulls filament from Tuggbo with the right amount of tension (i.e, keeps the filament tight and spooling neatly, without pulling so hard that the Tuggbo falls over.

//**LIBRARIES**//

//**PIN AND VARIABLE DECLARATIONS**//
  
  //*MOSFET MOTOR CONTROLLER*//
    const int MOSFET = 6; //MOSFET PWM output goes through pin 6 -- this needs to be a PWN pin. On the Nano Every that's D3, D5, D6, D9, D10
    int pwmSpeed = 52; //This sets the speed of the spooler -- we want this to be faster than the pulling speed of the tuggbo
                       //70
    int ChokeTime = 1; //This sets the amount of engine off-time per cycle -- the engine goes on for 50 milliseconds, and the off for the set amount of choke time
                        //Use this variable to control the spooling speed, once the appropriate pwmSpeed has been found to generate enough, but not too much tension 
    
void setup() {
  
  Serial.begin(9600); //Start serial communication

  //*MOSFET MOTOR CONTROLLER*//
  //MOSFET pin is set to output so that we can send PWM signals to control the motor
  pinMode(MOSFET, OUTPUT); 

  //Starts the motor in forward direction at the motor starting speed
  analogWrite(MOSFET, pwmSpeed);
  
}

void loop() {

  //The interplay between the PWM speed (MOSFET) and the two delay variables below, determines the speed and tension of the spooler. Higher PWM values generate more speed and tension,
  //while increasing the second delay variable reduces speed, but maintains the same amount of tension. It's a bit of a fiddly guessing game, but there's a lot of room for error
  
  
  //Puts the motor on at the set PWM speed for as long as stated in the delay
  analogWrite(MOSFET, pwmSpeed);
 
delay(50);

  //Turns the motor off for as long as stated in the delay
  analogWrite(MOSFET, 0);
 
delay(ChokeTime);

}
