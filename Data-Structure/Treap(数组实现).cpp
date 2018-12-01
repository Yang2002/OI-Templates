// bzoj 3224

#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= n; ++i)
#define writeln(x) (write(x), putchar('\n'))
#define INF 0x7fffffff
using namespace std;
typedef long long ll;

template<typename T> void read(T &x){
    x = 0; int f = 1; char ch = getchar();
    while(!isdigit(ch) ) { if(ch == '-') f = -1; ch = getchar();}
    while( isdigit(ch) ) {x = x * 10 + ch - 48; ch = getchar();}
    x *= f;
}
template<typename T, typename... Args> void read(T& x, Args&... args)
{ read(x), read(args...); }
template<typename T> void write(T x) {
    if(x < 0) putchar('-'), write(-x);
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

const int maxn = 100200;


namespace Treap {
    int tot, root;
    struct node {
        int val, dat, cnt, sz;
        int lc, rc;
    } tr[maxn];
    inline int New(int val) {
        tr[++tot].val = val;
        tr[tot].cnt = tr[tot].sz = 1;
        tr[tot].dat = rand();
        return tot;
    }
    inline void Update(int p) { 
        tr[p].sz = tr[ tr[p].lc ].sz + tr[ tr[p].rc ].sz + tr[p].cnt; 
    }
    inline void lrot(int& p) {
        int q = tr[p].rc;
        tr[p].rc = tr[q].lc;
        tr[q].lc = p;
        p = q;
        Update(tr[p].lc), Update(p);
    }
    inline void rrot(int &p) {
        int q = tr[p].lc;
        tr[p].lc = tr[q].rc;
        tr[q].rc = p;
        p = q;
        Update(tr[p].rc), Update(p);
    }
    inline void Init() { 
        root = New(INF);
        tr[root].lc = New(-INF);
        Update(root);
    }
    inline void Insert(int x, int &p = root) {
        if(p == 0) { p = New(x); return; }
        if(tr[p].val == x) {
            tr[p].cnt++;
            Update(p);
            return;
        } else if(tr[p].val > x) {
            Insert(x, tr[p].lc);
            if(tr[p].dat < tr[tr[p].lc].dat) rrot(p);
        } else if(tr[p].val < x) {
            Insert(x, tr[p].rc);
            if(tr[p].dat < tr[tr[p].rc].dat) lrot(p);
        }
        Update(p);
    }

    inline void Remove(int x, int& p = root) {
        if(p == 0) return;
        if(tr[p].val == x) {
            if(tr[p].cnt > 1) { tr[p].cnt--, Update(p); return; }
            if(tr[p].lc || tr[p].rc) {
                if(tr[p].rc == 0 || tr[tr[p].lc].dat > tr[tr[p].rc].dat)
                    rrot(p), Remove(x, tr[p].rc);
                else lrot(p), Remove(x, tr[p].lc);
                Update(p);
            } else p = 0;
            return;
        }
        if(tr[p].val < x) Remove(x, tr[p].rc);
        else Remove(x, tr[p].lc);
        Update(p);
    }
    int small(int val, int p) {
        if(p == 0) return 0;
        if(val == tr[p].val) return tr[tr[p].lc].sz;
        else if(val < tr[p].val) return small(val, tr[p].lc);
        else return small(val, tr[p].rc) + tr[p].cnt + tr[tr[p].lc].sz;
    }

    int kthsmall(int rk, int p) { // k smallest
        if(p == 0) return INF;
        if(tr[tr[p].lc].sz >= rk) return kthsmall(rk, tr[p].lc);
        if(tr[tr[p].lc].sz + tr[p].cnt >= rk) return tr[p].val;
        return kthsmall(rk - tr[tr[p].lc].sz - tr[p].cnt, tr[p].rc);
    }


    inline int Rank(int x) { return small(x, root); }
    inline int Kth (int k) { return kthsmall(k + 1, root); }
    inline int Prev(int x) { return Kth(Rank(x) - 1); }
    inline int Next(int x) { return Kth(Rank(x + 1)); }
}

using namespace Treap;
int n;
int main() {
    srand(2333333);
    read(n), Init();
    while(n--) {
        int opt, x;
        read(opt, x);
        switch(opt) {
            case 1: Insert(x); break;
            case 2: Remove(x); break;
            case 3: writeln(Rank(x)); break;
            case 4: writeln(Kth(x)); break;
            case 5: writeln(Prev(x)); break;
            case 6: writeln(Next(x)); break;
        }
        // dfs_clock = 0;
        // dfs(root);
    }
    
    return 0;
}
