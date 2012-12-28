/**
 @file
 Logger print library wrapper
 
 @author Ryan Powell
 @date 28-07-12
 @copyright Copyright (c) 2011  Ryan Powell
 @licence http://www.opensource.org/licenses/BSD-3-Clause
 */

 
#ifndef _LOGGERFACADE_H
#define _LOGGERFACADE_H


#ifdef __cplusplus
extern "C" {
#endif


/** comment line to disable logging */
#define LOGGER_ENABLED
    


#ifdef LOGGER_ENABLED


#include <string.h>
#include "logger.h"


#define LOGGER_INIT   loggerInitFromFileName(&_loggerHandle, __FILE__, strlen(__FILE__))
#define LOGGER_TERM      loggerTerm(_loggerHandle)
#define LOGGER_ENABLE_TYPE(a)  loggerAppendDebugLevel(_loggerHandle, (a))
#define LOGGER_DISABLE_TYPE(a) loggerRemoveDebugLevel(_loggerHandle, (a))

#define LOGGER_ENTRY LOGGER_PRINT_ENTRY(_loggerHandle, NULL)
#define LOGGER_EXIT LOGGER_PRINT_EXIT(_loggerHandle, NULL)
#define LOGGER_INFO(format, ... ) LOGGER_PRINT_INFO(_loggerHandle, format, ##__VA_ARGS__ )
#define LOGGER_WARN(format, ... ) LOGGER_PRINT_WARN(_loggerHandle, format, ##__VA_ARGS__ )
#define LOGGER_ERROR(format, ... ) LOGGER_PRINT_ERROR(_loggerHandle, format, ##__VA_ARGS__ )
#define LOGGER_FATAL(format, ... ) LOGGER_PRINT_FATAL(_loggerHandle, format, ##__VA_ARGS__ )
#define LOGGER_ASSERT(format, ... ) LOGGER_PRINT_ASSERT(_loggerHandle, format, ##__VA_ARGS__ )
#define LOGGER_EVENT(format, ... ) LOGGER_PRINT_EVENT(_loggerHandle, format, ##__VA_ARGS__ )



/* ASSERTIONS */
#define ASSERT_NULL(a) \
do { \
    if ((a)!=NULL) \
    { \
        LOGGER_ASSERT("ASSERT_NULL "); \
    } \
} while (0)

#define ASSERT_NULL_MSG(a,format, ...) \
do { \
    if ((a)!=NULL) \
    { \
        LOGGER_ASSERT("ASSERT_NULL " format, ##__VA_ARGS__); \
    } \
} while (0)

#define ASSERT_NOT_NULL(a) \
do { \
    if ((a)==NULL) \
    { \
        LOGGER_ASSERT("ASSERT_NOT_NULL "); \
    } \
} while (0)


#define ASSERT_NOT_NULL_MSG(a,format, ...) \
do { \
    if ((a)==NULL) \
    { \
        LOGGER_ASSERT("ASSERT_NOT_NULL " format, ##__VA_ARGS__ ); \
    } \
} while (0)

#define ASSERT_true(a) \
do { \
    if ((a)!=true) \
    { \
        LOGGER_ASSERT("ASSERT_true "); \
    } \
} while (0)		

#define ASSERT_true_MSG(a,format, ...) \
do { \
    if ((a)!=true) \
    { \
    LOGGER_ASSERT("ASSERT_true " format, ##__VA_ARGS__); \
    } \
} while (0)

#define ASSERT_false(a) \
do { \
    if ((a)!=false) \
    { \
        LOGGER_ASSERT("ASSERT_false "); \
    } \
} while (0)		

#define ASSERT_false_MSG(a,format, ...) \
do { \
    if ((a)!=false) \
    { \
        LOGGER_ASSERT("ASSERT_false " format, ##__VA_ARGS__); \
    } \
} while (0)

#define ASSERT_ZERO(a) \
do { \
    if ((a)!=0) \
    { \
        LOGGER_ASSERT("ASSERT_ZERO "); \
    } \
} while (0)		

#define ASSERT_ZERO_MSG(a,format, ...) \
do { \
    if ((a)!=0) \
    { \
        LOGGER_ASSERT("ASSERT_NOT_ZERO " format, ##__VA_ARGS__); \
    } \
} while (0)

#define ASSERT_NOT_ZERO(a) \
do { \
    if ((a)==0) \
    { \
        LOGGER_ASSERT("ASSERT_NOT_ZERO "); \
    } \
} while (0)		

#define ASSERT_NOT_ZERO_MSG(a,format, ...) \
do { \
    if ((a)==0) \
    { \
        LOGGER_ASSERT("ASSERT_NOT_ZERO " format, ##__VA_ARGS__); \
    } \
} while (0)

#define ASSERT_NOT_ZERO_F(a) \
do { \
    if ((a)==0.0f) \
    { \
        LOGGER_ASSERT("ASSERT_NOT_ZERO "); \
    } \
} while (0)		

#define ASSERT_NOT_ZERO_F_MSG(a,format, ...) \
do { \
    if ((a)==0.0f) \
    { \
        LOGGER_ASSERT("ASSERT_NOT_ZERO " format, ##__VA_ARGS__); \
    } \
} while (0)

#define ASSERT_EQUALS(a,b) \
do { \
    if ((a)!=(b)) \
    { \
        LOGGER_ASSERT("ASSERT_EQUALS %d!=%d",a,b); \
    } \
} while (0)		

#define ASSERT_EQUALS_MSG(a,b,format, ...) \
do { \
    if ((a)!=(b)) \
    { \
        LOGGER_ASSERT("ASSERT_EQUALS %d!=%d",a,b); \
        LOGGER_ASSERT(format, ##__VA_ARGS__); \
    } \
} while (0)

#define ASSERT_EQUALS_F(a,b) \
do { \
    if ((a)!=(b)) \
    { \
        LOGGER_ASSERT("ASSERT_EQUALS %f!=%f",a,b); \
    } \
} while (0)		

#define ASSERT_EQUALS_F_MSG(a,b,format, ...) \
do { \
    if ((a)!=(b)) \
    { \
        LOGGER_ASSERT("ASSERT_EQUALS %f!=%f",a,b); \
        LOGGER_ASSERT(format, ##__VA_ARGS__); \
    } \
} while (0)

#define ASSERT_NOT_EQUALS(a,b) \
do { \
    if ((a)==(b)) \
    { \
        LOGGER_ASSERT("ASSERT_NOT_EQUALS %d==%d",a,b); \
    } \
} while (0)		

#define ASSERT_NOT_EQUALS_MSG(a,b,format, ...) \
do { \
    if ((a)==(b)) \
    { \
        LOGGER_ASSERT("ASSERT_NOT_EQUALS %d==%d",a,b); \
        LOGGER_ASSERT(format, ##__VA_ARGS__); \
    } \
} while (0)

#define ASSERT_NOT_EQUALS(a,b) \
do { \
    if ((a)==(b)) \
    { \
        LOGGER_ASSERT("ASSERT_NOT_EQUALS %d==%d",a,b); \
    } \
} while (0)		

#define ASSERT_NOT_EQUALS_MSG(a,b,format, ...) \
do { \
if ((a)==(b)) \
    { \
        LOGGER_ASSERT("ASSERT_NOT_EQUALS %d==%d",a,b); \
        LOGGER_ASSERT(format, ##__VA_ARGS__); \
    } \
} while (0)

#define ASSERT_GREATER_THAN(a,b) \
do { \
    if ((a)<=(b)) \
    { \
        LOGGER_ASSERT("ASSERT_GREATER_THAN %d<=%d",a,b); \
    } \
} while (0)		

#define ASSERT_GREATER_THAN_MSG(a,b,format, ...) \
do { \
    if ((a)<=(b)) \
    { \
        LOGGER_ASSERT("ASSERT_GREATER_THAN %d<=%d",a,b); \
        LOGGER_ASSERT(format, ##__VA_ARGS__); \
    } \
} while (0)

#define ASSERT_GREATER_THAN_F(a,b) \
do { \
    if ((a)<=(b)) \
    { \
        LOGGER_ASSERT("ASSERT_GREATER_THAN %f<=%f",a,b); \
    } \
} while (0)		

#define ASSERT_GREATER_THAN_F_MSG(a,b,format, ...) \
do { \
if ((a)<=(b)) \
    { \
        LOGGER_ASSERT("ASSERT_GREATER_THAN %f<=%f",a,b); \
        LOGGER_ASSERT(format, ##__VA_ARGS__); \
    } \
} while (0)

#define ASSERT_LESS_THAN(a,b) \
do { \
    if ((a)>=(b)) \
    { \
        LOGGER_ASSERT("ASSERT_LESS_THAN %d>=%d",a,b); \
    } \
} while (0)		

#define ASSERT_LESS_THAN_MSG(a,b,format, ...) \
do { \
    if ((a)>=(b)) \
    { \
        LOGGER_ASSERT("ASSERT_LESS_THAN %d>=%d",a,b); \
        LOGGER_ASSERT(format, ##__VA_ARGS__); \
    } \
} while (0)

#define ASSERT_LESS_THAN_F(a,b) \
do { \
    if ((a)>=(b)) \
    { \
        LOGGER_ASSERT("ASSERT_LESS_THAN %f>=%f",a,b); \
    } \
} while (0)		

#define ASSERT_LESS_THAN_F_MSG(a,b,format, ...) \
do { \
    if ((a)>=(b)) \
    { \
        LOGGER_ASSERT("ASSERT_LESS_THAN %f>=%f",a,b); \
        LOGGER_ASSERT(format, ##__VA_ARGS__); \
    } \
} while (0)


#else /* NO LOGGER */


#define LOGGER_INIT {}
#define LOGGER_TERM {}
#define LOGGER_ENABLE_TYPE(a)  {}
#define LOGGER_DISABLE_TYPE(a) {}

#define LOGGER_ENTRY {}
#define LOGGER_EXIT {}
#define LOGGER_INFO(format, ... )  {}
#define LOGGER_WARN(format, ... )  {}
#define LOGGER_ERROR(format, ... )  {}
#define LOGGER_FATAL(format, ... )  {}
#define LOGGER_ASSERT(format, ... )  {}
#define LOGGER_EVENT(format, ... )  {}


/* ASSERTIONS */
#define ASSERT_NULL(a) {(a);} /* keep original expression-incase side-effects were intended */
#define ASSERT_NULL_MSG(a,format, ...) {}
#define ASSERT_NOT_NULL(a)  {(a);}
#define ASSERT_NOT_NULL_MSG(a,format, ...)  {}
#define ASSERT_true(a)  {(a);}
#define ASSERT_true_MSG(a,format, ...)  {(a);}
#define ASSERT_false(a)  {(a);}
#define ASSERT_false_MSG(a,format, ...)  {(a);}
#define ASSERT_ZERO(a)  {(a);}
#define ASSERT_ZERO_MSG(a,format, ...)  {(a);}
#define ASSERT_NOT_ZERO(a)  {(a);}
#define ASSERT_NOT_ZERO_MSG(a,format, ...)  {}
#define ASSERT_NOT_ZERO_F(a)  {(a);}
#define ASSERT_NOT_ZERO_F_MSG(a,format, ...)  {}
#define ASSERT_EQUALS(a,b)  {(a);(b);}
#define ASSERT_EQUALS_MSG(a,b,format, ...)  {}
#define ASSERT_EQUALS_F(a,b)  {(a);(b);}
#define ASSERT_EQUALS_F_MSG(a,b,format, ...)  {}
#define ASSERT_NOT_EQUALS(a,b)  {(a);(b);}
#define ASSERT_NOT_EQUALS_MSG(a,b,format, ...)  {(a);(b);}
#define ASSERT_NOT_EQUALS(a,b)  {(a);(b);}
#define ASSERT_NOT_EQUALS_MSG(a,b,format, ...)  {(a);(b);}
#define ASSERT_GREATER_THAN(a,b)  {(a);(b);}
#define ASSERT_GREATER_THAN_MSG(a,b,format, ...)  {(a);(b);}
#define ASSERT_GREATER_THAN_F(a,b)  {(a);(b);}
#define ASSERT_GREATER_THAN_F_MSG(a,b,format, ...)  {(a);(b);}
#define ASSERT_LESS_THAN(a,b)  {(a);(b);}
#define ASSERT_LESS_THAN_MSG(a,b,format, ...)  {(a);(b);}
#define ASSERT_LESS_THAN_F(a,b)  {(a);(b);}
#define ASSERT_LESS_THAN_F_MSG(a,b,format, ...)  {(a);(b);}


#endif /* LOGGER_ENABLED */


#ifdef __cplusplus
}
#endif


#endif /* _LOGGER_H */
