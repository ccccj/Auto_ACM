//
//  main.cpp
//  7.24
//
//  Created by admin on 18/7/24.
//  Copyright © 2018年 Amon. All rights reserved.
//
// K(一道简单的混合背包)
Description
麻烦的渣渣辉又要和女朋友去旅游啦。

他们有一个最多能用V公斤的背包，现在有n件物品，它们的重量分别是W1，W2，...Wn，它们的价值分别为C1C2...Cn。

有的物品只可以取一次（01背包），有的物品可以取无限次（完全背包），有的物品可以取的次数有一个上限（多重背包）。

求解将哪些物品装入背包可使这些物品的费用总和不超过背包容量，且价值总和最大。

Input
第一行：二个整数，V(背包容量，V<=200)，N(物品数量，N<=30)；

第2..N+1行：每行三个整数WiCiPi，前两个整数分别表示每个物品的重量，价值，第三个整数若为0，则说明此物品可以购买无数件，若为其他数字，则为此物品可购买的最多件数(Pi)。
Output
仅一行，一个数，表示最大总价值。

Sample Input
10 3
2 1 0
3 3 1
4 5 4
Sample Output
11

#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int v[2010];
int w[2010];
int num[1010];
int dp[20005];

int main() {
    int n, bag;
    while (cin >> bag >> n) {
        
        memset(dp, 0, sizeof(dp));
        for (int i = 1; i <= n; ++i) {
            scanf("%d%d%d", &v[i], &w[i], &num[i]);
        }
        
        int k = n + 1;
        for (int i = 1; i <= n; ++i) {
            if (num[i] <= 1) {
                continue;
            }
            int d = 1;
            while (num[i] > d) {
                v[k] = d * v[i];
                w[k++] = d * w[i];
                num[i] -= d;
                d *= 2;
            }
            v[i] *= num[i];
            w[i] *= num[i];
        }
        
        for (int i = 1; i < k; ++i) {
            if (num[i] > 0)  // 01背包/多重背包
                for (int j = bag; j >= v[i]; --j) {
                    dp[j] = max(dp[j], dp[j-v[i]] + w[i]);
                }
            else  // 完全背包
                for (int j = v[i]; j <= bag; ++j) {
                    dp[j] = max(dp[j], dp[j-v[i]] + w[i]);
                }
        }
        cout << dp[bag] << endl;
        
    }
    return 0;
}


// J
Description
双十一就这样轰轰烈烈的来了，对于一个买东西只靠网购的资深宅男小灰灰来说，这的确是个令人兴奋的事情。
而现在的小灰灰却是痛并快乐着，因为本就干瘪的钱包实在挤不出多少money用来购物了，谁叫他把钱都用来买纸了呢....话说钱到用时方恨少，小灰灰处在深深的忧虑中，不知道怎样才能用剩下的钱买到最有价值的东西，各位小伙伴你们能把他搞定这件事吗
Input
第一行一个整数T表示有T组测试数据（T<=50）。
接下来的T组测试数据：
第一行包含两个整数N和M，N表示小灰灰有多少钱，M表示有多少件物品（1<=M<=100）。
再二行包含M个整数，表示对应每个物品的价格。
第三行包含M个整数，表示对应每个物品的价值。
0<N，A，B<3000
Output
请帮助小灰灰使用仅有的钱购买物品，并使物品的总价值最大。输出最大值。
Sample Input
4
10 5
2 3 7 7 3
4 3 5 6 4
10 8
5 6 4 2 3 7 1 8
5 3 5 3 5 7 5 7
20 7
10 15 4 5 6 8 5
15 14 9 2 2 6 7
10 3
7 4 5
16 7 10
Sample Output
Case #1: 11
Case #2: 18
Case #3: 31
Case #4: 17

#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int v[110];
int w[110];
int dp[3010];

int main() {
    int t, n, bag, c = 1;
    cin >> t;
    while (t--) {
        cin >> bag >> n;
        memset(dp, 0, sizeof(dp));
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &v[i]);
        }
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &w[i]);
        }
        
        for (int i = 1; i <= n; ++i) {
            for (int j = bag; j >= v[i]; --j) {
                dp[j] = max(dp[j], dp[j-v[i]] + w[i]);
            }
        }
        printf("Case #%d: ", c++);
        cout << dp[bag] << endl;
    }
    return 0;
}


// I
Description
某国为了防御敌国的导弹袭击发展出一种导弹拦截系统.但是这种导弹拦截系统有一个缺陷:虽然它的第一发炮弹能够到达任意的高度但是以后每一发炮弹都不能超过前一发的高度.某天雷达捕捉到敌国的导弹来袭.由于该系统还在试用阶段所以只有一套系统因此有可能不能拦截所有的导弹.

怎么办呢?多搞几套系统呗!你说说倒蛮容易成本呢?成本是个大问题啊.所以俺就到这里来求救了请帮助计算一下最少需要多少套拦截系统.

Input
输入若干组数据.每组数据包括:导弹总个数(正整数)导弹依此飞来的高度(雷达给出的高度数据是不大于30000的正整数用空格分隔)

Output
对应每组数据输出拦截所有导弹最少要配备多少套这种导弹拦截系统.

Sample Input
8 389 207 155 300 299 170 158 65
Sample Output
2

#include <iostream>
#include <cstring>
using namespace std;

int arr[20010];
int m[20010];

int main() {
    int n;
    while (cin >> n) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &arr[i]);
        }
        int max_num = 1;
        for (int i = 1; i <= n; ++i) {
            int tmp = 0;
            for (int j = 1; j < i; ++j) {
                if (arr[i] > arr[j] && tmp < m[j]) {
                    tmp = m[j];
                }
            }
            m[i] = tmp + 1;
            max_num = max(max_num, m[i]);
        }
        cout << max_num << endl;
    }
    
    return 0;
}


// H
Description
创客的装备有点老旧啦，所以老师想给创客更新装备。

每个显示屏都有它的固有属性——刷新频率 T 和价格 S。

现在有 N 台显示屏可供选择，老师想购置 3 台新的显示屏放在创客。

老师对于购买显示屏的要求是：

1.对 N 台显示屏按照输入顺序标号为1，2，3 ... N。

2.对于购买的3个显示屏的编号 i < j < k 需要满足 Ti < Tj < Tk。

3.需要购买的显示屏总价格最小。

你能算出购买到符合老师要求的 3 台显示屏最少需要多少钱吗？

Input
输入包括多组测试样例。

对于每组测试样例：

第一行输入一个正整数 N ，表示有 N 台显示屏可供选择。（1 <= N <= 3000）。

第二行输入 N 个正整数，第 i 个数字表示第 i 台显示屏的刷新频率 Ti。（1 <= Ti <= 109）

第三行输入 N 个正整数，第 i 个数字表示第 i 台显示屏的价格 Si。（1 <= Si <= 108）

Output
对于每组测试样例输出占一行，输出结果为可花费的最小价格。

如果无法购买到合适的 3 台显示屏，输出 -1。

Sample Input
5
2 4 5 4 10
40 30 20 10 40
3
100 101 100
2 4 5
10
1 2 3 4 5 6 7 8 9 10
10 13 11 14 15 12 13 13 18 13
Sample Output
90
-1
33
HINT

在第一个示例中，您可以选择第 1，第 4 和第 5 台显示屏，因为 T1 < T4 <  T5，（ 2 < 4 < 10），价格是 40 + 10 + 40 = 90。


在第二个示例中，没有办法购置 3 台合适的显示屏，因此答案为 -1。

#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int main() {
    int n;
    int t[3010];
    int s[3010];
    
    int dp[4][3010];
    
    while (cin >> n) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &t[i]);
        }
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &s[i]);
        }
        
        fill(dp[2] + 1, dp[2] + n + 1, 300000010);
        fill(dp[3] + 1, dp[3] + n + 1, 300000010);
        
        
        // dp[k][i] 存储当前花费
        for (int i = 1; i <= n; ++i) {
            dp[1][i] = s[i];
        }
        for (int k = 2; k < 4; ++k) {
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j < i; ++j) {
                    if (t[i] > t[j]) {
                        dp[k][i] = min(dp[k][i], dp[k-1][j] + s[i]);
                    }
                }
            }
        }
        int m = 300000010;
        for (int i = 3; i <= n; ++i) {
            m = min(m, dp[3][i]);
        }
        if (m == 300000010) {
            cout << -1 << endl;
        }
        else cout << m << endl;
        
    }
    
    return 0;
}


// G
Description
渣渣辉非常喜欢跳来跳去。

但是现在他遇到了一个艰巨的任务。

给定一个由正整数构成的一维地图，该图上某一点的值代表在该点时可以跳跃的最大长度。

渣渣辉想要用最少的跳跃次数跳到地图的最右边一个位置。

(保证可以到达终点。)

Input
输入包括多组测试样例。

对于每个测试样例：

第一行输入为正整数 N ，代表一维地图的大小。（0 <= N <= 100）。

第二行输入为 N 个正整数，为地图该点可以跳跃的最大长度 K 。(0 <= K <= 100)。

Output
对于每一个测试样例输出一行，结果为跳跃到最右一个位置的最少跳跃次数。

Sample Input
5
2 3 1 1 4
6
2 3 1 4 2 4
Sample Output
2
3
HINT

对于第一个测试样例：


渣渣辉从第一个位置调到第二个位置，为第一次跳跃；再从第二个位置调到第五个位置为第二次跳跃。游戏结束。

#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int arr[110];
int b[110];

int main() {
    int n;
    while (cin >> n) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &arr[i]);
        }
        b[1] = 0;
        for (int i = 2; i <= n; ++i) {
            b[i] = 20000;
        }
        for (int i = 2; i <= n; ++i) {
            for (int j = 1; j < i; ++j) {
                if (arr[j] + j >= i) {
                    b[i] = min(b[i], b[j] + 1);
                }
            }
        }
        cout << b[n] << endl;
        
    }
    
    return 0;
}


// F
Description
结婚后的渣渣辉春光满面。

渣渣辉可是一个世纪好男人，下得了厅堂，进的了厨房。

有一天渣渣辉要去买菜。

妻管严的他只能拿到了N块钱，但是却得到了一个很无理的要求：

有M种菜，每种菜都有一定的数量（非0且不可能无限）。

已知每种菜的价格和好感度，要求是买的菜总好感度要最大。

都说“结了婚的男人会变笨”，你能帮帮他吗？


Input
输入数据的第一行为T，表示输入的测试样例数目（0 <= T <= 100）。

对于每个测试样例：

第一行输入为N，M，表示渣渣辉的总钱数为 N，有 M 种菜。( 1 <= N <= 1000，1 <= M <= 1000）。
                               
接下来 M 行输入三个正整数 Wi，Hi，Ci，表示第i种菜的价位为W，好感度为H，菜的数量C。（0 <= W，H，C <= 1000）。
                               
Output
对于每一个样例输出一行，结果为渣渣辉可以买的最大好感度。
Sample Input
1
20 5
4 20 3
3 12 4
6 15 2
8 12 1
5 8 3
Sample Output
88
                               
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int v[2010];
int w[2010];
int num[1010];
int dp[20005];

int main() {
    int t, n, bag;
    cin >> t;
    while (t--) {
        cin >> bag >> n;
        memset(dp, 0, sizeof(dp));
        for (int i = 1; i <= n; ++i) {
            scanf("%d%d%d", &v[i], &w[i], &num[i]);
        }
        int k = n + 1;
        for (int i = 1; i <= n; ++i) {
            int d = 1;
            while (num[i] > d) {
                v[k] = d * v[i];
                w[k++] = d * w[i];
                num[i] -= d;
                d *= 2;
            }
            v[i] *= num[i];
            w[i] *= num[i];
        }
        for (int i = 1; i < k; ++i) {
            for (int j = bag; j >= v[i]; --j) {
                dp[j] = max(dp[j], dp[j-v[i]] + w[i]);
            }
        }
        cout << dp[bag] << endl;
    }
    return 0;
}


// E
Description
渣渣辉快要和女朋友结婚啦！

所以他要和女朋友去度蜜月了，他还是用最大容量为N的行李箱。

当然渣渣辉女朋友的东西超级多。

漂亮衣服、鞋子、化妆品等 M 种物品都可以视为无限个。


已经知道了每种物品体积大小 V和的重要度 W ，渣渣辉想要带上的物品总重要度最高，你能帮帮他吗？

(每个物品都只有一件，且行李箱子可以不装满。)


Input
输入包含多组测试样例。

对于每组测试数据：

第一行输入两个正整数N和M，表示行李箱最大容量为N，物品数量为M；（1 <= M，N <= 100）

第二行输入M个正整数，第i个数字表示第i个物品的体积。( 1 <= Vi <= 1000)

第三行输入M个正整数，第i个数字表示第i个物品的重要度。( 1 <= Wi <= 1000)

Output
对于每一个样例输出一行，结果为渣渣辉可以带上的物品的最大总重要度。
Sample Input
17 5
10 8 5 6 1
14 7 6 4 1
Sample Output
22

#include <iostream>
#include <cstring>
using namespace std;

int v[110];
int w[110];
int dp[110];

int main() {
    int n, bag;
    while(cin >> bag >> n) {
        memset(dp, 0, sizeof(dp));
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &v[i]);
        }
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &w[i]);
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = v[i]; j <= bag; ++j) {
                dp[j] = max(dp[j], dp[j-v[i]] + w[i]);
            }
        }
        cout << dp[bag] << endl;
    }
    return 0;
}

// D
Description
(假设)渣渣辉有个女朋友，他女朋友非常喜欢旅游。

所以渣渣辉买了一个最大容量为 N 的行李箱，想带他女朋友去旅游。

但是渣渣辉女朋友想带的物品真的太多太多啦。

已经知道了每个物品体积大小 V 和的重要度 W ，渣渣辉想要带上的物品总重要度最高，你能帮帮他吗？

(每个物品都只有一件，且行李箱子可以不装满。)


Input
输入包含多组测试样例。

对于每组测试数据：

第一行输入两个正整数N和M，表示行李箱最大容量为N，物品数量为M；（1 <= M，N <= 100）

第二行输入M个正整数，第i个数字表示第i个物品的体积。( 1 <= Vi <= 1000)

第三行输入M个正整数，第i个数字表示第i个物品的重要度。( 1 <= Wi <= 1000)

Output
对于每一个样例输出一行，结果为渣渣辉可以带上的物品的最大总重要度。
Sample Input
10 5
4 6 5 2 7
3 4 8 4 6
Sample Output
12

#include <iostream>
#include <cstring>
using namespace std;

int v[1010];
int w[1010];
int dp[1010][1010];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    
    int bag, n;
    while (cin >> bag >> n) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &v[i]);
        }
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &w[i]);
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j <= bag; ++j) {
                if (j >= v[i]) {
                    dp[i][j] = max(dp[i-1][j], dp[i-1][j-v[i]] + w[i]);
                } else {
                    dp[i][j] = dp[i-1][j];
                }
            }
        }
        cout << dp[n][bag] << endl;
    }
    return 0;
}


// C
Description
渣渣辉从小的梦想就是当一名警察，做一名出色的反恐精英。

但是事与愿违，他现在只能天天在家里打 CF (codeforce) 了。

我们知道，CF上经常有比赛，渣渣辉这么热爱CF，当然一次也没有落下。

比赛规则是这样的：
1.有 N 种子弹型号，编号分别为 1，2 ... N。
2.有 N 种恐怖分子类型，编号也分别为1，2 ... N。
3.敌人有 M 个，子弹也会有 M 个。
4.只有一种子弹打中同种编号类型的敌人时，得分才会加 1 分。
5.子弹已经按照输入顺序装填，恐怖分子也按照输入顺序出现。
你能帮助渣渣辉打到最高分吗？
（渣渣辉射击百发百中，他可以放空枪，也可以选择不射击某名恐怖分子）

Input
输入有多组测试样例。
对于每组测试样例：
第一行输入为两个正整数 N 和 M，表示有 N 种类型的敌人和子弹，M 个敌人和子弹。( 1 <= N <= 100，1 <= M <= 1000）
第二行输入为 M 个数字，分别代表按照顺序出现的恐怖分子类型。
第三行输入为 M 个数字，分别代表按照顺序装填的子弹类型。
                                            
Output
对于每组测试样例，输出占一行，输出结果为渣渣辉可以得到的最高分数。
Sample Input
3 6
1 2 2 3 1 1
2 2 1 2 1 3
Sample Output
4
                                            
#include <iostream>
#include <cstring>
using namespace std;
// 最长公共子序列
int a[1010];
int b[1010];

int l[1010][1010];

int main() {
    
    int n, m;
    while (cin >> n >> m) {
        for (int i = 1; i <= m; ++i) {
            scanf("%d", &a[i]);
        }
        for (int i = 1; i <= m; ++i) {
            scanf("%d", &b[i]);
        }
        memset(l, 0, sizeof(l));
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (a[i] == b[j]) {
                    l[i][j] = l[i-1][j-1] + 1;
                } else {
                    l[i][j] = max(l[i-1][j], l[i][j-1]);
                }
            }
        }
        cout << l[m][m] << endl;
    }
    return 0;
}


// B
Description
A国部署的反导系统遇到了一个致命BUG，那就是每一次发射的拦截导弹的飞行高度都将只能小于等于上一枚导弹的飞行高度，第一次发射的拦截导弹的飞行高度可以看作是足够大。对于A国，这是一件很严重的问题，这意味着A国的防空系统面临空前危机。

通过对A国的军事部门计算机的入侵，A国还不知道敌对国B国刚才已经发现了这项BUG。更不知道，在这项BUG的报告书上交到B国空军司令部那一刻，三分钟后B国的全体高级空军军官已经在作战室讨论作战方案。

如果战争真的开始，B国将依次派出n架战斗机A国将依次发射拦截导弹，这n架飞机的飞行高度分别是h1h2h3.....hn。B国将要充分利用这项漏洞，考虑到这么一种情况，假设只要A国的导弹的飞行高度大于等于B国飞机就能百分之百地锁定并击落，那么B国，最少将会有几架不被击落飞机？

Input
第一行为T，表示有T组输入数据(T<200)。

每组数据第一行是n代表有n架飞机（1=<n<=20 000）。

接下来一行有n个数，分别代表n架飞机的飞行高度，飞机飞行高度maxh为(1<=maxh<=50 000)。

Output
对于每组测试数据，在每行中输出一个数。表示B国最少将会有几架未被击落飞机。

Sample Input
2
1
1000
6
340 260 101 405 278 89
Sample Output
0
2

#include <iostream>
using namespace std;
// 最长下降子序列
int arr[20010];
int m[20010];

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i) {
            scanf("%d", &arr[i]);
        }
        m[0] = 1;
        int max_num = 1;
        for (int i = 1; i < n; ++i) {
            int tmp = 0;
            for (int j = 0; j < i; ++j) {
                if (arr[i] <= arr[j]) {
                    tmp = max(tmp, m[j]);
                }
            }
            m[i] = tmp + 1;
            max_num = max(max_num, m[i]);
        }
        cout << n - max_num << endl;
    }
    
    return 0;
}

 
// A
Description
有一天，小辉辉在玩积木时，对渣渣辉提出了一个问题：
在2×n的一个长方形方格中用一个1×2的积木铺满方格输入n 输出铺放方案的总数.
例如n=3时为2×3方格，积木的铺放方案有三种如下图：
http://101.200.61.174/JudgeOnline/upload/image/20180723/20180723113520_71250.png
Input
输入数据由多行组成，每行包含一个整数n表示该测试实例的长方形方格的规格是2×n (0<n<=50)。
Output
对于每个测试实例，请输出铺放方案的总数，每个实例的输出占一行。
Sample Input
1
3
2
Sample Output
1
3
2

#include <iostream>
using namespace std;
long long int arr[55] = {0, 1, 2, 3};

int main(int argc, const char * argv[]) {
    
    for (int i = 4; i <= 50; ++i) {
        arr[i] = arr[i - 1] + arr[i - 2];
    }
    int n;
    while (cin >> n) {
        cout << arr[n] << endl;
    }
    return 0;
}
*/
