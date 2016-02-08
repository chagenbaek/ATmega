//$Id: uart.h 2.45.2.1 2014/11/25 14:52:59 jacob tnt $
//$Log: uart.h $
//Revision 2.45.2.1  2014/11/25 14:52:59  jacob
//Non blocking Puts 
//Revision 2.45  2013/05/06 10:01:10  jacob
//prefix with __vector_ to remove warn
//Revision 2.44  2013/03/19 10:01:36  jacob
//Backup
//Revision 2.43  2013/03/05 16:28:37  jacob
//Added Error detection to STM32 
//Revision 2.42  2013/03/05 11:46:01  jacob
//STM32 test branch
//Revision 2.41  2013/02/25 12:32:57  jacob
//STM32 fix
//Revision 2.40  2013/02/22 15:51:08  jacob
//STM32 fixes
//Revision 2.39  2013/02/18 17:51:25  jacob
//Added some STM32 support - tentative
//Revision 2.38  2013/01/31 07:25:27  Peter
//Only defines XMEGAUART if it exists
//Revision 2.37  2013/01/25 09:15:29  Peter
//Fixed use of avr register defines
//Revision 2.36  2013/01/24 12:17:22  Peter
//Added simple bit banging uart (only 115200)
//Tested ok on avr 8MHz (-Os and -O2)
//Revision 2.35  2013/01/10 08:26:57  Peter
//Updates in AVR and XMEGA
//Revision 2.34  2012/08/23 10:24:26  jacob
//Now uses interrupt_type from avrutils
//Revision 2.33  2011/11/10 13:24:01  Peter
//AVR: support for two speed cpu
//DataRegisterEmpty: JIC fix disabling interrupt
//Added EnableRx
//Revision 2.32  2011/11/02 11:08:47  jacob
//Simple warn fix
//Revision 2.31  2011/10/22 14:24:16  Peter
//Fix for mega32U2
//Revision 2.30  2011/09/29 09:58:14  Peter
//NIOS2 changes: Now works with fifoed avalon uart
//Revision 2.29  2011/09/19 10:31:58  Peter
//Added support for NIOS2 uart (only fixed baud).
//NIOS2 error handling not tested.
//Only tested with one instance.
//Revision 2.28  2011/06/29 12:35:50  jacob
//Added an non int driven uart specialization
//Revision 2.27  2011/02/21 09:05:28  jacob
//Removed Int2Type
//Revision 2.26  2011/01/20 10:30:45  Peter
//Added FlushRx function
//Revision 2.25  2011/01/05 08:31:41  Peter
//Now checks for BUFFER_OVERFLOW
//Revision 2.24  2010/12/21 12:00:42  Peter
//Added Puts for null terminated string
//Revision 2.23  2010/12/17 14:37:52  jacob
//Added support for last UART
//Revision 2.22  2010/10/21 12:08:39  jacob
//Fix to avoid warn
//Revision 2.21  2010/08/02 19:42:02  jacob
//Added support for USB646
//Revision 2.20  2010/08/02 18:08:21  jacob
//Merge of 2.16.1.8 into main trunk 
//Attempt to merge XMEGA and AVR into same file
//Revision 2.16.1.8  2010/07/21 07:57:02  Peter
//Added ManPutc function for manual TX not using interrupt or Tx-queue
//Revision 2.16.1.7  2010/07/09 13:57:30  jacob
//Fix so that this can be included in multple translation units
//Revision 2.16.1.6  2010/07/09 13:49:06  jacob
//Backup
//Revision 2.16.1.5  2010/07/08 12:48:31  jacob
//Attempt to support all XMEGA uarts
//Revision 2.16.1.4  2010/05/31 12:30:08  Peter
//Made m_Busy (and RxError) volatile
//Revision 2.16.1.3  2010/03/12 13:12:08  jacob
//A few fixes and enhancements
//Revision 2.16.1.2  2010/02/12 13:30:47  jacob
//Backup
//Revision 2.16.1.1  2010/02/02 18:52:10  jacob
//xmega
//Revision 2.16  2010/01/09 13:46:39  Administrator
//Now inherits from streambase
//Revision 2.15  2009/12/21 14:44:15  jacob
//Renamed error enums
//Revision 2.14  2009/12/21 12:05:18  jacob
//Moved result flags into class
//Revision 2.13  2009/12/17 17:00:04  jacob
//Renamed variable due to USB define clash
//Revision 2.12  2009/12/15 19:26:22  jacob
//Added Busy function
//Revision 2.11  2009/12/14 14:38:12  jacob
//Tentative ManReceive
//Revision 2.10  2009/12/11 10:45:05  Peter
//Interrupt vectors in constructor, not in init
//Revision 2.9  2009/12/11 08:45:36  jacob
//Added ShutDown and Init function 
//Revision 2.8  2009/12/09 13:38:10  jacob
//Getc and Putc static
//Revision 2.7  2009/12/08 11:30:20  jacob
//Fix for USB device that does not have uart 0
//Revision 2.6  2009/12/03 15:13:31  jacob
//PORTNUMBERS redefined
//Now vectors are taken from the defines 
//Revision 2.5  2009/12/03 14:09:40  jacob
//Minor fix that should help prevent include file sequence problems 
//Revision 2.4  2009/12/02 09:45:08  jacob
//Now uses simplequeue
//Revision 2.3  2009/12/02 09:21:25  jacob
//Clean up
//Revision 2.2  2009/11/25 14:08:58  jacob
//Added Error handling
//Revision 2.1  2009/11/24 13:15:35  jacob
//Now uses flush to initialize queues
//Revision 2.0  2009/11/23 14:54:27  jacob
//Template version

#ifndef __UART_H
#define __UART_H

//  Forward declarations 
template <int PORT, unsigned long BAUD, int RXSIZE, int TXSIZE, unsigned long IRQ_ID> class Uart;

#include "target.h"
#if defined(AVR)
 #include "avrutils.h"
#endif
#include "containers.h"
#include "StreamBase.h"


#if defined(XMEGA)
 #include "xmegauartcalc.h"

// Forward declaration 
template <int A, int PORT> class PortIO;        // The A parameter is to avoid having the specializations instantiated as this gives clash when this header file is 
                                                // included in multiple translation units 

template <int PORT, unsigned long BAUD> class PortTraits {

public:
    enum {RxCompleteVector          =   PortIO<0,PORT>::RxCompleteVector};
    enum {DataRegisterEmptyVector   =   PortIO<0,PORT>::DataRegisterEmptyVector};
    enum {TxCompleteVector          =   PortIO<0,PORT>::TxCompleteVector}; 
    

    #define USART_DREINTLVL        USART_DREINTLVL_MED_gc  // USART_DREINTLVL_LO_gc, USART_DREINTLVL_MED_gc, USART_DREINTLVL_HI_gc
    #define USART_TXCINTLVL        USART_TXCINTLVL_MED_gc  // USART_TXCINTLVL_LO_gc, USART_TXCINTLVL_MED_gc, USART_TXCINTLVL_HI_gc
    #define USART_RXCINTLVL        USART_RXCINTLVL_MED_gc  // USART_RXCINTLVL_LO_gc, USART_RXCINTLVL_MED_gc, USART_RXCINTLVL_HI_gc

    PortTraits() {};

    void Init(void)
    {
        // Set DEBUG_USART format, 8 Data bits, No Parity, 1 Stop bit.
        PortIO<0,PORT>::USART.CTRLC =  (USART_CHSIZE_8BIT_gc | USART_PMODE_DISABLED_gc);

        typedef XMegaUARTCalc<BAUD,XTAL_CPU> Setup;

        // Set baud rate 
    	PortIO<0,PORT>::USART.BAUDCTRLA = Setup::BSEL & 0xFF;
        PortIO<0,PORT>::USART.BAUDCTRLB = (unsigned char)(Setup::BS << USART_BSCALE0_bp) | ((Setup::BSEL >> 8) & 0xFF);
    
        // Double data rate
        PortIO<0,PORT>::USART.CTRLB |= (Setup::X2 ? USART_CLK2X_bm : 0);
    
        // Enable receive complete interrupt
    	PortIO<0,PORT>::USART.CTRLA = (PortIO<0,PORT>::USART.CTRLA & ~USART_RXCINTLVL_gm) | USART_RXCINTLVL;
    
        // Enable USART receiver and transmitter 
        PortIO<0,PORT>::USART.CTRLB |= (USART_RXEN_bm | USART_TXEN_bm);
        
        
    }

    void Tx(unsigned char data)
    {
        PortIO<0,PORT>::USART.DATA = data;
    }

    bool IsDataRegisterEmpty(void)
    {
        return (PortIO<0,PORT>::USART.STATUS & USART_DREIF_bm ? true : false);
    }

    bool RxErrors(void) {   return PortIO<0,PORT>::USART.STATUS & (USART_FERR_bm | USART_BUFOVF_bm | USART_PERR_bm);}
    bool FrameError(void) { return PortIO<0,PORT>::USART.STATUS & USART_FERR_bm;}
    bool OverRun(void) {    return PortIO<0,PORT>::USART.STATUS & USART_BUFOVF_bm;}
    bool ParityError(void) {return PortIO<0,PORT>::USART.STATUS & USART_PERR_bm;}

    unsigned char Rx(void) 
    {return PortIO<0,PORT>::USART.DATA;}

    /*
    bool RxReady(void) {

        return (UCSR0A & (1 << RXC0)) ? true : false;
    }
    */

    void EnableTxEmptyInterrupt(void) 
    {
        PortIO<0,PORT>::USART.CTRLA = (PortIO<0,PORT>::USART.CTRLA & ~USART_DREINTLVL_gm) | USART_DREINTLVL;
    }

    void DisableTxEmptyInterrupt(void) 
    {
        PortIO<0,PORT>::USART.CTRLA = (PortIO<0,PORT>::USART.CTRLA & ~USART_DREINTLVL_gm);
    }


    void EnableTxCompleteInterrupt(const int state) 
    {
        if (state) { 
            PortIO<0,PORT>::USART.CTRLA = (PortIO<0,PORT>::USART.CTRLA & ~USART_TXCINTLVL_gm) | USART_TXCINTLVL;
        } else {
            PortIO<0,PORT>::USART.CTRLA = (PortIO<0,PORT>::USART.CTRLA & ~USART_TXCINTLVL_gm);
        } // endif
    }

    void EnableRxInterrupt(const int state) 
    {
        if (state) { 
            PortIO<0,PORT>::USART.CTRLA = (PortIO<0,PORT>::USART.CTRLA & ~USART_RXCINTLVL_gm) | USART_RXCINTLVL;
        } else {
            PortIO<0,PORT>::USART.CTRLA = (PortIO<0,PORT>::USART.CTRLA & ~USART_RXCINTLVL_gm);
        } // endif
    }

    void EnableTx(const int state)
    {   
        
        if (state) { 
            PortIO<0,PORT>::USART.CTRLB |= USART_TXEN_bm;
        } else {
            PortIO<0,PORT>::USART.CTRLB &= ~USART_TXEN_bm;
        } // endif
    }

    void EnableRx(const int state)
    {   
        if (state) { 
            PortIO<0,PORT>::USART.CTRLB |= USART_RXEN_bm;
        } else {
            PortIO<0,PORT>::USART.CTRLB &= ~USART_RXEN_bm;
        } // endif
    }

};

#elif defined(AVR)

template <int PORT, unsigned long BAUD> class PortTraits;

#if !defined(__AVR_AT90USB1287__) && \
    !defined(__AVR_AT90USB646__) &&  \
    !defined(__AVR_ATmega32U2__)     

// Partial specialization for port 0
template <unsigned long BAUD> class PortTraits<0,BAUD> {
public:

    // These must be rounded to nearest integer. Done by adding 0.5 then floor  
    enum {TEST_UBRR0 = ((2*XTAL_CPU/(16*BAUD))-1)/2};          // No   X2
    enum {TEST_UBRR1 = ((2*XTAL_CPU/( 8*BAUD))-1)/2};          // With X2

    #if defined (XTAL_CPU_PRESCALED) // We have a second freq
    enum {TEST_UBRR0_PRESCALED = ((2*XTAL_CPU_PRESCALED/(16*BAUD))-1)/2};          // No   X2
    enum {TEST_UBRR1_PRESCALED = ((2*XTAL_CPU_PRESCALED/( 8*BAUD))-1)/2};          // With X2
    #endif

    /* 
    Note on above calculus : 
    Real formula is  
       (XTAL_CPU/(16*BAUD))-1
        Now add 0.5
        = (XTAL_CPU/(16*BAUD))-0.5
        Now multiply and divide with 2 to keep computation in ints
        = (2*(XTAL_CPU/(16*BAUD))-1)/2
    */ 

    enum {ERR_BAUD0 = (BAUD - XTAL_CPU/(16*(TEST_UBRR0+1)))};
    enum {ERR_BAUD1 = (BAUD - XTAL_CPU/(8*(TEST_UBRR1+1)))};

    #if defined (XTAL_CPU_PRESCALED) // We have a second freq
    enum {ERR_BAUD0_PRESCALED = (BAUD - XTAL_CPU_PRESCALED/(16*(TEST_UBRR0_PRESCALED+1)))};
    enum {ERR_BAUD1_PRESCALED = (BAUD - XTAL_CPU_PRESCALED/(8*(TEST_UBRR1_PRESCALED+1)))};
    #endif


    #undef _VECTOR
    #define _VECTOR(x) x
    enum {RxCompleteVector          =   USART0_RX_vect};
    enum {DataRegisterEmptyVector   =   USART0_UDRE_vect};
    enum {TxCompleteVector          =   USART0_TX_vect};
    #undef _VECTOR
    #define _VECTOR(N) __vector_ ## N

    PortTraits() {};

    void LocalX2(Int2Type<0>)
    {
        #if defined (XTAL_CPU_PRESCALED) // We have a second freq
            if ((XTAL_CPU/XTAL_CPU_PRESCALED) == XTAL_CPU_PRESCALER_VALUE) {
                UBRR0H = (unsigned char)(TEST_UBRR0_PRESCALED>>8);
                UBRR0L = (unsigned char) TEST_UBRR0_PRESCALED;
            } else {
                UBRR0H = (unsigned char)(TEST_UBRR0>>8);
                UBRR0L = (unsigned char) TEST_UBRR0;
            } // endif
        #else
            UBRR0H = (unsigned char)(TEST_UBRR0>>8);
            UBRR0L = (unsigned char) TEST_UBRR0;
        #endif
    }

    void LocalX2(Int2Type<1>)
    {
        #if defined (XTAL_CPU_PRESCALED) // We have a second freq
            if ((XTAL_CPU/XTAL_CPU_PRESCALED) == XTAL_CPU_PRESCALER_VALUE) {
                UBRR0H = (unsigned char)(TEST_UBRR1_PRESCALED>>8);
                UBRR0L = (unsigned char) TEST_UBRR1_PRESCALED;
            } else {
                UBRR0H = (unsigned char)(TEST_UBRR1>>8);
                UBRR0L = (unsigned char) TEST_UBRR1;
            } // endif
        #else
            UBRR0H = (unsigned char)(TEST_UBRR1>>8);
            UBRR0L = (unsigned char) TEST_UBRR1;
        #endif

        UCSR0A |= (1 << U2X0);    // Double data rate
    }

    void Init(void)
    {
        // Init UART 

        #if defined (XTAL_CPU_PRESCALED) // We have a second freq
            if ((XTAL_CPU/XTAL_CPU_PRESCALED) == XTAL_CPU_PRESCALER_VALUE) {
                 LocalX2(Int2Type<(((unsigned long)ERR_BAUD1_PRESCALED*(unsigned long)ERR_BAUD1_PRESCALED) < ((unsigned long)ERR_BAUD0_PRESCALED*(unsigned long)ERR_BAUD0_PRESCALED)) ? 1 : 0 >());
            } else {
                 LocalX2(Int2Type<(((unsigned long)ERR_BAUD1*(unsigned long)ERR_BAUD1) < ((unsigned long)ERR_BAUD0*(unsigned long)ERR_BAUD0)) ? 1 : 0 >());
            } // endif
        #else
            LocalX2(Int2Type<(((unsigned long)ERR_BAUD1*(unsigned long)ERR_BAUD1) < ((unsigned long)ERR_BAUD0*(unsigned long)ERR_BAUD0)) ? 1 : 0 >());
        #endif

        // Set frame format: asynchronous, 8data, no parity, 1stop bit
        UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);

    }


    void Tx(unsigned char data)
    {
        UDR0 = data;
    }

    bool RxErrors(void) {return UCSR0A & (1 << UPE0 | 1 << FE0 | 1 << DOR0);}
    bool FrameError(void) {return UCSR0A & (1 << FE0);}
    bool OverRun(void) {return UCSR0A & (1 << DOR0);}
    bool ParityError(void) {return UCSR0A & (1 << UPE0);
    }

    unsigned char Rx(void) 
    {return UDR0;}

    bool RxReady(void) {

        return (UCSR0A & (1 << RXC0)) ? true : false;
    }

    void EnableTxEmptyInterrupt(void) 
    {
        UCSR0B   |= (1<< UDRIE0);
    }

    void DisableTxEmptyInterrupt(void) 
    {
        UCSR0B   &= ~(1<< UDRIE0);
    }


    void EnableTxCompleteInterrupt(const int state) 
    {
        if (state) { 
            UCSR0B   |=  (1<< TXCIE0);
        } else {
            UCSR0B   &= ~(1<< TXCIE0);
        } // endif
    }

    void EnableRxInterrupt(const int state) 
    {
        if (state) { 
            UCSR0B   |= (1<< RXCIE0);
        } else {
            UCSR0B   &= ~(1<< RXCIE0);
        } // endif
    }

    void EnableTx(const int state)
    {   
        if (state) { 
            UCSR0B |= (1<<TXEN0);
        } else {
            UCSR0B &= ~(1<<TXEN0);
        } // endif
    }

    void EnableRx(const int state)
    {   
        if (state) { 
            UCSR0B |= (1<<RXEN0);
        } else {
            UCSR0B &= ~(1<<RXEN0);
        } // endif
    }

};

#endif // End of supported AVR devices 


// Partial specialization for port 1
template <unsigned long BAUD> class PortTraits<1,BAUD> {
public:
    #undef _VECTOR
    #define _VECTOR(x) x
    enum {RxCompleteVector          =   USART1_RX_vect};
    enum {DataRegisterEmptyVector   =   USART1_UDRE_vect};
    enum {TxCompleteVector          =   USART1_TX_vect};
    #undef _VECTOR
    #define _VECTOR(N) __vector_ ## N
    
    // These must be rounded to nearest integer. Done by adding 0.5 then floor  
    enum {TEST_UBRR0 = ((2*XTAL_CPU/(16*BAUD))-1)/2};          // No   X2
    enum {TEST_UBRR1 = ((2*XTAL_CPU/( 8*BAUD))-1)/2};          // With X2

    #if defined (XTAL_CPU_PRESCALED) // We have a second freq
    enum {TEST_UBRR0_PRESCALED = ((2*XTAL_CPU_PRESCALED/(16*BAUD))-1)/2};          // No   X2
    enum {TEST_UBRR1_PRESCALED = ((2*XTAL_CPU_PRESCALED/( 8*BAUD))-1)/2};          // With X2
    #endif

    /* 
    Note on above calculus : 
    Real formula is  
       (XTAL_CPU/(16*BAUD))-1
        Now add 0.5
        = (XTAL_CPU/(16*BAUD))-0.5
        Now multiply and divide with 2 to keep computation in ints
        = (2*(XTAL_CPU/(16*BAUD))-1)/2
    */ 

    enum {ERR_BAUD0 = (BAUD - XTAL_CPU/(16*(TEST_UBRR0+1)))};
    enum {ERR_BAUD1 = (BAUD - XTAL_CPU/(8*(TEST_UBRR1+1)))};

    #if defined (XTAL_CPU_PRESCALED) // We have a second freq
    enum {ERR_BAUD0_PRESCALED = (BAUD - XTAL_CPU_PRESCALED/(16*(TEST_UBRR0_PRESCALED+1)))};
    enum {ERR_BAUD1_PRESCALED = (BAUD - XTAL_CPU_PRESCALED/(8*(TEST_UBRR1_PRESCALED+1)))};
    #endif


    PortTraits() {};

    void LocalX2(Int2Type<0>)
    {
        #if defined (XTAL_CPU_PRESCALED) // We have a second freq
            if ((XTAL_CPU/XTAL_CPU_PRESCALED) == XTAL_CPU_PRESCALER_VALUE) {
                UBRR1H = (unsigned char)(TEST_UBRR0_PRESCALED>>8);
                UBRR1L = (unsigned char) TEST_UBRR0_PRESCALED;
            } else {
                UBRR1H = (unsigned char)(TEST_UBRR0>>8);
                UBRR1L = (unsigned char) TEST_UBRR0;
            } // endif
        #else
            UBRR1H = (unsigned char)(TEST_UBRR0>>8);
            UBRR1L = (unsigned char) TEST_UBRR0;
        #endif
    }

    void LocalX2(Int2Type<1>)
    {
        #if defined (XTAL_CPU_PRESCALED) // We have a second freq
            if ((XTAL_CPU/XTAL_CPU_PRESCALED) == XTAL_CPU_PRESCALER_VALUE) {
                UBRR1H = (unsigned char)(TEST_UBRR1_PRESCALED>>8);
                UBRR1L = (unsigned char) TEST_UBRR1_PRESCALED;
            } else {
                UBRR1H = (unsigned char)(TEST_UBRR1>>8);
                UBRR1L = (unsigned char) TEST_UBRR1;
            } // endif
        #else
            UBRR1H = (unsigned char)(TEST_UBRR1>>8);
            UBRR1L = (unsigned char) TEST_UBRR1;
        #endif

        UCSR1A |= (1 << U2X1);    // Double data rate
    }

    void Init(void)
    {
        // Init UART 

        #if defined (XTAL_CPU_PRESCALED) // We have a second freq
            if ((XTAL_CPU/XTAL_CPU_PRESCALED) == XTAL_CPU_PRESCALER_VALUE) {
                 LocalX2(Int2Type<(((unsigned long)ERR_BAUD1_PRESCALED*(unsigned long)ERR_BAUD1_PRESCALED) < ((unsigned long)ERR_BAUD0_PRESCALED*(unsigned long)ERR_BAUD0_PRESCALED)) ? 1 : 0 >());
            } else {
                 LocalX2(Int2Type<(((unsigned long)ERR_BAUD1*(unsigned long)ERR_BAUD1) < ((unsigned long)ERR_BAUD0*(unsigned long)ERR_BAUD0)) ? 1 : 0 >());
            } // endif
        #else
            LocalX2(Int2Type<(((unsigned long)ERR_BAUD1*(unsigned long)ERR_BAUD1) < ((unsigned long)ERR_BAUD0*(unsigned long)ERR_BAUD0)) ? 1 : 0 >());
        #endif

        // Set frame format: asynchronous, 8data, no parity, 1stop bit
        UCSR1C = (1<<UCSZ11) | (1<<UCSZ10);
    }

    void Tx(unsigned char indata)
    {
        UDR1 = indata;
    }

    bool RxErrors(void) {return UCSR1A & (1 << UPE1 | 1 << FE1 | 1 << DOR1);}
    bool FrameError(void) {return UCSR1A & (1 << FE1);}
    bool OverRun(void) {return UCSR1A & (1 << DOR1);}
    bool ParityError(void) {return UCSR1A & (1 << UPE1);}

    unsigned char Rx(void) 
    {return UDR1;}

    bool RxReady(void) {

        return (UCSR1A & (1 << RXC1)) ? true : false;
    }


    void EnableTxEmptyInterrupt(void) 
    {
        UCSR1B   |= (1<< UDRIE1);
    }

    void DisableTxEmptyInterrupt(void) 
    {
        UCSR1B   &= ~(1<< UDRIE1);
    }


    void EnableTxCompleteInterrupt(const int state) 
    {
        if (state) { 
            UCSR1B   |=  (1<< TXCIE1);
        } else {
            UCSR1B   &= ~(1<< TXCIE1);
        } // endif
    }

    void EnableRxInterrupt(const int state) 
    {
        if (state) { 
            UCSR1B   |= (1<< RXCIE1);
        } else {
            UCSR1B   &= ~(1<< RXCIE1);
        } // endif
    }

    void EnableTx(const int state)
    {   
        if (state) { 
            UCSR1B |= (1<<TXEN1);
        } else {
            UCSR1B &= ~(1<<TXEN1);
        } // endif
    }

    void EnableRx(const int state)
    {   
        if (state) { 
            UCSR1B |= (1<<RXEN1);
        } else {
            UCSR1B &= ~(1<<RXEN1);
        } // endif
    }

};


#elif defined(NIOS2)

template <unsigned long UART_BASE,unsigned long BAUD> class PortTraits {

public:

    static volatile unsigned int Errors;
    enum {UART_RXDATA  = (UART_BASE + 0*4)};
    enum {UART_TXDATA  = (UART_BASE + 1*4)};
    enum {UART_STATUS  = (UART_BASE + 2*4)};
    enum {UART_CONTROL = (UART_BASE + 3*4)};
    enum {UART_DIVISOR = (UART_BASE + 4*4)};

    PortTraits() {};

    void Init(void)
    {
        // Enable receive complete interrupt
        EnableRxInterrupt(1);
        Errors = 0;
    }

    void Tx(unsigned char data)
    {
        IOWR_32DIRECT(UART_TXDATA,0,data);
    }

    bool IsDataRegisterEmpty(void)
    {
        // Get status 
        unsigned int Status = IORD_32DIRECT(UART_STATUS,0);
        return ((Status & UART_STAT_TRDY) ? true : false);
    }

    bool RxErrors(void)    { return Errors & (UART_STAT_FE | UART_STAT_ROE | UART_STAT_PE); }
    bool FrameError(void)  { return Errors & UART_STAT_FE; }
    bool OverRun(void)     { return Errors & UART_STAT_ROE;}
    bool ParityError(void) { return Errors & UART_STAT_PE; }

    //bool BreakError(void)      { return Errors & UART_STAT_BRK; }
    //bool TxOverrunError(void)  { return Errors & UART_STAT_TOE; }

    unsigned char Rx(void) { return IORD_32DIRECT(UART_RXDATA,0); }

    void EnableTxEmptyInterrupt(void) 
    {
        RegBit32(UART_CONTROL,UART_CTRL_ITRDY,UART_CTRL_ITRDY);
    }

    void DisableTxEmptyInterrupt(void) 
    {
        RegBit32(UART_CONTROL,UART_CTRL_ITRDY,0);
    }

    void EnableTxCompleteInterrupt(const int state) 
    {
        RegBit32(UART_CONTROL,UART_CTRL_ITMT,(state ? UART_CTRL_ITMT : 0));
    }

    void EnableRxInterrupt(const int state) 
    {
        RegBit32(UART_CONTROL,UART_CTRL_IRRDY,(state ? UART_CTRL_IRRDY : 0));
    }

    void EnableTx(const int state)
    {   
        // We have no way to disable TX
    }

    void EnableRx(const int state)
    {   
        // We have no way to disable RX
    }
};

template <unsigned long UART_BASE,unsigned long BAUD> volatile unsigned int PortTraits<UART_BASE,BAUD>::Errors;

#elif defined(_STM32x_)

template <int A, int num> class STM_PortIO;

template <int A> class STM_PortIO<A,1> {
public: 
    static const int USART_BASE  = USART1_BASE;
    static const int IRQnum      = USART1_IRQn;
};

template <int A> class STM_PortIO<A,2> {
public: 
    static const int USART_BASE  = USART2_BASE;
    static const int IRQnum      = USART2_IRQn;
};

template <int A> class STM_PortIO<A,3> {
public: 
    static const int USART_BASE  = USART3_BASE;
    static const int IRQnum      = USART3_IRQn;
};




template <unsigned long PORTNUM,unsigned long BAUD> class PortTraits {

public:

    static volatile unsigned int Errors;

    PortTraits() {};

    typedef STM_PortIO<0,PORTNUM> t_PortInfo;


    void SetBaudRate(unsigned long Val)
    {

        USART_InitTypeDef USART_InitStructure;

        USART_InitStructure.USART_BaudRate = Val;
        USART_InitStructure.USART_WordLength = USART_WordLength_8b;
        USART_InitStructure.USART_StopBits = USART_StopBits_1;
        USART_InitStructure.USART_Parity = USART_Parity_No;
        USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
        USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

        // Configure USART
        USART_Init((USART_TypeDef *) t_PortInfo::USART_BASE , &USART_InitStructure);

    }


    void Init(void)
    {
        SetBaudRate(BAUD);

        // Enable the USARTy
        USART_Cmd((USART_TypeDef *) t_PortInfo::USART_BASE, ENABLE);

        NVIC_InitTypeDef NVIC_InitStructure;

        
        
        // Enable the USARTy Interrupt at highest priority 
        NVIC_InitStructure.NVIC_IRQChannel                      = t_PortInfo::IRQnum;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority           = 0;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority    = 0;
        NVIC_InitStructure.NVIC_IRQChannelCmd                   = ENABLE;
        NVIC_Init(&NVIC_InitStructure);

        // Enable receive complete interrupt
        EnableRxInterrupt(1);
        Errors = 0;
    }

    void Tx(unsigned char data)
    {
        USART_SendData((USART_TypeDef *) t_PortInfo::USART_BASE, data);
    }

    bool IsDataRegisterEmpty(void)
    {
        // Get status 
        TODO(); 
        return true;
    }



    bool RxErrors(void)    { return (Errors & (USART_FLAG_FE | USART_FLAG_ORE | USART_FLAG_PE));}
    bool FrameError(void)  { return (Errors & (USART_FLAG_FE));}
    bool OverRun(void)     { return (Errors & (USART_FLAG_ORE));}
    bool ParityError(void) { return (Errors & (USART_FLAG_PE));}

    //bool BreakError(void)      { return Errors & UART_STAT_BRK; }
    //bool TxOverrunError(void)  { return Errors & UART_STAT_TOE; }

    unsigned char Rx(void) { return USART_ReceiveData((USART_TypeDef *) t_PortInfo::USART_BASE); }

    void EnableTxEmptyInterrupt(void) 
    {
        USART_ITConfig((USART_TypeDef *) t_PortInfo::USART_BASE,USART_IT_TXE,ENABLE);
        
    }

    void DisableTxEmptyInterrupt(void) 
    {
        USART_ITConfig((USART_TypeDef *) t_PortInfo::USART_BASE,USART_IT_TXE,DISABLE);
    }

    void EnableTxCompleteInterrupt(const int state) 
    {
        USART_ITConfig((USART_TypeDef *) t_PortInfo::USART_BASE,USART_IT_TC,state ? ENABLE : DISABLE);
    }

    void EnableRxInterrupt(const int state) 
    {
        USART_ITConfig((USART_TypeDef *) t_PortInfo::USART_BASE,USART_IT_RXNE,state ? ENABLE : DISABLE);
    }

    void EnableTx(const int state)
    {   
        // We have no way to disable TX
    }

    void EnableRx(const int state)
    {   
        // We have no way to disable RX
    }
};

template <unsigned long UART_BASE,unsigned long BAUD> volatile unsigned int PortTraits<UART_BASE,BAUD>::Errors;



#endif





template <int PORT, unsigned long BAUD, int RXSIZE, int TXSIZE, unsigned long IRQ_ID = 0>
class Uart : public StreamBase
{
public:

    typedef SimpleQueue<unsigned char,RXSIZE, (QUEUE_WRAP|QUEUE_CLISTI|QUEUE_NOLOG|QUEUE_NO_INSERT_CLISTI)> RxQueueType;
    typedef SimpleQueue<unsigned char,TXSIZE, (QUEUE_WRAP|QUEUE_CLISTI|QUEUE_NOLOG)> TxQueueType;

    static  RxQueueType RxQueue;
    static  TxQueueType TxQueue;

    static volatile unsigned char RxError; 
    static volatile bool m_Busy; 

    static const unsigned short RxBufferSize = RXSIZE;
    static const unsigned short TxBufferSize = TXSIZE;

    Uart()
    {
        #if defined (AVR)
        // Bind the vectors 
        // USART, Rx Complete
        asm volatile (
                ".global __vector_%1\n\t"
                ".equ __vector_%1, %0 \n\t"
                :: "X" ((interrupt_type)(Uart<PORT,BAUD,RXSIZE,TXSIZE>::__vector_RxComplete)),"X" (PortTraits<PORT,BAUD>::RxCompleteVector)
        );

        asm volatile (
                ".global __vector_%1\n\t"
                ".equ __vector_%1, %0 \n\t"
                :: "X" ((interrupt_type)(Uart<PORT,BAUD,RXSIZE,TXSIZE>::__vector_DataRegisterEmpty)),"X" (PortTraits<PORT,BAUD>::DataRegisterEmptyVector)
        );

        asm volatile (
                ".global __vector_%1\n\t"
                ".equ __vector_%1, %0 \n\t"
                :: "X" ((interrupt_type)(Uart<PORT,BAUD,RXSIZE,TXSIZE>::__vector_TxComplete)),"X" (PortTraits<PORT,BAUD>::TxCompleteVector)
        );
        #elif defined (NIOS2)
        alt_irq_register(IRQ_ID,NULL,nios_uart_int);
        #elif defined (_STM32x_)
            asm("nop");
        #else
          #error No support
        #endif

        Init();
    }

    static void Init(void)
    {
        RxError = 0;
        m_Busy  = false;

        RxQueue.Flush();
        TxQueue.Flush();
        
        // Constructor 
        // This emits no real code - just ensures that the assemblercode that binds the int is emitted. 
        PortTraits<PORT,BAUD> Port;
        Port.Init();

        // Enable USART receiver and transmitter
        Port.EnableTx(1);
        Port.EnableRx(1);

        // Enable uart ints 
        Port.EnableRxInterrupt(1);

    }

    static void ShutDown(void)
    {
        PortTraits<PORT,BAUD> Port;

        // Disable USART receiver and transmitter
        Port.EnableTx(0);
        Port.EnableRx(0);

        // Disable uart ints 
        Port.EnableRxInterrupt(0);
        Port.DisableTxEmptyInterrupt();
        Port.EnableTxCompleteInterrupt(0);

        m_Busy  = false;

    }

    static void EnableRx(bool Enable)
    {
        PortTraits<PORT,BAUD> Port;

        Port.EnableRxInterrupt(Enable);
        Port.EnableRx(Enable);
    }


    static bool Busy(void)
    {
        return m_Busy;
    }

    FIXME(2 Untested);
    static unsigned int RxLeft(void) 
    {
        return (RxQueue.Size - RxQueue.GetCount());
    }


    #if defined (AVR)
     static void __vector_DataRegisterEmpty(void) __attribute__ ((signal))
    #elif defined (NIOS2) || defined(_STM32x_)
     static void DataRegisterEmpty(void)
    #endif
    {
        PortTraits<PORT,BAUD> Port;

        unsigned char c = 0;

        if (TxQueue.Get(c)) {
            Port.Tx(c);
            if (TxQueue.isEmpty()) {
                // Disable this interrupt
                Port.DisableTxEmptyInterrupt();

                // Enable TXComplete interrupt 
                Port.EnableTxCompleteInterrupt(1);
            } // endif 
        } else { // JIC!
            // Disable this interrupt
            Port.DisableTxEmptyInterrupt();
        } // endif
    }

    #if defined (AVR)
     static void __vector_TxComplete(void) __attribute__ ((signal))
    #elif defined (NIOS2) || defined(_STM32x_)
     static void TxComplete(void)
    #endif
    {
        PortTraits<PORT,BAUD> Port;

        // Disable TXComplete (this) interrupt 
        Port.EnableTxCompleteInterrupt(0);
        if (TxQueue.isEmpty()) {
            m_Busy = false;
        } // endif
    }

    #if defined (AVR)
     static void __vector_RxComplete(void) __attribute__ ((signal))
    #elif defined (NIOS2) || defined(_STM32x_)
     static void RxComplete(void)
    #endif
    {
        PortTraits<PORT,BAUD> Port;

        // Check for errors
        if (Port.RxErrors()) { 
            if (Port.ParityError()) RxError |= (PARITY_ERROR  >> 8);
            if (Port.OverRun())     RxError |= (OVERRUN_ERROR >> 8);
            if (Port.FrameError())  RxError |= (FRAME_ERROR   >> 8);
            FIXME(2. Test on avr if we need to clear flags in hw register);
        } // endif
        
        // Check for receive ringbuffer overflow
        if (RxQueue.isFull()) RxError |= (BUFFER_OVERFLOW >> 8);

        // This will clear error condition 
        RxQueue.Insert(Port.Rx());
    };

    #if defined (NIOS2)
    static void nios_uart_int(void* context, alt_u32 id)
    {
        PortTraits<PORT,BAUD> Port;

        bool reloop;
        do {
            reloop = false;
            unsigned int status  = IORD_32DIRECT(Port.UART_STATUS,0);
            Port.Errors = status; // Store errors
            IOWR_32DIRECT(Port.UART_STATUS,0,0); // Acknowledge int by writing 0 to status 
    
            unsigned int control = IORD_32DIRECT(Port.UART_CONTROL,0);
    
            if ( (control & UART_CTRL_IRRDY) && (status & UART_STAT_RRDY) ) {
                RxComplete();
                reloop = true;
            } // endif
            if ( (control & UART_CTRL_ITRDY) && (status & UART_STAT_TRDY) ) {
                DataRegisterEmpty();
                reloop = true;
            } // endif
            if ( (control & UART_CTRL_ITMT) && (status & UART_STAT_TMT) ) {
                TxComplete();
                reloop = true;
            } // endif
        } while (reloop);
    }

    #elif defined(_STM32x_)
    static void STM32_uart_int(void)
    {

        PortTraits<PORT,BAUD> Port;
        typedef STM_PortIO<0,PORT> t_PortInfo;

        bool reloop;
        do {
            reloop = false;

            FIXME(1a Were ignoring errors completely); 

            

            Port.Errors = ((USART_TypeDef *) t_PortInfo::USART_BASE)->SR;
            //USART_GetFlagStatus();

            if(USART_GetITStatus((USART_TypeDef *) t_PortInfo::USART_BASE, USART_IT_RXNE) != RESET) {
                RxComplete();
                reloop = true;
            } // endif

            // Transmit reg is empty 
            if(USART_GetITStatus((USART_TypeDef *) t_PortInfo::USART_BASE, USART_IT_TXE) != RESET) {
                DataRegisterEmpty();
                reloop = true;
            } // endif

            // Transmit complete 
            if(USART_GetITStatus((USART_TypeDef *) t_PortInfo::USART_BASE, USART_IT_TC) != RESET) {
                TxComplete();
                reloop = true;
            } // endif

            return;



        } while (reloop);
    };

    static void SetBaudRate(unsigned long Rate)
    {

        PortTraits<PORT,BAUD> Port;
        Port.SetBaudRate(Rate);
    };


    #endif


    static unsigned int Getc(void)
    {
        unsigned char Err = RxError;

        // Clear errors 
        RxError = 0;

        unsigned char ch;
        if (!RxQueue.Get(ch)) return NO_DATA;

        return (Err << 8) | ch;
        
    }

    static void Putc(char c)
    {
        PortTraits<PORT,BAUD> Port;

        SCOPE_CLI;
        m_Busy = true;
        TxQueue.Insert(c);
        Port.EnableTxEmptyInterrupt();
        
    }

    static void Puts(char* str)
    {
        PortTraits<PORT,BAUD> Port;

        //SCOPE_CLI;
        while (*str) {
            TxQueue.Insert(*str++);
        } // endwhile

        if (!TxQueue.isEmpty()) { 
            m_Busy = true;
            Port.EnableTxEmptyInterrupt();
        } // endif
    }


    // Manual TX - not using queue
    static void ManPutc(char c)
    {
        PortTraits<PORT,BAUD> Port;

        while (!Port.IsDataRegisterEmpty()) {
        } // endwhile

        Port.Tx(c);
    }

    static void ManReceive(void)
    {
        PortTraits<PORT,BAUD> Port;
        if (!Port.RxReady()) return; 

        // Check for errors
        if (Port.RxErrors()) { 
            if (Port.ParityError()) RxError |= (PARITY_ERROR  >> 8);
            if (Port.OverRun())     RxError |= (OVERRUN_ERROR >> 8);
            if (Port.FrameError())  RxError |= (FRAME_ERROR   >> 8);
        } // endif
        
        // This will clear error condition 
        RxQueue.Insert(Port.Rx());
    }

    static void FlushRx(void)
    {
        RxQueue.Flush();
    }

    static void TxSubmit(void)
    {
    }



};



template <int PORT, unsigned long BAUD, int RXSIZE, int TXSIZE, unsigned long IRQ_ID> SimpleQueue<unsigned char,RXSIZE, (QUEUE_WRAP|QUEUE_CLISTI|QUEUE_NOLOG|QUEUE_NO_INSERT_CLISTI)> Uart<PORT,BAUD,RXSIZE,TXSIZE,IRQ_ID>::RxQueue;
template <int PORT, unsigned long BAUD, int RXSIZE, int TXSIZE, unsigned long IRQ_ID> SimpleQueue<unsigned char,TXSIZE, (QUEUE_WRAP|QUEUE_CLISTI|QUEUE_NOLOG)> Uart<PORT,BAUD,RXSIZE,TXSIZE,IRQ_ID>::TxQueue;
template <int PORT, unsigned long BAUD, int RXSIZE, int TXSIZE, unsigned long IRQ_ID> volatile unsigned char Uart<PORT,BAUD,RXSIZE,TXSIZE,IRQ_ID>::RxError;
template <int PORT, unsigned long BAUD, int RXSIZE, int TXSIZE, unsigned long IRQ_ID> volatile bool Uart<PORT,BAUD,RXSIZE,TXSIZE,IRQ_ID>::m_Busy;

#if defined(XMEGA)

#define XMEGAUART(num,port) \
template <int A> class PortIO<A,num> {\
public: \
    static USART_t& USART;\
    enum {RxCompleteVector          = USART##port##_RXC_vect_num};\
    enum {DataRegisterEmptyVector   = USART##port##_DRE_vect_num};\
    enum {TxCompleteVector          = USART##port##_TXC_vect_num};\
};\
template <int A> USART_t& PortIO<A,num>::USART = USART##port; 


#ifdef USARTC0
XMEGAUART(0,C0);
#endif
#ifdef USARTC1
XMEGAUART(1,C1);
#endif
#ifdef USARTD0
XMEGAUART(2,D0);
#endif
#ifdef USARTD1
XMEGAUART(3,D1);
#endif
#ifdef USARTE0
XMEGAUART(4,E0);
#endif
#ifdef USARTE1
XMEGAUART(5,E1);
#endif
#ifdef USARTF0
XMEGAUART(6,F0);
#endif
#ifdef USARTF1
XMEGAUART(7,F1); 
#endif

template <unsigned long BAUD, int RXSIZE, int TXSIZE> class Uart<8,BAUD, RXSIZE, TXSIZE> : public StreamBase
{
public:

    static const unsigned short RxBufferSize = 1;
    static const unsigned short TxBufferSize = 1;

    Uart()
    {
        Init();
    }

    static void Init(void)
    {
        PortTraits<6,BAUD> Port;
        Port.Init();

        // Enable USART receiver and transmitter
        Port.EnableTx(1);
    }

    static void ShutDown(void)
    {
        PortTraits<6,BAUD> Port;
        // Disable USART receiver and transmitter
        Port.EnableTx(0);
        Port.EnableRx(0);

        // Disable uart ints 
        Port.EnableRxInterrupt(0);
        Port.DisableTxEmptyInterrupt();
        Port.EnableTxCompleteInterrupt(0);
    }

    static void DeInit(void)
    {
        ShutDown();
    }

    static bool Busy(void)
    {
        return false;
    }

    static unsigned int RxLeft(void) 
    {
        return 0;
    }

    static unsigned int Getc(void)
    {
        return NO_DATA;
    }

    static void Putc(char c)
    {
        PortTraits<6,BAUD> Port;

        while (!Port.IsDataRegisterEmpty()) {
        } // endwhile
        
        Port.Tx(c);
        
    }

    static void Puts(char* str)
    {
        while (*str) {
            Putc(*str++);
        } // endwhile
    }


    // Manual TX - not using queue
    static void ManPutc(char c)
    {
    }

    static void ManReceive(void)
    {
    }

    static void FlushRx(void)
    {
    }

    static void TxSubmit(void)
    {
    }

    


};


#endif 




#if (F_CPU==8000000UL)
  #define UART_BITBANG_DELAY { for(unsigned char i=0;i<12;i++) {asm("nop");}  asm("nop"); }
#else
  FIXME(Delay for other F_CPU);
  #define UART_BITBANG_DELAY {asm("nop");}
#endif

template <typename Pindef>
class UartBitBang_115200 : public StreamBase
{
public:

    static const unsigned short RxBufferSize = 1;
    static const unsigned short TxBufferSize = 1;

    UartBitBang_115200()
    {
        Init();
    }

    static void Init(void)
    {
        Pindef::Init();
        Pindef::Set();
    }

    static void Putc(char c)
    {
        {
            SCOPE_CLI;

            Pindef::Clr(); // Start bit, always low
            UART_BITBANG_DELAY
            if (0x01 & c) { asm("nop"); asm("nop"); Pindef::Set(); asm("nop"); asm("nop");} else { Pindef::Clr();}
            UART_BITBANG_DELAY
            if (0x02 & c) { asm("nop"); asm("nop"); Pindef::Set(); asm("nop"); asm("nop");} else { Pindef::Clr(); }
            UART_BITBANG_DELAY
            if (0x04 & c) { asm("nop"); asm("nop"); Pindef::Set(); asm("nop"); asm("nop");} else { Pindef::Clr(); }
            UART_BITBANG_DELAY
            if (0x08 & c) { asm("nop"); asm("nop"); Pindef::Set(); asm("nop"); asm("nop");} else { Pindef::Clr(); }
            UART_BITBANG_DELAY
            if (0x10 & c) { asm("nop"); asm("nop"); Pindef::Set(); asm("nop"); asm("nop");} else { Pindef::Clr(); }
            UART_BITBANG_DELAY
            if (0x20 & c) { asm("nop"); asm("nop"); Pindef::Set(); asm("nop"); asm("nop");} else { Pindef::Clr(); }
            UART_BITBANG_DELAY
            if (0x40 & c) { asm("nop"); asm("nop"); Pindef::Set(); asm("nop"); asm("nop");} else { Pindef::Clr(); }
            UART_BITBANG_DELAY
            if (0x80 & c) { asm("nop"); asm("nop"); Pindef::Set(); asm("nop"); asm("nop");} else { Pindef::Clr(); }
            UART_BITBANG_DELAY
            asm("nop"); asm("nop");
            Pindef::Set(); // Stop bit, always high
            asm("nop"); asm("nop");

        } // End SCOPE_CLI

        UART_BITBANG_DELAY
    }

    static void Puts(char* str)
    {
        while (*str) {
            Putc(*str++);
        } // endwhile
    }

    static void ShutDown(void);
    static void DeInit(void);
    static bool Busy(void);
    static unsigned int RxLeft(void);
    static unsigned int Getc(void);
    static void ManPutc(char c);
    static void ManReceive(void);
    static void FlushRx(void);
    static void TxSubmit(void);
};




#endif

