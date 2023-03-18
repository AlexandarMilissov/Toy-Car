#ifndef PS_CONTROLLER_WRAPPER
#define PS_CONTROLLER_WRAPPER


#if defined(PS_5)
    #include "ps5.h"
    #define psInit ps5Init
    #define psSetEventCallback ps5SetEventCallback
    #define ps_t ps5_t
    #define ps_event_t ps5_event_t
#elif defined(PS_4)
    #include "ps4.h"
    #define psInit ps4Init
    #define psSetEventCallback ps4SetEventCallback
    #define ps_t ps4_t
    #define ps_event_t ps4_event_t
#elif defined(PS_3)
    #include "ps3.h"
    #define psInit ps3Init
    #define psSetEventCallback ps3SetEventCallback
    #define ps_t ps3_t
    #define ps_event_t ps3_event_t
#else
    #error "Wrong Controller Model Selected!"
#endif

#endif