#include <stdio.h>

int main()
{
   /* 我的第一个 C 程序 */
	int unSortedArray[] = {49,38,65,97,76,13,27,49};
	if((sizeof(unSortedArray) / sizeof(unSortedArray[0]))==0){
		return 0;
	}
	int tmp;
	for(int i = 1;i<(sizeof(unSortedArray) / sizeof(unSortedArray[0]));i++){
		while(unSortedArray[i]<unSortedArray[i-1]){
			tmp = unSortedArray[i-1];
			unSortedArray[i-1] = unSortedArray[i];
			unSortedArray[i] = tmp;
		}
	}
	for(int i = 0;i<sizeof(unSortedArray) / sizeof(unSortedArray[0]);i++){
		printf("%d ",unSortedArray[i]);
	}
	
   
   return 0;
}
