#include <selection.h>
#include <script.h>
#include <filesystem.h>

#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <iterator>

using namespace std;
 
int load_selection( const string& dir_path, vector< pair< script, int > >& selection, int answer )
{
  selection.clear();
  
  vector< string > a;
  vector< string > b;
  vector< string > c;
  
  if ( fs::ls( dir_path, back_insert_iterator< vector< string > >( a ) ) != 0) {
    cerr << "fs::ls failed" << endl;
    return 1;
  }
  
  cout << " selection statistics for answer " << answer << ":" << endl;
  cout << "\t objects count = " << a.size() << endl;
  
  vector< string > js_ext;
  vector< string > rest_ext;
  
  js_ext.push_back( "js" );
  
  rest_ext.push_back( "txt" );
  rest_ext.push_back( "htm" );
  rest_ext.push_back( "mht" );
  rest_ext.push_back( "html" );

  extension_filter( a.begin(),
                    a.end(),
                    rest_ext.begin(),
                    rest_ext.end(),
                    back_insert_iterator< vector< string > >( b ) );
  
  extension_filter( a.begin(),
                    a.end(),
                    js_ext.begin(),
                    js_ext.end(),
                    back_insert_iterator< vector< string > >( c ) );
                    
  cout << " \t after extension filter = " << b.size() + c.size() << endl;
  
  a.clear();
  script_filter( b.begin(), b.end(), back_insert_iterator< vector< string > >( a ) );
  cout << " \t and after script filter = " << a.size() + c.size() << endl;
  
  for (int i = 0;i < a.size();++i) {
    selection.push_back( make_pair( script( a[i] ), answer ) );
  }
  
  for (int i = 0;i < c.size();++i ) {
    selection.push_back( make_pair( script( c[i] ), answer ) );
  }
  
  return 0;
}
