//
//  main.cpp
//  子集的和问题
//
//  Created by admin on 18/9/21.
//  Copyright © 2018年 Amon. All rights reserved.
//
//
//  main.cpp
//  子集的和问题
//
//  Created by admin on 18/9/21.
//  Copyright © 2018年 Amon. All rights reserved.
//
/*
// UVA 147
New Zealand currency consists of $100, $50, $20, $10, and $5 notes and $2, $1, 50c, 20c, 10c and 5c coins. Write a program that will determine, for any given amount, in how many ways that amount may be made up. Changing the order of listing does not increase the count. Thus 20c may be made up in 4 ways: 1×20c, 2×10c, 10c+2×5c, and 4×5c.

Input
Input will consist of a series of real numbers no greater than $300.00 each on a separate line. Each amount will be valid, that is will be a multiple of 5c. The  le will be terminated by a line containing zero (0.00).
Output
Output will consist of a line for each of the amounts in the input, each line consisting of the amount of money (with two decimal places and right justi ed in a  eld of width 6), followed by the number of ways in which that amount may be made up, right justi ed in a  eld of width 17.
Sample Input
0.20
2.00
0.00
Sample Output
  0.20                4
  2.00              293

#include <cstdio>
#include <cmath>
#include <iostream>
using namespace std;
typedef long long LL;
const int maxn = 6010;
const double EPS = 1e-9;
int w[12] = {1, 1, 2, 4, 10, 20, 40, 100, 200, 400, 1000, 2000};
LL dp[maxn];


int main() {
    dp[0] = 1;
    for (int i = 1; i <= 11; ++i) {
        for (int j = w[i]; j < maxn; ++j) {
            dp[j] += dp[j-w[i]];
        }
    }
    
    double x;
    while (~scanf("%lf", &x) && fabs(x) > EPS) {
        LL n = (LL)(x * 20);
        printf("%6.2lf%17lld\n", x, dp[n]);
        
    }
    return 0;
}



晓萌希望将1到N的连续整数组成的集合划分成两个子集合，且保证每个集合的数字和是相等。例如，对于N=3，对应的集合{1，2，3}能被划分成{3} 和 {1,2}两个子集合.

这两个子集合中元素分别的和是相等的。

对于N=3，我们只有一种划分方法，而对于N=7时，我们将有4种划分的方案。

输入包括一行，仅一个整数，表示N的值（1≤N≤39）。

输出包括一行，仅一个整数，晓萌可以划分对应N的集合的方案的个数。当没发划分时，输出0。

#include <cstdio>
using namespace std;
typedef long long LL;
const int maxn = 45;
LL dp[maxn][(1+maxn)*maxn/4];

int main(int argc, const char * argv[]) {
    // dp[i][j] 代表，在前i个数里，选出几个数，使得和为j的方案数
    // 这道题的第i个数就等于i
    int n;
    while (~scanf("%d", &n)) {
        LL sum = (1+n)*n/2;
        // “剪枝”，如果和是个奇数，就说明不可能分成两个和相同的集合
        if (sum % 2 == 1) {
            printf("0\n"); // 输出0，也就是没有方案
            continue;
        }
        sum /= 2;
        // 在0个数里选，使得和为0的方案数为1
        dp[0][0] = 1;
        for (int i = 1; i <= n; ++i) {
            // 在i个数里选，使得和为0的方案数为1（一个都不选）
            dp[i][0] = 1;
            // 背包容量为j，从小到大遍历
            for (int j = 1; j <= sum; ++j) {
                // 当前考虑到第i个数，我们考虑到底放不放进去
                if (j < i) {
                    // 第i个数为i，大于j，放不下i这么大的数
                    // 也就是说，背包比当前第i个数还大，那么只能不放
                    // 方案数等于 在i-1个数里选，使得和为j 的方案数
                    dp[i][j] = dp[i-1][j];
                    // 所以不放的方案数就等于dp[i-1][j]
                } else {
                    // 如果可以放，方案数就等于 放/不放的方案数相加
                    // 放，就相当于在在前i-1个数里选，使得选出的数相加为 j-i
                    //            放      或者    不放
                    dp[i][j] = dp[i-1][j-i] + dp[i-1][j];
                }
            }
        }
        // 输出 在n个数里选，使得和为sum的方案数，除以2，因为...这个有点说不清 蛮好理解的，有一半重复了
        printf("%lld\n", dp[n][sum] / 2);
    }
    return 0;
}


// 滚动数组
#include <cstdio>
using namespace std;
typedef long long LL;
const int maxn = 45;
LL dp[(1+maxn)*maxn/4];

int main(int argc, const char * argv[]) {
    
    int n;
    while (~scanf("%d", &n)) {
        LL sum = (1+n)*n/2;
        if (sum % 2 == 1) {
            printf("0\n");
            continue;
        }
        sum /= 2;
        dp[0] = 1;
        for (int i = 1; i <= n; ++i) {
            dp[0] = 1;
            for (LL j = sum; j >= i; --j) {
                dp[j] = dp[j-i] + dp[j];
            }
        }
        printf("%lld\n", dp[sum] / 2);
    }
    return 0;
}


*/
