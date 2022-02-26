//
//  main.cpp
//  ac自动机+后缀自动机
//
//  Created by admin on 18/8/18.
//  Copyright © 2018年 Amon. All rights reserved.
//
#include <cstdio>
#include <iostream>
#include <cstring>
#include <time.h>
#include <stdlib.h>
using namespace std;
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <vector>
#include <math.h>
#include <bitset>
#include <algorithm>
#include <climits>
using namespace std;

#define LS 2*i
#define RS 2*i+1
#define UP(i,x,y) for(i=x;i<=y;i++)
#define DOWN(i,x,y) for(i=x;i>=y;i--)
#define MEM(a,x) memset(a,x,sizeof(a))
#define W(a) while(a)
#define gcd(a,b) __gcd(a,b)
#define LL long long
#define N 2005
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define EXP 1e-8
#define rank rank1
int wa[N],wb[N],wsf[N],wv[N],sa[N];
int rank[N],height[N],s[N],a[N];
char str[N],str1[N],str2[N];
#define F(x) ((x)/3+((x)%3==1?0:tb))
#define G(x) ((x)<tb?(x)*3+1:((x)-tb)*3+2)
//sa:字典序中排第i位的起始位置在str中第sa[i]
//rank:就是str第i个位置的后缀是在字典序排第几
//height：字典序排i和i-1的后缀的最长公共前缀
int cmp(int *r,int a,int b,int k)
{
    return r[a]==r[b]&&r[a+k]==r[b+k];
}
void getsa(int *r,int *sa,int n,int m)//n要包含末尾添加的0
{
    int i,j,p,*x=wa,*y=wb,*t;
    for(i=0; i<m; i++)  wsf[i]=0;
    for(i=0; i<n; i++)  wsf[x[i]=r[i]]++;
    for(i=1; i<m; i++)  wsf[i]+=wsf[i-1];
    for(i=n-1; i>=0; i--)  sa[--wsf[x[i]]]=i;
    p=1;
    j=1;
    for(; p<n; j*=2,m=p)
    {
        for(p=0,i=n-j; i<n; i++)  y[p++]=i;
        for(i=0; i<n; i++)  if(sa[i]>=j)  y[p++]=sa[i]-j;
        for(i=0; i<n; i++)  wv[i]=x[y[i]];
        for(i=0; i<m; i++)  wsf[i]=0;
        for(i=0; i<n; i++)  wsf[wv[i]]++;
        for(i=1; i<m; i++)  wsf[i]+=wsf[i-1];
        for(i=n-1; i>=0; i--)  sa[--wsf[wv[i]]]=y[i];
        t=x;
        x=y;
        y=t;
        x[sa[0]]=0;
        for(p=1,i=1; i<n; i++)
            x[sa[i]]=cmp(y,sa[i-1],sa[i],j)? p-1:p++;
    }
}
void getheight(int *r,int n)//n不保存最后的0
{
    int i,j,k=0;
    for(i=1; i<=n; i++)  rank[sa[i]]=i;
    for(i=0; i<n; i++)
    {
        if(k)
            k--;
        else
            k=0;
        j=sa[rank[i]-1];
        while(r[i+k]==r[j+k])
            k++;
        height[rank[i]]=k;
    }
}

int Log[N];
int best[30][N];

void setLog()
{
    Log[0] = -1;
    for(int i=1; i<N; i++)
    {
        Log[i]=(i&(i-1))?Log[i-1]:Log[i-1] + 1 ;
    }
}
void RMQ(int n)  //初始化RMQ
{
    for(int i = 1; i <= n ; i ++) best[0][i] = height[i];
    for(int i = 1; i <= Log[n] ; i ++)
    {
        int limit = n - (1<<i) + 1;
        for(int j = 1; j <= limit ; j ++)
        {
            best[i][j] = min(best[i-1][j] , best[i-1][j+(1<<i>>1)]);
        }
    }
}
int LCP(int a,int b)  //询问a,b后缀的最长公共前缀
{
    a ++;
    int t = Log[b - a + 1];
    return min(best[t][a] , best[t][b - (1<<t) + 1]);
}
int t,n,m;

int solve(int l,int r,int n)
{
    int ans = (r-l+1)*(r-l+2)/2;
    int last = -1;
    int cnt = r-l+1;
    for(int i = 1; i<=n; i++)
    {
        if(!cnt) break;
        if(sa[i]<l || sa[i]>r) continue;
        cnt--;
        if(last == -1)
        {
            last = i;
            continue;
        }
        int a = last;
        int b = i;
        if(a>b) swap(a,b);
        int lcp = LCP(a,b);
        int la = r-sa[last]+1;//区间内该串的尾部
        int lb = r-sa[i]+1;
        if(la>=lb && lcp>=lb);//la包含lb了，那么就用la继续往后比较，借此保持字典序，来模拟得到该区间的所有height
        else last = i;
        ans-=min(lcp,min(la,lb));
    }
    return ans;
}

int main()
{
    freopen("/Users/admin/Desktop/test.txt", "r", stdin);
    freopen("/Users/admin/Desktop/test1.txt", "w", stdout);
    int i,j,k,len,l,r;
    scanf("%d",&t);
    setLog();
    W(t--)
    {
        scanf("%s",str);
        scanf("%d",&m);
        len = strlen(str);
        for(i = 0; i<len; i++)
            s[i] = str[i]-'a'+1;
        s[len] = 0;
        getsa(s,sa,len+1,30);
        getheight(s,len);
        RMQ(len);
        while(m--)
        {
            scanf("%d%d",&l,&r);
            printf("%d\n",solve(l-1,r-1,len));
        }
    }
    return 0;
}


// const int maxm=2500000;
/*
int main() {
    srand((unsigned)time(NULL));
    freopen("/Users/admin/Desktop/test.txt", "w", stdout);
    //freopen("/Users/admin/Desktop/test1.txt", "r", stdout);
    cout << 20 << endl;
    for (int i = 0; i < 20; ++i) {
        int len = rand() % 1500 + 100;
        for (int i = 0; i < len; ++i) {
            int r = rand() % 26 + 'a';
            printf("%c", r);
        }
        printf("\n");
        int q = rand() % 5000 + 100;
        printf("%d\n", q);
        for (int i = 0; i < q; ++i) {
            int a = rand() % (abs(len - 100));
            int b = a + rand() % 100;
            while (b > len) {
                --b;
            }
            cout << a << ' ' << b << endl;
        }
        
    }
    
    return 0;
}
*/
/*
struct node{
    int fa, len; // fail指针 和 步长
    int son[26]; // 26个孩子（26个不同的字母）
} t[maxm]; // 存储所有的结点

// root 编号为1，root 的 fa = 0（全局变量自动初始化为0）
int last = 1, siz = 1; // 每次插入的上一个结点，总结点数

void Insert(int c) { // c = '某一字符' - 'a'
    // p 为上一个结点，np 为当前结点
    int p = last, np = ++siz;
    // 给last重新赋值
    last = np;
    // 当前结点的步长为上一结点步长+1
    t[np].len = t[p].len + 1;
    // p一直按照fa指针往前回溯，直到：
    // 找到了 p 的 fa(0)，退出循环
    // or 找到了 p 的下一条边和自己当前这条边一样
    while(p && !t[p].son[c]) {
        t[p].son[c] = np; // 让沿途的每一个 p ，都指向自己（即实线）
        p = t[p].fa; // 回溯
    }
    if(!p) {
        // p 为 0 ，即 p = root->fa，即找到根结点了都没有找到沿途和自己边一样的
        t[np].fa = 1; // 让当前结点的 fa 指向 root(1)
    } else {
        // q 为 上一个结点的 fa 指针的下一个和自己一样的结点
        int q = t[p].son[c];
        
        if(t[p].len + 1 == t[q].len) {
            // 相等，不用新建立结点，直接建立 fa 指针
            t[np].fa = q;
        } else {
            // 否则，新创建结点
            int nq = ++siz; // 加一个结点个数
            // 复制 q
            t[nq] = t[q];
            t[nq].len = t[p].len + 1;
            t[q].fa = t[np].fa = nq;
            
            while (p && t[p].son[c] == q) {
                t[p].son[c] = nq; // 给新结点复制线（实线）
                p = t[p].fa; // 回溯
            }
        }
    }
}
int main()
{
//    long long ans = 0;
//    
//    scanf("%s",s);
//    
//    int len=(int)strlen(s);
//    
//    for(int i=0;i<len;i++)
//        Insert(s[i]-'a');
//    for(int i=1;i<=siz;i++) c[t[i].len]++;
//    for(int i=1;i<=siz;i++) c[i]+=c[i-1];
//    for(int i=1;i<=siz;i++) a[c[t[i].len]--]=i;
//    for(int i=siz;i;i--)
//    {
//        int now=a[i];
//        size[t[now].fa]+=size[now];
//        if(size[now]>1) ans=std::max(ans,1ll*size[now]*t[now].len);
//    }
//    printf("%lld\n",ans);
    return 0;
}
*/
/*
#include <map>
using namespace std;

#define N 101000
#define T 26

int pa[N<<1], son[N<<1][T];
int deep[N<<1], cnt, root, last;
char str[N];

int Newnode(int _deep) {
    deep[++cnt] = _deep;
    return cnt;
}

void SAM(int alp) {
    int cur = Newnode(deep[last]+1);
    int u = last;
    while(u && !son[u][alp]) {
        son[u][alp] = cur;
        u = pa[u];
    }
    
    if(!u) {
        pa[cur] = root;
    } else {
        
        int v = son[u][alp];
        if(deep[v] == deep[u]+1) {
            pa[cur] = v;
        } else {
            int nv = Newnode(deep[u]+1);
            memcpy(son[nv], son[v], sizeof(son[v]));
            pa[nv] = pa[v], pa[v] = pa[cur] = nv;
            
            while(u && son[u][alp] == v) {
                son[u][alp] = nv;
                u = pa[u];
            }
        }
    }
    last = cur;
}

void pre() {
    root = last = Newnode(0);
}

/*
struct state {
    int len, link;
    map<char, int> next;
};

const int MAXLEN = 100000;
state st[MAXLEN*2];
int sz, last; // last——当前匹配整个字符串的状态

void sa_init() {
    sz = last = 0;
    st[0].len = 0;
    st[0].link = -1;
    ++sz;
 
     // 若关于不同的字符串多次建立后缀自动机，就需要执行这些代码：
    // for (int i=0; i<MAXLEN*2; ++i)
//     st[i].next.clear();
 
}

// 向当前字符串的尾部添加一个字符，并相应地修改后缀自动机
void sa_extend (char c) {
    int cur = sz++;
    st[cur].len = st[last].len + 1; // 长度加1
    
    int p;
    for (p = last; p != -1 && !st[p].next.count(c); p = st[p].link)
        st[p].next[c] = cur;
    
    if (p == -1) {
        st[cur].link = 0;
    } else {
        int q = st[p].next[c];
        if (st[p].len + 1 == st[q].len) {
            st[cur].link = q;
        } else {
            int clone = sz++;
            st[clone].len = st[p].len + 1;
            st[clone].next = st[q].next;
            st[clone].link = st[q].link;
            for (; p != -1 && st[p].next[c] == q; p = st[p].link) {
                st[p].next[c] = clone;
            }
            st[q].link = st[cur].link = clone;
        }
    }
    last = cur;
}

int main() {
    return 0;
}
*/
/*
#include <iostream>
#include <queue>
using namespace std;

int cnt;

struct node{
    node *next[26]; // 下一个结点
    node *fail; // 失配指针指向
    int sum;
} *root;

// 字典树的建立
void Insert(char *s) {
    node *p = root;
    
    for(int i = 0; s[i]; ++i) {
        
        int x = s[i] - 'a';
        
        if(p->next[x] == NULL) {
            // 没有过这个结点
            struct node* newnode = new node;
            
            for(int j = 0; j < 26; ++j) {
                newnode->next[j] = 0;
            }
            newnode->sum = 0;
            newnode->fail = 0;
            // 建立字典树的过程中，先让每个节点的fail指针先为空
            p->next[x] = newnode;
        }
        p = p->next[x];
    }
    p->sum++;
}

// 基于广度搜索构造 fail 指针
void build_fail_pointer() {
    queue<node*> q;
    q.push(root);
    node* p;
    node* temp;
    while(!q.empty()) {
        temp = q.front(); // 取出队首元素
        q.pop(); // 出队列
        for(int i = 0; i < 26; i++) {
            if(temp->next[i]) { // 下面这个字符有结点
                if(temp == root) { // root 的 fail 指针 指向自己
                    temp->next[i]->fail = root;
                } else {  // 其他结点 类比kmp
                    p = temp->fail;
                    while(p) {
                        // 判断下一个结点是否存在
                        if(p->next[i]) {
                            temp->next[i]->fail = p->next[i];
                            break;
                        }
                        p = p->fail; // 回溯
                    }
                    if(p == NULL) temp->next[i]->fail = root;
                }
                q.push(temp->next[i]); // 再加入队列
            }
        }
    }
}

// 利用求得的 fail 指针进行匹配
// 从root节点开始，每次根据读入的字符沿着自动机向下移动。
// 当读入的字符，在分支中不存在时，递归走失败路径。如果走失败路径走到了root节点，则跳过该字符，处理下一个字符。
// 因为AC自动机是沿着输入文本的最长后缀移动的，所以在读取完所有输入文本后，最后递归走失败路径，直到到达根节点，这样可以检测出所有的模式。
void ac_automation(char* str) {
    
    node* p = root;
    int len = (int)strlen(str);
    
    for(int i = 0; i < len; ++i) {
        int x = str[i] - 'a';
        
        while(!p->next[x] && p != root) {
            p = p->fail;
        }
        p = p->next[x];
        
        if(!p) {
            p = root;
        }
        node* temp = p;
        while(temp != root) {
            if(temp->sum >= 0) {
                cnt += temp->sum;
                temp->sum = -1;
            } else {
                break;
            }
            temp = temp->fail;
        }
    }
}

// 释放内存
void destory() {
    if(root == NULL)
        return;
    queue<node*> q;
    node* tmp = NULL;
    q.push(root);
    
    while(!q.empty()) {
        tmp = q.front();
        q.pop();
        for (int i = 0; i < 26; i++) {
            if(tmp->next[i]) {
                q.push(tmp->next[i]);
            }
        }
        free(tmp);
    }
    return;
}

int main(int argc, const char * argv[]) {
    int n, m;
    while (cin >> n) {
        for (int i = 0; i < 26; i++) {
            root->next[i] = 0;
        }
        char s[10000];
        for (int i = 0; i < n; ++i) {
            scanf("%s", s);
            Insert(s);
        }
        cin >> m;
        for (int i = 0; i < m; ++i) {
            scanf("%s", s);
            ac_automation(s);
        }
        destory();
    }
    return 0;
}
*/
