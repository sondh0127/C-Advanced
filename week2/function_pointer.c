#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct{
	int(*MyFunctionPointer)(int);
}MyStruct;
// function take a function ptr
// passing function into other function
MyStruct *put_function_pointer_into_structure(int(*FunctionPointer)(int))
{
	MyStruct *newStruct = (MyStruct*)malloc(sizeof(MyStruct));
	newStruct->MyFunctionPointer = FunctionPointer;
	return newStruct;
}

int divide_by_two(int number)
{
	return number/2;
}

int main()
{
	MyStruct *StructureWithFunctionPointer = put_function_pointer_into_structure(divide_by_two);
	int a = 9000;
	int i = StructureWithFunctionPointer->MyFunctionPointer(a);
	printf("The haft of %d: %d\n", a, i);
	free(StructureWithFunctionPointer);
    return 0;
}
