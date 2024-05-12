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
#define INFTY (1 << 30)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)
ll llMax(ll x, ll y) { return (x >= y) ? x : y; }
ll llMin(ll x, ll y) { return (x <= y) ? x : y; }

int main() {
  /* input */
  string A, B, C;
  cin >> A >> B >> C;
  deque<char> qa, qb, qc;
  rep(i, A.size()) qa.push_back(A[i]);
  rep(i, B.size()) qb.push_back(B[i]);
  rep(i, C.size()) qc.push_back(C[i]);

  int turn = 0;
  while (true) {
    if (turn == 0) {
      if (qa.empty()) {
        cout << 'A' << endl;
        return 0;
      }
      char c = qa.front();
      qa.pop_front();
      if (c == 'a') turn = 0;
      if (c == 'b') turn = 1;
      if (c == 'c') turn = 2;
    } else if (turn == 1) {
      if (qb.empty()) {
        cout << 'B' << endl;
        return 0;
      }
      char c = qb.front();
      qb.pop_front();
      if (c == 'a') turn = 0;
      if (c == 'b') turn = 1;
      if (c == 'c') turn = 2;
    } else {
      if (qc.empty()) {
        cout << 'C' << endl;
        return 0;
      }
      char c = qc.front();
      qc.pop_front();
      if (c == 'a') turn = 0;
      if (c == 'b') turn = 1;
      if (c == 'c') turn = 2;
    }
  }

  /* solve */

  /* output */

  return 0;
}