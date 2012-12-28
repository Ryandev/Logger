/**
 @file
 Diagnostics print library - string utility calls
 
 @author Ryan Powell
 @date 28-07-12
 @copyright Copyright (c) 2011  Ryan Powell 
 @licence http://www.opensource.org/licenses/BSD-3-Clause
 */


#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>


#ifdef _WIN32
#define FILESYSTEM_DIRECTORY_SEPERATOR '\'
#else
#define FILESYSTEM_DIRECTORY_SEPERATOR '/'
#endif


void logger_string_fileNameFromPath ( char ** stringFileNameReturned, uint32_t * stringFileNameReturnedLen, const char * filePath, uint32_t filePathLen )
{
    uint32_t offsetForLocalPathOnly = 0U;
    uint32_t index = 0U;
    
    while ( ( index < filePathLen ) && ( filePath[index] != '\0' ) )
    {
        if ( filePath[index] == FILESYSTEM_DIRECTORY_SEPERATOR )
        {
            /* found it. Now as long as this isn't the last character */
            if ( index < filePathLen-1 )
            {
                offsetForLocalPathOnly = index+1;  /* +1 to ignore the / prefix */
            }
        }
        
        index++;
    }
    
    /* +1 to ignore the / prefix */
    snprintf(*stringFileNameReturned,(filePathLen - offsetForLocalPathOnly)+1U, "%s",(char*)&filePath[offsetForLocalPathOnly]);
    
    if ( stringFileNameReturnedLen )
    {
        *stringFileNameReturnedLen = filePathLen - offsetForLocalPathOnly;
    }
}

void logger_string_trimWhitespace ( char ** stringTrimmed, uint32_t * stringTrimmedLen, char * str, uint32_t strLen )
{
    if ( strLen == 0 )
    {
        stringTrimmed = 0;
        *stringTrimmedLen = 0;
        return;
    }
    
    const char *end;
    uint32_t out_size;
    
    /* Trim leading space */
    while ( isspace(*str) )
    {
        str++;
    }
    
    /* Is All spaces? */
    if ( *str == 0 )
    {
        *stringTrimmed = 0;
        *stringTrimmedLen = 1;
        return;
    }
    
    /* Trim trailing space */
    end = (str+strLen) - 1;

    while ( end > str && isspace(*end) )
    {
        end--;
    }

    end++;
    
    /* Set output size to minimum of trimmed string length and buffer size minus 1 */
    out_size = (end - str) < strLen-1 ? (end - str) : strLen-1;

    *stringTrimmed = str;
    
    *stringTrimmedLen = out_size;
}

void logger_string_trimFileNameExtension ( uint32_t * stringTrimmedLen, char * str, uint32_t strLen )
{
    uint32_t offsetForLocalPathOnly = strLen;
    uint32_t index = strLen;
    
    while ( index > 0U )
    {
        if ( str[index] == '.' )
        {
            /* found it. Now as long as this isn't the last character */
            if ( index > 1 )
            {
                offsetForLocalPathOnly = index;
                break;
            }
        }
        
        index--;
    }
    
    *stringTrimmedLen = offsetForLocalPathOnly;
}

char* logger_string_findFirstOccurenceOfChar ( const char* str, const char searchChar )
{
    while ( ( (void*)*str != NULL ) &&
           ( (char)*str != searchChar ) )
    {
        str += 1U;
    }
    
    return (char*)str;
}

uint32_t logger_string_numberOfOccurencesOfChar ( const char* str, uint32_t strLen, const char searchChar )
{
    uint32_t matchCount = 0U;

    for ( uint32_t i=0U; i<strLen; i++ )
    {
        char cmp = str[i];
        
        if ( cmp == searchChar )
        {
            matchCount += 1U;
        }
    }
    
    return matchCount;
}
