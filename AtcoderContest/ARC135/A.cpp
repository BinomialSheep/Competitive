#include <bits/stdc++.h>
using namespace std;
using ll = long long;
//#include <atcoder/all>
// using namespace atcoder;
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft
// VisualStudio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
// using mint = modint998244353;

vector<int> vec;

ll count2;
ll count3;

unordered_map<ll, pair<ll, ll>> myMap;

// 100以下はここを参照
vector<pair<ll, ll>> shortCut(26);

void makeShortCut() {
  shortCut[1] = pair<ll, ll>(0, 0);
  shortCut[2] = pair<ll, ll>(1, 0);
  shortCut[3] = pair<ll, ll>(0, 1);
  shortCut[4] = pair<ll, ll>(2, 0);
  shortCut[5] = pair<ll, ll>(1, 1);
  shortCut[6] = pair<ll, ll>(0, 2);
  shortCut[7] = pair<ll, ll>(2, 1);
  shortCut[8] = pair<ll, ll>(4, 0);
  shortCut[9] = pair<ll, ll>(3, 1);
  shortCut[10] = pair<ll, ll>(2, 2);
  shortCut[11] = pair<ll, ll>(1, 3);
  shortCut[12] = pair<ll, ll>(0, 4);
  shortCut[13] = pair<ll, ll>(2, 3);
  shortCut[14] = pair<ll, ll>(4, 2);
  shortCut[15] = pair<ll, ll>(6, 1);
  shortCut[16] = pair<ll, ll>(8, 0);
  shortCut[17] = pair<ll, ll>(7, 1);
  shortCut[18] = pair<ll, ll>(6, 2);
  shortCut[19] = pair<ll, ll>(5, 3);
  shortCut[20] = pair<ll, ll>(4, 4);
  shortCut[21] = pair<ll, ll>(3, 5);
  shortCut[22] = pair<ll, ll>(2, 6);
  shortCut[23] = pair<ll, ll>(1, 7);
  shortCut[24] = pair<ll, ll>(0, 8);
  shortCut[25] = pair<ll, ll>(2, 7);
}

unordered_map<ll, pair<ll, ll>> myMap;

pair<ll, ll> makeBoard(ll x) {
  if (x == 2) {
    return pair<ll, ll>(1, 0);
  } else if (x == 3) {
    return pair<ll, ll>(0, 1);
  } else if (myMap.find(x) != myMap.end()) {
    return myMap[x];
  } else {
    // 偶数なら1回で済む
    if (x % 2 == 0) {
      ll temp = x / 2;
      pair<ll, ll> p = makeBoard(temp);
      myMap[temp] = p;
      return pair<ll, ll>(2 * p.first, 2 * p.second);
    } else {
      ll temp1 = x / 2;
      pair<ll, ll> p1 = makeBoard(temp1);
      myMap[temp1] = p1;
      ll temp2 = (x + 1) / 2;
      pair<ll, ll> p2 = makeBoard(temp2);
      myMap[temp2] = p2;
      return pair<ll, ll>(p1.first + p2.first, p1.second + p2.second);
    }
  }
}

int main() {
  ll x;
  cin >> x;

  count2 = 0;
  count3 = 0;

  // makeShortCut();

  pair<ll, ll> ansPair = makeBoard(x);
  count2 = ansPair.first;
  count3 = ansPair.second;

  ll ans = 1;
  int MOD = 998244353;

  while (count2 >= 10) {
    ans *= 1024;
    ans %= MOD;
    count2 -= 10;
  }
  while (count3 >= 10) {
    ans *= 59049;
    ans %= MOD;
    count3 -= 10;
  }

  while (count2 != 0) {
    ans *= 2;
    ans %= MOD;
    count2--;
  }
  while (count3 != 0) {
    ans *= 3;
    ans %= MOD;
    count3--;
  }

  cout << ans << endl;

  return 0;
}