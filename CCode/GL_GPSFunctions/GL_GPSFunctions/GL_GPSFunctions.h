//
//  GL_GPSFunctions.h
//  GL_GPSFunctions
//
//  Created by Mario Coutino on 6/19/14.
//  Copyright (c) 2014 Mario Coutino. All rights reserved.
//

#ifndef GL_GPSFunctions_GL_GPSFunctions_h
#define GL_GPSFunctions_GL_GPSFunctions_h

#include "GL_STRFunctions.h"
#include "GL_UARTFunctions.h"

#include <math.h>

#define GPS_ON 1
#define GPS_OFF 0
#define GPS_ERROR -1

typedef struct{
    char* hour;
    char* status;
    char* lat;
    char* lon;
    char* latH;
    char* lonH;
}GPSMessage;

char* GPSgetMessage()
{
    /*
     */
    
    char* gpsMsg = NULL;
    char* tmpPnt = NULL;
    char readChar;
    
    int count = 0;
    
    while (1) {
        if (UARTisAvailable()) {
            readChar = UARTdataRead();
            count++;
        }
    }
    
    return gpsMsg;
}

int GPSisOK(GPSMessage msg)
{
    /*
     Returns the status of the satellite server.
     @param (GPSMessage)
     @return int w/ '1' if the server is active, '-1' otherwise.
     */
    
    if (strcmp(msg.status, "A") == 0) {
        return GPS_ON;
    }
    else
    {
        return GPS_OFF;
    }
}

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

double GPSgetCordinate(char* valueGPS, char* hem)
{
    /*
     Wrapper function to assign the correct sign to the information in the GPSValue.
     When hem is South (S) or West(W) the GPS coordinates must be negative, possitive 
     otherwise.
     @param (char*, char*)
     @return double w/ the correct sign.
     */
    
    double value = GPSdegreeToDouble(valueGPS);
    
    if (strcmp(hem, "S") == 0 || strcmp(hem, "W") == 0) {
        value *= -1;
    }
    
    return value;
}

double GPSgetLat(GPSMessage msg)
{
    /*
     Returns the double value of the Latitude.
     @param (GPSMessage)
     @return double w/ latitude. Returns -1 if the server is innactive.
     */
    
    if (GPSisOK(msg)) {
        return GPSgetCordinate(msg.lat, msg.latH);
    }
    else{
        return GPS_ERROR;
    }
}

double GPSgetLon(GPSMessage msg)
{
    /*
     Returns the double value of the Longitude.
     @param (GPSMessage)
     @return double w/ longitude. Returns -1 if the server is innactive.
     */
    
    if (GPSisOK(msg)) {
        return GPSgetCordinate(msg.lon, msg.lonH);
    }
    else{
        return GPS_ERROR;
    }
    
}

char* GPSgetHour(GPSMessage msg)
{
    /*
     Returns the hour is a formar hh:mm:ss.
     @param (GPSMessage)
     @return char* w/ the current satellite's hour.
     */
    
    char* tmpHour = malloc(6 * sizeof(char));
    
    strcpy(tmpHour, getSubString(msg.hour, 0, 2));
    strcat(tmpHour, ":");
    strcat(tmpHour, getSubString(msg.hour, 2, 4));
    strcat(tmpHour, ":");
    strcat(tmpHour, getSubString(msg.hour, 4, 6));
    
    return tmpHour;
    
}

char* GPSparseMessage(char* str, GPSMessage *msg)
{
    /*
     Parses the GPS message (str) and returning a pre-formatted string. The methods receives several arguments
     to store the important substrings in the GPS message.
     @param (char*, char*, char*, char*, char*, char*, char*)
     @return str w/ a pre-formatted GPS Message.
     */
    
    int pntPos;
    int chunkNum = 1;
    char* tmpStr;
    
    pntPos = indexOf(str, ',');
    
    tmpStr = getSubString(str, 0, pntPos);
    str = getSubString(str, pntPos + 1, getStrLen(str));
    
    if (strcmp(tmpStr, "$GPRMC") == 0) {
        do{
            pntPos = indexOf(str, ',');
            
            if (pntPos != -1) {
                tmpStr = getSubString(str, 0, pntPos);
                str = getSubString(str, pntPos + 1, getStrLen(str));
                
                switch (chunkNum) {
                    case 1:
                        //*hour = strCopy(tmpStr);
                        msg->hour = strCopy(tmpStr);
                        break;
                        
                    case 2:
                        msg->status = strCopy(tmpStr);
                        break;
                        
                    case 3:
                        msg->lat = strCopy(tmpStr);
                        break;
                    
                    case 4:
                        msg->latH = strCopy(tmpStr);
                        break;
                        
                    case 5:
                        msg->lon = strCopy(tmpStr);
                        break;
                        
                    case 6:
                        msg->lonH = strCopy(tmpStr);
                        break;
                        
                    default:
                        break;
                }
            }
            
            chunkNum++;
            
        }while (chunkNum <= 6);
    }
    
    
    char* outStr = malloc(60 * sizeof(char));
    
    strcpy(outStr, "$GPRMC - ");
    strcat(outStr, msg->hour);
    strcat(outStr, " - ");
    strcat(outStr, msg->status);
    strcat(outStr, " - ");
    strcat(outStr, msg->lat);
    strcat(outStr, " - ");
    strcat(outStr, msg->latH);
    strcat(outStr, " - ");
    strcat(outStr, msg->lon);
    strcat(outStr, " - ");
    return strcat(outStr, msg->lonH);
    
    
}



#endif
