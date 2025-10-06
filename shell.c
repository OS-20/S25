#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void search_first(char *filename, char *pattern) {
    FILE *fp = fopen(filename, "r");
    if(!fp){ printf("File not found!\n"); return; }

    char line[256];
    int line_no = 0;
    while(fgets(line, sizeof(line), fp)){
        line_no++;
        if(strstr(line, pattern)){
            printf("First occurrence at line %d: %s", line_no, line);
            fclose(fp);
            return;
        }
    }
    printf("Pattern not found in file.\n");
    fclose(fp);
}

int main() {
    char input[100], *arg[5];

    while(1){
        printf("myshell$ ");
        if(!fgets(input, sizeof(input), stdin)) break;

        int i=0;
        arg[i] = strtok(input, " \t\n");
        if(!arg[i]) continue;
        while((arg[++i] = strtok(NULL, " \t\n")));

        if(!strcmp(arg[0], "exit")) break;
        else if(!strcmp(arg[0], "search") && arg[1] && arg[2] && arg[3]){
            if(arg[1][0]=='f') search_first(arg[2], arg[3]);
            else printf("Unknown search option!\n");
        }
        else{
            if(fork()==0){
                execvp(arg[0], arg);
                perror("Command failed");
                exit(1);
            } else wait(NULL);
        }
    }

    return 0;
}
