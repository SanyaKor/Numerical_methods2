#include "Gauss.hpp"
#include <iostream>

long double N_sqrt(long double x,long double n){
    
    if(x<0){
        return -pow((-x),(1/n));
    }
    else
        return pow(x,(1/n));
}


void ffunc(vector<double> x,vector<vector<double>> &res){
    
    res[0][0] = 4*x[0];
    res[0][1] = -cos(x[1]);
    res[1][0] = -exp(x[0]);
    res[1][1] = 4*x[1];
    res[0][2] = 0;
    res[1][2] = 0;
    
}


/*vector<double> func(double a,double b,vector<double> res){
    res.push_back(4*a - cos(b));
    res.push_back(4*b - exp(a));
    return res;
}

void Mx(vector<vector<double>> &J,vector<double> x){

    vector<double> res;
    res = func(x[0],x[1],res);

    J[0][0] = 4;
    J[0][1] = sin(x[1]);
    J[1][0] = -exp(x[0]);
    J[1][1] = 4;
    J[0][2] = -res[0];
    J[1][2] = -res[1];

}*/


void df(vector<vector<double>> &res1,vector<double> x){
    
    vector<vector<double>> res;
    vector<vector<double>> dres;
    
    res.resize(x.size());
        for (int i = 0; i < x.size(); i++)
        res[i].resize(x.size()+1);
  
    dres = res;
    
    ffunc(x,res);
    
    for(int i=0;i<res.size();i++){
        x[i]-=0.001;
    }
    
    ffunc(x,dres);
    
    for(int i=0;i<res.size();i++){
        for(int j=0;j<res[i].size();j++){
            res1[i][j] = (res[i][j] - (dres[i][j]))/0.001;
            }
    }

    int j;
    for(int i=0;i<res.size();i++){
        for(j=0;j<res[i].size()-1;j++){
            res1[i][res[i].size()-1]+=res[i][j];
        }
        
        res1[i][res[i].size()-1]-=res[i][j];
        res1[i][res[i].size()-1]*=(-1);
    }
    
        
   
    
    res.clear();
    dres.clear();
    
}

void xfunc(vector<double> &res,vector<double>x){
    res[0] = cos(x[1])/4;
    res[1] = exp(x[0])/4;
}

void proverka_solo(vector<double> x,int str){
    
    double result=0;
    vector<vector<double>> res;
    res.resize(x.size());
        for (int i = 0; i < x.size(); i++)
        res[i].resize(x.size()+1);
    
    ffunc(x,res);
   
    for(int j=0;j<x.size();j++){
        result+=res[str][j]*x[str];
    }
    cout  << result << "    nevyaska = "  << abs(result - res[str][x.size()]) << endl;

}

void proverka(vector<double> x){
    
    vector<vector<double>> res;
    cout << endl << "Проверка:" << endl << endl;
    res.resize(x.size());
        for (int i = 0; i < x.size(); i++)
        res[i].resize(x.size()+1);
  
    ffunc(x,res);
    
    double result=0;
    for(int i=0;i<x.size();i++){
        result = 0;
        for(int j=0;j<x.size();j++){
            result+=res[i][j]*x[i];
        }
        cout << result << "   " << res[i][x.size()]<< endl;
    }
}

void PI(vector<double> &x,double eps){
    
    vector<double>res(x.size());
    cout << endl << endl;
    cout << "Метод простых итераций:"<< endl << endl;
    
    vector<double>xcopy;
    double max=1;
    while(abs(max)>eps){
        
        xfunc(res,x);
        
        xcopy = res;
        
        for(int i=0;i<res.size()-1;i++){
            if(abs(xcopy[i]-x[i])>abs(xcopy[i+1]-x[i+1]))
                max = abs(xcopy[i]-x[i]);
            else
                max = abs(xcopy[i]-x[i]);
        }
        x = xcopy;
        for(int i=0;i<x.size();i++){
            cout << "x_" << i+1 << ": " <<  x[i] << "   f(x)= " ;
            proverka_solo(x,i);//
        }
        cout << endl;
 
    }
    
    
    
}

void print_x(vector<double> x){
    for(int i=0;i<x.size();i++){
        cout << "x_" << i+1 << ": " <<  x[i] << endl;
    }
    cout << endl;
}
void Newtone(vector<double> x,double eps,int N){
    
    double max = 1;
    vector<vector<double>> J;
    
    vector<vector<double>> Jcopy;
    //int counter = 0;
    vector<double> x1;
    vector<double>res(2);
    x1 = x;
    Jcopy = J;
    cout << endl << "Метод Ньютона:"<< endl << endl;
    int counter = 0;
    J.resize(N);
        for (int i = 0; i < N; i++)
        J[i].resize(N+1);
    
    while(abs(max)>eps){
        counter++;
        df(J,x);
    
        Gauss G(N,N+1,J);
        for(int i=0;i<G.x.size();i++){
            max = G.x[0];
            if(abs(G.x[i])>max)
                max = G.x[i];
        }
        for(int i=0;i<N;i++){
            x[i] = G.x[i]+x[i];
        }
        
        for(int i=0;i<x.size();i++){
            cout << "x_" << i+1 << ": " <<  x[i] << "   f(x)= " ;
            proverka_solo(x,i);//
        }
        cout << endl;
 
        //print_x(x);
       
    }
    cout << endl;
    print_x(x);
    cout << endl;
 
    proverka(x);
    
    PI(x1,eps);
    cout << endl << endl;
 
    print_x(x1);

    proverka(x1);
   
    
  
   
}
int main(int argc, const char * argv[]) {
 
    vector<double> x;
    x.push_back(1);
    x.push_back(3);
    double eps = 0.00001;
    Newtone(x, eps, 2);
    cout << endl;
    cout << "Точность:" << eps << endl;
    return 0;
    
}
