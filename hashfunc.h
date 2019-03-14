#ifndef HASHFUNC_H_INCLUDED
#define HASHFUNC_H_INCLUDED

typedef unsigned int uint;

template<typename T>
struct HashFunc
{
    uint operator()(const T& key) = 0;
};

#endif // HASHFUNC_H_INCLUDED
