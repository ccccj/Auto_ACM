//
//  main.cpp
//  dp优化(快速幂+斜率优化)
//
//  Created by admin on 18/8/13.
//  Copyright © 2018年 Amon. All rights reserved.
//

/*
// C dp
Description
给定K个整数的序列{ N1N2 ... NK }，其任意连续子序列可表示为{ NiNi+1 ...
    Nj }，其中 1<= i <= j <= K。最大连续子序列是所有连续子序列中元素和最大的一个，
例如给定序列{ -211 -4 13 -5 -2 }，其最大连续子序列为{ 11 -4 13 }，最大和
为20。
在今年的数据结构考卷中，要求编写程序得到最大和，现在增加一个要求，即还需要输出该
子序列的第一个和最后一个元素。
Input
测试输入包含若干测试用例，每个测试用例占2行，第1行给出正整数K(< 10000 )，第2行给出K个整数，中间用空格分隔。当K为0时，输入结束，该用例不被处理。
Output
对每个测试用例，在1行里输出最大和、最大连续子序列的第一个和最后一个元
素，中间用空格分隔。如果最大连续子序列不唯一，则输出序号i和j最小的那个（如输入样例的第2、3组）。若所有K个元素都是负数，则定义其最大和为0，输出整个序列的首尾元素。
Sample Input
6

-2 11 -4 13 -5 -2

10

-10 1 2 3 4 -5 -23 3 7  -21

6

5 -8 3 2 5 0

1

10

3

-1 -5 -2

3

-1 0 -2

0
Sample Output
20 11 13
10 1 4
10 3 5
10 10 10
0 -1 -2
0 0 0

#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 10010;
long long int arr[maxn], sum[maxn], _left[maxn];

int main() {
    
    int n;
    while (cin >> n && n) {
        memset(sum, 0, sizeof(sum));
        for (int i = 0; i < n; ++i) {
            cin >> arr[i];
        }
        sum[0] = arr[0], _left[0] = 0;
        for (int i = 1; i < n; ++i) {
            if (arr[i] > sum[i - 1] + arr[i]) {
                _left[i] = i;
                sum[i] = arr[i];
            } else {
                sum[i] = sum[i - 1] + arr[i];
                _left[i] = _left[i - 1];
            }
        }
        double tmp = -0.5;
        long long int l = -1, r = -1;
        for (int i = 0; i < n; ++i) {
            if (tmp < (double)sum[i]) {
                tmp = sum[i];
                l = _left[i];
                r = i;
            }
        }
        
        if (l == -1 && r == -1) {
            cout << "0 " << arr[0] << ' ' << arr[n - 1] << endl;
        } else {
            cout << tmp << ' ' << arr[l] << ' ' << arr[r] << endl;
        }
    }
    return 0;
}


// C 矩阵快速幂
Description
函数 f(x).
若 x < 10 f(x) = x.
若x >= 10 f(x) = a0 * f(x-1) + a1 * f(x-2) + a2 * f(x-3) + …… + a9 * f(x-10);
ai(0<=i<=9) 只能为 0 或 1 .

已知 a0 ~ a9 和两个正整数 k 与 m 计算 f(k)%m.
Input
问题包含多个测试用例。
在每种情况下，都有两行。
在第一行中有两个正整数k和m。(k < 2 * 10 ^ 9 m < 10 ^ 5)
在第二行中，有10个整数代表a0 ~ a9
Output
每个样例在一行里输出 f(k) % m
Sample Input
10 9999
1 1 1 1 1 1 1 1 1 1
20 500
1 0 1 0 1 0 1 0 1 0
Sample Output
45
104

#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 11;
int MOD;

long long int ret[maxn][maxn], now[maxn][maxn], tmp[maxn][maxn];
int a;

void P(long long int A[][maxn], int n) {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            printf("%2lld ", A[i][j]);
        }
        cout << endl;
    }
    cout << endl;
}

void Mul(long long int A[][maxn], long long int B[][maxn], int n) {
    memset(tmp, 0, sizeof(tmp));
    
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            for (int k = 1; k <= n; ++k) {
                tmp[i][j] = (tmp[i][j] + A[i][k] * B[k][j]) % MOD;
            }
        }
    }
    memcpy(A, tmp, sizeof(ret));
}

// N次幂
void QuickPower(int N, int n) {
    
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (i == j) ret[i][j] = 1;
            else ret[i][j] = 0;
        }
    }
    while (N) {
        if (N & 1) {
            Mul(ret, now, n);
          //  cout << "ret :" << endl;
           // P(ret, n);
            
        }
        Mul(now, now, n);
        N >>= 1;
        //P(now, n);
    }
}

int main() {
    
    int n;
    while (~scanf("%d%d", &n, &MOD)) {
        memset(now, 0, sizeof(now));
        for (int i = 1; i <= 10; ++i) {
            cin >> a;
            now[1][i] = a;
            if (i != 10) {
                now[i + 1][i] = 1;
            }
        }
        if (n < 10) {
            cout << n << endl;
        }  else {
            QuickPower(n - 9, 10);
        
            long long int sum = 0;
            for (int i = 1; i <= 10; ++i) {
                sum += (10 - i) * ret[1][i];
            }
            cout << sum % MOD << endl;
        }
    }
    return 0;
}



// A 矩阵快速幂
Description
斐波那契数列的定义如下：

F(0) = 0
F(1) = 1
F(n) = F(n - 1) + F(n - 2) (n >= 2)

(1 1 2 3 5 8 13 21 34 55 89 144 233 377 ...)
给出n，求F(n)，由于结果很大，输出F(n) % 1000000009的结果即可。
Input
输入1个数n(1 <= n <= 10^18)。
Output
输出F(n) % 1000000009的结果。
Sample Input
11
Sample Output
89

#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 3, MOD = 1000000009;

long long int ret[maxn][maxn], now[maxn][maxn], tmp[maxn][maxn];

void P(long long int A[][maxn], int n) {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            printf("%2lld ", A[i][j]);
        }
        cout << endl;
    }
    cout << endl;
}

void Mul(long long int A[][maxn], long long int B[][maxn], int n) {
    memset(tmp, 0, sizeof(tmp));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            for (int k = 1; k <= n; ++k) {
                tmp[i][j] = (tmp[i][j] + A[i][k] * B[k][j]) % MOD;
            }
        }
    }
    memcpy(A, tmp, sizeof(ret));
}

// N次幂
void QuickPower(int N, int n) {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (i == j) ret[i][j] = 1;
            else ret[i][j] = 0;
        }
    }
    while (N) {
        if (N & 1) {
            Mul(ret, now, n);
            // cout << "ret :" << endl;
            // P(ret, n);
            
        }
        Mul(now, now, n);
        N >>= 1;
        // P(now, n);
    }
}

int main() {
    
    int n;
    while (cin >> n) {
        now[1][1] = 1, now[1][2] = 1, now[2][1] = 1, now[2][2] = 0;
        QuickPower(n - 1, 2);
        long long int a[3][3];
        a[1][1] = 1, a[2][1] = 0;
        Mul(ret, a, 2);
        cout << ret[1][1] << endl;
    }
    return 0;
}


#include <iostream>
using namespace std;

long long int mi(int a, int b) { // 底数和指数
    int i = 0;
    long long int ret = 1;
    while ( b > (1 << i) ) {
        if (b & (1 << i)) {
            ret *= a;
        }
        a *= a;
        ++i;
    }
    return ret;
}

int main(int argc, const char * argv[]) {
    return 0;
}
*/
