//
//  main.cpp
//  7.29博弈论+字典树
//
//  Created by admin on 18/7/29.
//  Copyright © 2018年 Amon. All rights reserved.
//
// E SG博弈
Description
辉辉想静静，于是把题全推给yoyo做。yoyo不想让辉辉想静静，想让他专心做题，于是yoyo设置了一个比赛。一共有n堆石子，每一轮允许两会中操作之一：①、从一堆石子中取走任意多个，②、将一堆数量不少于 2 的石子分成都不为空的两堆。yoyo先手，如果辉辉输了，他就不能再想静静了，否则辉辉就可以继续想静静，以此逃避做题。辉辉之后还能想静静吗。
Input
首行输入t，代表t组样例

每组样例第一行输入n，代表n堆石子。n<=100

接下来n个数字（n1n2……nn）代表每堆石子的石子数。ni<=100

Output
输出谁获胜。yoyo胜则输出noway，否则输出jingjing

Sample Input
2
3
2 2 3
2
3 3
Sample Output
noway
jingjing

// sg[0] = 0, sg[1] = 1, sg[2] = 2, sg[3] = 4, sg[4] = 3;
// sg[5] 开始循环，即
// sg[4k+1] = 4k+1;sg[4k+2] = 4k+2;sg[4k+3] = 4k+4;sg[4k+4] = 4k+3;
#include <iostream>
#include <cstring>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int sg = 0, n, a;
        cin >> n;
        for (int i = 0; i < n; ++i) {
            cin >> a;
            if (a % 4 == 3) {
                ++a;
            } else if (a % 4 == 0) {
                --a;
            }
            sg ^= a;
        }
        if (sg == 0) {
            cout << "jingjing" << endl;
        } else {
            cout << "noway" << endl;
        }
        
        
    }
    return 0;
}

/*
// F 字典树
Description
渣渣辉 和 小虎 做了一个游戏，小虎 给 渣渣辉 一个集合，集合中包含了 N 个正整数，随后 小虎 将向 渣渣辉 发起M次询问，每次询问中包含一个正整数 S ，之后 渣渣辉 需要在集合当中找出一个正整数 K ，使得 K 与 S 的异或结果最大。

渣渣辉想不出来，你能棒棒他吗？

Input
输入包含若干组测试数据，每组测试数据包含若干行。

输入的第一行是一个整数T（T < 10），表示共有T组数据。

每组数据的第一行输入两个正整数 N，M（1 <= N，M <= 100000），接下来一行，包含N个正整数，代表 渣渣辉 的获得的集合，之后M行，每行一个正整数S，代表 小虎 询问的正整数。所有正整数均不超过232 - 1。

Output
对于每组数据，首先需要输出单独一行”Case #?:”，其中问号处应填入当前的数据组数，组数从1开始计算。

对于每个询问，输出一个正整数K，使得K与S异或值最大。

Sample Input
2
3 2
3 4 5
1
5
4 1
4 6 5 6
3
Sample Output
Case #1:
4
3
Case #2:
4

#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int trie[3200001][2], tot, r;
int n, m;

void insert(int a)
{
    int root = 0; //根节点编号为0
    for (int i = 31; i >= 0; --i) {
        int id = (a >> i) & 1;
        if(!trie[root][id]) //如果之前没有从root到id的前缀
            trie[root][id] = ++tot; //插入，tot即为第一种编号
        root = trie[root][id]; //顺着字典树往下走
    }
}

int search(int a)
{
    int root = 0, sum = 0;
    for(int i = 31; i >= 0; --i)
    {
        int id = (a >> i) & 1;
        if (id == 1) {
            if(trie[root][0]) { // 有
                root = trie[root][0];
            } else { // 没有
                sum += 1 << i;
                root = trie[root][1];
            }
        } else {
            if(trie[root][1]) { // 有
                root = trie[root][1];
                sum += 1 << i;
            } else { // 没有
                root = trie[root][0];
            }
        }
    }
    return sum;
}
int main() {
    
    int T, CASE = 0;
    scanf("%d", &T);
    while (T--) {
        memset(trie, 0, sizeof(trie));
        tot = 0;
        int n, m, a;
        cin >> n >> m;
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &a);
            insert(a);
        }
        printf("Case #%d:\n", ++CASE);
        for (int i = 0; i < m; ++i) {
            scanf("%d", &a);
            printf("%d\n", search(a));
        }
    }
    return 0;
}


// D SG博弈
Description
yoyo有一个超萌的喵咪名叫灰灰，这天yoyo带着灰灰遇到了辉辉，见到灰灰后，辉辉感觉自己的萌值受到了挑战，于是打算从智商上证明自己比灰灰强。于是在yoyo的主持下，灰灰和辉辉举办了一个取石子比赛。规则如下。现在有 n 堆石子，每次可以从第 1 堆石子里取 1 颗、2 颗或 3颗，可以从第 2 堆石子里取奇数颗，可以从第 3 堆及以后石子里取任意颗……辉辉和灰灰轮流取，灰灰先取，灰灰能否战胜辉辉。PS（灰灰有yoyo帮助）

Input
首行输入t，代表t组样例

每组样例第一行输入n，代表共有n堆（0<n<1000）

接下来一行n个数字，代表每一堆石子的个数。ni<=100

Output
灰灰必胜输出Y，否则输出N

Sample Input
1
3
6 9 5

Sample Output
Y

// 第一堆石子，取 1..3 个，若共有1个，则取完剩下 0 ，所以 g(1) = 1
//                     若共有2个，则取完剩下 0/1 ，所以 g(1) = 2
//                     若共有3个，则取完剩下 0/1/2 ，所以 g(1) = 3
//                     若共有4个，则取完剩下 1/2/3 ，所以 g(1) = 0
//                     若共有5个，则取完剩下 2/3/4 ，所以 g(1) = 1
// ...循环，所以 g(x) = x % 4

// 第一堆石子，取奇数个，若共有奇数个，则取完剩下 偶数个(0/2/4..),所以 g(奇数) = 1
//                  若共有偶数个，则取完剩下 奇数个(1/3/5...),所以 g(奇数) = 0
// 此后，g(x) = x

#include <iostream>
using namespace std;

int main() {
    
    int T;
    cin >> T;
    while (T--) {
        int n; // n堆石子
        cin >> n;
        int m;
        // 1
        cin >> m;
        int ret = m % 4;
        // 2
        if (n > 1) {
            cin >> m;
            if (m % 2 == 1) {
                ret ^= 1;
            }
        }
        // 3...n
        for (int i = 2; i < n; ++i) {
            cin >> m;
            ret ^= m;
        }
        if (ret == 0) {
            cout << 'N' << endl;
        } else {
            cout << 'Y' << endl;
        }
        
    }
    
    return 0;
}


// C SG博弈
Description
辉辉攒了许多硬币，但是yoyo想给自己的宠物喵咪灰灰买糖吃，于是去找辉辉借硬币。辉辉不想借硬币给yoyo，于是将硬币分成了n堆，设置了一个题目刁难yoyo。现在有n堆硬币，第i堆硬币有xi个硬币。yoyo和灰灰轮流进行操作，每次操作只能选择一堆硬币，然后从这一堆硬币中取任意多个硬币（1~x，x为该堆最大数量），但不能不取。轮到的人如果没有硬币可取则输。yoyo先手，谁能获胜
Input
首行输入t，代表t组样例

每组样例第一行输入n，代表n堆硬币。n<=1000;

接下来n个数字（n1n2……nn）代表每堆硬币的硬币数。ni<=1000;

Output
输出谁赢。yoyo必胜输出yoyo，否则输出zhazhahui

Sample Input
2
3
2 3 4
4
2 3 4 5

Sample Output
yoyo
zhazhahui

#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
// 某一堆有 x 个硬币，可取 1...x 个，取完剩余 0...x-1 个 g(x) = x
// 最后结果为 x1 ^ x2 ^ .. ^ xn， 结果为0 则yoyo输，结果为1，则yoyo赢
int main() {
    int T;
    cin >> T;
    while (T--) {
        int n, m, ret = 0;
        cin >> n;
        for (int i = 0; i < n; ++i) {
            cin >> m;
            ret ^= m;
        }
        if (ret == 0) {
            cout << "zhazhahui" << endl;
        } else {
            cout << "yoyo" << endl;
        }
    }
    return 0;
}


// B 巴什博奕
Description
Alice和Bob在玩这样的一个游戏， 给定大小为K数组a1a2a3……ak。 一开始， 有x枚硬币， Alice和Bob轮流取硬币， 每次所取硬币的枚数一定要在 a1a2a3……ak之中。 每局Alice先取， 取走最后一枚硬币的一方获胜。 当双方都采取最优策略的时候， 谁会获胜？ 题目假定a1a2a3……ak之中一定有1。
Input
本题有多组测试数据。

每组数据第一行是两个数nm。分别代表开局有n个金币，和大小为m的数组。

随后一行是m个数，表示可以取得数。

Output
对于每组数据，输出赢家是谁

Sample Input
4 3
1 3 4
9 3
1 3 4

Sample Output
Alice
Bob

#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int arr[110];
bool dp[100010]; // dp[i] = 0 代表必输， = 1 代表必赢
int n, m;

void com() {
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (i < arr[j]) {
                break;
            }
            if (dp[i - arr[j]] == 0) {
                dp[i] = 1;
                break;
            }
        }
    }
}

int main() {
    while (cin >> n >> m) {
        for (int i = 0; i < m; ++i) {
            cin >> arr[i];
        }
        memset(dp, 0, sizeof(dp)); // 只剩0个，先手必输
        sort(arr, arr + m);
        com();
        if (dp[n] == 1) {
            cout << "Alice" << endl;
        } else {
            cout << "Bob" << endl;
        }
    }
    return 0;
}



// A 巴什博奕
Description
各位勇敢者要玩的第一个游戏是什么呢？很简单，它是这样定义的：
1、  本游戏是一个二人游戏;
2、  有一堆石子一共有n个；
3、  两人轮流进行;
4、  每走一步可以取走1…m个石子；
5、  最先取光石子的一方为胜；

如果游戏的双方使用的都是最优策略，请输出哪个人能赢。
Input
输入数据首先包含一个正整数T(T<=100)，表示有T组测试数据。
每组测试数据占一行，包含两个整数n和m（1<=nm<=10000），n和m的含义见题目描述。
Output
如果先走的人能赢，请输出“first”，否则请输出“second”，每个实例的输出占一行。
Sample Input
2
23 2
4 3
Sample Output
first
second

// 当只剩下 m + 1 个时，要走的人必输
// n = r * (m + 1) + s;
// 当 r >= 1，且 s > 0 时，先走的人取走 s 个，另一人无法每次取走 x 个，先走的人每次取 m + 1 - x 个，即可赢；但是，若 s == 0，则先手必输
// 当 r == 0 时，先手必赢，可一次取完

#include <iostream>
using namespace std;

int main(int argc, const char * argv[]) {
    
    int T, n, m;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        if (n % (m + 1) != 0) {
            cout << "first" << endl;
        } else {
            cout << "second" << endl;
        }
    }
    return 0;
}
*/
