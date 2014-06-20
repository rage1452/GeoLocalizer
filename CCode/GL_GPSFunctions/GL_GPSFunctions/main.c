//
//  main.c
//  GL_GPSFunctions
//
//  Created by Mario Coutino on 6/19/14.
//  Copyright (c) 2014 Mario Coutino. All rights reserved.
//

#include <stdio.h>
#include "GL_GPSFunctions.h"

int main(int argc, const char * argv[])
{
    printf("Probando Rutinas con Strings..\n");
    printf("---------------------------------\n");
    
    char* str = "4043.8432";
    
    float gpsCoord = GPSdegreeToDouble(str);
    
    printf("Cordenada Original: %s\n", str);
    
    printf("Coordenada Transformada: %.8f\n", gpsCoord);
    
    char* hour;
    char* status;
    char* lat;
    char* lon;
    char* latH;
    char* lonH;
    
    // Some Issues...
    //printf("Cadena de GPS: %s", GPSparseMessage(str, hour, status, lat, lon, latH, lonH));
    
    return 0;
}


