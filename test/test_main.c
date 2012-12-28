
#include <stdio.h>
#include <string.h>
#include "loggerFacade.h"
#include "test_logger_output.h"


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
        
        test_logger();

        return 0;
    }
}

