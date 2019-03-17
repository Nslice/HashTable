#ifndef MY_OWN_ALIASES_H_INCLUDED
#define MY_OWN_ALIASES_H_INCLUDED

#include <cstddef>
#include <string>

#include <boost/stacktrace.hpp>
#include <boost/exception/all.hpp>



typedef std::byte byte;
typedef unsigned int uint;
typedef unsigned long long ulong;



#define s std::string()+
#define _(x) std::to_string(x)

#define FNAME __PRETTY_FUNCTION__
#define SNAME __func__





// TODO не работает Boost.StackTrace
typedef boost::error_info<struct tag_stacktrace, boost::stacktrace::stacktrace> traced;

template <class E>
void throw_with_trace(const E& e)
{
    throw boost::enable_error_info(e) << traced(boost::stacktrace::stacktrace());
}


#endif // MY_OWN_ALIASES_H_INCLUDED
