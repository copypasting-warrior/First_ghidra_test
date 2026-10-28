#include<stdio.h>
int checkc(int code){
    if(code==1234){
        return 1;
    }
    return 0;
}
void main(){
    int code=1234;
    if(checkc(code)){
        printf("Access Granted");
    }else{
        printf("Access Denied");
    }
}