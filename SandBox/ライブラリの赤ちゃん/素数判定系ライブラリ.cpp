#include <bits/stdc++.h>
using namespace std;

/* 1個の整数について考えればいいならこっち */
// シンプルな約数判定 O(√N)
// シンプルな素因数分解 O(√N)

/* エラトステネスのふるいを利用した諸々 */
// 素数判定
// 約数列挙
// 素因数分解（prime factorization）
// ↑前処理 O(N loglog N)、クエリあたりN log N
// 高速ゼータ変換
// 高速メビウス変換

// TODO：より高速なふるいの実装
// アトキンのふるい（O(N/loglogN)、線形ふるい(O(N))

// 普通の素数判定(O(log(√N)))
bool isPrimeSimple(long long N) {
  if (N == 1) return false;
  for (long long i = 2; i * i <= N; ++i) {
    if (N % i == 0) return false;
  }
  return true;
}

// 普通の素因数分解 O(√N)
template <typename T>
vector<pair<T, T>> calcPrimeFactorSimple(T n) {
  vector<pair<T, T>> ret;
  for (T i = 2; i * i <= n; i++) {
    if (n % i != 0) continue;
    T tmp = 0;
    while (n % i == 0) {
      tmp++;
      n /= i;
    }
    ret.emplace_back(i, tmp);
  }
  if (n != 1) ret.emplace_back(n, 1);
  return ret;
}

// シンプルな約数列挙(O(√N))
// 1e6以下の最大の約数の個数は240、1e9で1344,
// 1e12で6720, 1e18で103680
vector<long long> calc_divisors(long long N) {
  // 答えを表す集合
  vector<long long> res;

  // 各整数 i が N の約数かどうかを調べる
  for (long long i = 1; i * i <= N; ++i) {
    // i が N の約数でない場合はスキップ
    if (N % i != 0) continue;

    // i は約数である
    res.push_back(i);

    // N ÷ i も約数である (重複に注意)
    if (N / i != i) res.push_back(N / i);
  }
  // 約数を小さい順に並び替えて出力
  sort(res.begin(), res.end());
  return res;
}

// 素数列挙：O(N loglogN)
// 素因数分解：O(N longN)
struct Eratosthenes {
  // 1-indexed
  vector<bool> isPrime;
  // 整数iを割り切る最小の素数
  vector<int> minfactor;
  // メビウス関数値
  vector<int> mobius;
  //
  int size;

  // コンストラクタ
  Eratosthenes(int N)
      : isPrime(N + 1, true), minfactor(N + 1, -1), mobius(N + 1, 1), size(N) {
    isPrime[1] = false;
    minfactor[1] = 1;
    // ふるい
    for (int p = 2; p <= N; ++p) {
      // すでに合成数ならスキップ
      if (!isPrime[p]) continue;
      // pはpで割り切れる
      minfactor[p] = p;

      mobius[p] = -1;

      // p以外のpの倍数を合成数に
      for (int q = p * 2; q <= N; q += p) {
        isPrime[q] = false;
        // qはpで割り切れる旨を更新
        if (minfactor[q] == -1) minfactor[q] = p;
        // nが2回以上割り切れるなら0、そうでなければ符号反転
        if ((q / p) % p == 0)
          mobius[q] = 0;
        else
          mobius[q] = -mobius[q];
      }
    }
  }

  // 高速素因数分解 O(N log N)
  vector<pair<int, int>> factorize(int n) {
    vector<pair<int, int>> res;
    while (n > 1) {
      int p = minfactor[n];
      int exp = 0;
      // nで割れるだけ割る
      while (minfactor[n] == p) {
        n /= p;
        ++exp;
      }
      res.emplace_back(p, exp);
    }
    return res;
  }

  // 約数列挙：O(約数の個数個)。n <= 10^9の場合1344
  vector<int> divisors(int n) {
    vector<int> res({1});
    // nを素因数分解
    auto pf = factorize(n);
    // 約数列挙
    for (auto p : pf) {
      int s = (int)res.size();
      for (int i = 0; i < s; ++i) {
        int v = 1;
        for (int j = 0; j < p.second; ++j) {
          v *= p.first;
          res.push_back(res[i] * v);
        }
      }
    }
    return res;
  }
};

// 高速ゼータ変換
// 入力 f が in-place に更新されて、F になる
template <class T>
void fastZeta(vector<T> &f) {
  int N = (int)f.size();

  // エラトステネスの篩を用いて素数を列挙
  Eratosthenes er(N);
  vector<bool> isprime = er.isPrime;

  // 各素数 p 軸に対して
  // 大きい座標 (k * p) から小さい座標 (k) へと足し込む
  for (int p = 2; p < N; ++p) {
    if (!isprime[p]) continue;

    // 座標が大きい方を起点として累積和をとる
    for (int k = (N - 1) / p; k >= 1; --k) {
      f[k] += f[k * p];
    }
  }
}

// 高速メビウス変換
// 入力 F が in-place に更新されて、f になる
template <class T>
void fastMobius(vector<T> &F) {
  int N = (int)F.size();

  // エラトステネスの篩を用いて素数を列挙
  Eratosthenes er(N);
  vector<bool> isprime = er.isPrime;

  // 各素数 p 軸に対して
  // 小さい座標 (k) から大きい座標 (k * p) を引いていく
  for (int p = 2; p < N; ++p) {
    if (!isprime[p]) continue;

    // 座標が小さい方を起点として差分をとる
    for (int k = 1; k * p < N; ++k) {
      F[k] -= F[k * p];
    }
  }
}

// 素数列挙テスト
void printPrimeList(Eratosthenes &er) {
  cout << "素数列挙テスト" << endl;
  for (int v = 1; v <= er.size; ++v) {
    // 入れると遅くなるので注意
    assert(isPrimeSimple(v) == er.isPrime[v]);

    cout << v << ": " << (er.isPrime[v] ? "prime" : "not") << endl;
  }
}

// 素因数分解テスト
void printPrimeFactorization(Eratosthenes &er) {
  cout << "素因数分解テスト" << endl;
  for (int n = 2; n <= er.size; ++n) {
    auto pf = er.factorize(n);
    // 入れると遅くなるので注意
    vector<pair<int, int>> pf2 = calcPrimeFactorSimple(n);
    cout << n << ": ";
    for (int i = 0; i < (int)pf.size(); ++i) {
      assert(pf[i].first == pf2[i].first);
      assert(pf[i].second == pf2[i].second);
      if (i > 0) cout << " * ";
      cout << pf[i].first << "^" << pf[i].second;
    }
    cout << endl;
  }
}

// 高速ゼータ変換テスト
void printZetaTransform() {
  // f[0] は関係ないので適当な値を入れておく
  vector<int> f = {-1000, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
  fastZeta(f);

  cout << "高速ゼータ変換テスト" << endl;
  for (int i = 1; i < (int)f.size(); ++i) {
    cout << i << ": " << f[i] << endl;
  }
}

// 高速メビウス変換テスト
void printMobiusTransform() {
  // f[0] は関係ないので適当な値を入れておく
  vector<int> f = {-1000, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

  // 高速ゼータ変換
  fastZeta(f);

  // 高速メビウス変換で元に戻す
  fastMobius(f);

  cout << "高速メビウス変換テスト" << endl;
  for (int i = 1; i < (int)f.size(); ++i) {
    cout << i << ": " << f[i] << endl;
  }
}

int main() {
  Eratosthenes er(50);
  printPrimeList(er);
  printPrimeFactorization(er);
  printZetaTransform();
  printMobiusTransform();
}