//
//  main.cpp
//  7.19
//
//  Created by admin on 18/7/19.
//  Copyright © 2018年 Amon. All rights reserved.
//
//  J 最大/小栈简单应用
Description
As an ACM-ICPC newbie，Aishah is learning data structures in computer science. She has already known that a stack， as a data structure，can serve as a collection of elements with two operations:

• push，which inserts an element to the collection， and

• pop， which deletes the most recently inserted element that has not yet deleted.

Now， Aishah hopes a more intelligent stack which can display the maximum element in the stack dynamically. Please write a program to help her accomplish this goal and go through a test with several operations. Aishah assumes that the stack is empty at first. Your program will output the maximum element in the stack after each operation. If at some point the stack is empty， the output should be zero.


Input
The input contains several test cases and the first line is a positive integer T indicating the number of test cases which is up to 50.

To avoid unconcerned time consuming in reading data，each test case is described by seven integers n (1 ≤ n ≤ 5 × 106 ) ，p， q， m (1 ≤ p q m ≤ 109 )， SA， SB and SC (104 ≤ SA SB SC ≤ 106 ). The integer n is the number of operations，and your program should generate all operations using the following code in C++.


int n，p，q，m;
unsigned int SA，SB，SC;
unsigned int rng61(){
    SA ^= SA << 16;
    SA ^= SA >> 5;
    SA ^= SA << 1;
    unsigned int t = SA;
    SA = SB;
    SB = SC;
    SC ^= t ^ SA;
    return SC;
}
void gen(){
    scanf("%d%d%d%d%u%u%u" &n，&p，&q，&m，&SA，&SB，&SC);
    for(int i = 1; i <= n; i++){
        if(rng61() % (p + q) < p)
            PUSH(rng61() % m + 1);
        else
            POP();
    }
}

The procedure PUSH(v) used in the code inserts a new element with value v into the stack and the procedure POP() pops the topmost element in the stack or does nothing if the stack is empty.

Output
For each test case，output a line containing Case #x: y where x is the test case number starting from 1，and y is equal to  where ai is the answer after the i-th operation and ⊕ means bitwise xor.

Sample Input
2
4 1 1 4 23333 66666 233333
4 2 1 4 23333 66666 233333

Sample Output
Case #1: 19
Case #2: 1
HINT

The first test case in the sample input has 4 operations:
• POP();
• POP();
• PUSH(1);
• PUSH(4).
The second test case also has 4 operations:
• PUSH(2);
• POP();
• PUSH(1);
• POP().

#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

int n, p, q, m;
unsigned int SA, SB, SC;

unsigned int rng61(){
    SA ^= SA << 16;
    SA ^= SA >> 5;
    SA ^= SA << 1;
    unsigned int t = SA;
    SA = SB;
    SB = SC;
    SC ^= t ^ SA;
    return SC;
}

int arr1[1010];
int h1, h2;
int arr2[1010];

void PUSH(int v) {
    arr1[h1++] = v;
    if (arr2[h2 - 1] > v) {
        arr2[h2] = arr2[h2 - 1];
        ++h2;
    } else {
        arr2[h2++] = v;
    }
}

void POP() {
    --h1, --h2;
    if (h1 < 0) { h1 = 0; h2 = 0;}
}

int main() {
    int T;
    cin >> T;
    int _ca = 1;
    while (T--) {
        int sum = 0;
        memset(arr1, 0, sizeof(arr1));
        memset(arr2, 0, sizeof(arr2));
        h1 = h2 = 0;
        cin >> n >> p >> q >> m >> SA >> SB >> SC;
        for(int i = 1; i <= n; i++){
            if(rng61() % (p + q) < p)
                PUSH(rng61() % m + 1);
            else
                POP();
            int k;
            if (h2 == 0)
                k = 0;
            else
                k = arr2[h2 - 1];
            sum ^= (k * i);
        }
        printf("Case #%d: ", _ca++);
        cout << sum << endl;
    }
    
    return 0;
}


// I
Description
期末试卷已经改完啦，老师想知道在多名同学中，分数最高的是多少。
当然，老师有时候需要更新某位同学的成绩。

Input
输入包含多组测试数据。
每组输入第一行是两个正整数N和M（0<N<=30000，0<M<5000），分别代表学生的数目和操作的数目。
学生ID编号从1到N。
第二行包含N个整数，代表这N个学生的初始成绩，其中第i个数代表ID为i的学生的成绩。
接下来有M行。每一行有一个字符C(只取‘Q’或‘U’)，和两个正整数A，B。
当C为‘Q’的时候，表示这是一条询问操作，它询问ID从A到B(包括AB)的学生当中，成绩最高的是多少。
当C为‘U’的时候，表示这是一条更新操作，要求把ID为A的学生的成绩更改为B。

Output
对于每一次询问操作，在一行里面输出最高成绩。

Sample Input
5 6
1 2 3 4 5
Q 1 5
U 3 6
Q 3 4
Q 4 5
U 2 9
Q 1 5

Sample Output
5
6
5
9

#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

int arr[30010];

int main() {
    
    int n, m;
    while (cin >> n >> m) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", &arr[i]);
        }
        for (int i = 0; i < m; ++i) {
            char c;
            int a, b;
            scanf("\n%c %d%d", &c, &a, &b);
            if (c == 'Q') {
                int tmp = arr[a];
                for (int j = a + 1; j <= b; ++j) {
                    if (tmp < arr[j]) {
                        tmp = arr[j];
                    }
                }
                cout << tmp << endl;
            } else {
                arr[a] = b;
            }
            
        }
        
        
    }
    return 0;
}


// H
Description
呵呵。大家都知道五代以内不得通婚，即两个人最近的共同祖先如果在五代以内（即本人、父母、祖父母、曾祖父母、高祖父母）则不可通婚。本题就请你帮助一对有情人判断一下，他们究竟是否可以成婚？

Input
输入第一行给出一个正整数N（2 <= N <= 104），随后N行，每行按以下格式给出一个人的信息：

本人ID 性别 父亲ID 母亲ID

其中ID是5位数字，每人不同；性别M代表男性、F代表女性。如果某人的父亲或母亲已经不可考，则相应的ID位置上标记为-1。

接下来给出一个正整数K，随后K行，每行给出一对有情人的ID，其间以空格分隔。

注意：题目保证两个人是同辈，每人只有一个性别，并且血缘关系网中没有乱伦或隔辈成婚的情况。

Output
对每一对有情人，判断他们的关系是否可以通婚：如果两人是同性，输出“Never Mind”；如果是异性并且关系出了五代，输出“Yes”；如果异性关系未出五代，输出“No”。

Sample Input
24
00001 M 01111 -1
00002 F 02222 03333
00003 M 02222 03333
00004 F 04444 03333
00005 M 04444 05555
00006 F 04444 05555
00007 F 06666 07777
00008 M 06666 07777
00009 M 00001 00002
00010 M 00003 00006
00011 F 00005 00007
00012 F 00008 08888
00013 F 00009 00011
00014 M 00010 09999
00015 M 00010 09999
00016 M 10000 00012
00017 F -1 00012
00018 F 11000 00013
00019 F 11100 00018
00020 F 00015 11110
00021 M 11100 00020
00022 M 00016 -1
00023 M 10012 00017
00024 M 00022 10013
9
00021 00024
00019 00024
00011 00012
00022 00018
00001 00004
00013 00016
00017 00015
00019 00021
00010 00011

Sample Output
Never Mind
Yes
Never Mind
No
Yes
No
Yes
No
No

#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;
struct node {
    char sex;
    int father, mother;
} per[100100];

bool can(int a, int b, int road) {
    if (road == 5) {
        return 1;
    }
    if (a == -1 || b == -1) {
        return 1;
    }
    if (a == b) {
        return 0;
    }
    if (per[a].father == 0 || per[b].father == 0) {
        return 1;
    }
    return can(per[a].father, per[b].father, road + 1)
    && can(per[a].mother, per[b].mother, road + 1)
    && can(per[a].father, per[b].mother, road + 1)
    && can(per[a].mother, per[b].father, road + 1);
}

int main() {
    
    int n;
    while (cin >> n) {
        memset(per, 0, sizeof(per));
        for (int i = 0; i < n; ++i) {
            int id, f, m;
            scanf("%d", &id);
            scanf(" %c %d%d", &per[id].sex, &f, &m);
            per[id].father = f, per[id].mother = m;
            if (f != -1) per[f].sex = 'M';
            if (m != -1) per[m].sex = 'F';
        }
        int q, a, b;
        cin >> q;
        for (int i = 0; i < q; ++i) {
            scanf("%d%d", &a, &b);
            if (per[a].sex == per[b].sex) {
                cout << "Never Mind" << endl;
            } else {
                if (can(a, b, 0)) {
                    cout << "Yes" << endl;
                } else {
                    cout << "No" << endl;
                }
            }
        }
    }
    return 0;
}

 
 
// G
Description
有一棵树，输出某一深度的所有节点，有则输出这些节点，无则输出EMPTY。该树是完全二叉树。

Input
输入有多组数据。

每组输入一个n(1<=n<=1000)，然后将树中的这n个节点依次输入，再输入一个d代表深度。

输入0时结束。


Output
输出该树中第d层得所有节点，节点间用空格隔开，最后一个节点后没有空格。


Sample Input
5
1 2 3 4 5
7
7
1 2 3 4 5 6 7
2
0

Sample Output
EMPTY
2 3

#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

int arr[1010];

int main() {
    
    int n;
    while (cin >> n && n) {
        for (int i = 0; i < n; ++i) {
            scanf("%d", &arr[i]);
        }
        int k;
        cin >> k;
        if (pow(2, k - 1) - 1 >= n) {
            cout << "EMPTY" << endl;
            continue;
        }
        for (int j = pow(2, k - 1) - 1;
             j < pow(2, k - 1) - 1 + pow(2, k - 1) && j < n; ++j) {
            cout << arr[j] << ' ';
        }
        cout << endl;
    }
    return 0;
}


// F
Description
把一个字符三角形掏空，就能节省材料成本，减轻重量，但关键是为了追求另一种视觉效果。在设计的过程中，需要给出各种花纹的材料和大小尺寸的三角形样板，通过电脑临时做出来，以便看看效果。
Input
每行包含一个字符和一个整数n(0<n<41)，不同的字符表示不同的花纹，整数n表示等腰三角形的高。显然其底边长为2n-1。如果遇到@字符，则表示所做出来的样板三角形已经够了。

Output
每个样板三角形之间应空上一行，三角形的中间为空。显然行末没有多余的空格。

Sample Input
X 2
A 7
@

Sample Output
 X
XXX
　
      A
     A A
    A   A
   A     A
  A       A
 A         A
AAAAAAAAAAAAA

#include <iostream>
#include <cstdio>
using namespace std;

int main() {
    
    char a;
    int _ca = 0;
    while (cin >> a && a != '@') {
        if (_ca++ > 0) {
            cout << endl;
        }
        int num;
        cin >> num;
        if (num == 1) {
            cout << a << endl;
            continue;
        } else if (num > 1) {
            for (int j = 0; j < num - 1; ++j) {
                cout << ' ';
            }
            cout << a << endl;
        } else {
            continue;
        }
        for (int i = 1; i < num - 1; ++i) {
            for (int j = 0; j < num - i - 1; ++j) {
                cout << ' ';
            }
            cout << a;
            for (int j = 0; j <= 2 * (i - 1); ++j) {
                cout << ' ';
            }
            cout << a << endl;
        }
        for (int i = 0; i < 2 * num - 1; ++i) {
            cout << a;
        }
        cout << endl;
    }
    return 0;
}

// E
Description
小明在做数据结构的作业，其中一题是给你一棵二叉树的前序遍历和中序遍历结果，要求你写出这棵二叉树的后序遍历结果。
Input
输入包含多组测试数据。每组输入包含两个字符串，分别表示二叉树的前序遍历和中序遍历结果。每个字符串由不重复的大写字母组成。字符串长度不超过1000。
Output
对于每组输入，输出对应的二叉树的后序遍历结果。

Sample Input
DBACEGF ABCDEFG
BCAD CBAD

Sample Output
ACBFGED
CDAB

#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

string xian, zhong, hou;

struct node {
    char _a;
    node* _left;
    node* _right;
    
    node(char data)
    :_a(data)
    ,_left(NULL)
    ,_right(NULL) {}
};

int c;

node* _find(int left, int right) {
    if (left > right) {
        return NULL;
    }
    int k = -1;
    for (int i = left; i < right; ++i) {
        if (zhong[i] == xian[c]) {
            k = i;
        }
    }
    if (k == -1) return NULL;
    node* root = new node(xian[c]);
    ++c;
    root->_left = _find(left, k);
    if (root->_left == NULL) {
        --c;
    }
    ++c;
    root->_right = _find(k + 1, right);
    if (root->_right == NULL) {
        --c;
    }
    return root;
}

void order(node* root) {
    if (root == NULL) {
        return;
    }
    order(root->_left);
    order(root->_right);
    cout << root->_a;
}

int main() {
    while (cin >> xian >> zhong) {
        hou = xian;
        c = 0;
        node* root = _find(0, int(xian.size()));
        order(root);
        cout << endl;
    }
    return 0;
}


// D
Description
给定一串由括号组成的字符串，请你判断这些括号是否一一匹配。

一个左括号“(”匹配一个右括号")”。
       
类似：“()”、"(())"，"()()"，“(()())”等都是匹配的。
       
而“(()”，"())"等都是不匹配的。
          
给定的字符串只包含左右括号和空格。类似于“()(    )( (  )          )”的输入是合法的，且这个字符串是匹配的。
          
Input
输入包含多组输入数据，需要处理到文件末尾。
          
每个测试样例占一行，只包含左右括号符号和空格。符号和空格的形成的字符串的最大长度不超过1000。
          
Output
对于每一个输入样例,如果括号完全匹配成功，输入"Yes"。否则输出"No"。
          
Sample Input
()()()()(()()()())
(          )
(   () )
(())))))))))()
)(

Sample Output
Yes
Yes
Yes
No
No
  
#include <iostream>
#include <cstdio>
using namespace std;

int main() {
    
    char s[100010];
flag:
    while (fgets(s, 100010, stdin)) {
        int count = 0;
        for (int i = 0; s[i]; ++i) {
            if (s[i] == '(') {
                ++count;
            } else if (s[i] == ')') {
                if (--count < 0) {
                    cout << "No" << endl;
                    goto flag;
                }
            }
        }
        if (count) {
            cout << "No" << endl;
        } else {
            cout << "Yes" << endl;
        }
    }
    return 0;
}


// C
  Description
  科大要建设美丽校园啦，而交给你的任务就是计算要买多少颗树。
  
  学校决定要在大小为N*M的空地里的多个区域种树(空地的左上角坐标为(1，1)，表示第1行第1列的空间)。
  
  并且给出多个需要种树的区域(该区域保证完全在上述空地内，不存在有超出给定空地的部分)。
  
  每次给定两个坐标(X1，Y1)、(X2，Y2)，表示左上角为(X1，Y1)，右下角为(X2，Y2)的需要种树的区域(包含端点的边界)。
  
  对于每一个面积为1的空间，如果已经有了树，则不需要重复种树，如果没有树，则需要种上一棵树。
  
  坐标(x，y)表示第x行第y列的空间。
  
  
  Input
  测试数据包含多组测试样例。
  
  对于每一组测试样例：
  
  输入的第一行为三个数 N，M，K(0 <= N，M，K <= 1000)，表示需要在 N*M 的空地里的 K 个区域种满树。
  
  接下来有 K 行，每行4个正整数 X1，Y1，X2，Y2(1 <= X1 <=X2 <= N，1 <= Y1  <= Y2 <= M)。
  
  当N=M=K=0时结束程序，不需要做任何输出。
  
  Output
  对于每个测试样例输出一个数字，表示树木的数量，占一行。
  
  Sample Input
  5 5 2
  1 1 3 3
  2 2 4 5
  0 0 0
  
  Sample Output
  17
  
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

bool arr[1010][1010];

int main() {
    
    int n, m, k;
    while (cin >> n >> m >> k && (n + m + k)) {
        memset(arr, 0, sizeof(arr));
        while (k--) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            for (int i = x1; i <= x2; ++i) {
                for (int j = y1; j <= y2; ++j) {
                    arr[i][j] = 1;
                }
            }
        }
        int count = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (arr[i][j] == 1) {
                    ++count;
                }
            }
        }
        cout << count << endl;
    }
    return 0;
}


// B
  Description
  好消息：小程的四级高分飘过啦！
  
  但是由于小程学英语太用心了，以至于他现在只会"One"、"Two"、"Three"..."Ten"，而不会阿拉伯数字了。
  
  为了让小程重新振作起来，我们要写一个程序来帮助他。
  
  Input
  输入数据有多组测试样例，你需要处理到文件末尾。
  
  每个测试样例为一行。
  
  测试样例输入仅包括One、Two、Three、Four、Five、Six、Seven、Eight、Nine、Ten、Zero。(首字母大写)
  
  Output
  对于每一个测试样例，输出一个对应的阿拉伯数字。
  Sample Input
  Seven
  Six
  Four
  
  Sample Output
  7
  6
  4
#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

char* arr[11] = {"Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten"};

int main() {
    string s;
    while (cin >> s) {
        for (int i = 0; i < 11; ++i) {
            if (string(arr[i]) == s) {
                cout << i << endl;
            }
        }
    }
    return 0;
}


// A
  Description
  Bob和Alice要进行决斗，他们约定谁输了，就女装一个星期，并把你邀请来当裁判。
  
  以下是他们的决斗规则：
  
  1.由计算机给定一组无序可重复的整数序列。
  
  2.Alice先抽出最小的数字。
  
  3.Bob再抽出最大的数字。
  
  4.抽出来的数字从序列中消失，两人轮流抽取，直至只剩下最后一个数字。
  
  如果剩下的这个数字是偶数，则Alice胜。如果是奇数，则Bob胜。
  
  你作为公平公正的裁判，能判断出究竟是Alice胜还是Bob胜吗？
  
  Input
  输入数据的的第一行是T（0 <= T <= 100），表示接下来的样例数目。
  
  对于每个样例，输入为一行：
  
  第一个数字为电脑给定的序列元素个数N（1 <= N <=10000），接下来N个数字为序列元素。
  
  Output
  对于每个测试样例，输出"Alice"或者"Bob"。
  
  如果Alice胜出，输出"Alice"。
  
  否则，输出"Bob"。
  
  
  
  Sample Input
  3
  5 1 2 3 4 5
  6 1 2 3 4 5 6
  4 6 1 4 5
  Sample Output
  Bob
  Alice
  Bob
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

int arr[10010];

int main(int argc, const char * argv[]) {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i) {
            scanf("%d", &arr[i]);
        }
        sort(arr, arr + n);
        if (arr[n / 2] % 2 == 0) {
            cout << "Alice" << endl;
        } else {
            cout << "Bob" << endl;
        }
    }
    return 0;
}
*/
