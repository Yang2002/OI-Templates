// 1. Add x into the set: Add(x, 1)
// 2. Delete x from the set: Add(x, -1)
// 3. Find Kth smallest element in the set: Find_kth(k)
// 4. Find rank of x (number of numbers < x + 1): Find_rk(x)
// 5. Find the Previous element before x (< x and max): Prev(x)
// 6. Find the Next element after x (> x and min) : Next(x)
// All these operations can be processed in O(logn) complexity
// Warning: all numbers should be in [1, 20000000].

#include<bits/stdc++.h>
#define rep(i, n) for(int i = 1; i <= n; ++i)
using namespace std;
typedef long long ll;
const int maxn = 20000010;
int n;
template<typename T> void read(T &x){
    x = 0; int f = 1; char ch = getchar();
    while(!isdigit(ch) ) { if(ch == '-') f *= -1; ch = getchar();}
    while( isdigit(ch) ) {x = x * 10 + ch - 48; ch = getchar();}
    x *= f;
}
template <typename T>
void write(T x){
	 if (x < 0) putchar('-'),x = ~x + 1;
	 if (x > 9) write(x / 10);
	 putchar( x % 10 + '0');
}
template <typename T> inline void writeln(T x) { write(x), putchar('\n'); }


struct Fenwick {
    #define lowbit(x) (x & (-x))
    private:
    int c[maxn + 100];

    public:
    inline void Add(int x, int v) {
        for(; x <= maxn; x += lowbit(x))
            c[x] += v;
    }
    inline int Find_kth(int k) { // kth smallest
        int ans = 0, cnt = 0, i;
        for(i = 26; i >= 0; --i) {
            ans += 1 << i;
            if(ans >= maxn || c[ans] + cnt >= k) ans -= 1 << i;
            else cnt += c[ans];
        }
        return ans + 1;
    }
    inline int Find_rk(int x) {
        int ret = 0; x--;
        for(; x; x -= lowbit(x))
            ret += c[x];
        return ret + 1;
    }
    inline int Prev(int x) { return Find_kth(Find_rk(x) - 1);}
    inline int Next(int x) { return Find_kth(Find_rk(x + 1));}
} t;
int main(){
    int q; read(q);
    while(q--) {
        int opt, x; read(opt), read(x);
        switch (opt) {
            case 1: t.Add(x, 1); break;
            case 2: t.Add(x, -1); break;
            case 3: writeln(t.Find_rk(x)); break;
            case 4: writeln(t.Find_kth(x)); break;
            case 5: writeln(t.Prev(x)); break;
            case 6: writeln(t.Next(x)); break;
        }
    }
}
