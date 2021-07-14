/*
  This programme was created as an Alternative for FWR(foil wrapper) PLC and  is based on existing locally made Logical gate circuit logic
  All programming logics have been tested extensively, except sealing cycle timing programming ,various timings will be changed on first time  simulation
  during actual operation.
 NOTE : SENSORS ARE 24 V SO CARE SHOULD BE TAKEN WHILE CONNECTING PINS TO  mu-CONTROLLER
        sensor signal: WHEN BUNDLE IS SENSED OUTPUT IS HIGH AND VICE VERSA
        circuit for isolating both signal is to be tested with optocoupler ILD74/IL74/ILQD74 it simplifies THE WIRING(no need for using voltage divider to convert level to 5v)
        circuit also remains neat   (after discussion) 

   RG - uno- 328- p ATMEGA has been used as the Microcontroller (cheap chinese make ,cp2101 driver),driver should be downloaded from internet to first time connection, 
   All Analog pins has been re purpoused for using it as OUTPUT pins (pin constraint)
   for which test programme was made as blinking LED and Pushbuttton and its operation was satisfactory
   Plans are there to expand this board as standalone : ie  dampening board operation also to be programmed  
   but for time being that part has been with held,will be added after test run of this programme in real time
   Also a simple HMI panel was made ready .If budget allows Nextion touch display can also be used
   
 Circuit wiring has been made with dotted pcb and hand soldered with looping of wires ,so plan has been made to make single layer PCB design and etching the PCB inhouse   


This code is private property of "THE HINDU"  and any modification or using of this code cannot be made without prior knowledge of the author
Author is not liable for any damage  arising from  misuse of this programm

  modified 27 july 2017 12:10 AM (FIRST MODIFICATION VERSION)---->doubts clarification needed
  by E.Ranjithkumar & R.saravanakumar
   modified 28 july 2017 6:28 AM (2nd MODIFICATION VERSION)--->added comments about optocoupler
  by E.Ranjithkumar 
   modified 28 july 2017 12:10 AM (THIRD MODIFICATION VERSION)---->S2 SENSOR logic changed,new comments added near timer
  by E.Ranjithkumar & R.saravanakumar
  modification 4th sealing bar dampening section emoved,foil screen hit time slightly modified
  modified on 10/8/17 pls refer edit4
 */
 
const int sensor1 = 2;                        //SENSOR AFTER STACKER BELT1 SENSOR

const int sensor3 = 5;                       // SENSOR AFTER SEALING BELT, BELT3 SENSOR

const int sensor4 = 6;                        //SENSOR BEFORE MOSA LONG,BELT4 SENSOR

const int sensor2 = 3;                         //SENSOR BEFORE SEALING BAR

const int Mosca = 4;                            // THIS IS SIGNAL FROM MOSCA INDICATION RUNNING STATUS OF MOSCA/DOWN STREAM MACHINE 
 
const int bottomFoilSensor = 8;                 //BOTTOM FOIL SENSOR

const int TopFoilSensor = 7;                     //TOP FOIL SENSOR 

const int belt1 = 14;                         //BELT AFTER STACKER CONNECTED TO ANALOG 0 PIN ,MAPPED AS DIGITAL 14 PIN

const int belt3 = 15;                        // THE BELT AFTER SEALING BAR. CONNECTED TO ANALOG 1 PIN ,MAPPED AS DIGITAL 15 PIN

const int belt4 = 16;                       // THE BELT BEFORE THE MOSCA LONG .CONNECTED TO ANALOG 2 PIN,MAPPED AS DIGITAL 16 PIN

const int bottom_Foil_Motor = 18;           //BOTTOM FOIL MOTOR FORWARD COMMAND

const int sealing_bar = 12;                // SEALING BAR UP AND DOWN ,TIMING MIMICS DAAMPENING BOARD OPERATION 3 BAR IN AIR PRESSURE (TIMING CHANGED FOR DIFFRENT AIR PRESSURE VALUES)

const int brake_flap =11;                  // BRAKE  FOR TOPFOIL FLAP

const int foil_Tension = 19;                // BOTTOM FOIL REVERSE COMMAND

const int topFoilMotor =17 ;               // TOP FOIL MOTOR RUN COMMAND


void setup() 
{
  
  pinMode(6, INPUT);         //SENSOR 4 ,ALL PINS ARE DECLARED AS INPUTS AND OUTPUTS CHANGES WHEN MADE HAS TO BE EDITED ACCORDINGLY inside the loop
  
 pinMode(2, INPUT);          // SENSOR 1 , TOTAL 7 INPUTS 
    
 pinMode(4,INPUT);         // MOSCA SIG
    
  pinMode(5, INPUT);        //SENSOR 3
    
  pinMode(3, INPUT);        //sensor2
      
  pinMode(7, INPUT);        //TOP FOIL SENSOR
         
   pinMode(8,INPUT);        //bottom foil sensor
  
  pinMode(14, OUTPUT);      // BELT1 , TOTAL OUTPUT 8 NOS
  
  pinMode(16,OUTPUT);      //BELT4
 
  pinMode(15,OUTPUT);     //BELT3
  
  pinMode(18,OUTPUT);    // bottom foil fwd
  
  pinMode(12, OUTPUT);    // sealing bar down
  
  pinMode(19,OUTPUT);    //bottom foil RWRS
 
  pinMode(11, OUTPUT);   //BRAKE FLAP
  
  pinMode(17, OUTPUT);   //TOP FOIL FORWARD
  //digitalWrite(belt3 ,HIGH);
     //digitalWrite(belt1 ,HIGH);
    // digitalWrite(belt4 ,HIGH);
       }
 


void sealing()
   {
  digitalWrite(belt3,HIGH);
  delay(200);                                      //time delay for bundle to hit foil screen * increase after field testing*edit4
  digitalWrite(bottom_Foil_Motor ,HIGH);          //18
//delay(500); //bottom foil unwind      
digitalWrite(brake_flap ,HIGH);                //topfoil brake release  11
 int TopFoilSensor = digitalRead(7);
   if(TopFoilSensor == HIGH)                        
    
    {
   
         digitalWrite(topFoilMotor,HIGH);
        // delay(750);   //edit4
                  delay(1000);      
                  
digitalWrite(bottom_Foil_Motor ,LOW); 
digitalWrite(belt3 ,LOW);
digitalWrite(sealing_bar,HIGH);   //12
delay(1000);
//digitalWrite(sealing_bar,LOW);
//delay(100);                                       //DAMPENING DOWNWARDS TIME
//digitalWrite(sealing_bar,HIGH);
//delay(350);
//digitalWrite(brake_flap ,LOW); //11
//delay(750);
//digitalWrite(sealing_bar,HIGH);
//delay(200);                                             //UPWARDS DAMPENING TIME
digitalWrite(sealing_bar,LOW);
digitalWrite(topFoilMotor,LOW);//TRAVELLING TIME
    
    }
else 
{
delay(1000);                               //TRAVELLING TIME
digitalWrite(bottom_Foil_Motor ,LOW); 
digitalWrite(belt3 ,LOW);
digitalWrite(sealing_bar,HIGH);   //12
delay(1000);
//digitalWrite(sealing_bar,LOW);
//delay(100);                                       //DAMPENING DOWNWARDS TIME
//digitalWrite(sealing_bar,HIGH);
//delay(350);
//digitalWrite(brake_flap ,LOW); //11
//delay(750);
//digitalWrite(sealing_bar,HIGH);
//delay(200);                                             //UPWARDS DAMPENING TIME
digitalWrite(sealing_bar,LOW);


}
   
 }

void tensioning()
{

int bottomFoilSensor = digitalRead(8);
if(bottomFoilSensor == HIGH)
  {
        digitalWrite(foil_Tension ,HIGH);
         delay(525);// edit4
         digitalWrite(foil_Tension ,LOW);
             
               }
  
 int belt4 = digitalRead(16);
  if(belt4 == HIGH)              // checking belt status before sennding new sealed bundle to mosca
 {
     delay(70);
     digitalWrite(belt3,HIGH);
            
             }
  }                  //bundle tensionin belt status function and next ends

void loop()               //MAIN PROGRAM STARTS FROM HERE
{
 
  int sensor1 = digitalRead(2);          //INITIALISING ALL INPUTS and OUTPUT INITIALISATION ARE MADE WHERE NEEDED
  
  int sensor4 = digitalRead(6);       //NOTE TO PROGRAMMER : Mistakes has been made here during calling of ouput in conditional statement pls remember next time if it has been called right
  
  int sensor3 = digitalRead(5);
  
  int Mosca = digitalRead(4);
  
 int sensor2 = digitalRead(3); 
 
 int TopFoilSensor = digitalRead(7);
 
 int bottomFoilSensor = digitalRead(8);
  
  if (sensor2 == HIGH)    // SEALING cycle begins 
 {
  sealing();                             //CALL sealing function
  tensioning();                                   // CALL bottom foil tensionong cycle

 }                                                             //machine run cycle start
  //digitalWrite(belt4 ,HIGH);
  // digitalWrite(belt3 ,HIGH);
    // digitalWrite(belt1 ,HIGH);
  
  if ((Mosca == HIGH) && (sensor4 == LOW ) || (Mosca == HIGH) && (sensor4 == HIGH ) ||(Mosca == LOW) && (sensor4 == LOW ))    // MOSCA DOWN STREANM MACHINE BLOCK ,Belt4 BLOCK
  {
   
      digitalWrite(belt4 ,HIGH);
      
    }
  
  else                                                //((Mosca == LOW )&& (sensor4 == HIGH))
  {     
   
   digitalWrite(belt4,LOW);
 // digitalWrite(belt3 ,HIGH);
   //  digitalWrite(belt1 ,HIGH);

  }
 int belt4 = digitalRead(16);                                            //always initialise output pin before using the in statement
    
    if ((sensor3 == HIGH ) && (belt4 == HIGH ) || (sensor3 == LOW ) && (belt4 == LOW )||(sensor3 == LOW ) && (belt4 == HIGH ))    // BELT 3 MACHINE BLOCK
  {
   
      digitalWrite(belt3 ,HIGH);
   
    }
  
  else                       //(sensor3 == HIGH) && (BELT4 == LOW )                                        
  {       
   delay(100);
   digitalWrite(belt3,LOW);

  }
int belt3 = digitalRead(15);
  if ((sensor1 == LOW ) && (belt3 == HIGH ) || (sensor1 == LOW ) && (belt3 == LOW ))   
  {
    digitalWrite(belt1 ,HIGH);
    }
    else if((sensor1== HIGH) && (belt3 == LOW))    
    {
      digitalWrite(belt1 ,LOW);
    }
 if ((sensor1 == HIGH ) && ( belt3 == HIGH ))
    {
      digitalWrite(belt1 ,HIGH);
  }
}

