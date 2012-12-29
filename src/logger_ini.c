/**
 @file
 Diagnostics print library - common defines
 
 @author Ryan Powell
 @date 03-10-11
 @copyright Copyright (c) 2011  Ryan Powell
 @licence http://www.opensource.org/licenses/BSD-3-Clause
 */


#include <stdio.h>
#include <string.h>

#include "logger.h"
#include "logger_ini.h"
#include "logger_common.h"
#include "logger_stringUtil.h"


typedef struct _IniSection
{
    char *buffer;
    size_t bufferLen;
    char *sectionName;
    size_t sectionNameLen;
    
    char **keyNames;
    char **valueNames;
    
    uint32_t numberOfKeys;
    
} IniSection;


static void **f_sectionsArray;
static uint32_t f_sectionsArrayCount = 0U;


static IniSection * logger_ini_createSection ( char *sectionName, size_t sectionNameLen, char *sectionBuffer, size_t sectionBufferLen )
{
    IniSection *setting = logger_memAlloc(sizeof(IniSection));
    
    if ( setting )
    {
        char * l_name = logger_memAlloc(sizeof(char) * sectionNameLen);
        char * l_buffer = logger_memAlloc(sizeof(char) * sectionBufferLen);
        
        if ( ( l_name ) && ( l_buffer ) )
        {
            strncpy(l_name, sectionName, sectionNameLen);
            strncpy(l_buffer, sectionBuffer, sectionBufferLen);
            
            l_name[sectionNameLen] = '\0';
            l_buffer[sectionBufferLen] = '\0';
            
            setting->sectionName = l_name;
            setting->sectionNameLen = sectionNameLen;
            setting->buffer = l_buffer;
            setting->bufferLen = sectionBufferLen;
            
            setting->numberOfKeys = logger_string_numberOfOccurencesOfChar(sectionBuffer,sectionBufferLen,'=');
            
            uint32_t allocSize = sizeof(char*) * setting->numberOfKeys;
            
            setting->keyNames = logger_memAlloc(allocSize);
            setting->valueNames = logger_memAlloc(allocSize);
            
            for ( uint32_t i=0U; i<setting->numberOfKeys; i++ )
            {
                *(setting->keyNames + i) = (void*)0;
                *(setting->valueNames + i) = (void*)0;
            }

            for ( uint32_t x=0U; x<setting->numberOfKeys; x++ )
            {
                /* get the newline after our key,value pair */
                char *equalsOffset = logger_string_findFirstOccurenceOfChar(sectionBuffer, '=');
                
                for ( uint32_t y=0U; y<x; y++ )
                {
                    equalsOffset = logger_string_findFirstOccurenceOfChar(equalsOffset+1U, '=');
                }
                
                char *newlineOffsetAfter = logger_string_findFirstOccurenceOfChar(equalsOffset+1U, '\n');
                
                char *newlineOffsetBefore = equalsOffset;
                
                while ( ( newlineOffsetBefore > sectionBuffer ) &&
                        ( *newlineOffsetBefore != '\n' ) )
                {
                    newlineOffsetBefore -= 1U;
                }
                

                /* create key */
                char *keyName = newlineOffsetBefore + 1U;
                size_t keyLen = ( equalsOffset - newlineOffsetBefore );
                
                setting->keyNames[x] = logger_memAlloc( sizeof(char) * keyLen );
                
                strncpy(setting->keyNames[x], keyName, keyLen);
                
                setting->keyNames[x][keyLen-1U] = 0;


                /* create value */
                char *valueName = equalsOffset + 1U;
                size_t valueLen = ( newlineOffsetAfter - equalsOffset ) - 1U;

                /* rstrip \n */
                while ( ( valueLen > 0 ) &&
                       ( valueName[valueLen] != '\n' ) )
                {
                    valueLen -= 1U;
                }
                
                /* rstrip ' ' */
                while ( ( valueLen > 0 ) &&
                       ( valueName[valueLen] == ' ' ) )
                {
                    valueLen -= 1U;
                }
                
                /* add one back for NULL terminated string */
                valueLen += 1U;
                
                if ( valueLen > 0 )
                {
                    setting->valueNames[x] = logger_memAlloc( sizeof(char) * valueLen );
                    
                    strncpy(setting->valueNames[x], valueName, valueLen);
                    
                    setting->valueNames[x][valueLen-1U] = 0;
                }
            }
        }
        else
        {
            logger_memFree(l_name);
            logger_memFree(l_buffer);
            
            setting = NULL;
        }
    }
    
    return setting;
}

static void logger_ini_freeSection ( IniSection *section )
{
    if ( section )
    {
        if ( section->sectionName )
        {
            logger_memFree((void*)section->sectionName);
            logger_memFree((void*)section->buffer);
            
            for ( uint32_t i=0U; i<section->numberOfKeys; i++ )
            {
                logger_memFree( *(section->keyNames + i) );
                
                if ( *(section->valueNames + i) )
                {
                    logger_memFree( *(section->valueNames + i) );
                }
            }
        }
    }
    
    logger_memFree(section);
}

static IniSection* logger_ini_sectionAtIndex ( uint32_t idx )
{
    IniSection * s = NULL;
    
    if ( idx < f_sectionsArrayCount )
    {
        s = *(f_sectionsArray + idx);
    }
    
    return s;
}

static bool logger_ini_removeSection ( IniSection *section )
{
    bool didAdd = false;
    
    for ( uint32_t i=0U; i<f_sectionsArrayCount; i++ )
    {
        if ( *(f_sectionsArray + i) == section )
        {
            *(f_sectionsArray + i) = section;
            didAdd = true;
        }
    }
    
    return didAdd;
}

static uint32_t logger_ini_numberOfSectionsInBuffer ( const char * fileBuffer, size_t fileBufferSize )
{
    uint32_t count = 0U;
    
    char* currentOffset = (char*)&fileBuffer[0U];
    
    while ( currentOffset < &fileBuffer[fileBufferSize] )
    {
        char* newLineOffset = logger_string_findFirstOccurenceOfChar(currentOffset, '\n');
        
        if ( *currentOffset == '[' )
        {
            /* find the closing brace */
            for ( size_t i=( currentOffset - &fileBuffer[0U] ); i<fileBufferSize; i++ )
            {
                if ( fileBuffer[i] == ']' )
                {
                    count++;
                    break; /* break from for loop */
                }
            }
        }
        
        currentOffset = newLineOffset + 1U;
    }
    
    return count;
}

/* remove any characters we will not be interpreting when reading the file */
static void logger_ini_formatFileBuffer ( char * fileBuffer, size_t fileBufferSize )
{
    /* fix any newline chars first */
    for ( uint32_t i=0U; i<fileBufferSize; i++ )
    {
        switch (fileBuffer[i])
        {
            case '\t':
            case '\r':
            case '\0':
                fileBuffer[i] = '\n';
                break;
                
            default:
                break;
        }
    }

    uint32_t curIdx = 0U;
    
    while ( curIdx < fileBufferSize )
    {
        char *newlinePosition = logger_string_findFirstOccurenceOfChar(&fileBuffer[curIdx], '\n');
        
        if ( ( fileBuffer[curIdx] == ';' ) ||
             ( fileBuffer[curIdx] == '#' ) )
        {
            size_t wipeCount = newlinePosition - &fileBuffer[curIdx];
            
            /* remove comment lines by compacting */
            for ( size_t i=curIdx; i<fileBufferSize-wipeCount; i++ )
            {
                fileBuffer[i] = fileBuffer[i+wipeCount];
            }
            
            memset(&fileBuffer[fileBufferSize-wipeCount], 0, wipeCount);
        }

        curIdx += 1U;
    }

}

static bool logger_ini_loadFileBuffer ( char * fileBuffer, size_t fileBufferSize )
{
    logger_ini_formatFileBuffer(fileBuffer, fileBufferSize);
    
    f_sectionsArrayCount = logger_ini_numberOfSectionsInBuffer(fileBuffer, fileBufferSize);
    
    uint32_t allocSize = sizeof(IniSection*) * f_sectionsArrayCount;
    
    f_sectionsArray = logger_memAlloc(allocSize);
    
    for ( uint32_t i=0U; i<f_sectionsArrayCount; i++ )
    {
        *(f_sectionsArray + i) = (void*)0;
    }
    
    size_t currentOffset = 0U;
    
    while ( ( currentOffset < fileBufferSize ) && ( fileBuffer[currentOffset] != 0 ) )
    {
        char *sectionTagStart = logger_string_findFirstOccurenceOfChar(&fileBuffer[currentOffset], '[') + 1U;
        char *sectionTagEnd = logger_string_findFirstOccurenceOfChar(sectionTagStart+1U, ']');

        char *bufferTagStart = sectionTagEnd+1U;
        char *bufferTagEnd = logger_string_findFirstOccurenceOfChar(bufferTagStart+1U, '[');

        IniSection *section = logger_ini_createSection(sectionTagStart, sectionTagEnd-sectionTagStart, bufferTagStart, bufferTagEnd-bufferTagStart);
        
        if ( section )
        {
            for ( uint32_t i=0U; i<f_sectionsArrayCount; i++ )
            {
                if ( logger_ini_sectionAtIndex(i) == NULL )
                {
                    *(f_sectionsArray + i) = section;
                    break;
                }
            }
        }
        
        currentOffset = bufferTagEnd - fileBuffer;
    }
    
    return true;
}

static void logger_ini_getSectionKeyByIndex( IniSection *section, uint32_t index, char *key, uint32_t *keyLen )
{
    char *bufferPosition = section->buffer;
    
    uint32_t cur_index = 0U;
    
    while ( ( bufferPosition < section->buffer+section->bufferLen) &&
            ( cur_index < index ) )
    {
        char *newlinePosition = logger_string_findFirstOccurenceOfChar(bufferPosition, '\n');
        char *equalsPosition = logger_string_findFirstOccurenceOfChar(bufferPosition, '=');
        char *comment1Position = logger_string_findFirstOccurenceOfChar(bufferPosition, ';');
        char *comment2Position = logger_string_findFirstOccurenceOfChar(bufferPosition, '#');
        
        if ( ( comment1Position == bufferPosition ) ||
             ( comment2Position == bufferPosition ) )
        {
            bufferPosition = newlinePosition + 1U;
        }
        else if ( equalsPosition < newlinePosition )
        {
            /* valid line */
            bufferPosition = newlinePosition + 1U;
        }
        else
        {
            /* dodgy line ?! */
        }
    }
    
    
}

bool logger_ini_initFromFile ( const char * filePath, size_t filePathLen )
{
    bool didInit = false;
    
    if ( filePath )
    {
        FILE *filePointer = fopen(filePath, "r");
        
        fseek(filePointer , 0 , SEEK_END);
        size_t fileBufferSize = ftell(filePointer);
        rewind(filePointer);
        
        char *fileBuffer = logger_memAlloc(sizeof(char) * fileBufferSize);
        
        fread(fileBuffer, 1, fileBufferSize, filePointer);
        
        if ( fileBuffer )
        {
            didInit = logger_ini_loadFileBuffer((char*)fileBuffer,fileBufferSize);
        }
        
        logger_memFree(fileBuffer);
    }
    
    return didInit;
}

void logger_ini_term ( void )
{
    for ( uint32_t i=0U; i<f_sectionsArrayCount; i++ )
    {
        IniSection *section = logger_ini_sectionAtIndex(i);
        
        logger_ini_removeSection(section);
    }
    
    f_sectionsArray = NULL;
    f_sectionsArrayCount = 0U;
}

bool logger_ini_isFileOpen ( void )
{
    return f_sectionsArray != NULL;
}

uint32_t logger_ini_numberOfSections ( void )
{
    return f_sectionsArrayCount;
}


LOGGER_INI_STATUS logger_ini_sectionHandleByIndex ( LOGGER_INI_SECTIONHANDLE *handle, uint32_t sectionIndex, char **sectionName, size_t *sectionLen )
{
    LOGGER_INI_STATUS status = LOGGER_INI_STATUS_UNDEF;
    
    if ( ( handle != NULL ) && ( sectionIndex < f_sectionsArrayCount ) )
    {
        IniSection *section = logger_ini_sectionAtIndex(sectionIndex);

        *handle = section;
        
        if ( sectionName )
        {
            *sectionName = section->sectionName;
        }
        
        if ( sectionLen )
        {
            *sectionLen = section->sectionNameLen;
        }
    }
    else
    {
        status = LOGGER_INI_STATUS_INVALID_PARAMS;
    }
    
    return status;
}


LOGGER_INI_STATUS logger_ini_sectionHandleByName ( LOGGER_INI_SECTIONHANDLE *handle, const char *sectionName, size_t sectionNameLen )
{
    LOGGER_INI_STATUS status = LOGGER_INI_STATUS_UNDEF;
    
    if ( ( handle != NULL ) && ( sectionName != NULL ) )
    {
        for ( uint32_t i=0U; i<f_sectionsArrayCount; i++ )
        {
            IniSection *section = logger_ini_sectionAtIndex(i);
            
            /* since strcmp can be an expensive operation. Lets compare the string length first */
            if ( section->sectionNameLen == sectionNameLen )
            {
                if ( strncmp((const char *)section->sectionName, sectionName, sectionNameLen) == 0 )
                {
                    *handle = section;
                    
                    status = LOGGER_INI_STATUS_SUCCESS;
                    break;
                }
            }
        }
    }
    else
    {
        status = LOGGER_INI_STATUS_INVALID_PARAMS;
    }
    
    return status;
}

LOGGER_INI_STATUS logger_ini_sectionNumberOfKeyValuePairs ( LOGGER_INI_SECTIONHANDLE handle, uint32_t *kvpairCount )
{
    LOGGER_INI_STATUS status = LOGGER_INI_STATUS_UNDEF;
    
    if ( ( handle != NULL ) &&  ( kvpairCount != NULL ) )
    {
        IniSection *section = (IniSection *)handle;
        
        /* at this point after the buffer formatting. The number of lines indicates the number of k,v pairs. Minus 1 for section name */
        *kvpairCount = logger_string_numberOfOccurencesOfChar(section->buffer,section->bufferLen,'\n') - 1U;
    }
    else
    {
        status = LOGGER_INI_STATUS_INVALID_PARAMS;
    }
    
    return status;
}

LOGGER_INI_STATUS logger_ini_sectionRetrieveKeyValueAtIndex ( LOGGER_INI_SECTIONHANDLE handle, uint32_t sectionIdx, char **keyName, size_t *keyLen, char **valueName, size_t *valueLen )
{
    LOGGER_INI_STATUS status = LOGGER_INI_STATUS_UNDEF;
    
    if ( ( handle != NULL ) && ( keyName != NULL ) && ( keyLen != NULL ) && ( valueName != NULL ) && ( valueLen != NULL) )
    {
        IniSection *section = (IniSection *)handle;
        
        /* at this point after the buffer formatting. The number of lines indicates the number of k,v pairs. Minus 1 for section name */
        uint32_t numberOfKeyValuePairs = logger_string_numberOfOccurencesOfChar(section->buffer,section->bufferLen,'\n') - 1U;

        if ( sectionIdx < numberOfKeyValuePairs )
        {
            char *k = section->keyNames[sectionIdx];
            char *v = section->valueNames[sectionIdx];
            
            size_t kLen = strlen(k);
            size_t vLen = 0U;
            
            if ( v )
            {
                vLen = strlen(v);
            }

            *keyName = k;
            *keyLen = kLen;
            
            *valueName = v;
            *valueLen = vLen;
            
            status = LOGGER_INI_STATUS_SUCCESS;
        }
        else
        {
            status = LOGGER_INI_STATUS_INVALID_PARAMS;
        }
    }
    else
    {
        status = LOGGER_INI_STATUS_INVALID_PARAMS;
    }
    
    return status;
}


LOGGER_INI_STATUS logger_ini_sectionRetrieveValueFromKey ( LOGGER_INI_SECTIONHANDLE handle, char *keyName, size_t keyLen, char **valueName, size_t *valueLen )
{
    LOGGER_INI_STATUS status = LOGGER_INI_STATUS_UNDEF;
    
    if ( ( handle != NULL ) && ( keyName != NULL ) && ( valueName != NULL ) && ( valueLen != NULL) )
    {
        uint32_t count = 0U;
        
        logger_ini_sectionNumberOfKeyValuePairs ( handle, &count );

        for ( uint32_t i=0U; i<count; i++ )
        {
            char* tmpkey = NULL;
            size_t tmpkeyLen = 0U;
            char* tmpvalue = NULL;
            size_t tmpvalueLen = 0U;
            
            logger_ini_sectionRetrieveKeyValueAtIndex(handle, i, &tmpkey, &tmpkeyLen, &tmpvalue, &tmpvalueLen);
            
            if ( tmpkeyLen == keyLen )
            {
                if ( strncmp(tmpkey, keyName, keyLen) == 0 )
                {
                    *valueName = tmpvalue;
                    *valueLen = tmpvalueLen;
                    
                    status = LOGGER_INI_STATUS_SUCCESS;
                    break;
                }
            }
        }
    }
    else
    {
        status = LOGGER_INI_STATUS_INVALID_PARAMS;
    }

    return status;
}

