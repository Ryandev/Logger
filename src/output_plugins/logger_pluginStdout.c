/**
 @file
 Diagnostics print library - print-stdout plugin
 
 @author Ryan Powell
 @date 03-10-11
 @copyright Copyright (c) 2011  Ryan Powell 
 @licence http://www.opensource.org/licenses/BSD-3-Clause
 */


#include <pthread.h>
#include <stdio.h>

#include "logger_PluginStdout.h"


static pthread_mutex_t f_mutex_print = PTHREAD_MUTEX_INITIALIZER;

static FILE * f_logger_stdout = NULL;


LOGGER_STATUS logger_stdout_initialize ( LOGGER_INI_SECTIONHANDLE paramBag )
{
    LOGGER_STATUS status = LOGGER_STATUS_FAILURE_INVALID_MESSAGE;
    
    if ( f_logger_stdout == NULL )
    {
        f_logger_stdout = stdout;
        LOGPRINT_LOG_I("Set output to stdout");
        status = LOGGER_STATUS_OK;
    }
    else
    {
        LOGPRINT_LOG_E("already initialized (%s)");
        status = LOGGER_STATUS_FAILURE_ALREADY_INITIALIZED;
    }

    return status;
}

LOGGER_STATUS logger_stdout_terminate ( void )
{
    LOGGER_STATUS status = LOGGER_STATUS_FAILURE;
    
    if ( f_logger_stdout )
    {
        f_logger_stdout = NULL;
        LOGPRINT_LOG_I("Disabled output from stdout");
        status = LOGGER_STATUS_OK;
    }
    else
    {
        LOGPRINT_LOG_E("already terminated (%s)",__FUNCTION__);
        status = LOGGER_STATUS_FAILURE_ALREADY_TERMINATED;
    }

    return status;
}

LOGGER_STATUS logger_stdout_transmit ( char * msg, uint32_t msgLen )
{
    LOGGER_STATUS status = LOGGER_STATUS_FAILURE_INVALID_MESSAGE;
    
    LOGPRINT_ASSERT(f_logger_stdout!=NULL);
    LOGPRINT_ASSERT(msg!=NULL);
    LOGPRINT_ASSERT(msgLen!=0U);    
    
    pthread_mutex_lock( &f_mutex_print );

    int charsPrinted = fprintf(f_logger_stdout, "%s\n",msg);

    pthread_mutex_unlock( &f_mutex_print );

    if ( charsPrinted >= msgLen )
    {
        status = LOGGER_STATUS_OK;
    }
    else
    {
        LOGPRINT_LOG_E("Failed to print whole message. Only %d/%d printed",charsPrinted,msgLen);
    }
    
    return status;
}

char* logger_stdout_name ( void )
{
    return "stdout";
}
