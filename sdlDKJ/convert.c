#include <stdio.h>

int charToInt(char *a, int largo){
    int num =0;
    int in = 1;
    for(int i=largo-1; i>=0; i--){
        num += (a[i]-'0')*in;
        in = in *10;
    }
    return num;
}
int getLargo(char *cadena){
    int i = 0;
    while(*cadena != '\0'){
        i ++;
        cadena ++;
    }
    return i;
}
void crearArray(char *a){
    char *tocken = strtok(a,";");
    //printf("%d", getLargo(tocken));
    int t = charToInt(tocken,getLargo(tocken));
    tocken= strtok(NULL,";");
    int b = charToInt(tocken,getLargo(tocken));
    tocken= strtok(NULL,";");
    //char *j = strtok(NULL,";");
    int c = charToInt(tocken,getLargo(tocken));
    tocken= strtok(NULL,";");
    int y = charToInt(tocken,getLargo(tocken));
    printf("%d %d %d %d",t,b,c,y);

}

//int main(int argc, char* argv[]) {
    //SOCKET s = crearSocket();

//    char r[]="20;15;2;7";
//    crearArray(r);
//int i = charToInt(r,getLargo(r));
    //printf("%d",i);

//}
