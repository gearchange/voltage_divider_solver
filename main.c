#include <stdio.h>
#include "voltage_divider_solver.h"

int main(int argc, char *argv[]){

	double upside, downside;

	voltage_divider_solver(&upside, &downside, 3.3, 0.12);

	printf("%3f\t%3f\t%3f\r\n", upside, downside, downside / (downside + upside) * 3.3);

	return 0;

}

