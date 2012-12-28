/**
 @file
 Diagnostics print library - ini file settings reader
 
 @author Ryan Powell
 @date 03-10-11
 @copyright Copyright (c) 2011  Ryan Powell
 @licence http://www.opensource.org/licenses/BSD-3-Clause
 */


#ifndef _LOGGER_INI_H
#define _LOGGER_INI_H


#ifdef __cplusplus
extern "C" {
#endif
    

#include <stdint.h>
#include <stdbool.h>


/**
 @enum _LOGGER_INI_STATUS
 @brief Various logger levels that can be enabled. \n
 All values are or'ed (bitwise) such that all, or none can be enabled
 \n\n
 #LOGGER_INI_STATUS_UNDEF Unused status code \n
 #LOGGER_INI_STATUS_SUCCESS Operation successfull\n
 #LOGGER_INI_STATUS_INVALID_PARAMS Operation failed due to parameters given are invalid\n
 #LOGGER_INI_STATUS_KEY_NOT_FOUND Could not find key in section\n
 #LOGGER_INI_STATUS_INTERNAL_ERROR Operation failed due to an unknown internal error\n
 #LOGGER_INI_STATUS_LAST_VALUE Unused status code\n
 */
typedef enum _LOGGER_INI_STATUS
{
    LOGGER_INI_STATUS_UNDEF = 0,
    LOGGER_INI_STATUS_SUCCESS,
    LOGGER_INI_STATUS_INVALID_PARAMS,
    LOGGER_INI_STATUS_KEY_NOT_FOUND,
    LOGGER_INI_STATUS_INTERNAL_ERROR,
    LOGGER_INI_STATUS_LAST_VALUE,
} LOGGER_INI_STATUS;


    
/** handle pointer used to access key-values from section */
typedef void* LOGGER_INI_SECTIONHANDLE;


/**
 @brief Opens ini file ready for reading section key-values
 @param[in] filePath file to open
 @param[in] filePathLen length of above param
 @return #true on success
 */
bool logger_ini_initFromFile ( const char * filePath, uint32_t filePathLen );


/**
 @brief Closes ini file
 */
void logger_ini_term ( void );
    
    
/**
 @brief Use to detect if ini file has been opened
 @return #true if ini file is open
 */
bool logger_ini_isFileOpen ( void );


/**
 @brief Number of sections in ini file
 @detail if file hasn't been  open. This will return zero
 @return section count
 */
uint32_t logger_ini_numberOfSections ( void );


/**
 @brief Get the section handle by the section index
 @param[out] handle section handle to be used to retrieve key-values
 @param[in] sectionIndex index of sectionHandle to get (index starts at zero)
 @param[out] sectionName name of section returned (optional)
 @param[out] sectionLen length of section name returned (optional)
 @return #LOGGER_INI_STATUS_SUCCESS on success
 */
LOGGER_INI_STATUS logger_ini_sectionHandleByIndex ( LOGGER_INI_SECTIONHANDLE *handle, uint32_t sectionIndex, char **sectionName, uint32_t *sectionLen );
    
    
/**
 @brief Get the section handle by the section's name
 @param[out] handle section handle to be used to retrieve key-values
 @param[in] sectionName name of section to retrieve
 @param[in] sectionNameLen length of name of section to retrieve
 @return #LOGGER_INI_STATUS_SUCCESS on success
 */
LOGGER_INI_STATUS logger_ini_sectionHandleByName ( LOGGER_INI_SECTIONHANDLE *handle, const char *sectionName, uint32_t sectionNameLen );
    
    
/**
 @brief Get the number of key-value pairs for this section
 @param[in] handle handle of section to use
 @param[out] kvpairCount returns the value of key-value pairs (only valid if return code success)
 @return #LOGGER_INI_STATUS_SUCCESS on success
 */
LOGGER_INI_STATUS logger_ini_sectionNumberOfKeyValuePairs ( LOGGER_INI_SECTIONHANDLE handle, uint32_t *kvpairCount );
    
    
/**
 @brief Get the key-value pair at index
 @param[in] handle handle of section to use
 @param[in] sectionIdx index to retrieve (value range 0<->#logger_ini_sectionNumberOfKeyValuePairs-1)
 @param[out] keyName returned key name
 @param[out] keyLen returned key name length
 @param[out] valueName returned value name
 @param[out] valueLen returned value name length
 @return #LOGGER_INI_STATUS_SUCCESS on success
 */
LOGGER_INI_STATUS logger_ini_sectionRetrieveKeyValueAtIndex ( LOGGER_INI_SECTIONHANDLE handle, uint32_t sectionIdx, char **keyName, uint32_t *keyLen, char **valueName, uint32_t *valueLen );
    
    
/**
 @brief Get the value name from the key name
 @param[in] handle handle of section to use
 @param[in] keyName key name to look for
 @param[in] keyLen key name length
 @param[out] valueName returned value name
 @param[out] valueLen returned value name length
 @return #LOGGER_INI_STATUS_SUCCESS on success, #LOGGER_INI_STATUS_KEY_NOT_FOUND if keyName not found
 */
LOGGER_INI_STATUS logger_ini_sectionRetrieveValueFromKey ( LOGGER_INI_SECTIONHANDLE handle, char *keyName, uint32_t keyLen, char **valueName, uint32_t *valueLen );


    
#ifdef __cplusplus
}
#endif


#endif /* _LOGGER_INI_H */
