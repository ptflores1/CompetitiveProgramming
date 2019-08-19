#include <bits/stdc++.h> // import everything in one shot

using namespace std;

int bit(int i, int mask)
{
    return mask & (1 << i);
}

int setbit(int i, int mask)
{
    mask |= (1 << i);
    return mask;
}

int unsetbit(int i, int mask)
{
    mask &= (~(1 << i));
    return mask;
}

int togglebit(int i, int mask)
{
    mask ^= (1 << i);
    return mask;
}

int count(int mask)
{
    int count = 0;
    while (mask)
    {
        mask &= (mask - 1);
        count++;
    }
    return count;
}

int main()
{
    int mask = 7;
    bitset<3> x1(mask);
    cout << x1 << endl;

    cout << "bit 1" << endl;
    cout << bit(1, mask) << endl
         << endl;

    cout << "count" << endl;
    cout << count(mask) << endl
         << endl;

    mask = 6;
    bitset<3> x2(mask);
    cout << "set 0" << endl;
    cout << x2 << endl;
    mask = setbit(0, mask);
    bitset<3> x3(mask);
    cout << x3 << endl
         << endl;

    cout << "unset 2" << endl;
    cout << x3 << endl;
    mask = unsetbit(2, mask);
    bitset<3> x4(mask);
    cout << x4 << endl
         << endl;

    cout << "toggle 1" << endl;
    mask = 7;
    bitset<3> x5(mask);
    cout << x5 << endl;

    mask = togglebit(1, mask);
    bitset<3> x6(mask);
    cout << x6 << endl;

    mask = togglebit(1, mask);
    bitset<3> x7(mask);
    cout << x7 << endl;

    return 0;
}