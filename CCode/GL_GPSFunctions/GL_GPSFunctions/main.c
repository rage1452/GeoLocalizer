//
//  main.c
//  GL_GPSFunctions
//
//  Created by Mario Coutino on 6/19/14.
//  Copyright (c) 2014 Mario Coutino. All rights reserved.
//

#include <stdio.h>
#include "GL_GPSFunctions.h"
#include "GL_UARTFunctions.h"

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
    
    char* testStr = GPSgetMessage(); // To switch between the two GPS string available
                                     // one with satellite data and one without, it is
                                     // necessary to comment the char* declaration
                                     // in the UARTdebug() function.
    
    GPSMessage myMsg;
    
    printf("Cadena de GPS:\n %s\n", GPSparseMessage(testStr, &myMsg));
    
    printf("Hora:\t\t%s\n", myMsg.hour);
    printf("Status:\t\t%s\n", myMsg.status);
    printf("Latitud:\t%s\n", myMsg.lat);
    printf("Latitud H:\t%s\n", myMsg.latH);
    printf("Longitud:\t%s\n", myMsg.lon);
    printf("Longitud H:\t%s\n", myMsg.lonH);
    
    printf("Latitud(Degrees):\t %.8f\n", GPSgetLat(myMsg));
    printf("Longitud(Degrees):\t %.8f\n", GPSgetLon(myMsg));
    printf("Hora Local: \t\t%s\n",GPSgetHour(myMsg));
    printf("Servicio: \t\t%d\n",GPSisOK(myMsg));
    
    printf("%s\n",GPSgetMessage());
    
    return 0;
}


