#include <math.h>
#include <stdbool.h>

typedef struct resistor{
	int series;
	int exponetial;
} RESISTOR;

const double E12_series[] = {1.0, 1.2, 1.5, 1.8, 2.2, 2.7, 3.3, 3.9, 4.7, 5.6, 6.8, 8.2};
const int resistor_series_size = sizeof (E12_series) / sizeof (E12_series[0]);
const int max_exponetial = 5;

static inline double calc_resistor_value(const RESISTOR r){
	double hoge = E12_series[r.series];
	for(int i = 0; i < r.exponetial; i++)hoge *= 10.0;
	return hoge;
}

static inline bool increment_resistor(RESISTOR *r){
	r->series++;
	if(r->series >= resistor_series_size){
		r->exponetial++;
		r->series = 0;
		if(r->exponetial > max_exponetial)return true;
	}
	return false;
}

static inline double calc_partial_voltage(const RESISTOR upside, const RESISTOR downside, const double suppry_voltage){
	return calc_resistor_value(downside) / (calc_resistor_value(downside) + calc_resistor_value(upside)) * suppry_voltage;
}

static inline bool compare_resistor(const RESISTOR a, const RESISTOR b){
	if((a.exponetial == b.exponetial) && (a.series == b.series))return true;
	else return false;
}

void voltage_divider_solver(double *upside_resistor, double *downside_resistor, const double suppry_voltage, const double target_voltage){

	RESISTOR upside = {0, 0}, downside = {0, 0};
	RESISTOR upside_best = {0, 0}, downside_best = {0, 0};

	while(1){

		double tmp_voltage = calc_partial_voltage(upside, downside, suppry_voltage);

		if(tmp_voltage < target_voltage){
			if(increment_resistor(&downside))break;
		}else if(tmp_voltage > target_voltage){
			if(increment_resistor(&upside))break;
		}else{
			break;
		}

		if(fabs(target_voltage - calc_partial_voltage(upside, downside, suppry_voltage)) <
				fabs(target_voltage - calc_partial_voltage(upside_best, downside_best, suppry_voltage))){
			downside_best = downside;
			upside_best = upside;
		}

		if(compare_resistor(upside, (RESISTOR){upside_best.series, upside_best.exponetial + 1}) 
				&& compare_resistor(upside, (RESISTOR){upside_best.series, upside_best.exponetial + 1}))
			break;

	}

	*upside_resistor = calc_resistor_value(upside_best);
	*downside_resistor = calc_resistor_value(downside_best);

}


