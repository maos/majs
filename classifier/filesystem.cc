#include <string>
#include <fstream>
#include <filesystem.h>

using namespace std;

namespace fs {

std::string read_content( const std::string& path ) throw (std::runtime_error)
{
  string res;
  ifstream in( path.c_str() );
  
  if ( !in.is_open() ) {
    throw runtime_error( ("can't open file specified by " + path).c_str() );
  }
  
  char c;
  for( ; ; ) {
    c = in.get();
    if ( in.good() ) {
      res += c;
    } else {
      break;
    }
  }
  
  return res;
}

} // fs
