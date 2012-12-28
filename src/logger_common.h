/**
 @file
 Diagnostics print library - common defines
 
 @author Ryan Powell
 @date 03-10-11
 @copyright Copyright (c) 2011  Ryan Powell 
 @licence http://www.opensource.org/licenses/BSD-3-Clause
 */


#ifndef _LOGGER_COMMON_H
#define _LOGGER_COMMON_H


#ifdef __cplusplus
extern "C" {
#endif


#include <stdint.h>
#include <stdlib.h>


/**
 @brief current logger version
 */
#define LOGGER_VERSION 1.0f


/**
 @enum _LOGGER_STATUS
 @brief returned status codes from internal logger print functions \n
 #LOGGER_STATUS_OK all ok \n
 #LOGGER_STATUS_FAILURE generic failure \n
 #LOGGER_STATUS_FAILURE_NOT_WHOLE_MESSAGE_PRINTED failed to print whole message \n
 #LOGGER_STATUS_FAILURE_ALREADY_INITIALIZED could not initialize location as it is already set up
 #LOGGER_STATUS_FAILURE_ALREADY_TERMINATED could not terminate location as it is already terminated
 #LOGGER_STATUS_FAILURE_INVALID_MESSAGE could not print, invalid message
 #LOGGER_STATUS_FAILURE_INVALID_PARAM invalid parameter passed into function
 */
typedef enum _LOGGER_STATUS
{
    LOGGER_STATUS_UNDEF = 0,    
    LOGGER_STATUS_OK,
    LOGGER_STATUS_FAILURE,
    LOGGER_STATUS_FAILURE_NOT_WHOLE_MESSAGE_PRINTED,
    LOGGER_STATUS_FAILURE_ALREADY_INITIALIZED,
    LOGGER_STATUS_FAILURE_ALREADY_TERMINATED,
    LOGGER_STATUS_FAILURE_INVALID_MESSAGE,
    LOGGER_STATUS_FAILURE_INVALID_PARAM,
    LOGGER_STATUS_LAST_VALUE,    
} LOGGER_STATUS;


typedef uint32_t LOGGER_LEVEL_FLAGS;


/**
 @brief internal structure holding all variables per logger handle
 */
typedef struct _LOGGER_HANDLE_PRV
{
    LOGGER_LEVEL_FLAGS loggerLevelsEnabled;
} LOGGER_HANDLE_PRV;



#define logger_memAlloc malloc
#define logger_memFree free


/* Enable to trace any defects in DebugPrint */
/* #define LOGGER_PRINT_LOGGER */

#ifdef LOGGER_PRINT_LOGGER
#include <stdio.h>
#define LOGPRINT_LOG(level,format, ... ) \
do \
{ \
    fprintf (stdout,"logger %s (%s:%d): ",level,__FUNCTION__,__LINE__); \
    fprintf (stdout, format, ##__VA_ARGS__ ); \
    fprintf (stdout, "\n"); \
} while (0)

#define LOGPRINT_LOG_E(fmt, ... ) LOGPRINT_LOG("-ERROR-",fmt, ##__VA_ARGS__)
#define LOGPRINT_LOG_W(fmt, ... ) LOGPRINT_LOG("-WARN-",fmt, ##__VA_ARGS__)
#define LOGPRINT_LOG_I(fmt, ... ) LOGPRINT_LOG("-INFO-",fmt, ##__VA_ARGS__)

#define LOGPRINT_ASSERT(cond) \
if ( (cond) != true ) \
{ \
    LOGPRINT_LOG_E("Assertion failure (%s:%d)",__FILE__,__LINE__); \
}
#else
    #define LOGPRINT_LOG_E(fmt, ...) {}
    #define LOGPRINT_LOG_W(fmt, ...) {}
    #define LOGPRINT_LOG_I(fmt, ...) {}
    #define LOGPRINT_ASSERT(cond) {}
#endif

    
#ifdef __cplusplus
}
#endif


#endif /* _LOGGER_COMMON_H */
