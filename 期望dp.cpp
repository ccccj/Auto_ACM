//
//  main.cpp
//  期望dp
//
//  Created by admin on 18/9/27.
//  Copyright © 2018年 Amon. All rights reserved.
//
// 一道简单的期望dp~希望大家喜欢~
#include <cstdio>
#include <cstring>
#include <map>
using namespace std;
const int maxn = 1e5 + 10;
double dp[maxn];

int main(int argc, const char * argv[]) {
    int n, m, x, y;
    while (~scanf("%d%d", &n, &m)) {
        // 初始化 dp 数组为0
        memset(dp, 0, sizeof(dp));
        // 用 map 存储所有的跳跃点
        map<int, int> mp;
        for (int i = 0; i < m; ++i) {
            scanf("%d%d", &x, &y);
            mp[x] = y;
        }
        // dp[i] 存储从第i个位置到 n 需要飞多长时间的数学期望
        // n 位置当然是 0 啦
        // 注意，n 后面的几个位置也是0
        dp[n] = 0;
        for (int i = n - 1; i >= 0; --i) {
            if (mp.find(i) != mp.end()) {
                // 如果 i 位置可以直接飞到后面某个位置，那么他们的期望是相同的
                dp[i] = dp[mp[i]];
            } else {
                // 枚举后面七个位置，注意，n 后面的都是0
                // dp[i] = dp[i+1]/7 + dp[i+2]/7 + dp[i+3]/7 + dp[i+4]/7 + dp[i+5]/7 + dp[i+6]/7 + dp[i+7]/7 + 1
                double sum = 0;
                int num = 0;
                for (int j = i + 1; num < 7; ++j, ++num) {
                    sum += dp[j] + 1;
                }
                dp[i] = sum / num;
            }
        }
        printf("%.4lf\n", dp[0]);
    }
    return 0;
}
