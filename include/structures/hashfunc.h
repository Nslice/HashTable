#ifndef HASHFUNC_H_INCLUDED
#define HASHFUNC_H_INCLUDED

#include <QString>
#include <string>
#include "include/aliases.h"


namespace slice {


template<typename T>
struct Hash final
{
    Hash() = delete;
    uint operator()(const T& key, uint tableSize) const;
};



template<>
struct Hash<std::string> final
{
    uint operator()(const std::string& key, uint tableSize) const
    {
        uint _hash = 0;
        uint a = 127;
        for (uint i = 0, length = key.length(); i < length; ++i)
        {
            _hash = (a * _hash + static_cast<uint>(key[i])) % tableSize;
        }
        return _hash;
    }
};



template<>
struct Hash<QString> final
{
    uint operator()(const QString& key, uint tableSize) const
    {
        uint _hash = 0;
        uint a = 127;
        for (uint i = 0, length = key.length(); i < length; ++i)
        {
            _hash = (a * _hash + static_cast<uint>(key[i].unicode())) % tableSize;
        }
        return _hash;
    }
};



template<>
struct Hash<int> final
{
    uint operator()(int key, uint tableSize) const
    {
        return static_cast<uint>(key) % tableSize;
    }
};



template<>
struct Hash<double> final
{
    quint64 operator()(double key, uint tableSize) const
    {
        data.input = key;
        return ((data.output >> SHIFT) | (data.output << SHIFT)) % tableSize;
    }

private:
    static const short SHIFT = sizeof(double) * 8 / 2;

    union
    {
        double input;
        quint64 output;
    } mutable data;
};



template<>
struct Hash<float> final
{
    uint operator()(float key, uint tableSize) const
    {
        data.input = key;
        return ((data.output >> SHIFT) | (data.output << SHIFT)) % tableSize;
    }

private:
    static const short SHIFT = sizeof(float) * 8 / 2;

    union
    {
        float input;
        uint output;
    } mutable data;
};

} // end of namespace "slice"


#endif // HASHFUNC_H_INCLUDED
