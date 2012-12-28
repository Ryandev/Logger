/**
 @file
 Diagnostics print library - logger level settings management
 
 @author Ryan Powell
 @date 03-10-11
 @copyright Copyright (c) 2011  Ryan Powell 
 @licence http://www.opensource.org/licenses/BSD-3-Clause
 */


#include "logger_levelManagement.h"

static LOGGER_LEVEL_FLAGS logger_level_flags ( LOGGER_LEVEL loggerLevel );


LOGGER_LEVEL loggerFlags_level_charToLevel ( char loggerChar )
{
    LOGGER_LEVEL loggerLevel = LOGGER_LEVEL_NONE;
    
    switch ( loggerChar )
    {
        case '>' :
            loggerLevel = LOGGER_LEVEL_ENTRY;
            break;
            
        case '<' :
            loggerLevel = LOGGER_LEVEL_EXIT;
            break;
            
        case 't' :
        case 'T' :
            loggerLevel = LOGGER_LEVEL_TRACE;
            break;
            
        case 'i' :
        case 'I' :
            loggerLevel = LOGGER_LEVEL_INFO;
            break;
            
        case 'w' :
        case 'W' :
            loggerLevel = LOGGER_LEVEL_WARN;
            break;
            
        case 'e' :
        case 'E' :
            loggerLevel = LOGGER_LEVEL_ERROR;
            break;
            
        case 'f' :
        case 'F' :
            loggerLevel = LOGGER_LEVEL_FATAL;
            break;
            
        case 'a' :
        case 'A' :
            loggerLevel = LOGGER_LEVEL_ASSERT;
            break;
            
        case 'v' :
        case 'V' :
            loggerLevel = LOGGER_LEVEL_EVENT;
            break;
            
        default :
            LOGPRINT_LOG_E("Unrecognised character: %c !!!",loggerChar);
            break;
    }
    
    return loggerLevel;
}

LOGGER_LEVEL_FLAGS loggerFlags_level_stringToFlags ( char * loggerLevel, uint32_t loggerLevelLen )
{
    LOGGER_LEVEL_FLAGS flags = 0U;
    
    if ( loggerLevel )
    {
        for ( uint32_t i=0U; i<loggerLevelLen; i++ )
        {
            if ( loggerLevel[i] != '\0' )
            {
                flags |= (LOGGER_LEVEL_FLAGS)loggerFlags_level_charToLevel(loggerLevel[i]);
            }
            else
            {
                break;
            }
        }
    }
    
    return flags;
}

/* convert enum to flag bit form */
static LOGGER_LEVEL_FLAGS logger_level_flags ( LOGGER_LEVEL loggerLevel )
{
    return (LOGGER_LEVEL_FLAGS)loggerLevel;
}

void logger_level_add ( LOGGER_HANDLE_PRV * handlePrv, LOGGER_LEVEL loggerLevel )
{
    if ( handlePrv )
    {
        handlePrv->loggerLevelsEnabled = handlePrv->loggerLevelsEnabled | logger_level_flags(loggerLevel);
    }
}

void logger_level_remove ( LOGGER_HANDLE_PRV * handlePrv, LOGGER_LEVEL loggerLevel )
{
    if ( handlePrv )
    {
        handlePrv->loggerLevelsEnabled = handlePrv->loggerLevelsEnabled & ~logger_level_flags(loggerLevel);
    }
}

bool logger_level_isEnabled ( LOGGER_HANDLE_PRV * handlePrv, LOGGER_LEVEL loggerLevel )
{
    bool loggerEnabled = false;
    
    if ( handlePrv )
    {
        if ( (handlePrv->loggerLevelsEnabled) & logger_level_flags(loggerLevel) )
        {
            loggerEnabled = true;
        }
    }
    
    return loggerEnabled;
}
