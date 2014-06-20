#define BUFFSIZE 90

char myChar;
String myStr = "";
char myBuffer[BUFFSIZE];

int buffIndx = 0;

//-------------------------------------------------
String etiqueta = "$GPRMC";
String longitud;      // deg-xx.xx
String latitud;      // deg-xx.xx
String horaServer;// hhmmss
String statusGPS; // A = OK , V = WARNING
String hemLat;    // N - S{-1}
String hemLong;   // E - W{-1}
//-------------------------------------------------

void setup() 
{
  // Open serial communications and wait for port to open:
  Serial3.begin(9600);
  Serial.begin(9600);
//  char xxx = '' 
}

void loop() // run over and over
{
  if (Serial3.available()){
    
    myChar = Serial3.read();
    
    if (myChar == '\n'){
      
      Serial.println(parseGPSString(myStr));
      
      convGrados(longitud);      
      
      myStr = "";
      
    }
    else{
      myStr = myStr + myChar;
      
    }
  }

}

String parseGPSString(String str)
{
  int commaPosition;
  int chunkNum = 1;
  String tmpStr;
  
  commaPosition = str.indexOf(',');
  
  tmpStr = str.substring(0,commaPosition);   // asigna subString a tmpStr
  str = str.substring(commaPosition + 1, str.length());  // borra chunk actual hasta la coma
  
  if (tmpStr == etiqueta)
  {
    do {
      commaPosition = str.indexOf(',');
    
      if(commaPosition != -1){
      
        tmpStr = str.substring(0,commaPosition);   // asigna subString a tmpStr
        str = str.substring(commaPosition + 1, str.length());  // borra chunk actual hasta la coma
        
        //Serial.println(tmpStr);
        switch(chunkNum){
            case 1:    // hora
              horaServer = tmpStr;
              break;
            case 2:    // status
              statusGPS = tmpStr;
              break;
            case 3:    // lat
              latitud = tmpStr;
              break;
            case 4:    // hemlat
              hemLat = tmpStr;
              break;
            case 5:    // long
              longitud = tmpStr;
              break;
            case 6:    // hemlong
              hemLong = tmpStr;
              break;
         }
       }
      chunkNum++;
    }while(chunkNum <= 6);
} 
  return (horaServer + " - " + statusGPS + " - " + latitud + " - " + hemLat + " - " + longitud + " - " + hemLong);
}

void convGrados(String Grados)
{
  int Pos = Grados.indexOf('.');
  String Grd, centMin, Dec;
  float grdOut;
  
  centMin = Grados.substring(Pos + 1, Grados.length()); 
  Dec = Grados.substring(Pos - 2, Pos); 
  Grd = Grados.substring(0, Pos - 2);
  
  //centMin = String();
  
  grdOut = float(Grd.toInt()) + float(Dec.toInt()/60.0) + float(centMin.toInt()/6000000.0);
  
  Serial.println(float(centMin.toInt()/6));
}
