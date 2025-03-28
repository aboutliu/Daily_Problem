提供一种构造方法，首先一个为 $1$ 的边 $x$（这条边一直不变），然后构造另一条 $max(d)-1$ 的边 $y$，剩下的构造成一条边 $z$。

如果长度 $d_i < x + y$ 那么从 $z$ 添加一些过来，反之从 $x$ 删去一些到 $z$ 。

时间复杂度 $O(nq)$ 。 

```cpp 
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;
using u64 = unsigned long long;

using i128 = __int128;
using u128 = unsigned __int128;

void solve() {
	int n, q;
	std::cin >> n >> q;

	std::vector<int> d(q);
	for (int i = 0; i < q; ++i) {
		std::cin >> d[i];
	}

	int max = *max_element(d.begin(), d.end());
	std::vector<int> fa(n + 1), son(n + 1), dep(n + 1);
	dep[1] = 1;
	dep[2] = 2;
	fa[2] = 1;
	int f = 1;
	std::cout << "1 2\n";
	for (int i = 3, j = max - 1; j > 0; ++i, --j) {
		std::cout << i << " " << f << "\n";
		dep[i] = dep[f] + 1;
		fa[i] = f;
		f = i;
	}
	int tf = 1;
	for (int i = f + 1; i <= n; ++i) {
		std::cout << tf << " " << i << "\n";
		dep[i] = dep[tf] + 1;
		fa[i] = tf;
		tf = i;
	}

	int now = max;
	// std::cerr << f << " <-> " << tf << "\n";
	for (int i = 0; i < q; ++i) {
		if (now == d[i]) {
			std::cout << "-1 -1 -1\n";
			continue;
		}
		if (now > d[i]) {
			int Tf = fa[f];
			std::vector<int> ord {f};
			while (now - 1 > d[i]) {
				f = fa[f];
				Tf = fa[f];
				ord.emplace_back(f);
				now--;
				// std::cerr << f << " " << now - 1 << " <-\n";
			}
			std::cout << f << " " << fa[f] << " " << tf << "\n";
			now--;
			f = Tf;
			while (!ord.empty()) {
				auto u = ord.back();
				ord.pop_back();

				fa[u] = tf;
				dep[u] = dep[tf] + 1;
				tf = u;
			}
		} else {
			int Tf = fa[tf];
			std::vector<int> ord {tf};
			while (now + 1 < d[i]) {
				tf = fa[tf];
				Tf = fa[tf];
				ord.emplace_back(tf);
				now++;
			}
			std::cout << tf << " " << fa[tf] << " " << f << "\n";
			now++;
			tf = Tf;
			while (!ord.empty()) {
				auto u = ord.back();
				ord.pop_back();
				
				fa[u] = f;
				dep[u] = dep[f] + 1;
				f = u;
			}
		}
	}
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
```

