#include"rpg_base.h"
int main(){
    FILE *fp;
    fp = fopen("rpg_data.txt", "r");
    char s[MAX_TXT];
    char array[MAX_NAME];
    while(fgets(s, 10, fp)) {
        if(1==fscanf(fp, "Name_sk:%s\n", array)){
            printf("%s\n", array);
            fgets(s, strlen(array), fp);
        }
    }
    fclose(fp);
}


