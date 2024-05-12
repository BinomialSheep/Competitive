#include <bits/stdc++.h>
using namespace std;

// 座標圧縮ライブラリ窃盗
// https://ei1333.github.io/luzhiled/snippets/other/compress.html
template <typename T>
struct Compress {
  vector<T> xs;
  Compress() = default;
  Compress(const vector<T>& vec) { add(vec); }
  Compress(const initializer_list<vector<T>>& vec) {
    for (auto& p : vec) add(p);
  }

  void add(const vector<T>& vec) {
    copy(begin(vec), end(vec), back_inserter(xs));
  }
  void add(const T& x) { xs.emplace_back(x); }

  void build() {
    sort(begin(xs), end(xs));
    xs.erase(unique(begin(xs), end(xs)), end(xs));
  }

  vector<int> get(const vector<T>& vec) const {
    vector<int> ret;
    transform(begin(vec), end(vec), back_inserter(ret), [&](const T& x) {
      return lower_bound(begin(xs), end(xs), x) - begin(xs);
    });
    return ret;
  }

  int get(const T& x) const {
    return (int)(lower_bound(begin(xs), end(xs), x) - begin(xs));
  }
  // inverted
  const T& operator[](int k) const { return xs[k]; }
};

int main() {
  /* input */
  int N;
  cin >> N;
  vector<long long> A(N);
  for (int i = 0; i < N; i++) cin >> A[i];
  /* solve */
  Compress c(A);
  c.build();
  /* output */
  for (int i = 0; i < N; i++) cout << c.get(A[i]) << "\n";

  return 0;
}
