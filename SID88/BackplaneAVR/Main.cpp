//$Id: Main.cpp 1.9 2014/12/04 07:44:00 carsten tnt $
//$Log: Main.cpp $
//Revision 1.9  2014/12/04 07:44:00  carsten
//1) Main(): Added new Timers for controlling HB-info. and ADC measurement output 
//2) Main(): HB output for LUX_VALUE changed from int to uint
//3) Main(): HB output for SystemTimer.TimerVal adjusted to 1Hz (1/1000)
//Revision 1.8c 2014/12/02 12:15:00  carsten
//1) Frequency count from Light Sensor (TCNT3) limited to uint/10 to fit 10x calculation in getLux()
//Revision 1.8b 2014/12/02 09:55:00  carsten
//1) Light to Frequency converter: LUX_VALUE changed from int to uint
//2) Main(): Timer for HB output and LumHandler set back to orig. 10s update rate 
//Revision 1.8a 2014/12/01 09:08:00  carsten
//1) ISR(TIMER0_OVF_vect): Modified to turn off 7-segments within interrupt for intensity 1-3
//2) ISR(TIMER0_OVF_vect): Modified to copy/store actual battery current read from ADC(2) 
//3) Main(): Added new Timer for HB_Led_Toggle with 3s update rate
//4) Main(): Timer for HB output and LumHandler changed from 10s to 30s update rate
//Revision 1.7  2014/11/27 11:32:00  carsten
//1) Modified CommandHandler for "*L0" to return actual intensity (not 0 from command)
//2) Modified SetDisplayIntensity with fix to reduce 7-segment pulse width @ intensity 2
//Revision 1.6b 2014/11/25 14:50:50  jacob
//Modified/Fixed ISR(TIMER0_OVF_vect) to turn off 7-segments within interrupt for intensity 1-2
//Revision 1.6a 2014/11/21 14:15:00  carsten
//Temporary trial with Timer2 and Timing (code reduction) => No changes to original code ...
//Revision 1.5  2014/11/19 11:52:00  carsten
//Modified/enabled to include SID88 Light Test
//1) While-loop: Changed evaluation for SetDisplaySpeed(0)
//2) SetDisplayIntensity: Intensity range changed to 0-100
//3) CommandHandler: Added/updated commands from SID_LUX 
//Revision 1.4  2014/07/18 09:51:29  jacob
//Backup
//Revision 1.3  2014/06/20 07:43:56  Peter
//Backup
//Revision 1.2  2014/06/18 08:24:17  jacob
//Revision 1.9  2013/11/28 20:27:20  jacob
//Fix of idiotic 6.5 x error
//Revision 1.8  2013/11/28 11:33:04  jacob
//Added a 5us before doinf the ADC measurement
//Revision 1.7  2013/11/25 10:18:02  jacob
//Now using a 2R resistor
//Revision 1.6  2013/11/11 21:00:50  jacob
//Filter constant changed from 66.0 to 0.0
//Revision 1.5  2013/11/11 09:57:23  jacob
//Changed PWM to phase correct.
//ADC runs on ints while PWM uses HW
//Revision 1.4  2013/11/07 16:28:35  jacob
//Backup
//Revision 1.3  2013/11/07 16:27:45  jacob
//WIP
//Revision 1.2  2013/11/07 11:56:04  jacob
//WIP
//Revision 1.1  2013/10/28 11:36:38  jacob

#include <stdlib.h>
#include <stdio.h>      // vsnprintf
#include <stdarg.h>     
#include <string.h>     
#include <math.h>

#include "CommonSupport.h"
#include "avrutils.h"
#include "VersionStr.h"


//-------------------------------------------------------------------------------------
//LIGHT TO FREQUENCY CONVERTER (SENSOR TSL230)
//-------------------------------------------------------------------------------------          
//primary sensor (front mounted)
//#define LFC_FACTOR_0                                          0.4578                                                        
//for sens x10
#define LFC_FACTOR_0                                          0.69                                                        
//for sens x1 (i OE testskilt (24x18) ???
#define LFC_FDIV_0                                         2.0                                                                
//frequency division factor     
#define LFC_TFP_0                                            66.0  // 98.9                                                  
//TFP = PSCfilter + BG40filter (transmitance for both)

//#define LFC_FACTOR_1                                          0.4578                                                        
//for sens x10
#define LFC_FACTOR_1                                          0.69                                                        
//for sens x1
#define LFC_FDIV_1                                         2.0                                                                
//frequency division factor     
#define LFC_TFP_1                                            66.0                                                        
//TFP = PSCfilter + BG40filter (transmitance for both)

#define LFC_MEASURESPERSEC                                10.0
//-------------------------------------------------------------------------------------
//LUMINANCE CONVERSION
//-------------------------------------------------------------------------------------          
//illuminance(lx) / luminance(cd/m2) relationship defined by :  luminans(illum.) = b*x^a [cd/m2]
//#define LUM_TFP                                                        40.0                                        //TotalFilterPercent (how much light is lost)
#define LUM_TFP                                                55.0                                                  
//TotalFilterPercent (how much light is lost)
#define LUM_SIGN_MIN                                        300                                                
//emmit minimum 300 cd/m2

//-------------FOR THE 16x12 NEWBIES (WHITE)------------------
#define LUM_ILLUM_A                                        0.48192  
#define LUM_ILLUM_B                                          98.9011  
#define LUM_SIGN_MAX                                        40.0e3                
//[cd/m2] measured@100% dutycycle (White LEDS as reference)
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//
//formula is: pwm_factor =  LUM_SIGN_MAX / ((b*lx^a)*(100+LUM_TFP/100)) * PWM_PERIODS;
//                                       "cd/m2" * "filterfactor"    

//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//GENERIC DEFINES
//-------------------------------------------------------------------------------------                       
#define PETDOG {asm("WDR");}                                        
//reset the watchdog timer   


//-------------------------------------------------------------------------------------
//TIMERS & TIMEOUTS
//-------------------------------------------------------------------------------------                                   
static const unsigned int MAX_PACKET_SIZE = 250;

//-------------------------------------------------------------------------------------
// PWM
//-------------------------------------------------------------------------------------                                   
#define PWMPERIODS                          255                                                
// = 44kHz interrupt / ~100Hz refresh rate
#define DEFAULTPWMDUTYMIN                  1.0                                   
//if '0.0' selected the system will set the lowest permissable level (1/256)
#define DEFAULTPWMDUTYMAX                  100.0              

      

#define ADC_VREF_TYPE ((0<<REFS1) | (1<<REFS0) | (0<<ADLAR))     


// uart 
t_DebugUart   DebugUart;

// 1kHz systemtimer 
t_SystemTimer SystemTimer;


// Local prototypes 
void ProtoReply(const char *fmt, ...);

void ShowHelp(void);

void SetDisplaySpeed(unsigned int Speed);
unsigned int GetDisplaySpeed(void);

void SetDisplayIntensity(unsigned char Intensity);
unsigned int GetDisplayIntensity(void);

void CommandHandler(void);
int GetInteger(char *txt, int iStartPos);

void LumHandler(bool maxchangeon);

void HB_Led_Toggle(void);


//-------------------------------------------------------------------------------------
//LIGHT TO FREQUENCY CONVERTER (SENSOR TSL230)
//-------------------------------------------------------------------------------------

//_____________PWM______________________________
uint                        PWMmanfactor = (uchar)(DEFAULTPWMDUTYMIN * (float)PWMPERIODS / 100.0);
unsigned char               PWMdutymin;                        //min. PWM duty
unsigned char               PWMdutymax;                        //max. PWM duty
uint                        PWMfactormin = 1;                  //vars used for the controlling of matrix brigthness
uint                        PWMfactormax = 100;
uint                        LUX_VALUE = 0;

//______LIGHT FREQUENCY COUINTING________________________________________
//frequency counting from lightsensor(s)
//"front mounted TSL230" (primary) uses counter 3 as input (TCNT3L, TCNT3H is read!)
//"back mounted TSL230" (secondary )uses IRQ7 as input (+ edge triggered) value stored in fsecondarysensor
unsigned int                        fregister0[11] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };        //rolling frecuency array register(primary sensor)
unsigned int                        fregister1[11] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };        //rolling frecuency array register(sec. sensor)
uchar                               fregistercount = 0;                        //the counter for fregister rolling array


//-------------------------------------------------------------------------------------
// 7 Segment display
//-------------------------------------------------------------------------------------
// 7 segment decoder values
const char SegCode[11] = { 0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78, 0x0, 0x10, 0xff };
//                         0    1    2    3    4    5    6    7    8    9    off
// Used to output manipulate digits, one at a time (MUX)
char Column[2] = { 0xff, 0xff };


//_______GLOBAL F_________________________________________________________________________
unsigned int       iShowTimeOut = 50;        // Timeout variable    1/10 sekunder
unsigned int       iShowFlash = 50;          // Speed Limit for Activate Flash



char               bAutoPWM                             = 1;        //make the system regulate brigthnes automaticaly
char               txtInfo[101];

volatile unsigned int iAD_BG_Segment_Current;
volatile unsigned int iAD_Flash_Current;
volatile unsigned int iAD_BG_Flash_Current;
volatile unsigned int iAD_Batteri_Current;
volatile unsigned int iAD_Segment[8];

/* 
 
TIMER USAGE 
0: 8  bit is used for segment multiplexing        => ~97Hz / 10,3 ms period (per segment)
1: 16 bit used for systemtimer                    =>  1kHz /  1,0 ms period
2; 8  bit                                         =>  N/A
3: 16 bit is used for ambient light measurements  =>  Pulsecount from sensor TSL230
 
*/


//_____________TIMERE, COUNTERE ETC______________________________________
unsigned long int       t_readyleds     = 5L;
unsigned long int       t_lumhandler    = 100L;                 //timere for de forskellige lag 1 handlere
//unsigned long int       t_showspeed     = 0L;



void init(void) {
    //****** R E G I S T E R / P O R T   I N I T ************
    // PORTX     = input: 0=tristated, 1=pulled up.  output: 0=0, 1=1
    // DDRX        = 0=input, 1=output

    PORTB =    0b00110001;
    DDRB =     0b11110001;

    PORTD =    0b00110000;     //0b00100000        //CS2(5)=HI, A16(6)=LO
    DDRD =     0b01110000;  //0b01110000

    PORTE = 0b00101100;    //0b00111000;
    DDRE = 0b00101000;    //0b00111000;

    PORTA = 0xff;
    DDRA = 0b11111111;

    PORTC = 0xff;
    DDRC = 0b11111111;

    // Port F initialization    Low 4 bit A/D   High 4 bit Output
    // Function: Bit7=Out Bit6=Out Bit5=Out Bit4=Out Bit3=In Bit2=In Bit1=In Bit0=In
    DDRF = (1 << DDF7) | (1 << DDF6) | (1 << DDF5) | (1 << DDF4) | (0 << DDF3) | (0 << DDF2) | (0 << DDF1) | (0 << DDF0);
    // State: Bit7=0 Bit6=0 Bit5=0 Bit4=0 Bit3=T Bit2=T Bit1=T Bit0=T
    PORTF = (0 << PORTF7) | (0 << PORTF6) | (0 << PORTF5) | (0 << PORTF4) | (0 << PORTF3) | (0 << PORTF2) | (0 << PORTF1) | (0 << PORTF0);

    PORTG    = 0b00001000;
    DDRG    = 0b00001000;            //00011000  ONLY PG3&PG4


    // Segment Multiplexer
    // Timer/Counter 0 initialization
    // OC0 output: Disconnected
    // Timer Period: 10,3 ms -> ~97Hz
    ASSR = 0 << AS0;
    TCCR0 = (0 << WGM00) | (0 << COM01) | (0 << COM00) | (0 << WGM01) | (1 << CS02) | (0 << CS01) | (0 << CS00);
    TCNT0 = 0x58;
    OCR0 = 0x00;


    // Timer/Counter 3 initialization
    // Clock source: T3 pin Rising Edge
    // Mode: Normal top=FFFFh
    // OC3A output: Discon.
    // OC3B output: Discon.
    // OC3C output: Discon.
    TCCR3A = 0x00;
    TCCR3B = 0x07;
    //TCCR3B=0x00;
    TCCR3C = 0x00;
    TCNT3H = 0x00;
    TCNT3L = 0x00;
    ICR3H = 0x00;
    ICR3L = 0x00;
    OCR3AH = 0x00;
    OCR3AL = 0x00;
    OCR3BH = 0x00;
    OCR3BL = 0x00;
    OCR3CH = 0x00;
    OCR3CL = 0x00;


    // External Interrupt(s) initialization
    // INT0: Off
    // INT1: Off
    // INT2: Off
    // INT3: Off
    // INT4: Off
    // INT5: Off
    // INT6: Off
    // INT7: On
    // INT7 Mode: Rising Edge
    EICRA = 0x00;
    EICRB = 0xC0;
    EIMSK = 0x80;
    EIFR = 0x80;

    PETDOG;

    // Timer(s)/Counter(s) Interrupt(s) initialization
    // enable overflow interrupt Timer 0, 1 og 2
    //TIMSK |= (1 << TOIE0);
    //TIMSK |= (1 << TOIE1);
    //TIMSK |= (1 << TOIE2);
    TIMSK = ((0 << OCIE2) | (0 << TOIE2) | (0 << TICIE1) | (0 << OCIE1A) | (0 << OCIE1B) | (0 << TOIE1) | (1 << OCIE0) | (1 << TOIE0));

    ETIMSK = 0x00;


    // Analog Comparator initialization
    // Analog Comparator: Off
    // Analog Comparator Input Capture by Timer/Counter 1: Off
    // Analog Comparator Output: Off
    ACSR = 0x80;
    SFIOR = 0x00;

    // ADC initialization
    // ADC Clock frequency: 691,200 kHz
    // ADC Voltage Reference: AVCC pin
    // Voltage Reference: AVCC pin
    ADMUX = ADC_VREF_TYPE;
    ADCSRA = (1 << ADEN) | (0 << ADSC) | (0 << ADFR) | (0 << ADIF) | (0 << ADIE) | (1 << ADPS2) | (0 << ADPS1) | (0 << ADPS0);
    SFIOR = (0 << ACME);

    PWMdutymin = (uchar)DEFAULTPWMDUTYMIN;        //set the default values if values =0
    PWMdutymax = (uchar)DEFAULTPWMDUTYMAX;

    PWMfactormin = 	(int)((float)PWMdutymin * ((float)PWMPERIODS / 100.0));         //calculate the corresponding PWMfactors
    PWMfactormax = 	(int)(((float)PWMdutymax / 100.0) * (float)PWMPERIODS);

    //-------------------------------------------------------------------------------------*******
    PORTB |= (1 << 4);
    PORTB |= (1 << 7);

    bAutoPWM = 1;

    return;
}


volatile bool bFlashState = false;

void TurnOnFlash(void) {
    bFlashState = true;
    SetBit(FLASHCTRL);
}

void TurnOffFlash(void) {
    bFlashState = false;
    ClrBit(FLASHCTRL);
}



// Segment Multiplexer - Timer 0 output compare interrupt service routine

ISR(TIMER0_OVF_vect) {  // Segment Multiplexer - Timer0

    static unsigned char iSegmentToogle = 1;

    iSegmentToogle = iSegmentToogle << 1;
    if (iSegmentToogle > 0x40) {
        iSegmentToogle = 1;
    } // endif

    // Reset counter 
    TCNT0 = 0;

    // Turn on segments
    PORTA = Column[0] | ~iSegmentToogle;
    PORTC = Column[1] | ~iSegmentToogle;

    if (OCR0 < 8) { // Check/wait here and turn off segments for Intensity level = 1-3
        while (TCNT0 < OCR0) {} // endwhile

        // Switch off all segments
        PORTA = 0xFF;
        PORTC = 0xFF;

    } // endif

    typedef enum {
        SEGMENTS,
        FLASH,
        BATTERY,
    } t_adcstate;

    static t_adcstate ADCState = SEGMENTS;

    // If we have a MUX change then please let it settle
    static unsigned char LastADCMUX;
    if (ADMUX != LastADCMUX) {
        LastADCMUX = ADMUX;
        return;
    } // endif

    // Hack to make sure that we get to read ALL the segment currents
    static unsigned char SegmentCount;


    // Get the ADC reading
    unsigned short int AdcValue = ADCW;

    switch (ADCState) {
    case SEGMENTS:
        if (Column[0] == 0xFF && Column[1] == 0xFF) {
            // No segments was on
            iAD_BG_Segment_Current = AdcValue;

            // Setup to measure flash current
            ADMUX = 1 | ADC_VREF_TYPE;
            ADCState = FLASH;
            break;
        } // endif

        // We've just turned on a new segment but the ADC reading has to do with the previous one
        switch (iSegmentToogle) {
        case 0x01:
            iAD_Segment[6] = AdcValue; break;
        case 0x02:
            iAD_Segment[0] = AdcValue; break;
        case 0x04:
            iAD_Segment[1] = AdcValue; break;
        case 0x08:
            iAD_Segment[2] = AdcValue; break;
        case 0x10:
            iAD_Segment[3] = AdcValue; break;
        case 0x20:
            iAD_Segment[4] = AdcValue; break;
        case 0x40:
            iAD_Segment[5] = AdcValue; break;
        } // endswitch

        if (SegmentCount++ > 10) {
            SegmentCount = 0;

            // Setup to measure flash current
            ADMUX = 1 | ADC_VREF_TYPE;
            ADCState = FLASH;
        } // endif
        break;

    case FLASH:
        if (bFlashState) {
            iAD_Flash_Current = AdcValue;
        } else {
            iAD_BG_Flash_Current = AdcValue;
        } // endif

        // Setup to measure battery
        ADMUX = 2 | ADC_VREF_TYPE;
        ADCState = BATTERY;
        break;

    case BATTERY:
        iAD_Batteri_Current = AdcValue;

        // Setup to measure segment current when we start again
        ADMUX = 0 | ADC_VREF_TYPE;
        ADCState = SEGMENTS;
        break;

    } // endswitch

    

    // Start new ADC conversion
    ADCSRA |= (1 << ADSC);

}

ISR(TIMER0_COMP_vect) {

    // Switch off all segments
    PORTA = 0xFF;
    PORTC = 0xFF;
}

ISR(INT7_vect) {
    // This interrupt is triggered on PORTE.7 (IRQ7) on positive transitions!
}


void HandleFlash(void)
{
    typedef enum {
        IDLE,
        ON,
        OFF,
    } t_state;

    static t_state state = IDLE;

    bool Speeding = (GetDisplaySpeed() > iShowFlash); 

    static TimeStamp<t_SystemTimer> Timer;

    switch (state) {
    case IDLE: 
        if (Speeding) {
            state = ON;

            // ON for 12ms ? 
            Timer.Mark(12);
            TurnOnFlash();
        } // endif
        break;

    case ON:
         
        if (!Timer.TimeOut()) return;
        TurnOffFlash();
        state = OFF;

        // wait
        Timer.Mark(500);
        break;

    case OFF:
        if (!Timer.TimeOut()) return;
        state = IDLE;
    } // endswitch

    

}


TimeStamp<t_SystemTimer> ShowSpeedTimer;
TimeStamp<t_SystemTimer> LuxTimer;

int main(void) {

    DebugUart.Init();


    // Legacy init will kill SystemTimer
    init();

    SystemTimer.Init();

    // IO setup
    SetBitDirOut(HB_LED);
    SetBitDirOut(TXD0);
    SetBitDirOut(TXD1);
    SetBitDirOut(GPIO_0);
    SetBitDirOut(GPIO_1);

    ClrBit(FLASHCTRL);
    SetBitDirOut(FLASHCTRL);


    SetBitDirIn(RXD0);
    SetBitDirIn(RXD1);

    // Enable ints for the first time
    sei();
   

    TimeStamp<t_SystemTimer> CheckTimer;
    TimeStamp<t_SystemTimer> LumTimer;
    TimeStamp<t_SystemTimer> HBledTimer;
    TimeStamp<t_SystemTimer> HBinfTimer;
    TimeStamp<t_SystemTimer> AdcTimer;

    ProtoReply("*** BOOT ***\n");
    ProtoReply("# HB: %d Start...\n", 42);

    SetDisplayIntensity(7);

    while (1) {

        PETDOG;

        //__________ COMM Handler  and  Ready HB  and  A/D Measurement __________________

        CommandHandler();

        HandleFlash();


        // Turn off after xx second if 
        if (iShowTimeOut > 0 && ShowSpeedTimer.TimeOut()) {
            SetDisplaySpeed(0);  
        } // endif

        if (LuxTimer.Update(100)) {
            unsigned int Tmp;

            // Get value and clear counter 
            Tmp = TCNT3;
            TCNT3 = 0;  

            if (fregistercount++ > 9) fregistercount = 0;   // Make sure counter is occasionally reset

            if (Tmp > 6553) Tmp = 6553;         // Adjust measured frequency to max. value (uint/10) that can be handled by getLux()

                                                // Primary light sensor
            fregister0[fregistercount] = Tmp;   // Put in the measured frequency in the rolling array
            fregister0[10] = Tmp;               // allways keep the last measurement at index 10

            //if (fregistercount == 3) {          // Debug! Monitor light sensor frequency (count at index 3) ...
            //ProtoReply("Tmp3: %u\n", Tmp);
			//} // endif

        } // endif


        // Update HB-Led @ 3s interval
        if (HBledTimer.Update(1000 * 3L)) {
            //Debug ProtoReply("HBledTimer=3s\n");
            HB_Led_Toggle();
        } // endif


        if (CheckTimer.Update(1000 * 10L)) {
            //Debug ProtoReply("CheckTimer=10s\n");

            //__ LUM Handler  ___________________
            if (bAutoPWM == 1 && GetDisplaySpeed() < iShowFlash) {   //aut. lum. regulation selected

                //if time for regulating PWMregulating
                if (LumTimer.Update(2000 * 100L)) {
                    //Debug ProtoReply("LumTimer=200s\n");
                    TurnOffFlash();
                    LumHandler(true);
                } // endif
            } // endif

        } // endif


        // Output HB info. @ 180s interval
        if (HBinfTimer.Update(1000 * 180L)) {
            //Debug ProtoReply("HBinfTimer=180s\n");
            ProtoReply("#HB: %lu S=%d T=%d F=%d L=%u\n", SystemTimer.TimerVal()/1000, GetDisplaySpeed(), iShowTimeOut, iShowFlash, LUX_VALUE);
        } // endif


        // Output ADC current measurements @ 300s interval
        if (AdcTimer.Update(1000 * 300L)) {
            //Debug ProtoReply("AdcTimer=300s\n");
            // Der må IKKE ændres i syntax printf, bruges af SID88
            ProtoReply("$AD: FC=%d BC=%d\n", iAD_Flash_Current, iAD_Batteri_Current);
            ProtoReply("$BG: SC=%d FC=%d \n", iAD_BG_Segment_Current, iAD_BG_Flash_Current);
            ProtoReply("$SC: %d %d %d %d %d %d %d \n", iAD_Segment[0], iAD_Segment[1], iAD_Segment[2], iAD_Segment[3], iAD_Segment[4], iAD_Segment[5], iAD_Segment[6]);
        } // endif

    } // endwhile
    
}


void ProtoReply(const char *fmt, ...) {
    static char str[101];

    va_list args;
    va_start(args, fmt);
    vsnprintf(str, 100, fmt, args);
    va_end(args);
    str[100] = 0;   // JIC
    t_DebugUart::Puts(str);
}


//*************************************************************************
//*** CommandHandler
//***
//*** Kommandoer start med *
//*** Response start med * + OK / ERROR / UNKOWN

void CommandHandler(void) {


    FIXME(Do a timeout on the buffer);
    FIXME(Handle all chars in one pass);

    // Check for incomming chars
    unsigned int ch = t_DebugUart::Getc();
    if (ch == t_DebugUart::NO_DATA) return;

    static unsigned int BufIndex = 0;
    static char rxpacketbuf[MAX_PACKET_SIZE];

    // See if terminating char
    if (ch != '\r' && ch != '\n') {

        // Check if receive buffer is filled...
        if (BufIndex == MAX_PACKET_SIZE) {
            BufIndex = 0;
            return;
        } // endif

        // Insert char
        rxpacketbuf[BufIndex++] = ch & 0xFF;
        return;
    } // endif

    // Terminate buffer
    rxpacketbuf[BufIndex] = 0;
    BufIndex = 0;

    switch (rxpacketbuf[0]) {
    case '*':
        int x;
        switch (rxpacketbuf[1]) {

        case 'f':   
            x = iShowFlash;
            ProtoReply("*f SpeedLimitFlash=%d [kmt]\n", x);
            break;

        case 'l':  
            x = GetDisplayIntensity();
            if ( bAutoPWM == 1 ) {        
                snprintf(txtInfo, 100, "*l Lum=%d (AutoPWM)", x);
            }    
            else {     
                snprintf(txtInfo, 100, "*l Lum=%d", x);
            }
            ProtoReply("%s\n", txtInfo);
            break;    

        case 'r':
            if (strcmp(rxpacketbuf,"*reboot") == 0) {
                ProtoReply("OK\n");
                delay(100);
                Reboot();
            } else {
                ProtoReply("*UNKNOWN %s\n", rxpacketbuf);
            } // endif
            break;

        case 's':
            x = GetDisplaySpeed();
            ProtoReply("*s Speed=%d [kmt]\n", x);
            break;

        case 't':
            x = iShowTimeOut;
            ProtoReply("*t Time=%d [1/10sec]\n", x);
            break;

        case 'C':  // Clear Display  
        case 'c':  
            SetDisplaySpeed(0);
            ProtoReply("*C OK\n");
            break;

        case 'F':  // Speed Limit for activating Flash 
            x = GetInteger(rxpacketbuf, 2);
            if (x >= 1 && x <= 99) {
                iShowFlash = x; 
                ProtoReply("*F OK SpeedLimitFlash=%d [kmt]\n", x);
            } else {
                ProtoReply("*F ERROR (1->99) %s\n", rxpacketbuf);
            }
            break;

        case 'H':
        case 'h':
            ShowHelp();
            break;

        case 'L':  // LUM Auto / Manual -> SID88 Light Test  
            if ( strlen(rxpacketbuf) <= 2 ) {        
                snprintf(txtInfo, 100, "*L ERROR (0->100 or A->F) %s", rxpacketbuf);
            }    
            else {     
                x = GetInteger(rxpacketbuf, 2);
                if ( x == -99 ) {        
                    switch (rxpacketbuf[2]) {
                    case 'A':  // Set LUM A -> SID88 Light Test
                        bAutoPWM = 0;
                        SetDisplayIntensity(2);    
                        snprintf(txtInfo, 100, "*LA OK Lum=2");
                        break;
                    case 'B':  // Set LUM B -> SID88 Light Test
                        bAutoPWM = 0;
                        SetDisplayIntensity(4);    
                        snprintf(txtInfo, 100, "*LB OK Lum=4");
                        break;
                    case 'C':  // Set LUM C -> SID88 Light Test
                        bAutoPWM = 0;
                        SetDisplayIntensity(6);    
                        snprintf(txtInfo, 100, "*LC OK Lum=6");
                        break;
                    case 'D':  // Set LUM D -> SID88 Light Test
                        bAutoPWM = 0;
                        SetDisplayIntensity(20);    
                        snprintf(txtInfo, 100, "*LD OK Lum=20");
                        break;
                    case 'E':  // Set LUM E -> SID88 Light Test
                        bAutoPWM = 0;
                        SetDisplayIntensity(100);    
                        snprintf(txtInfo, 100, "*LE OK Lum=100");
                        break;
                    case 'F':  // Set LUM F -> SID88 Light Test
                        bAutoPWM = 0;
                        SetDisplayIntensity(100);    
                        snprintf(txtInfo, 100, "*LF OK Lum=100");
                        break;
                    default:
                        snprintf(txtInfo, 100, "*L ERROR (A->F) %s", rxpacketbuf);
                    }    
                }    
                else {     
                    if ( x == 0 ) {        
                        bAutoPWM = 1;   
                        x = GetDisplayIntensity();
                        snprintf(txtInfo, 100, "*L0 OK Lum=%d (AutoPWM)", x);
                    }    
                    else {     
                        if (x >= 1 && x <= 100) {
                            bAutoPWM = 0;
                            SetDisplayIntensity(x);    
                            snprintf(txtInfo, 100, "*L OK Lum=%d", x);
                        } else {
                            snprintf(txtInfo, 100, "*L ERROR (0->100) %s", rxpacketbuf);
                        }
                    }
                }
            }
            ProtoReply("%s\n", txtInfo);
            break; 

        case 'S':
            x = GetInteger(rxpacketbuf, 2);
            if (x > 0 && x < 100) {
                SetDisplaySpeed(x);
                ShowSpeedTimer.Mark(iShowTimeOut * 100);
                ProtoReply("*S OK Speed=%d [kmt]\n", x);
            } else {
                ProtoReply("*S ERROR (1->99) %s\n", rxpacketbuf);
            }
            break;

        case 'T':
            if ( strlen(rxpacketbuf) <= 2 ) {        
                ProtoReply("*T ERROR (0->600) %s\n", rxpacketbuf);
            }    
            else {     
                x = GetInteger(rxpacketbuf, 2);
                if (x >= 0 && x <= 600) {
                    iShowTimeOut = x; // * 10; // 1/10 sekunder
                    ProtoReply("*T OK Time=%d [1/10sec]\n", x);
                } else {
                    ProtoReply("*T ERROR (0->600) %s\n", rxpacketbuf);
                }
            }
            break;

        case 'V':
        case 'v':
            ProtoReply("*V App: %s Ver: %s\n", PROGRAM_NAME, VERSIONA);
            break;

        case 'X':
            ProtoReply("*X AD OK\n");
            break;

        default:
            ProtoReply("*UNKNOWN %s\n", rxpacketbuf);
        }
        break;
    default:
        ProtoReply("*UNKNOWN command \"%s\"\n", rxpacketbuf);
    }

    return;
}




//*************************************************************************
//*** GetInteger
//***
//*** Konverter delmængde af teksstreng til Int
//***
int GetInteger(char *txt, int iStartPos) {
    int i, iLen, iIsDigit = 1;

    iLen = strlen(txt + iStartPos) + iStartPos;
    for (i = iStartPos; i < iLen; i++) {
        if (txt[i] < 0x30 || txt[i] > 0x39) {
            iIsDigit = 0;
        }
    }
    if (iIsDigit == 1) {
        return atoi(txt + iStartPos);
    } // endif

    return -99;
}



//*************************************************************************
//*** ShowHelp
//***
void ShowHelp(void) {

    FIXME(2 Could just wait for UART and skip delay);

    ProtoReply("*** App: %s\n", PROGRAM_NAME);
    delay_ms(10);
    ProtoReply("*** Ver: %s\n", VERSIONA);
    delay_ms(10);

    ProtoReply("*** Commands: ->\n");
    delay_ms(10);
    ProtoReply("***    *f     Show SpeedLimitFlash\n");
    delay_ms(10);
    ProtoReply("***    *h     Show Help - this\n");
    delay_ms(10);
    ProtoReply("***    *l     Show Luminance\n");
    delay_ms(10);
    ProtoReply("***    *s     Show Speed\n");
    delay_ms(10);
    ProtoReply("***    *t     Show Timeout\n");
    delay_ms(10);
    ProtoReply("***    *v     Show Version\n");
    delay_ms(10);
    ProtoReply("***    *C     Clear Display\n");
    delay_ms(10);
    ProtoReply("***    *Fss   Set SpeedLimitFlash, ss: 1 - 99 kmt\n");
    delay_ms(10);
    ProtoReply("***    *Llll  Set Luminance, lll: 0 (AutoPWM) or 1 - 100 (Fixed level)\n");
    delay_ms(10);
    ProtoReply("***    *LA    Set Luminance, A: 2\n");
    delay_ms(10);
    ProtoReply("***    *LB    Set Luminance, B: 4\n");
    delay_ms(10);
    ProtoReply("***    *LC    Set Luminance, C: 6\n");
    delay_ms(10);
    ProtoReply("***    *LD    Set Luminance, D: 20\n");
    delay_ms(10);
    ProtoReply("***    *LE    Set Luminance, E: 100\n");
    delay_ms(10);
    ProtoReply("***    *LF    Set Luminance, F: 100\n");
    delay_ms(10);
    ProtoReply("***    *Svv   Set Speed, vv: 1 - 99 kmt\n");
    delay_ms(10);
    ProtoReply("***    *Tttt  Set Timeout, ttt: 0 (No timeout) or 1 - 600 1/10sec\n");
    delay_ms(10);
    ProtoReply("***    *X     Start A/D\n");
    delay_ms(10);
    ProtoReply("***    Exe cmd: CR (13)\n");
    delay_ms(10);
    ProtoReply("*** Commands: <-\n");
    delay_ms(10);
    ProtoReply("***     CMD + OK / ERROR / UNKNOWN\n");
    delay_ms(10);
    ProtoReply("*** Info: <-\n");
    delay_ms(10);
    ProtoReply("***     # Information...\n");
    delay_ms(10);
    ProtoReply("*** End\n");
    delay_ms(10);
}


unsigned int CurrentSpeed = 0;
//*************************************************************************
//*** Show Speed på display
//*** Convert int to 7-Segment code
void SetDisplaySpeed(unsigned int Speed) {
    int A, B;
    char txtInt[3];

    CurrentSpeed = Speed;

    snprintf(txtInt, 3, "%d", Speed);
    A =  txtInt[0] - 48;
    B =  txtInt[1] - 48;

    if (Speed > 9  && Speed <= 99) {
        Column[0] = SegCode[A];
        Column[1] = SegCode[B];
    }    else if (Speed <= 0 || Speed > 99) {
        Column[0] = SegCode[10];
        Column[1] = SegCode[10];
    } else if (Speed <= 9) {
        Column[0] = SegCode[10];
        Column[1] = SegCode[A];
    } // endif
  

}

unsigned int GetDisplaySpeed(void) {
    return CurrentSpeed;
}



//*************************************************************************
//*** Get LUX til Lum Handler
float getLux(uchar sensornumber) {
    //returns the amount of light on the sign (in lux)
    float a, b, c, d;
    float meanfreq = 0;

    if (sensornumber == 0) {
        meanfreq += fregister0[0];
        meanfreq += fregister0[1];
        meanfreq += fregister0[2];
        meanfreq += fregister0[3];
        meanfreq += fregister0[4];
        meanfreq += fregister0[5];
        meanfreq += fregister0[6];
        meanfreq += fregister0[7];
        meanfreq += fregister0[8];
        meanfreq += fregister0[9];
        // now we have the sum of ten tenth of a second = real frequency
        a = meanfreq;
        b = a * (float)LFC_FDIV_0;                                                                //real frequency
        c = b * LFC_FACTOR_0;
        d = c * ((100.0 + LFC_TFP_0) / 100.0);
        return (d);
    }
    if (sensornumber == 1) {
        meanfreq += fregister1[0];
        meanfreq += fregister1[1];
        meanfreq += fregister1[2];
        meanfreq += fregister1[3];
        meanfreq += fregister1[4];
        meanfreq += fregister1[5];
        meanfreq += fregister1[6];
        meanfreq += fregister1[7];
        meanfreq += fregister1[8];
        meanfreq += fregister1[9];
        // now we have the sum of ten tenth of a second = real frequency
        a = meanfreq;
        b = a * (float)LFC_FDIV_1;                                                            //real frequency
        c = b * LFC_FACTOR_1;
        d = c * ((100.0 + LFC_TFP_1) / 100.0);
        return (d);
    }

    return 0;
}


//*************************************************************************
//*** Luminance Handler
//*** Overordnet handler.
//*** Håndterer luminansregulering. Sørger for automatisk regulering hvis dette ikke er disabled. Justerer PWM til manuelt valgt niveau hvis manuel justering er valgt.
// pwmregulate(YES);
void LumHandler(bool maxchangeon)	{
    //Aut. PWM regulation
    float lux;
    float a, b, c, d;
    float temp;
    //static uchar i;
    //int min, max;
    //char str[50];

    if (bAutoPWM == 0) {                              //manual mode- nogen tror bare de er bedre...
        SetDisplayIntensity(PWMmanfactor);
        ProtoReply("LumHandler (MANUAL):  PWMAVALUE:%d PWMBVALUE:%d\0", (int)PWMmanfactor, (int)PWMmanfactor);
        return;
    } // endif

    lux  = getLux(0);                               //retrieve the amount of light on the sign prom primary sensor

//#ifdef SECSENSORUSED
//	lux1 = getlux(1);								//retrieve the amount of light on the sign from secondary sensor
//    if(lux1>lux) lux = lux1;						//choose the highest value
//#endif

    //formula is: pwm_factor =  LUM_SIGN_MAX / ((b*lx^a)*(100+LUM_TFP/100.0)) * PWMPERIODS;
    //                                       "cd/m2" * "filterfactor"
    a = LUM_ILLUM_B * (pow(lux, LUM_ILLUM_A));
    b = (100.0 + LUM_TFP) / 100.0;
    c = a * b;                        //now c = cd/m2
    if (c < LUM_SIGN_MIN) {
        c = LUM_SIGN_MIN;               //make sure allways a little on
    }

    d = c / LUM_SIGN_MAX;                   //get the factor
    temp = d * PWMPERIODS;                  //how many periods out of total PWMPERIODS
    if (temp > PWMPERIODS) {
        temp = PWMPERIODS;          //make sure no overflow
    }

    if (PWMfactormin > temp) temp = PWMfactormin;     //make sure we use the programmed minimum
    if (PWMfactormax < temp) temp = PWMfactormax;     //make sure we use the programmed maximum

    // Another hack 
    if (temp < 7) {
        temp = 7;
    } // endif
    SetDisplayIntensity(temp);
    
    LUX_VALUE = (uint)lux;

    ProtoReply("LumHandler: LUX=%u PWM=%d\n", LUX_VALUE, (int)GetDisplayIntensity());
}


//*** Toggle HB Led
void HB_Led_Toggle(void) {
    static bool Toggle = false;
    if (Toggle) {
        SetBit(HB_LED);
    } else {
        ClrBit(HB_LED);
    } // endif
    Toggle = !Toggle;
}


unsigned char gIntensity; 

void SetDisplayIntensity(unsigned char Intensity)
{

    gIntensity = Intensity;

    FIXME(1a); 
    // In the original code intensity was a number 0-80 -> Changed to 0-100! 
    // Now we have 255 levels so scale it !!

    if (Intensity == 2) {  // Fix to reduce 7-segment pulse width @ intensity 2 (5 to 4 counts)
        OCR0 = 4;
    } else {
        OCR0 = ((unsigned int)Intensity*255)/100;
    } // endif

}

unsigned int GetDisplayIntensity(void)
{
    return gIntensity;

}

