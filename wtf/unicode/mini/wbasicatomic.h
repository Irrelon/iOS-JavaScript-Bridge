

#ifndef __WBASICATOMIC_H__
#define __WBASICATOMIC_H__


class WBasicAtomicInt
{
public:

    volatile int _q_value;


    // Non-atomic API
    inline bool operator==(int value) const
    {
        return _q_value == value;
    }

    inline bool operator!=(int value) const
    {
        return _q_value != value;
    }

    inline bool operator!() const
    {
        return _q_value == 0;
    }

    inline operator int() const
    {
        return _q_value;
    }

    inline WBasicAtomicInt &operator=(int value)
    {
        _q_value = value;
        return *this;
    }

    bool ref();
    bool deref();

};

#endif