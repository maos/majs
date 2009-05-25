//\textit{selection.cc}
//\begin{verbatim}
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <string>
#include <iterator>
#include <map>
#include <ctime>

#include <mt/uid.h>
#include <download.h>

#include <selection.h>
#include <script.h>
#include <filesystem.h>
#include <evristics.h>

using namespace std;

bool js_ext( const std::string& s )
{
  int dot_place = s.rfind(".");
  
  if (dot_place == string::npos) { // no ext
    return false;
  }
  
  std::string ext = tolower( s.substr( dot_place + 1 ) );
  
  return (ext == "js");
}

bool good_size( const string& s, int threshold )
{
  return ( fs::sz( s ) <= threshold );
}

bool is_js( const string& s )
{
  std::string content = fs::cat( s );
  return ( ( content.find( "<script") != std::string::npos ) ||
         ( content.find( "<SCRIPT") != std::string::npos )   ||
         ( content.find( "</script") != std::string::npos )  ||
         ( content.find( "</SCRIPT") != std::string::npos ) );
}
 
int load_selection( const string& dir_path,
                    vector< pair< script, int > >& selection,
                    int answer,
                    int mx_count,
                    int mx_size )
{
  selection.clear();
  
  vector< string > a;
  
  if ( fs::ls( dir_path, back_insert_iterator< vector< string > >( a ) ) != 0) {
    cerr << "fs::ls failed" << endl;
    return 1;
  }
  
  cout << "total objects count = " << a.size() << endl;
  
  for (int i = 0;i < a.size();++i) {
    if ( good_size(a[i], mx_size) && ( js_ext(a[i]) || is_js(a[i]) ) && (selection.size() < mx_count) ) {
      selection.push_back( make_pair( script(a[i]), answer ) );
    }
  }
  
  cout << "objects count after filtering = " << selection.size() << endl;
           
  return 0;
}

int find_good_js( const string& top_path,
                  const string& dst_path,
                  int first,
                  int last )
{
  map< string, int > top = load_top( top_path, last );
  
  cout << "top size = " << top.size() << endl;
  
  for ( map< string, int >::const_iterator i = top.begin();i != top.end();++i) {
    if (i->second >= first && i->second <= last) {
      string target = (string("http://www.") + i->first);
      cout << "trying to load " << target << " ...";
      FILE* f = downloadGetURL( target.c_str(), "" );
      if (f != 0) {
        ofstream out( (dst_path + "/" + i->first).c_str() );
        if (!out.is_open()) {
          cout << "FAILED" << endl;
          continue;
        }
        out << fs::cat( f );
        fclose(f);
        cout << "OK" << endl;
      } else {
        cout << "FAILED" << endl;
      }
    }
  }
}

int split_files( const std::string& src_path,
                 const std::string& dst_path,
                 int min_size,
                 int max_size )
{
  vector< string > a;
  
  if ( fs::ls( src_path, back_insert_iterator< vector< string > >( a ) ) != 0) {
    cerr << "fs::ls failed" << endl;
    return 1;
  }
  
  srand( time(NULL) ); 
  
  for (int i = 0;i < a.size();++i) {
    std::string content = fs::cat(a[i]);
    int j = 0;
    while (j < content.size()) {
      int r = min_size + rand() % (max_size - min_size);
      string name = xmt::uid_str();
      ofstream out( (dst_path + "/" + name).c_str() );
      if ( !out.is_open() ) {
        continue;
      }
      
      out << content.substr(j,min(r,int(content.size()) - j));
      j += r;
    }
  }
}


//\end{verbatim}
