#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cmath>
using namespace std;
struct SparseTable
{
    vector<vector<int>> ST;
    vector<int> power2;
    int n;

    SparseTable(vector<int> &v)
    {
        n = v.size();
        power2.resize(24);
        power2[0] = 1;
        for (int i = 1; i < 24; i++)
            power2[i] = 2 * power2[i - 1];
        int power = searchPower(n);
        ST.resize(power + 1, vector<int>(n));
        for (int i = 0; i < n; i++)
        {
            ST[0][i] = v[i];
        }
        for (int i = 1; i <= power; i++)
        {
            for (int j = 0; j < n - power2[i - 1]; j++)
            {
                ST[i][j] = max(ST[i - 1][j], ST[i - 1][j + power2[i - 1]]);
            }
        }
    }

    int searchPower(int n)
    {
        int l = 0, r = 23;
        for (int m = (l + r) / 2; l != r; m = (l + r) / 2)
        {
            if (power2[m] <= n)
                l = m + 1;
            else
                r = m;
        }
        return l;
    }

    int RMQ(int x, int y)
    {
        int distance = y - x + 1;
        int power = searchPower(distance);
        return max(ST[power - 1][x], ST[power - 1][y - power2[power - 1] + 1]);
    }
};
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }
    SparseTable ST(v);
    int q;
    cin >> q;
    while (q--)
    {
        int a, b;
        cin >> a >> b;
        // cout << a << b << endl;
        cout << ST.RMQ(a, b) << endl;
    }
    return 0;
}
