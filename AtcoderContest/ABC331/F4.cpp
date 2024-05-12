#include <bits/stdc++.h>
using namespace std;
#include <atcoder/all>

// Rolling hash
const int p1 = 1000000021;
const int p2 = 1000000021;
struct mints {
  int d1, d2;
  mints(int val = 0) : d1(val), d2(val) {}
  mints(int _d1, int _d2) : d1(_d1), d2(_d2) {}
  mints operator+(const mints& a) const {
    return mints((d1 + a.d1) % p1, (d2 + a.d2) % p2);
  }
  mints operator*(const mints& a) const {
    return mints(((long)d1 * a.d1) % p1, ((long)d2 * a.d2) % p2);
  }
  bool operator==(const mints& a) const { return d1 == a.d1 && d2 == a.d2; }
};

// Segment tree
struct D {
  mints h, c;
  D(mints _h, mints _c) : h(_h), c(_c) {}
};
auto op = [](D a, D b) -> D { return D(a.h + b.h * a.c, a.c * b.c); };
auto e = []() -> D { return D(0, 1); };

int main() {
  // 入力
  int N, Q;
  cin >> N >> Q;
  string S;
  cin >> S;

  // セグ木準備
  int x = rand() % p1;
  atcoder::segtree<D, op, e> t1(N), t2(N);
  for (int i = 0; i < N; i++) t1.set(i, D(S[i], x));
  for (int i = 0; i < N; i++) t2.set(N - 1 - i, D(S[i], x));

  // クエリ
  for (int qi = 0; qi < Q; qi++) {
    int type;
    cin >> type;
    if (type == 1) {
      int i;
      char c;
      cin >> i >> c;
      --i;
      t1.set(i, D(c, x));
      t2.set(N - 1 - i, D(c, x));
    } else {
      int l, r;
      cin >> l >> r;
      --l;
      mints h1 = t1.prod(l, r).h;
      mints h2 = t2.prod(N - r, N - l).h;
      cout << (h1 == h2 ? "Yes" : "No") << "\n";
    }
  }
  cout << flush;

  return 0;
}