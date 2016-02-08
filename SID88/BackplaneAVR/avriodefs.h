//$Id: avriodefs.h 1.38 2013/12/12 10:34:25 jacob tnt $
//$Log: avriodefs.h $
//Revision 1.38  2013/12/12 10:34:25  jacob
//Fixme cleanup
//Revision 1.37  2013/12/10 14:11:03  jacob
//STM32 Now sets value before setting dir at boot
//Revision 1.36  2013/12/02 20:02:37  Peter
//STM32 Change in pin io functions
//Revision 1.35  2013/11/07 11:59:02  jacob
//Minor AVR fix
//Revision 1.34  2013/10/17 10:11:21  jacob
//mainly STM32 related 
//Checkin 1.33.1.4 as main trunk 
//Revision 1.33.1.4  2013/10/09 20:56:32  jacob
//Added function to get port name - not perfect
//Revision 1.33.1.3  2013/09/25 21:02:52  jacob
//Added SetPerif for STM32
//Revision 1.33.1.2  2013/09/20 13:30:02  jacob
//Fix of problem with dummy port
//Revision 1.33.1.1  2013/09/18 12:57:20  jacob
//STM test branch
//Revision 1.36  2013/09/12 14:11:31  jacob
//More STM32
//Revision 1.35  2013/09/11 07:41:29  jacob
//Added forced inlines
//Revision 1.34  2013/09/10 10:31:06  jacob
//Added STM32 support - still tentative 
//Revision 1.33  2013/05/06 10:22:52  jacob
//Added inverted IO support and fixed bummers on LimitSlewRate
//Revision 1.32  2013/01/31 07:30:39  Peter
//Only defines MAPTOPORT if port exists
//Added port R
//Changed virtual port set/clr form asm to C to make it compile under Atmel toolchain, the compiler should figure out to make a sbi/cbi
//Revision 1.31  2011/01/19 13:49:05  Peter
//Added ioextender pins init (MAX 32 pins)
//Revision 1.30  2011/01/19 11:10:32  Peter
//IOEXTENDER now takes a SpiMaster af parameter.
//ex.:
//typedef SpiMaster<SCSPI::E,0,2000000UL>  t_GlobalSpi;
//IOEXTENDER(0,t_GlobalSpi,IOEXT_SS_PIN,2);
//Revision 1.29  2011/01/04 14:12:07  jacob
//Added a FIXME
//Revision 1.28  2010/12/22 22:07:10  Peter
//Added support for pull_up/down
//Fixed major bummer in extender
//Revision 1.27  2010/12/22 20:07:23  Peter
//Fix of IOextender 
//Revision 1.26  2010/12/22 17:35:23  jacob
//Revision 1.25  2010/12/22 17:06:00  jacob
//Major cleanup 
//Added IOEXTENDER support
//Revision 1.24  2010/12/22 14:53:15  jacob
//Revision 1.23  2010/12/22 14:28:08  jacob
//Revision 1.22  2010/12/22 13:43:40  jacob
//Version with all features TEST
//Revision 1.21  2010/12/22 12:24:35  jacob
//Another fix TENTATIVE
//Revision 1.20  2010/12/22 11:49:58  jacob
//Tentative new io definition scheme
//Revision 1.19  2010/12/21 09:51:49  jacob
//Cleaned up version
//Revision 1.18  2010/09/05 15:24:38  Jacob
//Added a LimitSlewRate define
//Revision 1.17  2010/03/31 06:58:13  Peter
//Added xmega PullDown
//Revision 1.16  2010/03/16 14:16:00  Peter
//Xmega IsPinInSet, IsPinInClr, IsPinOutSet, IsPinOutClr
//Not tested!
//Revision 1.15  2010/03/10 11:45:23  Peter
//EnablePullUp DisablePullUp for Xmega added
//Revision 1.14.1.1  2010/03/10 11:14:15  jacob
//Revision 1.14  2010/03/10 10:43:02  Peter
//Xmega TEST EnablePullUp DisablePullUp
//Revision 1.13  2010/02/12 12:16:55  jacob
//Added tentative XMEGA support
//Revision 1.12  2010/01/11 12:41:31  jacob
//Removed FIXME
//Revision 1.11  2009/12/08 11:52:50  jacob
//Added MKS header

#ifndef __AVRIODEFS_H_
#define __AVRIODEFS_H_

#if !defined(WIN32)

#if defined(AVR)
 #include "avrutils.h"


#if defined(XMEGA)
 typedef PORT_t SCIO_PortType;
#endif 


#elif defined(_STM32x_)
 #include "STMutils.h"          // Needed for SCOPE_CLI

    #ifndef FIXME 
     #define FIXME(...) 
    #endif 

    #ifndef TODO
     #define TODO(...) 
    #endif 

  typedef GPIO_TypeDef SCIO_PortType;

#else 
 #error "Ups";
#endif 

void IOregClr(unsigned char bit);
void IOregSet(unsigned char bit);

extern void CannotSetBitDirectionInExtendedRegister(void);
#define IOREGBUG CannotSetBitDirectionInExtendedRegister()

#if !defined(XMEGA) && !defined(_STM32x_)

#define X__SFR_OFFSET 0x0



#define SetBit(bit)         if (!(bit & (1 << 4))) { \
                                        *((volatile uint8_t *)((unsigned char)(bit >> 24) + X__SFR_OFFSET)) |=  (1 << (bit & 0x0007));\
                                    } else { \
                                        IOregSet(bit & 0x000F);\
                                    };

#define ClrBit(bit)         if (!(bit & (1 << 4))) { \
                                        *((volatile uint8_t *)((unsigned char)(bit >> 24) + X__SFR_OFFSET)) &= ~(1 << (bit & 0x0007));\
                                    } else { \
                                        IOregClr(bit & 0x000F);\
                                    };

#define IsPinSet(bit)       (*((volatile uint8_t *)((unsigned char)(bit >> 8) + X__SFR_OFFSET)) & (1 << (bit & 0x00FF)))
#define IsPinClr(bit)       (!IsPinSet(bit))

#define SetBitDirIn(bit)    if (!(bit & (1 << 4))) { \
                                        *((volatile uint8_t *)((unsigned char)(bit >> 16) + X__SFR_OFFSET)) &= ~(1 << (bit & 0x0007));\
                                    } else { \
                                        IOREGBUG;\
                                    };

#define SetBitDirOut(bit)    if (!(bit & (1 << 4))) { \
                                        *((volatile uint8_t *)((unsigned char)(bit >> 16) + X__SFR_OFFSET)) |=  (1 << (bit & 0x0007));\
                                    } else { \
                                        IOREGBUG;\
                                    };


#define EnablePullUp(bit)       SetBit(bit)
#define DisablePullUp(bit)      ClrBit(bit)


//#define SetBitDirOut(bit)   *((volatile uint8_t *)((unsigned char)(bit >> 16) + X__SFR_OFFSET)) |=  (1 << (bit & 0x00FF))

#define ADDR(x)         (unsigned int)(&(x) - X__SFR_OFFSET)
#define PORTDEF(x)      ((unsigned long)((unsigned long)(ADDR(PORT##x)) << 24 | (unsigned long)(ADDR(DDR##x)) << 16 | (unsigned long)(ADDR(PIN##x)) << 8))
#define IOREG(x)        (unsigned long)((1 << 4) | x)
#define BITNUM(x)       (x & 0xFF)


#else 


#if defined(_STM32x_)
typedef struct {} VPORT_t;
static const VPORT_t VPORT0 = {};

/*
static const SCIO_PortType *abe = 0;
static const SCIO_PortType  &DUMMYPORT = *abe; 
*/ 



#endif 

#if defined(XMEGA)
TODO(Ensure we call no more than 0..3 VPORTS)
#endif 

namespace SCIO
{
   typedef enum {
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        J,
        K,
        L,
        M,
        N,
        Q,
        R
   } t_ioports;

   
   typedef enum {
        VIRTUAL,
        NORMAL,
        EXTENDER
   } t_ioaccess;
   

   typedef enum {
       VIRT0,
       VIRT1,
       VIRT2,
       VIRT3
   } t_virtportnumber;

   TODO(1 Create a BIDIR type - This way we can check illigal actions. For instance SetBit on an input etc);
   typedef enum {
       OUTPUT,
       INPUT,
       INPUT_PULLUP,
       INPUT_PULLDOWN, 
       INPUT_ANALOG, 
       PERIF
   } t_iotype;


};

#if !defined(_STM32x_)

// This template provides access to the right virtual port config register 
template <SCIO::t_virtportnumber N> struct SetUpVirtualPort;
template <> struct SetUpVirtualPort<SCIO::VIRT0>
{
        void inline Init(unsigned char val) {PORTCFG.VPCTRLA = ((PORTCFG.VPCTRLA & 0xF0) | (val<<0));};
        static VPORT_t& VPort(void) {return VPORT0;};
};

template <> struct SetUpVirtualPort<SCIO::VIRT1>
{
        void inline Init(unsigned char val) {PORTCFG.VPCTRLA = ((PORTCFG.VPCTRLA & 0x0F) | (val<<4));};
        static VPORT_t& VPort(void) {return VPORT1;};
};

template <> struct SetUpVirtualPort<SCIO::VIRT2>
{
        void inline Init(unsigned char val) {PORTCFG.VPCTRLB = ((PORTCFG.VPCTRLB & 0xF0) | (val<<0));};
        static VPORT_t& VPort(void) {return VPORT2;};
};

template <> struct SetUpVirtualPort<SCIO::VIRT3>
{
        void inline Init(unsigned char val) {PORTCFG.VPCTRLB = ((PORTCFG.VPCTRLB & 0x0F) | (val<<4));};
        static VPORT_t& VPort(void) {return VPORT3;};
};


// This provides the right value to put into the virtual port setup register 
template <SCIO::t_ioports N> struct VirtualPortSetupValue;


#ifdef XMEGA_A4U
    // PORTCFG_VP0MAP_PORTx_gc AND PORTCFG_VP2MAP_PORTz_gc is combined into PORTCFG_VP02MAP_PORTx_gc
    #define VIRTUALPORTSETUPVALUE(PORT) \
            template<> struct VirtualPortSetupValue<SCIO:: PORT> {enum {Result = PORTCFG_VP02MAP_PORT##PORT##_gc};};
#else
    #define VIRTUALPORTSETUPVALUE(PORT) \
            template<> struct VirtualPortSetupValue<SCIO:: PORT> {enum {Result = PORTCFG_VP0MAP_PORT##PORT##_gc};};
#endif

VIRTUALPORTSETUPVALUE(A);
VIRTUALPORTSETUPVALUE(B);
VIRTUALPORTSETUPVALUE(C);
VIRTUALPORTSETUPVALUE(D);
VIRTUALPORTSETUPVALUE(E);
VIRTUALPORTSETUPVALUE(F);
VIRTUALPORTSETUPVALUE(G);
VIRTUALPORTSETUPVALUE(H);
VIRTUALPORTSETUPVALUE(J);
VIRTUALPORTSETUPVALUE(K);
VIRTUALPORTSETUPVALUE(L);
VIRTUALPORTSETUPVALUE(M);
VIRTUALPORTSETUPVALUE(N);
VIRTUALPORTSETUPVALUE(Q);

#endif 


#if defined(XMEGA)

template <SCIO::t_ioports> static const SCIO_PortType& MapToPort(void);
#define MAPTOPORT(P) \
    template<> const SCIO_PortType& MapToPort<SCIO:: P>(void) {return PORT##P;};\

#if defined(PORTA) 
MAPTOPORT(A); 
#endif
#if defined(PORTB) 
MAPTOPORT(B);
#endif
#if defined(PORTC) 
MAPTOPORT(C);
#endif
#if defined(PORTD) 
MAPTOPORT(D);
#endif
#if defined(PORTE) 
MAPTOPORT(E);
#endif
#if defined(PORTF) 
MAPTOPORT(F);
#endif
#if defined(PORTG) 
MAPTOPORT(G);
#endif 
#if defined(PORTH) 
MAPTOPORT(H);
#endif 
#if defined(PORTJ) 
MAPTOPORT(J);
#endif 
#if defined(PORTK) 
MAPTOPORT(K);
#endif 
//MAPTOPORT(L);
//MAPTOPORT(M);
//MAPTOPORT(N);
#if defined(PORTQ) 
MAPTOPORT(Q);
#endif 
#if defined(PORTR) 
MAPTOPORT(R);
#endif 

#elif defined(_STM32x_)

template <SCIO::t_ioports> static const SCIO_PortType& MapToPort(void);
template <SCIO::t_ioports> static const char * PortName(void);
#define MAPTOPORT(P) \
    template<> const SCIO_PortType& MapToPort<SCIO:: P>(void) {return *GPIO##P;};\
    template<> const char *PortName<SCIO:: P>(void) {return "GPIO"#P;};\
    

#if defined(GPIOA) 
MAPTOPORT(A); 
#endif
#if defined(GPIOB) 
MAPTOPORT(B);
#endif
#if defined(GPIOC) 
MAPTOPORT(C);
#endif
#if defined(GPIOD) 
MAPTOPORT(D);
#endif
#if defined(GPIOE) 
MAPTOPORT(E);
#endif
#if defined(PORTF) 
MAPTOPORT(F);
#endif
#if defined(GPIOG) 
MAPTOPORT(G);
#endif 


/*
template <SCIO::t_ioports> class MapToPortII;

#define MAPTOPORTII(P) \
    template<> class MapToPortII<SCIO:: P> {const SCIO_PortType &Port = GPIO##P;};

#if defined(GPIOA) 
MAPTOPORTII(A); 
#endif 
*/ 


#endif 


#if !defined(_STM32x_)
template <SCIO::t_ioports N, SCIO::t_virtportnumber VP> struct HSPORT
{
    static void inline Init(void)
    {
        SetUpVirtualPort<VP> Setup;
        Setup.Init(VirtualPortSetupValue<N>::Result);
    };

    static const SCIO::t_ioaccess PortType = SCIO::VIRTUAL;

    static inline SCIO_PortType& PortR(void)
    {
        return (SCIO_PortType&) MapToPort<N>();
    };

    static VPORT_t& VPort(void)
    {
        SetUpVirtualPort<VP> Setup;
        return Setup.VPort();
    };
};

#endif 

//template <SCIO::t_ioports N> struct NormalPortSetupValue;

template <SCIO::t_ioports N, SCIO::t_virtportnumber VP> struct NORMALPORT
{
    static void inline Init(void) {};

    static const SCIO::t_ioaccess PortType = SCIO::NORMAL;

    //typedef int IOPIN;

    static inline SCIO_PortType& PortR(void)
    {
        return (SCIO_PortType&) MapToPort<N>();
    };

    static inline const char * Name(void)
    {
        return PortName<N>();
    };

    //static const SCIO_PortType& Reg = MapToPort<N>();

    #if !defined(_STM32x_)
    static VPORT_t& VPort(void)
    {
        asm("bug");
        return VPORT0;
    }
    #endif 
};

template <typename SPIMASTER, typename CSPIN, unsigned int LEN> struct IOEXTENDERPORT
{
    static const unsigned char chainlenght = LEN;

    // Holds the values loaded into the register 
    static unsigned char Val[LEN];

    static void inline Init(void) 
    {
        FIXME(1 Could we pick up initial values from the PinDef ? );
        FIXME(2 Detect if SS is an input ? );
        for (unsigned int i=0;i<LEN;i++) { 
            Val[i] = 0;
        } // endfor

        SPIMASTER::Init();
    };

    static void Update(void)
    {
        FIXME(1 Blocking ?);
        SCOPE_CLI;
        CSPIN::clr();
        unsigned char i = (LEN-1);
        do {
            SPIMASTER::DataWrite(Val[i]);
            // Wait for transmission complete.
            while(!(SPIMASTER::TransferComplete())) {
            } // endwhile 
        } while (i-- != 0);
        CSPIN::set();
    };

    static const SCIO::t_ioaccess PortType = SCIO::EXTENDER;

    #if !defined(_STM32x_)
    static VPORT_t& VPort(void)
    {
        asm("bug");
        return VPORT0;
    };

    static inline SCIO_PortType& PortR(void)
    {
        asm("bug");
        return DUMMYPORT;
    };
    #endif 

};
template <typename SPIMASTER, typename CSPIN, unsigned int LEN> unsigned char IOEXTENDERPORT<SPIMASTER,CSPIN,LEN>::Val[LEN];


// Forward declaration 
template <SCIO::t_ioaccess PT, typename P, unsigned int NUM, SCIO::t_iotype Type, int val> class PD;

// Specialize for NORMAL
#if defined(AVR) 
template <typename P, unsigned int NUM, SCIO::t_iotype Type, int val>
class PD<SCIO::NORMAL,P,NUM,Type,val>
{

public: 

    static inline void SetDirOut(void)
    {
        P::PortR().DIR |= (1 << NUM);
    };

    static inline void SetDirIn(void)
    {
        P::PortR().DIR &= ~(1 << NUM);
    };

    static inline void Init(void)
    {
        switch (Type) {
        case SCIO::OUTPUT:
            SetDirOut();
            if (val) { 
                set();
            } else {
                clr();
            } // endif
            break;

        case SCIO::INPUT_PULLUP:
            EnablePullUp();
            SetDirIn();
            break;

        case SCIO::INPUT_PULLDOWN:
            EnablePullDown();
            SetDirIn();
            break;

        case SCIO::INPUT:
            SetDirIn();
            break;
        } // endswitch
            
    };

    static inline void set(void)
    {
        P::PortR().OUTSET = (1 << NUM);
    };

    static inline void clr(void)
    {
        P::PortR().OUTCLR = (1 << NUM);
    };

    // Tested OK 
    static inline void EnablePullUp(void)
    {
         *((volatile unsigned char *)&P::PortR().PIN0CTRL + NUM) = \
        (*((volatile unsigned char *)&P::PortR().PIN0CTRL + NUM) & (~PORT_OPC_gm)) | PORT_OPC_PULLUP_gc;
    };

    // Tested OK 
    static inline void DisablePullUp(void)
    {
        *((volatile unsigned char *)&P::PortR().PIN0CTRL + NUM) = \
        (*((volatile unsigned char *)&P::PortR().PIN0CTRL + NUM) & (~PORT_OPC_gm));
    };

    // Tested OK 
    static inline void EnablePullDown(void)
    {
         *((volatile unsigned char *)&P::PortR().PIN0CTRL + NUM) = \
        (*((volatile unsigned char *)&P::PortR().PIN0CTRL + NUM) & (~PORT_OPC_gm)) | PORT_OPC_PULLDOWN_gc;
    };

    // Tested OK 
    static inline void DisablePullDown(void)
    {
        *((volatile unsigned char *)&P::PortR().PIN0CTRL + NUM) = \
        (*((volatile unsigned char *)&P::PortR().PIN0CTRL + NUM) & (~PORT_OPC_gm));
    };

    // Test
    static inline void LimitSlewRate(void)
    {
        *((volatile unsigned char *)&P::PortR().PIN0CTRL + NUM) |= PORT_SRLEN_bm;
    };

    // Test
    static inline void FullSlewRate(void)
    {
        *((volatile unsigned char *)&P::PortR().PIN0CTRL + NUM) = \
        (*((volatile unsigned char *)&P::PortR().PIN0CTRL + NUM) & (~PORT_SRLEN_bm));
    };

    // Test
    static inline void InvertedIO(void)
    {
        *((volatile unsigned char *)&P::PortR().PIN0CTRL + NUM) |= PORT_INVEN_bm;
    };

    static inline void NonInvertedIO(void)
    {
        *((volatile unsigned char *)&P::PortR().PIN0CTRL + NUM) = \
        (*((volatile unsigned char *)&P::PortR().PIN0CTRL + NUM) & (~PORT_INVEN_bm));
        
    };

    static inline bool IsPinInSet(void)
    {
        return ((P::PortR().IN & (1 << NUM)) != 0);
    };

    static inline bool IsPinInClr(void)
    {
        return !IsPinInSet();
    };

    static inline bool IsPinOutSet(void)
    {
        return ((P::PortR().OUT & (1 << NUM)) != 0);
    };

    static inline bool IsPinOutClr(void)
    {
        return (!IsPinOutSet());
    };

    static inline void ToggleBit(void)
    {
        P::PortR().OUTTGL = (1 << NUM);
    };

};

// Specialize for VIRTUAL
template <typename P, unsigned int NUM, SCIO::t_iotype Type, int val>
class PD<SCIO::VIRTUAL,P,NUM,Type,val>
{

public: 

    static inline void SetDirOut(void)
    {
        P::PortR().DIR |= (1 << NUM);
    };

    static inline void SetDirIn(void)
    {
        P::VPort().DIR &= ~(1 << NUM);
    };

    static inline void Init(void)
    {
        switch (Type) {
        case SCIO::OUTPUT:
            SetDirOut();
            if (val) { 
                set();
            } else {
                clr();
            } // endif
            break;

        case SCIO::INPUT_PULLUP:
            EnablePullUp();
            SetDirIn();
            break;

        case SCIO::INPUT_PULLDOWN:
            EnablePullDown();
            SetDirIn();
            break;

        case SCIO::INPUT:
            SetDirIn();
            break;
        } // endswitch
            
    };


    static inline void set(void)
    {
        // The compiler should figure out to make a sbi
        P::VPort().OUT |= (1 << NUM); 
        
        /*
        asm volatile (
                "sbi %1,%0\n\t"
                ::"i"(NUM), "i"(&(P::VPort().OUT))
        ); 
        */ 
    };

    static inline void clr(void)
    {
        // The compiler should figure out to make a cbi
        P::VPort().OUT &= ~(1 << NUM); 
        /*
        asm volatile (
                "cbi %1,%0\n\t"
                ::"i"(NUM), "i"(&(P::VPort().OUT))
        ); 
        */ 
    };

    // Tested OK 
    static inline void EnablePullUp(void)
    {
         *((volatile unsigned char *)&P::PortR().PIN0CTRL + NUM) = \
        (*((volatile unsigned char *)&P::PortR().PIN0CTRL + NUM) & (~PORT_OPC_gm)) | PORT_OPC_PULLUP_gc;
    };

    // Tested OK 
    static inline void DisablePullUp(void)
    {
        *((volatile unsigned char *)&P::PortR().PIN0CTRL + NUM) = \
        (*((volatile unsigned char *)&P::PortR().PIN0CTRL + NUM) & (~PORT_OPC_gm));
    };

    // Tested OK 
    static inline void EnablePullDown(void)
    {
         *((volatile unsigned char *)&P::PortR().PIN0CTRL + NUM) = \
        (*((volatile unsigned char *)&P::PortR().PIN0CTRL + NUM) & (~PORT_OPC_gm)) | PORT_OPC_PULLDOWN_gc;
    };

    // Tested OK 
    static inline void DisablePullDown(void)
    {
        *((volatile unsigned char *)&P::PortR().PIN0CTRL + NUM) = \
        (*((volatile unsigned char *)&P::PortR().PIN0CTRL + NUM) & (~PORT_OPC_gm));
    };

    // Test
    static inline void LimitSlewRate(void)
    {
        *((volatile unsigned char *)&P::PortR().PIN0CTRL + NUM) |= PORT_SRLEN_bm;
    };

    // Test
    static inline void FullSlewRate(void)
    {
        *((volatile unsigned char *)&P::PortR().PIN0CTRL + NUM) = \
        (*((volatile unsigned char *)&P::PortR().PIN0CTRL + NUM) & (~PORT_SRLEN_bm));
    };

    // Test
    static inline void InvertedIO(void)
    {
        *((volatile unsigned char *)&P::PortR().PIN0CTRL + NUM) |= PORT_INVEN_bm;
    };

    static inline void NonInvertedIO(void)
    {
        *((volatile unsigned char *)&P::PortR().PIN0CTRL + NUM) = \
        (*((volatile unsigned char *)&P::PortR().PIN0CTRL + NUM) & (~PORT_INVEN_bm));
        
    };

    static inline bool IsPinInSet(void)
    {
        return ((P::VPort().IN & (1 << NUM)) != 0);
    };

    static inline bool IsPinInClr(void)
    {
        return !IsPinInSet();
    };

    static inline bool IsPinOutSet(void)
    {
        return ((P::VPort().OUT & (1 << NUM)) != 0);
    };

    static inline bool IsPinOutClr(void)
    {
        return (!IsPinOutSet());
    };

    static inline void ToggleBit(void)
    {
        // Using regular IO seems to be the fastest no matter what
        P::PortR().OUTTGL = (1 << NUM);
    };

};


#elif defined(_STM32x_)



template <typename P, unsigned int NUM, SCIO::t_iotype Type, int val>
class PD<SCIO::NORMAL,P,NUM,Type,val>
{

    

    static void inline SetConfA(Int2Type<0> dum, unsigned int Value) __attribute__((always_inline))
    {
        P::PortR().CRL = (P::PortR().CRL & ~mask) | ( Value << ((NUM-0)*4));
    }

    static void inline SetConfA(Int2Type<1> dum, unsigned int Value) __attribute__((always_inline))
    {
        P::PortR().CRH = (P::PortR().CRH & ~mask) | ( Value << ((NUM-8)*4));
    }

    static void inline SetConf(unsigned int Value) __attribute__((always_inline))
    {
        Int2Type<(NUM > 7) ? 1:0> dum;
        SetConfA(dum,Value);
    }

public: 

    static const unsigned int PortNum = NUM;

    static const char * Name(void) 
    {
        return P::Name();
    }



public: 

    // RM0008 Table 20 page 156

    // CNF1, CNF0 in Group position in Port configuration register high/low (CRH/CRL)
    #define STM32_GPIO_CONF_OUT_PUSHPULL        (0x00 << 2)
    #define STM32_GPIO_CONF_OUT_OPENDRAIN       (0x01 << 2)
    #define STM32_GPIO_CONF_ALTERNATE_PUSHPULL  (0x02 << 2)
    #define STM32_GPIO_CONF_ALTERNATE_OPENDRAIN (0x03 << 2)
    #define STM32_GPIO_CONF_IN_ANALOG           (0x00 << 2)
    #define STM32_GPIO_CONF_IN_FLOAT            (0x01 << 2)
    #define STM32_GPIO_CONF_IN_PULL             (0x02 << 2)

    // MODE1, MODE0 in Group position in Port configuration register high/low (CRH/CRL)
    #define STM32_GPIO_MODE_INPUT               (0x00)
    #define STM32_GPIO_MODE_OUTPUT_10MHZ        (0x01)
    #define STM32_GPIO_MODE_OUTPUT_2MHZ         (0x02)
    #define STM32_GPIO_MODE_OUTPUT_50MHZ        (0x03)

    static const unsigned int mask = 0xF << ((NUM < 8) ? (NUM*4) : ((NUM-8)*4));

    static inline void SetDirOut(void) __attribute__((always_inline))
    {
        FIXME(2 fixed output speed);
        SetConf(STM32_GPIO_MODE_OUTPUT_50MHZ | STM32_GPIO_CONF_OUT_PUSHPULL);
    };

    static inline void SetDirIn(void) __attribute__((always_inline))
    {
        SetConf(STM32_GPIO_MODE_INPUT | STM32_GPIO_CONF_IN_FLOAT);
    };

    static inline void Init(void) __attribute__((always_inline))
    {
        switch (Type) {
        case SCIO::OUTPUT:
            if (val) { 
                set();
            } else {
                clr();
            } // endif
            SetDirOut();
            break;

        case SCIO::INPUT_PULLUP:
            SetDirIn_PullUp();
            break;

        case SCIO::INPUT_PULLDOWN:
            SetDirIn_PullDown();
            break;

        case SCIO::INPUT:
            SetDirIn();
            break;

        case SCIO::INPUT_ANALOG:
            SetConf(0);
            break;

        case SCIO::PERIF:
            SetPerif();
            break;
        } // endswitch
            
    };

    static inline void set(void) __attribute__((always_inline))
    {
        P::PortR().BSRR = (1 << NUM);
    };

    static inline void clr(void) __attribute__((always_inline))
    {
        P::PortR().BRR = (1 << NUM);
    };


    static inline void SetDirIn_PullUp(void) __attribute__((always_inline))
    {
        SetConf(STM32_GPIO_MODE_INPUT | STM32_GPIO_CONF_IN_PULL);
        P::PortR().ODR |= (1 << NUM); // pull-up
        
    };

    static inline void SetPerif(void) __attribute__((always_inline))
    {
        FIXME(2 fixed output speed and conf);
        SetConf(STM32_GPIO_MODE_OUTPUT_2MHZ | STM32_GPIO_CONF_ALTERNATE_PUSHPULL);

    };

    static inline void SetDirIn_PullDown(void) __attribute__((always_inline))
    {
        SetConf(STM32_GPIO_MODE_INPUT | STM32_GPIO_CONF_IN_PULL);
        P::PortR().ODR &= ~(1 << NUM); // pull-down
    };

    // Test
    static inline void LimitSlewRate(void) __attribute__((always_inline))
    {
        FIXME(2 Fixed speed and conf)
        SetConf(STM32_GPIO_MODE_OUTPUT_2MHZ | STM32_GPIO_CONF_OUT_PUSHPULL);
    };

    // Test
    static inline void FullSlewRate(void) __attribute__((always_inline))
    {
        FIXME(2 Fixed speed and conf)
        SetConf(STM32_GPIO_MODE_OUTPUT_50MHZ | STM32_GPIO_CONF_OUT_PUSHPULL);
    };

    // Test
    static inline void InvertedIO(void)
    {
    };

    static inline void NonInvertedIO(void)
    {
    };

    static inline bool IsPinInSet(void) __attribute__((always_inline))
    {
        return !IsPinInClr();
    };

    static inline bool IsPinInClr(void) __attribute__((always_inline))
    {

        return ((P::PortR().IDR & (1 << NUM)) == 0);
    };

    static inline bool IsPinOutSet(void) __attribute__((always_inline))
    {
        TODO(1a); 
        asm("bug");
        return false;
    };

    static inline bool IsPinOutClr(void)
    {
        TODO(1a); 
        asm("bug");
        return false;
    };

    static inline void ToggleBit(void)
    {
        TODO(1a); 
        asm("bug");
        return false;
    };

};


#else 
 #error "NOT";
#endif 


// Specialize for IOEXTENDER
template <typename P, unsigned int NUM, SCIO::t_iotype Type, int val>
class PD<SCIO::EXTENDER,P,NUM,Type,val>
{

public: 

    /*
    static inline void SetDirOut(void)
    {
    };

    static inline void SetDirIn(void)
    {
    };
    */

    static inline void Init(void)
    {
        if (val) { 
            P::Val[NUM / 8] |= (1 << (NUM % 8));
        } else {
            P::Val[NUM / 8] &= ~(1 << (NUM % 8));
        } // endif
    };

    static inline void set(void)
    {
        P::Val[NUM / 8] |= (1 << (NUM % 8));
        P::Update();
    };

    static inline void clr(void)
    {
        P::Val[NUM / 8] &= ~(1 << (NUM % 8));
        P::Update();
    };

    static inline bool IsPinOutSet(void)
    {
        return ((P::Val[NUM / 8] & (1 << (NUM % 8))) != 0);
    };

    static inline bool IsPinOutClr(void)
    {
        return (!IsPinOutSet());
    };

    static inline void ToggleBit(void)
    {
        if (IsPinOutSet()) { 
            clr();
        } else {
            set();
        } // endif
    };

};




#define PREFIX

// The two typedefs serves to present a callable name to the user and a name that can be called by the init routines 
// The static const declaration serves to prevent two definitions of the same port - at compile time
#define PinDef(PORT,NUM, TYPE, VAL) \
    static const int CHECK##MYPORT##PORT##NUM = 0;\
    typedef PD<MYPORT##PORT::PortType, PREFIX MYPORT##PORT,NUM, TYPE, VAL> MYPORT##PORT##NUM;\
    typedef PD<MYPORT##PORT::PortType, PREFIX MYPORT##PORT,NUM, TYPE, VAL>
    

// The static const int decl checks that the same virtual port is not used more than once
#define VirtPortDef(PORT,VPORT) static const int TEST##VPORT = 0; typedef HSPORT<PORT,VPORT> MYPORT##PORT
//#define NormPortDef(PORT) static const int PORT##TEST = 0;  typedef NORMALPORT<PORT,(SCIO::t_virtportnumber)0> MYPORT##PORT

#define NormPortDefII(PORT) typedef NORMALPORT<SCIO::PORT,(SCIO::t_virtportnumber)0> MYPORT##PORT

#define IOEXTENDER(NAME,SPIMASTER, CSPIN, LEN) typedef IOEXTENDERPORT<SPIMASTER,CSPIN,LEN> MYPORTIOEXTPORT_##NAME

// Default declarations OUTSIDE namespace
struct Nothing 
{
    static void Init(void) {};
    static void Update(void) {};
};

#define NOTHING(PORT) \
        typedef Nothing MYPORT##PORT##0;  typedef Nothing MYPORT##PORT##8;  typedef Nothing MYPORT##PORT##16;  typedef Nothing MYPORT##PORT##24;\
        typedef Nothing MYPORT##PORT##1;  typedef Nothing MYPORT##PORT##9;  typedef Nothing MYPORT##PORT##17;  typedef Nothing MYPORT##PORT##25;\
        typedef Nothing MYPORT##PORT##2;  typedef Nothing MYPORT##PORT##10; typedef Nothing MYPORT##PORT##18;  typedef Nothing MYPORT##PORT##26;\
        typedef Nothing MYPORT##PORT##3;  typedef Nothing MYPORT##PORT##11; typedef Nothing MYPORT##PORT##19;  typedef Nothing MYPORT##PORT##27;\
        typedef Nothing MYPORT##PORT##4;  typedef Nothing MYPORT##PORT##12; typedef Nothing MYPORT##PORT##20;  typedef Nothing MYPORT##PORT##28;\
        typedef Nothing MYPORT##PORT##5;  typedef Nothing MYPORT##PORT##13; typedef Nothing MYPORT##PORT##21;  typedef Nothing MYPORT##PORT##29;\
        typedef Nothing MYPORT##PORT##6;  typedef Nothing MYPORT##PORT##14; typedef Nothing MYPORT##PORT##22;  typedef Nothing MYPORT##PORT##30;\
        typedef Nothing MYPORT##PORT##7;  typedef Nothing MYPORT##PORT##15; typedef Nothing MYPORT##PORT##23;  typedef Nothing MYPORT##PORT##31;\


// Define a type for ALL iopins on the device 
NOTHING(A);
NOTHING(B);
NOTHING(C);
NOTHING(D);
NOTHING(E);
NOTHING(F);
NOTHING(G);
NOTHING(H);
NOTHING(J);
NOTHING(K);
NOTHING(L);
NOTHING(M);
NOTHING(N);
NOTHING(Q);
NOTHING(R);

// Define all ports as normal 
NormPortDefII(A);
NormPortDefII(B);
NormPortDefII(C);
NormPortDefII(D);
NormPortDefII(E);
NormPortDefII(F);
NormPortDefII(G);
NormPortDefII(H);
NormPortDefII(J);
NormPortDefII(K);
NormPortDefII(L);
NormPortDefII(M);
NormPortDefII(N);
NormPortDefII(Q);
NormPortDefII(R);

// Create empty types for the IOEXTENDER
typedef Nothing MYPORTIOEXTPORT_0;
typedef Nothing MYPORTIOEXTPORT_1;
typedef Nothing MYPORTIOEXTPORT_2;
typedef Nothing MYPORTIOEXTPORT_3;

// Define a type for ALL iopins on the IOEXTENDERS 
NOTHING(IOEXTPORT_0);
NOTHING(IOEXTPORT_1);
NOTHING(IOEXTPORT_2);
NOTHING(IOEXTPORT_3);

#undef NOTHING
#undef NormPortDefII

FIXME(2 We should be able to pick up all default values and directions and do a single IO initialization);
#define INIT(PORT)           \
    MYPORT##PORT::Init();    \
    MYPORT##PORT##0::Init();    MYPORT##PORT##8::Init();    MYPORT##PORT##16::Init();   MYPORT##PORT##24::Init();\
    MYPORT##PORT##1::Init();    MYPORT##PORT##9::Init();    MYPORT##PORT##17::Init();   MYPORT##PORT##25::Init();\
    MYPORT##PORT##2::Init();    MYPORT##PORT##10::Init();   MYPORT##PORT##18::Init();   MYPORT##PORT##26::Init();\
    MYPORT##PORT##3::Init();    MYPORT##PORT##11::Init();   MYPORT##PORT##19::Init();   MYPORT##PORT##27::Init();\
    MYPORT##PORT##4::Init();    MYPORT##PORT##12::Init();   MYPORT##PORT##20::Init();   MYPORT##PORT##28::Init();\
    MYPORT##PORT##5::Init();    MYPORT##PORT##13::Init();   MYPORT##PORT##21::Init();   MYPORT##PORT##29::Init();\
    MYPORT##PORT##6::Init();    MYPORT##PORT##14::Init();   MYPORT##PORT##22::Init();   MYPORT##PORT##30::Init();\
    MYPORT##PORT##7::Init();    MYPORT##PORT##15::Init();   MYPORT##PORT##23::Init();   MYPORT##PORT##31::Init();

#define BEGIN_IOINIT() \
namespace SCIO {

#define END_IOINIT() \
template <int dum> void XXX_IoInit(void) \
{\
INIT(A);           \
INIT(B);           \
INIT(C);           \
INIT(D);           \
INIT(E);           \
INIT(F);           \
INIT(G);           \
INIT(H);           \
INIT(J);           \
INIT(K);           \
INIT(Q);           \
INIT(R);           \
INIT(IOEXTPORT_0); \
INIT(IOEXTPORT_1); \
INIT(IOEXTPORT_2); \
INIT(IOEXTPORT_3); \
MYPORTIOEXTPORT_0::Update();\
MYPORTIOEXTPORT_1::Update();\
MYPORTIOEXTPORT_2::Update();\
MYPORTIOEXTPORT_3::Update();\
}; \
}; \
using namespace SCIO;


#define IOINIT XXX_IoInit<0>();

#define SetBit(bit)             bit::set();
#define ClrBit(bit)             bit::clr();

#define SetPerif(bit)           bit::SetPerif();

#define IsPinInSet(bit)         bit::IsPinInSet()
#define IsPinInClr(bit)         bit::IsPinInClr()

#define IsPinOutSet(bit)        bit::IsPinOutSet()
#define IsPinOutClr(bit)        bit::IsPinOutClr()

#define SetBitDirOut(bit)       bit::SetDirOut();
#define SetBitDirIn(bit)        bit::SetDirIn();

/*
#define EnablePullUp(bit)       bit::EnablePullUp();
#define DisablePullUp(bit)      bit::DisablePullUp();

#define EnablePullDown(bit)     bit::EnablePullDown();
#define DisablePullDown(bit)    bit::DisablePullDown();
*/

#define SetBitDirIn_PullUp(bit)       bit::SetDirIn_PullUp();
#define SetBitDirIn_PullDown(bit)     bit::SetDirIn_PullDown();


#define LimitSlewRate(bit)      bit::LimitSlewRate();
#define FullSlewRate(bit)       bit::FullSlewRate();

#define InvertedIO(bit)         bit::InvertedIO();
#define NonInvertedIO(bit)      bit::NonInvertedIO();


#define ToggleBit(bit)          bit::ToggleBit();


#endif 

#else 

    #include "log.h"



    #define SetBit(bit)                 if (!(bit & (1 << 4))) { \
                                            Register[(unsigned char)((unsigned long)bit >> 24)] |=  (1 << (bit & 0x0007));\
                                        } else { \
                                            log_dev("BUMMER\n");\
                                        };



    #define ClrBit(bit)                 if (!(bit & (1 << 4))) { \
                                            Register[(unsigned char)((unsigned long)bit >> 24)] &=  ~(1 << (bit & 0x0007));\
                                        } else { \
                                            log_dev("BUMMER\n");\
                                        };      
    


    #define IsPinSet(bit)   (Register[(unsigned char)((unsigned long)bit >> 24)] & (1 << (bit & 0x0007)))


    #define IsPinClr(bit)   (!IsPinSet(bit))


    #define HasChanged(bit) (Register[(unsigned char)((unsigned long)bit >> 24)].change & (1 << (bit & 0x0007)))
                            


    #define AcknChange(bit) (Register[(unsigned char)((unsigned long)bit >> 24)].change &= ~(1 << (bit & 0x0007)))
                            
        
    #define SetBitShare(x,bit)(Register[(unsigned char)((unsigned long)bit >> 24)].Share("AvrEmulationBitShare_"x,((unsigned char)(bit & 0x0007))))
        
        
        
    #define SetBitDirIn(bit)  
    #define SetBitDirOut(bit) 
    #define EnablePullUp(bit)
    #define DisablePullUp(bit)
    //#define PORTDEF(x) x
    
    
    #define ADDR(x)         (unsigned int)(&(x) - (&Register[0]))
    
    #define PORTDEF(x)      ((unsigned long)((unsigned long)(ADDR(PORT##x)) << 24 | (unsigned long)(ADDR(DDR##x)) << 16 | (unsigned long)(ADDR(PIN##x)) << 8))
    #define IOREG(x)   x

#endif 

#endif 
