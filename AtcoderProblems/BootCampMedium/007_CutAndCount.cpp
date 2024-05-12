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
ll llMax(ll x, ll y) { return (x >= y) ? x : y; }
ll llMin(ll x, ll y) { return (x <= y) ? x : y; }

int main() {
  /* input */
  int n;
  string s;
  cin >> n >> s;

  /* solve */
  int ans = 0;
  rep(i, n) {
    // 分割
    string left = s.substr(0, i);
    string right = s.substr(i, n - i);
    // 左側をセットに入れていく
    set<char> leftSet;
    rep(j, left.size()) leftSet.insert(left[j]);
    // 右側をセットに入れていく
    set<char> rightSet;
    rep(j, right.size()) rightSet.insert(right[j]);
    // 重複を数える
    int num = 0;
    for (char c : leftSet) {
      if (rightSet.count(c) != 0) num++;
    }
    ans = max(ans, num);
  }

  /* output */
  cout << ans << endl;

  return 0;
}