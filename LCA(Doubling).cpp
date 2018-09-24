// O(nlogn) Precalculate and O(log n) per query
// LCA::solve() is to test the algorithm
// Input format:
// n, q, root
// n-1 lines describes edges x <-> y
// q lines describes queries lca(x, y)
#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= (n); ++i)
using namespace std;
typedef long long ll;
const int maxn = 500020, maxm = 1000020;
int anc[maxn][30], root, dep[maxn], lg[maxn];
namespace adjlist{
    int n, m, ecnt = 0, head[maxn], nxt[maxm];
    struct edge{
        int from, to;
        edge(int x = 0, int y = 0) : from(x), to(y) {}
    } e[maxm];
    inline void init(int sz){
        memset(head, 0, sizeof(int) * (sz + 10));
        ecnt = 0;
    }
    inline void addedge(int x, int y){
        e[++ecnt] = edge(x, y);
        nxt[ecnt] = head[x];
        head[x] = ecnt;
    }
}

namespace LCA{
    using namespace adjlist;
    int LOG;                                                                           
    void dfs(int v, int fa, int depth){
        anc[v][0] = fa, dep[v] = depth;
        for(int i = 1; i <= LOG; ++i)
            anc[v][i] = anc[ anc[v][i-1] ][i-1];
        for(register int i = head[v] ; i ; i = nxt[i]) {
            if(e[i].to != fa) dfs(e[i].to, v, depth + 1);
        }
    }
    inline int LCA(int x, int y){
        if(dep[x] < dep[y]) swap(x, y);
        while(dep[x] > dep[y]) x = anc[x][ lg[dep[x] - dep[y]] ];
        if(x == y) return x;
        for(int i = lg[dep[x]]; i >= 0; --i) if(anc[x][i] != anc[y][i]) 
            x = anc[x][i], y = anc[y][i];
        return anc[x][0];
    }
    inline void init(int root){
        LOG = lg[n] + 1;
        dfs(root, root, 1);
    }
    inline void solve(){
        int rt, q;
        scanf("%d%d%d", &n, &q, &rt);
        adjlist::init(n);
        m = (n - 1) << 1;
        rep(i, n - 1) {
            int x, y; scanf("%d%d", &x, &y); 
            addedge(x, y), addedge(y, x);
        }
        init(rt);
        while(q--){
            int x, y; scanf("%d%d", &x, &y);
            printf("%d\n", LCA(x, y) );
        }
    }
}
inline void log_init(){
    for(register int i = 2; i <= 500000; ++i)
        lg[i] = lg[i - 1] + (1 << (lg[i-1] + 1) == i);
}
int main(){
    log_init();
    LCA::solve();
}
