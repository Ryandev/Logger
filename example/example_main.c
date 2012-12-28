
#include <stdio.h>
#include <string.h>
#include "loggerFacade.h"


void test ( void )
{
    LOGGER_OUTPUT_HANDLE _loggerHandle = NULL;
    
    /* get logger permissions for main.c and set _loggerHandle */
    LOGGER_INIT;

    LOGGER_ENTRY;
    
    LOGGER_INFO("This is an info");
    
    LOGGER_WARN("This is a warning");
    
    LOGGER_ERROR("This is an error");
    
    LOGGER_FATAL("This is a fatal");
    
    LOGGER_EXIT;
    
    /* destroy _loggerHandle */
    LOGGER_TERM;
}

int main(int argc, const char * argv[])
{
    if ( argc != 2 )
    {
        fprintf(stderr, "Must be called with ini file to load (%u)\n",argc);
        return 1;
    }
    else
    {
        char *inifile = (char*)argv[1];

        fprintf(stdout, "Loading ini file: %s\n",inifile);
        
        /* load the configuration file which details which files have what logging permissions */
        loggerLoadIniFile(inifile, (uint32_t)strlen(inifile));
        
        test();
        return 0;
    }
}

