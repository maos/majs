#ifndef _STRINGOLOGY_H_
#define _STRINGOLOGY_H_

#include <string>
#include <vector>

std::string tolower( const std::string& s );

int lcs( const std::string& a, const std::string& b );
int lis( const std::vector< int >& a );

// simple O( a.size() * b.size() ) dynamics
int naive_edit_distance( const std::string& a,
                         const std::string& b,
                         int ch_cost = 2,
                         int ins_cost = 1,
                         int del_cost = 1 );

// precondition: ch_cost = 2, ins_cost = del_cost = 1;
// O( k * log(k) ) where k = | { (i,j) : a[i] == b[j] } |, Ek = a.size() * b.size() / alphabet_size
int edit_distance( const std::string& a, const std::string& b);

#endif // _STRINGOLOGY_H_
