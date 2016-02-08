//$Id: avrutils.h 1.45 2014/07/18 09:49:42 jacob tnt $
//$Log: avrutils.h $
//Revision 1.45  2014/07/18 09:49:42  jacob
//Revision 1.44  2014/07/08 09:17:04  jacob
//Typo fix
//Revision 1.43  2014/06/26 12:43:06  Peter
//Added WriteResetSourceRegister
//Revision 1.42.1.1  2014/06/18 08:27:47  Peter
//Duplicate revision
//Revision 1.41  2013/05/06 09:57:53  jacob
//Added inline to delay
//Revision 1.40  2013/04/11 10:16:15  jacob
//Moved inlined functions to header interrupt move functions
//Revision 1.39  2012/08/23 10:04:36  jacob
//ATMEL_TOOLCHAIN fix
//Revision 1.38  2012/08/22 17:19:31  jacob
//Added interrupt_type
//Revision 1.37  2012/07/03 09:36:40  jacob
//Typo fix in isBOD
//Revision 1.36  2012/07/03 09:34:40  jacob
//Moved delay loop 2 to header file 
//Revision 1.35  2011/11/25 07:14:56  jacob
//Added attributes
//Revision 1.34  2011/11/24 12:21:20  jacob
//Inlines init in CresetSource
//Revision 1.33  2011/11/23 12:09:16  Peter
//ResetSource changes
//Revision 1.32  2011/11/11 12:12:10  Peter
//Added support for dual speed systems
//Revision 1.31  2011/10/22 14:26:03  Peter
//Fix for mega32U2
//Revision 1.30  2011/05/06 12:27:20  Peter
//Updated xmega reset source
//Revision 1.29  2011/03/02 07:19:09  Peter
//Added  is_sei() and is_cli() for xmega
//Revision 1.28  2011/02/08 12:12:15  jacob
//Added SCOPE_PULSE
//Revision 1.27  2011/02/02 11:16:34  jacob
//Added RebootWD
//Revision 1.26  2011/01/20 14:39:37  Johan
//Added Reset Flag string function to CResetSource and SDRF
//(spike detection has been disowned by Atmel in later datasheets, though)
//Revision 1.25  2010/12/21 16:10:12  Johan
//Lines 71-75,  toggled some h-file includes to avoid circular h-file problem.
//Revision 1.24  2010/12/17 13:59:45  jacob
//Added function to set resetsource
//Revision 1.23  2010/10/08 14:52:59  jacob
//Added function to return the m_source var
//Revision 1.22  2010/09/14 09:39:46  jacob
//Added support for MEGA164P
//Revision 1.21  2010/07/09 13:20:42  Johan
//udelay inclosed in brackets
//Revision 1.20  2010/04/16 09:33:32  Peter
//JTAG enable/disable functions
//Removed unused variable ResetSource
//Revision 1.19  2010/03/30 09:22:56  Peter
//Added XMEGA support functions
//Revision 1.18  2010/02/12 14:07:43  jacob
//Disabled ScopeDebug
//Revision 1.17  2010/02/12 13:34:33  jacob
//XMEGA support
//Revision 1.16  2010/01/29 09:08:28  jacob
//Tentative XMEGA support
//Revision 1.15  2010/01/13 13:13:08  Peter
//m_Source is now public
//Revision 1.14  2009/12/21 10:40:24  jacob
//Fix in CResetSource for AT90CAN128
//Revision 1.13  2009/12/17 15:18:25  jacob
//WatchDog clear fix...
//Revision 1.12  2009/12/15 09:22:04  jacob
//Removed ScopeDebug
//Revision 1.11  2009/12/15 07:39:31  Peter
//Only debug changes
//Revision 1.10  2009/12/03 15:14:57  jacob
//Tentative CAN device support
//Revision 1.9  2009/11/02 11:11:08  Peter
//EMU changes
//Revision 1.8  2009/06/21 11:50:01  jacob
//Added support for USB1287
//Revision 1.7  2008/12/02 08:56:18  jacob
//Added CResetSource Class - tentative
//Revision 1.6  2008/10/29 12:38:37  jacob
//Minor cleanup
//Revision 1.5  2008/10/20 10:55:35  jacob
//Added SCOPE_CLI
//Revision 1.4  2008/10/01 08:33:23  jacob
//Backup
//Revision 1.3  2008/08/27 15:24:52  jacob
//Backup after changes related to EMU
//Revision 1.2  2008/08/22 12:13:44  jacob
//Added interrupt move functions for mega32 only 
//changed call interface to native C types 
//Revision 1.1  2008/08/21 10:50:47  jacob
//Revision 1.3  2007/08/14 11:13:06  jacob
//Backup
//Revision 1.2  2007/05/28 15:27:27  jacob
//backup
//Revision 1.1  2007/04/17 16:54:13  jacob
//Initial revision
//Revision 1.2  2007/04/17 16:39:11  jacob
//Revision 1.1  2007/04/17 16:26:51  jacob
//Initial revision
//Revision 1.3  2004/12/11 13:56:19  Jacob
//Backup
//Revision 1.2  2004/11/26 11:55:33  Jacob
//Now udelay accepts delays above 500
//Revision 1.1  2004/11/18 22:03:46  Jacob
//Initial revision

#ifndef __AVRUTILS_H_
#define __AVRUTILS_H_

#include "CommonSupport.h"



// 16-bit count, 4 cycles/loop 
static void inline delay_loop_2(unsigned int __count) __attribute__((always_inline));
static void inline delay_loop_2(unsigned int __count)
{
    #if !defined(WIN32)
	asm volatile (
		"1: sbiw %0,1" "\n\t"
		"brne 1b"
		: "=w" (__count)
		: "0" (__count)
	);
    #else 
    #endif 
}


void delay_loop_1(unsigned char __count);
   
   
   
// delays for the given number of milliseconds                            
void delay(unsigned int ms);
void delay_ms(unsigned int ms);

#if defined (XTAL_CPU_PRESCALED) // We have a second freq
  #if defined (__AVR_ATmega32U2__)
    #define XTAL_CPU_PRESCALER_VALUE      (1 << (CLKPR & 0x0F))
  #else
   #error "No variable xtal support for this target"
  #endif

  #define udelay(us) \
          if ((XTAL_CPU/XTAL_CPU_PRESCALED) == XTAL_CPU_PRESCALER_VALUE) { \
          if (((unsigned int)(((XTAL_CPU_PRESCALED/10)*(unsigned long)(us)/400000L))) > 1) delay_loop_2((unsigned int)(((XTAL_CPU_PRESCALED/10)*(unsigned long)(us)/400000L)-1L)); \
          } else { \
              delay_loop_2((unsigned int)(((XTAL_CPU/10)*(unsigned long)(us)/400000L)-1L)); \
          }
#else

  FIXME(2 calling udelay with to low a value, denpending on f_cpu will create a very long delay);

  #define udelay(us) ({ delay_loop_2((unsigned int)(((XTAL_CPU/10)*(unsigned long)(us)/400000L)-1L) ); })     
#endif


int ClockCalibrate(void);

void move_interrupts_to_app(void)  __attribute__((always_inline));
void move_interrupts_to_boot(void) __attribute__((always_inline));

void inline move_interrupts_to_app(void)
{
    FIXME(Test for IOM164_H);
    #if defined(__AVR_ATmega1281__)  || \
        defined(__AVR_AT90USB1287__) || \
        defined(__AVR_AT90CAN128__)  || \
        defined(__AVR_ATmega32U2__)  || \
        defined(__AVR_ATmega128__)   || \
        defined(_AVR_IOM164_H_)                    

        FIXME(check for __AVR_ATmega32U2__);
        unsigned char  temp;
        // Get MCUCR
        temp = MCUCR;
        // Enable change of Interrupt Vectors
        MCUCR = temp | (1<<IVCE);
        // Move interrupts to App Flash section
        MCUCR = temp & ~(1<<IVSEL);

    #elif defined(__AVR_ATmega32__)
        // Enable change of interrupt vectors
        GICR = (1<<IVCE);
        // Move interrupts to userspace  Flash section
        GICR = 0;
    #elif defined(XMEGA)
        uint8_t temp = PMIC.CTRL & ~PMIC_IVSEL_bm;
        CCP = CCP_IOREG_gc;
        PMIC.CTRL = temp;
    #else
        #error #error "move_interrupts_to_app does not work for this target"
    #endif 
    

}

void inline move_interrupts_to_boot(void)
{
    #if defined(__AVR_ATmega1281__)  || \
        defined(__AVR_AT90USB1287__) || \
        defined(_AVR_IOM164_H_)      || \
        defined(__AVR_ATmega32U2__)  || \
        defined(__AVR_ATmega128__)   || \
        defined(__AVR_AT90CAN128__) 

        FIXME(check for __AVR_ATmega32U2__);
        MCUCR = (1<<IVCE);
        MCUCR = (1<<IVSEL);

    #elif defined(__AVR_ATmega32__)
        // Enable change of interrupt vectors
        GICR = (1<<IVCE);
        // Move interrupts to boot Flash section
        GICR = (1<<IVSEL);
    #elif defined(XMEGA)
        uint8_t temp = PMIC.CTRL | PMIC_IVSEL_bm;
        CCP = CCP_IOREG_gc;
        PMIC.CTRL = temp;
    #else 
        #error #error "move_interrupts_to_boot does not work for this target"
    #endif 
}



void Reboot(void)   __attribute__((__noreturn__));
void RebootWD(void) __attribute__((__noreturn__));

void Jtag_Disable(void);
void Jtag_Enable(void);

void EnterBootloader(void) __attribute__((__noreturn__));


#if defined (WIN32)
#define __attribute__(x)
#endif

#if defined (AVR)

    #ifndef ATMEL_TOOLCHAIN
        #define ATMEL_TOOLCHAIN 0
    #endif 
    
    #if ATMEL_TOOLCHAIN == 0
        typedef prog_int32_t interrupt_type;
    #elif ATMEL_TOOLCHAIN == 1
        typedef int32_t interrupt_type;
    #else
        #error "Unsupported compiler"
    #endif
#endif

struct CResetSource
{
public:
    void init(void) __attribute__((always_inline))
    {
        asm("wdr");
        FIXME(Test for IOM164_H);
        #if defined(_AVR_IOM32_H_)      || \
            defined(_AVR_IOM1281_H_)    || \
            defined(_AVR_ATmega32U2_H_) || \
            defined(_AVR_AT90USB1287_H_)
         m_Source = MCUSR & 0x1F;           // Store reset source
         MCUSR       &= ~0x1F;              // And clear it
         WDTCSR     |= (1 << WDCE) | (1 << WDE);
         WDTCSR     = 0x00;
        #elif defined(_AVR_IOM128_H_)
         FIXME(1a untested); 
         m_Source = MCUCSR & 0x1F;           // Store reset source
         MCUCSR      &= ~0x1F;              // And clear it
         WDTCR     |= (1 << WDCE) | (1 << WDE);
         WDTCR     = 0x00;
         
        #elif defined(__AVR_AT90CAN128__)
         m_Source = MCUSR & 0x1F;           // Store reset source
         MCUSR       &= ~0x1F;              // And clear it
         WDTCR      |= (1 << WDCE) | (1 << WDE);
         WDTCR      = 0x00;
        #elif defined(XMEGA)
         m_Source   = RST.STATUS;
         // Clear reset source
         RST.STATUS = (RST_PORF_bm | RST_EXTRF_bm | RST_BORF_bm | RST_WDRF_bm | RST_PDIRF_bm | RST_SRF_bm | RST_SDRF_bm);    
        #elif defined(_AVR_IOM164_H_) 
         m_Source = MCUSR & 0x1F;           // Store reset source
         MCUSR       &= ~(1 << WDRF);              // And clear it
         WDTCSR     |= (1 << WDCE) | (1 << WDE);
         WDTCSR     = 0x00;


        #elif defined (WIN32)
         m_Source = 0x00;
        #else
         #error "CResetSource does not work for this target"
        #endif
    }


    #if defined(XMEGA)

        // spike flag was removed from A1 datasheet in revision 12/09??? (8077H-2)
        // bool IsSPIKE()  __attribute__((always_inline)) {return  m_Source & RST_SDRF_bm;}

        // SRF: Software Reset Flag. This flag is set if a Software reset occurs. The flag will be cleared by a power-on reset or by writing a one to the bit location.
        bool IsSW()     __attribute__((always_inline)) {return  m_Source & RST_SRF_bm;}

        // PDIRF: Program and Debug Interface Reset Flag. This flag is set if a Programming interface reset occurs. The flag will be cleared by a power-on reset or by writing a one to the bit location.
        bool IsJTAG()   __attribute__((always_inline)) {return  m_Source & RST_PDIRF_bm;}

        // WDRF: Watchdog Reset Flag. This flag is set if a Watchdog reset occurs. The flag will be cleared by a power-on reset or by writing a one to the bit location.
        bool IsWD()     __attribute__((always_inline)) {return  m_Source & RST_WDRF_bm;}

        // BORF: Brown Out Reset Flag. This flag is set if a Brown out reset occurs. The flag will be cleared by a power-on reset or by writing a one to the bit location.
        bool IsBOD()    __attribute__((always_inline)) {return  m_Source & RST_BORF_bm;}

        // EXTRF: External Reset Flag. This flag is set if an External reset occurs. The flag will be cleared by a power-on reset or by writing a one to the bit location.
        bool IsEXT()    __attribute__((always_inline)) {return  m_Source & RST_EXTRF_bm;}

        // PORF: Power On Reset Flag. This flag is set if a Power-on reset occurs. Writing a one to the flag will clear the bit location.
        bool IsPOR()    __attribute__((always_inline)) {return  m_Source & RST_PORF_bm;}

        bool IsNone()   __attribute__((always_inline)) {return (m_Source == 0);}

        // build string of Reset Source Flags and shoot it into provided buffer
        void snResetFlagStr(char* str, unsigned char nmax) ;

    #else 

        bool IsWD()     __attribute__((always_inline)) {return  m_Source & (1 << WDRF );}
        #if !defined(_AVR_ATmega32U2_H_)
        bool IsJTAG()   __attribute__((always_inline)) {return  m_Source & (1 << JTRF );}
        #endif 
        bool IsBOD()    __attribute__((always_inline)) {return  m_Source & (1 << BORF );}
        bool IsEXT()    __attribute__((always_inline)) {return  m_Source & (1 << EXTRF);}
        bool IsPOR()    __attribute__((always_inline)) {return  m_Source & (1 << PORF );}
        bool IsNone()   __attribute__((always_inline)) {return (m_Source ==0);}
    #endif 

    unsigned char RawSource(void) 
    {   
        return m_Source;
    }

    void SetResetSource(unsigned char val)
    {
        m_Source = val;

    }

    void WriteResetSourceRegister()
    {
         #if defined(XMEGA)
         RST.STATUS = m_Source;
        #else
         //#warning TODO
        #endif
  }

private:
    unsigned char m_Source; 
};

extern CResetSource ResetSource;



#if !defined (WIN32)

#define SCOPE_CLI CScopeCli DummyScopeCli;
class CScopeCli
{
public:
    CScopeCli() {
        m_sreg = SREG;
        cli();
    }

    ~CScopeCli() {
        SREG = m_sreg;
    }

private:
    unsigned char m_sreg; 

};

template <typename PIN>
class SCOPE_PULSE
{
public: 
    SCOPE_PULSE()
    {
        PIN::set();
    };

    ~SCOPE_PULSE()
    {
        PIN::clr();
    };
};

#if defined(XMEGA)
 #define is_sei()        ((SREG & CPU_I_bm) ? true : false)
 #define is_cli()        ((SREG & CPU_I_bm) ? false : true)
#endif // defined(XMEGA)





/*
#define SCOPE_DEBUG(x) CScopeDebug<x> DummyScopeDebug;

template <unsigned long PIN>
class CScopeDebug
{
public:
    CScopeDebug() {SetBit(PIN);}
    ~CScopeDebug(){ClrBit(PIN);}
};
*/

#endif


//---- XMEGA Support Functions Prototypes ----//
#if defined(XMEGA)
 unsigned char SP_ReadCalibrationByte(unsigned char index);
 void xmega_get_serial(unsigned char* pSerial, unsigned char Len);
#endif // defined(XMEGA)


#endif //__AVRUTILS_H_
                                             
