#ifndef _CLASSIFIER_H_
#define _CLASSIFIER_H_

#include <vector>
#include <algorithm>
#include <utility>

// X - objects type
// m - |Y|
template < typename X, int m >
class MetricClassifier
{
  private:
    typedef std::vector< std::pair< X, int > > selection_container_type;

    selection_container_type selection;
    int k; // how many neighbors we look at

  public:
    MetricClassifier( int _k = -1 ) : k(_k) {};

    // add new object to selection
    MetricClassifier& operator+=( const std::pair< X, int >& a )
    {
      selection.push_back(a);
      return *this;
    }

    int classify( const X& x );
};

// simple voting
template < typename X, int m >
int MetricClassifier< X, m >::classify( const X& x )
{
  int n = selection.size();
  std::vector< std::pair< double, int > > ind(n); // MetricClassifier::selection_container_type::iterator instead of int here
  int j;

  for (int i = 0;i < n;++i) { // make normal iterator base cycle here
    ind[i] = std::make_pair( x.dist( selection[i].first ), i );
  }

  std::sort( ind.begin(), ind.end() );

  int res = -1;
  double mx = -1;

  for (int i = 0;i < m;++i) {
    double t = 0;
    for (int j = 0;j < n;++j) {
      t += (i == selection[ind[j].second].second); // * w(i,u)
    }
    if (mx < t) {
      mx = t;
      res = i;
    }
  }

  return res;
}

#endif // _CLASSIFIER_H_
