#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>

#include <evristics.h>
#include <stringology.h>
#include <filesystem.h>

using namespace std;

bool nojs( const std::string& script_path )
{
  return !zmatch( "<script", fs::cat( script_path ) );
}

map< string, int > load_top( const string& top_path, int top_count ) throw (runtime_error)
{
  ifstream in( top_path.c_str() );
  if ( !in.is_open() ) {
    throw runtime_error( "can't open top file" );
  }
  
  map< string, int > m;
  for (int i = 0;i < top_count;++i) {
    string s;
    int place;
    string name;
    getline( in, s );
    s[ s.find(',') ] = ' ';
    istringstream(s) >> place >> name;
    m[ name ] = place;
  }
   
  return m;
}

// 0 if not in list
// m.size() - (real place in top) + 1
int search_top( const map< string, int >& m, const string& target )
{
  map< string, int >::const_iterator i = m.find( target );
  if (i == m.end()) {
    return 0;
  } else {
    return m.size() - i->second + 1;
  }
}

// good reason to call this is search_top returned 0
// same return logic as in search_top but with - sign.
int search_fishing( const map< string, int >& m, const string& target, int threshold )
{
  // currently find first that is less than threshold
  for ( map< string, int >::const_iterator i = m.begin();i != m.end();++i ) {
    if ( edit_distance(i->first,target) < threshold ) {
      return -(m.size() - i->second + 1);
    }
  }
  
  return 0;
}

int search_bad_words( const string& words_path, const string& script_path ) throw (runtime_error)
{
  ifstream in( words_path.c_str() );
  if ( !in.is_open() ) {
    throw runtime_error( "can't open words file" );
  }
  
  vector< string > patterns;
  string s;
  while ( getline(in,s) ) {
    patterns.push_back(s);
  }
  
  return -aho_korasik( patterns, fs::cat( script_path ) );
}
