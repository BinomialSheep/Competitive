#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vl = vector<long long>;
using vb = vector<bool>;
using vs = vector<string>;
using vc = vector<char>;
using vpii = vector<pair<int, int>>;
using vpll = vector<pair<long long, long long>>;
using vvi = vector<vector<int>>;
using vvb = vector<vector<bool>>;
using vvl = vector<vector<long long>>;
using vvc = vector<vector<char>>;
using vvvi = vector<vector<vector<int>>>;
//#include <atcoder/all>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define MAX 10000
#define INFTY (1 << 30)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)
ll llMax(ll x, ll y) { return (x >= y) ? x : y; }
ll llMin(ll x, ll y) { return (x <= y) ? x : y; }

// Zobrist Hashを使った解法
struct custom_hash {
  static uint64_t splitmix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }

  size_t operator()(uint64_t x) const {
    // 実行するまで値が分からないため、撃墜されにくい
    static const uint64_t FIXED_RANDOM =
        chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x + FIXED_RANDOM);
  }
} rng;

int main() {
  /* input */
  int N;
  cin >> N;

  // hashA[i] := 数列aの先頭からi個分の集合を表すハッシュ値

  // N個の入力を受け取って、Zobrist Hashを返す
  auto hashing = [&]() -> vector<uint64_t> {
    vector<uint64_t> hash(N + 1, 0);
    // ここまでの数列の集合
    set<ll> S;
    rep(i, N) {
      ll x;
      cin >> x;

      // すでに含まれているなら変わらない
      if (S.count(x)) {
        hash[i + 1] = hash[i];
        continue;
      }
      S.insert(x);
      // 各要素に対して乱数を割り当てたあとで、XORをとる
      hash[i + 1] = hash[i] ^ rng(x);
    }
    return hash;
  };

  /* solve */
  const auto& hashA = hashing();
  const auto& hashB = hashing();

  // クエリ処理
  int Q;
  cin >> Q;
  while (Q--) {
    int x, y;
    cin >> x >> y;
    cout << (hashA[x] == hashB[y] ? "Yes" : "No") << endl;
  }

  /* output */

  return 0;
}