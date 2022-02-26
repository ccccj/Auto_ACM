//
//  main.cpp
//  计算几何
//
//  Created by admin on 18/8/22.
//  Copyright © 2018年 Amon. All rights reserved.
//
判断是否存在一条直线，经过所有的线段即可。
若存在，则这条直线必然可以经过两个端点。
将所有点两两相连作为直线，判断是否经过其他线段即可。
// poj3304
Problem D: 线段的投影

给定二维空间中的n个线段，确定是否存在一条直线，使得将这些段投影到其上之后，所有投影至少有一个共同点。

Input
输入以数字T开头，显示测试用例的数量，然后是T组测试用例。

对于每组测试用例，n表示线段的个数(n<=100)随后是n行包含四个实数x1 y1 x2 y2，其中（x1，y1）和（x2，y2）是其中一个线段的两个端点的坐标。

Output
对于每个测试用例，如果存在存在题目要求的直线，输出“Yes!”，否则输出“No!”。如果| a - b |<10-8，则两个浮点数a和b相等。
Sample Input
3
2
1.0 2.0 3.0 4.0
4.0 5.0 6.0 7.0
3
0.0 0.0 0.0 1.0
0.0 1.0 0.0 2.0
1.0 1.0 2.0 1.0
3
0.0 0.0 0.0 1.0
0.0 2.0 0.0 3.0
1.0 1.0 2.0 1.0
Sample Output
Yes!
Yes!
No!

#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <cstdio>
using namespace std;
const double EPS = 1e-9;

int dcmp(double x) {
    if (fabs(x) < EPS) return 0;
    if (x>0) return 1;
    return -1;
}

struct Vector {
    double x, y;
    bool operator==(const Vector& a) {
        return dcmp(a.x-x) == 0 && dcmp(a.y-y) == 0;
    }
};

struct point {
    double x, y;
    Vector operator-(const point& a) {
        Vector tmp = {x - a.x, y - a.y};
        return tmp;
    }
} s[110], e[110];

double cross(Vector A, Vector B)  { //叉积
    return A.x * B.y - A.y * B.x;
}

bool operator ==(const point& a, const point& b) {
    return dcmp(a.x-b.x) == 0 && dcmp(a.y-b.y) == 0;
}

// 直线a1a2是否与线段b1b2相交
bool SegmentItersection(point a1, point a2, point b1, point b2) {
    if (a1 == a2) {
        return 0;
    }
    double c1 = cross(a2-a1, b1-a1), c2 = cross(a2-a1, b2-a1);
    return dcmp(c1) * dcmp(c2) <= 0;
}


int main() {
    //freopen("/Users/admin/Desktop/test-8.in", "r", stdin);
    //freopen("/Users/admin/Desktop/aaa.txt", "w", stdout);
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i) {
            scanf("%lf%lf%lf%lf", &s[i].x, &s[i].y, &e[i].x, &e[i].y);
        }
        int flag1 = 1, flag2 = 1, flag3 = 1, flag4 = 1;
        for (int i = 0; i < n - 1; ++i) {
            for (int j = i + 1; j < n; ++j) {
                flag1 = 1, flag2 = 1, flag3 = 1, flag4 = 1;
                for (int k = 0; k < n; ++k) {
                    if (k == i || k == j) continue;
                    if (flag1 == 1
                        && SegmentItersection(s[i], s[j], s[k], e[k]) == 0) {
                        flag1 = 0;
                    }
                    if (flag2 == 1
                        && SegmentItersection(s[i], e[j], s[k], e[k]) == 0) {
                        flag2 = 0;
                    }
                    if (flag3 == 1
                        && SegmentItersection(e[i], s[j], s[k], e[k]) == 0) {
                        flag3 = 0;
                    }
                    if (flag4 == 1
                        && SegmentItersection(e[i], e[j], s[k], e[k]) == 0) {
                        flag4 = 0;
                    }
                    if (!(flag1 || flag2 || flag3 || flag4)) {
                        break;
                    }
                }
                if (flag1 || flag2 || flag3 || flag4) {
                    break;
                }
            }
            if (flag1 || flag2 || flag3 || flag4) {
                break;
            }
        }
        if (flag1 || flag2 || flag3 || flag4) {
            cout << "Yes!" << endl;
        } else {
            cout << "No!" << endl;
        }
    }
    
    return 0;
}


/*
// D错误做法，目前还不知道错哪了
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
const double EPS = 1e-9;

int dcmp(double x) {
    if (fabs(x) < EPS) return 0;
    if (x>0) return 1;
    return -1;
}

struct Vector {
    double x, y;
    bool operator==(const Vector& a) {
        return dcmp(a.x-x) == 0 && dcmp(a.y-y) == 0;
    }
};

struct point {
    double x, y;
    Vector operator-(const point& a) {
        Vector tmp = {x - a.x, y - a.y};
        return tmp;
    }
} s[110], e[110];

double dot(Vector A, Vector B) {    //向量点积
    return A.x * B.x + A.y * B.y;
}

double Length(Vector A) {    //向量A长度
    return sqrt(dot(A, A));
}

double angle(Vector A, Vector B) {    //向量A和B夹角
    return acos(dot(A,B) / Length(A) / Length(B));
}

int main() {
    //freopen("/Users/admin/Desktop/test-8.in", "r", stdin);
    //freopen("/Users/admin/Desktop/aaa.txt", "w", stdout);
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i) {
            scanf("%lf%lf%lf%lf", &s[i].x, &s[i].y, &e[i].x, &e[i].y);
        }
        int f = 0;
        for (int i = 0; i < n; ++i) {
            double min1 = 0, max1 = 180;
            int flag1 = 1, flag2 = 1;
            for (int j = 0; j < n; ++j) {
                if (i == j) {
                    continue;
                }
                point start = {s[i].x, s[i].y},
                      end1 = {e[i].x, e[i].y},
                      end2 = {s[j].x, s[j].y},
                      end3 = {e[j].x, e[j].y};
                Vector v1 = end1 - start,
                       v2 = end2 - start,
                       v3 = end3 - start;
                double x = angle(v1, v2), y = angle(v1, v3);
                if (x > y) swap(x, y);
                if (x < max1 || dcmp(x-max1)) {
                    min1 = max(x, min1);
                } else {
                    flag1 = 0;
                    break;
                }
                if (y > min1 || dcmp(y-min1)) {
                    max1 = min(y, max1);
                } else {
                    flag1 = 0;
                    break;
                }
                if (min1 > max1) {
                    flag1 = 0;
                    break;
                }
            }
            if (flag1 == 1) {
                f = 1;
                break;
            }
            min1 = 0, max1 = 180;
            for (int j = 0; j < n; ++j) {
                if (i == j) {
                    continue;
                }
                point start = {e[i].x, e[i].y},
                end1 = {s[i].x, s[i].y},
                end2 = {s[j].x, s[j].y},
                end3 = {e[j].x, e[j].y};
                
                Vector v1 = end1 - start,
                v2 = end2 - start,
                v3 = end3 - start;
                
                double x = angle(v1, v2), y = angle(v1, v3);
                if (x > y) swap(x, y);
                
                if (x < max1 || dcmp(x-max1)) {
                    min1 = max(x, min1);
                } else {
                    flag2 = 0;
                    break;
                }
                if (y > min1 || dcmp(y-min1)) {
                    max1 = min(y, max1);
                } else {
                    flag2 = 0;
                    break;
                }
                if (min1 > max1) {
                    flag2 = 0;
                    break;
                }
            }
            if (flag2 == 1) {
                f = 1;
                break;
            }
        }
        if (f == 1) {
            printf("Yes!\n");
        } else {
            printf("No!\n");
        }
        
        
    }
    
    return 0;
}


Problem B: 圆与三角形
给出圆的圆心和半径，以及三角形的三个顶点，问圆同三角形是否相交。相交输出"Yes"，否则输出"No"。（三角形的面积大于0）。

Input
第1行：一个数T，表示输入的测试数量(1 <= T <= 10000)，之后每4行用来描述一组测试数据。

4-1：三个数，前两个数为圆心的坐标xc yc，第3个数为圆的半径R。(-3000 <= xc yc <= 3000 1 <= R <= 3000）
4-2：2个数，三角形第1个点的坐标。
4-3：2个数，三角形第2个点的坐标。
4-4：2个数，三角形第3个点的坐标。(-3000 <= xi yi <= 3000）
                                                        
Output
共T行，对于每组输入数据，相交输出"Yes"，否则输出"No"。
Sample Input
2
0 0 10
10 0
15 0
15 5
0 0 10
0 0
5 0
5 5
Sample Output
Yes
No
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;

const double EPS = 1e-9;

int dcmp(double x) {
    if (fabs(x) < EPS) return 0;
    if (x>0) return 1;
    return -1;
}

struct Vector {
    double x, y;
    bool operator==(const Vector& a) {
        return dcmp(a.x-x) == 0 && dcmp(a.y-y) == 0;
    }
};

struct point {
    double x, y;
    Vector operator-(const point& a) {
        Vector tmp = {x - a.x, y - a.y};
        return tmp;
    }
} v[5];

// 判断点是否同一个点
bool operator ==(const point& a, const point& b) {
    return dcmp(a.x-b.x) == 0 && dcmp(a.y-b.y) == 0;
}

double dis(int a, int b, int c, int d) {
    return sqrt((c-a) * (c-a) + (d-b) * (d-b));
}

double dot(Vector A, Vector B) {    //向量点积
    return A.x * B.x + A.y * B.y;
}
double Length(Vector A) {    //向量A长度
    return sqrt(dot(A, A));
}

double cross(Vector A, Vector B)  { //叉积
    return A.x * B.y - A.y * B.x;
}

double DistoSegment(point P, point A, point B){
    if(A == B) return Length(P - A); //两点之间的距离
    Vector v1 = B - A, v2 = P - A, v3 = P - B;
    if (dcmp(dot(v1, v2)) < 0) return Length(v2); // p点投影到射线
    if (dcmp(dot(v1, v3)) > 0) return Length(v3); // p点投影到射线
    return fabs(cross(v1,v2)) / Length(v1); // p点投影到线段
}


int is[10];

int main() {
    int T;
    cin >> T;
    double a, b, r;
    while (T--) {
        memset(is, 0, sizeof(is));
        cin >> a >> b >> r;
        int f = 0;
        for (int i = 0; i < 3; ++i) {
            cin >> v[i].x >> v[i].y;

            if (dis(v[i].x, v[i].y, a, b) < r) {
                is[i] = -1;
            } else if (abs(dis(v[i].x, v[i].y, a, b) - r) < EPS) {
                f = 1;
            } else {
                is[i] = 1;
            }
        }
        if (f) {
            cout << "Yes" << endl;
            continue;
        }
        if (is[0] + is[1] + is[2] == -3) {
            cout << "No" << endl;
            continue;
        }
        
        double ans = DistoSegment({a, b}, v[0], v[1]);
        if (ans <= r) {
            f = 1;
        }
        ans = DistoSegment({a, b}, v[1], v[2]);
        if (ans <= r) {
            f = 1;
        }
        ans = DistoSegment({a, b}, v[0], v[2]);
        if (ans <= r) {
            f = 1;
        }
        if (f) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
        
    }
    return 0;
}


Problem C: 调多大的角度
假如你是一位迫击炮炮手，需要摧毁同一地平线上，距离为s米的地方工事，你要讲炮口角度a调为多少合适，炮口角度a定义为炮身与地平线的夹角，单位为角度，忽略空气阻力，忽略地球是圆的。当然，也可能会因为距离太远无法射到，如果太远，请计算出需要向目标移动的最短距离。迫击炮也有最短射程b米，低于(<b)的都无法射到。

Input
有多组输入数据，每组一行v  s  b

初始速度v，敌人距离s，迫击炮最短射程b，全部为大于0的整数。

v的单位是米/秒。

文件结束时输入数据结束。

Output
如果可以射到，先输出一个a和一个空格，再输出角度，单位为角度，保留到个位即可。

如果太远无法到达，先输出move和一个空格，再输出最短移动距离，保留两位小数，并保证移动后必须能够射到目标。

如果太近无法射到，输出-1。

注意：G值为9.8

Sample Input
10 10 5
556 25956 139
211 28944 74
446 22680 24824
Sample Output
a 39
a 28
move 24401.04
-1

#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;

const double g = 9.8, pi = acos(-1);

int main() {
    
    double v, x, Min;
    int ca = 1;
    while (cin >> v >> x >> Min) {
        if (ca++ > 1) {
            cout << endl;
        }
        if (x < Min) {
            cout << -1 << endl;
            continue;
        }
        double smax = v * v / g;
        if (smax < x) {
            printf("move %.2lf\n", x - smax);
        } else {
            double sin = g * x / v / v;
            printf("a %.0lf\n", (asin(sin) * 90 / pi));
            
        }
        
    }
    return 0;
}


海伦公式求解
Problem A: 三角形的面积
Description

我愿为自己加上private

在你的class中

只有你能调用

Lily的老师给他出了一个问题，给出三角形的三边长abc，lily要计算出这个三角形的面积，liy比较懒（周末要睡觉嘛），现在要向你求助。

Input
有多组测试数据，第一行输入一个整数T表示测试数据的组数。

接下来T组测试数据，每组测试数据占一行。该行包含三个整数a b c，为三角形的三边。

Output
对每组测试数据，输出一行。如果三条边能构成三角形，则输出三角形的面积并保留三位小数，否则输出“-1”。相邻两组测试数据输出之间有一个空行。
Sample Input
2
1 2 3
3 4 5
Sample Output
-1

6.000

#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

const double EPS = 1e-9;
double arr[10];

bool cmp(double a, double b) {
    return a < b;
}

int main(int argc, const char * argv[]) {
    int T, ca = 1;
    cin >> T;
    while (T--) {
        if (ca++ > 1) {
            cout << endl;
        }
        for (int i = 0; i < 3; ++i) {
            cin >> arr[i];
        }
        sort(arr, arr + 3, cmp);
        if (arr[0] + arr[1] < arr[2]
            || abs(arr[2] - arr[0] - arr[1]) < EPS) {
            cout << -1 << endl;
            continue;
        }
        double s = (arr[2] + arr[0] + arr[1]) / 2;
        double ans = s * (s - arr[0]) * (s - arr[1]) * (s - arr[2]);
        printf("%0.3lf\n", sqrt(ans));
    }
    
    return 0;
}
*/
