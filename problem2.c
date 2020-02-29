#include<stdio.h>
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
void printArray(int a[],int len){
	int i = 0;
	for (i =0 ; i<len;i++){
	printf("%d\n", a[i]);
}}

int main(){
        int arr[100];
	char *filename = "./File1.txt";


	read_ints(filename,arr);
	printArray(arr,10 );
        return 0;
}
