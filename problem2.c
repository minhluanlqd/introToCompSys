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
int *find_max(int arr[],int arrLength){ //this function find max also find hidden key
        int i;
        int max = arr[0];
        int result[4];
        int hidden[3];
        int hid = 0;
        for(i = 1; i<arrLength; i++){
                if(max < arr[i]){
                        max = arr[i];
                }
                if (arr[i] <0){
                hidden[hid] = i;
                hid++;
                                }
        }
        result[0] = max;
        result[1] = hidden[0];
        result[2] = hidden[1];
        result[3]= hidden[2];
        return result;
}


void writeResult(const char* file_name,int arr[], int len){
        FILE *file = fopen(file_name, "w");
        int* result = find_max(arr, len);

        fprintf(file, "Hello I am process: %d\nMax = %d\nI found hidden keys in position A[%d] A[%d] A[%d]", getpid(), result[0], result[1], result[2], result[3]);
        


        fclose(file);
}
 
void printArray(int a[],int len){
	int i = 0;
	for (i =0 ; i<len;i++){
	printf("%d\n", a[i]);
}}

int main(){
        int arr[1000000];
	char *filename = "./File1M.txt";
	char *resultFile ="./result1M.txt";
	read_ints(filename,arr);
	writeResult(resultFile, arr, 1000000); //10 is just a dummy length
        return 0;
}
