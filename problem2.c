#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>

void read_ints(const char* file_name,int arr[]){
	FILE *file = fopen(file_name, "r");
	int i = 0;
	int pointer = 0;
	fscanf(file, "%d", &i);
	while (!feof (file)){

		arr[pointer]= i;
		pointer++;
		fscanf(file, "%d", &i);
	}
	fclose(file);
}
void writeResult(const char* file_name,int arr[], int len){
        FILE *file = fopen(file_name, "w");
        int max = find_max(arr, len);

        fprintf(file, "Hello I am process: %d\n Max = %d", getpid(), max);
        


        fclose(file);
}
 
int find_max(int arr[],int arrLength){
        int i;
        int max = arr[0];
        for(i = 1; i<arrLength; i++){
                if(max < arr[i]){
                        max = arr[i];
                }
        }
        return max;
}
void printArray(int a[],int len){
	int i = 0;
	for (i =0 ; i<len;i++){
	printf("%d\n", a[i]);
}}

int main(){
        int arr[100];
	char *filename = "./File1.txt";
	char *resultFile ="./result.txt";
	read_ints(filename,arr);
	writeResult(resultFile, arr, 10); //10 is just a dummy length
        return 0;
}
