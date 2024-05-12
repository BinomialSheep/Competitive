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
  int n, m;
  cin >> n >> m;
  vector<pair<int, int>> AB(n);
  rep(i, n) cin >> AB[i].first;
  rep(i, n) cin >> AB[i].second;
  vector<pair<int, int>> CD(m);
  rep(i, m) cin >> CD[i].first;
  rep(i, m) cin >> CD[i].second;
  /* solve */
  sort(AB.rbegin(), AB.rend());
  sort(CD.rbegin(), CD.rend());

  multiset<int> ms;

  int i = 0;
  int j = 0;
  while (i < n) {
    // 縦の長さが長い方から平面走査する
    if (j < m && AB[i].first <= CD[j].first) {
      // 箱にぶつかった場合（同時なら箱を先に処理
      // 箱の横の長さをmultisetに追加する
      ms.insert(CD[j].second);
      j++;
    } else {
      // チョコにぶつかった場合
      // 入れれる箱を探す

      // auto it = ms.lower_bound(AB[i].second);
      auto it = lower_bound(ms.begin(), ms.end(), AB[i].second);

      // なければ終わり
      if (it == ms.end()) {
        cout << "No" << endl;
        return 0;
      }
      // あれば箱を取り除いて続行
      ms.erase(it);
      i++;
    }
  }

  /* output */
  cout << "Yes" << endl;

  return 0;
}