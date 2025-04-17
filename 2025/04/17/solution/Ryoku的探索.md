显然基环树。玩样例会发现从每个点出发，最后环上的某条边会被忽略。当进入环会选择当前相邻两点其中一点其边 $p$ 更大，另一条边会被忽略。


```cpp 
#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;
using u64 = unsigned long long;

using i128 = __int128;
using u128 = unsigned __int128;

std::vector<std::vector<std::array<int, 3>>> e;

struct UnicyclicGraph {
    int DFN = 0, n, rt;
    std::vector<int> dfn, fa, s, vis;
    UnicyclicGraph() {}
    UnicyclicGraph(int _, int RT = 1) {
        init(_, RT);
    }
    void init(int _, int RT) {
        this->rt = RT;
        this->n = _;
        dfn.resize(n + 1);
        fa.resize(n + 1);
        vis.resize(n + 1);
    }
    void dfs(int u) {
        dfn[u] = ++DFN;
        for (auto [v, w, p] : e[u]) {
            if (!dfn[v]) {
                fa[v] = u;
                dfs(v);
            } else if (dfn[v] >= dfn[u]) {
                s.emplace_back(v);
                vis[v] = 1;
                while (v != u) {
                    vis[fa[v]] = 1;
                    s.emplace_back(fa[v]);
                    v = fa[v];
                }
            }
        }
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    i64 sum = 0;
    e.assign(n + 1, {});
    for (int i = 0; i < n; ++i) {
        int u, v, w, p;
        std::cin >> u >> v >> w >> p;
        sum += w;
        e[u].emplace_back(std::array {v, w, p});
        e[v].emplace_back(std::array {u, w, p});
    }

    UnicyclicGraph ug(n);
    ug.dfs(ug.rt);
    std::vector<i64> ans(n + 1);
    std::vector<int> vis(n + 1);
    for (auto i : ug.s) {
        std::vector<int> ord {i};
        std::vector<std::array<int, 2>> tord;

        auto dfs = [&](auto &&self, int u) -> void {
            vis[u] = 1;
            for (auto [v, w, p] : e[u]) {
                if (ug.vis[v] && v != i) {
                    tord.emplace_back(std::array {w, p});
                } else if (!vis[v]) {
                    ord.emplace_back(v);
                    self(self, v);
                }
            }
        };

        dfs(dfs, i);
        int w = tord[0][1] > tord[1][1] ? tord[1][0] : tord[0][0];
        for (auto j : ord) {
            ans[j] = sum - w;
        }
    }
    for (int i = 1; i <= n; ++i) {
        std::cout << ans[i] << "\n";
    }

    return 0;
}
```

