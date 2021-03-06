#ifndef __singleton_h
#define __singleton_h

template <typename T>
class Singleton {
private:

public:
    static T &getInstance()
    {
        static T instance;
        return instance;
    }
};

#endif
