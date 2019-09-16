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

struct LCA
{
    int N, log2N;
    vector<vi> *g;
    vector<vi> A;
    vi D;
    int inline log2(int x) { return 31 - __builtin_clz(x); }
    void dfs(int u, int p)
    {
        A[u][0] = p;
        for (int neig : (*g)[u])
        {
            if (D[neig] == -1)
            {
                D[neig] = D[u] + 1;
                dfs(neig, u);
            }
        }
    }
    int lca(int u, int v)
    {

        if (D[u] < D[v])
            swap(u, v);
        u = raise(u, D[u] - D[v]);

        if (u == v)
            return u;

        invrep(exp, 0, log2N + 1)
        {
            if (A[u][exp] != A[v][exp])
                u = A[u][exp], v = A[v][exp];
        }
        return A[u][0];
    }
    int raise(int u, int n)
    {
        for (int i = 0; n; i++, n >>= 1)
            if (n & 1)
                u = A[u][i];
        return u;
    }
    int distance(int u, int v)
    {
        return D[u] + D[v] - 2 * D[lca(u, v)];
    }
    LCA(vector<vi> &g_, int root)
    {
        g = &g_;
        N = g_.size();
        log2N = log2(N);
        D.assign(N, -1);
        A.assign(N, vi(log2N + 1, -1));
        D[root] = 0;
        dfs(root, -1);
        rep(exp, 1, log2N + 1)
        {
            rep(u, 0, N)
            {
                int anc = A[u][exp - 1];
                A[u][exp] = (anc == -1 ? -1 : A[anc][exp - 1]);
            }
        }
    }
};

int main()
{
    // OPTIONAL: for faster input/output (only if using cin/cout)
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T, N, Q, conns, v, w;
    cin >> T;
    rep(t, 0, T)
    {
        vector<vi> g;
        cin >> N;
        g.resize(N);
        rep(i, 0, N)
        {
            cin >> conns;
            rep(j, 0, conns)
            {
                cin >> v;
                v--;
                g[i].push_back(v);
                g[v].push_back(i);
            }
        }

        LCA lca = LCA(g, 0);
        cout << "Case " << t + 1 << ":" << endl;
        cin >> Q;
        rep(i, 0, Q)
        {

            cin >> v >> w;
            v--;
            w--;
            cout << lca.lca(v, w) + 1 << endl;
        }
    }
    return 0;
}