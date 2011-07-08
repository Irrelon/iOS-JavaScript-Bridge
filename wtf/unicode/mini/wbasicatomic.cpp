#include "Platform.h"
#include "wbasicatomic.h"

#if PLATFORM(IOS_SIMULATOR)
bool WBasicAtomicInt::ref()
{
    unsigned char ret;
    asm volatile("lock\n"
                 "incl %0\n"
                 "setne %1"
                 : "=m" (_q_value), "=qm" (ret)
                 : "m" (_q_value)
                 : "memory");
    return ret != 0;
}

bool WBasicAtomicInt::deref()
{
    unsigned char ret;
    asm volatile("lock\n"
                 "decl %0\n"
                 "setne %1"
                 : "=m" (_q_value), "=qm" (ret)
                 : "m" (_q_value)
                 : "memory");
    return ret != 0;
}
#else

bool WBasicAtomicInt::ref()
{
    register int newValue;
    register int result;
    asm volatile("0:\n"
                 "ldrex %[newValue], [%[_q_value]]\n"
                 "add %[newValue], %[newValue], #1\n"
                 "strex %[result], %[newValue], [%[_q_value]]\n"
                 "teq %[result], #0\n"
                 "bne 0b\n"
                 : [newValue] "=&r" (newValue),
                 [result] "=&r" (result),
                 "+m" (_q_value)
                 : [_q_value] "r" (&_q_value)
                 : "cc", "memory");
    return newValue != 0;
}

bool WBasicAtomicInt::deref()
{
    register int newValue;
    register int result;
    asm volatile("0:\n"
                 "ldrex %[newValue], [%[_q_value]]\n"
                 "sub %[newValue], %[newValue], #1\n"
                 "strex %[result], %[newValue], [%[_q_value]]\n"
                 "teq %[result], #0\n"
                 "bne 0b\n"
                 : [newValue] "=&r" (newValue),
                 [result] "=&r" (result),
                 "+m" (_q_value)
                 : [_q_value] "r" (&_q_value)
                 : "cc", "memory");
    return newValue != 0;
}
#endif
