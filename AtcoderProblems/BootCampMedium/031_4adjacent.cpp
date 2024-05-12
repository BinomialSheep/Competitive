#include <bits/stdc++.h>
using namespace std;
using ll = long long;
//#include <atcoder/all>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define MAX 10000
#define INFTY (1 << 29)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)
ll llMax(ll x, ll y) { return (x >= y) ? x : y; }
ll llMin(ll x, ll y) { return (x <= y) ? x : y; }

int main() {
  /* input */
  int N;
  cin >> N;
  int mod2 = 0;
  int mod4 = 0;
  int odd = 0;
  rep(i, N) {
    int a;
    cin >> a;
    if (a % 4 == 0)
      mod4++;
    else if (a % 2 == 0)
      mod2++;
    else
      odd++;
  }
  // cout << mod4 << " " << mod2 << " " << odd << endl;

  /* solve */
  // mod2を並べれば1つを除いて考えなくてよい
  // 1つだけはoddとして数える
  if (mod2 > 0) odd++;
  // oddの間にmod4を挟むのが最善で、この時oddが1つ多くてもいい
  if (odd <= mod4 + 1) {
    cout << "Yes" << endl;
  } else {
    cout << "No" << endl;
  }

  /* output */

  return 0;
}