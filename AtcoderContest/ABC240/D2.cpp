#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define MAX 10000
#define INTFY (1 << 29)

int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  rep(i, n) { cin >> a[i]; }

  // 初期化
  int num = a[0];
  vector<int> count(n);
  count[0] = 1;
  int ans = 1;
  cout << ans << endl;

  stack<int> myStack;
  int count = 0;

  rep(i, n) {
    myStack.push(i);
    
  }



  // シミュレーション
  for (int i = 1; i < n; i++) {
    if (a[i] == num) {
      count[i] = count[i - 1] + 1;
      if (count[i] != num) {
        ans++;
      } else {
        // まとめて消えるとこ
        ans -= a[i] - 1;
        num = a[ans - 1];
        count[i] = count[ans - 1];
        // hack
        a[i] = a[ans - 1];
      }
    } else {
      num = a[i];
      count[i] = 1;
      ans++;
    }
    cout << ans << endl;
  }

  return 0;
}