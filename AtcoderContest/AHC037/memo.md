# AHC037

## first submitまで
とりあえずN回の操作だけで貪欲にやる。
first submit(19:31:23)。


## 
木構造をしている。
グラフとして出次数、入次数を管理するようにすると差分更新しやすそう。
その際、コストが同じなら2本以上の辺を張っておくと削除の際の考慮が楽になって◎。
出次数が2以上の場合、明らかに改善できる。
あるいは、ランダムに頂点を置いて焼きなます方式か？


## 03
出次数が2以上のグラフについて中点を置くようにした。
4441731162点。



## 
よく考えると理想的にはグラフの出自数も入次数も2以下になる


## 06 山登り


ilu@sheep:~/Competitive/Competitive$ ./a.out < input.txt > output.txt 
add_cnt: 149 | loop_cnt: 21327
31931950954

1500頂点くらいにしかならないので、一旦グラフの機微は捨てて高速化してよさそう。
そのあとでよりよい頂点生成を検討する。




loop_cnt: 24576 | add_cnt: 307
time_threshold: 1990 | graph.calc_score(): 30958136046

loop_cnt: 217984 | add_cnt: 472
time_threshold: 19900 | graph.calc_score(): 30413108382

loop_cnt: 2033984 | add_cnt: 602
time_threshold: 199000 | graph.calc_score(): 30103394723te