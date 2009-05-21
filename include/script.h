#ifndef _SCRIPT_H_
#define _SCRIPT_H_

#include <string>
#include "stringology.h"

class script
{
  private:
    std::string content;
  public:
    script( const std::string& _content ) :
        content( _content )
      { };

    double dist( const script& s ) const { return naive_edit_distance( content, s.content ); }
};


#endif // _SCRIPT_H_
