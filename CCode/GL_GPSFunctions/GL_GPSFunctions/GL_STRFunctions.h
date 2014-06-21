//
//  GL_STRFunctions.h
//  GL_GPSFunctions
//
//  Created by Mario Coutino on 6/20/14.
//  Copyright (c) 2014 Mario Coutino. All rights reserved.
//

#ifndef GL_GPSFunctions_GL_STRFunctions_h
#define GL_GPSFunctions_GL_STRFunctions_h

#include <stdlib.h>
#include <string.h>

int indexOf(char* str, char c)
{
    
    /*
     Returns the first incidence of the desired character 'c'
     in the string 'str'.
     @param (char*, char)
     @return int w/ the position, -1 otherwise
     */
    
    int charPos = -1;
    int i = 0;
    
    do {
        if (*str++ == c) {
            charPos = i;
            break;
        }
        i++;
    } while (*str != '\0');
    
    return charPos;
}

char* getSubString(char* str, int startPos, int endPos)
{
    /*
     Gets the substring 'subStr' from the string 'str' from the
     startPos until endPos (Not including endPos).
     subStr <- str[starPos, endPos)
     @param (char*, int, int)
     @return char* w/ the substring
     */
    
    int strSize = endPos - startPos;
    char* subStr = malloc(strSize * sizeof(char));
    
    int i;
    
    for (i = startPos; i < endPos; i++) {
        *subStr++ = *(str+i);
    }
    
    *subStr = '\0';
    
    return (subStr - strSize);
    
}

int getStrLen(char* str)
{
    /*
     Gets the lenght of the desired string 'str'.
     @param (char*)
     @return int w/ the string's lenght
     */
    
    int i = 0;
    do {
        i++;
    } while (*++str != '\0');
    
    return i;
}


char* strCopy(char* str)
{
    /*
     Return a new allocated copy of the string 'str'.
     */
    
    return getSubString(str, 0, getStrLen(str));
}

double str2Double(const char* c)
{
    /*
     Wrapper fuction to convert a string into double.
     In the case that 'atoi()' function is not supported, only
     change the implementation of this function.
     @param (const char*)
     @return double w/ the numerical representation of the string.
     */
    
    return (double)atoi(c);
}


#endif
