// $Id: containers.h 1.56 2014/07/18 09:50:29 jacob tnt $
// $Log: containers.h $
// Revision 1.56  2014/07/18 09:50:29  jacob
// Stopped including log.h
// Revision 1.55  2014/01/08 16:20:14  jacob
// Added PeekAt and Peek into a std::vector
// Added unittest code - tent 
// Revision 1.54  2013/03/15 14:57:54  jacob
// Added fix for undefined protect class
// Revision 1.53  2013/03/15 09:40:28  jacob
// STM32 fix
// Revision 1.52  2013/02/18 17:50:40  jacob
// Added some STM32 support
// Revision 1.51  2011/03/23 12:05:22  Peter
// EMU is using CScopeCli as ProtectClass
// Revision 1.50  2011/03/03 22:15:46  jacob
// Fixes related to V3 terminal
// Revision 1.49  2011/03/02 13:13:23  jacob
// Added GetFront function
// Revision 1.48  2011/03/01 16:31:22  jacob
// Comment FIX
// Revision 1.47  2011/03/01 15:02:12  jacob
// Warn fix under WIN32
// Revision 1.46  2011/02/28 15:21:19  jacob
// minor WIN32 fix 
// Revision 1.45  2011/02/27 20:16:31  jacob
// Removed the static define and added a WARNING DO READ 
// Revision 1.44  2011/02/22 23:41:10  jacob
// Added protection under NIOS !!!
// Revision 1.43  2011/02/08 10:04:44  jacob
// Added Peek
// Revision 1.42  2011/01/18 16:34:17  jacob
// Removed old queue
// Revision 1.41  2010/10/21 12:08:23  jacob
// Minor optimization
// Revision 1.40  2010/09/02 05:57:13  Peter
// STATIC not working as intended - Do not use
// Revision 1.39  2010/08/30 21:31:45  jacob
// Minimize queue by making members static - seems to work
// Revision 1.38  2010/08/30 09:21:15  jacob
// Added a ProtectionPolicy 
// Revision 1.37  2010/08/23 11:33:53  jacob
// Stopped including string,h 
// Avrutils only included under AVR
// Revision 1.36  2010/08/11 15:09:10  Johan
// worked to integrate modules and pc comm with head unit code (in progress)
// Revision 1.35  2010/03/12 13:00:39  jacob
// Now size of queue is accessible 
// Revision 1.34  2010/03/09 13:28:57  jacob
// Warning fix under win32
// Revision 1.33  2010/03/01 07:32:21  jacob
// Insert in SimpleQueue now returns a bool
// Revision 1.32  2010/02/15 17:20:31  jacob
// AVR specifics ifdef'ed
// Revision 1.31  2010/01/14 10:51:17  jacob
// Added IsFull to simplequeue 
// Typecasted default value in Queue to avoid warning
// Revision 1.30  2010/01/09 13:37:34  Administrator
// Added GetCount to simplequeue
// Revision 1.29  2009/12/17 17:11:55  jacob
// SimpleLog now included
// Revision 1.28  2009/12/08 14:42:31  jacob
// Do not include target.h 
// Revision 1.27  2009/11/02 11:32:29  Peter
// Now including target
// Revision 1.26  2009/10/19 09:10:53  jacob
// Stopped including log.h
// Revision 1.25  2009/06/23 11:39:01  jacob
// Need to include log.h
// Revision 1.24  2008/10/20 10:57:27  jacob
// Uses SCOPE_CLI
// Revision 1.23  2007/01/30 05:51:34  jacob
// Fix that makes it compile under WIN32 too
// Revision 1.22  2006/11/01 12:39:48  jacob
// Added support for NV containers
// Revision 1.21  2006/04/19 11:56:25  Jacob
// Head and Tail pointers are now volatile
// Revision 1.20  2006/03/21 21:26:07  Jacob
// Backup
// Revision 1.19  2006/03/07 09:29:38  Jacob
// Added GetPrev and fixed bugs in MoveOldest and Newest
// Revision 1.18  2005/11/30 12:09:45  Jacob
// Memory is now staically allocated - not using malloc
// Revision 1.17  2005/11/13 00:14:28  Jacob
// NIOS2 Backup
// Revision 1.16  2005/07/01 13:44:41  Jacob
// Added Size and Improved GetCount for Queue
// Revision 1.15  2005/06/12 15:09:39  Jacob
// Backup
// Revision 1.14  2005/06/03 08:19:35  Jacob
// Added a HasWrapped function - untested
// Revision 1.13  2005/04/28 12:14:00  Jacob
// backup
// Revision 1.12  2005/03/28 11:25:07  Jacob
// Backup
// Revision 1.11  2005/03/20 13:26:38  Jacob
// Fixed warning
// Revision 1.10  2005/03/01 01:55:35  Jacob
// Revised cli-sti usage to use a real version because debug printf uses this code too
// 
// Revision 1.9  2005/02/14 09:18:14  Jacob
// Fixed amazing error with index versus Index 
// Revision 1.8  2005/02/11 13:04:57  Jacob
// Now uses the PURE STI-CLI functions
// Revision 1.7  2004/12/29 00:40:52  Jacob
// Backup
// Revision 1.6  2004/12/16 23:35:42  Jacob
// Added a get function to the queue 
// Revision 1.5  2004/12/15 08:50:03  Jacob
// Added a flush func and a flag that prevents logging QUEUE_NOLOG
// Revision 1.4  2004/12/09 17:59:46  Jacob
// Backup
// Revision 1.3  2004/12/02 22:23:01  Jacob
// Renamed file from stack 
// Revision 1.2  2004/11/26 22:42:43  Jacob
// Backup seems to work 
// Revision 1.1  2004/07/27 12:57:36  Jacob
// Initial revision

/* $$Contents 
This header file contains the definitions of the structures used in the 
terminal for handling and storing a font and the API functions to load it.
*/


#pragma once 

#include "CommonSupport.h"


/*
#if defined(NIOS)
    extern "C" {void alt_dcache_flush (void* start, alt_u32 len);};
#else
    #define alt_dcache_flush(x,y)
#endif 
*/ 

// ********* Defines a STACK ****************
template <typename T>
class Stack
{
public:
	Stack(int StackSize) ; 
	~Stack() { delete [] stackPtr ; }
	int push(const T&); 
	int pop(T&) ;  // pop an element off the stack
	int isEmpty()const { return top == -1 ; } 
	int isFull() const { return top == size - 1 ; } 
    T& operator () (int index);

private:
	int size ;  // Number of elements on Stack
	int top ;  
	T* stackPtr ;  
} ;

//constructor with the default size 10
template <typename T>
Stack<T>::Stack(int StackSize)
{
	size = StackSize;
	top = -1 ;  // initialize stack
	NEWPROTECT(stackPtr = new T[size] ) ;  // moved semi-colon to avoid error msg (???)

}
 // push an element onto the Stack 
template <typename T>
int Stack<T>::push(const T& item)
{
	if (!isFull())
	{
		stackPtr[++top] = item ;
		return 1 ;  // push successful
	}
	return 0 ;  // push unsuccessful
}

// pop an element off the Stack
template <typename T>
int Stack<T>::pop(T& popValue) 
{
	if (!isEmpty())
	{
		popValue = stackPtr[top--] ;
		return 1 ;  // pop successful
	}
	return 0 ;  // pop unsuccessful
}


/*
template <typename T>
T& Stack<T>::operator () (T& popValue) 
{
	if (!isEmpty())
	{
		popValue = stackPtr[top--] ;
		return 1 ;  // pop successful
	}
	return 0 ;  // pop unsuccessful
}
*/


// ********* Defines a QUEUE ****************
#define QUEUE_WRAP      0x0001              // Just roll around overwriting the oldest members
#define QUEUE_CLISTI    0x0002              // Protect this queue  
#define QUEUE_NOLOG     0x0004              // DO NOT LOG - important for the log functions using this QUEUE
#define QUEUE_NOINIT    0x0008              // Do not initialize 
#define QUEUE_FLUSH     0x0010              // Bypass cache
#define QUEUE_NO_INSERT_CLISTI      0x0020              // Do not protect queue insertion (usually because it happens from within an interrupt)

template <int v>
struct Int2Type_x {
    enum {value = v};
};


class protect 
{
    unsigned char sreg; 
public:
#if defined(AVR)
    protect()  {sreg = SREG; cli();}
    ~protect() {SREG = sreg;}
#elif defined(WIN32)
    // WIN32 protection 
    protect()  {}
    ~protect() {}
#else
    protect()  {asm("bug");}
    ~protect() {}
    //#error "GOT TO SUPPORT THIS"
#endif 
};

class noprotect 
{
public:
    noprotect()  {}
    ~noprotect() {}
};

template <typename P>
class ProtectionSelector
{
};

template <> class ProtectionSelector<Int2Type_x<0> >
{
public: 
    typedef class noprotect ProtectClass;

};

template <> class ProtectionSelector<Int2Type_x<1> >
{
public: 
#if defined (AVR)
    typedef class protect ProtectClass;
#elif defined (_STM32x_)
    typedef class CScopeCli ProtectClass;
#elif defined (NIOS2)
    typedef class CScopeCli ProtectClass;
#elif defined (WIN32)
    #if defined (EMU) // Using CScopeCli in EMU
        typedef class CScopeCli ProtectClass;
    #else // No protection!
        typedef class noprotect ProtectClass;
    #endif
#else 
    #error "Target needed"
#endif 


};


// Used to determine a suitable type for the index vars  
template <bool SIZE>
class IndexTypeSelector
{
public: 
    typedef unsigned int HeadTailType;
};

template <> class IndexTypeSelector<true>
{
public: 
    typedef unsigned char HeadTailType;
};


// Standard protection class that acts upon the flags - for compability 
template <int FLAGS>
struct DefaultProtect 
{
public: 
    typedef typename ProtectionSelector<Int2Type_x<(FLAGS & QUEUE_CLISTI) ? (FLAGS & QUEUE_NO_INSERT_CLISTI ? 0 : 1) : 0 > >::ProtectClass  InsertProtectType;
    typedef typename ProtectionSelector<Int2Type_x<(FLAGS & QUEUE_CLISTI) ? 1 : 0 > >::ProtectClass                                         ExtractProtectType;
    typedef typename ProtectionSelector<Int2Type_x<(FLAGS & QUEUE_CLISTI) ? 1 : 0 > >::ProtectClass                                         GeneralProtectType;
};

// Do not protect at all 
struct NoQueueProtect 
{
public: 

    typedef class InsertProtect
    {
    public:
        InsertProtect(){};
        ~InsertProtect(){}
    } InsertProtectType;

    typedef class ExtractProtect
    {
    public:
        ExtractProtect(){};
        ~ExtractProtect(){}
    } ExtractProtectType;

    typedef class GeneralProtect
    {
    public:
        GeneralProtect(){};
        ~GeneralProtect(){}
    } GeneralProtectType;

};

/*
NOTE that this is a STRUCT there's NO constructor 
********* Call flush before uisng it *************
*/
template <typename T, int SIZE, int FLAGS = 0, class Protect = DefaultProtect<FLAGS> >
struct SimpleQueue
{
    FIXME(3 Add check for SIZE - must be a power of 2);
    FIXME(2 See if we can use an unsigned char for sizes <= 256);

    typedef typename IndexTypeSelector<(SIZE <=128) ? true : false >::HeadTailType HeadTailType;

    volatile HeadTailType Head;
    volatile HeadTailType Tail;
    T DataPtr[SIZE];        
    
    typedef typename Protect::InsertProtectType     InsertProtectType;
    typedef typename Protect::ExtractProtectType    ExtractProtectType;
    typedef typename Protect::GeneralProtectType    GeneralProtectType;

    typedef T ContentsType;



public:

    static const HeadTailType Size = SIZE;

bool Insert(const T& item) 
    {

        InsertProtectType dum;

        HeadTailType tmphead = (Head + 1) & (SIZE -1);
        if ( tmphead == Tail ) {
            if (FLAGS & QUEUE_WRAP) {
                Tail = (Tail +1) & (SIZE -1);
            } else {
                return false; 
            } // endif
        } // endif
        Head = tmphead;
        DataPtr[tmphead] = item;
        return true;
    };

void Flush(void) 
    {
        GeneralProtectType dum;
        Head = Tail = 0;  // initialize queue 
        return;
    }

bool Get(T& popValue) 
    {
        if (Head == Tail) return false;

        ExtractProtectType dum;

        HeadTailType tmptail = (Tail + 1) & (SIZE -1);
        Tail = tmptail;
        popValue = DataPtr[tmptail];
        return true;
    }

// Get the last element inserted 
bool GetFront(T& popValue) 
{
    // Its emtpy 
    if (Head == Tail) return false;
    
    ExtractProtectType dum;

    popValue = DataPtr[Head];

    // Now decrement head 
    Head = (Head - 1) & (SIZE -1);
    return true;
}


bool Peek(T& popValue) 
    {
        if (Head == Tail) return false;
        ExtractProtectType dum;
        HeadTailType tmptail = (Tail + 1) & (SIZE -1);
        popValue = DataPtr[tmptail];
        return true;
    }


// pop an element off the Queue returning a pointer to it - BEWARE
T* Get(void) 
    {
        ExtractProtectType dum;

        if (Head == Tail) return NULL;

        HeadTailType tmptail = (Tail + 1) & (SIZE -1);
        Tail = tmptail;
        return &(DataPtr[tmptail]);
    }


HeadTailType GetCount(void) 
    {
        GeneralProtectType dum;

        // Its emtpy 
        if (Head == Tail) return 0;

        HeadTailType i = 0;
        i = (Head > Tail) ? (Head-Tail) : (SIZE-Tail) + Head;
        return i;
    }

bool isEmpty(void) 
    {
        return (Head == Tail);
    }

bool isFull(void) 
    {
        HeadTailType tmphead = (Head + 1) & (SIZE -1);
        return (tmphead == Tail);
    }


// Returns oldest element at index 0
bool PeekAt(HeadTailType Index, T& Val)
    {

        if (GetCount() <= Index) return false;

        GeneralProtectType dum;

        // Oldest element 
        HeadTailType tmptail = (Tail + 1) & (SIZE -1);

        for (HeadTailType n = 0;n < Index;n++) { 
            tmptail = (tmptail + 1) & (SIZE -1);
        } // endfor
        Val = DataPtr[tmptail];
        return true;
    }

#if defined(WIN32)
bool Peek(HeadTailType Count, std::vector<T> &Vect)
    {

        if (GetCount() < Count) return false;

        GeneralProtectType dum;

        // Oldest element 
        HeadTailType tmptail = (Tail + 1) & (SIZE -1);

        for (HeadTailType n = 0;n < Count;n++) {
            Vect.push_back(DataPtr[tmptail]);
            tmptail = (tmptail + 1) & (SIZE -1);
        } // endfor
        return true;
    }

#endif 


};


#if defined(UNITTESTMAIN)

    //UNIT(crc32.cpp)
    //UNIT(Fileutils.cpp)

int main(void)
{

    SimpleQueue<int,16,QUEUE_WRAP> Test;
    Test.Flush();

    for (int i=0;i<17 && !Test.isFull();i++) { 
        Test.Insert(i);
    } // endfor

    int v;

    std::vector<int> Vec;

    for (int i=0;i<16;i++) { 
        
        if (Test.PeekAt(i,v)) {
            log_info("Peek at %i said %i\n", i,v);
        } else {
            log_warn("Peek at %i failed\n", i);
        } // endif
    } // endfor

    if (Test.Peek(16,Vec)) {
        log_info("Vector peek OK %i\n",Vec.size());
        for (std::vector<int>::iterator it= Vec.begin(); it != Vec.end();it++) { 
            log_info("Vector %i\n",*it);
        } // endfor
    } else {
        log_warn("Vector peek failed\n");
    } // endif

    while (Test.Get(v)) {
        log_info("Popped %i\n", v);
    } // endwhile
    

}

#endif
