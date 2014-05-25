#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "dynamicArray.h"
#include "toDoList.h"

#define TESTSORT
int main(int argc, const char * argv[])
{
  Task *task1, *task2, *task3, *task4, *task5, *task6, *task7, *task8, *task9, *task10;
  Task *task11, *task12, *task13, *task14, *task15, *task16, *task17, *task18, *task19, *task20;
	DynArr *mainList;
	int i;
	mainList = createDynArr(10);

	/* create tasks */
	task1 = createTask(9, "task 1");
	task2 = createTask(3, "task 2");
	task3 = createTask(2, "task 3");
	task4 = createTask(4, "task 4");
	task5 = createTask(5, "task 5");
	task6 = createTask(7, "task 6");
	task7 = createTask(8, "task 7");
	task8 = createTask(6, "task 8");
	task9 = createTask(1, "task 9");
	task10 = createTask(10, "task 10");
    task11 = createTask(19, "task 11");
	task12 = createTask(13, "task 12");
	task13 = createTask(12, "task 13");
	task14 = createTask(14, "task 14");
	task15 = createTask(15, "task 15");
	task16 = createTask(17, "task 16");
	task17 = createTask(18, "task 17");
	task18 = createTask(16, "task 18");
	task19 = createTask(3, "task 19");
	task20 = createTask(110, "task 20");

	/* add tasks to the dynamic array */
	addHeap(mainList, task1);
	addHeap(mainList, task2);
	addHeap(mainList, task3);
	addHeap(mainList, task4);
	addHeap(mainList, task5);
	addHeap(mainList, task6);
	addHeap(mainList, task7);
	addHeap(mainList, task8);
	addHeap(mainList, task9);
	addHeap(mainList, task10);
    addHeap(mainList, task11);
	addHeap(mainList, task12);
	addHeap(mainList, task13);
	addHeap(mainList, task14);
	addHeap(mainList, task15);
	addHeap(mainList, task16);
	addHeap(mainList, task17);
	addHeap(mainList, task18);
	addHeap(mainList, task19);
	addHeap(mainList, task20);

#ifdef TESTHEAP
    printf("Print heap\n");
	for(i = 0; i < sizeDynArr(mainList);i++)
		print_type(getDynArr(mainList,i));


	while(!isEmptyDynArr(mainList))
	{
		TYPE v;
		v = getMinHeap(mainList);
		 printf("Removing: ");
		print_type(v);
		removeMinHeap(mainList);

        for(i = 0; i < sizeDynArr(mainList);i++)
            print_type(getDynArr(mainList,i));
	}
#endif

#ifdef TESTSORT

	printf("Before Sort Called \n");
	for(i = 0; i < sizeDynArr(mainList);i++)
			printf("DynArr[%d] = %d\n", i, ((Task*)getDynArr(mainList,i))->priority);


	/* sort tasks */
	sortHeap(mainList);
	printf("After Sort Called \n");

	/* print sorted tasks from the dynamic array */
	for(i = 0; i < sizeDynArr(mainList);i++)
				printf("DynArr[%d] = %d\n", i, ((Task*)getDynArr(mainList,i))->priority);

	return 0;

#endif
}
