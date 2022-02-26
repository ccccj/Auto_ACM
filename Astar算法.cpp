//
//  main.cpp
//  A星
//
//  Created by admin on 18/9/12.
//  Copyright © 2018年 Amon. All rights reserved.
/*
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
const int INF = 1e9;
const int maxm = 10005;
const int maxn = 1005;
typedef long long LL;
struct Edge {
    int to, next, length;
} edge[maxm], reedge[maxm];
struct A_node {
    int F, G, H;
    int id, k;
    friend bool operator < (A_node A, A_node B) {
        return A.F > B.F;
    }
} node[maxn];
int head[maxn], rehead[maxn], path[maxn];
int n, m, S, E, K, T, cnt, u, v, t;
bool vis[maxn];

void add_edge(int u, int v, int len) {
    edge[++cnt].next = head[u];
    edge[cnt].to = v;
    edge[cnt].length = len;
    head[u] = cnt;
    reedge[cnt].next = rehead[v];
    reedge[cnt].to = u;
    reedge[cnt].length = len;
    rehead[v] = cnt;
}

void init() {
    memset(head, 0, sizeof head);
    memset(rehead, 0, sizeof rehead);
    memset(edge, 0, sizeof edge);
    memset(reedge, 0, sizeof reedge);
    fill(path, path + maxn, INF);
    memset(vis, 0, sizeof vis);
    memset(node, 0, sizeof node);
    cnt = 0;
}

int main(int argc, const char * argv[]) {
    
    while (scanf("%d %d", &n, &m) != EOF) {
        init();
        scanf("%d %d %d %d", &S, &E, &K, &T);
        for (int i = 0; i < m; i++) {
            scanf("%d %d %d", &u, &v, &t);
            add_edge(u, v, t);
        }
        
        queue<int> q;
        q.push(E);
        path[E] = 0;
        vis[E] = true;
        while (!q.empty()) {
            int now = q.front(); q.pop();
            vis[now] = false;
            for (int i = rehead[now]; i; i = reedge[i].next) {
                int to = reedge[i].to, cost = reedge[i].length;
                if (path[now] + cost < path[to]) {
                    path[to] = path[now] + cost;
                    if (vis[to] == false) {
                        q.push(to);
                        vis[to] = true;
                    }
                }
            }
        }
        
//        for (int i = 1; i <= n; i++) {
//            printf("* %d\n", path[i]);
//        }
        
        A_node now = {path[S], 0, path[S], S, 1};
        priority_queue<A_node> A_star;
        A_star.push(now);
        while (!A_star.empty()) {
            now = A_star.top(); A_star.pop();
            //printf("%lld %lld %lld\n", now.F, now.G, now.H);
            if (now.id == E && now.k == K) {
                break;
            }
            if (now.G >= T) {
                now.G += 1;
                break;
            }
            int k = now.k;
            if (now.id == E) {
                k++;
                while (!A_star.empty()) A_star.pop();
            }
            
            for (int i = head[now.id]; i; i = edge[i].next) {
                int to = edge[i].to, cost = edge[i].length;
                A_node temp = {now.G + cost + path[to], now.G + cost, path[to], to, k};
                A_star.push(temp);
            }
        }
        //printf("%d\n", now.G);
        if (now.G <= T) printf("yareyaredawa\n");
        else printf("Whitesnake!\n");
    }
    
    
    return 0;
}
*/
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
const int INF = 1e9;
const int maxm = 10005;
const int maxn = 1005;
typedef long long LL;

struct Edge {
    int to, next, length;
} edge[maxm], reedge[maxm];

struct A_node {
    int F, G, H, id;
    friend bool operator < (A_node A, A_node B) {
        return A.F > B.F;
    }
} node[maxn];

struct dij {
    int id, length;
    friend bool operator < (dij a, dij b) {
        return a.length > b.length;
    }
};

int head[maxn], rehead[maxn], path[maxn];
int n, m, S, E, K, T, cnt, u, v, t;
bool vis[maxn];

void add_edge(int u, int v, int len) {
    edge[++cnt].next = head[u];
    edge[cnt].to = v;
    edge[cnt].length = len;
    head[u] = cnt;
    
    reedge[cnt].next = rehead[v];
    reedge[cnt].to = u;
    reedge[cnt].length = len;
    rehead[v] = cnt;
}

void init() {
    memset(head, 0, sizeof head);
    memset(rehead, 0, sizeof rehead);
    memset(edge, 0, sizeof edge);
    memset(reedge, 0, sizeof reedge);
    fill(path, path + maxn, INF);
    memset(vis, 0, sizeof vis);
    memset(node, 0, sizeof node);
    cnt = 0;
}

void dijs() {
    priority_queue<dij> q;
    q.push({E, 0});
    path[E] = 0;
    while (!q.empty()) {
        dij now = q.top(); q.pop();
        if (vis[now.id] == true) continue;
        vis[now.id] = true;
        for (int i = rehead[now.id]; i; i = reedge[i].next) {
            int to = reedge[i].to;
            if (path[to] > path[now.id] + reedge[i].length) {
                path[to] = path[now.id] + reedge[i].length;
                q.push({to, path[to]});
            }
        }
    }
//            for (int i = 1; i <= n; i++) {
//                printf("* %d\n", path[i]);
//            }
}

int main(int argc, const char * argv[]) {
    
    while (scanf("%d %d", &n, &m) != EOF) {
        init();
        scanf("%d %d %d %d", &S, &E, &K, &T);
        for (int i = 0; i < m; i++) {
            scanf("%d %d %d", &u, &v, &t);
            add_edge(u, v, t);
        }
        dijs();
        
        if (path[S] == INF) {
            printf("Whitesnake!\n");
            continue;
        }
        A_node now = {path[S], 0, path[S], S};
        priority_queue<A_node> A_star;
        A_star.push(now);
        int k = 0;
        while (!A_star.empty()) {
            now = A_star.top(); A_star.pop();
            //printf("%lld %lld %lld\n", now.F, now.G, now.H);
            if (now.id == E) {
                ++k;
            }
            if (k == K) {
                break;
            }
            if (now.G > T) {
                break;
            }
            
//            if (now.id == E) {
//                k++;
//                //while (!A_star.empty()) A_star.pop();
//            }

            for (int i = head[now.id]; i; i = edge[i].next) {
                int to = edge[i].to, cost = edge[i].length;
                A_node temp;
             
                temp = {now.G + cost + path[to], now.G + cost, path[to], to};
                A_star.push(temp);
            }
        }
        //printf("%d\n", now.G);
        if (now.G <= T) printf("yareyaredawa\n");
        else printf("Whitesnake!\n");
    }
    
    
    return 0;
}
