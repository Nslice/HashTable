#ifndef HASHFUNC_H_INCLUDED
#define HASHFUNC_H_INCLUDED

#include <string>
#include "aliases.h"


template<typename T>
struct Hash final
{
    Hash() = delete;
    uint operator()(const T& key) const;
};



// TODO у Седжвика посмортеть как реализовать
template<>
struct Hash<std::string>
{
    // TODO арифм. переполнение исправить, есть вариант с помощью XOR, SHL, SHR.
    uint operator()(const std::string& key) const
    {
        uint _hash = 0;
        uint a = 127;
        for (size_t i = 0, length = key.length(); i < length; ++i)
        {
            _hash = (a * _hash + static_cast<uint>(key[i]));
        }
        return _hash;
    }
};



template<>
struct Hash<int>
{
    uint operator()(int key) const
    {
        return static_cast<uint>(key);
    }
};



template<>
struct Hash<double>
{
    ulong operator()(double key) const
    {
        data.input = key;
        return (data.output >> shift) | (data.output << shift);
    }

private:
    const short shift = sizeof(double) * 8 / 2;

    mutable union
    {
        double input;
        ulong output;
    } data;
};



template<>
struct Hash<float>
{
    uint operator()(float key) const
    {
        data.input = key;
        return (data.output >> shift) | (data.output << shift);
    }

private:
    const short shift = sizeof(float) * 8 / 2;

    mutable union
    {
        float input;
        uint output;
    } data;
};



#endif // HASHFUNC_H_INCLUDED
