/*
                #####                                                           
              ##########                                                        
             ###     ###                                                        
             ###     ###                                                        
             ###     ###                                                        
             ###     ###                                                        
             ###     ###                                                
             ###     ##########                                                 
             ###     ##################                                        
             ###     ###     ##############                                   
             ###     ###     ####     #######                               
             ###     ###     ####     ###   ###                                
  ######     ###     ###     ####     ###   ######                            
###########  ###     ###     ####     ###       ###                            
####     #######                      ###       ###                            
#######      ###                                 ###                            
  #####                                          ###                            
  #######                                        ###                            
     ####                                        ###                            
      ######                                     ###                            
         ###                                  #####                            
         #######                             ####                               
            ####                             ###                                                         
             #######                     #######
                ####                     ####
                #############################
                #############################

                Hardware used: Arduino UNO R4
*/

int photoPin = A0;
int thresholdPin = A1;

int relaisPin = 2;
int ledPin = 13;
int light = 30;
int refLight = 30;
int threshold = 40;


void setup() {
              Serial.begin(9600);
              pinMode(ledPin, OUTPUT);  // Set lepPin - 9 pin as an output
              pinMode(photoPin, INPUT);// Set pResistor - A0 pin as an input (optional)
              pinMode(relaisPin, OUTPUT);  // Set lepPin - 9 pin as an output
              pinMode(thresholdPin, INPUT); // Set thresholdPin - A1 (Poti)
}

void loop() {
              light = analogRead(photoPin); // First Measurement 
              Serial.print("light= ");
              Serial.println(light); 

              threshold = map(analogRead(thresholdPin), 0, 1023, 0, 300);
              Serial.print("threshold= ");
              Serial.println(threshold); // tweaking the value with a poti try to get

              checkThreshold();
              trigger();

}

bool inRange(int val, int minimum, int maximum)
            {
            return ((minimum <= val) && (val <= maximum));
            }

void checkThreshold(){

if ( inRange(threshold, light +10, light +30) )
{
  Serial.println("between 7 and 20");
  digitalWrite(ledPin, HIGH); //Turn led on
} 
else if ( inRange(threshold, light +31, light +50) )
{
  Serial.println("between 26 and 40");
  digitalWrite(ledPin, HIGH); //Turn led on
  delay(100);
  digitalWrite(ledPin, LOW); //Turn led of
}
else if ( inRange(threshold, light +51, light +300) )
{
  Serial.println("between 21 and 300");
  digitalWrite(ledPin, HIGH); //Turn led on
  delay(400);
  digitalWrite(ledPin, LOW); //Turn led of
}
else if ( inRange(threshold, light -200, light +9) )
{
  Serial.println("between -200 and +4");
  digitalWrite(ledPin, LOW); //Turn led of
}


}

void trigger() {
              if (light >= threshold)
                    {
                    //digitalWrite(ledPin, LOW);  //Turn led off
                    digitalWrite(relaisPin, LOW);  //Turn relais on
                    delay(1000);
                    }

              else
                    {
                    //digitalWrite(ledPin, HIGH); //Turn led on
                    digitalWrite(relaisPin, HIGH); //Turn relais on
                    }  
}