//\textit{script.h}
//\begin{verbatim}
#ifndef _SCRIPT_H_
#define _SCRIPT_H_

#include <string>
#include <iostream>
#include <frequency.h>
#include <stringology.h>
#include <filesystem.h>

class script
{
  protected:
    std::string p; // path
  public:
    script() {};
    script( const std::string& _path ) :
        p( _path )
      { };
    
    std::string path() const
     { return p; }
      
    // don't use it directly
    virtual double dist( const script& s ) const
      { throw "warn"; return 0; }
    
    bool operator==( const script& s ) 
      { return (p == s.p); }
    bool operator!=( const script& s )
      { return !(*this == s); }
};

class edit_distance_script :
  public script
{
  public:
    edit_distance_script() {};
  
    edit_distance_script( const std::string& _path ) :
      script( _path )
        { };
    
    edit_distance_script( const script& s ) :
        script( s.path() )
      { };    
  
    edit_distance_script( const edit_distance_script& s ) :
        script( s.path() )
      { };
        
    virtual double dist( const script& s ) const 
      { return edit_distance( fs::cat( p ), fs::cat( s.path() ) ); }
};

class frequency_script :
  public script
{
  public:
    frequency_script() {};
  
    frequency_script( const std::string& _path ) :
      script( _path )
        { };
    
    frequency_script( const script& s ) :
        script( s.path() )
      { };    
  
    frequency_script( const edit_distance_script& s ) :
        script( s.path() )
      { };
        
    virtual double dist( const script& s ) const 
      { return euclid_metric( frequency( fs::cat( p ) ),
                              frequency( fs::cat( s.path() ) ) ); }
};  


#endif // _SCRIPT_H_
//\end{verbatim}
