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
struct LCAOp
{
    int neutro = INT_MIN;
    int operation(int a, int b) { return max(a, b); }
};
struct LCAModified
{
    int N, log2N;
    vector<vector<ii>> *g;
    vector<vi> A;
    vector<vi> Info;
    LCAOp op;
    vi D;

    int inline log2(int x) { return 31 - __builtin_clz(x); }
    void dfs(int u, int p)
    {
        A[u][0] = p;
        for (ii neig : (*g)[u])
        {
            if (D[neig.first] == -1)
            {
                D[neig.first] = D[u] + 1;
                Info[neig.first][0] = neig.second;
                dfs(neig.first, u);
            }
        }
    }
    ii lca(int u, int v)
    {

        if (D[u] < D[v])
            swap(u, v);
        ii raising = raise(u, D[u] - D[v]);
        u = raising.first;

        if (u == v)
            return raising;
        int info = op.neutro;
        invrep(exp, 0, log2N + 1)
        {
            if (A[u][exp] != A[v][exp])
            {
                info = op.operation(info, op.operation(Info[u][exp], Info[v][exp]));
                u = A[u][exp], v = A[v][exp];
            }
        }
        info = op.operation(info, Info[u][0]);
        info = op.operation(info, Info[v][0]);
        return make_pair(A[u][0], op.operation(raising.second, info));
    }
    ii raise(int u, int n)
    {
        int info = op.neutro;
        for (int i = 0; n; i++, n >>= 1)
        {
            if (n & 1)
            {
                info = op.operation(info, Info[u][i]);
                u = A[u][i];
            }
        }
        return make_pair(u, info);
    }

    int distance(int u, int v)
    {
        return D[u] + D[v] - 2 * D[lca(u, v).first];
    }
    LCAModified(vector<vector<ii>> &g_, int root, LCAOp &op)
    {
        g = &g_;
        N = g_.size();
        log2N = log2(N);
        D.assign(N, -1);
        A.assign(N, vi(log2N + 1, -1));
        Info.assign(N, vi(log2N + 1, -1));
        D[root] = 0;
        dfs(root, -1);
        rep(exp, 1, log2N + 1)
        {
            rep(u, 0, N)
            {
                int anc = A[u][exp - 1];
                A[u][exp] = (anc == -1 ? -1 : A[anc][exp - 1]);
                Info[u][exp] = (anc == -1 ? -1 : op.operation(Info[u][exp - 1], Info[anc][exp - 1]));
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
    return 0;
}