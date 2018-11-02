/*
Heavy-Light Decomposition
Link: https://www.luogu.org/problemnew/show/P3384
Description: Turn a problem on tree into a problem on paths
Operations:
  1. Add v on every vertex on path from u to v
  2. Find the total sum of all vertices on path u->v
  3. Add all vertices in subtree of v value v
  4. Query the total sum of all vertices on subtree of v
  (q3 and q4 can be done without heavy light decomposition. 
   We can simply use DFS sequence)
Complexity: O(logn * ???) [O(n log^2 n) here as we use segment tree
*/


#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;
typedef long long ll;

template<typename T> void read(T &x){
    x = 0; int f = 1; char ch = getchar();
    while(!isdigit(ch) ) { if(ch == '-') f *= -1; ch = getchar();}
    while( isdigit(ch) ) {x = x * 10 + ch - 48; ch = getchar();}
    x *= f;
}

const int maxn = 100300;
int n, q, root, mod;
inline int addn(int _a, int _b) { return (_a + _b) - ((_a + _b >= mod) ? mod : 0);}
inline int muln(int _a, int _b) { return 1LL * _a * _b % mod; }
struct SegmentTree {
    #define lson (o << 1)
    #define rson (o << 1 | 1)
    private:
    int sum[maxn << 2], Add[maxn << 2];
    inline void pushup(int o) {sum[o] = addn(sum[lson], sum[rson]);}
    inline void pushdown(int o, int l, int r) {
        if(Add[o] == 0) return;
        int mid = (l + r) >> 1;
        Add[lson] = addn(Add[lson], Add[o]);
        Add[rson] = addn(Add[rson], Add[o]);
        sum[lson] = addn(sum[lson], muln(Add[o], mid - l + 1));
        sum[rson] = addn(sum[rson], muln(Add[o], r - mid));
        Add[o] = 0;
    }

    public:
    void Build(int o, int l, int r, int *arr) {
        Add[o] = 0;
        if(l == r) { sum[o] = arr[l] % mod; return; }
        int mid = (l + r) >> 1;
        Build(lson, l, mid, arr);
        Build(rson, mid + 1, r, arr);
        pushup(o);
    }

    void IntervalAdd (int o, int l, int r, int ql, int qr, int v) {
        if(ql <= l && r <= qr) {
            Add[o] = addn(Add[o], v); 
            sum[o] = addn(sum[o], muln(v, r - l + 1)); 
            return;
        }
        pushdown(o, l, r);
        int mid = (l + r) >> 1;
        if(ql <= mid) IntervalAdd(lson, l, mid, ql, qr, v);
        if(qr > mid) IntervalAdd(rson, mid + 1, r, ql, qr, v);
        pushup(o);
    }

    int Query(int o, int l, int r, int ql, int qr) {
        if(ql <= l && r <= qr) return sum[o];
        int mid = (l + r) >> 1, ans = 0;
        pushdown(o, l, r);
        if(ql <= mid) ans = addn(ans, Query(lson, l, mid, ql, qr));
        if(qr > mid) ans = addn(ans, Query(rson, mid + 1, r, ql, qr));
        return ans;
    }
} seq;

int head[maxn], nxt[maxn << 1], ecnt = 0;
int sz[maxn], fa[maxn], dep[maxn], son[maxn], top[maxn];
int dfn[maxn], tim[maxn], dfs_clock = 0;
int a[maxn], ar[maxn];
struct edge{
    int from, to;
    edge(int x = 0, int y = 0) :
        from(x), to(y) { }
} e[maxn << 1];
inline void addedge(int x, int y) {
    e[++ecnt] = edge(x, y);
    nxt[ecnt] = head[x];
    head[x] = ecnt;
}

void dfs1(int v, int fath, int depth) {
    fa[v] = fath, dep[v] = depth, sz[v] = 1;
    for(int i = head[v]; i ; i = nxt[i]) {
        if(e[i].to == fath) continue;
        dfs1(e[i].to, v, depth + 1);
        sz[v] += sz[e[i].to];
    }
}
void dfs2(int v, int fath, int tp) {
    tim[v] = ++dfs_clock;
    dfn[dfs_clock] = v;
    ar[dfs_clock] = a[v];
    top[v] = tp;
    int lar = 0;
    for(int i = head[v]; i ; i = nxt[i]) {
        int to = e[i].to;
        if(to == fath) continue;
        if(sz[to] > lar) lar = sz[to], son[v] = to;
    }
    if(!son[v]) return;
    dfs2(son[v], v, tp);
    for(int i = head[v]; i ; i = nxt[i]) {
        if(e[i].to == son[v] || e[i].to == fath) continue;
        dfs2(e[i].to, v, e[i].to);
    }
}

inline void mPath(int x, int y, int val) {
    while(top[x] != top[y]) {
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        seq.IntervalAdd(1, 1, n, tim[top[x]], tim[x], val);
        x = fa[top[x]];
    }
    if(dep[x] > dep[y]) swap(x, y);
    seq.IntervalAdd(1, 1, n, tim[x], tim[y], val);
}

inline int qPath(int x, int y) {
    int ans = 0;
    while(top[x] != top[y]) {
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
        ans = addn(ans, seq.Query(1, 1, n, tim[top[x]], tim[x]));
        x = fa[top[x]];
    }
    if(dep[x] > dep[y]) swap(x, y);
    ans = addn(ans, seq.Query(1, 1, n, tim[x], tim[y]));
    return ans;
}

inline void mSubtree(int v, int val) {
    seq.IntervalAdd(1, 1, n, tim[v], tim[v] + sz[v] - 1, val);
}

inline int qSubtree(int v) {
    return seq.Query(1, 1, n, tim[v], tim[v] + sz[v] - 1);
}

int main(){
    read(n), read(q), read(root), read(mod);
    for(int i = 1; i <= n; ++i) read(a[i]);
    for(int i = 1; i < n; ++i) {
        int x, y; 
        read(x), read(y);
        addedge(x, y);
        addedge(y, x);
    }
    dfs1(root, -1, 1);
    dfs2(root, -1, root);
    seq.Build(1, 1, n, ar);
    while(q--) {
        int opt, x, y, val;
        read(opt), read(x);
        switch(opt) {
            case 1: 
                read(y), read(val);
                mPath(x, y, val); 
                break;
            case 2: 
                read(y);
                printf("%d\n", qPath(x, y)); 
                break;
            case 3: 
                read(val); 
                mSubtree(x, val); 
                break;
            case 4: 
                printf("%d\n", qSubtree(x)); 
                break;
            assert(false);
        }
    }
    return 0;
}
