/**
 @file
 Diagnostics print library - message assembly
 
 @author Ryan Powell
 @date 03-10-11
 @copyright Copyright (c) 2011  Ryan Powell 
 @licence http://www.opensource.org/licenses/BSD-3-Clause
 */


#include <time.h>
#include <stdio.h>

#include "logger.h"
#include "logger_messageAssemble.h"


#define LOGGER_LOG_ENTRY_FORMAT ("%s%c%s%c%s%c%s%c%s%c%s")


void logger_assemble_string ( char * string, uint32_t string_size, char * timestamp, char * filename, char * linenumber, char * functionname, char * severity, char * message )
{
    snprintf( (char*)(string), (string_size), LOGGER_LOG_ENTRY_FORMAT, \
             (char*)(timestamp), LOGGER_SEPERATOR_CHAR, \
             (char*)(filename), LOGGER_SEPERATOR_CHAR, \
             (char*)(linenumber), LOGGER_SEPERATOR_CHAR, \
             (char*)(functionname), LOGGER_SEPERATOR_CHAR, \
             (char*)(severity), LOGGER_SEPERATOR_CHAR, \
             (char*)(message) );
}

void loggerLevelStringFromLevel ( LOGGER_LEVEL level, char * stringSeverity, uint8_t stringSize )
{
    char * levelStr = NULL;
    
    switch ( level )
    {
        case LOGGER_LEVEL_ENTRY:
            levelStr = "-->";
            break;
            
        case LOGGER_LEVEL_EXIT:
            levelStr = "<--";
            break;
            
        case LOGGER_LEVEL_INFO:
            levelStr = "INFO";
            break;
            
        case LOGGER_LEVEL_WARN:
            levelStr = "WARN";
            break;
            
        case LOGGER_LEVEL_ERROR:
            levelStr = "ERROR";
            break;
            
        case LOGGER_LEVEL_FATAL:
            levelStr = "FATAL";
            break;
            
        case LOGGER_LEVEL_ASSERT:
            levelStr = "ASSRT";
            break;
            
        case LOGGER_LEVEL_EVENT:
            levelStr = "EVENT";
            break;
            
        default:
            levelStr = "?????";
            LOGPRINT_LOG_E("Unrecognised logger level %d",level);
            break;
    }
    
    snprintf((char *)stringSeverity, stringSize, "%s",(char*)levelStr);
}

void loggerGetTimeString ( char * stringTimestamp, uint8_t stringSize )
{
    time_t  t = time(NULL);
    struct  tm *tme = localtime(&t);
    
    snprintf((char*)stringTimestamp, (size_t)stringSize, "%02d:%02d:%02d %02d/%02d/%02d",
             tme->tm_hour, tme->tm_min, tme->tm_sec, tme->tm_mday, (tme->tm_mon+1), (tme->tm_year+1900)%1000 );
}
