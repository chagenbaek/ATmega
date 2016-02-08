// $Id: log.h 3.45 2013/11/05 12:35:50 jacob tnt jacob $
// $Log: log.h $
// Revision 3.45  2013/11/05 12:35:50  jacob
// Fix of format uner unittest
// Revision 3.44  2013/10/27 12:33:57  jacob
// UNITTEST fix so that output can be parsed by slickedit
// Revision 3.43  2013/10/27 12:12:25  jacob
// Fix of "abe % giraf problem"
// Revision 3.42  2013/10/14 18:22:03  jacob
// backup
// Revision 3.41  2013/09/20 13:17:42  jacob
// log_simple support for STM32
// Revision 3.40  2013/02/18 17:55:55  jacob
// AVR_STD_UART now visible for all targets 
// STM32 changes 
// Revision 3.39  2013/02/18 12:18:10  Peter
// Not compiling version, explains a bug in the log!
// Revision 3.38  2013/01/10 11:16:11  Peter
// Not including rtc.h
// Revision 3.37  2012/12/12 08:51:56  Peter
// WIN32_FILE bug fix
// Revision 3.36  2012/10/09 09:10:34  Peter
// Added new output class: WIN32_FILE_BUFFERED for setting the filename runtime
// Revision 3.35  2012/08/30 12:58:41  jacob
// New system for setting up timestamps
// Revision 3.34  2012/08/22 17:11:56  jacob
// MaxLogFileSize fix
// Revision 3.33  2012/07/01 15:04:08  jacob
// Added define to query devlogstate
// Revision 3.32  2012/06/12 13:38:57  jacob
// Added comment
// Revision 3.31  2012/02/24 09:58:29  jacob
// WIN32 fix
// Revision 3.30  2012/01/16 12:39:26  jacob
// Added datatime support for WIN32 
// Added logfilesize limit WIN32
// Revision 3.29  2011/12/13 12:07:34  jacob
// Added a few more defaults to the config part
// Revision 3.28  2011/12/13 08:54:52  jacob
// Added some defaults and a few comments
// Revision 3.27  2011/11/30 13:17:31  jacob
// Added some forward declarations for WIN32 templates
// Revision 3.26  2011/11/29 11:09:31  jacob
// Warning fix 
// Revision 3.25  2011/11/23 12:18:57  Peter
// Removed unused code
// Revision 3.24  2011/10/24 15:36:33  jacob
// WIN32 fix
// Revision 3.23  2011/10/22 14:27:15  Peter
// Placed XMEGA code under XMEGA define
// Revision 3.22  2011/08/19 12:38:13  Peter
// Fixed __FILEX__ to support both / and '\' 
// Revision 3.21  2011/07/01 10:00:26  jacob
// Added support for globally disabling logtypes 
// Tentative fix of space problem with long filenames
// Revision 3.20  2011/06/30 09:58:30  jacob
// Minor Gcc fix
// Revision 3.19  2011/06/29 14:34:43  jacob
// Support for optional linenumber and len of it 
// Support for using printf under windows
// Revision 3.18  2011/06/29 11:37:40  jacob
// Added a NoLogAtAll class
// Revision 3.17  2011/06/28 16:19:49  jacob
// Fix of slashing forward slashes from the filename
// Revision 3.16  2011/06/28 15:18:08  jacob
// Outdefined WIN32 specific code
// Revision 3.15  2011/06/28 15:11:03  jacob
// Added Support for saving history per Thread
// Revision 3.14  2011/06/28 14:53:58  jacob
// Backup
// Revision 3.13  2011/06/28 12:34:31  jacob
// Backup DNU
// Revision 3.12  2011/06/28 12:28:19  jacob
// Added WIN32 mutex lock 
// Added ThreadID support
// Revision 3.11  2011/06/27 15:17:08  jacob
// More fixes
// Revision 3.10  2011/06/27 15:13:46  jacob
// Removed debug code
// Revision 3.9  2011/06/27 15:11:43  jacob
// Build TimeStamp now a void function
// Revision 3.8  2011/06/27 15:06:35  jacob
// XMEGA changes 
// Revision 3.7  2011/06/27 14:44:45  jacob
// DNU test
// Revision 3.6  2011/06/27 14:15:36  jacob
// DNU
// Revision 3.5  2011/06/27 12:35:52  jacob
// Support for Log2File under WIN32
// Revision 3.4  2011/06/27 10:24:31  jacob
// Generic TimeStamp support - TEST
// Revision 3.3  2011/06/24 14:40:04  jacob
// WIN32 define fix for avr
// Revision 3.2  2011/06/24 12:07:06  jacob
// Added GetLastError support for WIN32
// Revision 3.1  2011/06/24 11:24:45  jacob
// Still under dev
// Revision 3.0  2011/06/24 09:02:52  jacob
// New tentative version TEST
// Revision 2.29.2.17.1.1  2011/06/23 13:58:16  jacob
// New log test
// Revision 2.29.2.17  2011/04/26 16:21:53  jacob
// Updated the BuildTime stamp template 
// Revision 2.29.2.16  2011/04/14 13:13:42  Peter
// CritError also under EMU
// Revision 2.29.2.15  2011/04/12 19:09:41  jacob
// Added NIOS2 support (again)
// Revision 2.29.2.14  2011/04/07 08:38:56  jacob
// Reworked version that avoids the progmem warn and cuts the code size somewhat too
// Revision 2.29.2.13.1.3  2011/04/01 15:05:09  jacob
// Fix to avoid having the line numbers and the static string embedded
// Revision 2.29.2.13.1.2  2011/04/01 11:37:38  jacob
// Ne approach this avoids progmem warns
// Revision 2.29.2.13.1.1  2011/04/01 11:25:06  jacob
// Revision 2.29.2.13  2011/03/23 12:07:33  Peter
// Removed a comment
// Revision 2.29.2.12  2011/03/03 13:37:29  jacob
// New CritError
// Revision 2.29.2.11  2011/03/02 09:23:55  jacob
// Include file order fix
// Revision 2.29.2.10  2011/03/01 23:58:58  jacob
// No CritHandler when in bootloader
// Revision 2.29.2.9  2011/03/01 23:51:17  jacob
// Tentative CritHandler
// Revision 2.29.2.8  2011/02/28 13:27:16  jacob
// Removed legacy support 
// Revision 2.29.2.7  2011/02/27 20:17:37  jacob
// Backup
// Revision 2.29.2.6  2011/02/25 11:45:48  jacob
// Backup
// Revision 2.29.2.4  2011/02/22 23:41:35  jacob
// Added protection 
// Revision 2.29.2.3  2011/02/22 22:53:54  jacob
// Added a lot of legacy prototypes 
// Revision 2.29.2.2  2011/02/11 12:11:38  jacob
// Backup - tentative version supporting custom logging
// Revision 2.29.2.1  2011/02/10 12:50:05  jacob
// Tentative version supporting configuration via target.h
// Revision 2.29  2011/01/29 18:23:57  Johan
// included 'avr/pgmspace.h' since PSTR() is used
// Revision 2.28  2011/01/21 11:14:32  jacob
// Minor typecast fix in bindump
// Revision 2.27  2011/01/13 18:26:14  jacob
// Attempt to NIOS2 support
// Revision 2.26  2010/10/06 18:45:26  jacob
// Fix in bindump
// Revision 2.25  2010/09/05 15:41:32  Johan
// Now takes 16 bytes for the filename
// Revision 2.24  2010/02/19 11:26:21  jacob
// Tentative fix for PSTR log problem in AVR
// Revision 2.23  2010/02/16 11:33:35  jacob
// Added trace and bindump for AVR
// Revision 2.22  2010/02/15 18:11:18  jacob
// Added bindump
// Revision 2.21  2010/02/12 13:23:25  jacob
// Stopped using PSTR when BOOTLOADER is defined
// Revision 2.20  2010/01/26 15:42:12  jacob
// Added NODEVLOG
// Revision 2.19  2010/01/13 10:17:24  Peter
// Now uses printf to write to stdout
// WriteConsole only writes to console not stdout
// Revision 2.18  2010/01/12 15:06:58  jacob
// Removed warn
// Revision 2.17  2010/01/12 10:22:00  Peter
// log_raw puts * before string
// Revision 2.16  2010/01/11 11:19:49  jacob
// Now slashes are handled in another way in win32
// Revision 2.15  2010/01/09 09:51:15  Administrator
// Cleanup and beautification
// Revision 2.14  2010/01/07 14:55:58  Peter
// Fixed crit to warn bug
// Revision 2.13  2010/01/04 10:53:49  jacob
// Fixed WIN32 warn
// Revision 2.12  2010/01/02 19:58:24  Administrator
// Include windows.h for WIN32
// Revision 2.11  2009/12/30 11:53:26  jacob
// Rename due to WIN32 clash
// Revision 2.10  2009/12/29 15:01:49  jacob
// Now raw uses logstream directly
// Revision 2.9  2009/12/29 13:54:05  jacob
// Reenabled Raw function for Genie
// Revision 2.8  2009/12/29 13:06:41  jacob
// Tentative log stub declaration
// Revision 2.7  2009/12/29 12:11:00  jacob
// Now requires an external DumpLog 
// Clean up etc
// Revision 2.6  2009/12/29 08:56:40  jacob
// Added missing defines
// Revision 2.5  2009/12/29 08:31:26  jacob
// Reworked to provide granularity
// Revision 2.2.1.3  2009/12/28 14:20:37  jacob
// Attempt to provide granularity
// Revision 2.2.1.2  2009/12/09 08:06:17  Peter
// FIxed I D W C copy-paste-error
// Revision 2.2.1.1  2009/12/07 12:36:48  jacob
// Logs directly to Genie. Cheat version
// Revision 2.2  2009/12/03 15:19:19  jacob
// Added raw function
// Revision 2.1  2009/12/01 15:54:08  jacob
// Now used in a win32 commandline project
// Revision 2.0  2009/12/01 10:23:11  jacob
// Tentative new version 

#ifndef _LOG__H
#define _LOG__H

#include <stdio.h>		// manages variable-length argument passing                                                                   
#include <stdarg.h>		// manages variable-length argument passing
#include <string.h>		// strcpy strlen etc
#include <stddef.h>		// strcpy strlen etc

#if defined(WIN32)
 #include <map>
 #include <string>
 #include <vector>

 // Forward declarations needed as we include CommonSupport.h 
 // CommonSupport.h includes target.h that includes log.h (this file) 
 template <template <int> class S1> struct WIN32_STD_1;
 template <
    template <int> class S1, 
    template <int> class S2> 
 struct WIN32_STD_2;

 template <int A> class WIN32_MUTEX;
 template <int A> class WIN32_CONSOLE_PRINTF;
 template <int A> class WIN32_CONSOLE;
 template <int A> class WIN32_FILE;

#endif 

#include "CommonSupport.h"      // Can be omitted. But we loose FIXME etc. 

typedef enum {
        TimeStamp_none,
        TimeStamp_custom,
        TimeStamp_std
    } t_TimeStampType;

typedef enum {
        DateTime_none,
        DateTime_custom,
        DateTime_YYYYMMDD_HHMMSS_TTT,
        DateTime_YYMMDD_HHMMSS_TTT_COMPACT,
        DateTime_HHMMSS_TTT
    } t_DateTime;

/********/
class logconfig_defaults
{
public:
    static const bool DisplayThreadID = false;

    static const unsigned int GlobalEnable_Simple   = 1;
    static const unsigned int GlobalEnable_Trace    = 1;
    static const unsigned int GlobalEnable_Dev      = 1;
    static const unsigned int GlobalEnable_Info     = 1;
    static const unsigned int GlobalEnable_Warn     = 1;
    static const unsigned int GlobalEnable_Crit     = 1;
    

    static const unsigned int KeepHistory = 0;
    static const bool         KeepHistoryThreadID = false;  // Do not fill the history with the Thread ID 

    // Default to having linenumbers with 5 chars 
    static const unsigned char LineNumLen  = 5; 

    static const unsigned long MaxLogFileSize    = (10*1024*1024L);

    // Conf the timestamp
    static const t_TimeStampType    TimeStampType   = TimeStamp_std; 
    static const unsigned int       TimeStampLenght = 0;        // 


    static const t_DateTime         DateTimeType    = DateTime_HHMMSS_TTT;

    // Limit filenames to 16 chars 
    static const unsigned char  FileNameLen = 16;

    // GetTicks()
    
    static unsigned long GetTicks();

    

    // Do not protect the log in any way 
    class noprotect 
    {
    public:
        noprotect()  {}
        ~noprotect() {}
    };

    typedef noprotect ProtectClass;


};

class NoLogAtAll {};

// Forward decl 
template <int> class LogConfig;

template <int,int,int,int,int,int,int > class DoLog;

//** For usage without a specific policy 
typedef DoLog<0,0,1,1,1,1,1> LogPolicy;
typedef DoLog<0,0,0,0,1,1,1> CritWarnOnly;
typedef DoLog<0,0,0,0,0,1,1> CritOnly;
typedef DoLog<0,0,0,1,1,1,1> NoDevLog;
typedef DoLog<0,0,1,1,1,1,1> FullLog;
typedef DoLog<0,0,0,0,0,0,1> NoLog;

#define NOLOG           typedef NoLog           LogPolicy;
#define FULLLOG         typedef FullLog         LogPolicy;
#define CRITWARNONLY    typedef CritWarnOnly    LogPolicy;
#define CRITONLY        typedef CritOnly        LogPolicy;
#define NODEVLOG        typedef NoDevLog        LogPolicy;

#define DevLogEnabled (LogPolicy::DevEnabled)

typedef enum {
    LOGTYPE_TRACE   = 'T',
    LOGTYPE_INFO    = 'I',
    LOGTYPE_WARN    = 'W',
    LOGTYPE_CRIT    = 'C',
    LOGTYPE_DEV     = 'D'
} t_logtype;


#if defined (WIN32)
    #define __attribute__(x)
    #define X_vsprintf vsprintf

    // Just allocate enough 
    #define BUFFERSIZE      32*256
    #define FNTBUFFERSIZE    16*80

#elif defined(AVR) || defined(XMEGA)
    #define BUFFERSIZE      256
    #define FNTBUFFERSIZE    80

    // included avr program space headers (since we use PSTR())
    #include <avr/pgmspace.h>
    #include "avrutils.h"

    #if !defined(BOOTLOADER)
        #define X_vsprintf vsprintf_P
        #define STRMODIFIER(x) PSTR(x)
    #else 
        #define X_vsprintf vsprintf
        #define STRMODIFIER(x) (x)
    #endif 
#elif defined(NIOS2)
    #define X_vsprintf vsprintf
    #define STRMODIFIER(x) (x)

    // Just allocate enough 
    #define BUFFERSIZE      32*256
    #define FNTBUFFERSIZE    16*80

#elif defined(_STM32x_)

    #include "safe_sprintf.h"

    #define BUFFERSIZE      256
    #define FNTBUFFERSIZE    80

    #define X_vsprintf safe_vsprintf
    #define STRMODIFIER(x) (x)

#else 
    #error "Need a target"
#endif 

#if defined(WIN32)

    #include "windows.h"
    #include <stdio.h>
    #include <stdlib.h>


    // Thank you for the backwards slashes Bill 
    #define __FILEX__ strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

    #define log_dev(x,...)		LogPolicy::dev(__FILEX__,__LINE__,x,__VA_ARGS__)  
    #define log_info(x,...)		LogPolicy::info(__FILEX__,__LINE__,x,__VA_ARGS__)  
    #define log_warn(x,...)		LogPolicy::warn(__FILEX__,__LINE__,x,__VA_ARGS__)  
    #define log_crit(x,...)		LogPolicy::crit(__FILEX__,__LINE__,x,__VA_ARGS__)  

    #define log_dev_details(x,...)		{DWORD Err = GetLastError();LogPolicy::dev (__FILEX__,__LINE__,x,__VA_ARGS__);LogPolicy::Win32Err(LOGTYPE_DEV,Err); }
    #define log_inf0_details(x,...)		{DWORD Err = GetLastError();LogPolicy::info(__FILEX__,__LINE__,x,__VA_ARGS__);LogPolicy::Win32Err(LOGTYPE_INFO,Err);}
    #define log_warn_details(x,...)		{DWORD Err = GetLastError();LogPolicy::warn(__FILEX__,__LINE__,x,__VA_ARGS__);LogPolicy::Win32Err(LOGTYPE_WARN,Err);} 
    #define log_crit_details(x,...)		{DWORD Err = GetLastError();LogPolicy::crit(__FILEX__,__LINE__,x,__VA_ARGS__);LogPolicy::Win32Err(LOGTYPE_CRIT,Err);} 

    #define log_bindump(data,size) LogPolicy::bindump(__FILEX__,__LINE__,data,size)

    #define log_trace(x,...)	
#elif defined(AVR)

    // PSTR duplicate strings are not merged in code 
    // PSTR strings are NOT removed from code by compiler

    #define __FILEX__ strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__ 

    #define PROGMEM2 __attribute__((section(".progmem.data"))) 


    #define log_dev(x,args...)  \
    {\
            if (LogPolicy::DevEnabled) { \
                static const char Hans[] PROGMEM2 = x;\
                LogPolicy::dev (__FILEX__,__LINE__, Hans,## args);\
            }\
    };

    #define log_simple(x)  \
    {\
            if (LogPolicy::SimpleEnabled) { \
                LogPolicy::simple (x);\
            }\
    };

    #define log_info(x,args...) \
    {\
            if (LogPolicy::InfoEnabled) { \
                static const char Hans[] PROGMEM2 = x;\
                LogPolicy::info(__FILEX__,__LINE__,Hans,## args);\
            }\
    };

    #define log_warn(x,args...) \
    {\
            if (LogPolicy::WarnEnabled) { \
                static const char Hans[] PROGMEM2 = x;\
                LogPolicy::warn(__FILEX__,__LINE__,Hans,## args);\
            }\
    };

    #define log_crit(x,args...) \
    {\
            if (LogPolicy::CritEnabled) { \
                static const char Hans[] PROGMEM2 = x;\
                LogPolicy::crit(__FILEX__,__LINE__,Hans,## args);\
            }\
    };

    #define log_raw(x)          LogPolicy::raw(x);  
    #define log_bindump(data,size) LogPolicy::bindump(__FILEX__,__LINE__,(char *)data,size)
    #define log_trace(x,...)	

#elif defined(NIOS2) || defined(_STM32x_)

    #define __FILEX__ strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__ 

    #define log_dev(x,args...)  LogPolicy::dev (__FILEX__,__LINE__,LogPolicy::DevEnabled  ?  STRMODIFIER(x) : NULL,## args)  
    #define log_info(x,args...) LogPolicy::info(__FILEX__,__LINE__,LogPolicy::InfoEnabled ?  STRMODIFIER(x) : NULL,## args)  
    #define log_warn(x,args...) LogPolicy::warn(__FILEX__,__LINE__,LogPolicy::WarnEnabled ?  STRMODIFIER(x) : NULL,## args)  
    #define log_crit(x,args...) LogPolicy::crit(__FILEX__,__LINE__,LogPolicy::CritEnabled ?  STRMODIFIER(x) : NULL,## args)  
    #define log_simple(x)       {if (LogPolicy::SimpleEnabled) LogPolicy::simple(x);}

    #define log_raw(x)          LogPolicy::raw(x);  
    #define log_bindump(data,size) LogPolicy::bindump(__FILEX__,__LINE__,(char *)data,size)
    #define log_trace(x,...)	
    
#endif 


// For selecting one of two types by a boolean 
template <bool, typename T,typename S> struct Bool2Type;

template <typename T,typename S> struct Bool2Type<true,T,S> 
{
    typedef T Result;
};

template <typename T,typename S> struct Bool2Type<false,T,S> 
{
    typedef S Result;
};

namespace LogHelper {

    template <int N> struct Power2Ten 
    {
        static const unsigned long long Value = 10*Power2Ten<N-1>::Value;
    };

    template <> struct Power2Ten<0> 
    {
        static const unsigned long long Value = 1;
    };

    /******** TimeStamp ***********/

    // Decl 
    template <t_TimeStampType TimeStampType, class T, class ST> struct TimeStampBuilder;

    // Spec for standard 
    template <class T, class ST> struct TimeStampBuilder<TimeStamp_std,T,ST>
    {
        static void BuildTimeStamp(void) {

            if (T::TimeStampLenght == 0) { 
                return;
            } // endif

            char str[T::TimeStampLenght+5];

            unsigned long Time = T::GetTicks();

            typename Bool2Type<(T::TimeStampLenght > 8) ? true:false, unsigned long long, unsigned long>::Result Div = Power2Ten<T::TimeStampLenght>::Value;

            str[0] = '(';

            Time = Time % Div;
            Div /= 10;

            int i = 1; 
            while (Div) {

                unsigned char d; 
                d = (char )(Time / Div);

                str[i++] = '0' + d;

                Time = Time % Div;
                Div /= 10;
                
            } // endwhile

            str[i++] = ')';
            str[i++] = ' ';
            str[i++] = 0;

            ST::Out(str); 
             
            return;
        };
    };

    // Spec for custom timestamp 
    template <class T, class ST> struct TimeStampBuilder<TimeStamp_custom,T,ST>
    {

        static void BuildTimeStamp(void) {

            // Call the one implemented in LogConfig 
            T::BuildTimeStamp();
        };
    };

    // Spec for no timestamp 
    template <class T, class ST> struct TimeStampBuilder<TimeStamp_none,T,ST>
    {

        static void BuildTimeStamp(void) {};
    };

    /************ Date and time ***********************/
    // Decl 
    template <t_DateTime DateTimeType, class T, class ST> struct DateTimeBuilder;

    // Spec for none
    template <class T, class ST> struct DateTimeBuilder<DateTime_none,T,ST>
    {

        static void BuildDateTime(void) {};
    };

    // Spec for DataTime_HHMMSS_TTT
    template <class T, class ST> struct DateTimeBuilder<DateTime_HHMMSS_TTT,T,ST>
    {
        static void BuildDateTime(void) {

            #if defined(WIN32) 
                char line[128];
                SYSTEMTIME Time;
                GetLocalTime(&Time);
                sprintf(line,"%02u.%02u:%02u:%03u ",
                    Time.wHour,
                    Time.wMinute,
                    Time.wSecond,
                    Time.wMilliseconds);
                ST::Out(line); 
            #endif

        };
    };

    // Spec for DateTime_YYYYMMDD_HHMMSS_TTT
    template <class T, class ST> struct DateTimeBuilder<DateTime_YYYYMMDD_HHMMSS_TTT,T,ST>
    {
        static void BuildDateTime(void) {

            #if defined(WIN32) 
                char line[128];
                SYSTEMTIME Time;
                GetLocalTime(&Time);
                sprintf(line,"%02u/%02u/%02u %02u.%02u:%02u:%03u ",
                    Time.wYear,
                    Time.wMonth,
                    Time.wDay,
                    Time.wHour,
                    Time.wMinute,
                    Time.wSecond,
                    Time.wMilliseconds);
                ST::Out(line); 
            #endif

        };
    };

    // Spec for DateTime_YYMMDD_HHMMSS_TTT_COMPACT
    template <class T, class ST> struct DateTimeBuilder<DateTime_YYMMDD_HHMMSS_TTT_COMPACT,T,ST>
    {
        static void BuildDateTime(void) {

            #if defined(WIN32) 
                char line[128];
                SYSTEMTIME Time;
                GetLocalTime(&Time);
                sprintf(line,"%02u%02u%02u %02u.%02u.%02u:%03u ",
                    Time.wYear % 100,
                    Time.wMonth,
                    Time.wDay,
                    Time.wHour,
                    Time.wMinute,
                    Time.wSecond,
                    Time.wMilliseconds);
                ST::Out(line); 
            #endif

        };
    };


    // Spec for custom 
    template <class T, class ST> struct DateTimeBuilder<DateTime_custom,T,ST>
    {

        static void BuildDateTime(void) {
            // Call the one implemented in LogConfig 
            T::BuildDateTime();
        };
    };
    




    /******** Thread ID ***********/
    // Decl 
    template <bool Enable, class ST> struct ThreadIDBuilder;

    // Spec for standard 
    template <class ST> struct ThreadIDBuilder<false,ST>
    {
        static void inline ThreadID(void) {};
    };

    // Spec for WIN32
    template <class ST> struct ThreadIDBuilder<true,ST>
    {
        static void inline ThreadID(void) 
        {
            #if defined(WIN32)
            DWORD ID = GetCurrentThreadId();
            char buf[80];
            sprintf(buf,"%08lX ",ID);
            ST::Out(buf); 
            #endif 
        };
    };

    /******** Line Numbers ***********/
    // Decl 
    template <int N, class ST> struct LineNumBuilder;

    // Spec for none 
    template <class ST> struct LineNumBuilder<0,ST>
    {
        static void Build(unsigned int LineNum) {};
    };

    // Standard 
    template <int N, class ST> struct LineNumBuilder
    {
        static void Build(unsigned int LineNum) {

            typename Bool2Type<(N > 8) ? true:false, unsigned int, unsigned long>::Result Div = Power2Ten<N>::Value;

            LineNum = LineNum % Div;
            Div /= 10;

            char str[N+5];

            int i = 0; 
            while (Div) {

                unsigned char d; 
                d = (char )(LineNum / Div);

                str[i++] = '0' + d;

                LineNum = LineNum % Div;
                Div /= 10;

            } // endwhile

            str[i++] = ' ';
            str[i++] = 0;

            ST::Out(str); 

            return;
        };
    };



};

#if defined(WIN32)
template <typename T, unsigned int N > class KeepHistoryWrapper
{
public:

    static void Out(char *str)
    {
        Line += str;
        T::Out(str);
    };

    static const bool Init(void)
    {
        return T::Init();
    };

    static const bool Close(void)
    {
        return T::Close();
    };

    static void EndOfLine(void)
    {
        DWORD ID = GetCurrentThreadId();
        t_Storage::iterator it = m_Storage.find(ID);

        if (it == m_Storage.end()) { 
            // Thread ID not found in map
            std::vector<std::string> Vect;
            Vect.push_back(Line);
            m_Storage[ID] = Vect;
        } else {
            it->second.push_back(Line);

            while ( it->second.size() > N ) {
                it->second.erase(it->second.begin());
            } // endwhile

        } // endif

        // It has been stored now 
        Line = "";
    };

    
    static bool GetLogByThreadID(DWORD ID, std::vector<std::string> &list)
    {
        t_Storage::iterator it = m_Storage.find(ID);

        if (it == m_Storage.end()) { 
            return false;
        } // endif
        list = it->second;
        return true;
    }
    

private:

    static std::string Line;

    // Create a map of vectors containing strings 
    typedef std::map<DWORD, std::vector<std::string> > t_Storage;
    static t_Storage m_Storage;

};

template <typename T ,unsigned int N> std::string KeepHistoryWrapper<T,N>::Line = std::string("");
template <typename T ,unsigned int N> typename KeepHistoryWrapper<T,N>::t_Storage KeepHistoryWrapper<T,N>::m_Storage;
#else 

// Empty def 
template <typename T, unsigned int N > class KeepHistoryWrapper : public T
{
public: 
    static inline void EndOfLine(void) {};
};


#endif 

// Empty def 
template <typename T > class NoHistoryWrapper : public T
{
public: 

    static inline void EndOfLine(void) {};
};



TODO( Consider if we can make the strlen(filename) a compile time call );
    

template <class T, typename ST>
class TLogStream : public T, 
                   public Bool2Type<T::KeepHistory == 0, NoHistoryWrapper<ST>, KeepHistoryWrapper<ST,T::KeepHistory> >::Result 
{
public:

    // Basically this is NOT needed as we inherit from it BUT it makes reading somewhat easier 
    typedef typename Bool2Type<T::KeepHistory == 0, NoHistoryWrapper<ST>, KeepHistoryWrapper<ST,T::KeepHistory> >::Result OutStream;

    static void inline Common(const char *Filename, unsigned int Line, t_logtype Type)
    {

        // This is all the standard info 
        SetTextColor(Type);

        // ThreadID optionally include the Thread ID in the history although redundant 
        LogHelper::ThreadIDBuilder<T::DisplayThreadID,
                                   typename Bool2Type<T::KeepHistoryThreadID,OutStream,ST>::Result
                                  >::ThreadID();

        size_t len = strlen(Filename);

        char str[T::FileNameLen+2];

        if (len < T::FileNameLen) { 
            OutStream::Out((char *)Filename);

            unsigned char Index = 0;
            while (len++ < T::FileNameLen) {
                str[Index++] = ' ';
            } // endwhile
            str[Index] = 0;
            OutStream::Out(str);
        } else {

            // Retain last 3 chars 
            strncpy(str,Filename,T::FileNameLen -6);
            str[T::FileNameLen - 6] = '.';
            str[T::FileNameLen - 5] = '.';

            str[T::FileNameLen - 4] = *(Filename + len-3);
            str[T::FileNameLen - 3] = *(Filename + len-2);
            str[T::FileNameLen - 2] = *(Filename + len-1);
            str[T::FileNameLen - 1] = ' ';
            str[T::FileNameLen] = 0;

            OutStream::Out(str);
        } // endif

        #if defined(UNITTEST)
            // Output in a format that slickedit can act upon
            char tmp[16];
            sprintf(tmp,":%05u:",Line);
            OutStream::Out(tmp);
        #else 
            // Line num 
            LogHelper::LineNumBuilder<T::LineNumLen,OutStream>::Build(Line);
        #endif 

        

        
        // And log type 
        str[0] = (char )Type;
        str[1] = ' ';
        str[2] = 0;
        OutStream::Out(str);

        // Now the optional parts 


        LogHelper::DateTimeBuilder<T::DateTimeType,
                                    T,
                                    OutStream>::BuildDateTime();

        TODO(consider an if here - might slash codesize);
        // Optional CustomTimeStamp 
        LogHelper::TimeStampBuilder<T::TimeStampType,
                                    T,
                                    OutStream>::BuildTimeStamp();

    };

    

    FIXME(1a Reboot); 
    static void inline CritHandler(const char *Filename, unsigned int Line, char *str)
    {
        

        #if !defined(BOOTLOADER) && (defined(NIOS2) || defined(EMU))
            extern void CritError(const char *,unsigned int, char *);
            CritError(Filename,Line,str);
        #else
            OutStream::Out((char *)"UPS\n");
        #endif 
        
    }

    #if defined(WIN32)
    static void inline SetTextColor(t_logtype Type)
    {
        switch (Type) {
        
        default:
        case LOGTYPE_INFO   :
        case LOGTYPE_TRACE  : 
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            return;

        case LOGTYPE_WARN: 
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_GREEN);
            return;

        case LOGTYPE_DEV: 
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            return;

        case LOGTYPE_CRIT: 
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_INTENSITY);
            return;
        } // endswitch
    }
    #else 
    static void inline SetTextColor(t_logtype /*Type*/) {} __attribute__((always_inline));
    #endif 

    
};

// ************* Info *****************
template <int DUM, int INFO> struct Info;

// Specialization 
template <int DUM> struct Info<DUM,0> {
public:
    static void info(const char *Filename, unsigned int Line, const char *fmt, ... ) {};
};

template <int DUM> struct Info<DUM,1> : public TLogStream<LogConfig<DUM>,typename LogConfig<DUM>::OutClass> {
public:
    static void info(const char *Filename, unsigned int Line, const char *fmt, ... )
    {
        typedef TLogStream<LogConfig<DUM>,typename LogConfig<DUM>::OutClass> B;

        va_list args;
        char str[FNTBUFFERSIZE];
        
        typename LogConfig<DUM>::ProtectClass P;
        
        B::Common(Filename,Line,LOGTYPE_INFO);

        va_start (args, fmt);
        X_vsprintf(str,fmt,args);
        va_end(args);

        B::Out(str);
        B::EndOfLine();
    } 
};

// ************* Dev *****************
template <int DUM, int DEV> struct Dev;

// Specialization 
template <int DUM> struct Dev<DUM,0> {
public:
    static void dev(const char *Filename, unsigned int Line, const char *fmt, ... ) {};
};

template <int DUM> struct Dev<DUM,1> : public TLogStream<LogConfig<DUM>,typename LogConfig<DUM>::OutClass> {
public:
    static void dev(const char *Filename, unsigned int Line, const char *fmt, ... )
    {
        typedef TLogStream<LogConfig<DUM>,typename LogConfig<DUM>::OutClass> B;

        va_list args;
        char str[FNTBUFFERSIZE];

        typename LogConfig<DUM>::ProtectClass P;
        
        B::Common(Filename,Line,LOGTYPE_DEV);

        va_start (args, fmt);
        X_vsprintf(str,fmt,args);
        va_end(args);
        B::Out(str);
        B::EndOfLine();
    } 
};

// ************* Warn *****************
template <int DUM, int WARN> struct Warn;

// Specialization 
template <int DUM> struct Warn<DUM,0> {
public:
    static void warn(const char *Filename, unsigned int Line, const char *fmt, ... ) {};
};

template <int DUM> struct Warn<DUM,1> : public TLogStream<LogConfig<DUM>,typename LogConfig<DUM>::OutClass> {
public:
    static void warn(const char *Filename, unsigned int Line, const char *fmt, ... )
    {
        typedef TLogStream<LogConfig<DUM>,typename LogConfig<DUM>::OutClass> B;

        va_list args;
        char str[FNTBUFFERSIZE];

        typename LogConfig<DUM>::ProtectClass P;
        
        B::Common(Filename,Line,LOGTYPE_WARN);

        va_start (args, fmt);
        X_vsprintf(str,fmt,args);
        va_end(args);
        B::Out(str);
        B::EndOfLine();
    } 
};

// ************* Crit *****************
template <int DUM, int CRIT> struct Crit;

// Specialization 
template <int DUM> struct Crit<DUM,0> {
public:
    static void crit(const char *Filename, unsigned int Line, const char *fmt, ... ) {};
};

template <int DUM> struct Crit<DUM,1> : public TLogStream<LogConfig<DUM>,typename LogConfig<DUM>::OutClass> {
public:
    static void crit(const char *Filename, unsigned int Line, const char *fmt, ... )
    {
        typedef TLogStream<LogConfig<DUM>,typename LogConfig<DUM>::OutClass> B;

        va_list args;
        char str[FNTBUFFERSIZE];

        typename LogConfig<DUM>::ProtectClass P;
        
        B::Common(Filename,Line,LOGTYPE_CRIT);

        va_start (args, fmt);
        X_vsprintf(str,fmt,args);
        va_end(args);
        B::Out(str);
        B::EndOfLine();

        B::CritHandler(Filename,Line,str);

    } 
};

// ************* Simple *****************
template <int DUM, int SIMPLE> struct Simple;

// Specialization 
template <int DUM> struct Simple<DUM,0> {
public:
    static void simple(char *) {};
    static void simple(const char *) {};
    static void simple(unsigned long) {};
};

template <int DUM> struct Simple<DUM,1> : public TLogStream<LogConfig<DUM>,typename LogConfig<DUM>::OutClass> {
public:
    static void simple(char *str)
    {
        typename LogConfig<DUM>::ProtectClass P;
        typedef TLogStream<LogConfig<DUM>,typename LogConfig<DUM>::OutClass> B;
        B::Out(str);
        B::EndOfLine();
    } 

    static void simple(const char *str)
    {
        simple((char *)str);
    }


    
    static void simple(unsigned long Val)
    {
        typename LogConfig<DUM>::ProtectClass P;
        typedef TLogStream<LogConfig<DUM>,typename LogConfig<DUM>::OutClass> B;

        
        char buf[10];
        for (unsigned char i=0;i<8;i++) { 

            unsigned char data;
            char c;
    
            data = (Val & 0xF0000000) >> 28;
    
            if (data >= 10 ) {
                c = 'A' + (data-10);
            } else {
                c = '0' + data;
            } // endif
            buf[i] = c;
            //B::Out(c);

            Val <<= 4;

        } // endfor
        buf[8] = '\n';
        buf[9] = 0;

        B::Out(buf);
        B::EndOfLine(); 
    } 
    
};


template <int DUMMY>
class LogBase
{

public:

    typedef TLogStream<LogConfig<DUMMY>,typename LogConfig<DUMMY>::OutClass> B;

    static void bindump(const char *Filename, unsigned int Line, char *ptr, unsigned int size)
    {
        // Protect this code 
        typename LogConfig<DUMMY>::ProtectClass P;
        
        char buf[5];

        buf[2] = ' ';
        buf[4] = 0;        
        

        for ( unsigned int i=0;i< size;i++ ) {

            unsigned char data = *ptr++;

            if ( (data / 16) >= 10 ) {
                buf[0] = 'A' + ((data/16)-10);
            } else {
                buf[0] = '0' + (data/16);
            } // endif
            
    
            if ( (data % 16) >= 10 ) {
                buf[1] = 'A' + ((data % 16)-10);
            } else {
                buf[1] = '0' + (data  % 16);
            } // endif
    
            if ( (i+1) % 16 == 0 ) {
                buf[3] = '\n';
            } else {
                buf[3] = 0;
            } // endif

            B::Out(buf);

        } // endfor
        B::Out((char *)"\n");
    }
    
    static void raw(char *str)
    {
        // Protect this code 
        typename LogConfig<DUMMY>::ProtectClass P;

        B::Out((char *)"*");
        B::Out(str);
    }

    #if defined(WIN32)
    static void Win32Err(t_logtype ErrType, DWORD Err)
    {
        LPVOID lpMsgBuf;
        LPVOID lpDisplayBuf;

        FormatMessage(
                     FORMAT_MESSAGE_ALLOCATE_BUFFER | 
                     FORMAT_MESSAGE_FROM_SYSTEM,
                     NULL,
                     Err,
                     MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                     (LPTSTR) &lpMsgBuf,
                     0, NULL );

        lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, 
                                          (lstrlen((LPCTSTR)lpMsgBuf)+40)*sizeof(TCHAR)); 

        /*
        StringCchPrintf((LPTSTR)lpDisplayBuf, 
                        LocalSize(lpDisplayBuf),
                        TEXT("%s failed with error %d: %s"), 
                        lpszTitle, dw, lpMsgBuf); 
        */
        sprintf((LPTSTR)lpDisplayBuf, TEXT("\tGetLastError: %d: %s"), Err, lpMsgBuf); 


        B::SetTextColor(ErrType);
        B::Out((char *)lpDisplayBuf);

        //MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK); 

        LocalFree(lpMsgBuf);
        LocalFree(lpDisplayBuf);
    }
    #endif


};

/*
This assembles all the (static) functions into a single wrapper 
You cannot declare functions/vars inside this class as they get duplicated for each flavor of the 
code 
*/ 
template <int DUMMY, int TRAC, int DEV, int INFO, int WARN, int CRIT, int SIMPLE>
class DoLog :   public Info  <0,INFO    *LogConfig<DUMMY>::GlobalEnable_Info>, 
                public Dev   <0,DEV     *LogConfig<DUMMY>::GlobalEnable_Dev>, 
                public Warn  <0,WARN    *LogConfig<DUMMY>::GlobalEnable_Warn>, 
                public Crit  <0,CRIT    *LogConfig<DUMMY>::GlobalEnable_Crit>, 
                public Simple<0,SIMPLE  *LogConfig<DUMMY>::GlobalEnable_Simple>, 
                public LogBase<DUMMY> {
public: 
    // Used for preventing AVR to load const strings into flash 
    static const bool DevEnabled    =   (DEV*   LogConfig<DUMMY>::GlobalEnable_Dev   ) ? true : false;
    static const bool InfoEnabled   =   (INFO*  LogConfig<DUMMY>::GlobalEnable_Info  ) ? true : false;
    static const bool WarnEnabled   =   (WARN*  LogConfig<DUMMY>::GlobalEnable_Warn  ) ? true : false;
    static const bool CritEnabled   =   (CRIT*  LogConfig<DUMMY>::GlobalEnable_Crit  ) ? true : false; 
    static const bool SimpleEnabled =   (SIMPLE*LogConfig<DUMMY>::GlobalEnable_Simple) ? true : false; 
};


#if defined(WIN32)
template <int A>
class WIN32_CONSOLE {

public:

    static void Out(char *str)
    {
        WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), str, strlen(str), NULL, NULL);
    };

    static const bool Init(void)
    {
        return true;
    };

    static const bool Close(void)
    {
        return true;
    };
};

template <int A>
class WIN32_CONSOLE_PRINTF {

public:

    static void Out(char *str)
    {
        printf("%s",str);
    };

    static const bool Init(void)
    {
        return true;
    };

    static const bool Close(void)
    {
        return true;
    };
};


template <int A>
class WIN32_FILE {

public:

    static HANDLE hFile;

    static void Out(char *str)
    {
        if (hFile == INVALID_HANDLE_VALUE) { 
            return; 
        } // endif

        DWORD Written;

        if (!WriteFile(hFile,str,strlen(str),&Written,NULL)) {
            return;
        } // endif
    };

    static const bool Init(void)
    {

        // Check the filesize 
        if (FileExist(LogConfig<A>::LogFileName)) { 
            if (!LimitFileSize(LogConfig<A>::LogFileName, LogConfig<A>::MaxLogFileSize, LogConfig<A>::MaxLogFileSize*3/4)) {
                log_warn("Error handling log file\n");
            } // endif
        } // endif

        hFile = CreateFile(LogConfig<A>::LogFileName,GENERIC_WRITE,FILE_SHARE_READ | FILE_SHARE_WRITE,NULL,OPEN_ALWAYS,0,NULL);

        if (hFile == INVALID_HANDLE_VALUE) { 
            return false;
        } // endif

        // Go to end of file
        SetFilePointer(hFile,0,0,FILE_END);

        return true;
    };

    static const bool Close(void)
    {
        if (hFile != INVALID_HANDLE_VALUE) { 
            CloseHandle(hFile);
            hFile = INVALID_HANDLE_VALUE;
        } // endif
        return true;
    };
};

template <int A> HANDLE WIN32_FILE<A>::hFile = INVALID_HANDLE_VALUE;


template <int A>
class WIN32_FILE_BUFFERED {

public:

    static HANDLE hFile;
    static std::string QueueStr;
    static const unsigned long MaxBufferSize = (10*1024);

    static void Out(char *str)
    {
        if (hFile == INVALID_HANDLE_VALUE) { 

            if (QueueStr.size() >= MaxBufferSize) { 
                QueueStr.erase(0,strlen(str));
            } // endif
            QueueStr += str;
            return; 
        } // endif

        DWORD Written;

        if (!WriteFile(hFile,str,strlen(str),&Written,NULL)) {
            return;
        } // endif
    };

    static const bool Init(void)
    {
        QueueStr.clear();
        return true;
    }


    static const bool SetFileName(const char* FileName)
    {
		
        // Check the filesize 
        if (FileExist(FileName)) { 
            if (!LimitFileSize(FileName, LogConfig<A>::MaxLogFileSize, LogConfig<A>::MaxLogFileSize*3/4)) {
                log_warn("Error handling log file\n");
            } // endif
        } // endif
                        
        hFile = CreateFile(FileName,GENERIC_WRITE,FILE_SHARE_READ | FILE_SHARE_WRITE,NULL,OPEN_ALWAYS,0,NULL);

        if (hFile == INVALID_HANDLE_VALUE) { 
            return false;
        } // endif

        // Go to end of file
        SetFilePointer(hFile,0,0,FILE_END);

        // Flush buffer to file

        DWORD Written;
        if (!WriteFile(hFile,QueueStr.c_str(),QueueStr.size(),&Written,NULL)) {
            return false;
        } // endif

        QueueStr.clear();

        return true;
    };

    static const bool Close(void)
    {
        if (hFile != INVALID_HANDLE_VALUE) { 
            CloseHandle(hFile);
            hFile = INVALID_HANDLE_VALUE;
        } // endif
        return true;
    };
};

template <int A> HANDLE WIN32_FILE_BUFFERED<A>::hFile = INVALID_HANDLE_VALUE;
template <int A> std::string WIN32_FILE_BUFFERED<A>::QueueStr;


template <template <int> class S1> 
struct WIN32_STD_1
{
    static void Out(char *str)
    {
        S1<0>::Out(str);
    };

    static bool Init(void)
    {
        return S1<0>::Init();
    };

    static bool Close(void)
    {
        return S1<0>::Close();
    };

};

template <
    template <int> class S1, 
    template <int> class S2> 

struct WIN32_STD_2
{
    static void Out(char *str)
    {
        S1<0>::Out(str);
        S2<0>::Out(str);
    };

    static bool Init(void)
    {
        return S1<0>::Init() && S2<0>::Init();
    };

    static bool Close(void)
    {
        return S2<0>::Close() && S1<0>::Close();
    };

};


template <int A, int PORT>
class UP_StdUART_LogStream {

public:

    static void Out(char *str)
    {
        printf("%s",str);
        //WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), str, strlen(str), NULL, NULL);
    };
};
#endif 

#if defined(AVR)

#if defined(XMEGA)

template <typename UART, typename SYSTEMTIMER, typename NIOSCOM>
class Terminal_XMEGA_LogStream {

public:

    static void Out(char *str)
    {
        // Recursive check
        static bool Service = false;
        if (Service) { 
            return;
        } // endif
        Service = true;
        while (*str) {
            
            if (is_sei()) { // If interrupt enabled wait if TX queue is full
                while (UART::TxQueue.isFull()) {
                } // endwhile
            } // endif
            
            NIOSCOM::Putc(*str);
            UART::Putc(*str);
            str++;
        } // endwhile 

        SYSTEMTIMER::UpdateStackCheck();
        Service = false;
    };

    static bool Init(void) {return true;};
    static bool Close(void){return true;};
};

#endif 
#endif 


template <typename UART, int DUM>
class AVR_STD_UART {

public:

    static void Out(char *str)
    {
        while (*str) {
            UART::Putc(*str);
            str++;
        } // endwhile 
    };

    static bool Init(void) {return true;};
    static bool Close(void){return true;};
};



template <int A> bool Log_Init(void)
{

    typedef typename LogConfig<A>::OutClass B;
    return B::Init();
}


template <int A> bool Log_Close(void)
{
    typedef typename LogConfig<A>::OutClass B;
    return B::Close();
}

#if defined(WIN32)
template <int A>
class WIN32_MUTEX 
{
public:
    WIN32_MUTEX()  {
        int i = 0;
        while (1) {

            DWORD ret = WaitForSingleObject(LogBlockMutex,1);
    
            if (ret  == WAIT_OBJECT_0 ) {
                break;
            } // endif

        } // endwhile
    };

    ~WIN32_MUTEX() 
    {
        ReleaseMutex(LogBlockMutex);
    };


private:
    static HANDLE LogBlockMutex;
};
template <int A> HANDLE WIN32_MUTEX<A>::LogBlockMutex = CreateMutex(NULL,FALSE,NULL);
#endif 


template <int A>
static const bool ThreadIDEnabled(void)
{
    return LogConfig<A>::DisplayThreadID;
}

#if defined(WIN32)
template <int A>
static bool GetLogByThreadID(DWORD ID, std::vector<std::string> &list)
{
    typedef TLogStream<LogConfig<A>,typename LogConfig<A>::OutClass> B;

    return B::GetLogByThreadID(ID,list);
}

static void RegisterThreadName(std::string Name)
{
    FIXME(2 Obviously does not work);

}
#endif 





#endif 
