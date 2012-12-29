/**
 @file
 Diagnostics print library - logger level settings management
 
 @author Ryan Powell
 @date 03-10-11
 @copyright Copyright (c) 2011  Ryan Powell 
 @licence http://www.opensource.org/licenses/BSD-3-Clause
 */


#ifndef _LOGGER_LEVELMANAGEMENT_H
#define _LOGGER_LEVELMANAGEMENT_H


#ifdef __cplusplus
extern "C" {
#endif


#include "logger.h"
#include "logger_common.h"


/**
 @brief from a given character get the associated LOGGER_LEVEL
 @details conversions types below \n
 '>' <-> LOGGER_LEVEL_ENTRY \n
 '<' <-> LOGGER_LEVEL_EXIT \n
 'i'/'I' <-> LOGGER_LEVEL_INFO \n
 'w'/'W' <-> LOGGER_LEVEL_WARN \n
 'e'/'E' <-> LOGGER_LEVEL_ERROR
 'f'/'F' <-> LOGGER_LEVEL_FATAL
 'a'/'A' <-> LOGGER_LEVEL_ASSERT \n
 'v'/'V' <-> LOGGER_LEVEL_EVENT \n
 @return returns not #LOGGER_LEVEL_NONE on success
 */
LOGGER_LEVEL loggerFlags_level_charToLevel ( char loggerChar );


/**
 @brief from a given string convert into #LOGGER_LEVEL_FLAGS
 @param[in] loggerLevel NULL terminated string of logger level chars
 @param[in] loggerLevelLen Number of characters in above char array to examine
 @return returns all flags from string
 */
LOGGER_LEVEL_FLAGS loggerFlags_level_stringToFlags ( char * loggerLevel, size_t loggerLevelLen );


/**
 @brief add #LOGGER_LEVEL to handlePrv
 @param[in] handlePrv handle to logger to be changed
 @param[in] loggerLevel level to be added
 */
void logger_level_add ( LOGGER_HANDLE_PRV * handlePrv, LOGGER_LEVEL loggerLevel );


/**
 @brief remove #LOGGER_LEVEL to handlePrv
 @param[in] handlePrv handle to logger to be changed
 @param[in] loggerLevel level to be removed
 */
void logger_level_remove ( LOGGER_HANDLE_PRV * handlePrv, LOGGER_LEVEL loggerLevel );


/**
 @brief test if #LOGGER_LEVEL is enabled in handlePrv
 @param[in] handlePrv handle to logger to be tested
 @param[in] loggerLevel level to test for
 @return #true on success
 */
bool logger_level_isEnabled ( LOGGER_HANDLE_PRV * handlePrv, LOGGER_LEVEL loggerLevel );

    
#ifdef __cplusplus
}
#endif


#endif
