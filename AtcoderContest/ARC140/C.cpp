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
  int N, X;
  cin >> N >> X;

  /* solve */
  if (N == 2) {
    if (X == 1) cout << "1 2" << endl;
    if (X == 2) cout << "2 1" << endl;
    return 0;
  }
  if (N == 3) {
    if (X == 1) cout << "1 2 3" << endl;
    if (X == 2) cout << "2 1 3" << endl;
    if (X == 3) cout << "3 2 1" << endl;
    return 0;
  }

  if (N % 2 == 1) {
    //　とりあえずスタートは真ん中
    int num = N / 2 + 1;
    int sig;
    if (X == num) {
      sig = 1;
      X = -1;
    } else if (X > num) {
      sig = -1;
      cout << X << " ";
    } else {
      sig = 1;
      cout << X << " ";
    }
    rep(i, N) {
      num += i * sig;
      if (num == X) {
        num -= i * sig;
        continue;
      }
      if (num == 0) {
        cout << N;
        break;
      }
      if (num == N + 1) {
        cout << 1;
        break;
      }
      assert(0 < num && num <= N);
      cout << num << " ";
      if (sig == 1)
        sig = -1;
      else
        sig = 1;
    }
  } else {
    int num = N / 2;
    if (X <= num) num++;
    int sig;
    if (X < num) {
      sig = 1;
    } else {
      sig = -1;
    }
    cout << X << " ";
    rep(i, N) {
      num += i * sig;
      if (num == X) {
        num -= i * sig;
        continue;
      }
      if (0 >= num || num > N) continue;
      assert(0 < num && num <= N);
      cout << num << " ";
      if (sig == 1)
        sig = -1;
      else
        sig = 1;
    }
  }
  cout << endl;

  /* output */

  return 0;
}