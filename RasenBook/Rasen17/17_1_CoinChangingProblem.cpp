#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define MAX 10000
#define INFTY (1 << 29)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)

static const int MMAX = 20;
static const int NMAX = 50000;

int main() {
  // input
  int n, m;
  cin >> n >> m;
  vector<int> C(m);
  rep(i, m) cin >> C[i];
  // solve
  // t円払う時の最小枚数
  vector<int> T(n + 1, INFTY);
  T[0] = 0;
  // 1円のみ使える場合、1円と（例えば）3円のみ使える場合……m種類全ての硬貨が使える場合のように更新するDP
  rep(i, m) {
    for (int j = 0; j + C[i] <= n; j++) {
      // j+C[i]円を支払う時の最小枚数は、j円払う枚数にC[i]円1枚を足した枚数と、C[i]円を使わずにj+C[i]円払う枚数のmin
      T[j + C[i]] = min(T[j + C[i]], T[j] + 1);
    }
  }
  // output
  cout << T[n] << endl;

  return 0;
}