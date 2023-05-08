#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    int i = fork();
    if(i>0){
        int fdw = open("fifo1", O_WRONLY);
        if(fdw==-1){
            perror("open");
            exit(-1);
        }
        char buffer[1024];
        while(1){
            printf("Enter a line of text: \n");
            fgets(buffer, sizeof(buffer), stdin);
            printf("You entered: %s\n", buffer);
            int w = write(fdw, buffer, sizeof(buffer));
            if(w==-1){
                perror("write");
                exit(-1);
            }
        }
        close(fdw);
    }else if (i==0)
    {
        int fdr = open("fifo2", O_RDONLY);
        if(fdr==-1){
            perror("open");
            exit(-1);
        }
        char buffer[1024];
        while(1){
            int r = read(fdr, buffer, sizeof(buffer));
            if(r==-1){
                perror("read");
                exit(-1);
            }else if(r==0){
                break;
            }
            printf("Receive message: %s\n", buffer);
        }
        close(fdr);
    }
    return 0;
}
