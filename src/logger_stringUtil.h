/**
 @file
 Diagnostics print library - string utility calls

 @author Ryan Powell
 @date 28-07-12
 @copyright Copyright (c) 2011  Ryan Powell 
 @licence http://www.opensource.org/licenses/BSD-3-Clause
*/


#ifndef _LOGGER_STRINGUTIL_H
#define _LOGGER_STRINGUTIL_H


#ifdef __cplusplus
extern "C" {
#endif


/**
 @brief Retrieve just the filename from the full filepath (unix shell equivalent 'basename')
 @detail returned parameter #stringFileNameReturned does not contain a new refrence but simply a pointer within the char array provided w/o whitespaces
 @param[out] stringFileNameReturned char array of just the filename
 @param[out] stringFileNameReturnedLen length of above char array (optional)
 @param[in] filePath char array to remove path from
 @param[in] filePathLen length of above char array
 */
void logger_string_fileNameFromPath ( char ** stringFileNameReturned, uint32_t * stringFileNameReturnedLen, const char * filePath, uint32_t filePathLen );


/**
 @brief Return a subreference containing char array #str removed of any leading & trailing whitespace
 @detail returned parameter #stringTrimmed does not contain a new refrence but simply a pointer within the char array provided w/o whitespaces
 @param[out] stringTrimmed returned whitespace free char array
 @param[out] stringTrimmedLen length of above array
 @param[in] str char array to remove whitespaces from
 @param[in] strLen length of above array
 */
void logger_string_trimWhitespace ( char ** stringTrimmed, uint32_t * stringTrimmedLen, char * str, uint32_t strLen );


/**
 @brief Trim any filename extension at the end the provided char array #str
 @detail #stringTrimmedLen will return the last occurence of the character '.' in the #str char array
 @param[out] stringTrimmedLen length of string w/o fileName extension
 @param[in] str char array to search
 @param[in] strLen length of above char array
 */
void logger_string_trimFileNameExtension ( uint32_t * stringTrimmedLen, char * str, uint32_t strLen );



/** Return pointer to first occurence of char in given string.
 @param[in] str string to search
 @param[in] searchChar character to look for
 @return !NULL on success
 */
char* logger_string_findFirstOccurenceOfChar ( const char* str, const char searchChar );

    
/** Return pointer to first occurence of char in given string.
 @param[in] str string to search
 @param[in] strLen string length of above param
 @param[in] searchChar character to look for
 @return occurences of search char in string
 */
uint32_t logger_string_numberOfOccurencesOfChar ( const char* str, uint32_t strLen, const char searchChar );


#ifdef __cplusplus
}
#endif


#endif /* _LOGGER_STRINGUTIL_H */
