#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <cstdio>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#include <deque>
#include <map>
#include <set>
#include <algorithm>
#include <cmath>
#include <cctype>
#include <cassert>
#include <cstdio>
#include <numeric>
#include <iterator>

#include <misc/opts.h>

#include <script.h>
#include <classifier.h>
#include <filesystem.h>

using namespace std;

#define ALL(c) (c).begin(), (c).end()
#define DBG(x) cout << #x << " = " << x << endl

typedef pair<int,int> ii;
typedef pair<ii,int> iii;

typedef long long ll;
typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector< vi > vvi;
typedef vector< ii > vii;

int load_selection( const string& dir_path, vector< pair< script, int > >& selection  )
{
  selection.clear();
  
  string good_path = dir_path + "/good";
  string bad_path = dir_path + "/bad/manual";
  
  vector< string > good;
  vector< string > bad;
  
  if ( fs::list_dir( good_path, back_insert_iterator< vector< string > >(good) ) != 0) {
    cerr << "fs::list_dir error" << endl;
    return 1;
  }
  
  if ( fs::list_dir( bad_path, back_insert_iterator< vector< string > >(bad) ) != 0 ) {
    cerr << "fs::list_dir error" << endl;
    return 1;
  }
  
  for (int i = 0;i < good.size();++i) {
    selection.push_back( make_pair( script( good_path + "/" + good[i] ), 0 ) );
  }
  
  for (int i = 0;i < bad.size();++i) {
    selection.push_back( make_pair( script( bad_path + "/" + bad[i] ), 1 ) );
  }
    
  return 0;
}

int main( int argc, const char** argv )
{ 
  Opts opts;
  
  opts.description( "majs - MAlicios JavaScript detector" );
  opts.usage( "[options]" );
  opts.copyright( "Copyright (C) maos, 2009" );
  
  opts << option<void>( "print this help message", 'h', "help" )
       << option<string>( "path to selection", 's', "selection" )["/tmp/selection"];
  
  try {
    opts.parse( argc, argv );
  }
  catch (...) {
    opts.help( cerr );
    return 1;
  }
  
  if ( opts.is_set( 'h' ) ) {
    opts.help( cerr );
    return 0;
  }
  
  MetricClassifier< script, 2 > mc;
  vector< pair< script, int > > selection;
  
  if ( load_selection( opts.get<string>('s'), selection ) != 0) {
    cerr << "error on selection loading" << endl;
    return 1;
  }
  
  for (int i = 0;i < selection.size();++i) {
    mc += selection[i];
  }
  
  return 0;
}
