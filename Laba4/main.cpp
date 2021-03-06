#include <iostream>
#include "math.h"
#include <cmath>
#include <cstdlib>
 
using namespace std;


long double N_sqrt(long double x,long double n){
    
    if(x<0){
        return -pow((-x),(1/n));
    }
    else
        return pow(x,(1/n));
}

long double func(long double x){
    return x*exp(x) - 1.6005;
}

long double dfunc(long double x){
    return (func(x)-func(x-0.1))/0.1;
}

long double ddfunc(long double x){
    return 4 - (1/(pow((x+1),2)));
}

long double xfunc(long double x){
    double res=0;
    res = ((1 + log(x+1))/2);
    res = pow(res,0.5);
    return res;
}

long double xfunc1(long double x){
    double res=0;
    res = exp(2*x*x-1)-1;
    return res;
}


bool proverka(long double a, long double b){
    
    if(func(a)*func(b)<0)
        return 1;
    else
        return 0;
}

long double Newtone(long double a,long double b,long double eps){
    
    long double x,xbuff;
    x=b;
    xbuff = x - func(x)/dfunc(x);
    cout << "x = " << xbuff << "  f(x) = " << func(xbuff)<< endl;

    while(abs(xbuff-x)>eps){
        x = xbuff;
        xbuff = x - func(x)/dfunc(x);
        cout << "x = " << xbuff << "  f(x) = " << func(xbuff)<< " " << abs(func(x)) << endl;
    }
    
    
    return xbuff;
}

long double metod_prostih(long double a, long double b, long double eps){
    
    if(xfunc(a)>1 && xfunc(b)>1){
         cout << "функция не подходит";
         return 0;
    }
    
    long double x,xbuff;
    x = b;
    xbuff  = xfunc(x);
    cout << "x = " << xbuff << "  f(x) = " << func(xbuff)<< endl;

    while(abs(xbuff-x)>=eps){
        x = xbuff;
        xbuff  = xfunc(x);
        cout << "x = " << xbuff << "  f(x) = " << func(xbuff) << "  d = " << abs(func(x)) << endl;
 
    }
    
    return xbuff;
}

long double metod_prostih1(long double a, long double b, long double eps){
    
    
    long double x,xbuff;
    x = b;
    xbuff  = xfunc(x);
    cout << "x = " << xbuff << "  f(x) = " << func(xbuff)<< endl;

    while(abs(xbuff-x)>=eps){
        x = xbuff;
        xbuff  = xfunc1(x);
        cout << "x = " << xbuff << "  f(x) = " << func(xbuff) << "  d = " << abs(func(x)) << endl;
 
    }
    
    return xbuff;
}

long double metod_polovina(long double a,long double b,long double eps){
    
    long double x=0,y,z;
    long double xbuff=(a+b)/2;
    while(abs(b-a)>eps){
        z = func(a);
        x = (a+b)/2;
        y = func(x);
        if(y*z>0){
            a = x;
            z = y;
        }
        else
            b = x;
        cout << "x = " << x<< "  f(x) = " << func(x) << "  d = " << abs(func(x)) << endl;
        xbuff = x;
    }
    return x;
}

long double metod_sec(long double a,long double b,long double eps){
    
    long double x,x0,xbuff=-99999,df;
    
    x0=b;
    df = (func(x0) - func(x0-0.1))/0.1;
    x = x0 - func(x0)/df;
    
    while(abs(xbuff-x0)>eps){
        xbuff = x - (func(x)/(func(x)-func(x0)))*(x - x0);
        x0 = x;
        cout << "x = " << xbuff << "  f(x) = "  << func(xbuff) << "  d = " << abs(func(xbuff)) << endl;
 
        x = xbuff;
   
    }
    return xbuff;
}

int main(int argc, const char * argv[]) {
    
    double a=-1,b=1;
    
    if(!proverka(a,b))
        return 0;
    
    long double eps = 0.001;
    cout << "Метод половинного деления:" << endl;
    long double res = metod_polovina(a, b,eps);
    cout << endl;
   
    cout << "Метод Ньютона:" << endl;
    long double res1 = Newtone(a, b,eps);
    cout << endl;
    cout << "Метод простых итераций:"<< endl;
    cout << "1" << endl;
   
    long double res2 =  metod_prostih(a, b, eps);
    cout << "2" << endl;
   
    long double ress = metod_prostih(a, b, eps);
    cout << endl;
    cout << "Метод секущих:"  << endl;
    
    long double res3 = metod_sec(a, b, eps);
   
    cout << endl;
    cout << "Точность:" << eps << endl;
    
    return 0;
}
