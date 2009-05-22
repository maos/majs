#ifndef _SCRIPT_H_
#define _SCRIPT_H_

#include <string>
#include <stringology.h>
#include <filesystem.h>

class script
{
  private:
    std::string p; // path
  public:
    script( const std::string& _path ) :
        p( _path )
      { };
    
    std::string path() const
     { return p; }

    double dist( const script& s ) const 
      { return naive_edit_distance( fs::read_content( p ), fs::read_content( s.path() ) ); }
};


#endif // _SCRIPT_H_
