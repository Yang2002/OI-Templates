// BZOJ 3224

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
    int tot = 0;
    struct node {
        int val, dat, cnt, sz;
        node *lc, *rc;
        inline void Update() {
            sz = lc->sz + rc->sz + cnt;
        }
    } tr[maxn], *root, *Null;
    node* New(int val) {
        tr[++tot].val = val;
        tr[tot].dat = rand();
        tr[tot].cnt = tr[tot].sz = 1;
        tr[tot].lc = tr[tot].rc = Null;
        return tr + tot;
    }
    inline void lrot(node* &p) {
        node* q = p->rc;
        p->rc = q->lc;
        q->lc = p;
        p = q;
        p->lc->Update();
        p->Update();
    }
    inline void rrot(node* &p) {
        node* q = p->lc;
        p->lc = q->rc;
        q->rc = p;
        p = q;
        p->rc->Update();
        p->Update();
    }

    void Insert(int v, node* &p = root) {
        if(p == Null) { p = New(v); return ; }
        if(p->val == v) {
            p->cnt++;
            p->Update();
            return;
        } else if(p->val < v) {
            Insert(v, p->rc);
            if(p->rc->dat > p->dat) lrot(p);
        } else {
            Insert(v, p->lc);
            if(p->lc->dat > p->dat) rrot(p);
        }
        p->Update();
    }
    void Remove(int v, node* &p = root) {
        if(p == Null) return;
        if(p->val == v) {
            if(p->cnt > 1) {
                p->cnt--;
                p->Update();
            } else if(p->lc != Null || p->rc != Null) {
                if(p->rc == Null || p->lc->dat > p->rc->dat) {
                    rrot(p);
                    Remove(v, p->rc);
                } else lrot(p), Remove(v, p->lc);
                p->Update();
            } else p = Null;
            return;
        }
        if(p->val < v) Remove(v, p->rc);
        else Remove(v, p->lc);
        p->Update();
    }

    int small(int v, node* &p = root) {
        if(p == Null) return 0;
        if(p->val >  v) return small(v, p->lc);
        if(p->val == v) return p->lc->sz;
        return p->lc->sz + p->cnt + small(v, p->rc);
    }

    int kth_s(int k, node* &p = root) {
        if(p == Null) return INF;
        if(p->lc->sz >= k) return kth_s(k, p->lc);
        if(p->lc->sz + p->cnt >= k) return p->val;
        return kth_s(k - p->lc->sz - p->cnt, p->rc);
    }

    inline void Init() {
        Null = tr;
        root = New(-INF);
        root->rc = New(INF);
        root->Update();
    }

    inline int Rank(int x) { return small(x); }
    inline int Kth (int x) { return kth_s(x + 1); }
    inline int Prev(int x) { return Kth(Rank(x) - 1); }
    inline int Next(int x) { return Kth(Rank(x + 1)); }
}

using namespace Treap;
int n;
int main() {
    srand(19260817);
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
            default: return 0;
        }
    }

    return 0;
}
