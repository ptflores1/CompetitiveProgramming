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

struct Kosaraju
{
    vector<vi> inverse_g;
    vector<vi> g;
    vector<vi> SCCs;
    stack<int> s;
    vi visited;
    void dfs1(int i)
    {
        if (visited[i])
            return;
        visited[i] = 1;
        for (int neig : g[i])
            dfs1(neig);
        s.push(i);
    }

    void dfs2(int i)
    {
        if (visited[i])
            return;
        visited[i] = 1;
        for (int neig : inverse_g[i])
            dfs2(neig);

        SCCs.back().push_back(i);
    }

    Kosaraju(vector<vi> &g_)
    {
        g = g_;
        inverse_g.resize(g_.size());

        rep(i, 0, g.size())
        {
            for (int v : g[i])
                inverse_g[v].push_back(i);
        }
        visited.assign(g.size(), 0);

        rep(i, 0, g.size())
        {
            dfs1(i);
        }

        visited.assign(g.size(), 0);

        while (!s.empty())
        {
            if (visited[s.top()])
            {
                s.pop();
                continue;
            }
            SCCs.push_back(vi());
            dfs2(s.top());
            s.pop();
        }
    }
};

int main()
{
    // OPTIONAL: for faster input/output (only if using cin/cout)
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int N, M, u, v;
    cin >> N >> M;
    vector<vi> g(N);
    rep(i, 0, M)
    {
        cin >> u >> v;
        g[u].push_back(v);
    }

    cout << "Grafo:" << endl;

    rep(i, 0, g.size())
    {
        cout << i << " -> ";
        for (int v : g[i])
            cout << v << " ";

        cout << endl;
    }

    Kosaraju sccs = Kosaraju(g);
    rep(i, 0, sccs.SCCs.size())
    {
        rep(j, 0, sccs.SCCs[i].size())
        {
            cout << sccs.SCCs[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}