/* ## 解法：
 *
 *   1. 题目中有一个特别重要的条件：一次性把该染色的袜子都染了，而不是每天都染！
 *      该条件是解题的唯一关键。
 *
 *   2. 一次性染，也就是说，当染色工作结束后，每天穿的袜子颜色都应该相同。则题意
 *      化简为：n 只袜子，染色后，m 天每一天穿的袜子颜色都一样。
 *
 *   3. 如果有配对 `{a, b}`, `{b, c}`，则按照要求，到最终袜子 `a`、`b`、`c` 的颜
 *      色都应该相同。
 *
 *   4. 到这里解法已经很明晰了：
 *
 *      题目条件：染色后，所有的配对 `{li, ri}`，`li` 和 `ri` 的袜子颜色相同
 *
 *      推论条件：染色后，以袜子为点、袜子配对连边建无向图，则在同一个连通块的
 *                  每个节点颜色都相同
 *
 *   5. 答案：Σ(每个联通块内最少需要染多少节点才能使该连通块内所有节点同色)
 *          = Σ(每个联通块的节点数目 - 联通块内颜色最多的节点数目)
 *          = n - Σ(联通块内颜色最多的节点数目)
 */

#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

#define MAX_N 400005

struct Edge {
    int src;
    int dst;
    int weights;
} edge[MAX_N];

int n, m, k;
int edge_num = 0;
int family_count = 0;
int color[MAX_N], family[MAX_N], maxn[MAX_N], color_count[MAX_N];
bool visit[MAX_N];
vector<int> adj[MAX_N], adj2[MAX_N];
map< pair<int,int>, int > mapper;

void add_edge(int src, int dst, int weights) {
    edge_num ++;
    edge[edge_num].src = src;
    edge[edge_num].dst = dst;
    edge[edge_num].weights = weights;
}

int find_family(int node) {
    if (family[node] == node) {
        return node;
    } else {
        return family[node] = find_family(family[node]);
    }
}

void union_family(int src, int dst) {
    family[ find_family(src) ] = family[dst];
}

void dfs(int node) {
    visit[node] = true;
    adj2[ find_family(node) ].push_back(node);

    for(vector<int> :: iterator it = adj[node].begin(); it != adj[node].end(); it++) {
        if (not visit[ *it ]) {
            dfs(*it);
        }
    }
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &color[i]);
    }

    // 初始化并查集
    for(int i = 1; i <= n; i++) {
        family[i] = i;
    }

    for(int i = 1; i <= m; i++) {
        int src, dst;
        scanf("%d %d", &src, &dst);

        // 合并并查集
        if (find_family(src) != find_family(dst)) {
            union_family(src, dst);
        }

        adj[src].push_back(dst);
        adj[dst].push_back(src);
    }

    for (int i = 1; i <= n; i++) {
        if (not visit[i]) {
            dfs(find_family(i));
        }
    }

    int ans = n;

    for (int i = 1; i <= n; i++) {
        if (find_family(i) == i) {
            int tmp = 0;

            for(vector<int> :: iterator it = adj2[i].begin();
                it != adj2[i].end(); it++) {
                color_count[ color[ *it ] ] ++;

                tmp = max(tmp, color_count[ color[*it] ]);
            }

            for(vector<int> :: iterator it = adj2[i].begin();
                it != adj2[i].end(); it++) {
                color_count[ color[ *it ] ] --;
            }

            ans -= tmp;
        }
    }

    printf("%d\n", ans);

    return 0;
}
