long xy;
int xz = 0;
int stepPin = 2;
int dirPin = 5;
int RPM = 200 ;
uint16_t schrittzeit = 100000/RPM;
int endschalter = 9;
void setup_stepper() //Setup des Ports für den Stepper
{
  pinMode(enaPin,INPUT_PULLUP);
  pinMode(dirPin, INPUT_PULLUP);
  pinMode(stepPin, INPUT_PULLUP);
  pinMode(enaPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(endschalter, INPUT_PULLUP);
  pinMode(A0,OUTPUT);
  digitalWrite(enaPin, HIGH);
}
void stepper_go_x() 
{  
  digitalWrite(enaPin,LOW);
  if (x_position_richtung = 2)
  {
    zaehler = -1;
  digitalWrite(dirPin, LOW);
   }
  if (x_position_richtung = 1)
  {
    zaehler = 1;
  digitalWrite(dirPin, HIGH);
   }
       if (digitalRead(endschalter) == LOW)   // HIGH
{
  if (debug == 1)
  {
        Serial.println(" Endschalter LOW");
  }  
        //return;
}
  schritt();
  digitalWrite(enaPin, HIGH);
}
void ausgabe()
 { Serial.println(position); }

void stepper_referenzfahrt()
{

  while ((digitalRead(endschalter) == HIGH))
  {
  digitalWrite(dirPin, LOW);
  digitalWrite(enaPin,LOW);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(schrittzeit);
    digitalWrite(stepPin, HIGH);
     delayMicroseconds(schrittzeit);
  
    digitalWrite(enaPin,HIGH);
    }
   digitalWrite(dirPin, HIGH);
    position = 0;
    testposition = 0;
    //x_position_ist=0; //Fehler
    x_position_ist = motorkonstante_horizontal*Azimuth_Sommersonnenwende;
  x_position_soll=0;
  x_position_diff=0; 
  
//  merker_waagerecht = 0;  //23.05.2021 Merker wurde um 1:00 zurückgesetzt
  
  }
   void schritt()
   {
    Serial.println("Schritte");
    for (xy = 0; xy < abs(zielposition); xy++)
    {

    digitalWrite(stepPin, LOW);
    delayMicroseconds(schrittzeit);
    digitalWrite(stepPin, HIGH);
     delayMicroseconds(schrittzeit);
    testposition = testposition + zaehler;
    }
   } 
