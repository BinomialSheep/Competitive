// #include <bits/stdc++.h>
// using namespace std;
// using ll = long long;
// #define rep(i, n) for (int i = 0; i < (int)(n); i++)

// // ll arr[2 << 20];

// // int main() {
// //   ios::sync_with_stdio(false);
// //   cin.tie(nullptr);
// //   ll T;
// //   cin >> T;
// //   T *= 2;
// //   rep(i, T) cin >> arr[i];
// //   for (int i = 0; i < T;) cout << arr[i++] + arr[i++] << '\n';

// //   return 0;
// // }

// // #include <bits/stdc++.h>
// // using namespace std;
// // using ll = long long;
// // #define rep(i, n) for (int i = 0; i < (int)(n); i++)

// ll arr[2 << 20];

// int main() {
//   ios::sync_with_stdio(false);
//   cin.tie(nullptr);
//   ll T;
//   cin >> T;
//   T *= 2;
//   rep(i, T) cin >> arr[i];
//   for (int i = 0; i < T;) printf("%lld\n", arr[i++] + arr[i++]);

//   return 0;
// }

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

// ll arr[2 << 20];

// 高速入力関数
inline ll fast_input() {
  ll x = 0;
  int c = getchar_unlocked();  // 標準入力のロックを解除して高速化
  while (c < '0' || c > '9')
    c = getchar_unlocked();       // 数字が来るまで読み飛ばし
  while (c >= '0' && c <= '9') {  // 数字を読み取って数値に変換
    x = x * 10 + (c - '0');
    c = getchar_unlocked();
  }
  return x;
}

int main() {
  ll T = fast_input();  // 高速入力を使用
  rep(i, T) {
    ll A = fast_input(), B = fast_input();
    printf("%lld\n", A + B);
  }
  // rep(i, T) arr[i] = fast_input();

  // for (int i = 0; i < T;) printf("%lld ", arr[i++] + arr[i++]);

  return 0;
}
