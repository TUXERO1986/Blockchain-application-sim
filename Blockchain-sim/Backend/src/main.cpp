
#include <iomanip>
#include <iostream>

int main(){
    char b =200;
    for (int i=0; i<3;i++){
        std::cout<< std::hex<<static_cast<int>(b)<<"\n";
        
    }
    std::cout<<"\n";
}