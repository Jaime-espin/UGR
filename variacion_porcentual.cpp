#include<iostream>
#include<cmath>
using namespace std;

main(){
    double v1, v2, resultado;

    cout<<"escribe el valor inicial: "<<endl;
    cin>>v1;

    cout<<"escribe el valor final: "<<endl;
    cin>>v2;

    resultado=(100*(v2-v1)/v1);
    cout<<resultado<<endl;

    return 0;
}
