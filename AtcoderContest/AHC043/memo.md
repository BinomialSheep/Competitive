## day1

-理想形を考えると、幹線道路があって、クラスタごとに枝葉があるみたいな構造になりそうか。

- 全点対の最短路を更新するのは厳しい
- 焼けない

- 01BFS して復元する感じか
- revert しやすいので、木上のビームサーチが最終形になりそう
  　- 「今の状態で毎ターン稼げるお金」も「ある 2 点が何か所で繋がっているか」が分かれば revert で差分更新できる

- 「繋ぐコストが money 以下で、コスパがいい順のキュー」「距離が money より大きく、繋ぐコストが小さい順のキュー」の 2 つを使うと計算量落とせそう。
- グリッドの各点について「近くにどれだけ start か target があるか」で最初に土地の価値を決めることができそう

- 線路の区画をあとから駅に上書きできる！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！

初投から数時間掛けて数百行のコードをバグらせずに書く必要があるの、そんなに初心者向けではない……。

### 初投（0.8M）

とりあえず近い順に復元して繋いでみる。
これはすごく悪い（殆どのケースで、初期マネーより少なくなる）
やはり「可能で収益性が高い」ものを選んでいく必要がある。

ChatGPT が

- 最初は収益性高く
- 中盤は全体を繋ぐように
  という構想を提示してきた。ありかも。

## day2

### 提出２（3.29M）

お金が払えてかつ距離が長い順に建てることにした。

### 考察

- 2 個駅を建てて間をつなぐ
- 1 個駅を建てて間をつなぐ
- 駅を建てずに既存の駅同士の間をつなぐ
  で整理すると分かりやすいのかも。

土地の価値が高い順に建てるか、直近の収益が高い順に建てるか、悩ましい。

### 提出３（6.51M）

全 2 点対の建てた時の収益を求めて、いい順に建てることにした。
M が大きい時は上手く回っている。でも 1660perf らしい。

### 考察

3.9M 取れているケース 54 とか見ると、近いところに結構無駄に駅を建てている。

### 提出 4（6.73M）

「駅を建てずに既存の駅同士の間をつなぐ」を入れた。

## day3

### 考察

- 「線路の途中に駅を置く」というパターンが漏れていた
  - 結局 dsu で管理するのが楽か
  - money が十分ある場合、BFS でまたがるのも良さそう

## day4

### 考察

「2 個駅を建てて間をつなぐ」を管理するための LandPairValue が複製しにくい。
よく考えたらこれが有効なのは最初の数手だけなので、最初に数回それをやったら、あとは

- 駅を建ててどこかとつなぐ（線路上なら OK）
- 駅と駅の間をつなぐ
  だけの action で良さそう。
  これで beam を打てる。

## day7

### 提出 5(6.72M)

「1 つの駅とどこかを繋ぐ」を実装

### 提出 6（19.20M）

復元で 01BFS を実装

### 提出７（19.20M）

駅が(0, 0)にある時のバグを修正

### 提出８（45.00M）

線路の上に駅を建てる可能性を追加。
スコアは伸びたが、実行時間も 373ms→2812ms に一気に伸びた。
これで 1522perf 相当らしい。ふざけてる。

### 考察

ビームや 0 遷移も考えると、高速化が必要なフェイズ。

### 提出１０（59.04M）

「1 個駅を建てる」候補を 2500 通りにしていたが、
ある市民の職場と学校に対して 1 つずつ（一番利用者が多い駅）だけを候補にするようにした。
高々数百にしかならない。
実行時間は 2204m で、あまり変わっていないが、スコアは伸びた。そうなんだ……。

array<unordered*set<int>, 2500> connected*;を使っていなかったので削除。
2204ms -> 1571ms
208004KB -> 98264KB

## 提出１１

最初の 2 個建てを 5 パターンやるようにしたけど、スコア伸びなかった。そうなんだ……。

### 考察

land_pair_value.initialize();が割と重い。84ms 掛かっている。
その後は M が大きいと重く、get_one_action が支配的に重い。特にターンが進むほど（駅が増えるほど）重くなる。

とりあえず get_one_action をヒープにする。
land_pair_value は、提出 10 みたいにする？少なくとも明らかに無駄な探索を省きたい。

#### M が小さい場合

main の実行時間のほぼすべてが naive05(TimeKeeper&) に費やされている

main の 99.2% が naive05(TimeKeeper&) に費やされており、そのほとんど (98.8%) は early_stage(std::vector<State>&) に消費されています。
つまり、early_stage がプログラムのボトルネックであり、最適化の主要ターゲットになり得る。
early_stage の中で LandPairValue::initialize() に 93.2% の時間が使われている

LandPairValue::initialize() の 87.0% (1.13 秒) が std::priority_queue::emplace に集中している。
std::priority_queue の操作（emplace, push_heap, pop_heap など）がボトルネックとなっている。
std::priority_queue::emplace() が 1.08 秒（82.0%）を消費

std::priority_queue::emplace() の内部で std::push_heap() (72.1%) や std::pair のコピー (17.8%) が大きな割合を占めている。
つまり、priority_queue の管理する要素のコピーやヒープ操作が高コストになっている。

[2] 98.8 0.00 1.30 1 naive05(TimeKeeper&) [2]
0.00 1.23 1/1 early_stage(std::vector<State, std::allocator<State> >&) [3]
0.00 0.02 73/73 Action::calc_operations(State&) [39]
0.00 0.02 73/78 Action::exec_connect_action(State&) [40]
0.00 0.02 74/74 get_one_action(State&) [46]
0.00 0.02 1/1 std::vector<State, std::allocator<State> >::vector(unsigned long, std::allocator<State> const&) [50]
0.00 0.00 72/77 State::operator=(State const&) [100]
0.00 0.00 1/7 std::vector<Operation, std::allocator<Operation> >::vector(std::vector<Operation, std::allocator<Operation> > const&) [133]
0.00 0.00 945/950 std::vector<State, std::allocator<State> >::operator[](unsigned long) [471]
0.00 0.00 218/223 State::get_turn() [559]
0.00 0.00 147/83997 bool chmax<int>(int&, int) [261]
0.00 0.00 74/84 Action::~Action() [629]
0.00 0.00 73/78 State::evaluate_score() [634]
0.00 0.00 1/1 std::allocator<State>::allocator() [782]
0.00 0.00 1/961 std::vector<Operation, std::allocator<Operation> >::vector() [470]
0.00 0.00 1/3 std::allocator<State>::~allocator() [747]
0.00 0.00 1/1 std::vector<State, std::allocator<State> >::~vector() [814]
0.00 0.00 1/1042 std::vector<Operation, std::allocator<Operation> >::~vector() [461]

#### M が大きい場合

get_one_action(State&) の実行回数が増え、72.5% の CPU 時間を消費

1337320 回 呼び出され、その大半が Board::list_new_commuters() に費やされている。
Board::list_new_commuters() が 72.0% の CPU 時間を消費

\_\_gnu_cxx::operator!= が 37.8%、std::vector<int>::operator++() が 14.7% など、リストの走査に時間を取られている。
vector<int> の反復 (std::vector<int>::begin() と std::vector<int>::end()) だけで 3.3% の CPU 時間を消費。
std::priority_queue::emplace() の負担が減少 (8.0% → 6.2%)

std::push_heap() の割合が 0.94 秒 から 0.73 秒 に減少。
State::check_update_station() の負担が大きい (18.0%)

vector<int> の走査 (operator++, operator\*) に 13.6% の CPU 時間を費やしている。
\_\_gnu_cxx::operator!= の実行回数が 1.3 × 10^9 回と非常に多い。

                0.00   10.96       1/1           main [1]

[2] 92.9 0.00 10.96 1 naive05(TimeKeeper&) [2]
0.01 8.55 69/69 get_one_action(State&) [3]
0.00 1.29 68/73 Action::exec_connect_action(State&) [11]
0.00 1.09 1/1 early_stage(std::vector<State, std::allocator<State> >&) [12]
0.00 0.01 69/69 Action::calc_operations(State&) [62]
0.00 0.01 1/1 std::vector<State, std::allocator<State> >::vector(unsigned long, std::allocator<State> const&) [82]
0.00 0.00 1/1 std::vector<State, std::allocator<State> >::~vector() [109]
0.00 0.00 68/73 State::operator=(State const&) [113]
0.00 0.00 936/941 std::vector<State, std::allocator<State> >::operator[](unsigned long) [456]
0.00 0.00 204/209 State::get_turn() [549]
0.00 0.00 137/1375339 bool chmax<int>(int&, int) [231]
0.00 0.00 69/79 Action::~Action() [599]
0.00 0.00 68/73 State::evaluate_score() [606]
0.00 0.00 1/1 std::allocator<State>::allocator() [776]
0.00 0.00 1/952 std::vector<Operation, std::allocator<Operation> >::vector() [455]
0.00 0.00 1/3 std::allocator<State>::~allocator() [750]
0.00 0.00 1/7 std::vector<Operation, std::allocator<Operation> >::vector(std::vector<Operation, std::allocator<Operation> > const&) [685]
0.00 0.00 1/1029 std::vector<Operation, std::allocator<Operation> >::~vector() [446]

## day8

## 提出１３（89.67M）

214ms, 9264KB に改善。
これでビームを検討できる。
今 235 位で 1662perf らしい。異常すぎる。

early_stage で距離が遠いものを無視。
85ms、44620KB に改善。

#### M が小さい場合（seed0）

                0.00    1.60       1/1           main [1]

[2] 99.1 0.00 1.60 1 solve(TimeKeeper&) [2]
0.00 1.52 1/1 early_stage(std::vector<State, std::allocator<State> >&) [3]
0.00 0.02 73/73 Action::calc_operations(State&) [41]
0.00 0.02 74/74 get_one_action(State&) [43]
0.00 0.02 1/1 std::vector<State, std::allocator<State> >::vector(unsigned long, std::allocator<State> const&) [54]
0.00 0.01 73/78 Action::exec_connect_action(State&) [59]
0.00 0.00 72/77 State::operator=(State const&) [98]
0.00 0.00 1/7 std::vector<Operation, std::allocator<Operation> >::vector(std::vector<Operation, std::allocator<Operation> > const&) [128]
0.00 0.00 945/950 std::vector<State, std::allocator<State> >::operator[](unsigned long) [470]
0.00 0.00 218/223 State::get_turn() [559]
0.00 0.00 147/83997 bool chmax<int>(int&, int) [258]
0.00 0.00 74/84 Action::~Action() [629]
0.00 0.00 73/78 State::evaluate_score() [634]
0.00 0.00 1/1 std::allocator<State>::allocator() [782]
0.00 0.00 1/961 std::vector<Operation, std::allocator<Operation> >::vector() [469]
0.00 0.00 1/3 std::allocator<State>::~allocator() [747]
0.00 0.00 1/1 std::vector<State, std::allocator<State> >::~vector() [814]
0.00 0.00 1/1042 std::vector<Operation, std::allocator<Operation> >::~vector() [460]

#### M が大きい場合（seed25）

                0.00    2.80       1/1           main [1]

[2] 95.3 0.00 2.80 1 solve(TimeKeeper&) [2]
0.00 1.48 65/65 get_one_action(State&) [3]
0.00 1.07 1/1 early_stage(std::vector<State, std::allocator<State> >&) [5]
0.00 0.25 64/69 Action::exec_connect_action(State&) [14]
0.00 0.00 1/1 std::vector<State, std::allocator<State> >::vector(unsigned long, std::allocator<State> const&) [102]
0.00 0.00 65/65 Action::calc_operations(State&) [107]
0.00 0.00 63/68 State::operator=(State const&) [115]
0.00 0.00 1/1 std::vector<State, std::allocator<State> >::~vector() [134]
0.00 0.00 1/7 std::vector<Operation, std::allocator<Operation> >::vector(std::vector<Operation, std::allocator<Operation> > const&) [218]
0.00 0.00 927/932 std::vector<State, std::allocator<State> >::operator[](unsigned long) [475]
0.00 0.00 191/196 State::get_turn() [565]
0.00 0.00 129/590348 bool chmax<int>(int&, int) [272]
0.00 0.00 65/75 Action::~Action() [616]
0.00 0.00 64/69 State::evaluate_score() [621]
0.00 0.00 1/1 std::allocator<State>::allocator() [783]
0.00 0.00 1/939 std::vector<Operation, std::allocator<Operation> >::vector() [474]
0.00 0.00 1/3 std::allocator<State>::~allocator() [748]
0.00 0.00 1/1007 std::vector<Operation, std::allocator<Operation> >::~vector() [467]

# day9 (2/22 Sat)

## 提出 14（123.2M）

行動を最大 10 種類行うようにした貪欲。
726 ms、76888 KB。
時間が掛かりすぎなので一旦削ってから chokudai か。

## 提出 15（150.6M）

提出 14 で、state がコピーされていないバグがあったので修正。
1338 ms、76476 KB。
これでまだ 1763perf 相当らしい。

### 考察

600 ターンくらいで打ち切っても良さそうでは？
→mx_turn が 763 なので、微妙。

最初に 2 個建てる駅の多様化
5 種類から 10 種類にしたら、
150.6M→155.0M
1338ms→1345 ms
76476 KB→76472KB
だった。効果あり。

## 提出 16（152.5M）

chokudai サーチ化したが、M が大きい時に最後まで回らなくて逆に下がる。
高速化について考える。

## 提出 17（144.4M）

復元をシンプルにするなどリファクタ。

### 考察

よく考えたら board で線路の種類を持つ必要がない。
線路の bitset と駅の bitset でいいんでは？

復元時にできるだけ価値が高いマスを踏むようにするとかどうかな？

input_K が小さい時用の特殊ソルバーを作ってもいいかも

重複排除をする。駅だけの最大値とかで排除するのが典型か？

## 提出 20（192.7M）

重複排除を実装。

## 提出 21（200.3M）

35.4GB で、2001perf。
early でできるだけ価値が高いマスを踏むようにした。

### 考察
- 小規模用ソルバー
- サイズごとのチューニング
