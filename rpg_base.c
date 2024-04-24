#include"rpg_base.h"
int main(){
    FILE *fp;
    fp = fopen("rpg_data.txt", "r");
    char array[MAX_NAME];
    for (int i = 0; i<2;i++){
        fscanf(fp, ":%s;", &array[0]);
        //printf("%s", array);
    };
    for (int i = 0; i<strlen(array)-1;i++){
        printf("%c", array[i]);
    }
    fclose(fp);
}


