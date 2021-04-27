#include <stdio.h>

int charToInt(char *a, int largo){
    int num =0;
    int in = 1;
    for(int i=largo-2; i>=0; i--){
        num += (a[i]-'0')*in;
        in = in *10;
    }
    return num;
}
/*
Ejemplo de ejecución, siempre tiene que ser así y ya tiene que estar dividido
int main(int argc, char* argv[]) {
    char a[]="12";
    int result = charToInt(a,sizeof(a)/sizeof(a[0]));
    printf("%d",result);


}
*/
