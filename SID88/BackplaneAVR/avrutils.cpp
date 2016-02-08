//$Id: avrutils.cpp 1.43 2014/07/18 09:49:39 jacob tnt $
//$Log: avrutils.cpp $
//Revision 1.43  2014/07/18 09:49:39  jacob
//Added delay_ms
//Revision 1.42  2014/06/20 06:51:29  Peter
//Changed a #error to #warning 
//Revision 1.41  2014/06/20 06:45:35  Peter
//Changed a #warning to #error
//Revision 1.40  2014/06/18 08:28:09  jacob
//Removed some headers 
//Revision 1.39  2013/11/07 11:58:42  jacob
//AT128 'fix'
//Revision 1.38  2013/04/11 10:16:15  jacob
//Moved inlined functions to header interrupt move functions
//Revision 1.37  2013/01/31 07:49:43  Peter
//Added bootloader jump for xmega128A4U - untested!
//Changed define-names for xmega128A1 and xmega64A1 in EnterBootloader.
//Revision 1.36  2013/01/23 09:56:32  Peter
//Added bootloader jump for AT90USB1287
//Untested!
//Revision 1.35  2012/07/03 09:34:40  jacob
//Moved delay loop 2 to header file 
//Revision 1.34  2011/11/30 09:08:51  Peter
//Enterbootloader for ATmega32U2
//Revision 1.33  2011/11/25 07:14:31  jacob
//Adde some comments
//Revision 1.32  2011/11/23 12:09:16  Peter
//ResetSource changes
//Revision 1.31  2011/11/11 12:12:09  Peter
//Added support for dual speed systems
//Revision 1.30  2011/10/22 14:26:20  Peter
//Fix for mega32U2
//Revision 1.29  2011/05/02 08:39:21  jacob
//Cleanup 
//Revision 1.28  2011/04/07 08:45:34  jacob
//Progmem warn fix
//Revision 1.27  2011/03/02 09:23:54  jacob
//Include file order fix
//Revision 1.26  2011/02/22 18:23:43  jacob
//Added support for xmega64A1
//Revision 1.25  2011/02/02 11:16:33  jacob
//Added RebootWD
//Revision 1.24  2011/01/21 16:02:03  Johan
//changed Reboot() from WD timeout to HW supported software reset
//Revision 1.23  2011/01/20 14:39:37  Johan
//Added Reset Flag string function to CResetSource and SDRF
//(spike detection has been disowned by Atmel in later datasheets, though)
//Revision 1.22  2010/12/22 11:48:53  jacob
//Added EnterBootloader for XMEGA
//Revision 1.21  2010/09/21 18:08:57  jacob
//JTAG enable/disable now works for xmega
//Revision 1.20  2010/09/14 09:39:42  jacob
//Added support for MEGA164P
//Revision 1.19  2010/08/31 07:34:05  Johan
//Changed #warning to FIXME()
//Revision 1.18  2010/06/01 06:25:22  Peter
//Changed error to warning
//Revision 1.17  2010/04/16 09:33:12  Peter
//JTAG enable/disable functions
//Revision 1.16  2010/03/30 09:45:41  Peter
//now includes <stddef.h>
//Revision 1.15  2010/03/30 09:22:56  Peter
//Added XMEGA support functions
//Revision 1.14  2010/02/12 12:19:05  jacob
//More Xmega support
//Revision 1.13  2010/01/29 09:08:54  jacob
//Tentative XMEGA support
//Revision 1.12  2010/01/11 13:53:21  jacob
//degraded fixme
//Revision 1.11  2009/12/21 14:41:02  jacob
//Simplified version
//Revision 1.10  2009/12/07 10:01:09  jacob
//Added comment
//Revision 1.9  2009/12/03 15:14:57  jacob
//Tentative CAN device support
//Revision 1.8  2009/06/21 11:49:41  jacob
//Added support for USB1287
//Revision 1.7  2008/12/02 09:01:20  jacob
//Added CResetSource 
//Updated interrupt vector move functions
//Revision 1.5  2008/10/20 10:56:48  jacob
//Added Reboot function
//Revision 1.4  2008/10/01 08:33:23  jacob
//Backup
//Revision 1.3  2008/08/27 15:24:52  jacob
//Backup after changes related to EMU
//Revision 1.2  2008/08/22 12:13:44  jacob
//Added interrupt move functions for mega32 only 
//changed call interface to native C types 
//Revision 1.1  2008/08/21 10:50:42  jacob
//Revision 1.6  2007/11/16 13:30:25  Jacob
//Backup
//Revision 1.5  2007/10/29 19:15:16  Jacob
//Backup
//Revision 1.4  2007/10/11 13:40:08  Jacob
//backup
//Revision 1.3  2007/08/14 11:13:06  jacob
//Backup
//Revision 1.2  2007/05/28 15:27:27  jacob
//backup
//Revision 1.1  2007/04/17 16:54:13  jacob
//Initial revision
//Revision 1.2  2007/04/17 16:39:11  jacob
//Revision 1.1  2007/04/17 16:26:53  jacob
//Initial revision
//Revision 1.2  2004/11/26 11:55:16  Jacob
//Clockcalibrate now uses stk_cli - sti approach
//Revision 1.1  2004/11/18 22:03:46  Jacob
//Initial revision



#include <stdlib.h>         // For abs 
#include <stddef.h>

#include "CommonSupport.h"
#include "avrutils.h"

// 8-bit count, 3 cycles/loop
void delay_loop_1(unsigned char __count)
{
    #if !defined(WIN32)
	asm volatile (
		"1: dec %0" "\n\t"
		"brne 1b"
		: "=r" (__count)
		: "0" (__count)
	);
    #else 
    #endif 
}

 
#if defined (XTAL_CPU_PRESCALED)

void delay(unsigned int ms)
{
    if ((XTAL_CPU/XTAL_CPU_PRESCALED) == XTAL_CPU_PRESCALER_VALUE) { 
        while (ms--) {
            delay_loop_2(XTAL_CPU_PRESCALED/4000L);
        } // endwhile
    } else {
        while (ms--) {
            delay_loop_2(XTAL_CPU/4000L);
        } // endwhile
    } // endif
}

#else          
          
void delay(unsigned int ms)
{
    while (ms--) {
        delay_loop_2(XTAL_CPU/4000L);
    } // endwhile
}

#endif

void delay_ms(unsigned int ms)
{
    return delay(ms);
}


/*
#define LIMIT 880
int ClockCalibrate(void)
{

#if defined (WIN32) 
	return 1;
#endif 

    unsigned int i;
    unsigned char tmp;
    int adjust = 0;
    char sreg;

    while (1) {
        sreg = SREG;
        cli();
        i = 0;
        tmp = TCNT2;
        while (TCNT2 == tmp) {} // endwhile
        tmp = TCNT2;
        while (TCNT2 == tmp) {i++;} // endwhile
        SREG = sreg;

        if (abs(i-LIMIT) < 10) return adjust;

        adjust = 1;

        if (i>LIMIT) { 
            OSCCAL--;
        } else {
            OSCCAL++;
        } // endif

    } // endwhile
    return 0;
} 
*/ 
 
 

/*
void udelay(unsigned int us)
{
    if (IOregVal(VCCENABLE)) { 
        _delay_loop_2(XTAL_CPU/400000L);
    } else {
        _delay_loop_2(XTAL_CPU/400000L);
    } // endif
    
}
*/

void Reboot(void) 
{
    #if defined(XMEGA)
        cli();
        CCP = CCP_IOREG_gc;
        RST.CTRL = 0x01 ;
        while (1) {
        } // endwhile
    #else 
        // Done this way to ensure a clean boot of the usercode with all the registers cleared. 
        cli();
        wdt_enable(WDTO_15MS);
        while (1) {
        } // endwhile 
    #endif 
};

void RebootWD(void) __attribute__((__noreturn__));
void RebootWD(void) 
{
    #if defined(XMEGA)
        cli();
        CCP = CCP_IOREG_gc;
        WDT.CTRL = WDT_PER_16CLK_gc | WDT_CEN_bm | WDT_ENABLE_bm;         // 16ms
        while (1) {
        } // endwhile
    #else 
        // Done this way to ensure a clean boot of the usercode with all the registers cleared. 
        cli();
        wdt_enable(WDTO_15MS);
        while (1) {
        } // endwhile 
    #endif 
};



void Jtag_Disable(void)
{
#if !defined(XMEGA)
    #if defined(__AVR_ATmega32U2__)
        // Targets without JTAG 
    #else 
    // Disable Jtag
    unsigned char Tmp;
    Tmp = MCUCR;
    Tmp |= (1 << JTD);
    SCOPE_CLI
    MCUCR = Tmp;
    MCUCR = Tmp;
    #endif 
#else
    SCOPE_CLI
    unsigned char temp = MCU.MCUCR | MCU_JTAGD_bm;
    CCP = CCP_IOREG_gc;
    MCU.MCUCR = temp;
#endif

}

void Jtag_Enable(void)
{
#if !defined(XMEGA)
    #if defined(__AVR_ATmega32U2__)
        // Targets without JTAG 
    #else 
    // Enable Jtag
    unsigned char Tmp;
    Tmp = MCUCR;
    Tmp &= ~(1 << JTD);
    SCOPE_CLI
    MCUCR = Tmp;
    MCUCR = Tmp;
    #endif 
#else
    SCOPE_CLI
    unsigned char temp = MCU.MCUCR & ~MCU_JTAGD_bm;
    CCP = CCP_IOREG_gc;
    MCU.MCUCR = temp;
#endif
}


// The instance 
CResetSource ResetSource;

extern "C" {
void BootSourceInit (void) __attribute__ ((naked)) __attribute__ ((section (".init5"))); // The Init 5 section is after clearing the bss
void BootSourceInit (void)
{
    ResetSource.init();
}
}



#if defined(XMEGA)
void CResetSource::snResetFlagStr(char* str, unsigned char nmax)
{
    unsigned char source = RawSource() ;
    unsigned char value = source ;
    char buffer[100] ;
    char* index = buffer ;
    char next_byte ;
    bool Previous = false ; // keep track of if space is needed between flags :)

    // official flag names (LSB to MSB)
    // spike flag was removed from A1 datasheet in revision 12/09??? (8077H-2)
    
    static const char RstStr[] PROGMEM2 = "PORF\0EXTRF\0BORF\0WDRF\0PDIRF\0SRF\0SDRF\0\0";

    PGM_P desc = RstStr;

    //log_dev("desc: %p\n", desc) ;   

    // run through bits and names
    do {
        if(value & 0x01) {
            if(Previous) {
                // make space after previous flag
                *(index++) = ' ' ;
            }
            // flags set, copy string
            while( (next_byte = pgm_read_byte(desc++)) ) {
                *(index++) = next_byte ;
            }
            Previous = true ;
        } else {
            // flag not set, skip string
            while( (next_byte = pgm_read_byte(desc++)) ) ;
        }
        value >>= 1 ;
    } while ( pgm_read_byte(desc) > 0 ) ; // pstr is double-terminated

    //log_dev("desc: %p\n", desc) ;   

    if(not Previous) {
        // hint if no flags were set in stead of empty brackets
        static const char RstNone[] PROGMEM2 = "none";
        strcpy_P(index, RstNone);
    } else {
        // dont forget to terminate
        *index = 0 ;
    }

    // write nice msg
    snprintf(str, nmax, "Reset Flags: 0x%2.2X (%s)", source, buffer) ;
    return;
}
#endif

void EnterBootloader(void)
{
    #if defined(__AVR_ATxmega128A1__)
        cli();
        asm("ldi r30, 0x00");
        asm("ldi r31, 0x00");
        asm("ldi r27, 0x01");
        asm("out 0x3c, r27");
        asm("eijmp");
    #elif defined(__AVR_ATxmega64A1__)
        cli();
        asm("ldi r30, 0x00");
        asm("ldi r31, 0x80");
        asm("ldi r27, 0x00");
        asm("out 0x3c, r27");
        asm("eijmp");
    #elif defined(__AVR_ATmega32U2__)
        cli();
        void (*bl_funcptr)( void ) = (void (*)(void)) (0x7000/2); // Set up function pointer to bootloader start address
        EIND = 0x00;
        bl_funcptr(); // Jump to bootloader
    #elif defined(__AVR_AT90USB1287__)
        // Bootloader address is set by fuses: BOOTSZ0 and BOOTSZ1. Define BOOTLOADER_ADDRESS (Byte address!) in makefile
        #if !defined(BOOTLOADER_ADDRESS)
          #error "define BOOTLOADER_ADDRESS"
        #endif
        cli();
        void (*bl_funcptr)( void ) = (void (*)(void)) (BOOTLOADER_ADDRESS/2); // Set up function pointer to bootloader start address
        bl_funcptr(); // Jump to bootloader
    #elif defined(__AVR_ATxmega128A4U__) 
        cli();
        asm("ldi r30, 0x00");
        asm("ldi r31, 0x00");
        asm("ldi r27, 0x01");
        asm("out 0x3c, r27");
        asm("eijmp");
    #elif defined(__AVR_ATmega128__) 
        #warning Implement 
    #else 
        #error "EnterBootloader not implemented for this target"
    #endif 
    // This to avoid a warn about function returning although declared 'noreturn'. If compiled with Os it has ny size penalty 
    for (;;) {} // endfor


}



//---- XMEGA Support Functions ----//

#if defined(XMEGA)

unsigned char SP_ReadCalibrationByte( unsigned char index)
{
	unsigned char result;
	// Load the NVM Command register to read the calibration row.
	NVM_CMD = NVM_CMD_READ_CALIB_ROW_gc;
 	result = pgm_read_byte(index);
	// Clean up NVM Command register.
 	NVM_CMD = NVM_CMD_NO_OPERATION_gc;
	return result;
}

void xmega_get_serial(unsigned char* pSerial, unsigned char Len)
{
    while (Len > 11) {
        *pSerial++ = 0;
        Len--;
    } // endwhile
    if (Len) { *pSerial++ = SP_ReadCalibrationByte( offsetof( NVM_PROD_SIGNATURES_t, COORDY1 ) );  Len--;  } // endif
    if (Len) { *pSerial++ = SP_ReadCalibrationByte( offsetof( NVM_PROD_SIGNATURES_t, COORDY0 ) );  Len--;  } // endif
    if (Len) { *pSerial++ = SP_ReadCalibrationByte( offsetof( NVM_PROD_SIGNATURES_t, COORDX1 ) );  Len--;  } // endif
    if (Len) { *pSerial++ = SP_ReadCalibrationByte( offsetof( NVM_PROD_SIGNATURES_t, COORDX0 ) );  Len--;  } // endif
    if (Len) { *pSerial++ = SP_ReadCalibrationByte( offsetof( NVM_PROD_SIGNATURES_t, WAFNUM  ) );  Len--;  } // endif
    if (Len) { *pSerial++ = SP_ReadCalibrationByte( offsetof( NVM_PROD_SIGNATURES_t, LOTNUM5 ) );  Len--;  } // endif
    if (Len) { *pSerial++ = SP_ReadCalibrationByte( offsetof( NVM_PROD_SIGNATURES_t, LOTNUM4 ) );  Len--;  } // endif
    if (Len) { *pSerial++ = SP_ReadCalibrationByte( offsetof( NVM_PROD_SIGNATURES_t, LOTNUM3 ) );  Len--;  } // endif
    if (Len) { *pSerial++ = SP_ReadCalibrationByte( offsetof( NVM_PROD_SIGNATURES_t, LOTNUM2 ) );  Len--;  } // endif
    if (Len) { *pSerial++ = SP_ReadCalibrationByte( offsetof( NVM_PROD_SIGNATURES_t, LOTNUM1 ) );  Len--;  } // endif
    if (Len) { *pSerial++ = SP_ReadCalibrationByte( offsetof( NVM_PROD_SIGNATURES_t, LOTNUM0 ) );  Len--;  } // endif
}

#endif // defined(XMEGA)
