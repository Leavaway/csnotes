#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>

void print_binary(int num) {
    char binary_str[sizeof(int) * 8 + 1] = {0}; 
    int index = sizeof(int) * 8 - 1;

    for (int i = 0; i < sizeof(int) * 8; i++) {
        binary_str[index] = (num & 1) ? '1' : '0';
        num >>= 1;
        index--;
    }

    printf("Binary: %s\n", binary_str);
}

int main(int argc, char * argv[]){
    if(argc < 2){
        printf("%s filename \n", argv[0]);
        return -1;
    }
    struct stat st;
    if((stat(argv[1], &st))==-1){
        perror("stat: ");
        return -1;
    }
    char mod[11] = {0};
    //Set the file type.
    switch (st.st_mode & S_IFMT) {
            case S_IFREG:
                mod[0] = '-';
                break;
            case S_IFDIR:
                mod[0] = 'd';
                break;
            case S_IFLNK:
                mod[0] = 'l';
                break;
            case S_IFBLK:
                mod[0] = 'b';
                break;
            case S_IFCHR:
                mod[0] = 'c';
                break;
            case S_IFIFO:
                mod[0] = 'p';
                break;
            case S_IFSOCK:
                mod[0] = 's';
                break;    
            default:
                mod[0] = '?';
                break;
        }
    
    mod[1]=(st.st_mode & S_IRUSR)?'r':'-';
    mod[2]=(st.st_mode & S_IWUSR)?'w':'-';
    mod[3]=(st.st_mode & S_IXUSR)?'x':'-';
    
    mod[4]=(st.st_mode & S_IRGRP)?'r':'-';
    mod[5]=(st.st_mode & S_IWGRP)?'w':'-';
    mod[6]=(st.st_mode & S_IXGRP)?'x':'-';

    mod[7]=(st.st_mode & S_IROTH)?'r':'-';
    mod[8]=(st.st_mode & S_IWOTH)?'w':'-';
    mod[9]=(st.st_mode & S_IXOTH)?'x':'-';

    //The number of hard link.
    int nlink = st.st_nlink;
    
    //Get the user name
    char * user = getpwuid(st.st_uid) -> pw_name;

    //Get the group name
    char * group = getgrgid(st.st_gid) -> gr_name;

    //Get the size of file
    long int size = st.st_size;

    //Get the modify time
    const char *time_const = ctime(&st.st_mtime);
    char time[30]; 
    strncpy(time, time_const, sizeof(time) - 1);
    time[sizeof(time) - 1] = '\0';
    time[strlen(time) - 1] = '\0';


    char buf[1024];

    sprintf(buf,"%s %d %s %s %ld %s %s", mod, nlink, user, group, size, time, argv[1]);

    printf("%s\n", buf);

    return 0;
}
