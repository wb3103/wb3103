//#include <Arduino.h>
  //#include <seriell.ino>
  /*
   * Lichtschranke endschalter an y+
   * Lichtschranke Position an z+
  */
  #include <stdio.h>
  #include <SoftwareSerial.h>
  SoftwareSerial serial1(15,14); //RX, TX
  float Eberswalde_lon = 13.491619;
  float Eberswalde_lat = 52.509110;
  int neustart = 1;
  int debug = 1;
  int crlf = 1;

   char str1[10];
  
  int zeitstellen = 0; //1 wenn gestellt werden soll
  #include <SoftwareSerial.h>
  int elevation_unter_horizont = 1; //unter horizont = 1, über horizont = 0
  volatile bool merker_waagerecht = false;//false entspricht 0, true entspricht 1
  unsigned long motorkonstante_horizontal = 14900; //14900;  //Schritte je Grad
  int motorkonstante_vertikal = 1000;
  unsigned int Azimuth_Sommersonnenwende = 60; //Sommersondenwende in Grad
  int Windsicherung = 36; //Waagerecht fahren bis Lichtschrankenpunkt 38 für Windsicherung
  double dElevation;
  double dAzimuth;
  volatile int end_y = 10; //Lichtschranke
  volatile int pos_y = 11; //Lichtschranke Position

 volatile float Aufgang;
 volatile float Untergang;
 
  int sPin_y = 6;  //DC-Motor
  int dPin_y = 3;
  
  int monat;
  int tag;
  int jahr;                                                                                                                                    
  int stunde;
  int minute;
  int sekunde;
  
  String seriellstring  = "";
  String achse= "";
  String schritte= "";
  
  #define x_schritt 2
  #define x_endschalter_rechts 9
  #define x_endschalter_links 9
  #define x_richtung 5
  
  //#define y_endschalter_rechts_dc 10
  //#define y_endschalter_links 10
  int x_position_richtung = 1;
  unsigned long x_position_ist = 0;
  unsigned long x_position_soll = 0;
  long x_position_diff = 0;  //auf signed getellt um zu erkennen ab wann die Bewegung positiv wird
  
  volatile long y_position_ist = 0;
  volatile long y_position_soll = 0;
  volatile long y_position_diff = 0;
  volatile int y_richtung = 0;
  int zaehler = 0;
  long testposition = 0;
  int auf = 1;
  int ab = 2;
  int  halt = 0;
  //int y = 0;
  //int x = 0;
  int w = 0;
  int cc = 0;
  char i;
  //String i = "";
  uint16_t x_position;
  uint16_t y_position;
  long position = 0;
  int enaPin = 8;
  
  int z = 0;
  int ff = 0;
  int result = 0;
  long zielposition;
  
  long myTimer = 0;
  long myTimeout = 0;
  //int debug = 0;
  
  void setup() {
   Serial.begin(115200);
   serial1.begin(9600);
  setup_echtzeituhr();
   pinMode(x_endschalter_rechts, INPUT_PULLUP);
   pinMode(x_richtung,OUTPUT);
 setup_stepper();
  setup_dcmotor();
//abwaerts();
//delay(10000);
dc_referenzfahrt();



//testlauf();
  


 
  if (debug == 1) { Serial.println("Startet"); }
  neustart = 1;

  loop_echtzeituhr();
    if (neustart == 1)
  {
    if (debug == 1) {Serial.println("X fährt Referenz");}
  neustart = 0;
  referenz();
  }
  
  loop_SONNENSTAND();
  Sonnenaufgang();
  myTimeout = 30000;
  if (millis() > myTimeout + myTimer)
  {
    myTimer = millis();
  }
  delay(5000);
  }
  void loop()  //Hier beginnt die Hauptschleife des Programms
  {
    loop_echtzeituhr();
  Sonnenaufgang(); 
  loop_SONNENSTAND();
  //ser();  //zweite serielle Schnittstelle
  Serial.print(x_position_ist); 
  Serial.print(" ");
  Serial.println(x_position_soll);
  
  Serial.print("Merker waagerecht ");
  Serial.println(merker_waagerecht);
  
  if (elevation_unter_horizont == 1)
  {

    if ((dElevation < 0) && (merker_waagerecht == 0)) //Wenn unter 0 dann Waage und Merker setzen Nicht ausführen wenn merker 1 ist
  
  {
     Serial.println("Fahre Waage");
   while (y_position_ist < Windsicherung)
   {
    y_position_diff = 1;
    dc_go();
   }
   Serial.println("Waage gesetzt");
    merker_waagerecht = 1;  //merke dir, du bist waagerecht gefahren
    show("Waagerecht",merker_waagerecht,true);
    
          show("Pos y ",digitalRead(pos_y),true); 
          show("End y ", digitalRead(end_y), true);  
    }

  if ((dElevation > 0) && (merker_waagerecht == 1))  //wenn kurz vor Sonnenaufgang fahre in Startposition
  
  {
    Serial.println("Fahre Pos normal");
   
    dc_referenzfahrt();
    merker_waagerecht = 0; //setze den Merker zurück
   show("Waagerecht",merker_waagerecht,true);
    show("Y-Startpos",merker_waagerecht,true);
      }
     
   if((stunde == 1) && (minute < 10))
    {
    stepper_referenzfahrt(); // wenn Änderung entfernt wird muß hier referenz(); stehen
    }
    goto abbruch;    
  }
  
  if (debug == 1) {
  Serial.print("X-Soll: ");
  Serial.print(x_position_soll);
  Serial.print(" IST: ");
  Serial.print(x_position_ist);
  }
  
  x_position_diff = x_position_soll - x_position_ist;
  if (debug == 1) {
  Serial.print(" DIFF: ");
  Serial.print(x_position_diff);
  }
  zielposition=x_position_diff;
 
  if(zielposition > 0)
  {
    x_position_richtung = 2;
  stepper_go_x();
  if (debug == 1) 
    {
    Serial.println();
    x_position_ist = x_position_soll;
    }
  
  y_position_diff = y_position_soll - y_position_ist;
  show("y-differenz ", y_position_diff, true);
  while(y_position_soll != y_position_ist)
  {
  dc_go();
  }
  y_position_diff = 0;
  }
   abbruch:
   delay(180000); // = alle 3.0 Minuten
    cc = 0;
      
  }
  // +++++ hier Beginn Testprogramm

// /*  
void testlauf()
{

// aufwaerts();
//  delay(1000);
//  stopp();
  Serial.println("Testlauf");
  rundlauf:
 // stepper_referenzfahrt(); //fahre x zum Referenzpunkt  
  delay(1000);  //warte eine Sekunde
  while (y_position_ist < Windsicherung) //fahre y zur Position Windwicherung
   {
    y_position_diff = 1;
    dc_go();
   }
   Serial.println("Sicherung erreicht");
   delay(1000); //warte eine Sekunde   
   while(y_position_ist > 0)
   {
    y_position_diff = -1;
     dc_go();
    }
//   dc_referenzfahrt(); //fahre y zur Referenz
   delay(1000);   //warte eine Sekunde
 //  y_position_soll = 3;  //Fahre y auf position 3
 //while(y_position_soll != y_position_ist)
 //   dc_go();
 // y_position_diff = 0;
 //  delay(1000);
   goto rundlauf;
}
// */

  // ++++ Ende Testprogram
