//$Id: target.h 1.2 2014/11/25 15:06:44 jacob tnt $
//$Log: target.h $
//Revision 1.2  2014/11/25 15:06:44  jacob
//SystemTimer scale down
//Revision 1.2  2014/11/21 13:53:00  carsten
// SystemTimerSetup: Changed to 32bit => Decrease interrupt timing overhead
//Revision 1.1  2014/06/17 14:25:08  jacob


#pragma once 

#include "avriodefs.h"

#define HB_LED        (PORTDEF(E) | 3)

#define TXD0          (PORTDEF(E) | 1)              
#define TXD1          (PORTDEF(D) | 3)              

#define RXD0          (PORTDEF(E) | 0)              
#define RXD1          (PORTDEF(D) | 2)        
     

#define FLASHCTRL     (PORTDEF(F) | 4)


#define GPIO_0        (PORTDEF(B) | 2)              
#define GPIO_1        (PORTDEF(B) | 3)              



#define SCOPE_DEBUG0 CScopeDebug0 DummyScopeDebug0;
#define SCOPE_DEBUG1 CScopeDebug1 DummyScopeDebug1;

class CScopeDebug0
    {
    public:
        CScopeDebug0() {
            SetBit(GPIO_0);
        }
        ~CScopeDebug0(){
            ClrBit(GPIO_0);
        }
    };

class CScopeDebug1
    {
    public:
        CScopeDebug1() {
            SetBit(GPIO_1);
        }
        ~CScopeDebug1(){
            ClrBit(GPIO_1);
        }
    };


    template <int N>
    void DebugToggle0(void)
    { 
        // Debug pin 1 
        for (int i=0;i<N;i++) { 
            SetBit(GPIO_0);
            ClrBit(GPIO_0);
        } // endfor
    }



#include "uart.h"
#include "SystemTimer.h"

// Watchdog hack for undefined function in SerFlash.h
#define WatchDog()      asm("wdr")

// NOTE: System timer is 1000Hz
struct SystemTimerSetup{
    enum { InterruptVector  =   TIMER1_COMPA_vect_num  };
    static void Init(void) {
        TCCR1A = 0;
        TCCR1B = (1<<CS10) | (1<<WGM12);        // Div with 1
        OCR1A = (XTAL_CPU/1000)-1;
        Enable(true);
    };

    static void Enable(bool En)
    {
        if (En) {
            TIMSK |= (1 << OCIE1A);
        } else {
            TIMSK &= ~(1 << OCIE1A);
        } // endif
    }
        
    static const unsigned long Frequency = XTAL_CPU;
};

typedef SystemTimerAvr<SystemTimerSetup,unsigned long,false> t_SystemTimer;

typedef Uart<1,115200,                     128,256>   t_DebugUart;


#define MINSTACKINFO extern unsigned int __bss_end;\
                     log_dev("SP: %u bytes\n",t_SystemTimer::MinimumStackPointer()-( (unsigned int) &__bss_end));


