/**
 @file
 Diagnostics print library - print-file plugin
 
 @author Ryan Powell
 @date 03-10-11
 @copyright Copyright (c) 2011  Ryan Powell 
 @licence http://www.opensource.org/licenses/BSD-3-Clause
 */


#include <stdio.h>
#include <string.h>
#include <pthread.h>

#include "logger_pluginFile.h"


static pthread_mutex_t f_mutex_print = PTHREAD_MUTEX_INITIALIZER;

static FILE * f_logger_file = NULL;


LOGGER_STATUS logger_file_initialize ( LOGGER_INI_SECTIONHANDLE paramBag )
{
    LOGGER_STATUS status = LOGGER_STATUS_FAILURE_INVALID_MESSAGE;
    
    if ( paramBag == NULL )
    {
        status = LOGGER_STATUS_FAILURE_INVALID_PARAM;
        LOGPRINT_LOG_E("NULL param to : %s",__FUNCTION__);
    }
    else if ( f_logger_file != NULL )
    {
        status = LOGGER_STATUS_FAILURE_ALREADY_INITIALIZED;
        LOGPRINT_LOG_E("already initialized (%s)",__FUNCTION__);        
    }
    else
    {
        char *filePath = NULL;
        size_t filePathLen = 0U;

        logger_ini_sectionRetrieveValueFromKey(paramBag, "output", strlen("output"), &filePath, &filePathLen);

        if ( filePath )
        {
            f_logger_file = fopen(filePath, "w");
            
            if ( f_logger_file != NULL )
            {
                status = LOGGER_STATUS_OK;
                LOGPRINT_LOG_I("Set output to file (%s",parambag->filePath);
            }
            else
            {
                LOGPRINT_LOG_E("Failed to open: %s",parambag->filePath);
            }
        }
        else
        {
            LOGPRINT_LOG_E("Missing param: output from configuration");
            status = LOGGER_STATUS_FAILURE_INVALID_PARAM;
        }
    }

    return status;
}

LOGGER_STATUS logger_file_terminate ( void )
{
    LOGGER_STATUS status = LOGGER_STATUS_FAILURE_INVALID_MESSAGE;
    
    if ( f_logger_file == NULL )
    {
        LOGPRINT_LOG_I("already terminated (%s)",__FUNCTION__);
        status = LOGGER_STATUS_FAILURE_ALREADY_TERMINATED;
    }
    else if ( fclose(f_logger_file) != 0 )
    {
        LOGPRINT_LOG_E("Error closing file");
    }
    else
    {
        f_logger_file = NULL;
        LOGPRINT_LOG_I("Terminated: file");
        status = LOGGER_STATUS_OK;
    }
    
    return status;
}

LOGGER_STATUS logger_file_transmit ( char * msg, size_t msgLen )
{
    LOGGER_STATUS status = LOGGER_STATUS_FAILURE_INVALID_MESSAGE;
    
    LOGPRINT_ASSERT(f_logger_file!=NULL);
    LOGPRINT_ASSERT(msg!=NULL);
    LOGPRINT_ASSERT(msgLen!=0U);    
    
    pthread_mutex_lock( &f_mutex_print );
    
    int charsPrinted = fprintf(f_logger_file, "%s\n",msg);
    
    pthread_mutex_unlock( &f_mutex_print );

    if ( charsPrinted >= msgLen )
    {
        status = LOGGER_STATUS_OK;
    }
    else
    {
        LOGPRINT_LOG_E("Failed to write whole message. Only %d/%d printed",charsPrinted,msgLen);
    }

    return status;
}

char* logger_file_name ( void )
{
    return "file";
}
