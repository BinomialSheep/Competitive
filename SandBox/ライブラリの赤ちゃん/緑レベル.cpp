#include <bits/stdc++.h>
using namespace std;
// その場で書いてもいいのでスニペットに入れていないシリーズ

int main() {
  // 座標圧縮(0-indexed)
  auto compress = [&](vl& vec) -> map<ll, int> {
    map<ll, int> mp;
    set<ll> st;
    for (auto v : vec) st.insert(v);
    int i = 0;
    for (auto v : st) mp[v] = i++;
    return mp;
  };
  /*
  これでも計算量は同じだが、二分探索verにしてもいい
  多相ラムダ式ってどう書くの？
  スニペットにするならconversionメソッドも入れてクラスにするなど検討
  */

  return 0;
}