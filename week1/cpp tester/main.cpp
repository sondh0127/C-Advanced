#include <iostream>
#include "func.h"

using std::cout;
using std::endl;
int main()
{
	for (int j = 0 ; j > 100; j++) {
		func("Hello World");
	}
	int sum_value = sum(2, 5) ;
	cout << sum_value << endl;
    return 0;
}
