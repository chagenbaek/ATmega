//$Id: StreamBase.h 1.5 2013/10/28 11:36:12 jacob tnt $
//$Log: StreamBase.h $
//Revision 1.5  2013/10/28 11:36:12  jacob
//Added support for parity, stop bit etc,
//Revision 1.4  2011/12/13 12:07:56  jacob
//Added empty functions
//Revision 1.3  2010/06/01 06:26:34  Peter
//Renamed back
//Revision 1.2  2010/04/21 05:36:18  Peter
//Renamed enums due to FAIL define
//Revision 1.1  2010/01/09 13:44:13  Administrator
//Initial revision

#ifndef __STREAMBASE_H__
#define __STREAMBASE_H__


class StreamBase
{
public:
    enum {
        PARITY_ERROR     = 0x1000,
        FRAME_ERROR      = 0x0800,              // Framing Error by UART    
        OVERRUN_ERROR    = 0x0400,              // Overrun condition by UART hardware 
        BUFFER_OVERFLOW  = 0x0200,              // receive ringbuffer overflow
        FAIL             = (BUFFER_OVERFLOW | OVERRUN_ERROR | FRAME_ERROR | PARITY_ERROR),
        NO_DATA          = 0x0100              // No receive data available
    };

    static void DeInit(void) {};
    static void Idle(void) {};
    static void TxSubmit(void) {};

    // First 2 bits 
    typedef enum {
        PAR_NONE = 0,
        PAR_ODD  = 1,
        PAR_EVEN = 2,
    } t_paritet;

    typedef enum {
        STOP_1   = 0 << 2,
        STOP_2   = 1 << 2
    } t_stopbits;

    typedef enum {
        DATA_8  = 0 << 3,
        DATA_5  = 1 << 3,
        DATA_6  = 2 << 3,
        DATA_7  = 3 << 3,
        DATA_9  = 4 << 3
    } t_databits;


};

#endif 

