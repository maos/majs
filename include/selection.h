//\textit{selection.h}
//\begin{verbatim}
#ifndef _SELECTION_H_
#define _SELECTION_H_

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>

#include <script.h>
#include <stringology.h>
#include <filesystem.h>

bool js_ext( const std::string& s );
bool good_size( const std::string& s, int threshold );
bool is_js( const std::string& s );

int load_selection( const std::string& dir_path,
                    std::vector< std::pair< script, int > >& selection,
                    int answer,
                    int mx_count,
                    int mx_size  );
                    
int find_good_js( const std::string& top_path,
                  const std::string& dst_path,
                  int first,
                  int last );
                  
int split_files( const std::string& src_path,
                 const std::string& dst_path,
                 int min_size,
                 int max_size );

#endif // _SELECTION_H_
//\end{verbatim}
