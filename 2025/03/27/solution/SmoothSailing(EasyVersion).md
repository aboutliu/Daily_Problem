$q$ 很小，容易想到二分答案，$check \Rightarrow $ 首先预处理出来每个点离最近的 $volacno$ 的距离，然后对于每个 $mid$ 我们只能从出发点经过这些 $dis \ge mid$ 的点。那么如何判断是否完全围绕 $island$ 呢？你将所有从出发点能够抵达的合法点全部标记一下，再从 $island$ 出发，如果能够不经过标记点抵达边界即无法完全围绕，反之可以。

```cpp 
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;
using u64 = unsigned long long;

using i128 = __int128;
using u128 = unsigned __int128;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

 	int n, m, q;
 	std::cin >> n >> m >> q;

 	std::vector<std::string> s(n);
 	for (int i = 0; i < n; ++i) {
 		std::cin >> s[i];
 	}   

 	std::vector vis(n, std::vector<int>(m, 1E9));
 	std::queue<std::array<int, 2>> que;
 	int islandx, islandy;
 	for (int i = 0; i < n; ++i) {
 		for (int j = 0; j < m; ++j) {
 			if (s[i][j] == 'v') {
 				vis[i][j] = 0;
 				que.emplace(std::array {i, j});
 			} else if (s[i][j] == '#') {
 				islandx = i;
 				islandy = j;
 			}
 		}
 	}
 	while (!que.empty()) {
 		auto [x, y] = que.front();
 		que.pop();

 		for (auto [dx, dy] : {std::pair {-1, 0}, {1, 0}, {0, -1}, {0, 1}}) {
			int xx = x + dx, yy = y + dy;
			if (xx < 0 || xx >= n || yy < 0 || yy >= m || vis[xx][yy] <= vis[x][y] + 1) {
				continue;
			}
			vis[xx][yy] = vis[x][y] + 1;
			que.emplace(std::array {xx, yy});
		}
 	}

 	auto check = [&](int X, int sx, int sy) -> int {
 		if (vis[sx][sy] < X || s[sx][sy] == '#') {
 			return 0;
 		}
 		std::vector tvis(n, std::vector<int>(m));
 		std::queue<std::array<int, 2>> que;
 		que.emplace(std::array {sx, sy});
 		tvis[sx][sy] = 1;
 		while (!que.empty()) {
 			auto [x, y] = que.front();
 			que.pop();

 			for (auto [dx, dy] : {std::pair {-1, 0}, {1, 0}, {0, -1}, {0, 1}}) {
 				int xx = x + dx, yy = y + dy;
 				if (xx < 0 || xx >= n || yy < 0 || yy >= m || tvis[xx][yy] || vis[xx][yy] < X || s[xx][yy] == '#') {
 					continue;
 				}
 				tvis[xx][yy] = 1;
 				que.emplace(std::array {xx, yy});
 			}
 		}
 		std::vector islandvis(n, std::vector<int>(m));
 		que.emplace(std::array {islandx, islandy});
 		islandvis[islandx][islandy] = 1;
 		while (!que.empty()) {
 			auto [x, y] = que.front();
 			que.pop();

 			if (!x || x == n - 1 || !y || y == m - 1) {
 				return 0;
 			}

 			for (auto [dx, dy] : {std::pair {-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {1, 1}, {-1, 1}, {1, -1}}) {
 				int xx = x + dx, yy = y + dy;
 				if (xx < 0 || xx >= n || yy < 0 || yy >= m || tvis[xx][yy] || islandvis[xx][yy]) {
 					continue;
 				}
 				islandvis[xx][yy] = 1;
 				que.emplace(std::array {xx, yy});
 			}
 		}
 		return 1;
 	};
 	auto solve = [&](int x, int y) -> int {
 		int lo = 0, hi = n + m - 1, ans = 0;
 		while (lo <= hi) {
 			int mid = (lo + hi) / 2;
 			if (check(mid, x, y)) {
 				ans = mid;
 				lo = mid + 1;
 			} else {
 				hi = mid - 1;
 			}
 		}
 		return ans;
 	};

 	while (q--) {
 		int sx, sy;
 		std::cin >> sx >> sy;
 		sx--;
 		sy--;

 		int ans = solve(sx, sy);
 		std::cout << ans << "\n";
 	}

    return 0;
}
```

