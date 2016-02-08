//$Id: SystemTimer.h 1.38.3.2 2014/11/28 12:37:02 jacob tnt $
//$Log: SystemTimer.h $
//Revision 1.38.3.2  2014/11/28 12:37:02  jacob
//TimerVal protected
//Revision 1.38.3.1  2014/11/25 14:52:24  jacob
//AVR now uses an interrupt type interrupt (not signal)
//Revision 1.38  2014/07/14 06:52:09  Peter
//STM32 default type is unsigned long
//Revision 1.37  2014/06/20 07:52:23  Peter
//Fixed template-bug in AvrSystemTimer
//Fixed bootloadertimer using SytemTimer
//Revision 1.36  2014/06/17 15:49:30  jacob
//Dumme Bootloadertimer for AVR
//Revision 1.35  2014/03/17 12:10:33  Peter
//STM32: Added interrupt Hook and function to add to timerval 
//Revision 1.34  2014/02/18 15:49:25  jacob
//STM version using systick
//Revision 1.33  2013/11/07 16:27:31  jacob
//Ugly fix for atmega128
//Revision 1.32  2013/11/07 11:58:23  jacob
//Prefix with vector to avoid warning
//Revision 1.31  2013/10/31 08:40:44  Peter
//No BootloaderTimer is not an error
//Revision 1.30  2013/09/20 13:16:53  jacob
//Added bootloadetimer for STM32
//Revision 1.29  2013/05/06 10:25:19  jacob
//Rename of intvector to avoid warns
//Revision 1.28  2013/02/22 15:51:34  jacob
//Initial STM32 version
//Revision 1.27  2013/02/18 17:54:45  jacob
//Fixed typo
//Revision 1.26  2013/01/31 07:14:01  Peter
//Only defines XMEGATIMER if timer exists
//Revision 1.25  2012/08/23 10:19:33  jacob
//ATMEL_TOOLCHAIN changes
//
//Revision 1.24  2012/08/22 17:10:58  jacob
//Attempt to support new atmel toolchain
//Revision 1.23  2012/06/21 00:13:16  jacob
//Added parameter to include stackcheck or not 
//Revision 1.22  2012/06/20 10:51:07  Peter
//BootloaderTimer only if BOOTLOADER defined
//Revision 1.21  2012/06/13 08:15:16  jacob
//Changed EMU define to WIN32
//Revision 1.20  2011/12/22 12:19:12  jacob
//More t_bootloader timer fixes
//Revision 1.19  2011/12/22 11:29:43  jacob
//Fixed problem with avr code included in non avr targets
//Revision 1.18  2011/12/13 12:08:27  jacob
//Implemented bootloader timer - tentative
//Revision 1.17  2011/12/07 14:05:36  Peter
//Converted enun to static const unsigned long
//Revision 1.16  2011/11/23 12:13:12  Peter
//Added frequency to AvrSystemTimer
//Revision 1.15  2011/11/02 14:32:32  Peter
//TESTET ON AVR ONLY
//Made timer variable type a template parameter.
//default is unsigned long
//Revision 1.14  2011/10/27 11:45:25  Peter
//Added template class for avr systemtimer
//Revision 1.13  2011/10/22 14:25:43  Peter
//Code does not work for AVR only XMEGA
//Revision 1.12  2011/10/04 15:20:58  Peter
//Avr 12MHz support
//Revision 1.11  2011/05/02 11:58:19  Peter
//No stack check in booloader
//Revision 1.10  2011/03/23 14:16:39  Peter
//SystemTimer class for EMU
//Revision 1.9  2011/02/22 19:15:07  jacob
//Added empty functions for NIOS
//Revision 1.8  2011/02/22 15:28:19  jacob
//Added StackCheck functions 
//Revision 1.6  2011/02/10 10:27:18  jacob
//Backup
//Revision 1.5  2010/12/22 19:25:37  jacob
//Now TimeStamp is added as a template
//Revision 1.4  2010/12/21 16:11:14  Johan
//backup (works: log-uart, sys-timer, led matrix)
//Revision 1.3  2010/10/11 07:58:50  jacob
//Local SP now static
//Revision 1.2  2010/10/08 09:51:13  jacob
//Revision 1.1  2010/10/07 12:47:42  jacob
//Initial revision
//Revision 1.2  2010/10/06 18:46:45  jacob
//Cleanup
//Revision 1.1  2010/09/17 11:51:24  jacob
//Revision 1.1  2010/09/17 11:48:43  jacob
//Initial revision
//Revision 1.2  2010/08/31 13:17:56  Johan
//Revision 1.1  2010/07/08 21:28:27  jacob
//Initial revision
//Revision 1.5  2010/03/29 14:15:43  Peter
//Backup
//Revision 1.4  2010/03/29 12:53:31  Peter
//Backup
//Revision 1.3  2010/03/24 15:38:33  Peter
//Backup
//Revision 1.2  2010/03/09 10:15:01  Peter
//Added stackpointer support
#ifndef _SYSTEMTIMER_H_
#define _SYSTEMTIMER_H_

#if defined(XMEGA)

#include "xmegatimer.h"
#include "avrutils.h"

typedef enum {
    TIMERPORT_C0, 
    TIMERPORT_D0, 
    TIMERPORT_E0, 
    TIMERPORT_F0
} t_timerport;

//  Forward declarations 
template <t_timerport PORT,typename T> class SystemTimer;
template <int A, int PORT> class TimerPortIO;       // The A parameter is to avoid having the specializations instantiated as this gives clash when this header file is 
                                                    // in multiple translation units 



template <t_timerport PORT, typename T = unsigned long>
class SystemTimer
{

    enum {
        OverFlowVector = TimerPortIO<0,PORT>::OverFlowVector
    };

public:

    typedef T TYPE;

    SystemTimer() {

        asm volatile (
                ".global __vector_%1\n\t"
                ".equ __vector_%1, %0 \n\t"
                :: "X" ((interrupt_type)(SystemTimer<PORT,T>::__vector_OverFlow)),"X" (OverFlowVector)
        );

        Init();
    };

    static void __vector_OverFlow(void) __attribute__ ((signal))
    {
        m_TimerVal++;
        FIXME(2 Make this optional in the template);
        #if !defined(BOOTLOADER)
          UpdateStackCheck();
        #endif
    };

    FIXME(2 Make this optional in the template);
    #if !defined(BOOTLOADER)
    static void UpdateStackCheck(void)
    {
        SCOPE_CLI;
        if ( SP < m_MinStackPointer ) {
                m_MinStackPointer = SP;
        } // endif
    }

    static unsigned int MinimumStackPointer(void)
    {
        SCOPE_CLI;
        return m_MinStackPointer;
    };
    #endif

    static T TimerVal(void)
    {
        // Ensure that g_Timerval is not altered during the return
        SCOPE_CLI;
        return m_TimerVal;
    };

    static void Init(void)
    {
        #if (XTAL_CPU==32000000UL)
            TC_SetPeriod( (&TimerPortIO<0,PORT>::TIMER), 501 );
            TC0_ConfigClockSource( &TimerPortIO<0,PORT>::TIMER, TC_CLKSEL_DIV64_gc);
            TC0_SetOverflowIntLevel(&TimerPortIO<0,PORT>::TIMER,TC_OVFINTLVL_MED_gc);
        #elif (XTAL_CPU==16000000UL)
            TC_SetPeriod( (&TimerPortIO<0,PORT>::TIMER), 251 );
            TC0_ConfigClockSource( &TimerPortIO<0,PORT>::TIMER, TC_CLKSEL_DIV64_gc);
            TC0_SetOverflowIntLevel(&TimerPortIO<0,PORT>::TIMER,TC_OVFINTLVL_MED_gc);
        #elif (XTAL_CPU==12000000UL)
            TC_SetPeriod( (&TimerPortIO<0,PORT>::TIMER), 1501 );
            TC0_ConfigClockSource( &TimerPortIO<0,PORT>::TIMER, TC_CLKSEL_DIV8_gc);
            TC0_SetOverflowIntLevel(&TimerPortIO<0,PORT>::TIMER,TC_OVFINTLVL_MED_gc);
        #elif (XTAL_CPU==2000000UL)
            TC_SetPeriod( (&TimerPortIO<0,PORT>::TIMER), 251 );
            TC0_ConfigClockSource( &TimerPortIO<0,PORT>::TIMER, TC_CLKSEL_DIV8_gc);
            TC0_SetOverflowIntLevel(&TimerPortIO<0,PORT>::TIMER,TC_OVFINTLVL_MED_gc);
        #else
            #error "Selected F_CPU not supported."
        #endif
    };


    static void TimerDisable()
    {
        TC0_SetOverflowIntLevel(&TimerPortIO<0,PORT>::TIMER, TC_OVFINTLVL_OFF_gc);
        m_TimerVal = 0;
    };

    static void TimerEnable()
    {
        TC0_SetOverflowIntLevel(&TimerPortIO<0,PORT>::TIMER, TC_OVFINTLVL_MED_gc);
    };

    static void TimerInc(TYPE IncVal)
    {
        SCOPE_CLI;
        m_TimerVal += IncVal;

    }

private:
    static volatile T m_TimerVal;
    static volatile unsigned int  m_MinStackPointer;
};

template <t_timerport PORT,typename T> volatile T SystemTimer<PORT,T>::m_TimerVal = 0L;
template <t_timerport PORT,typename T> volatile unsigned int  SystemTimer<PORT,T>::m_MinStackPointer = 0xFFFF;

#elif defined(NIOS2)
class SystemTimer
{
public:

    typedef unsigned long TYPE;

    SystemTimer() {
    };

    static unsigned int LocalSP(void)
    {
        SCOPE_CLI;
        FIXME(Implement);
        return 0;
    };

    static void UpdateStackCheck(void)
    {
    };

    static unsigned int MinimumStackPointer(void)
    {
        return 0;
    };

    static unsigned long TimerVal(void)
    {
        return GetTickCount();
    };


private:
    //static volatile unsigned long g_TimerVal;
    //static volatile unsigned int StackPointer;
};

#elif defined(WIN32)
class SystemTimer
{
public:

    typedef unsigned long TYPE;

    SystemTimer() {
    };

    static unsigned int LocalSP(void)
    {
    };

    static void UpdateStackCheck(void)
    {
    };

    static unsigned int MinimumStackPointer(void)
    {
        return 0;
    };

    static unsigned long TimerVal(void)
    {
        SCOPE_CLI // For emu
        return GetTickCount();
    };


private:
    //static volatile unsigned long g_TimerVal;
    //static volatile unsigned int StackPointer;
};

#elif defined(AVR)

template <bool S, typename SETUP> class StackCheckClass;

template <typename SETUP> class StackCheckClass<true,SETUP>
{
public:
    static volatile unsigned int  m_MinStackPointer;

    static void UpdateStackCheck(void)
    {
        SCOPE_CLI;
        if ( SP < m_MinStackPointer ) {
                m_MinStackPointer = SP;
        } // endif
    };

    static unsigned int MinimumStackPointer(void)
    {
        SCOPE_CLI;
        return m_MinStackPointer;
    };
};

template <typename SETUP> class StackCheckClass<false,SETUP>
{
public:
    inline static void UpdateStackCheck(void)
    {
    };
    inline static unsigned int MinimumStackPointer(void)
    {
        return 0;
    };
};

template <typename SETUP, typename T = unsigned long, bool StackCheck = true> 
class SystemTimerAvr : public StackCheckClass<StackCheck,SETUP>
{
public:

    using StackCheckClass<StackCheck,SETUP>::UpdateStackCheck;

    typedef T TYPE;
    static const unsigned long Frequency = SETUP::Frequency;

    SystemTimerAvr() {

        asm volatile (
                ".global __vector_%1\n\t"
                ".equ __vector_%1, %0 \n\t"
                :: "X" ((interrupt_type)(SystemTimerAvr<SETUP,T,StackCheck>::__vector_TimerIsr)),"X" (SETUP::InterruptVector)
        );

        Init();
    };

    static void __vector_TimerIsr(void) __attribute__ ((interrupt)) 
    {
        {
            SCOPE_CLI
            m_TimerVal++;
        }
        UpdateStackCheck();
    };

    static T TimerVal(void)
    {
        // Ensure that g_Timerval is not altered during the return
        SCOPE_CLI;
        return m_TimerVal;
    };

    static void Init(void)
    {
        SETUP::Init();
    };


    static void TimerDisable()
    {
        SETUP::Enable(false);
        m_TimerVal = 0;
    };

    static void TimerEnable()
    {
        SETUP::Enable(true);
    };

    static void TimerInc(T IncVal)
    {
        SCOPE_CLI;
        m_TimerVal += IncVal;

    }

private:
    static volatile T m_TimerVal;
    
};

template <typename SETUP,typename T, bool StackCheck> volatile T SystemTimerAvr<SETUP,T,StackCheck>::m_TimerVal = 0L;
template <typename SETUP> volatile unsigned int  StackCheckClass<true,SETUP>::m_MinStackPointer = 0xFFFF;
    
#elif defined(_STM32x_)

//void SystemTimerInt_Hook()  __attribute__ ((weak));

inline void SystemTimerInt_Hook_default() 
{
}


template <typename T = unsigned long, void (*U) (void) = SystemTimerInt_Hook_default> 
struct SystemTimer
{

private:
    static volatile T m_TimerVal;

public:

    typedef T TYPE;

    static bool Init(void)
    {
        if (SysTick_Config(SystemCoreClock / 1000)) { /* Setup SysTick for 1 msec interrupts */
            // Handle Error !
            FIXME(1a); 
            while (1);
        } // endif

        // Hack to set systick int priority 
        NVIC_InitTypeDef NVIC_InitStructure;
        SysTickIntInfo::Init(NVIC_InitStructure);
        NVIC_InitStructure.NVIC_IRQChannel                      = SysTick_IRQn;
        NVIC_InitStructure.NVIC_IRQChannelCmd                   = ENABLE;
        NVIC_Init(&NVIC_InitStructure); 
        return true;
    }

    static unsigned int LocalSP(void)
    {
        return 0;
    };

    static void UpdateStackCheck(void)
    {
    };

    static unsigned int MinimumStackPointer(void)
    {
        return 0;
    };

    static inline unsigned long TimerVal(void) __attribute__((always_inline))
    {
        BindVectors();
        TODO(lock only if type not 32 bit);
        SCOPE_CLI
        return m_TimerVal;
    };

    static void inline SystemTimerInt(void) __attribute__((always_inline))
    {
        m_TimerVal++;
        U();
    };

    static void inline TimerValInc(TYPE Value) __attribute__((always_inline))
    {
        SCOPE_CLI
        m_TimerVal += Value;
    };

    static void BindVectors(void)
    {
        asm volatile (
                ".thumb\n\t"
                ".global SysTick_Handler\n\t"
                ".equ SysTick_Handler, %c0 \n\t"
                :: "X" (SystemTimer::SystemTimerInt)
            ); 

    };

private:
    //static volatile unsigned int StackPointer;
};


template <typename T,void (*U) (void)> volatile T SystemTimer<T,U>::m_TimerVal = 0L;


#else 
 #error "SystemTimer not available for this target ";
#endif 


#if defined(XMEGA)

#define XMEGATIMER(num,port) \
template <int A> class TimerPortIO<A,num> {\
public: \
    static TC0_t& TIMER;\
    enum {OverFlowVector          = TC##port##_OVF_vect_num};\
};\
template <int A> TC0_t& TimerPortIO<A,num>::TIMER = TC##port; 

#ifdef TCC0 
XMEGATIMER(TIMERPORT_C0,C0); // Timer/Counter - Port C - Type 0
#endif
#ifdef TCD0 
XMEGATIMER(TIMERPORT_D0,D0); // Timer/Counter - Port D - Type 0
#endif
#ifdef TCE0 
XMEGATIMER(TIMERPORT_E0,E0); // Timer/Counter - Port E - Type 0
#endif
#ifdef TCF0 
XMEGATIMER(TIMERPORT_F0,F0); // Timer/Counter - Port F - Type 0
#endif
#undef XMEGATIMER

#endif 



template <typename TIMERSOURCE>
class TimeStamp
{
private:

    typename TIMERSOURCE::TYPE time;

public:
    // if parameter true, init to TimerVal(), else 0
    TimeStamp(bool init = false) {
        time = (init) ? TIMERSOURCE::TimerVal() : 0;
    };
    
    // manipulate timestamp value    
    void Set(typename TIMERSOURCE::TYPE t)       // set vaule
    {
        time = t;
    };

    void Mark(typename TIMERSOURCE::TYPE add = 0)  // set value to now + parameter (mark current)
    {
        time = TIMERSOURCE::TimerVal() + add;
    };

    void Step(typename TIMERSOURCE::TYPE val)       // add value to current (step forward)
    {
        time += val;
    };

    // evaluate time value
    typename TIMERSOURCE::TYPE Get(void)  // get value
    {
        return time;
    }
    bool TimeOut()                // did we pass current value
    {
        return TIMERSOURCE::TimerVal() >= time;
    };
                                      
    long Elapsed()                // return SIGNED time elapsed SINCE timestamp
    {
        return TIMERSOURCE::TimerVal() - time;
    }
    bool MoreEqThan(typename TIMERSOURCE::TYPE em)  // return true if more time has passed
    {
        return TIMERSOURCE::TimerVal() >= (time + em);
    }
    bool LessThan(typename TIMERSOURCE::TYPE lt)    // return true if less time has passed
    {
        return ( TIMERSOURCE::TimerVal() < (time + lt) );
    }


    // test if current timestamp is passed, then add new value to old value (not current time!)
    // Less "safe" since very outdated timestamp will result in many calls before up-to-date -- see Update()
    inline bool Interval(typename TIMERSOURCE::TYPE val) { return TimeOut() ? (Step(val), true) : false ; }     // return true if timeout

    // Test if current timestamp is passed, then add new value to current time
    // "Safe" since very old timestamp will be "corrected" after 1 call (technically less accurate) - see Interval()
    inline bool Update(typename TIMERSOURCE::TYPE val) { return TimeOut() ? (Mark(val), true) : false ; }   // return true if timeout

    /* 
     *  Interval() is more accurate since we get (on average) exactly one "return true" per timeout
     *  Update() is less accurate since we just step forward from current time, no matter if timeout was exceeded
    */

} ;


// 2 simple sw timers for saving codespace in bootloader
#if !defined(XMEGA) && defined(AVR)
template <typename Timer>
struct BootloaderTimer {
public:

    static const unsigned long Frequency = Timer::Frequency; // 1ms timer

    static TimeStamp<Timer> Timer_1;
    static TimeStamp<Timer> Timer_2;

    static void Init(void) __attribute__((always_inline))
    {
        Timer::Init();
    }

    static void Idle(void) __attribute__((always_inline))
    {
        // Nothing to do, timer inc from isr
    };

    static void Reset_1(const unsigned int Value) __attribute__((always_inline))
    {
        Timer_1.Mark(Value);
    };

    static void Reset_2(const unsigned int Value) __attribute__((always_inline))
    {
        Timer_2.Mark(Value);
    };

    static bool TimeOut_1(void) __attribute__((always_inline))
    {
        return Timer_1.TimeOut();
    }
    static bool TimeOut_2(void) __attribute__((always_inline))
    {
        return Timer_2.TimeOut();
    }
};

template <typename Timer> TimeStamp<Timer> BootloaderTimer<Timer>::Timer_1;
template <typename Timer> TimeStamp<Timer> BootloaderTimer<Timer>::Timer_2;


#elif defined(AVR) && !defined(__AVR_ATmega128__)
template <t_timerport PORT, unsigned long FREQ>
struct BootloaderTimer {
public:

    static const unsigned long Frequency = FREQ; 

    static void Init(void) __attribute__((always_inline))
    {
        FIXME(1 This needs verification);
        FIXME(2 generalize this setup of freq);
        #if (XTAL_CPU==32000000UL)
            TC_SetPeriod( (&TimerPortIO<0,PORT>::TIMER), 5001 );
            TC0_ConfigClockSource( &TimerPortIO<0,PORT>::TIMER, TC_CLKSEL_DIV64_gc);
            //TC0_SetOverflowIntLevel(&TimerPortIO<0,PORT>::TIMER,TC_OVFINTLVL_MED_gc);
        #elif (XTAL_CPU==16000000UL)
            TC_SetPeriod( (&TimerPortIO<0,PORT>::TIMER), 2501 );
            TC0_ConfigClockSource( &TimerPortIO<0,PORT>::TIMER, TC_CLKSEL_DIV64_gc);
            //TC0_SetOverflowIntLevel(&TimerPortIO<0,PORT>::TIMER,TC_OVFINTLVL_MED_gc);
        #elif (XTAL_CPU==12000000UL)
            TC_SetPeriod( (&TimerPortIO<0,PORT>::TIMER), 15001 );
            TC0_ConfigClockSource( &TimerPortIO<0,PORT>::TIMER, TC_CLKSEL_DIV8_gc);
            //TC0_SetOverflowIntLevel(&TimerPortIO<0,PORT>::TIMER,TC_OVFINTLVL_MED_gc);
        #elif (XTAL_CPU==2000000UL)
            TC_SetPeriod( (&TimerPortIO<0,PORT>::TIMER), 2501 );
            TC0_ConfigClockSource( &TimerPortIO<0,PORT>::TIMER, TC_CLKSEL_DIV8_gc);
            //TC0_SetOverflowIntLevel(&TimerPortIO<0,PORT>::TIMER,TC_OVFINTLVL_MED_gc);
        #else
            #error "Selected F_CPU not supported."
        #endif

        TC_Restart((&TimerPortIO<0,PORT>::TIMER));

        #if defined(XTAL_CPU_PRESCALED)
            #error "XTAL_CPU_PRESCALED not supported."
        #endif
    }
    static void Idle(void) __attribute__((always_inline))
    {
        
        if (TC_GetOverflowFlag((&TimerPortIO<0,PORT>::TIMER))) { 
            TC_ClearOverflowFlag((&TimerPortIO<0,PORT>::TIMER));
            if ((TimerPortIO<0,PORT>::TIMER).CCA)   (TimerPortIO<0,PORT>::TIMER.CCA)--;
            if ((TimerPortIO<0,PORT>::TIMER).CCB)   (TimerPortIO<0,PORT>::TIMER.CCB)--;
        } // endif 
         
    }
    static void Reset_1(const unsigned int Value) __attribute__((always_inline))
    {
        TimerPortIO<0,PORT>::TIMER.CCA = Value;
    }
    static void Reset_2(const unsigned int Value) __attribute__((always_inline))
    {
        TimerPortIO<0,PORT>::TIMER.CCB = Value;
    }
    static bool TimeOut_1(void) __attribute__((always_inline))
    {
        return (TimerPortIO<0,PORT>::TIMER.CCA == 0 ? true : false);
    }
    static bool TimeOut_2(void) __attribute__((always_inline))
    {
        return (TimerPortIO<0,PORT>::TIMER.CCB == 0 ? true : false);
    }
};

#elif defined(_STM32x_)
template <int PORT>
struct BootloaderTimer {
public:

    static const unsigned long Frequency = 1000; // 10ms timer

    static unsigned int Tim1;
    static unsigned int Tim2;

    static void Init(void) __attribute__((always_inline))
    {
    }

    static void Idle(void) __attribute__((always_inline))
    {
    }

    static void Reset_1(const unsigned int Value) __attribute__((always_inline))
    {
        extern volatile unsigned int msTicks;
        Tim1 = msTicks + Value;
    }

    static void Reset_2(const unsigned int Value) __attribute__((always_inline))
    {
        extern volatile unsigned int msTicks;
        Tim2 = msTicks + Value;
    }

    static bool TimeOut_1(void) __attribute__((always_inline))
    {
        extern volatile unsigned int msTicks;
        return (msTicks > Tim1 ? true : false);
    }

    static bool TimeOut_2(void) __attribute__((always_inline))
    {
        extern volatile unsigned int msTicks;
        return (msTicks > Tim2 ? true : false);
    }

};

template <int PORT> unsigned int BootloaderTimer<PORT>::Tim1;
template <int PORT> unsigned int BootloaderTimer<PORT>::Tim2;


#endif 




#endif // _SYSTEMTIMER_H_

