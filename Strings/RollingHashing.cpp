#include <bits/stdc++.h> // import everything in one shot
using namespace std;

#define rep(i, a, b) for (int i = a; i <= b; ++i)
typedef unsigned long long int ull;

const int MAXLEN = 1e6;

struct RH
{                                 // rolling hashing
    static const ull B = 127;     // base
    static const ull P = 1e9 + 7; // prime
    static ull pow[MAXLEN];

    static ull add(ull x, ull y) { return (x + y) % P; }
    static ull mul(ull x, ull y) { return (x * y) % P; }

    static void init()
    {
        pow[0] = 1;
        rep(i, 1, MAXLEN - 1) pow[i] = mul(B, pow[i - 1]);
    }

    vector<ull> h;
    int len;
    RH(string &s)
    {
        len = s.size();
        h.resize(len);
        h[0] = s[0] - 'a';
        rep(i, 1, len - 1) h[i] = add(mul(h[i - 1], B), s[i] - 'a');
    }

    ull hash(int i, int j)
    {
        if (i == 0)
            return h[j];
        return add(h[j], P - mul(h[i - 1], pow[j - i + 1]));
    }

    ull hash() { return h[len - 1]; }
    bool operator<(const RH &o) const { return len < o.len; }

    bool contains(RH &other)
    {
        if (other.len > len)
            return false;

        for (int i = 0; i <= len - other.len; i++)
        {
            if (hash(i, i + other.len - 1) == other.hash())
                return true;
        }
        return false;
    }
};
ull RH::pow[MAXLEN]; // necessary for the code to compile

int main()
{
    RH::init();
    string s1 = "an";
    string s2 = "cant";
    RH rh1(s1);
    RH rh2(s2);
    // cout << rh1.hash(0, 3) << endl;
    // cout << rh1.hash() << endl;

    // cout << rh2.hash(1, 4) << endl;
    // cout << rh2.hash(0, 4) << endl;
    // cout << rh2.hash() << endl;
    cout << rh2.contains(rh1) << endl;
    return 0;
}