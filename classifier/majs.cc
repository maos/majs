//\textit{filesystem.cc}
//\begin{verbatim}
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <iterator>
#include <cassert>
#include <stdexcept>

#include <misc/opts.h>

#include <classifier.h>
#include <selection.h>

using namespace std;

int main( int argc, const char** argv )
{ 
  Opts opts;
  
  opts.description( "majs - MAlicios JavaScript detector" );
  opts.usage( "[options]" );
  opts.copyright( "Copyright (C) Dmitry Osmakov - maos, 2009" );
  
  opts << option<void>( "print this help message", 'h', "help" )
       << option<string>( "url to study", 'u', "url" )["www.uglysite.com"]
       << option<string>( "operation mode - [test | classify | load]", 'm', "mode" )["classify"]
       << option<string>( "path to selection", 's', "selection" )["/tmp/selection"]
       << option<string>( "top sites list path in csv format", 't', "top")["/tmp/selection/top-1m.csv"]
       << option<int>( "top count", "top_count")[1000]
       << option<string>( "bad words list", 'w', "words" )["/tmp/selection/words.txt"]
       << option<int>( "count filter", 'c', "count" )[300]
       << option<int>( "script size filter", 'b', "bytes" )[4 * 1024];
  
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
  
  string mode = opts.get<string>("mode");
  
  if ( mode == "classify" ) {
    cout << "starting in classify mode" << endl;
    try {
      if ( classify( opts.get<string>("url"),
                     opts.get<string>("selection"),
                     opts.get<int>("count"),
                     opts.get<int>("bytes"),
                     opts.get<string>("top"),
                     opts.get<int>("top_count"),
                     opts.get<string>("words") ) ) {
        cout << "script seems to be good" << endl;
      } else {
        cout << "script seems to be bad" << endl;
      }
    } catch( const runtime_error& e ) {
      cout << "failed to classify: " << e.what() << endl;
    } catch( ... ) {
      cout << "failed to classify: unknown error" << endl;
    }
  } else if (mode == "test") {
    cout << "starting in test mode" << endl;
    test_metric_classifiers( opts.get<string>("selection"), opts.get<int>("count"), opts.get<int>("bytes") );
  } else if (mode == "load") {
    cout << "starting in load mode" << endl;
    find_good_js( opts.get<string>("top"),
                  opts.get<string>("selection") + "/download",
                  1000,
                  2000 );
    //split_files( opts.get<string>("selection") + "/good", opts.get<string>("selection") + "/split", 0, 4 * 1024 );
  } else {
    cout << "hey, i can't do that" << endl;
  }
  
  return 0;
}
//\end{vertbatim}
