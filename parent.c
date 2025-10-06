#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void bubbleSort(int arr[], int n){
    for(int i=0;i<n-1;i++)
        for(int j=0;j<n-i-1;j++)
            if(arr[j]>arr[j+1]){
                int t=arr[j]; arr[j]=arr[j+1]; arr[j+1]=t;
            }
}

int main() {
    int n, i;
    printf("Enter number of elements: ");
    scanf("%d",&n);
    int arr[n];
    printf("Enter elements: ");
    for(i=0;i<n;i++) scanf("%d",&arr[i]);

    bubbleSort(arr,n);

    char *args[n+3]; // array elements + search number + program name + NULL
    args[0] = "./child"; // program to exec
    printf("Enter element to search: ");
    int key;
    scanf("%d",&key);

    for(i=0;i<n;i++){
        char *num = malloc(10);
        sprintf(num,"%d",arr[i]);
        args[i+1]=num;
    }

    char key_str[10];
    sprintf(key_str,"%d",key);
    args[n+1] = key_str;
    args[n+2] = NULL;

    pid_t pid = fork();
    if(pid==0){
        execve("./child", args, NULL);
        perror("execve failed");
        exit(1);
    } else {
        wait(NULL);
    }

    return 0;
}
