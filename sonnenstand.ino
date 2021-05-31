  //(C) 2011 Hannes Hassler. 
  //updated and checked 2015
  #include <Helios.h>
  
  Helios helios;
  //DS1107H clock;
  double Pi = 3.1415;
  float zeitgleichung;
  float tagnummer ;
  float Deklination;
  float Zeitdifferenz;
  
  float B = Pi*Eberswalde_lat/180; // 0.9221; //geografische Breite B = Pi *52.83492° / 180 (Eberswalde)
  
  float h = 0.0145; //Höhe der Sonne bei Aufgang halbes Bogenmaß der Sonne
 // float Aufgang;
 // float Untergang;
  
  int vorkommawert;
  int nachkommawert;
  
  int leap=0;
  long mytimer = 0;
  long mytimeout = 2000;
  // Tabelle Monatstage
  int monatstage[13] = {0, 0, 31, 59, 90, 121, 152, 182, 213, 244, 274, 305, 335 };
  
  //double dAzimuth;
  //double dElevation;
  float latitude; //double
  float longitude;     
  
  void setup_SONNENSTAND()
  {
  }
  void loop_SONNENSTAND()
  {
  latitude = Eberswalde_lat;
  longitude = Eberswalde_lon;
  //helios.calcSunPos(jahr,monat,tag, stunde-1, minute,sekunde,longitude,latitude); 
  helios.calcSunPos(jahr,monat,tag, stunde, minute,sekunde,longitude,latitude); 
  dAzimuth=helios.dAzimuth;
  dElevation=helios.dElevation;
  Serial.print(dElevation);
  if (dElevation < 0)
  {
    elevation_unter_horizont = 1;
    Serial.println(" Elevation UNTER Horizont");
  }
  else
  {
    elevation_unter_horizont = 0;
    Serial.println(" Elevation ÜBER Horizont");

    
    merker_waagerecht = 0;
  
  }
 // Serial.println(dElevation);
  y_position_soll = dElevation/2;  //alle errechneten 2,0 Grad Position ändern
  
  //x_position_soll = (dAzimuth + 30)*motorkonstante_horizontal;
  x_position_soll = (dAzimuth)*motorkonstante_horizontal;
  show("Elevat in Schritten ",y_position_soll,true);
  delay(80);
  //y_richtung = ab;
  
  if (debug == 1) {
  show("Azimuth",dAzimuth,false);
  Serial.print("\t");
  show(" Elevation ",dElevation,true);
  } }
  
   // Neuer Befehl show
  void show(char nameStr[], double val, boolean newline) {
    Serial.print(nameStr);  
    Serial.print("= ");
    if (newline)
         Serial.println(val);
    else Serial.print(val);
  }
  void Sonnenaufgang() {
  
    tagnummer_berechnen();
  zeitgleichung = -0.171*sin(0.0337*tagnummer + 0.465)-0.1299*sin(0.01787+tagnummer -0.168);
  if (debug == 1) {
  Serial.print("Zeitgleichung: ");
  Serial.println(zeitgleichung);
  }
  Deklination = 0.4095*sin(0.016906*(tagnummer-80.086)) ;
  if (debug == 1) {
  Serial.print("Deklination: ");
  Serial.println(Deklination);
  }
  Zeitdifferenz = 12*acos((sin(h) - sin(B)*sin(Deklination)) / (cos(B)*cos(Deklination)))/Pi; 
  
  if (debug == 1) {
    Serial.print("Zeitdifferenz: ");Serial.println(Zeitdifferenz);
  }
  Aufgang  = 12 - Zeitdifferenz - zeitgleichung - longitude/15 +B ;
  Untergang  = 12 + Zeitdifferenz - zeitgleichung - longitude/15 +0.5 +B; 
  vorkommawert = Aufgang;
  nachkommawert = (Aufgang-vorkommawert)*60; //in Minuten
  if (debug == 1) {
  Serial.print("Aufgang: ");
  Serial.println(Aufgang, DEC);
  Serial.print("Zeit Aufgang: ");
  Serial.print(vorkommawert);
  Serial.print(":");
  Serial.println (nachkommawert);
  Serial.print("Untergang: ");
  Serial.println(Untergang, DEC);
  Serial.print("Zeit Untergang: ");
  vorkommawert = Untergang;
  nachkommawert = (Untergang-vorkommawert)*60; //in Minuten
  Serial.print(vorkommawert);
  Serial.print(":");
  Serial.println (nachkommawert);
  Serial.print("Winkel Aufgang: ");
  Serial.println(15 * Aufgang);
  Serial.print("Winkel Untergang: ");
  Serial.println(15 * Untergang);
  }}
  void tagnummer_berechnen()
  {  
    tagnummer = tag + monatstage[monat];
    isLeapYear ();
    if (leap == 0)
    {
      if (monat > 2)
      { tagnummer++; }
      if (debug == 1) {
      Serial.println("Es ist ein Schaltjahr");
       }}
  else
  {if (debug == 1) {
  Serial.println("Es ist kein Schaltjahr");  
  }
     Serial.print("Tagnummer: ");
     Serial.println(tagnummer);
  }}
  void isLeapYear ()
  {
    /*
    1. Ein Jahr ist ein Schaltjahr, wenn es restlos durch 4 teilbar ist.
    2. Falls sich die Jahrzahl durch 100 restlos teilen lässt, ist es kein Schaltjahr.
    3. Falls auch eine Teilung durch 400 ganzzahlig möglich ist, dann ist es ein Schaltjahr.
    */
     leap = jahr % 4; // Modulo, wenn leap = 0 dann Schaltjahr
  }
