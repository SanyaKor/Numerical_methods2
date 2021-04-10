#include <iostream>
#include "vector"
#include "math.h"
using namespace std;


void print_Mx(vector<vector<long double>> Mx){
    cout << endl;
    for (int i = 0; i < Mx.size(); i++){
        for (int j = 0; j < Mx[i].size(); j++)
            cout << Mx[i][j] << " ";
        cout << endl;
  }
    cout << endl;
}


void My_mx(int N,vector<vector<long double>> &Mx){
    
    Mx.resize(N);
    for (int i = 0; i < N; i++)
        Mx[i].resize(N);
    
    Mx[0][0] = -4;
    Mx[0][1] = 1;
    Mx[0][2] = -7;
    
    Mx[1][0] = 1;
    Mx[1][1] = 9;
    Mx[1][2] = 1;
    
    Mx[2][0] = -7;
    Mx[2][1] = 1;
    Mx[2][2] = 7;
    
    print_Mx(Mx);
}


long double phi_func(vector<vector<long double>> Mx,int i, int j){
    long double phi = 0;
    
    phi = 0.5*atan(2*Mx[i][j]/(Mx[i][i] - Mx[j][j]));
    
    return phi;
}

vector<vector< long double>> Jacobian(int N,int i,int j,long double phi){
    vector<vector<long double>> res;
    
    res.resize(N);
    for (int i = 0; i < N; i++)
        res[i].resize(N);
    
    for (int i = 0; i < N; i++)
        res[i][i]=1;
    
    res[i][j] = -sin(phi);
    res[j][i] = sin(phi);
    res[i][i] = cos(phi);
    res[j][j] = cos(phi);
    
    
    return res;
}

void T(vector<vector<long double>> &a){
      long double t;
        for(int i = 0; i < a.size(); ++i)
        {
            for(int j = i; j < a.size(); ++j)
            {
                t = a[i][j];
                a[i][j] = a[j][i];
                a[j][i] = t;
            }
        }
}




void Mx_multiplication(vector<vector< long double>> a,vector<vector< long double>> b,vector<vector< long double>> &res){
    
    
    
    for (int i = 0; i < a.size(); i++)
    {
      for (int j = 0; j < b[i].size(); j++)
      {
        res[i][j] = 0;
        for (int k = 0; k < a[i].size(); k++)
          res[i][j] += a[i][k] * b[k][j];
      }
    }
    
}

void proverka(vector<vector<long double>> Mcopy,vector<vector<long double>> H,vector<vector<long double>> Mx){
    
    
    vector<long double> buf1(3);
    vector<long double> buf2(3);
    
    
    for(int k=0;k<Mx.size();k++){
        cout << "A * v_" << k <<  " = (";
        for(int i=0;i<Mcopy.size();i++){
            buf1[i]=0;
            for(int j=0;j<Mcopy.size();j++){
                buf1[i]+=Mcopy[i][j]*H[j][k];
        }
            cout  << buf1[i] << "  " ;
        }
        cout << ")T" << endl;
        cout << "l_" << k << " * v_" << k << " = (";
        
        for(int i=0;i<Mx.size();i++){
            buf2[i]=Mx[k][k]*H[i][k];
            cout   << buf2[i] << "  ";
        }
        cout <<  ")T" << endl << endl;
    }
}

bool one_iteration(vector<vector< long double>> &Mx, long double eps,vector<vector< long double>> &H){
    
    long double max=0;
    long double phi=0;
    vector<vector< long double>> j;
    vector<vector< long double>> res;
    
    res.resize(Mx.size());
    for (int i = 0; i < Mx.size(); i++)
        res[i].resize(Mx.size());
    
    
    int i1=0,j1=0;
    for(int i=0;i<Mx.size();i++){
        for(int j=i+1;j<Mx.size();j++){
            if(abs(max)<abs(Mx[i][j])){
                max = Mx[i][j];
                i1 = i;
                j1 = j;
            }
        }
    }
    if(abs(max)<eps)
        return 1;
    
    phi = phi_func(Mx, i1, j1);
    j = Jacobian(Mx.size(), i1, j1, phi);
    Mx_multiplication(H, j, H);
    T(j);
    Mx_multiplication(j, Mx, res);
    T(j);
    Mx_multiplication(res, j, res);
    Mx = res;
    
    return 0;
}


void Jacobi(vector<vector< long double>> Mx){
    
    long double eps = 0.001;
    
    vector<vector<long double>>Mcopy;
    vector<vector<long double>> H;
   
    Mcopy =  Mx;
    
    H.resize(Mx.size());
    for (int i = 0; i < Mx.size(); i++)
        H[i].resize(Mx.size());
    
    
    for(int i=0;i<Mx.size();i++)
        H[i][i]=1;
    
    while(!one_iteration(Mx, eps,H)){
    }
    for(int i=0;i<Mx.size();i++){
        cout << "l_" << i << " = " << Mx[i][i] << endl;
    }
    cout << endl;
    
    for(int i=0;i<H.size();i++){
        cout << "v_" << i << " = " << "(" << H[0][i] << ", " << H[1][i] << ", " << H[2][i] << ")T" << endl ;
    }
    cout << endl;

    proverka(Mcopy, H,Mx);
    cout << endl;
}




int main()
{
    vector<vector<long double>> a;
    
    My_mx(3,a);
    Jacobi(a);
    
    
    return 0;
}
