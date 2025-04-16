#include <bits/stdc++.h>
using namespace std;

/*
    問題:
      N, M が与えられ,
      N 個の要素 x_1..x_N (全部 0 初期) に対して M 回の操作が可能.
      i 回目の操作は以下の3つのうち1つを選ぶ:
        操作0: 何もしない        (コスト0)
        操作1: [L_i..R_i] 内を1に (コスト1)
        操作2: [L_i..R_i] 外を1に (コスト1)
      最終的に x_1..x_N 全部を1にしたい。
      できれば最小コスト、その操作の種類を出力。できないなら -1。

    制約:
      1 <= N <= 1,000,000
      1 <= M <= 200,000
      1 <= L_i <= R_i <= N

    解法(概要):
      1. コスト1で可能？ -> "ある1区間が[1..N]を覆う"場合。
      2. コスト2で可能？ -> 4パターン(A,Bは[Li..Ri]):
           (1) A ∪ B = [1..N]         (両方操作1)
           (2) A ∩ B = ∅ => A^c ∪ B^c=[1..N] (両方操作2)
           (3) A ⊂ B => A ∪ B^c=[1..N] (片方1, 片方2)
           (4) B ⊂ A => B ∪ A^c=[1..N] (片方1, 片方2)
      3. どれでもダメなら -1
*/

struct Interval {
  int L, R, idx;  // idxは元の入力順
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int N, M;
  cin >> N >> M;

  vector<Interval> intervals(M);
  for (int i = 0; i < M; i++) {
    cin >> intervals[i].L >> intervals[i].R;
    intervals[i].idx = i;  // 後で出力順に使う
  }

  // ---- Step1: コスト1で達成可能か？ ----
  //     [1..N] を覆う区間があれば OK
  {
    for (int i = 0; i < M; i++) {
      if (intervals[i].L == 1 && intervals[i].R == N) {
        // これ1回操作1にすれば全部1になる
        // 出力 (コスト=1)
        cout << 1 << "\n";
        // i番目のみ操作1, 他0
        vector<int> ans(M, 0);
        ans[i] = 1;
        for (int j = 0; j < M; j++) {
          cout << ans[j];
          if (j + 1 < M) cout << " ";
        }
        cout << "\n";
        return 0;
      }
    }
  }

  // ---- 以下コスト2でできるかを順にチェックする ----
  //    見つかれば出力して終了

  // ---- (1) A ∪ B = [1..N] (両方操作1) ----
  //  - たとえば「L=1 の区間」の中で最も R が大きいものをAとし、
  //    そこから先を最後まで覆える区間B(R=N)があればOK というチェック例。
  {
    // まず L=1 かつ R が最大のものを探す
    int bestIdx = -1;  // その区間の idx
    int maxR = -1;     // その区間の R
    for (int i = 0; i < M; i++) {
      if (intervals[i].L == 1 && intervals[i].R > maxR) {
        maxR = intervals[i].R;
        bestIdx = i;
      }
    }
    // bestIdx != -1 のとき → A = intervals[bestIdx] が [1..maxR] を覆う
    if (bestIdx != -1 && maxR < N) {
      // まだ全部は覆っていないので、後半部分 [maxR+1 .. N]
      // を覆う区間があるか確認 具体的には L <= maxR+1 かつ R = N
      // という区間があれば良い
      for (int j = 0; j < M; j++) {
        if (j == bestIdx) continue;
        if (intervals[j].L <= maxR + 1 && intervals[j].R == N) {
          // 2つの操作で [1..N] をカバーできる
          // -> 両方操作1, コスト2
          cout << 2 << "\n";
          vector<int> ans(M, 0);
          ans[bestIdx] = 1;  // 操作1
          ans[j] = 1;        // 操作1
          for (int k = 0; k < M; k++) {
            cout << ans[k];
            if (k + 1 < M) cout << " ";
          }
          cout << "\n";
          return 0;
        }
      }
    }
  }

  // ---- (2) A ∩ B = ∅ => A^c ∪ B^c = [1..N] (両方操作2) ----
  //  - 交わらない2区間があれば、その補集合の和集合は全体になる
  //  - 交わらない条件: R_A < L_B or R_B < L_A
  //  - 下の例では「R 昇順ソート」を使って「suffixの最小L」を比較
  {
    auto intervals2 = intervals;
    // R 昇順にソート
    sort(intervals2.begin(), intervals2.end(),
         [](auto &a, auto &b) { return a.R < b.R; });
    // suffixMinL[i]: intervals2[i..] の中で最小の L
    vector<int> suffixMinL(M + 1, INT_MAX);
    for (int i = M - 1; i >= 0; i--) {
      suffixMinL[i] = min(suffixMinL[i + 1], intervals2[i].L);
    }
    // 走査: intervals2[i] と交わらない区間が i+1 以降にあるか？
    for (int i = 0; i < M - 1; i++) {
      int curR = intervals2[i].R;
      // 後ろにある区間のうち最小の L
      int candidateL = suffixMinL[i + 1];
      if (candidateL > curR) {
        // すなわち intervals2[i] の R より L が大きい区間が存在する =>
        // 交わらない 実際にどれか1つその区間を探す
        for (int j = i + 1; j < M; j++) {
          if (intervals2[j].L > curR) {
            // i, j が交わらない
            // -> 両方操作2
            cout << 2 << "\n";
            vector<int> ans(M, 0);
            ans[intervals2[i].idx] = 2;
            ans[intervals2[j].idx] = 2;
            for (int k = 0; k < M; k++) {
              cout << ans[k];
              if (k + 1 < M) cout << " ";
            }
            cout << "\n";
            return 0;
          }
        }
      }
    }
  }

  // ---- (3)(4) 包含関係: A ⊂ B or B ⊂ A ----
  //      => A ∪ B^c = [1..N] あるいは B ∪ A^c = [1..N]
  //      => (片方操作1, 片方操作2) でカバー
  // ソートで「L 昇順、L 同じなら R 降順」にしてチェックする例を2回行う:
  //   - 1回目の走査で「A ⊂ B」を見つける
  //   - 2回目の走査で「B ⊂
  //   A」を見つける（ソート順変えてもよいが、ここでは2回ほぼ同じ処理）
  {
    auto intervals2 = intervals;
    // (3) A ⊂ B  → A∪B^c=[1..N]
    //     ソート: L 昇順, L 同値なら R 降順
    sort(intervals2.begin(), intervals2.end(), [](auto &a, auto &b) {
      if (a.L == b.L) return a.R > b.R;  // L同じならR大きい方を先に
      return a.L < b.L;
    });
    // maxR: これまで見た中で最大のR
    // maxR_idx: その区間のidx
    int maxR = -1;
    int maxR_idx = -1;
    for (int i = 0; i < M; i++) {
      int curL = intervals2[i].L;  // ソートにより, すでに past.L <= curL
      int curR = intervals2[i].R;
      int curIdx = intervals2[i].idx;

      // 過去に出てきた区間( maxR_idx ) のR が今の curR より大きければ
      // その過去区間は「L_past <= L_cur」(ソートによる) かつ「R_past >= curR」
      // つまり intervals2[i] が含まれている → (A ⊂ B)
      if (maxR >= curR && maxR_idx != -1) {
        // 包含元 = intervals2[ maxR_idx ]
        // 包含先 = intervals2[i]
        // => (A, B)=(含まれる区間, 包含する区間)
        // => Aを操作1, Bを操作2にして A ∪ B^c = [1..N]
        //  (A⊂B なら B^c が「A の外側」も含んで全域をカバー可能)
        cout << 2 << "\n";
        vector<int> ans(M, 0);
        // A = curIdx → 操作1
        ans[curIdx] = 1;
        // B = maxR_idx → 操作2
        ans[maxR_idx] = 2;
        for (int k = 0; k < M; k++) {
          cout << ans[k];
          if (k + 1 < M) cout << " ";
        }
        cout << "\n";
        return 0;
      }
      // maxR を更新
      if (curR > maxR) {
        maxR = curR;
        maxR_idx = curIdx;
      }
    }
  }

  {
    // (4) B ⊂ A → B∪A^c=[1..N]  (片方1,片方2)
    //   今度は R 昇順, R 同値なら L 降順 とか、あるいは
    //   L 降順のまま逆向きにたどってもいいですが、
    //   ここでは簡単のため「R 昇順, R同じならL降順」でソートし直す例
    auto intervals2 = intervals;
    sort(intervals2.begin(), intervals2.end(), [](auto &a, auto &b) {
      if (a.R == b.R) return a.L < b.L;  // R同じならLが小さい方を先
      return a.R < b.R;
    });
    // minL: これまで見た中で最小の L
    // minL_idx: その区間の idx
    // いま見ている区間(大きいR)が過去の区間(小さいR)を含むかどうか → (B ⊂ A)
    //   B: Rが小さいほう, A: Rが大きいほう
    //   R_B <= R_A （ソート上自明に Bが先）
    //   L_A <= L_B   が必要
    int minL = INT_MAX;
    int minL_idx = -1;
    for (int i = 0; i < M; i++) {
      int curR = intervals2[i].R;
      int curL = intervals2[i].L;
      int curIdx = intervals2[i].idx;

      // いま見てる区間を「A」(Rが大きい側) とみる
      // 過去に出てきた区間を「B」(Rが小さい側) とみると
      // B ⊂ A の条件: L_A <= L_B and R_B <= R_A(今のソート順でR_B <=
      // R_Aは自動OK) だから (過去の区間のL) >= (今の区間のL) ならダメ
      //          (過去の区間のL) >= L_A → Bが左にあるか同じか
      // 実際は「BのL >= AのL」 => BがAに含まれる となる
      // ここはややややこしいですが例として実装
      // minL = これまでの中で最小の L(B)
      // AのL(curL) <= BのL(minL) なら B ⊂ A(=今の)
      if (minL_idx != -1) {
        // 過去に区間がある
        if (curL <= minL) {
          // 今見ている区間(A)のL <= 過去区間(B)のL なら Bが含まれている
          // B = intervals2[minL_idx], A = intervals2[i]
          cout << 2 << "\n";
          vector<int> ans(M, 0);
          // B => 操作1, A => 操作2  (B ⊂ A  -> B∪A^c=[1..N])
          ans[intervals2[minL_idx].idx] = 1;
          ans[curIdx] = 2;
          for (int k = 0; k < M; k++) {
            cout << ans[k];
            if (k + 1 < M) cout << " ";
          }
          cout << "\n";
          return 0;
        }
      }

      // minL を更新
      if (curL < minL) {
        minL = curL;
        minL_idx = i;  // i 番目のintervals2に入ってる
      }
    }
  }

  // ---- ここまで来たらコスト2でも不可能 ----
  cout << -1 << "\n";
  return 0;
}
