//\textit{classifier.cc}
//\begin{verbatim}
#include <classifier.h>
#include <string>
#include <iostream>
#include <fstream>
#include <map>

#include <download.h>
#include <mt/uid.h>

#include <script.h>
#include <classifier.h>
#include <filesystem.h>
#include <selection.h>
#include <evristics.h>
#include <script.h>

using namespace std;

void test_metric_classifiers( const std::string& selection_path,
                              int mx_count,
                              int mx_size )
{
  MetricClassifier< edit_distance_script, 2 > edit_distance_classifier(1);
  MetricClassifier< frequency_script, 2 > frequency_classifier(1);
  
  // loading selection
  {    
    vector< pair< script, int > > good;
    vector< pair< script, int > > bad;
    
    load_selection( selection_path + "/bad",
                    bad,
                    0,
                    mx_count,
                    mx_size );

    load_selection( selection_path + "/good",
                    good,
                    1,
                    mx_count,
                    mx_size );
    
    // awfull
    for (int i = 0;i < good.size();++i) {
      edit_distance_classifier += good[i];
      frequency_classifier += good[i];
    }
    for (int i = 0;i < bad.size();++i) {
      edit_distance_classifier += bad[i];
      frequency_classifier += bad[i];
    }
    
    cout << "selection loaded" << endl;
  }
  
  cout << "error probability for edit distance = "
       << edit_distance_classifier.loo()
       << endl;
          
  cout << "error probability for frequency distribution = "
       << frequency_classifier.loo()
       << endl;
}
              

int classify( const std::string& target,
              const std::string& selection_path,
              int mx_count,
              int mx_size,
              const std::string& top_path,
              int top_count,
              const std::string& words_path )
{
  FILE* f = downloadGetURL( target.c_str(), "" );
  
  if (f == 0) {
    throw runtime_error("can't download file");
  }
  
  string script_path = string("/tmp/") + xmt::uid_str();
  
  {
    ofstream out( script_path.c_str() );
    out << fs::cat( f );
    fclose(f);
  }
  
  cout << "script size = " << fs::sz( script_path.c_str() ) << endl;
  
  // cout << fs::cat( script_path );
  
  if ( nojs( script_path ) ) {
    cout << "no js detected" << endl;
    return 1;
  }
  
  // playing with url
  struct url* _url = downloadParseURL( target.c_str() );
  // top weights
  map< string, int > top = load_top( top_path, top_count );
  int top_weight = search_top( top, _url->host );
  int fishing_weight = 0;
  if ( top_weight == 0 ) {
    fishing_weight = search_fishing( top, _url->host );
  }
  
  // playing with bad words
  int words_weight = 10 * search_bad_words( words_path, script_path );
  
  MetricClassifier< edit_distance_script, 2 > edit_distance_classifier(1);
  MetricClassifier< frequency_script, 2 > frequency_classifier(1);
  
  // loading selection
  {    
    vector< pair< script, int > > good;
    vector< pair< script, int > > bad;
    
    load_selection( selection_path + "/bad",
                    bad,
                    0,
                    mx_count,
                    mx_size );

    load_selection( selection_path + "/good",
                    good,
                    1,
                    mx_count,
                    mx_size );
    
    // awfull
    for (int i = 0;i < good.size();++i) {
      edit_distance_classifier += good[i];
      frequency_classifier += good[i];
    }
    for (int i = 0;i < bad.size();++i) {
      edit_distance_classifier += bad[i];
      frequency_classifier += bad[i];
    }
    
    cout << "selection loaded" << endl;
  }
  
  cout << "go classifiers, go!" << endl;
  int edit_ans = edit_distance_classifier.classify( 
              edit_distance_script( script_path ) );
              
  int fr_ans = frequency_classifier.classify( edit_distance_script( script_path ) );
  
  int edit_distance_weight = 42 * ( ( edit_ans == 0) ? -1 : 1 );
  int frequency_weight = 10 * ( (fr_ans == 0) ? -1 : 1);
  
  int res = ( top_weight +
             fishing_weight +
             words_weight +
             edit_distance_weight +
             frequency_weight); 
  
  cout << "top_weight = " << top_weight << endl;
  cout << "fishing_weight = " << fishing_weight << endl;
  cout << "words_weight = " << words_weight << endl;
  cout << "edit_distance_weight = " << edit_distance_weight << endl;
  cout << "frequency_weight = " << frequency_weight << endl;
  
  cout << "total weight = " << res << endl;
  
  return ( res >= 0 );
}
//\end{verbatim}
 
