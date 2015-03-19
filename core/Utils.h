#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <sstream>

template<typename T>
std::string ttos( T t )
{
   std::stringstream ss;
   std::string s;
   if(ss << t){
   ss >> s;
   return s;
   }
   return "";
}

template <typename T>
T stot( std::string s )
{
    std::stringstream ss( s );
    T t;
    ss >> t;
    return t;
}

#endif // UTILS_H
