/**
 @file
 Diagnostics print library - initTerm behaviour
 
 @author Ryan Powell
 @date 03-10-11
 @copyright Copyright (c) 2011  Ryan Powell 
 @licence http://www.opensource.org/licenses/BSD-3-Clause
 */


#include <pthread.h>
#include <string.h>

#include "logger_initTerm.h"
#include "logger_pluginStdout.h"
#include "logger_pluginFile.h"
#include "logger_pluginUdp.h"


static uint32_t f_registeredCount = 0U;
#define LOGGER_REGISTEREDCOUNT_MAXVALUE (0xFFFFFFFFU)

static pthread_mutex_t f_mutex_initCount = PTHREAD_MUTEX_INITIALIZER;

static LOGGER_STATUS logger_startup ( void );

static LOGGER_STATUS logger_shutdown ( void );

static LOGGER_TEMPLATE_INIT f_pluginInitArray[] =
{
    logger_stdout_initialize,
    logger_file_initialize,
    logger_udp_initialize
};


static LOGGER_TEMPLATE_TERM f_pluginTermArray[] =
{
    logger_stdout_terminate,
    logger_file_terminate,
    logger_udp_terminate
};


static LOGGER_TEMPLATE_SEND f_pluginSendArray[] =
{
    logger_stdout_transmit,
    logger_file_transmit,
    logger_udp_transmit
};


static LOGGER_TEMPLATE_NAME f_pluginNameArray[] =
{
    logger_stdout_name,
    logger_file_name,
    logger_udp_name
};

#define OUTPUT_LOCATION_COUNT 3U

static uint32_t f_pluginIndex = 0U; /* default */


static LOGGER_STATUS logger_startup ( void )
{
    LOGGER_STATUS status = LOGGER_STATUS_UNDEF;

    for ( uint32_t i=0U; i<logger_ini_numberOfSections(); i++ )
    {
        LOGGER_INI_SECTIONHANDLE handle = NULL;
        
        char *sectionname = NULL;
        uint32_t sectionlen = 0;
        
        logger_ini_sectionHandleByIndex(&handle, i, &sectionname, &sectionlen);
        
        if ( strncmp(sectionname, "output=", strlen("output=")) == 0 )
        {
            char *outputName = &sectionname[strlen("output")+1U];

            for ( uint32_t y=0U; y<OUTPUT_LOCATION_COUNT; y++ )
            {
                if ( strncmp((*f_pluginNameArray[y])(), outputName, strlen(outputName)) == 0 )
                {
                    f_pluginIndex = y;
                    break;
                }
            }
            
            LOGPRINT_ASSERT(f_pluginInitArray[f_pluginIndex]!=NULL);
            
            status = (*f_pluginInitArray[f_pluginIndex])(handle);
            
            
            break;
        }
    }

    return status;
}

static LOGGER_STATUS logger_shutdown ( void )
{
    LOGGER_STATUS status = LOGGER_STATUS_UNDEF;
    
    LOGPRINT_ASSERT(f_pluginTermArray[f_pluginIndex]!=NULL);

    status = (*f_pluginTermArray[f_pluginIndex])();
    
    return status;
}

bool logger_init ( void )
{
    bool success = false;
    
    if ( f_registeredCount == LOGGER_REGISTEREDCOUNT_MAXVALUE )
    {
        LOGPRINT_LOG_E("Too many calls to %s, check your code!",__FUNCTION__);
    }
    else
    {
        success = true;
        
        pthread_mutex_lock(&f_mutex_initCount);
        
        if ( f_registeredCount == 0U )
        {
            /* init output for first time */
            if ( logger_startup() != LOGGER_STATUS_OK )
            {
                LOGPRINT_LOG_E("Failed to init startup");
            }
        }

        f_registeredCount += 1U;

        pthread_mutex_unlock(&f_mutex_initCount);

        LOGPRINT_LOG_I("initialized count:%u",f_registeredCount);
    }

    return success;
}

bool logger_term ( void )
{
    bool success = false;
    
    if ( f_registeredCount == 0U )
    {
        LOGPRINT_LOG_E("Too many calls to %s, check your code!",__FUNCTION__);
    }
    else
    {
        pthread_mutex_lock(&f_mutex_initCount);
        f_registeredCount -= 1U;
        pthread_mutex_unlock(&f_mutex_initCount);
        
        LOGPRINT_LOG_I("termination. count:%u",f_registeredCount);
        
        if ( f_registeredCount == 0U )
        {
            /* terminate output for last time - do this one time */
            if ( logger_shutdown() == LOGGER_STATUS_OK )
            {
                success = true;
            }
        }
    }
    
    return success;
}

char* logger_currentOutput ( void )
{
    return (*f_pluginNameArray[f_pluginIndex])();
}

LOGGER_TEMPLATE_SEND logger_getPrintHandler ( void )
{
    return f_pluginSendArray[f_pluginIndex];
}
