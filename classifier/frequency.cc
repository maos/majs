//\textit{frequency.cc}
//\begin{verbatim}
#include <vector>
#include <string>
#include <cassert>
#include <cmath>

#include <frequency.h>
#include <stringology.h>

using namespace std;

vector< int > frequency( const string& s )
{
  vector<int> res( 256 );
  
  for (int i = 0;i < s.size();++i) {
    ++res[ toint(s[i]) ];
  }
  
  return res;
}

double sqr( double a )
  { return a * a; }

double euclid_metric( const vector< int >& a, const vector< int >& b)
{
  assert( a.size() == b.size() );
  double res = 0;
  int n = a.size();
  for (int i = 0;i < n;++i) {
    res += sqr(toint(a[i]) - toint(b[i]));
  }
  
  return sqrt( res );
}

//\end{verbatim}
