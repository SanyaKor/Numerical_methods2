
#include "Gauss.hpp"
#include <iostream>


void read_Matrix(int M,int N,vector<vector<double>> &Mx){
    
    Mx.resize(N);
        for (int i = 0; i < N; i++)
            Mx[i].resize(M);

    int el;
    for(int i = 0; i<N ; i++){
        for(int j = 0; j<M ; j++){
            cout << "Mx[" << i << "][" << j << "] = ";
            cin >> el;
            Mx[i][j] = el;
            }
    }
    cout << endl;
    for(int i = 0; i<N ; i++){
        for(int j = 0; j<M ; j++){
            cout << Mx[i][j] << "  ";
        }
        cout << endl;
    }
    cout << endl;
    
    Gauss G(N,M,Mx);
}

void cur_Matrix(int M,int N,vector<vector<double>> &Mx){
    Mx.resize(N);
        for (int i = 0; i < N; i++)
            Mx[i].resize(M);

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

 /* invert  Mx[0][1] = 1;
    Mx[0][2] = -3;
    //
    Mx[1][0] = 5;
    Mx[1][1] = 4;
    Mx[1][2] = 2;
    
    Mx[2][0] = 2;
    Mx[2][1] = -1;
    
    
    Mx[0][3] = 2;
    Mx[1][3] = 6;
    Mx[2][3] = 3;
  */
 /*
    
    Mx[0][0] = 2;
    Mx[0][1] = -1;
    
    Mx[1][0] = 5;
    Mx[1][1] = 4;
    Mx[1][2] = 2;
    
    Mx[2][1] = 1;
    Mx[2][2] = -3;
    
    
    Mx[0][3] = 3;
    Mx[1][3] = 6;
    Mx[2][3] = 2;
*/

    cout << endl;
    for(int i = 0; i<N ; i++){
        for(int j = 0; j<M ; j++){
            cout << Mx[i][j] << "  ";
        }
        cout << endl;
    }
    cout << endl;
    

    Gauss G(N,M,Mx);

    
    
}

int main(int argc, const char * argv[]) {
    
    
    
 //   int N=3;
 //   int M=4;
   
    int N=5;
    int M=6;
     
    
    vector<vector<double>> Mx;
    cur_Matrix(M,N,Mx);
    
    return 0;
}
