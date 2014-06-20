//
//  GL_GPSFunctions.h
//  GL_GPSFunctions
//
//  Created by Mario Coutino on 6/19/14.
//  Copyright (c) 2014 Mario Coutino. All rights reserved.
//

#ifndef GL_GPSFunctions_GL_GPSFunctions_h
#define GL_GPSFunctions_GL_GPSFunctions_h

#include "GP_STRFunctions.h"
#include <math.h>

double GPSdegreeToDouble(char* valueGPS)
{
    /*
     Converts the string 'valueGPS' w/ a coordinate value into its Double representation.
     This representation is in the format %degrees.centDegrees%.
     @param (char*)
     @return double w/ the representation in degrees and decimal of degree.
     */
    
    int pos = indexOf(valueGPS, '.');
    char* deg;
    char* min;
    char* dec;
    
    dec = getSubString(valueGPS, pos + 1, getStrLen(valueGPS));
    min = getSubString(valueGPS, pos - 2, pos);
    deg = getSubString(valueGPS, 0, pos - 2);
    
    return str2Double(deg) + str2Double(min)/60.0 + str2Double(dec)/(60 * pow(10.0, (double)getStrLen(dec)));
    
}

char* GPSparseMessage(char* str, char* hour, char* status, char* lat, char* lon, char* latH, char* lonH)
{
    int pntPos;
    int chunkNum = 1;
    char* tmpStr;
    
    pntPos = indexOf(str, '.');
    
    tmpStr = getSubString(str, 0, pntPos);
    str = getSubString(str, pntPos + 1, getStrLen(str));
    
    if (strcmp(tmpStr, "$GPRMC") == 0) {
        do{
            pntPos = indexOf(str, '.');
            
            if (pntPos != -1) {
                tmpStr = getSubString(str, 0, pntPos);
                str = getSubString(str, pntPos + 1, getStrLen(str));
                
                switch (chunkNum) {
                    case 1:
                        hour = tmpStr;
                        break;
                        
                    case 2:
                        status = tmpStr;
                        break;
                        
                    case 3:
                        lat = tmpStr;
                        break;
                    
                    case 4:
                        latH = tmpStr;
                        break;
                        
                    case 5:
                        lon = tmpStr;
                        break;
                        
                    case 6:
                        lonH = tmpStr;
                        break;
                        
                    default:
                        break;
                }
            }
            
            chunkNum++;
            
        }while (chunkNum <= 6);
    }
    
    char outStr[90];
    
    strcpy(outStr, "$GPRMC");
    strcat(outStr, hour);
    strcat(outStr, " - ");
    strcat(outStr, status);
    strcat(outStr, " - ");
    strcat(outStr, lat);
    strcat(outStr, " - ");
    strcat(outStr, latH);
    strcat(outStr, " - ");
    strcat(outStr, lon);
    strcat(outStr, " - ");
    strcat(outStr, lonH);
    strcat(outStr, " - ");

    printf("%s", outStr);
    
    return outStr;
}

/*
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
*/

#endif
