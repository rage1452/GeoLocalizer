//
//  main.c
//  GL_GPSFunctions
//
//  Created by Mario Coutino on 6/19/14.
//  Copyright (c) 2014 Mario Coutino. All rights reserved.
//

#include <stdio.h>
#include "GL_GPSFunctions.h"

void changeMsg(GPSMessage* msg)
{
    msg->hour = "hola";
}

int main(int argc, const char * argv[])
{
    printf("Probando Rutinas con Strings..\n");
    printf("---------------------------------\n");
    
    char* str = "4043.8432";
    
    float gpsCoord = GPSdegreeToDouble(str);
    
    printf("Cordenada Original: %s\n", str);
    
    printf("Coordenada Transformada: %.8f\n", gpsCoord);
    
    char* testStr = "$GPRMC,155123.000,A,4043.8432,N,07359.7653,W,0.15,83.25,200407,,*28";
    
    GPSMessage myMsg;
    
    printf("Cadena de GPS:\n %s\n", GPSparseMessage(testStr, &myMsg));
    
    printf("%s\n", myMsg.hour);
    printf("%s\n", myMsg.status);
    printf("%s\n", myMsg.lat);
    printf("%s\n", myMsg.latH);
    printf("%s\n", myMsg.lon);
    printf("%s\n", myMsg.lonH);
    
    return 0;
}


