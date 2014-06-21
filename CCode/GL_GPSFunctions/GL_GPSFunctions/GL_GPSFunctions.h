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

typedef struct{
    char* hour;
    char* status;
    char* lat;
    char* lon;
    char* latH;
    char* lonH;
}GPSMessage;

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

char* GPSparseMessage(char* str, char** hour, char** status, char** lat, char** lon, char** latH, char** lonH)
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
                        *hour = strCopy(tmpStr);
                        break;
                        
                    case 2:
                        *status = strCopy(tmpStr);
                        break;
                        
                    case 3:
                        *lat = strCopy(tmpStr);
                        break;
                    
                    case 4:
                        *latH = strCopy(tmpStr);
                        break;
                        
                    case 5:
                        *lon = strCopy(tmpStr);
                        break;
                        
                    case 6:
                        *lonH = strCopy(tmpStr);
                        break;
                        
                    default:
                        break;
                }
            }
            
            chunkNum++;
            
        }while (chunkNum <= 6);
    }
    
    char outStr[90];
    
    strcpy(outStr, "$GPRMC - ");
    strcat(outStr, *hour);
    strcat(outStr, " - ");
    strcat(outStr, *status);
    strcat(outStr, " - ");
    strcat(outStr, *lat);
    strcat(outStr, " - ");
    strcat(outStr, *latH);
    strcat(outStr, " - ");
    strcat(outStr, *lon);
    strcat(outStr, " - ");
    strcat(outStr, *lonH);
    
    return outStr;
}

#endif
