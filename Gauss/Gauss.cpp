
#include "Gauss.hpp"

Gauss::Gauss(int sn, int sm, vector<vector<double>> MX) {
    N = sn;
    M = sm;

    G_Mx.resize(N);
    for (int i = 0; i < N; i++)
        G_Mx[i].resize(M);
    
    G_opy.resize(N);
    for (int i = 0; i < N; i++)
        G_opy[i].resize(M);
   
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            G_Mx[i][j] = MX[i][j];
        }
    }
    
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            G_opy[i][j] = MX[i][j];
        }
    }
 
        
    G_tuda();
}
void Gauss::proverka(){
    vector<double> res(N);
    
    for(int i=0;i<N;i++){
        for(int j=0;j<M-1;j++){
            res[i]+=G_opy[i][j]*x[j];
        }
    }
    cout << endl;
    
    
    for(int i=0;i<N;i++){
            cout << G_opy[i][N] << " = " << res[i] << endl;
    }
    

}

void Gauss::eq_printer(vector<double> x){
    for (int i=0; i<x.size(); i++) {
        cout << "x" << i << " = " << x[i]  << endl;
    }
    proverka();
}

void Gauss::print_mx() {
    cout << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cout << G_Mx[i][j] << "      ";
        }
        cout << endl;
    }
}

void Gauss::max_swap(int swapper){
    double max=-1;
    int num=0;
    int i=0;
    i+=swapper;
    for(i;i<N;i++){
        if(abs(max)<abs(G_Mx[i][swapper])){
            max = G_Mx[i][swapper];
            num = i;
        }
    }
    if(num>=0 && num!=0)
        swap(G_Mx[swapper],G_Mx[num]);
    print_mx();
    cout << "i = " <<  swapper << "  " << "j = " << num << endl;
}
void Gauss::G_tuda() {
    
    
    for(int k=0;k<N;k++)
    {
        max_swap(k);
        for (int i=k+1; i<N; i++)
        {
            double temp = G_Mx[i][k]/G_Mx[k][k];
            for (int j=k+1; j<=N; j++)
                G_Mx[i][j] -= G_Mx[k][j]*temp;
            G_Mx[i][k] = 0;
        }
    }
    //print_mx();
    G_obratno();
}

void Gauss::G_obratno() {
    
    x.resize(N);

    for (int i = N-1; i >= 0; i--)
    {
        x[i] = G_Mx[i][N];
        for (int j=i+1; j<N; j++)
        {
            x[i] -= G_Mx[i][j]*x[j];
        }

        x[i] = x[i]/G_Mx[i][i];
    }
    cout << endl;
 
    eq_printer(x);
  }

Gauss::~Gauss() {
    G_Mx.clear();
    x.clear();
}
