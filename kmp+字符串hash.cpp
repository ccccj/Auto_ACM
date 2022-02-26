//
//  main.cpp
//  kmp+字符串hash
//
//  Created by admin on 18/8/13.
//  Copyright © 2018年 Amon. All rights reserved.
//
/*
#include <iostream>
#include <cstring>
#include <cstdio>
#include <time.h>
#include <cstdlib>
using namespace std;

#define MAXN 1000010

char st[MAXN];
void kmp_pre(char x[],int m,int nextt[]){
    int i,j;
    j=nextt[0]=-1;
    i=0;
    while(i<m){
        while(-1!=j&&x[i]!=x[j]) j=nextt[j];
        if(x[++i]==x[++j]) nextt[i]=nextt[j];
        else nextt[i]=j;
    }
}
int nextt[MAXN];
bool kmp(char x[],int m,char y[],int n){
    int i,j;
    kmp_pre(x,m,nextt);
    i=j=0;
    while(i<n){
        while(-1!=j&&y[i]!=x[j]) j=nextt[j];
        i++;j++;
        if(j>=m)
            return true;
    }
    return false;
}
int main() {

    freopen("/Users/admin/Desktop/test.txt", "w", stdout);
    srand((unsigned)time(NULL));
    cout << 200 << endl;
    for (int i = 0; i < 100; ++i) {
        int l = rand() % 1000 + 100;
        for (int j = 0; j < l; ++j) {
            int c = rand() % 26 + 'a';
            printf("%c", c);
        }
        printf("\n");
    }
    for (int i = 0; i < 100; ++i) {
        int l = rand() % 1000 + 100;
        for (int j = 0; j < l; ++j) {
            int c = rand() % 10 + 'a';
            printf("%c%c", c, c);
        }
        printf("\n");
    }
    
    freopen("/Users/admin/Desktop/test.txt", "r", stdin);
    freopen("/Users/admin/Desktop/test1.txt", "w", stdout);
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%s",st);
        int len=strlen(st);
        int i,j;
        for(i=len/3;i>=1;i--){
            for(j=0;j<i;++j){
                if(st[j]!=st[len-i+j])
                    break;
            }
            if(j>=i){
                kmp_pre(st,i,nextt);
                if(kmp(st,i,st+i,len-2*i))
                    break;
            }
        }
        if(i>=1)
            printf("%d\n",i);
        else
            printf("0\n");
    }
    return 0;
}
*/

#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

char s[1000010], p[1000010];

void cal_next(char *str, int *next, int len) {
    
    next[0] = -1; // next[0]初始化为-1，-1表示不存在相同的最大前缀和最大后缀
    int k = -1; // k初始化为-1
    
    for (int q = 1; q <= len-1; ++q) {
        
        while (k > -1 && str[k+1] != str[q]) {
            // 如果下一个不同，那么k就变成next[k]，注意next[k]是小于k的，无论k取任何值。
            k = next[k]; // 往前回溯
        }
        
        if (str[k + 1] == str[q]) {
            // 如果相同，++k
            ++k;
        }
        // 把算的k的值（就是相同的最大前缀和最大后缀长）赋给next[q]
        next[q] = k;
    }
}

long long KMP(char *str, int slen, char *ptr, int plen) {
    long long int sum = 0;
    int *next = new int[plen];
    cal_next(ptr, next, plen); // 计算next数组
    
    int j = -1;
    for (int i = 0; i < slen; i++) {
        while (j > -1 && ptr[j + 1] != str[i]) {
            // ptr 和 str 不匹配，且 j > -1（表示 ptr 和 str 有部分匹配）
            j = next[j]; // 往前回溯
        }
        
        if (ptr[j + 1] == str[i])
            j = j + 1;
        
        if (j == plen-1) {
            ++sum;
            j = next[j];
            // 说明 j 移动到 ptr 的最末端
            //return i-plen+1; //返回相应的位置
        }
    }
    // return -1;
    return sum;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%s", s);
        int len = (int)strlen(s);
        if (len < 3) {
            printf("0\n");
            continue;
        }
        int *next = new int[len + 2];
        
        cal_next(s, next, len);
        int Max = 0;
        
                for (int i = 0; i < len; ++i) {
                    cout << next[i];
                }
                cout << endl;
        
        for (int i = len-1; i >= len * 2 / 3 - 1; --i) {
            if (next[i]+1 > Max) {
                memcpy(p, s, len);
                int k = next[i];
                while (len - 2 * k < k) {
                    k = next[k];
                }
                while (k > 0) {
                    p[k + 1] = '\0';
                    if (KMP(s + k + 1, len - 2 * (k + 1), p, (int)strlen(p)) != -1) {
                        Max = k + 1;
                        break;
                    }
                    k = next[k];
                    
                }
                
            }
        }
        printf("%d\n",Max);
    }
    return 0;
}


/*
char s[1000010], p[1000010];

void cal_next(char *str, int *next, int len) {
    
    next[0] = 0; // next[0]初始化为-1，-1表示不存在相同的最大前缀和最大后缀
    int k = 0; // k初始化为-1
    next[1] = 0;
    for (int q = 2; q <= len; ++q) {
        
        while (k > 0 && str[k] != str[q-1]) {
            // 如果下一个不同，那么k就变成next[k]，注意next[k]是小于k的，无论k取任何值。
            k = next[k]; // 往前回溯
        }
        
        if (str[k] == str[q-1]) {
            // 如果相同，++k
            ++k;
        }
        // 把算的k的值（就是相同的最大前缀和最大后缀长）赋给next[q]
        next[q] = k;
    }
//    for (int i = 0; str[i]; ++i) {
//      cout << next[i];
//    }
//    cout << next[len] << endl;
}

//#include <iostream>
//#include <cstring>
//#include <cstdio>
//#include <time.h>
//#include <cstdlib>
//using namespace std;
//
//char s[100010], p[50010];

//void cal_next(char *str, int *next, int len) {
//    
//    next[0] = -1; // next[0]初始化为-1，-1表示不存在相同的最大前缀和最大后缀
//    int k = -1; // k初始化为-1
//    
//    for (int q = 1; q <= len-1; ++q) {
//        
//        while (k > -1 && str[k+1] != str[q]) {
//            // 如果下一个不同，那么k就变成next[k]，注意next[k]是小于k的，无论k取任何值。
//            k = next[k]; // 往前回溯
//        }
//        
//        if (str[k + 1] == str[q]) {
//            // 如果相同，++k
//            ++k;
//        }
//        // 把算的k的值（就是相同的最大前缀和最大后缀长）赋给next[q]
//        next[q] = k;
//    }
//}

int main() {
//    srand((unsigned)time(NULL));
//    freopen("/Users/admin/Desktop/test.txt", "w", stdout);
//    for (int i = 1; i <= 4999; ++i) {
//        printf("a");
//    }
//    printf("\n");
//    for (int i = 1; i <= 4999; ++i) {
//        printf("a");
//    }
//    printf("\n");
//    char t[5010];
//    for (int i = 0; i < 500; ++i) {
//        int l = rand() % 4000;
//        for (int j = 0; j < l; ++j) {
//            int tmp = rand() % 26 + 'a';
//            t[j] = tmp;
//        }
//        t[l] = '\0';
//        printf("%s\n", t);
//        
//        l = rand() % 2000 + 3000;
//        for (int j = 0; j < l; ++j) {
//            int tmp = rand() % 26 + 'a';
//            printf("%c", tmp);
//        }
//        printf("%s\n", t);
//    }
    //freopen("/Users/admin/Desktop/test-8.in", "r", stdin);
    //freopen("/Users/admin/Desktop/test1.txt", "w", stdout);
    while (~scanf("%s%s", s, p)) {
        
        
        int lens = (int)strlen(s), lenp = (int)strlen(p);
        strcat(s, p);
        
        int n[100010];
        
        int len = (int)strlen(s);
        cal_next(s, n, len);
        
        int ans = n[len];
        
        while (ans > lens || ans > lenp) {
            ans = n[ans];
        }
        if (ans == 0) {
            printf("0\n");
            continue;
        } else {
            s[ans] = '\0';
            printf("%s %d\n", s, ans);
        }
    }
    return 0;
}

Description
赵神最近在做一份兼职——帮人查一串字符串中某个单词的出现次数。


当工作太多时，赵神就忙不过来啦，所以他想找一名助手帮他。

Input
第一行输入一个 T ，代表数据数目。


每组数据第一行输入需要查找的单词。

第二行输入这个较长的字符串（长度小于1000010）。

Output
每组数据输出一个 n ，代表要这个单词出现的次数。


Sample Input
3
ABCD
ABCD
AZA
AZAZAZA
HIDSJ
FJOSJWHABNMDS
Sample Output
1
3
0

#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

char s[1000010], p[1000010];

void cal_next(char *str, int *next, int len) {
    
    next[0] = 0; // next[0]初始化为-1，-1表示不存在相同的最大前缀和最大后缀
    int k = 0; // k初始化为-1
    next[1] = 0;
    for (int q = 2; q <= len; ++q) {
        
        while (k > 0 && str[k] != str[q-1]) {
            // 如果下一个不同，那么k就变成next[k]，注意next[k]是小于k的，无论k取任何值。
            k = next[k]; // 往前回溯
        }
        
        if (str[k] == str[q-1]) {
            // 如果相同，++k
            ++k;
        }
        // 把算的k的值（就是相同的最大前缀和最大后缀长）赋给next[q]
        next[q] = k;
    }
    //for (int i = 0; str[i]; ++i) {
      //  cout << next[i];
    //}
    //cout << next[len] << endl;
}

long long KMP(char *str, int slen, char *ptr, int plen) {
    long long int sum = 0;
    int *next = new int[plen];
    cal_next(ptr, next, plen); // 计算next数组
    
    int j = 0;
    for (int i = 1; i <= slen; i++) {
        while (j > 0 && ptr[j] != str[i-1]) {
            // ptr 和 str 不匹配，且 j > -1（表示 ptr 和 str 有部分匹配）
            j = next[j]; // 往前回溯
        }
        
        if (ptr[j] == str[i])
            j = j + 1;
        
        if (j == plen) {
            ++sum;
            j = next[j];
            // 说明 j 移动到 ptr 的最末端
            //return i-plen+1; //返回相应的位置
        }
    }
    // return -1;
    return sum;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%s%s", p, s);
        printf("%lld\n",KMP(s, (int)strlen(s), p, (int)strlen(p)));
    }
    return 0;
}

Description
创客又迎来了一批学生~刘虎子同学想要去采购一批书，但是书可是很贵哒。

没有办法给所有学生买一本新书，于是推出了一项新政策——看完一本书的同学可以把书给没看过的同学看，这样虽然看书的周期较长，但节约了经费啊~~


为了简化看书的过程，我们给每个同学编了标号，标号大的同学代表看书进度目前较快，他可以在看完书后，把书给任何一个标号严格小于他的的同学看（标号比他小的同学，看完后可以继续把书给标号更小的同学看）。每个同学的书，可以由标号大的同学那里得来，或是新买一本书。要求必须每名同学都看过书。


现在，负责去采购的刘虎子同学想要知道他最少需要购买多少本书？


Input
每组数据由多行组成。


第一行一个 n (0 < n < 3000)。


接下来有n行，每行一个数字，代表这名同学的标号（标号可能大于 long long 范围）。

Output
最少需要多少本书？
Sample Input
4
10
20
30
04
5
2
3
4
3
4
Sample Output
1
2

// 有两种做法： 1.map 2.hash
// 找出出现次数最多的数
// Map
#include <iostream>
#include <cstring>
#include <cstdio>
#include <map>
#include <string>
using namespace std;

int main() {
    
    int n;
    while (cin >> n) {
        map<string, int> m;
        string s;
        for (int i = 0; i < n; ++i) {
            cin >> s;
            char* k = &s[0];
            int j = 0;
            while (s[j] == '0') {
                ++k;
                ++j;
            }
            s = k;
            m[s]++;
        }
        map<string, int>::iterator it = m.begin();
        int tmp = 0;
        for (; it != m.end(); ++it) {
            if (tmp < it->second) {
                tmp = it->second;
            }
        }
        cout << tmp << endl;
    }
    return 0;
}

// hash
#include <iostream>
#include <cstring>
#include <cstdio>

const int MOD = 7003;
char s[100];
int Hash[7100], num[7100], res;

// ELF Hash Function
// 逻辑移位：移出去的位丢弃，空缺位（vacant bit）用 0 填充
// 算术移位：移出去的位丢弃，空缺位（vacant bit）用“符号位”来填充

unsigned int ELFHash(char *str) {
    unsigned int hash = 0, x = 0;
    while (*str != '\0')  {
        hash = (hash << 4) + (*str++);// hash左移4位，把当前字符ASCII存入hash低四位。
        if ((x = hash & 0xF0000000L) != 0) {
            // 如果最高的四位不为0，则说明字符多余7个，现在正在存第7个字符，如果不处理，再加下一个字符时，第一个字符会被移出，因此要有如下处理。
            // 该处理，如果最高位为0，就会仅仅影响5-8位，否则会影响5-31位，因为C语言使用的算数移位
            // 因为1-4位刚刚存储了新加入到字符，所以不能>>28
            hash ^= (x >> 24);
            // 本身X和hash的高4位相同，下面这行代码&~即对28-31(高4位)位清零。
            hash &= ~x;
        }
    }
    //返回一个符号位为0的数，即丢弃最高位，以免函数外产生影响。(我们可以考虑，如果只有字符，符号位不可能为负)
    return (hash & 0x7FFFFFFF);
}

void hash_table(char *str) {
    int k = ELFHash(str);
    int t = k % MOD;
    
    while(Hash[t] != k && Hash[t] != -1) {
        t = (t + 1) % MOD;
    }
    if(Hash[t] == -1) {
        num[t] = 1, Hash[t] = k;
        res = max(1, res);
    }
    else res = max(res, ++num[t]);
}

int main(int argc, const char * argv[]) {
    
    freopen("/Users/admin/Desktop/test-3.in", "r", stdin);
    freopen("/Users/admin/Desktop/test-3.out", "w", stdout);
    int n;
    while (~scanf("%d", &n)) {
        memset(Hash, -1, sizeof(Hash));
        res = 0;
        
        for (int i = 0; i < n; ++i) {
            scanf("%s", s);
            
            char* now = s;
            while (*now == '0') {
                // 处理前导0
                ++now;
            }
            hash_table(now);
        }
        cout << res << endl;
    }
    
    return 0;
}
*/
