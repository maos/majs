#include <string>
#include <vector>
#include <ctype.h>
#include <algorithm>
#include <iostream>
#include <cassert>

#include <trie.h>
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

int aho_korasik( const vector<string>& patterns,
                         const string& text )
{
  int res = 0;
  Trie t;
  for (int i = 0;i < patterns.size();++i)
    t += patterns[i];

  t.calc_p_function();
  t.calc_max_terminal_prefixes();
  
  Trie::node* j = t.root;
  int i = 0;
  int n = text.size();
  
  while (i < n) {   
    if (j->childs[text[i]]) {
      j = j->childs[text[i]];
      ++i;
    } else {
      if (j != t.root) {
        j = t.p[j];
      } else {
        ++i;
      }
    }
    
    if (j->is_terminal) {
      ++res;
      //string matched = t[j];
      //cout << "find match with " << matched << " at position " << i - matched.size() << endl;
    }
    
    if (j != t.root) {
      Trie::node* k = t.m[j];
      while (k != t.root) {
        ++res;
        //string matched = t[k];
        //cout << "find match with " << matched << " at position " << i - matched.size() << endl;
        k = t.m[k];
      }
    }
  }
  
  return res;
}

// calculates z function for s
vector<int> z_function( const string& s )
{
  int n = s.size();
  vector<int> z(n);

  int l = 0;
  int r = 0;
  int i;
  z[0] = 0;

  for (int k = 1;k < n;++k) {
    if (k > r) {
      i = 0;
      while (k + i < n && s[k + i] == s[i])
        ++i;
      l = k;
      z[k] = i;
      r = k + i - 1;
    } else {
      int p = k - l;
      if (r - k + 1 > z[p]) {
        z[k] = z[p];
      } else {
        i = r - k + 1;
        while (k + i < n && s[i] == s[k + i])
          ++i;
        l = k;
        z[k] = i;
        r = k + i - 1;
      }
    }

  }

  return z;
}

bool zmatch(const string& p,const string& t)
{
  vector<int> res;
  int n = p.size();
  vector<int> z = z_function(p + '0' + t);

  for (int i = 0;i < z.size();++i)
    if (z[i] == n)
      return true;
      
  return false;
}

