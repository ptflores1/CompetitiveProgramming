// https://github.com/PabloMessina/Competitive-Programming-Material/blob/master/Codejam_template.cpp
#pragma GCC optimize("Ofast") // OPTIONAL: for faster execution
#include <bits/stdc++.h>      // import everything in one shot
using namespace std;
// defines
#define rep(i, a, b) for (int i = a; i < b; ++i)
#define invrep(i, a, b) for (int i = b - 1; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
// typedefs
typedef unsigned int uint;
typedef unsigned long long int ull;
typedef long long int ll;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef tuple<int, int, int> iii;
// -------------------------------
struct Edge
{
    int u, v, cost;
    bool operator<(const Edge &o) const { return cost < o.cost; }
};

struct UnionFind
{
    vector<int> p, rank;
    UnionFind(int n)
    {
        rank.assign(n, 0);
        p.resize(n);
        rep(i, 0, n - 1) p[i] = i;
    }
    int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
    bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
    void unionSet(int i, int j)
    {
        if (!isSameSet(i, j))
        {
            int x = findSet(i), y = findSet(j);
            if (rank[x] > rank[y])
            {
                p[y] = x;
            }
            else
            {
                p[x] = y;
                if (rank[x] == rank[y])
                    rank[y]++;
            }
        }
    }
};
int find_mst(int n_nodes, vector<Edge> &edges, vector<vector<ii>> &mst)
{
    sort(edges.begin(), edges.end());
    UnionFind uf(n_nodes);
    mst.assign(n_nodes, vector<ii>());
    int mstcost = 0;
    int count = 1;
    for (auto &e : edges)
    {
        int u = e.u, v = e.v, cost = e.cost;
        if (!uf.isSameSet(u, v))
        {
            mstcost += cost;
            uf.unionSet(u, v);
            mst[u].emplace_back(v, cost);
            mst[v].emplace_back(u, cost);
            if (++count == n_nodes)
                break;
        }
    }
    return mstcost;
}
int main()
{
    // OPTIONAL: for faster input/output (only if using cin/cout)
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    return 0;
}