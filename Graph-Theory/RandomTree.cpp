// A naive template for generating a weighed tree (using dsu)
// Edit the constant MaxSize and MaxWeight when needed
const int MaxSize = 10;
const int MaxWeight = 30;
// The program will output the tree in the file "in.txt"
// The format is as follows:
// First line: sz -- The number of nodes in the tree
// 2 ~ n line: (from, to, weight) of each edge
// Change the Weighted constant into false if you don't need weight
const bool Weighted = true;

#include<bits/stdc++.h>
using namespace std;
struct dsu{
	static const int maxn = 100030;
	int fa[maxn], size;
	inline void init(int sz){
		size = sz;
		for(int i = 1; i <= size; ++i) fa[i] = i;
	}
	int find(int x){
		return fa[x] == x ? x : fa[x] = find(fa[x]);
	}
	void merge(int x, int y){
		x = find(x), y = find(y);
		if(x != y) fa[x] = y;
	}
} d1;
void randomtree(int size, bool weighed){
	d1.init(size);
	int cnt = 0;
	while(cnt < size - 1){
		int x = rand() % size + 1, y = rand() % size + 1, hx = d1.find(x), hy = d1.find(y);
		if(hx == hy) continue;
		else{
		    printf("%d %d", x, y);
            if (weighed) {
                int weight = rand() % MaxWeight + 1;
			    printf(" %d", weight);
            }
            putchar('\n');
			d1.merge(x, y);
			cnt++;
		}
	}
}
int main()
{
	freopen("in.txt", "w", stdout);
	srand(time(NULL));
	int sz = rand() % MaxSize + 1;
	printf("%d\n", sz);
	randomtree(sz, Weighted);
	putchar('\n');
	return 0;
}
