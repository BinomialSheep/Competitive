#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

int main() {
  ll h;
  cin >> h;

  // hは2^40以下
  int l = 0, r = 41, mid;
  while (l + 1 < r) {
    mid = (l + r) / 2;

    // 右側探索
    if (pow(2, mid) <= h) {
      l = mid;
    } else {
      // 左側探索
      r = mid;
    }
  }

  ll ans = pow(2, r) - 1;
  cout << ans << endl;

  /*
  ll ans = 0;
  stack<ll> myStack;
  myStack.push(h);

  // 体力と倒す回数
  unordered_map<ll, ll> memo;

  while (!myStack.empty()) {
    ans++;
    ll hp = myStack.top();
    myStack.pop();
    if (hp == 1) continue;
    if (memo.find(hp) != memo.end()) {
      ans += memo[hp];
    } else {
      myStack.push(hp / 2);
      myStack.push(hp / 2);
    }
  }
  cout << ans << endl;
  */

  return 0;
}