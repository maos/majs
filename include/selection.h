#ifndef _SELECTION_H_
#define _SELECTION_H_

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>

#include <script.h>
#include <stringology.h>
#include <filesystem.h>

template < typename InputIterator, typename BackInsertIterator >
void extension_filter( InputIterator first,
                       InputIterator last,
                       InputIterator ext_first,
                       InputIterator ext_last,
                       BackInsertIterator bi )
{
  for (InputIterator i = first;i != last;++i) {
    std::string& s = *i;
    int dot_place = s.rfind(".");
    if ( dot_place != std::string::npos ) {
      std::string ext = tolower( s.substr( dot_place + 1 ) );
      if ( std::find( ext_first, ext_last, ext ) != ext_last ) {
        ++bi = s;
      }
    } else {
      // no extension
      if ( std::find( ext_first, ext_last, "") ) {
        ++bi = s;
      }
    }
  }
}

// i ought to currently
template < typename InputIterator, typename BackInsertIterator >
void sz_filter( InputIterator first,
                InputIterator last,
                BackInsertIterator bi )
{
  int threshold = 2048;
   
  for (InputIterator i = first;i != last;++i) {
    std::string& s = *i;
    if ( fs::sz( s ) <= threshold ) {
      ++bi = s;
    }
  }
}


template < typename InputIterator, typename BackInsertIterator >
void script_filter( InputIterator first, InputIterator last, BackInsertIterator bi )
{
  for (InputIterator i = first;i != last;++i) {
    std::string& s = *i;
    std::string content = fs::cat( s );
    if ( ( content.find( "<script") != std::string::npos ) &&
         ( content.find( "script>") != std::string::npos ) ) 
         { ++bi = s; }; 
  }
}

int load_selection( const std::string& dir_path, std::vector< std::pair< script, int > >& selection, int answer  );

#endif // _SELECTION_H_
