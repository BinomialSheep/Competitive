#include <bits/stdc++.h>
using namespace std;
using ll = long long;
//#include <atcoder/all>
// using namespace atcoder;
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft
// VisualStudio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
// using mint = modint998244353;

int MOD = 998244353;

unordered_map<ll, ll> myMap;

ll solution(ll x, ll tempAns) {
  if (x <= 4) {
    return tempAns * x % MOD;
  } else if (myMap.find(x) != myMap.end()) {
    return tempAns * myMap[x] % MOD;
  } else {
    ll temp1 = x / 2;
    ll v1 = solution(temp1, 1);
    myMap[temp1] = v1;
    ll temp2 = (x + 1) / 2;
    ll v2 = solution(temp2, 1);
    myMap[temp2] = v2;
    return tempAns * (v1 * v2 % MOD) % MOD;
  }
}

int main() {
  ll x;
  cin >> x;

  cout << solution(x, 1) << endl;

  return 0;
}