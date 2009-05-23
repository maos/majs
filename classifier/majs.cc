#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <iterator>

#include <misc/opts.h>

#include <script.h>
#include <classifier.h>
#include <filesystem.h>
#include <selection.h>

using namespace std;

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
  
  string selection_path = opts.get< string >('s');
  
  vector< pair< script, int > > good;
  vector< pair< script, int > > bad;
  
  load_selection( selection_path + "/bad", bad, 0 );
  load_selection( selection_path + "/good", good, 1 );
  
  // awfull
  for (int i = 0;i < good.size();++i) {
    mc += good[i];
  }
  for (int i = 0;i < bad.size();++i) {
    mc += bad[i];
  }
    
  return 0;
}
