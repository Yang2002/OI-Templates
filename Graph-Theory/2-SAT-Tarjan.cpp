#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;
typedef long long ll;

struct TwoSAT {
    int n, sz, dfs_clock, scc_cnt;
    vector< vector<int> > G;
    vector<int> dfn, low, sccno, ans;

    TwoSAT(int size) {
        this->n = size * 2;
        this->sz = size;
        G.resize(n + 22);
        dfn.resize(n + 22);
        low.resize(n + 22);
        sccno.resize(n + 22);
        dfs_clock = scc_cnt = 0;
    }
    inline void Add(int x, bool xv, int y, bool yv) { // x==xv || y==yv
        G[x + (!xv) * sz].push_back(y + yv * sz);
        G[y + (!yv) * sz].push_back(x + xv * sz);
    }

    stack<int> S;
    void Tarjan(int v) {
        low[v] = dfn[v] = ++dfs_clock;
        S.push(v);
        for(auto u : G[v]) {
            if(!dfn[u]) {
                Tarjan(u);
                low[v] = min(low[v], low[u]);
            } else if(!sccno[u])
                low[v] = min(low[v], dfn[u]);
        }
        if(low[v] == dfn[v]) {
            scc_cnt++;
            for(;;) {
                int p = S.top(); S.pop();
                sccno[p] = scc_cnt;
                if(p == v) break;
            }
        }
    }

    bool solve() {
        for(int i = 1; i <= n; ++i)
            if(!dfn[i]) Tarjan(i);
        for(int i = 1; i <= sz; ++i)
            if(sccno[i] == sccno[i + sz]) 
                return false;
        for(int i = 1; i <= sz; ++i)
            ans.push_back(sccno[i + sz] < sccno[i]);// Pay attention to '<'
        return true; 
    }
};

int n, m;
int main() {
    scanf("%d%d", &n, &m);
    TwoSAT solver(n);
    while(m--) {
        int a, va, b, vb;
        scanf("%d%d%d%d", &a, &va, &b, &vb);
        solver.Add(a, va, b, vb);
    }
    bool ok = solver.solve();
    puts(ok ? "POSSIBLE" : "IMPOSSIBLE");
    for(auto v : solver.ans) printf("%d ", v);
    
    return 0;
}
