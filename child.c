#include <stdio.h>
#include <stdlib.h>

int binarySearch(int arr[], int n, int key){
    int l=0, r=n-1;
    while(l<=r){
        int m = l + (r-l)/2;
        if(arr[m]==key) return m;
        else if(arr[m]<key) l=m+1;
        else r=m-1;
    }
    return -1;
}

int main(int argc, char *argv[]){
    if(argc<3){
        printf("Usage: ./child <sorted_array>... <key>\n");
        return 1;
    }

    int n = argc-2;
    int arr[n];
    for(int i=0;i<n;i++) arr[i]=atoi(argv[i+1]);
    int key = atoi(argv[argc-1]);

    int index = binarySearch(arr,n,key);
    if(index!=-1) printf("Element %d found at index %d\n", key, index);
    else printf("Element %d not found\n", key);

    return 0;
}
