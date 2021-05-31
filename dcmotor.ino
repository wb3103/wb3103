 //  int yy;
  


//  int sPin_y = 3;
//   int dPin_y = 6;
  

  int zeitverzoegerung = 2000;
  
    void setup_dcmotor()   //Port für dc-Motor wird gesetzt
    {
      digitalWrite(sPin_y, HIGH);
     digitalWrite(dPin_y, HIGH);
    pinMode(sPin_y, OUTPUT);
    pinMode(dPin_y, OUTPUT);
    pinMode(end_y, INPUT_PULLUP);
      pinMode(pos_y, INPUT_PULLUP);
    }
  
    void dc_go()       
        {
if(y_position_diff < 0)
      {

  if (debug == 1) {
    Serial.print("Down ");
  }
  if(y_position_ist > 0)
  {
  //  delay(2);
   abwaerts();
  }  
       y_position_ist--;
      }
  if(y_position_diff > 0)
      {
        aufwaerts();
        y_position_ist++;
  if (debug == 1) {
       Serial.print("Up ");
  }
        }
  Serial.print("zur ");      
  Serial.println(y_position_ist);
       // delay(10);
         show("Pos y ",digitalRead(pos_y),true); 
       show("End y ", digitalRead(end_y), true); 
        while(digitalRead(pos_y) == LOW) // && digitalRead(end_y) == HIGH) //Wechselspiel der Lichtschranken abwarten   
       
        {
          delay(2);
         // Serial.print(digitalRead(pos_y));
         // Serial.print(digitalRead(end_y));
          }
        delay(5);
       show("Pos y ",digitalRead(pos_y),true); 
       show("End y ", digitalRead(end_y), true);  
        while(digitalRead(pos_y) == HIGH) // && digitalRead(end_y) == HIGH)
          
           {
            delay(2);
            // nur zum Test einbauen, sonst auskommentiert
            /*
            delay(2);
            Serial.print(digitalRead(pos_y));
            Serial.print(digitalRead(end_y));
            */
            }
        delay(5);
        // siehe vorheriege while-Schleife 
        /*
        if(digitalRead(end_y) == LOW)
        {
        Serial.println("Fehler");
        }
        */
        stopp();
   show("Punkt Li ", y_position_ist, true);
      }
      
void dc_referenzfahrt()
   {
    Serial.println("Rückfahrt Referenz");
    abwaerts();
      show("Endsch y ", digitalRead(end_y), true); 
      show("Possch y ", digitalRead(pos_y), true); 

      delay(100);   

    while(digitalRead(end_y) == HIGH)
    { 
      delay(100);
      }
  stopp();
  delay(10);
           show("Endsch y ist ", digitalRead(end_y), true);
           show("Possch y ist ", digitalRead(pos_y), true);
      delay(1000);

     show("Possch y ", digitalRead(pos_y), true);
           aufwaerts();
     while(digitalRead(pos_y) == LOW )
     { }
       stopp();
       
       y_position_diff = 1;
       dc_go();
       show("Pos y erreicht ", digitalRead(pos_y), true);
      // Test der Li-Schranken
     //  y_position_diff = 1;
      // dc_go();
      // show("Pos y erreicht ", digitalRead(pos_y), true);
      show("Endsch y ", digitalRead(end_y), true); 
      show("Possch y ", digitalRead(pos_y), true);    
      
        Serial.println("Referenz erreicht");
        delay(1000);
  y_position_ist = 0;
  y_position_soll = 0;
  y_position_diff = 0;
  zaehler = 0; 
 show("ist soll diff ", y_position_ist + y_position_soll + y_position_diff + zaehler, true);
//       y=0;     
   }

void abwaerts()
{
  
        digitalWrite(dPin_y, LOW);
      digitalWrite(sPin_y, HIGH); 
//       Serial.print(digitalRead(dPin_y));
//         Serial.print(digitalRead(sPin_y));
      Serial.println("AB");    
}

void aufwaerts()
{
         digitalWrite(dPin_y, HIGH);
         digitalWrite(sPin_y, LOW);
//           Serial.print(digitalRead(dPin_y));
//         Serial.print(digitalRead(sPin_y));
         Serial.println("AUF");   
}

void stopp()
 {
    digitalWrite(dPin_y, HIGH);
    digitalWrite(sPin_y, HIGH); 
//    Serial.print(digitalRead(dPin_y));
//    Serial.print(digitalRead(sPin_y));
    Serial.println("AUS");   
 }

 void relay()
 {
  Serial.print("Relay ");
 } 
