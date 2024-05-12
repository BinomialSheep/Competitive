#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vl = vector<long long>;
using vs = vector<string>;
using vc = vector<char>;
using vpii = vector<pair<int, int>>;
using vpll = vector<pair<long long, long long>>;
using vvi = vector<vector<int>>;
using vvl = vector<vector<long long>>;
using vvc = vector<vector<char>>;
using vvvi = vector<vector<vector<int>>>;
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
  string S;
  cin >> S;
  int Q;
  cin >> Q;

  /* solve */
  // push_frontしたいので
  deque<char> str;
  rep(i, S.size()) str.push_back(S[i]);

  int revFlag = 0;
  rep(i, Q) {
    int T;
    cin >> T;

    if (T == 1) {
      revFlag ^= 1;
    } else {
      int F;
      char C;
      cin >> F >> C;

      if ((F == 1 && !revFlag) || (F == 2 && revFlag)) {
        str.push_front(C);
      } else {
        str.push_back(C);
      }
    }
  }

  /* output */
  if (!revFlag) {
    while (!str.empty()) {
      cout << str.front();
      str.pop_front();
    }
    cout << endl;
  } else {
    while (!str.empty()) {
      cout << str.back();
      str.pop_back();
    }
    cout << endl;
  }
  return 0;
}