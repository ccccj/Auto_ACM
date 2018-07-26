//
//  main.cpp
//  7.23
//
//  Created by admin on 18/7/22.
//  Copyright © 2018年 Amon. All rights reserved.
//
// 2018-07-30
/*
// F 点分治
Description
Have you ever played quoit in a playground? Quoit is a game in which flat rings are pitched at some toys, with all the toys encircled awarded.
In the field of Cyberground, the position of each toy is fixed, and the ring is carefully designed so it can only encircle one toy at a time. On the other hand, to make the game look more attractive, the ring is designed to have the largest radius. Given a configuration of the field, you are supposed to find the radius of such a ring.

Assume that all the toys are points on a plane. A point is encircled by the ring if the distance between the point and the center of the ring is strictly less than the radius of the ring. If two toys are placed at the same point, the radius of the ring is considered to be 0.

Input
The input consists of several test cases. For each case, the first line contains an integer N (2 <= N <= 100,000), the total number of toys in the field. Then N lines follow, each contains a pair of (x, y) which are the coordinates of a toy. The input is terminated by N = 0.

Output
For each test case, print in one line the radius of the ring required by the Cyberground manager, accurate up to 2 decimal places.
Sample Input
2
0 0
1 1
2
1 1
1 1
3
-1.5 0
0 0
0 1.5
0
Sample Output
0.71
0.00
0.75

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

struct node {
    double x, y;
} a[100010], b[100010];

bool cmpx(struct node i, struct node j) {
    return i.x < j.x;
}

bool cmpy(struct node i, struct node j) {
    return i.y < j.y;
}

double dis(struct node i, struct node j) {
    return sqrt(pow(i.x - j.x, 2) + pow(i.y - j.y, 2));
}

double find_min(int left, int mid, int right, double s) {
    int count = 0;
    for (int i = left; i <= right; ++i) {
        if (a[i].x >= a[mid].x - s && a[i].x <= a[mid].x + s) {
            // 在中间
            b[count].x = a[i].x;
            b[count++].y = a[i].y;
        }
    }
    sort(b, b + count, cmpy);
    for (int i = 0; i < count; ++i) {
        for (int j = i + 1; j < count; ++j) {
            if (b[j].y - b[i].y > s) {
                break;
            }
            double ret = dis(b[i], b[j]);
            
            if (ret < s) {
                s = ret;
            }
        }
    }
    return s;
}

double recursionMax (int left, int right) {
    if (left >= right) {
        return 0x7fffffff;
    }
    // 只有两个数
    if (left == right - 1) {
        return dis(a[left], a[right]);
    }
    int mid = (left + right) / 2;
    double x;
    if (right - left == 2) {
        x = dis(a[left], a[right]);
        x = min(x, dis(a[mid], a[right]));
        x = min(x, dis(a[mid], a[left]));
        return x;
    }
    double minLeft = recursionMax (left, mid); // 左
    double minRight = recursionMax(mid, right); // 右
    
    double s = minLeft <= minRight ? minLeft : minRight;
    
    s = find_min(left, mid, right, s);
    return s;
}

int main ()
{
    int  n;
    while (cin >> n && n) {
        for (int i = 0; i < n; ++i) {
            cin >> a[i].x >> a[i].y;
        }
        sort(a, a + n, cmpx);
        double ret = recursionMax(0, n - 1);
        printf("%0.2lf\n", ret / 2);
    }
    return 0;
}


// E 分治求最大连续子序列
Description
渣渣辉最近体重上升的很快，明明他小时候是个瘦子的啊。他想知道他怎么会变成这样的。

于是他记录下了最近N天内，他每天体重的变化情况。你能告诉他哪几天连续的天数内他体重增长的最多吗？

如果有多个答案，请输出第一个答案（最左边的~）。

Input
渣渣辉将会告诉你他几次测量的结果，每次测试由一个N和N个数字组成。

N (1<=N<=100000)代表这段时间有N天。

接下来是这 N 天内，每天的体重与前一天的变化（正数代表他又胖啦，负数代表他瘦啦）。



Output
对于渣渣辉的每次测量，都输出三个整数：

这段时间内，连续的天数里最大增长的体重；以及这连续的天数 开始与结束的时间。

每个数字间有一个空格。

每组输出由一行组成。

Sample Input
5
4 -3 4 -5 3
7
0 3 -1 1 -3 7 -5
Sample Output
5 1 3
7 1 6
HINT

对于第一组，体重增长最多的是第一天到第三天，共增长5：4-3+4


对于第二组，体重增长最多的是第一天到第六天，共增长7：0+3-1+1-3+7

#include <cstdio>
#include <iostream>
using namespace std;

int a[100010];

struct node {
    int sum, left, right;
};

node recursionMax (int left, int right)
{
    // 只有一个数
    if (left == right) return {a[left], left, right};
    
    int mid = (left + right) / 2;
    
    node maxLeft = recursionMax (left, mid); // 左
    node maxRight = recursionMax(mid + 1, right); // 右
    
    int left_sum = -0x7fffffff, right_sum = -0x7fffffff, li = mid, ri = mid + 1;
    int tmp = 0;
    for (int i = mid; i >= left; i--)
    {
        tmp += a[i];
        if (left_sum <= tmp) {
            left_sum = tmp;
            li = i;
        }
    }
    
    tmp = 0;
    for (int  j = mid + 1; j <= right; j++)
    {
        tmp += a[j];
        if (right_sum < tmp) {
            right_sum = tmp;
            ri = j;
        }
    }
    node ret = maxLeft.sum >= maxRight.sum ? maxLeft : maxRight;
    if (ret.sum > left_sum + right_sum) {
        return ret;
    } else if (ret.sum == left_sum + right_sum && ret.left < li) {
        return ret;
        
    } else {
        return {left_sum + right_sum, li, ri};
    }
}

int main ()
{
    int  n;
    while (cin >> n) {
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        node ret = recursionMax(0, n - 1);
        printf("%d %d %d\n", ret.sum, ret.left + 1, ret.right + 1);
    }
    return 0;
}



// D 分治求最大连续子序列
Description
小A同学最近打算买股票，他已经知道了某支股票 n 天内每天的价格（你问他咋知道的？？我也不知道）。他希望在低价时买进，高价时卖出，这样才能获得最大收益。

Input
第一行是一个n (n < 100000)。

第二行为 n 个整数，代表每天的价格。

本题有多个测试案例。

Output
输出小A同学能够获得的最大收益。每个答案占一行。

Sample Input
3
50 35 40
17
100 113 110 85 105 102 86 63 81 101 94 106 101 79 94 90 97
Sample Output
5
43

#include <cstdio>
#include <iostream>
using namespace std;

int b[100010];
int a[100010];

int recursionMax (int left, int right)
{
    // 只有一个数
    if (left == right) return a[left];
    
    int mid = (left + right) / 2;
    int maxLeft = recursionMax (left, mid); // 左
    int maxRight = recursionMax(mid + 1, right); // 右
 
    int left_sum = -0x7fffffff, right_sum = -0x7fffffff, tmp = 0;
    
    for (int i = mid; i >= left; i--)
    {
        tmp += a[i];
        if (left_sum < tmp)
            left_sum = tmp;
    }
    
    tmp = 0;
    for (int  j = mid + 1; j <= right; j++)
    {
        tmp += a[j];
        if (right_sum < tmp)
            right_sum = tmp;
    }
    
    tmp = maxLeft > maxRight ? maxLeft : maxRight;
    if (tmp >= left_sum + right_sum) return tmp;
    else return left_sum + right_sum;
}

int main ()
{
    
    int n;
    while (cin >> n) {
        for (int i = 0; i < n; ++i) {
            cin >> b[i];
        }
        a[0] = 0;
        for (int i = 1; i < n; ++i) {
            a[i] = b[i] - b[i - 1];
        }
        cout << recursionMax(0, n - 1) << endl;
    }
    return 0;
}


// C 汉诺塔简单问题
Description
我们都已经知道了汉诺塔问题，如果还有不懂得可以看以下解释：

汉诺塔来源于印度传说的一个故事，上帝创造世界时作了三个金刚石柱子，在一根柱子上从上往下，按从小到大顺序摞着64片黄金圆盘，上帝命令婆罗门把圆盘从下面开始按大小顺序重新摆放在另一根柱子上，并且规定，在小圆盘上不能放大圆盘，在三根柱子之间每次只能移动一个圆盘，只能移动在最顶端的圆盘。

现在有 n 个圆盘从上往下，从小到大叠在第一根柱子上，要把这些圆盘全部移动到第三根柱子，我们都知道，最少的移动数目为 2^n - 1 次。但是现在我们要求的并不是这个。


我们用 1，2，...，n 表示 n个盘子的编号，编号越大盘子就越大。在移动过程中，有的圆盘移动次数多，有的少。告知盘子总数和盘号，计算该盘子的移动次数。

Input
输入包含多组数据，首先输入 T ，表示有 T 组数据。每个数据一行，是盘子的数目(1 <= N <= 60)和盘号 k (1 <= k <= N)。


Output
对于每组数据，输出一个数，即到达目标时 k 号盘需要的最少移动数。



Sample Input
2
60 1
3 1
Sample Output
576460752303423488
4
HINT

注意：范围超出了32位，建议使用 long long哦~

#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

long long int hanoi(int n, int a) {
    if (n == a) {
        return 1;
    }
    if (n == 1) {
        return 0;
    } else {
        return 2 * hanoi(n - 1, a);
    }
}

int main() {
    
    int T;
    cin >> T;
    while (T--) {
        
        int n, a;
        cin >> n >> a;
        cout << hanoi(n, a) << endl;
    }
    return 0;
}


// B 归并求逆序对变形
Description
自从上次换座位开始，渣渣辉就一直在思考一个问题：如果他们班有N名同学，学号分别为 0，1，2，...，N-1，如果这些同学被打乱，使得学号并不按升序排列，得到了一个新的序列：a1 a2 a3 ... aN;


在这个序列中有多少个逆序对想必我们都知道，但渣渣辉现在思考的并不是这个问题，而是，每次移动第一个数，得到一个新的序列，如下：

a1 a2 ... an-1 an

a2 a3 ... an a1

a3 a4 ... an a1 a2

...

an a1 a2 ... an-1



在这些序列中，逆序对最少的是多少呢？渣渣辉已经思考很久啦，你能帮帮他吗？

Input
第一行给出一个 N (N < 5000);

第二行给出 N 个数，为 1...N 打乱后的顺序。

Output
求出每次将第一个数移动到最后的过程中，逆序对最少为多少。

每个案例输出占一行，行尾无多余空格。

Sample Input
10
1 3 6 9 0 8 5 7 4 2
Sample Output
16

#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>
using namespace std;

int data[5050];
int arr[5050];
int tmp[5050];

long long int cnt;
void Merge(int beg, int mid, int end) {
    if (end <= beg)
        return;
    
    int i = 0;
    int beg1 = beg, beg2 = mid;
    while (beg1 < mid && beg2 < end) {
        if (data[beg1] <= data[beg2]) {
            tmp[i++] = data[beg1++];
        } else {
            tmp[i++] = data[beg2++];
            cnt += mid - beg1;
        }
    }
    while (beg1 < mid) {
        tmp[i++] = data[beg1++];
    }
    while (beg2 < end) {
        tmp[i++] = data[beg2++];
    }
    memcpy(data + beg, tmp, sizeof(int) * (end - beg));
}

int main(int argc, const char * argv[]) {
    
    int n;
    while (cin >> n) {
        cnt = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%d", &data[i]);
            arr[i] = data[i];
        }
        for (int length = 1; length <= n; length *= 2) {
            for(int beg = 0, mid = beg + length, end = mid + length; beg < n;
                beg += 2 * length, mid = beg + length, end = mid + length) {
                if (mid > n) {
                    mid = n;
                }
                if (end > n) {
                    end = n;
                }
                Merge(beg, mid, end);
            }
        }
        long long int ret = cnt;
        for (int i = 0; i < n; ++i) {
            
            cnt = cnt - arr[i] + n - 1 - arr[i];
            if (ret > cnt) ret = cnt;
        }
        cout << ret << endl;
    }
    
    return 0;
}

 
// A 归并求逆序对
Description
大家都知道，听课时如果渣渣辉同学坐在前面，他庞大的身躯就会遮档住后面同学的视线，因此老师需要将渣渣辉的座位往后调。可是渣渣辉并不愿意坐后面，于是老师只好换一个方法来调座位，那就是按照同学们的编号来排座位（因为渣渣辉是男生，学号在后面呢）。

规定，每次只能交换相邻两名同学的座位（交换的同学的学号并不一定要相邻，只是坐的座位相邻）。要求最后的编号，按升序排序。

Input
第一行给出一个N(N < 10000)，代表同学的数量。

第二行给出N个数，代表每名同学的编号，中间以空格隔开。

本题有多组测试数据。


Output
输出最少需要交换的次数。每组测试的输出占一行。
Sample Input
4
2 4 3 1
10
1 3 6 9 0 8 7 5 2 4
Sample Output
4
22
HINT

注意：给出的编号并不一定是1..N哦~


例如给出N=3，第二行给出的数可能为 4 2 6~所以答案是1，只需要交换2和4即可~

#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>
using namespace std;

int data[10000010];
int tmp[10000010];

long long int cnt;
void Merge(int beg, int mid, int end) {
    if (end <= beg)
        return;
    
    int i = 0;
    int beg1 = beg, beg2 = mid;
    while (beg1 < mid && beg2 < end) {
        if (data[beg1] <= data[beg2]) {
            tmp[i++] = data[beg1++];
        } else {
            tmp[i++] = data[beg2++];
            cnt += mid - beg1;
        }
    }
    while (beg1 < mid) {
        tmp[i++] = data[beg1++];
    }
    while (beg2 < end) {
        tmp[i++] = data[beg2++];
    }
    memcpy(data + beg, tmp, sizeof(int) * (end - beg));
}

int main(int argc, const char * argv[]) {
    
    int n;
    while (cin >> n) {
        cnt = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%d", &data[i]);
        }
        for (int length = 1; length <= n; length *= 2) {
            int beg = 0, mid = beg + length, end = mid + length;
            for(; beg < n; beg += 2 * length,
                           mid = beg + length, end = mid + length) {
                if (mid > n) {
                    mid = n;
                }
                if (end > n) {
                    end = n;
                }
                Merge(beg, mid, end);
            }
        }
        cout << cnt << endl;
    }
    
    return 0;
}
*/
