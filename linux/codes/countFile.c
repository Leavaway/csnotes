#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int getFileNum(const char * path);

int main(int argc, char * argv[]){

    if(argc < 2){
        printf("%s path\n", argv[0]);
        return -1;
    }

    int num = getFileNum(argv[1]);

    printf("The number of regular file is: %d\n", num);
    

    return 0;
}

int getFileNum(const char * path){
    DIR *dir = opendir(path);
    if(dir == NULL){
        perror("opendir");
        exit(0);
    }

    struct dirent *ptr;

    int count = 0;

    while((ptr=readdir(dir))!=NULL){
        char * dname = ptr->d_name;
        if(strcmp(dname, ".")==0||strcmp(dname, "..")==0){
            continue;
        }
        if(ptr->d_type == DT_DIR){
            char newpath[256];
            sprintf(newpath, "%s%s%s", path, "/",dname);
            count += getFileNum(newpath);
        }

        if(ptr->d_type == DT_REG){
            count++;
        }
    }
    closedir(dir);
    return count;
}
