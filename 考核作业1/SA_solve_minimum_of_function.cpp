#include <iostream>  
#include <string.h>  
#include <stdlib.h>  
#include <algorithm>  
#include <stdio.h>  
#include <time.h>  
#include <math.h>  
  
#define ITERS 5 
#define T 40  
#define eps 1e-2 
#define delta 0.4 
#define INF 1e99  
  
using namespace std;  
  
double x[ITERS];  
  
int Judge(double x, double y)  
{  
    if(fabs(x - y) < eps) return 0;  
    return x < y ? -1 : 1;  
}  
  
double Random()  
{  
    double x = rand() * 1.0 / RAND_MAX;  
    if(rand() & 1) x *= -1;  
    return x;  
}  
  
double F(double x, double y)  
{  
    return   5 * pow(x,5) - 11 * pow(x,4) + 13 * pow(x,3) - 12 * pow(x,2) + y * x;  
}  
  
void Init()  
{  
    for(int i = 0; i < ITERS; i++)  
        x[i] = fabs(Random()) * 100;  
}  
  
double SA(double y)  
{  
    double ans = INF;  
    double t = T;  
    while(t > eps)  
    {  
        for(int i = 0; i < ITERS; i++)  
        {  
            double tmp = F(x[i], y);  
            for(int j = 0; j < ITERS; j++)  					//内循环，在邻域内搜索 
            {  
                double _x = x[i] + Random() * t;  
                if(Judge(_x, 0) >= 0 && Judge(_x, 100) <= 0)  
                {  
                    double f = F(_x, y);  
                    if(tmp > f){  
                        x[i] = _x;
					}
                }  
            }
			if(i > 0 && F(x[i],y) > F(x[i-1],y)){;}
			else{
				cout<<x[i]<<'\t'<<F(x[i],y)<<endl;   
		}
		}  
        
    	cout<<endl;
        t *= delta;  
    }  
    
    for(int i = 0; i < ITERS; i++) { 
//    	cout<<i<<' '<<x[i]<<' '<<F(x[i],y)<<endl;
        ans = min(ans, F(x[i], y));     
	}
    return ans;  
}  
  
int main()  
{  
//    int t;  
//    scanf("%d", &t);  
//    while(t--)  
//    {  
    double y;  
	scanf("%lf", &y);  
    srand(time(NULL));  
    Init();  
//    cout<<endl;
    printf("%.4lf\n", SA(y));  
      
    return 0;  
}  
