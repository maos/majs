//\textit{filesystem.cc}
//\begin{verbatim}
#include <sys/stat.h>
#include <stdio.h>

#include <cassert>
#include <stdexcept>
#include <string>
#include <fstream>
#include <iostream>
#include <filesystem.h>

using namespace std;

namespace fs {
  
int mkdir( const std::string& path )
 { return ::mkdir( path.c_str(), S_IRWXU | S_IRGRP | S_IXGRP ); }

int rmdir( const std::string& path )
 { return ::rmdir( path.c_str() ); }
 
int cd( const std::string& path )
  { return ::chdir( path.c_str() ); }

std::string cat( const std::string& path ) throw (std::runtime_error)
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

std::string cat( FILE* f ) throw (std::runtime_error)
{
  assert( f != 0 );
  
  string res;
  int c;

  for ( ; ; ) {
    c = fgetc(f);
    if ( c != EOF ) {
      res += char(c);
    } else {
      break;
    }
  }
  
  rewind(f);

  return res;
}

int cp( const string& which, const string& where )
{
  ofstream out( where.c_str() );
  
  if ( !out.is_open() ) {
    cerr << "copy_file: can't open dst file" << endl;
    return 1;
  }
  
  try {
    out << cat( which );
  } catch( ... ) {
    cerr << "copy_file: can't open src file" << endl;
    return 1;
  }
  
  return 0;
}

std::string pwd()
{
  char* buf = ::getcwd( 0, 0 );
  if ( buf == NULL ) {
    return "";
  } else {
    string res = buf;
    free( buf );
    return res;
  }
}

int sz( const string& path )
{
  struct stat st;
  stat( path.c_str(), &st );
  
  return st.st_size;
}

} // fs
//\end{verbatim}
