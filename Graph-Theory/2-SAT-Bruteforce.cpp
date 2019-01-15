#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;
typedef long long ll;

const int MAXN = 1002000;
struct TwoSAT {
    int n;
    vector< vector<int> > G;
    vector<int> S;
    vector<bool> mark;
    int c;


    void init(int num) {
        this->n = num, c = 0;
        G.resize(n * 2 + 100);
        for(int i = 0; i < n * 2; ++i) G[i].clear();
        mark.resize(n * 2 + 100);
        fill(mark.begin(), mark.end(), 0);
        S.resize(n * 2 + 100);
    }

    bool dfs(int x) {
        if(mark[x ^ 1]) return false;
        if(mark[x]) return true;
        mark[x] = true;
        S[c++] = x;
        for(int i = 0; i < G[x].size(); ++i)
            if(!dfs(G[x][i])) return false;
        return true;
    }
    void add(int x, int xv, int y, int yv) {
        x = x * 2 + xv;
        y = y * 2 + yv;
        G[x ^ 1].push_back(y);
        G[y ^ 1].push_back(x);
    }
    bool solve() {
        for(int i = 0; i < n * 2; i += 2) {
            if(!mark[i] && !mark[i + 1]) {
                c = 0;
                if(!dfs(i)) {
                    while(c > 0) mark[S[--c]] = false;
                    if(!dfs(i + 1)) return false;
                }
            }
        }
        return true;
    }
};

int t, m;
int main() {
    scanf("%d%d", &t, &m);
    TwoSAT solver;
    solver.init(t);
    while(m--) {
        int a, va, b, vb;
        scanf("%d%d%d%d", &a, &va, &b, &vb);
        a--, b--;
        solver.add(a, va, b, vb);
    }
    bool ok = solver.solve();
    puts(ok ? "POSSIBLE" : "IMPOSSIBLE");
    if(ok) for(int i = 1; i < t * 2; i += 2) {
        printf("%d ", solver.mark[i] ? 1 : 0);
    }  
    
    return 0;
}
