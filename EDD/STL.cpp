#include <bits/stdc++.h>	
using namespace std;
typedef long long ll;								//ll funciona como long long

struct SegmentTreeLazy{
													//Todos los push son para empujar updates
    vector<ll>ST;									//Arbol
    vector<ll>UPD;									//Arbol de updates
    int n;											//largo del arreglo inicial
    ll neutro1, neutro2;							//valores neutros
    ll mergeThem(ll a, ll b){						//funcion de mezcla
        return a+b;
    }
    void init(int i, int l, int r, vector<ll>&arr){	//inicializa el segment tree
        if (l==r){									//caso bacan
            ST[i]=arr[l];
            return;
        }
        init(2*i, l, (l+r)/2, arr);					//Casos no bacanes
        init(2*i+1, (l+r)/2+1, r, arr);
        ST[i]=mergeThem(ST[2*i], ST[2*i+1]);
    }
    SegmentTreeLazy(vector<ll>&arr){				//constructor
        neutro2=0LL;
        neutro1=0LL;
        n=arr.size();
        ST.resize(4*n+5, 0LL);
        UPD.resize(4*n+5, neutro2);
        init(1, 0, n-1, arr);
    }
    void update(ll &pos, ll val){					//update para el pusheo
        pos+=val;
    }
    void push(int i, int l, int r){					//funcion de pusheo
        update(ST[i], UPD[i]);
        if (l!=r){
            update(UPD[2*i], UPD[i]);
            update(UPD[2*i+1], UPD[i]);
        }
        UPD[i]=neutro2;
    }
    void update(int i, int l, int r, int a, int b, ll val){	//update el rango [a, b] con val
        if (l>b or r<a){									//Caso fuera
            push(i, l, r);
            return;
        }
        if (a<=l && r<=b){									//Caso dentro
            update(UPD[i], val);
            push(i, l, r);
            return;
        }
        push(i, l, r);										//Caso interseccion
        update(2*i, l, (l+r)/2, a, b, val);
        update(2*i+1, (l+r)/2+1, r, a, b, val);
        ST[i]=mergeThem(ST[2*i], ST[2*i+1]);
    }
    void update(int a, int b, ll valor){					//update simbolicamente publico
        if (a>b){											//Caso ciclico
            update(1, 0, n-1, 0, b, valor);
            update(1, 0, n-1, a, n-1, valor);
        }
        else												//Caso no ciclico
            update(1, 0, n-1, a, b, valor);
    }
    ll get(int i, int l, int r, int a, int b){				//responder queries	
        if (a>r or l>b)										//Caso fuera
            return neutro1;
        push(i, l, r);
        if (a<=l and r<=b)									//Caso dentro
            return ST[i];
        return mergeThem(get(2*i, l, (l+r)/2, a, b), get(2*i+1, (l+r)/2+1, r, a, b));	//Caso interseccion
    }
    ll get(int a, int b){									//Responder queries simbolicamente publico
        if (a>b)											//Caso ciclico
            return mergeThem(get(1, 0, n-1, 0, b), get(1, 0, n-1, a, n-1));
        return get(1, 0, n-1, a, b);						//Caso no ciclico
    }
};

int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int t;
    cin >> t;
    while(t--){
        int n, u;
        cin >> n >> u;
        vector<ll>val(n);
        SegmentTreeLazy STL(val);
        while(u--){
            int a, b;
            ll c;
            cin >> a >> b >> c;
            STL.update(a, b, c);
        }
        int q;
        cin >> q;
        while(q--){
            int a;
            cin >> a;
            cout << STL.get(a, a) << "\n";
        }
    }
    return 0;
}
