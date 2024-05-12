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

int main() {
  int n;
  string s;
  cin >> n >> s;

  string ans = "";

  int i = 0;
  while (i != n) {
    if (s[i] != 'B') {
      ans.push_back(s[i]);
      i++;
      continue;
    }

    // Bの場合
    if (i == n - 1) {
      // 最後だったら終わり
      ans.push_back(s[i]);
      break;
    }
    if (s[i + 1] == 'C') {
      ans.push_back(s[i]);
      i++;
      continue;
    }
    if (s[i + 1] == 'B') {
      // BBの場合、Aに変換して2回インクリメントする
      ans.push_back('A');
      i += 2;
      continue;
    }
    // BAの場合、ABに入れ替える
    ans.push_back('A');
    s[i + 1] = 'B';
    i++;
  }

  cout << ans << endl;

  return 0;
}