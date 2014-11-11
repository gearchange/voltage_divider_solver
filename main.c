#include <stdio.h>
#include "voltage_divider_solver.h"

int main(int argc, char *argv[]){

	double upside, downside;

	voltage_divider_solver(&upside, &downside, 8.10, 1.14514);

	printf("%3f\t%3f\t%3f\r\n", upside, downside, downside / (downside + upside) * 8.10);

	return 0;

}

