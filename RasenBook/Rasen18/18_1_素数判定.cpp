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

// O(√n)の定数倍改善アルゴリズム
bool isPrime(int x) {
  if (x == 2) return true;
  if (x < 2 || x % 2 == 0) return false;
  int end = (int)sqrt(x) + 1;
  for (int i = 3; i <= end; i += 2)
    if (x % i == 0) return false;
  return true;
}

// 素数列挙（エラトステネスの篩）O(N log logN)
vector<bool> eratos(int n) {
  vector<bool> isPrime(n + 1, true);  // 1-prigin;
  isPrime[0] = isPrime[1] = false;
  int end = (int)sqrt(n) + 1;
  for (int i = 2; i <= end; i++) {
    if (isPrime[i]) {
      for (int j = i + i; j <= n; j += i) isPrime[j] = false;
    }
  }
  return isPrime;
}

int main() {
  int n;
  cin >> n;

  int num, ans = 0;
  rep(i, n) {
    cin >> num;
    if (isPrime(num)) ans++;
  }

  cout << ans << endl;

  /* 列挙
  vector<bool> primeVec = eratos(n);
  for (int i = 1; i <= n; i++) {
    cout << i << " " << (primeVec[i] ? "Yes" : "No") << endl;
  }
  */

  return 0;
}