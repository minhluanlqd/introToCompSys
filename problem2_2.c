#include<stdio.h>
#include<time.h>
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
int* findHiddenKeys (int arr[], int lowerBound, int upperBound, int fork){
	if (fork ==0){
		int hidden[1];
		int i = lowerBound;
		for (i = lowerBound; i < upperBound; i++){
			if (arr[i] < 0){
				 hidden[0] = i;
				 return hidden;
			}


		}
	}

	else {
		int hidden[2];
		int i;
		int count = 0;
		for (i = lowerBound; i< upperBound; i++){
			if (arr[i] < 0){
				hidden[count] =i;
				count++;
			}
			if (count ==2 ) return hidden;
		}
	}

}
int find_max(int arr[],int lowerBound, int upperBound){ //this function find max also find hidden key
        int i;
        int max = arr[lowerBound];
      
        for(i = lowerBound ; i<upperBound; i++){
                if(max < arr[i]){
                        max = arr[i];
                }
	}
        return max;
}


void writeResult(const char* file_name,int arr[], int low, int high){
        FILE *file = fopen(file_name, "w");
        int result = find_max(arr, low, high);

        fprintf(file, "Hello I am process: %d\nMax = %d\n", getpid(), result);
        


        fclose(file);
}


int main(){
	double time_spent = 0.0;
	clock_t begin = clock();

	int myPipe[2];
	int maxPipe[2];
        int arr[10];
	int size = sizeof(arr)/sizeof(arr[0]);
	char outString[100];
	char *filename = "./File10.txt";
	char *resultFile ="./result_2_1.txt";
	read_ints(filename,arr);

	int createPipe=	pipe(myPipe);
	pipe(maxPipe);
	if (createPipe == -1){
		fprintf(stderr, "Pipe failed");	
	}
	int p = fork();
	if (p < 0) exit(0);
	else if (p == 0) { //Child process
		int max1 = find_max(arr, 0, size/2-1);
		int *hidden = findHiddenKeys(arr, 0, size/2-1, p);
		int hiddenKey = hidden[0];
		sprintf(outString, "Hi I am  process %d and my parent is %d\nI found hidden key at A[%d]\n", getpid(),getppid(), hiddenKey);
		write(myPipe[1], outString, 100);
		write(maxPipe[1],&max1, sizeof(max1));
	}
	else {//parent process
		waitpid(NULL);
		read(myPipe[0], outString, 100);
		int maxChild;
		read(maxPipe[0], &maxChild, sizeof(maxChild));
		int max2 = find_max(arr, size/2-1, size-1);
		int *hidden = findHiddenKeys(arr, size/2-1, size-1, p);
		int hidden1 = hidden[0], hidden2 = hidden[1];
		//printf("Hi I am process %d and my parent is %d\nI found hidden keys at A[%d] A[%d]\n", getpid(),getppid(), hidden1, hidden2);
		//printf("%s", outString);
		if(maxChild > max2){
			max2= maxChild;
		}
		FILE *file = fopen(resultFile, "w");
		fprintf(file, "Max is %d\n", max2);
		fprintf(file, "Hi I am process %d and my parent is %d\nI found hidden keys at A[%d] A[%d]\n", getpid(), getppid(), hidden1, hidden2);
		fprintf(file, "%s", outString);
		//waitpid(NULL);

		clock_t end = clock();
		time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
		printf("\nTime elpased is %f seconds\n", time_spent);
	}

        return 0;
}
