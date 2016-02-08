//$Id: CommonSupport.h 1.59 2013/10/27 12:15:16 jacob tnt $
//$Log: CommonSupport.h $
//Revision 1.59  2013/10/27 12:15:16  jacob
//Added support for unittesting
//Revision 1.58  2013/10/21 06:44:26  jacob
//Revised FIXME/TODO macroes for creating lists via the compiler
//Revision 1.57  2013/10/17 10:10:12  jacob
//SizeOf check changes and STM32
//Revision 1.56  2013/05/08 11:44:54  jacob
//PROGMEM2 not defined for new AVR compiler
//Revision 1.55.1.4  2013/10/17 10:07:07  jacob
//Revision 1.55.1.3  2013/10/14 18:20:23  jacob
//SIZEOF_CHECK redefined
//Revision 1.55.1.2  2013/09/12 14:06:10  jacob
//backup
//Revision 1.55.1.1  2013/03/18 11:17:05  jacob
//STM32 branch for dev until more stable
//Revision 1.55  2013/03/17 15:48:26  jacob
//Added some debug templates
//Revision 1.54  2013/03/02 16:04:03  jacob
//Revision 1.53  2013/02/25 12:33:34  jacob
//STM32
//Revision 1.52  2013/02/24 13:36:41  jacob
//Backup
//Revision 1.51  2013/02/22 15:49:28  jacob
//Added PACK for STM32
//Revision 1.50  2013/02/22 10:48:06  jacob
//Backup
//Revision 1.49  2013/02/18 17:52:01  jacob
//Added some STM32 support
//Revision 1.48  2013/01/31 07:47:16  Peter
//Added SIZEOF_CHECK for Atmel toolchain, seems to work...
//Revision 1.47  2012/11/13 13:51:50  jacob
//defines ASSERT if not defined in stdio.h etc.
//Revision 1.46  2012/11/07 08:44:00  jacob
//Added include stdio.h under WIN32
//Revision 1.45  2012/10/09 09:19:33  Peter
//Moved xml class typedef hack above include "target.h"
//Revision 1.44  2012/08/23 10:19:33  jacob
//ATMEL_TOOLCHAIN changes
//
//Revision 1.43  2012/06/11 19:20:40  jacob
//Added profile class to WIN32 section
//Revision 1.42  2011/12/08 12:26:57  jacob
//NIOS2 fix for usleep
//Revision 1.41  2011/12/08 10:40:06  jacob
//Fix to strcmpi
//Revision 1.40  2011/11/02 14:28:42  Peter
//including avr/wdt.h for AVR
//Revision 1.39  2011/10/31 10:51:16  jacob
//XMEGA FIX 
//Revision 1.38  2011/10/27 11:46:26  Peter
//Added sleep.h for AVR
//Revision 1.37  2011/10/25 11:48:33  Peter
//Added boot.h include for avr
//Revision 1.36  2011/07/01 07:58:15  Peter
//EMU changes only
//Revision 1.35  2011/06/28 17:48:22  jacob
//Merge of NIOS2 branch into trunk
//Revision 1.34  2011/06/24 14:18:39  jacob
//Added Filesystem hack
//Revision 1.33  2011/06/24 12:48:53  jacob
//Win32 Update
//Revision 1.32  2011/06/24 09:01:29  jacob
//Avr Update
//Revision 1.31  2011/04/07 08:45:11  jacob
//Added Progmem2 define
//Revision 1.30  2011/03/02 09:23:54  jacob
//Include file order fix
//Revision 1.29  2011/02/11 12:11:01  jacob
//Added Int2Type template
//Revision 1.28  2011/02/09 15:31:48  jacob
//Backup before really restructuring 
//Revision 1.27  2011/01/13 17:16:54  jacob
//NIOS changes
//Revision 1.26  2011/01/06 13:56:09  jacob
//Added SIZEOF_CHECK and PACK defines for NIOS2
//Revision 1.25  2011/01/03 16:14:30  jacob
//Fix of NEWPROTECT under NIOS2
//Revision 1.24  2010/12/22 11:50:52  jacob
//Now uses SystemTimer
//Revision 1.23  2010/10/08 14:49:35  jacob
//Changes related to SystemTimer
//Revision 1.22  2010/08/23 12:17:00  jacob
//STK_STI defined to nothing under WIN32
//Revision 1.21  2010/03/18 14:07:38  jacob
//TimerVal and GetTickCount define fix
//Revision 1.20  2010/02/16 11:36:09  jacob
//More AVR support and cleanup
//Revision 1.19  2009/12/07 11:32:13  jacob
//Now include stdlib under win32
//Revision 1.18  2009/12/03 15:17:58  jacob
//Stopped usign avrlog.h
//Revision 1.17  2009/12/01 15:57:31  jacob
//Killed some log code
//Revision 1.16  2009/11/02 11:11:48  Peter
//EMU changes, simple console log
//Revision 1.15  2009/10/19 09:11:36  jacob
//Avr fix
//Revision 1.14  2009/09/16 11:01:08  jacob
//Fix to SCopeCli when under WIN32 only 
//Revision 1.13  2009/09/11 10:50:43  Peter
//Backup
//Revision 1.12  2009/06/25 08:46:33  jacob
//Stopped including log.h when in TERMINAL compile mode
//Revision 1.11  2009/05/29 11:51:06  jacob
//Revision 1.10  2009/05/19 08:36:47  jacob
//Added some ASSERT fixes
//Revision 1.9  2009/01/16 00:10:11  jacob
//Includes stdafx if MFC defined
//Revision 1.8  2009/01/14 11:37:55  jacob
//Revision 1.7  2009/01/13 10:48:27  jacob
//Added NIOS2 contents
//Revision 1.6  2009/01/02 09:55:41  jacob
//Added safealloc etc ..
//Revision 1.5  2008/10/21 11:38:55  jacob
//Revision 1.4  2008/10/21 06:58:00  jacob
//backup
//Revision 1.3  2008/10/08 14:25:40  jacob
//Removed annoying typo
//Revision 1.2  2008/10/01 08:33:24  jacob
//Backup
//Revision 1.1  2008/09/25 11:13:48  jacob
//Initial revision
 
#ifndef __COMMONSUPPORT_H__
#define __COMMONSUPPORT_H__

#if defined(FIXMETEST)
#define FIXME(args...) FIXMEMARKER __FILE__:__LINE__: (args)
#define TODO(args...) TODOMARKER __FILE__:__LINE__: (args)
#else 
#define FIXME(...) 
#define TODO(...) 
#endif 



#if (ATMEL_TOOLCHAIN != 0)
    #define SIZEOF_CHECK(expr) {typedef char SIZEOF_CHECK_unnamed[(expr) ? 1:-1];}
#else 
    //#define SIZEOF_CHECK(expr) {char unnamed[(expr) ? 1:-1];unnamed[0] = 0;}
    #define SIZEOF_CHECK(expr) {typedef char SIZEOF_CHECK_unnamed[(expr) ? 1:-1];}
#endif 



#define safestrcpy(x,y) {strncpy((x),(y),sizeof((x)));(x)[sizeof((x))-1] = 0;}

template <int v>
struct Int2Type {
    enum {value = v};
};



// TARGET SPECIFICS 

#if defined(AVR) 

    #define NEWPROTECT(x) x

    #define PACK __attribute__ ((packed))
    #define PACKALIGN __attribute__ ((packed,aligned(4)))

    #define kernel_timer() t_SystemTimer::TimerVal()

    #if !defined(ATMEL_TOOLCHAIN)
     FIXME(Check if this is needed at all); 
     #define PROGMEM2 __attribute__((section(".progmem.data"))) 
    #endif 

    // first off, include all the REAL hardware stuff
    #include <avr/io.h>
    #include <avr/interrupt.h>
    #include <avr/pgmspace.h>
    #if !defined(XMEGA)
    #include <avr/boot.h>
    #include <avr/wdt.h>
    #endif 
    #include <avr/sleep.h>

    #define TRACE 

     typedef unsigned int uint;
     typedef unsigned char uchar;
     typedef unsigned long ulong;

    #include "avrutils.h"
    #include "target.h"

#elif defined(NIOS2)

    // Use this class with a local static vars
    // Like:
    // static volatile int InserviceCount = 0;
    // InserviceLock ServiceLock(&InserviceCount);
    
    class InserviceLock {
    public:
        InserviceLock(volatile int *lock) {pLock = lock;(*pLock)++;}
        ~InserviceLock() {(*pLock)--;}
    
        bool MultipleLock(void) {return (*pLock) > 1;}
        bool SingleLock(void) {return (*pLock) == 1;}
    protected: 
        volatile int *pLock;
    };
    
    
    
    #include <stdarg.h>		// manages variable-length argument passing
    #include <stddef.h>
    #include <string.h>
    #include <unistd.h>
    
    #define NVRAM __attribute__ ((section (".nv_sram")))
    
    // Structure packing                 
    #define PACK __attribute__ ((packed))
    #define PACKALIGN __attribute__ ((packed,aligned(4)))
    
    #if !defined(EMU)
    #define MAX_PATH 64
    #define _MAX_PATH MAX_PATH
    #endif 
    
    #define ASSERT(...) 
    
    #include "target.h"

#elif defined(WIN32)
   
    #define NEWPROTECT(x)       x
    #define VSPRINTF_PROTECT(x) x

    #include <stdarg.h>		// manages variable-length argument passing
    #include <string.h>		// strcpy strlen etc
    #include <stddef.h>		// strcpy strlen etc
    #include "stdlib.h"
    #include "stdio.h"

    #if !defined(ASSERT)
        #define ASSERT _ASSERT
    #endif 


    #if !defined(EMU)
    //Hack to make xml class compile 
    class t_FS
    {
    public: 
        typedef FILE FILEHANDLE;
    };
    #endif 
	

    #if !defined(UNITTEST)
    #include "target.h"
    #else 

    #include <windows.h>
    #include <stdio.h>

    #include "log.h"

    
    // Defines a logconfig for unit testing
    template <int A>
    class LogConfig : public logconfig_defaults{
    public:

        class noprotect {
        public:
            noprotect()  {}
            ~noprotect() {}
        };
        typedef noprotect ProtectClass;

        // Set the lenght of the filename displayed 
        static const unsigned char FileNameLen = 16;

        // Determined if we need a time stamp 
        // This requires that we add a function in MyLogStream called 
        // char * BuildTime(char *buf) 
        // That return the required timestamp 
        static const bool CustomTimeStamp = false;

        // These must be implemented to use a standard tick count 
        static const unsigned long TimeStampLenght = 6;

        static unsigned long GetTicks(void)
        {
            return GetTickCount();
        };

        typedef WIN32_STD_1<WIN32_CONSOLE_PRINTF> OutClass;



    };

    #endif 

    #define safefree      free
    #define safemalloc    malloc
    #define saferealloc   realloc

    #define safe_sprintf  sprintf
    #define safe_vsprintf vsprintf

    #if !defined(strcmpi)
    #define strcmpi _strcmpi
    #endif

    

    #define NVRAM
    #define kernel_timer GetTickCount

    #if !defined(EMU)
        #define SCOPE_CLI CScopeCli dummyCScopeCli;
    
        #define STK_CLI
        #define STK_STI
    
        class CScopeCli {
        public:
            CScopeCli() { }
            ~CScopeCli() { }
        };
    #endif

    // For Gcc compability 
    #define PACK 
    #define PACKALIGN 



    /* HACK SECTION */


    #if defined(EMU)
    class InserviceLock {
    public:
        InserviceLock(volatile int *lock) {pLock = lock;(*pLock)++;}
        ~InserviceLock() {(*pLock)--;}

        bool MultipleLock(void) {return (*pLock) > 1;}
        bool SingleLock(void) {return (*pLock) == 1;}
    protected: 
        volatile int *pLock;
    };
    #endif 

    class profile
    {

    public:

        profile(const char *Name) {
            strcpy(m_Name,Name);
            m_StartTime = GetTickCount();
        };

        ~profile() {

            DWORD Elapsed = GetTickCount() - m_StartTime;
            log_dev("*** %s took %u mS\n",m_Name,Elapsed);
        };


    private:
        DWORD m_StartTime;
        char m_Name[32];
    };

    #define PROFILE(x) profile dummy_##x(#x);


#elif defined(_STM32x_)

    #define PACK __attribute__ ((packed))
    #define PACKALIGN __attribute__ ((packed,aligned(4)))
    
    #include "target.h"

#elif defined(UNITTEST)

    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include "log.h"

#else 
    #error "No way"
#endif 

#endif 
