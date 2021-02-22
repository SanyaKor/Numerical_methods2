//
//  main.cpp
//  metod_progonki
//
//  Created by Alex L on 03.02.2021.
//

#include <iostream>
#include <vector>

using namespace std;

void proverka(vector<double> res,vector<vector<double>> Mx){
    
    vector<double> res1(Mx.size());
    int k=res.size()-1;
    for(int i = 0; i<Mx.size() ; i++){
        k=res.size()-1;
        
        for(int j = 0; j<Mx[i].size(); j++){
            res1[i]+=Mx[i][j]*res[k];
            //cout << res[k] << endl;
            k--;
        }
    }
    cout << endl;
    
    for(int i = 0; i<Mx.size() ; i++){
        cout << Mx[i][Mx.size()] << " = " << res1[i] << endl;
    }
  
}

void Sweep(vector<double> a, vector<double> b,vector<double> c,vector<double> d,
           vector<vector<double>>Mx){
    
    vector<double> P;
    vector<double> Q;
    vector<double> res;
    
    
    P.push_back(-c[0]/b[0]);
    Q.push_back(d[0]/b[0]);
    
    double el=0;
    
    int i;
    
    for(i=1;i<a.size()-1;i++){
        el = b[i] + a[i]*P[i-1];
        P.push_back(-c[i]/el);
        Q.push_back((d[i] - a[i]*Q[i-1])/el);
    }
    
    Q.push_back((d[i] - a[i]*Q[i-1])/(b[i] + a[i]*P[i-1]));
    P.push_back(0);
    
    res.push_back(Q[i]);
    
    for(int i=0;i<P.size();i++){
        cout <<  "P" << i <<"   " <<P[i] << "   " << "Q" << i <<"   "<< Q[i] << endl;
    }
    int k = P.size()-2;
    for(i=1;i<P.size();i++){
        res.push_back(P[k]*res[i-1] + Q[k]);
        k--;
    }
    k=0;
    for(i = res.size()-1;i>=0;i--){
        cout << "x_" << k << " = " << res[i] << endl;
        k++;
    }
    proverka(res,Mx);
}

void read_Matrix(int N,vector<vector<double>> &Mx){
    
    Mx.resize(N);
        for (int i = 0; i < N; i++)
            Mx[i].resize(N+1);

    int el;
    for(int i = 0; i<N ; i++){
        for(int j = 0; j<N+1 ; j++){
            cout << "Mx[" << i << "][" << j << "] = ";
            cin >> el;
            Mx[i][j] = el;
            }
    }
    
    for(int i = 0; i<N ; i++){
        for(int j = 0; j<N+1 ; j++){
            cout << Mx[i][j] << "  ";
        }
        cout << endl;
    }
    cout << endl;
}


void print_Matrix(vector<vector<double>> Mx){
    
    for(int i = 0; i<Mx.size() ; i++){
        for(int j = 0; j<Mx[i].size(); j++){
            cout << Mx[i][j] << "  ";
        }
        cout << endl;
    }
    cout << endl;
    
}


void print_sys(vector<vector<double>> Mx){
    for(int i=0;i<Mx.size() ; i++){
        for(int j = 0; j<Mx[i].size(); j++){
            if(Mx[i][j]!=0 && j!= Mx[i].size()-1 )
                cout  << Mx[i][j] << "x_" << j << "  ";
            else if(j==Mx[i].size()-1)
                cout << " = " << Mx[i][j] ;
        }
        cout << endl;
    }
    cout << endl;
}

void My_Matrix(vector<vector<double>> &Mx, int N){
    
    Mx.resize(N);
        for (int i = 0; i < N; i++)
            Mx[i].resize(N+1);
  
    
    Mx[0][0] = -12;
    Mx[0][1] = -7;
    
    Mx[1][0] = -7;
    Mx[1][1] = -11;
    Mx[1][2] = -3;
    
    Mx[2][1] = -7;
    Mx[2][2] = 21;
    Mx[2][3] = -8;
    
    Mx[3][2] = 4;
    Mx[3][3] = -13;
    Mx[3][4] = 5;
    
    Mx[4][3] = -6;
    Mx[4][4] = 14;
    
    // D
    
    Mx[0][5] = -102;
    Mx[1][5] = -92;
    Mx[2][5] = -65;
    Mx[3][5] = 38;
    Mx[4][5] = -12;

    print_Matrix(Mx);
  
}


void get_koeff( vector<vector<double>> Mx){
    
    vector<double> a;
    vector<double> b;
    vector<double> c;
    vector<double> d;
  
    a.push_back(0);
    
    for(int i = 0; i<Mx.size()-1; i++){
        b.push_back(Mx[i][i]);
        c.push_back(Mx[i][i+1]);
        a.push_back(Mx[i+1][i]);
        d.push_back(Mx[i][Mx.size()]);
    }
    d.push_back(Mx[Mx.size()-1][Mx.size()]);
    b.push_back(Mx[Mx.size()-1][Mx.size()-1]);
    c.push_back(0);
    
    cout << endl;
    
    Sweep(a,b,c,d,Mx);
}

int main(int argc, const char * argv[]) {
    
    
    int N=5;// число неизвестных
    
    vector<vector<double>> Mx;
  
    My_Matrix(Mx,N);
    get_koeff(Mx);
  
    
return 0;
}
