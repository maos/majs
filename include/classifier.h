#ifndef _CLASSIFIER_H_
#define _CLASSIFIER_H_

#include <vector>
#include <algorithm>
#include <utility>
#include <iostream>
#include <cmath>

// main thing, wild thing...
int classify( const std::string& target,
              const std::string& selection_path,
              int mx_count,
              int mx_size,
              const std::string& top_path,
              int top_count,
              const std::string& words_path );
              
void test_metric_classifiers( const std::string& selection_path,
                              int mx_count,
                              int mx_size );

// X - objects type
// m - |Y|
template < typename X, int m >
class MetricClassifier
{
  public:
    typedef std::vector< std::pair< X, int > > selection_container_type;
    
    selection_container_type selection;
    int k; // how many neighbors we look at
  
  public:
    MetricClassifier( int _k = 0 ) : k(_k) {}; // 0 for all

    // add new object to selection
    MetricClassifier& operator+=( const std::pair< X, int >& a )
      { selection.push_back(a); return *this; }
    
    void clear()
      { selection.clear(); }
    
    selection_container_type order_selection( const X& x );
    std::pair< X, int > get_nearest_neighbor( const X& x );
    selection_container_type get_active_selection( const X& x, int c ); // c neighbors
    
    double get_weight( const X& target_x, const X& neighbor_x, int rank );
    double get_class_weight( const X& x, int y, const selection_container_type& active );

    int classify( const X& x );
    
    double margin( const X& x, int y );   
    
    void stolp();
    
    double loo();
};

// warn: selection_container_type must be returned
template < typename X, int m >
std::vector< std::pair< X, int > > MetricClassifier< X, m >::get_active_selection( const X& x, int c )
{
  selection_container_type res;
  if (c <= 0) { // order all selection
    res = order_selection(x);
  } else if (c == 1) { // get neirest neigbor
    res.push_back( get_nearest_neighbor(x) );
  } else {
    // TODO: O(n) algo here
    selection_container_type tmp = order_selection(x);
    int n = std::min( int(tmp.size()), c );
    res.resize(n);
    for (int i = 0;i < n;++i)
      res[i] = tmp[i];
  }
  
  return res;
}

template < typename X, int m >
std::pair< X, int > MetricClassifier< X, m >::get_nearest_neighbor( const X& x )
{
  int n = selection.size();
  std::vector< std::pair< double, int > > ind(n); // MetricClassifier::selection_container_type::iterator instead of int here
  int j;

  for (int i = 0;i < n;++i) { // make normal iterator base cycle here
    ind[i] = std::make_pair( x.dist( selection[i].first ), i );
  }
  
  return selection[ std::max_element( ind.begin(), ind.end() )->second ];  
}

// warn: selection_container_type must be returned
template < typename X, int m >
std::vector< std::pair< X, int > >  MetricClassifier< X, m >::order_selection( const X& x )
{
  int n = selection.size();
  std::vector< std::pair< double, int > > ind(n); // MetricClassifier::selection_container_type::iterator instead of int here
  int j;

  for (int i = 0;i < n;++i) { // make normal iterator base cycle here
    ind[i] = std::make_pair( x.dist( selection[i].first ), i );
  }
  
  sort( ind.begin(), ind.end() );
  
  selection_container_type ordered_selection(n);
  
  for (int i = 0;i < n;++i) {
    ordered_selection[i] = selection[ ind[i].second ];
  }
  
  return ordered_selection;
}

template < typename X, int m >
double MetricClassifier< X, m >::get_weight( const X& target_x, const X& neighbor_x, int rank )
{
  const double q = 0.96;
  return pow( q, rank );
}

template < typename X, int m >
double MetricClassifier< X, m >::get_class_weight( const X& x, int y, const selection_container_type& active_selection )
{  
  int n = active_selection.size();
  double res = 0;
  
  for (int i = 0;i < n;++i) {
    if (active_selection[i].second == y) {
      res += get_weight( x, active_selection[i].first, i );
    }
  }
  
  return res;
}

template < typename X, int m >
int MetricClassifier< X, m >::classify( const X& x )
{
  selection_container_type active = get_active_selection( x, k );
  
  double mx = 0;
  int res = 0;
  
  for (int y = 0;y < m;++y) {
    int t = get_class_weight( x, y, active );
    if (t > mx) {
      res = y;
      mx = t;
    }
  }

  return res;
}

template < typename X, int m >
double MetricClassifier< X, m >::margin( const X& x, int y )
{
  selection_container_type active = get_active_selection( x, k );
  
  double self = get_class_weight( x, y, active );
    
  double mx = 0;
  for (int j = 0;j < m;++j) {
    if ( y != j ) {
      mx = max( mx, get_class_weight( x, j, active ) );
    }
  }

  return self - mx;  
}

template < typename X, int m >
void MetricClassifier< X, m >::stolp()
{
  // remove ejections
  {
    double ejection_threshold = 0;
  
    std::vector< bool > ejections( selection.size() );

    for (int i = 0;i < selection.size();++i) {
      if ( margin( selection[i].first, selection[i].second ) < ejection_threshold ) {
        ejections[i] = true;
      }
    }
    
    selection_container_type tmp;
    
    for (int i = 0;i < selection.size();++i) {
      if ( !ejections[i] ) {
        tmp.push_back( selection[i] );
      }
    }
    
    selection = tmp;
  }
  // greedy search
}

template < typename X, int m >
double MetricClassifier< X, m >::loo()
{
  int n = selection.size();
  double res = 0;
  for (int i = 0;i < n;++i) {
    selection_container_type active = get_active_selection( selection[i].first, 2 );
    if ((active.back().second != selection[i].second)) {
      ++res;
      // std::cout << "FAILED" << std::endl;
    } else {
      // std::cout << "OK" << std::endl;
    }
  }
  
  return res / n;
}

#endif // _CLASSIFIER_H_
 
