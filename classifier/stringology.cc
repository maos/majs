#include <string>
#include <vector>
#include <ctype.h>
#include <algorithm>
#include <iostream>
#include <cassert>

#include <stringology.h>

using namespace std;

string tolower( const std::string& s )
{
  string res = s;
  for (int i = 0;i < res.size();++i) {
    res[i] = tolower(res[i]);
  }
  
  return res;
}

int lis( const vector< int >& a )
{
  static const int big = 123456789;
  vector< int >  c( a.size() , big );
  
  for (int i = 0;i < int(a.size());++i) {
    *lower_bound( c.begin(), c.end(), a[i] ) = a[i];
  }
  
  return (lower_bound( c.begin(), c.end(), big ) - c.begin());
}

// maybe there is a better way?
int toint( char c )
  { return (c + 8 * sizeof(char) ) % (8 * sizeof(char)); }

int lcs( const string& a, const string& b )
{
  vector< vector< int > > t( (1 << (8 * sizeof(char)) ) );
  for (int i = int(b.size()) - 1;i >= 0;--i) {
    t[ toint(b[i]) ].push_back( i );
  }
  
  vector< int > c;
  for (int i = 0;i < a.size();++i) {
    for (int j = 0;j < t[ toint(a[i]) ].size();++j) {
      c.push_back( t[ toint(a[i]) ][j] );
    }
  }
  
  return lis(c);
}

// precondition: ch_cost = 2, ins_cost = del_cost = 1;
int edit_distance( const string& a, const string& b )
{
  return a.size() + b.size() - 2 * lcs( a, b );
}

// simple dynamics
int naive_edit_distance( const string& a, const string& b,int ch_cost, int ins_cost, int del_cost )
{
  int n = a.size();
  int m = b.size();
  vector< vector<int> > d(n + 1,vector<int>(m + 1));
  d[0][0] = 0;
  for (int i = 1;i <= n;++i)
    d[i][0] = del_cost * i;
  for (int j = 1;j <= m;++j)
    d[0][j] = ins_cost * j;

  for (int i = 1;i <= n;++i)
    for (int j = 1;j <= m;++j)
      d[i][j] = min( min( d[i - 1][j - 1] + (a[i] != b[j]) * ch_cost,
                          d[i - 1][j] + del_cost  ),
                          d[i][j - 1] + ins_cost  );

  return d[n][m];
}


