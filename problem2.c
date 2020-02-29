#include<stdio.h>

void read_ints(const char* file_name){
	FILE *file = fopen(file_name, "r");
	int i = 0;
	fscanf(file, "%d", &i);
	while (!feof (file)){
		printf("%d\n", i);
		fscanf(file, "%d", &i);
	}
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
int main(){
	char *filename = "/Users/luantran/Desktop/File1.txt";
	read_ints(filename);
	int arr[9] = {100, 20, 35, 999, 45, 23, 1, 10, 7};
	int max = find_max(arr,9);
	printf("Max is: %d\n", max);
	return 0;
}
