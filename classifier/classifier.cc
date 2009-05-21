#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <cstdio>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#include <deque>
#include <map>
#include <set>
#include <algorithm>
#include <cmath>
#include <cctype>
#include <cassert>
#include <cstdio>
#include <numeric>

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

#include "script.h"
#include "classifier.h"

using namespace std;

#define ALL(c) (c).begin(), (c).end()
#define DBG(x) cout << #x << " = " << x << endl

typedef pair<int,int> ii;
typedef pair<ii,int> iii;

typedef long long ll;
typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector< vi > vvi;
typedef vector< ii > vii;


int main()
{
  //freopen("test.in", "r", stdin);
  //freopen("test.out", "w", stdout);
  
  MetricClassifier< script, 2 > mc;

  mc += make_pair( script("good"), 0 );
  mc += make_pair( script("bad"), 1 ); 

  cout << mc.classify( script("whoami") ) << endl;
  
  {
    namespace fs = boost::filesystem;
    fs::create_directory( "tmp" );
  }
  
  //fclose(stdin);
  //fclose(stdout);
  return 0;
}
