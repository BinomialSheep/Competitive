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
  int N, A, B, C, D;
  cin >> N >> A >> B >> C >> D;
  --A;
  --B;
  --C;
  --D;
  string S;
  cin >> S;
  /* solve */
  // C < Dの場合、先にBをDに動かして、次にAをCに動かせばいい
  // C > Dの場合、岩のないマスが3つ並んでいる個所で上手く追い越す
  if (C < D) {
    for (int i = A; i < D; i++) {
      if (S[i] == '#' && S[i + 1] == '#') {
        cout << "No" << endl;
        return 0;
      }
    }
    cout << "Yes" << endl;
    return 0;
  }
  for (int i = A; i < C; i++) {
    if (S[i] == '#' && S[i + 1] == '#') {
      cout << "No" << endl;
      return 0;
    }
  }
  // BからDの区間で追い越す（空きマス3つの区間がある）必要がある
  for (int i = B - 1; i <= D - 1; i++) {
    if (S[i] == '.' && S[i + 1] == '.' && S[i + 2] == '.') {
      cout << "Yes" << endl;
      return 0;
    }
  }

  /* output */
  cout << "No" << endl;
  return 0;
}