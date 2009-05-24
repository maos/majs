#ifndef _EVRISTICS_H_
#define _EVRISTICS_H_

#include <map>
#include <string>
#include <stdexcept>

bool nojs( const std::string& script_path );

std::map< std::string, int > load_top( const std::string& top_path, int top_count ) throw (std::runtime_error);

// 0 if not in list
// m.size() - (real place in top) + 1
int search_top( const std::map< std::string, int >& m, const std::string& target );

// good reason to call this is search_top returned 0
// same return logic as in search_top but with - sign.
int search_fishing( const std::map< std::string, int >& m, const std::string& target, int threshold = 2 );

int search_bad_words( const std::string& words_path, const std::string& script_path ) throw (std::runtime_error);

#endif // _EVRISTICS_H_


