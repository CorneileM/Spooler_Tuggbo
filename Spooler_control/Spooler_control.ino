//This sketch governs the behaviour of a filament pulling device designed to control the diameter of filament.
//The diameter of the filament is controlled by the speed of a DC motor which pulls filament from an extruder (Filabot EX2): faster = thinner filament; slower = thicker filament.
//The speed of the DC motor is adjusted based on the measured filament diameter which is read from a Mitutoyo digital plunge-dial indicator, to obtain a stable filament diameter.

//This sketch incoporates code from SSpence for reading data from the Mitutoyo plangue dial: https://www.instructables.com/id/Interfacing-a-Digital-Micrometer-to-a-Microcontrol/ 

//**LIBRARIES**//

//**PIN AND VARIABLE DECLARATIONS**//
  
  //*MOSFET MOTOR CONTROLLER*//
    const int MOSFET = 6; //MOSFET PWM output goes through pin 6 -- this needs to be a PWN pin. On the Nano Every that's D3, D5, D6, D9, D10
    int pwmSpeed = 46; //This sets the speed of the spooler -- we want this to be faster than the pulling speed of the tuggbo
                       //51 seems stable
    int ChokeTime = 1; //This sets the amount of engine off-time per cycle -- the engine goes on for 50 milliseconds, and the off for the set amount of choke time
                        //Use this variable to control the spooling speed, once the appropriate pwmSpeed has been found to generate enough, but not too much tension 

//**TIMING VARIABLES**//

    unsigned long previousMillis = 0;        // will store last time heater was on
    long PWMupInterval = 900000;          // milliseconds of off-time 1800000
    
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

  // check to see if it's time to change the state of the heater
  unsigned long currentMillis = millis();
  int pwmSpeedNEW;

  if(currentMillis - previousMillis >= PWMupInterval)
  {
    pwmSpeedNEW = pwmSpeed + 1;
    previousMillis = currentMillis;  // Remember the time
    pwmSpeed = pwmSpeedNEW;
  }
  Serial.println(pwmSpeed);
}
