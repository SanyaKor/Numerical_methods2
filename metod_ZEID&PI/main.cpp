
#include <vector>
#include <iostream>

using namespace std;

void print_res(vector<double> res,double eps){
    cout << endl;
    for(int i = 0;i<res.size();i++){
        cout << "x_" << i << " = " << res[i] << endl;
    }
    cout << "Точность:" ;
    cout << eps << endl;
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

void proverka(vector<vector<double>> Mx,vector<double> res){
    
    vector<double> res1(Mx.size()-1);
    
    for(int i = 0; i<Mx.size(); i++){
        for(int j = 0; j<Mx[i].size()-1; j++){
            res1[i]+=Mx[i][j]*res[j];
        }
    }
    cout << endl;
    
    for(int i = 0; i<Mx.size() ; i++){
        cout << Mx[i][Mx.size()] << " = " << res1[i] << endl;
    }
  
}

void My_Matrix(vector<vector<double>> &Mx, int N){
    
    Mx.resize(N);
    for (int i = 0; i < N; i++)
        Mx[i].resize(N+1);
        
        Mx[0][0] = 16;
        Mx[0][1] = 0;
        Mx[0][2] = -2;
        Mx[0][3] = 7;

        Mx[1][0] = -1;
        Mx[1][1] = 14;
        Mx[1][2] = -3;
        Mx[1][3] = 2;

        Mx[2][0] = 5;
        Mx[2][1] = 5;
        Mx[2][2] = 26;
        Mx[2][3] = 7;

        Mx[3][0] = -2;
        Mx[3][1] = -6;
        Mx[3][2] = 9;
        Mx[3][3] = 24;

        Mx[0][4] = 50;
        Mx[1][4] = 2;
        Mx[2][4] = 273;
        Mx[3][4] = 111;
    
}

void one_iteration(vector<vector<double>> Mx,vector<double> &res, vector<double> rescopy,double &eps){
  
    for(int i = 0 ; i< Mx.size(); i++){
        rescopy[i]=0;
        rescopy[i]+=Mx[i][Mx.size()];
        for(int j = 0 ; j< Mx.size(); j++){
            if(i!=j)
                rescopy[i]-=Mx[i][j]*res[j];
        }
        rescopy[i]/=Mx[i][i];
    }
    
    double max = 0;
    for(int i = 0;i<res.size();i++){
        eps = rescopy[i] - res[i];
        if(abs(max)<abs(eps))
            max = eps;
    }
    eps = max;
    res = rescopy;
}

void one_zeid(vector<vector<double>> Mx,vector<double> &res, vector<double> rescopy,double &eps){
    int count = 0;
    int countbuff=0;
    for(int i = 0 ; i< Mx.size(); i++){
        rescopy[i]=0;
        rescopy[i]+=Mx[i][Mx.size()];
        count=countbuff;
        for(int j = 0 ; j< Mx.size(); j++){
            if(i!=j && count>0){
                rescopy[i]-=Mx[i][j]*rescopy[j];
                count--;
            }
            else if(i!=j && count==0)
                rescopy[i]-=Mx[i][j]*res[j];
            }
        countbuff++;
        
        rescopy[i]/=Mx[i][i];
    }
    
    double max = 0;
    for(int i = 0;i<res.size();i++){
        eps = rescopy[i] - res[i];
        if(abs(max)<abs(eps))
            max = eps;
    }
    eps = max;
    res = rescopy;
}

void Metod_PIZD(vector<vector<double>> Mx){
    
    double eps1 = 0.0001;
   
    
    vector<double> res;
    vector<double> rescopy(Mx.size());
    
    vector<vector<double>> Mcopy;
    Mcopy = Mx;
    double eps=1;
    
    for(int i=0;i<Mx.size();i++){
        res.push_back(0);
    }
    int count =0;
    res = rescopy;
    cout << "Метод простых итераций:" << endl;
        while(abs(eps1)<abs(eps)){
            one_iteration(Mx, res, rescopy, eps);
            print_res(res,eps);
            count++;
        }
    
    proverka(Mx, res);
    cout << "Колличетсво итераций:" << count <<endl;
    count =0;
    eps=1;
    for(int i=0;i<Mx.size();i++){
        res[i] = 0;
        rescopy[i] = 0;
    }
    cout << endl << endl;
    cout << "Метод Зейделя:" << endl;
    
    while(abs(eps1)<abs(eps)){
        one_zeid(Mx, res, rescopy, eps);
    
        print_res(res,eps);
        count++;
    }
    cout << endl;
    cout << "Колличетсво итераций:" << count <<endl;
    
    proverka(Mx, res);
    
    
  
    
}

int main(int argc, const char * argv[]) {
 
    int N=4;// число неизвестных
    
    vector<vector<double>> Mx;
    
    My_Matrix(Mx, N);
    print_Matrix(Mx);
    Metod_PIZD(Mx);
    return 0;
}
