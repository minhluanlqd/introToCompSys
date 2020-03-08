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
int find_max(int arr[],int lowerBound, int upperBound){ //this function find max 
        int i;
        int max = arr[lowerBound];
        for(i = lowerBound ; i<upperBound; i++){
                if(max < arr[i]){
                        max = arr[i];
                }
	}
        return max;
}
int find_hidden_key(int arr[], int lowerBound, int upperBound){
	int i;
	int hiddenID;
	for(i = lowerBound; i < upperBound; i++){
		if(arr[i]<0){
			hiddenID = i;
			return hiddenID; 
		}else{
			hiddenID = 0;
		}
	}
	return hiddenID;
}

void writeResult(const char* file_name,int arr[], int low, int high){
        FILE *file = fopen(file_name, "w");
        int result = find_max(arr, low, high);

        fprintf(file, "Hello I am process: %d\nMax = %d\n", getpid(), result);
        


        fclose(file);
}


int main(){
//	double time_spent = 0.0;
//	clock_t begin = clock();

	int Pipe1[2];
	int Pipe2[2];
	int Pipe3[2];
	int Pipe4[2];
	int Pipe5[2];
	int Pipe6[2];
        int arr[1000000];   // FIX THIS LENGTH ACCORDING TO THE FILE
	int size = sizeof(arr)/sizeof(arr[0]);
	int interval = (size - 1)/7;
	int b1 = interval * 1;
	int b2 = interval * 2;
	int b3 = interval * 3;
	int b4 = interval * 4;
	int b5 = interval * 5;
	int b6 = interval * 6;
	int b7 = size;
	char outString1[100];
	char outString2[100];
	char outString3[100];
	char outString4[100];
	char outString5[100];
	char outString6[100];
	char *filename = "./File1M.txt"; // FIX NAME FILE
	char *resultFile ="./result_3_1M.txt"; // FIX NAME OF RESULT FILE
	read_ints(filename,arr);
	pipe(Pipe1);
	pipe(Pipe2);
	pipe(Pipe3);
	pipe(Pipe4);
	pipe(Pipe5);
	pipe(Pipe6);

	int p = fork();
	int p1 = fork();

	if(p > 0 && p1 > 0){ // Parent
		wait(NULL);
		wait(NULL);
		read(Pipe1[0], outString1, 100);
		read(Pipe2[0], outString2, 100);
		read(Pipe3[0], outString3, 100);
		read(Pipe4[0], outString4, 100);
		read(Pipe5[0], outString5, 100);
		read(Pipe6[0], outString6, 100);
		int maxGrChild[7];
		int hiddenArr[7];
		read(Pipe1[0], &maxGrChild[1], sizeof(maxGrChild[1]));
		read(Pipe2[0], &maxGrChild[2], sizeof(maxGrChild[2]));
		read(Pipe3[0], &maxGrChild[3], sizeof(maxGrChild[3]));
		read(Pipe4[0], &maxGrChild[4], sizeof(maxGrChild[4]));
		read(Pipe5[0], &maxGrChild[5], sizeof(maxGrChild[5]));
		read(Pipe6[0], &maxGrChild[6], sizeof(maxGrChild[6]));
		maxGrChild[0] = find_max(arr,b6,b7); // this elem is max of parent
		int max = find_max(maxGrChild, 0 , 7);
		int hiddenID = find_hidden_key(arr,b6,b7);
		FILE *file = fopen(resultFile, "w");
		if(hiddenID == 0){
			fprintf(file,"Parent: Hi I am process %d and my parent is %d\nMax is: %d\n", getpid(), getppid(),maxGrChild[0]);
		}else{
			fprintf(file,"Parent: Hi I am process %d and my parent is %d and I found hidden key at A[%d]\nMax is: %d\n", getpid(), getppid(),hiddenID,maxGrChild[0]);
		}
		printf("maxGrChild1 is: %d\nmaxGrChild2 is: %d\nmaxGrChild3 is: %d\n", maxGrChild[1], maxGrChild[2], maxGrChild[3]);
		printf("maxGrChild4 is: %d\nmaxGrChild5 is: %d\nmaxGrChild6 is: %d\n", maxGrChild[4], maxGrChild[5], maxGrChild[6]);
		fprintf(file,"%s\n", outString1);
		fprintf(file,"%s\n", outString2);
		fprintf(file,"%s\n", outString3);
		fprintf(file,"%s\n", outString4);
		fprintf(file,"%s\n", outString5);
		fprintf(file,"%s\n", outString6);
		fprintf(file,"Total max is: %d\n", max);
		fclose(file);
	}else if (p == 0 && p1 > 0){ // 1st child
		int max = find_max(arr,b4,b5);
		int hiddenID = find_hidden_key(arr,b4,b5);
		printf("1st Child: Hi I am process %d and my parent is %d\nMax is: %d\n", getpid(), getppid(),max);
		if(hiddenID == 0){
			sprintf(outString5, "Hi I am  process %d and my parent is %d\nMax is: %d", getpid(),getppid(), max);
			write(Pipe5[1], outString5, 100);
			write(Pipe5[1], &max, sizeof(max));
		}else{
			sprintf(outString5, "Hi I am  process %d and my parent is %d and I found hidden key at A[%d]\nMax is: %d", getpid(),getppid(),hiddenID, max);
			write(Pipe5[1], outString5, 100);
			write(Pipe5[1], &max, sizeof(max));
		}
		int p2 = fork(); // 1st child born 2nd grandchild
		if(p2 == 0){
			int max = find_max(arr,b1,b2);
			int hiddenID = find_hidden_key(arr,b1,b2);
			printf("2nd GrChild: Hi I am process %d and my parent is %d\nMax is: %d\n", getpid(), getppid(),max);
			if(hiddenID == 0){
				sprintf(outString2, "Hi I am process %d and my parent is %d\nMax is: %d\n",getpid(), getppid(), max);
				write(Pipe2[1], outString2, 100);
				write(Pipe2[1], &max, sizeof(max));
			}else{
				sprintf(outString2, "Hi I am process %d and my parent is %d and I found hidden key at A[%d]\nMax is: %d\n",getpid(), getppid(),hiddenID, max);
				write(Pipe2[1], outString2, 100);
				write(Pipe2[1], &max, sizeof(max));
			}
		}else{
			wait(NULL);
			wait(NULL);
		}
	}else if (p > 0 && p1 == 0){ // 2nd child
		int max = find_max(arr,b5,b6);
		int hiddenID = find_hidden_key(arr,b5,b6);
		printf("2nd Child: Hi I am process %d and my parent is %d\nMax is: %d\n", getpid(), getppid(),max);
		if(hiddenID == 0){
			sprintf(outString6, "Hi I am  process %d and my parent is %d\nMax is: %d", getpid(),getppid(), max);
			write(Pipe6[1], outString6, 100);
			write(Pipe6[1], &max, sizeof(max));
		}else{
			sprintf(outString6, "Hi I am  process %d and my parent is %d and I found hidden key at A[%d]\nMax is: %d", getpid(),getppid(),hiddenID, max);
			write(Pipe6[1], outString6, 100);
			write(Pipe6[1], &max, sizeof(max));
		}
		int p3 = fork(); // 2nd child born 1st granchild
		if(p3 == 0){ // 3rd grandchild
			int max = find_max(arr,b2,b3);
			int hiddenID = find_hidden_key(arr,b2,b3);
			printf("3rd GrChild: Hi I am process %d and my parent is %d\nMax is: %d\n", getpid(), getppid(),max);
			if(hiddenID == 0){
				sprintf(outString3,"Hi I am process %d and my parent is %d\nMax is: %d\n", getpid(), getppid(), max);
				write(Pipe3[1], outString3, 100);
				write(Pipe3[1], &max, sizeof(max));
			}else{
				sprintf(outString3, "Hi I am  process %d and my parent is %d and I found hidden key at A[%d]\nMax is: %d", getpid(),getppid(),hiddenID, max);
				write(Pipe3[1], outString3, 100);
				write(Pipe3[1], &max, sizeof(max));
			}
		}else{
			int p4 = fork(); //2nd child born 2nd grandchild
//			wait(NULL);
			if(p4 == 0){ // 4th grandchild
				int max = find_max(arr, b3, b4);
				int hiddenID = find_hidden_key(arr,b3,b4);
				printf("4th GrChild: Hi I am process %d and my parent is %d\nMax is: %d\n", getpid(), getppid(),max);
				if(hiddenID == 0){
					sprintf(outString4, "Hi I am  process %d and my parent is %d\nMax is: %d", getpid(),getppid(), max);
					write(Pipe4[1], outString4, 100);
					write(Pipe4[1], &max, sizeof(max));
				}else{
					sprintf(outString4, "Hi I am process %d and my parent is %d and I found hidden key at A[%d]\nMax is: %d\n",getpid(), getppid(), hiddenID, max);
					write(Pipe4[1], outString4, 100);
					write(Pipe4[1], &max, sizeof(max));
				}
			}else{
				wait(NULL);
				wait(NULL);
			}
		}
	}else{ // 1st grandchild
		int max = find_max(arr,0,b1);
		int hiddenID = find_hidden_key(arr,0,b1);
		printf("1st GrChild: Hi I am process %d and my parent is %d\nMax is: %d\n", getpid(), getppid(),max);
		if(hiddenID == 0){
			sprintf(outString1,"Hi I am process %d and my parent is %d\nMax is: %d\n", getpid(), getppid(),max);
			write(Pipe1[1],outString1, 100);
			write(Pipe1[1],&max, sizeof(max));
		}else{
			sprintf(outString1,"Hi I am process %d and my parent is %d and I found hidden key at A[%d]\nMax is: %d\n",getpid(),getppid(), hiddenID, max);
			write(Pipe1[1],outString1, 100);
			write(Pipe1[1],&max, sizeof(max));
		}
	}
//	else if (p == 0) { //Child process
//		int max1 = find_max(arr, 0, size/2-1);
//		int *hidden = findHiddenKeys(arr, 0, size/2-1, p);
//		int hiddenKey = hidden[0];
//		sprintf(outString, "Hi I am  process %d and my parent is %d\nI found hidden key at A[%d]\n", getpid(),getppid(), hiddenKey);
//		write(myPipe[1], outString, 100);
//		write(maxPipe[1],&max1, sizeof(max1));
		
//	}
//	else {//parent process
//		waitpid(NULL);
//		read(myPipe[0], outString, 100);
//		int maxChild;
//		read(maxPipe[0], &maxChild, sizeof(maxChild));
//		int max2 = find_max(arr, size/2-1, size-1);
//		int *hidden = findHiddenKeys(arr, size/2-1, size-1, p);
//		int hidden1 = hidden[0], hidden2 = hidden[1];
		//printf("Hi I am process %d and my parent is %d\nI found hidden keys at A[%d] A[%d]\n", getpid(),getppid(), hidden1, hidden2);
		//printf("%s", outString);
//		if(maxChild > max2){
//			max2= maxChild;
//		}
//		FILE *file = fopen(resultFile, "w");
//		fprintf(file, "Max is %d\n", max2);
//		fprintf(file, "Hi I am process %d and my parent is %d\nI found hidden keys at A[%d] A[%d]\n", getpid(), getppid(), hidden1, hidden2);
//		fprintf(file, "%s", outString);
		//waitpid(NULL);

//		clock_t end = clock();
//		time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
//		printf("\nTime elpased is %f seconds\n", time_spent);
//	}
        return 0;
}
