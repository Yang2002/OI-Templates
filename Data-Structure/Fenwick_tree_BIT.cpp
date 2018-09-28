// Fenwick Tree a.k.a. Binary Indexed Tree
// Accepted on luogu P3374
// Remember to initialize n when using
#include<bits/stdc++.h>
const int maxn = 500020;
inline int lowbit(int x) {return x & (-x);}
int n, q;
struct Fenwick {
    int c[maxn] = {0};
    inline int sum(int x) {
        int ret = 0;
        while(x) ret += c[x], x -= lowbit(x);
        return ret;
    }
    inline void add(int x, int d) { 
        while(x <= n) c[x] += d, x += lowbit(x); 
    }
    inline int query(int x, int y) { 
        return sum(y) - sum(x - 1);
    }
} sol;
int main() {
    scanf("%d%d", &n, &q);
    for(int i = 1; i <= n; ++i) {
        int x; scanf("%d", &x);
        sol.add(i, x);
    }
    while(q--) {
        int opt, x, y;
        scanf("%d%d%d", &opt, &x, &y);
        if(opt == 1) sol.add(x, y);
        else printf("%d\n", sol.query(x, y));
    }
    return 0;
}
