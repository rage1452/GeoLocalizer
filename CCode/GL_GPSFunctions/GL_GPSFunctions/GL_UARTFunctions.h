//
//  GL_UARTFunctions.h
//  GL_GPSFunctions
//
//  Created by Mario Coutino on 6/21/14.
//  Copyright (c) 2014 Mario Coutino. All rights reserved.
//

#ifndef GL_GPSFunctions_GL_UARTFunctions_h
#define GL_GPSFunctions_GL_UARTFunctions_h

#define UART_ON 1
#define UART_OFF 0

char UARTdebug(void)
{
    /*
     Debugging Function to test UARTdataRead integration.
     @param (void)
     @return char w/ a constant value for debug
     */
    
    static int count = 0;
    
    if (count++ < 5) {
        return 'a';
    }
    else{
        count = 0;
        return '\n';
    }
}

char UARTdataRead(void)
{
    /*
     Returns the read character from the active Serial Communication.
     @param (void)
     @return char read from the UART buffer
     */
    
    // @Function Not Implemented Yet!
    
    // The debugging call must be changed!
    return UARTdebug();
}

int UARTisAvailable(void)
{
    /*
     Checks if the UART module is available to transmit the buffer.
     Returns '1' if it is available or '0' otherwise.
     @param (void)
     @return int {1,0} w/ the readiness state of the UART module
     */
    
    // For Debug state is always ready {1}
    return UART_ON;
}

#endif
