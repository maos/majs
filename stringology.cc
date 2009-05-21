#include <string>
#include <vector>

#include "stringology.h"

using namespace std;

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
