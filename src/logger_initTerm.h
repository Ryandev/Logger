/**
 @file
 Diagnostics print library - initTerm behaviour
 
 @author Ryan Powell
 @date 03-10-11
 @copyright Copyright (c) 2011  Ryan Powell 
 @licence http://www.opensource.org/licenses/BSD-3-Clause
 */


#ifndef _LOGGER_INITTERM_H
#define _LOGGER_INITTERM_H


#ifdef __cplusplus
extern "C" {
#endif


#include <stdbool.h>

#include "logger.h"
#include "logger_template.h"
#include "logger_common.h"


/**
 @brief maintains initialization count & acts when appropriate
 @details must be called each time a new #LOGGER_HANDLE_PRV is created
 @param[in] handle handle to be destroyed
 @return #true on success
 */
bool logger_init ( void );


/**
 @brief opposite of #logger_init & will tear-down output connections when needed
 @details must be called before each #LOGGER_HANDLE_PRV is destroyed
 @param[in] handle handle to be destroyed
 @return #true on success
 */
bool logger_term ( void );


/**
 @brief get the current location of logger output
 @return !NULL on success
 */
char* logger_currentOutput ( void );


/**
 @brief get the current function handler for printing messages
 @return !NULL on success
 */
LOGGER_TEMPLATE_SEND logger_getPrintHandler ( void );

    
#ifdef __cplusplus
}
#endif


#endif /* _LOGGER_INITTERM_H */
