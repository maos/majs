#ifndef _SCRIPT_H_
#define _SCRIPT_H_

#include <string>
#include <stringology.h>
#include <filesystem.h>

class script
{
  private:
    std::string p; // path
    std::string url;
    std::string desc;
  public:
    script() {};
    script( const std::string& _path ) :
        p( _path )
      { };
    
    std::string path() const
     { return p; }

    double dist( const script& s ) const 
      { return edit_distance( fs::cat( p ), fs::cat( s.path() ) ); }
    
    bool operator==( const script& s ) 
      { return (p == s.p); }
    bool operator!=( const script& s )
      { return !(*this == s); }
};


#endif // _SCRIPT_H_
