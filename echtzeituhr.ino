      #include <Wire.h>
      #include <ds3231.h>
       
      struct ts t;
       
      void setup_echtzeituhr() {
       // Serial.begin(9600);
        Wire.begin();
        DS3231_init(DS3231_INTCN);
  
  // ++++++++++ Echtzeituhr setzen
  if(zeitstellen == 1) // braucht nicht verändert werden
  { 
    t.hour=20; // Deine Zeit einsetzen
    t.min=30;
    t.sec=0;
    t.mday=1;
    t.mon=4;
    t.year=2021;
    DS3231_set(t); 
  }
  // ++++++++ Ende setzen
       
      }
       
      void loop_echtzeituhr() {
      //  char str1[10]; //im Haupprog gesetzt
        // put your main code here, to run repeatedly:
        DS3231_get(&t);
      //  if (debug == 1) {
      if (!crlf == 1) {
  Serial.write(0x1B); // Escape
  Serial.print("[2J");
      }
      Serial.println("");  //Leerzeile
      sprintf(str1,"Date: %02d/%02d/%04d\t",t.mday,t.mon,t.year);
      Serial.print(str1);
        sprintf(str1,"Time: %02d:%02d:%02d",t.hour,t.min,t.sec);
         Serial.println(str1);
 
       tag = t.mday;
       monat = t.mon;
       jahr = t.year;
      // day=tag;
       //month=monat;
       //year=jahr;
       stunde = t.hour;
       minute = t.min;
       sekunde = t.sec;   
        delay(50);
      }
