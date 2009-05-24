#ifndef _CLASSIFIER_H_
#define _CLASSIFIER_H_

#include <vector>
#include <algorithm>
#include <utility>
#include <iostream>

// X - objects type
// m - |Y|
template < typename X, int m >
class MetricClassifier
{
  public:
    typedef std::vector< std::pair< X, int > > selection_container_type;

    selection_container_type selection;
    int k; // how many neighbors we look at
    
    void order_selection( const X& x );

  public:
    MetricClassifier( int _k = -1 ) : k(_k) {};

    // add new object to selection
    MetricClassifier& operator+=( const std::pair< X, int >& a )
    {
      selection.push_back(a);
      return *this;
    }
    
    void clear()
      { selection.clear(); }

    int classify( const X& x );
    
    double margin( const X& x, int y );    
    
    // precondition: selection is ordered by x
    double get_class_weight( const X& x, int y );
    
    void stolp();
};

template < typename X, int m >
void MetricClassifier< X, m >::order_selection( const X& x )
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
  
  selection = ordered_selection;
}

template < typename X, int m >
double MetricClassifier< X, m >::get_class_weight( const X& x, int y )
{
  int n = selection.size();
  double res = 0;
  
  // tune here
  double q = 0.96;
  double w = 1;
  
  for (int i = 0;i < n;++i) {
    res += w * (selection[i].second == y);
    w = w * q;
  }
  
  return res;
}


// nearest neighbor
template < typename X, int m >
int MetricClassifier< X, m >::classify( const X& x )
{
  order_selection( x );
  
  double mx = 0;
  int res = 0;
  
  for (int y = 0;y < m;++y) {
    int t = get_class_weight( x, y );
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
  order_selection( x );
  double self = get_class_weight( x, y );
    
  double mx = 0;
  for (int j = 0;j < m;++j) {
    if ( y != j ) {
      mx = max( mx, get_class_weight( x, j ) );
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

#endif // _CLASSIFIER_H_
