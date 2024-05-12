#include <bits/stdc++.h>

// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
using namespace std;
using ll = long long;

map<pair<ll, ll>, bool> mp;

bool f(ll a, ll s) {
  if (!s) return a == 0;
  auto p = make_pair(a, s);
  // メモに記録済みならそれを返す
  if (mp.count(p)) return mp[p];
  // 1番下の桁だけに注目し、(x, y) = (0, 0)..(1,1)の4パターンを試す
  rep(x, 2) rep(y, 2) {
    // x & yとaの1桁目（a&1で取り出せる）は一致している必要がある
    if ((x & y) != (a & 1)) continue;
    // (x + y)がsよりも大きいとダメ（それはそう）
    if (s - x - y < 0) continue;
    // sの1桁目と、(x+y)の1桁目は一致している必要がある(s&1 != (x XOR y))
    if ((s - x - y) % 2 != 0) continue;
    // ここまで成り立っていれば、1番下の桁については矛盾なしOK
    // 1番下の桁を削除したものについて再帰的に試す。ただしsについては繰り上がりを考慮している（x+yが2の場合のみ、sの2桁目から1引かれる）
    // OKならメモに入れてから返す（mpをクリアするように変更したからこれ不要？）
    if (f(a >> 1, (s - x - y) >> 1)) return mp[p] = true;
  }
  // どのパターンもダメならメモに入れる（メモ化再帰）
  return mp[p] = false;
}

void solve() {
  ll a, s;
  cin >> a >> s;
  mp = map<pair<ll, ll>, bool>();
  if (f(a, s))
    cout << "Yes" << endl;
  else
    cout << "No" << endl;
}

int main() {
  int t;
  cin >> t;
  rep(ti, t) solve();

  return 0;
}