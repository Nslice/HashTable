#ifndef MY_OWN_ALIASES_H_INCLUDED
#define MY_OWN_ALIASES_H_INCLUDED

#include <cstddef>
#include <string>



typedef std::byte byte;
typedef unsigned int uint;
typedef unsigned long long ulong;



#define s std::string()+
#define _(x) std::to_string(x)

#define FNAME __PRETTY_FUNCTION__
#define SNAME __func__



#endif // MY_OWN_ALIASES_H_INCLUDED
