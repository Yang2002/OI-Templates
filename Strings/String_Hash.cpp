/*
Link: Contest Hunter 1401 http://contest-hunter.org:83/
Use P = 13331 or 131 to make rp++
O(1) calculate Hash number of each substring
*/

#include <cstring>
#include <cstdio>
#include <cctype>


#define rep(i, n) for(int i = 1; i <= (n); ++i)
using namespace std;
typedef unsigned long long ll;

const int maxn = 1002000, P = 13331;
char s[maxn];

unsigned long long hsh[maxn], Ppow[maxn], len, q;
inline unsigned long long Hash(int l, int r) {
	return hsh[r] - hsh[l-1] * Ppow[r - l + 1];
}
int main() {
	scanf("%s%lld", s + 1, &q); len = strlen(s + 1);
	Ppow[0] = 1;
	for(int i = 1; i <= len; ++i) {
		Ppow[i] = Ppow[i - 1] * P;
		hsh[i] = hsh[i-1] * P + s[i] - 'a' + 1;
	}
	while(q--) {
		int l1, l2, r1, r2;
		scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
		ll h1 = Hash(l1, r1), h2 = Hash(l2, r2);
		printf("Hash(%d, %d) = %lld, Hash(%d, %d) = %lld\n", l1, r1, h1, l2, r2, h2);
		if(h1 == h2) puts("Yes");
		else puts("No");
	}
	return 0;
}





