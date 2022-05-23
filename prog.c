#include <stdio.h>
#include <strings.h>     // bzero, bcopy, bcmp

int main (){
	/*
	char str[30] = "Hello";
	bzero(&str[2], 1);      // bzero(void * ptr, nbytes)
	printf("Number stored: %s\n", str);
	for (int i=0; i<30; i++){
		printf("%c|", str[i]);
	}
	printf("\n");*/
	//=========================================
	/*char str1[30] = "Hello";
	char str2[20] = "Hold";
	if (bcmp(str1, str2, 2) == 0){       // bcmp(void *ptr1, void *ptr2, size_t nbytes)
		printf("Equal\n");
	}
	else{
		printf("Not Equal\n");
	}*/
	//=========================================
	//int a = 1;
	//int b = 256;
	char str1[30] = "Hello";
	char str2[30] = "Sitanshu";
	bcopy(&str2, &str1, 9);// bcopy(void *source, voi *destination, size_t nbytes)
	printf("%s\n", str1);
	return 0;
}
