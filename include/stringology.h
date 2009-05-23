#ifndef _STRINGOLOGY_H_
#define _STRINGOLOGY_H_

#include <string>

std::string tolower( const std::string& s );

int naive_edit_distance( const std::string& a,
                         const std::string& b,
                         int ch_cost = 2,
                         int ins_cost = 1,
                         int del_cost = 1 );



#endif // _STRINGOLOGY_H_
