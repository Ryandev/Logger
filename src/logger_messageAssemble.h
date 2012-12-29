/**
 @file
 Diagnostics print library - message assembly
 
 @author Ryan Powell
 @date 03-10-11
 @copyright Copyright (c) 2011  Ryan Powell 
 @licence http://www.opensource.org/licenses/BSD-3-Clause
 */


#ifndef _LOGGER_MESSAGEASSEMBLE_H
#define _LOGGER_MESSAGEASSEMBLE_H


#ifdef __cplusplus
extern "C" {
#endif


#include <stdint.h>

#include "logger.h"
#include "logger_common.h"


/**
 @def LOGGER_SEPERATOR_CHAR
 @brief character seperator used to split each aspect of logger entry
 */
#define LOGGER_SEPERATOR_CHAR ('|')
#define LOGGER_SEPERATOR_CHAR_SIZE (1)

/* sizes include terminating \0 char */
#define LOGGER_TIMESTAMP_SIZE        (18U)     /* size of the timestamp string */
#define LOGGER_FUNCTIONNAME_SIZE     (62U)
#define LOGGER_FILENAME_SIZE         (20U)
#define LOGGER_LINENUMBER_SIZE       (6U)
#define LOGGER_SEVERITY_SIZE         (6U)
#define LOGGER_MESSAGE_SIZE          (1024U)


/**
 @def LOGGER_MAX_LOGGER_CHARS
 @brief max size of user print message
 */
#define LOGGER_MAX_LOGGER_CHARS \
    ( LOGGER_TIMESTAMP_SIZE + \
    LOGGER_FUNCTIONNAME_SIZE + \
    LOGGER_FILENAME_SIZE + \
    LOGGER_LINENUMBER_SIZE + \
    LOGGER_SEVERITY_SIZE + \
    LOGGER_MESSAGE_SIZE )


/**
 @def LOGGER_LOG_ENTRY_SIZE
 @brief maxumum size per entry in log
 */
#define LOGGER_LOG_ENTRY_SIZE ( LOGGER_TIMESTAMP_SIZE + LOGGER_SEPERATOR_CHAR_SIZE + LOGGER_FUNCTIONNAME_SIZE + LOGGER_SEPERATOR_CHAR_SIZE + LOGGER_FILENAME_SIZE + LOGGER_SEPERATOR_CHAR_SIZE + LOGGER_LINENUMBER_SIZE + LOGGER_SEPERATOR_CHAR_SIZE + LOGGER_MAX_LOGGER_CHARS )


/**
 @brief from the given message properties write to string assembling output
 @param[in] string string to write to
 @param[in] string_size max chars to write into string
 @param[in] timestamp NULL terminated string detailing current momemnt of time
 @param[in] filename NULL terminated string of filename (filename without path)
 @param[in] linenumber NULL terminated string of linenumber
 @param[in] functioname NULL terminated string of functionname
 @param[in] severity NULL terminated string of severity
 @param[in] message NULL terminated string of message
 */
void logger_assemble_string ( char * string, size_t string_size, char * timestamp, char * filename, char * linenumber, char * functionname, char * severity, char * message );


/**
 @brief from a given level generate string representation
 @param[in] level logger level
 @param[out] stringSeverity returned logger level string
 @param[in] stringSize maximum chars to write to stringSeverity
 */
void loggerLevelStringFromLevel ( LOGGER_LEVEL level, char * stringSeverity, uint8_t stringSize );


/**
 @brief remove path from filename. leaving just the filename
 @details if filename is equal to /home/user/app/class/object.m returned string will be equal to object.m
 @param[out] stringFileName returned shorthand of filename
 @param[in] stringSize maximum number of chars to write to stringFilename
 @param[in] filename input filename with/without filepath
 */
void loggerFileNameString ( char * stringFileName, uint8_t stringSize, char * filename );



#define LOGGER_TIMESTAMP_CHARS_MINIMUM 17


/**
 @brief create current timestamp
 @details create in format printf("%02d:%02d:%02d %02d/%02d/%02d",hr,min,seconds,day,month,year)
 @param[out] stringTimeStamp timestamp string to write to
 @param[in] stringSize maximum number of chars to write timestamp to. must be greater than equal to #LOGGER_TIMESTAMP_CHARS_MINIMUM
 */
void loggerGetTimeString ( char * stringTimestamp, size_t stringSize );

    
#ifdef __cplusplus
}
#endif


#endif
