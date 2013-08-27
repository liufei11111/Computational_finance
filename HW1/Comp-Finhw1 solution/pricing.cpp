/*
 * pricing.cpp
 *
 *  Created on: Sep 16, 2012
 *      Author: Carlos J Arguello - Columbia University - cja2119
 */

#include <iostream>
#include <vector>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_cdf.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_rng.h>
#include "pricing.h"

using namespace std;

void closed_formula_pricing::black_scholes_formula_pricing() {

	double d1=0, d2=0, Call_T=0, Put_T=0, cdf_d1, cdf_neg_d1, cdf_d2, cdf_neg_d2;
	// cdf = cumulant density function

	d1=(log(initial_stock_price/strike_price)+(return_rate-dividend_yield+0.5*pow(volatility,2))
			*maturity_time)/(volatility*sqrt(maturity_time));
	d2=d1-volatility*sqrt(maturity_time);

	cdf_d1 = gsl_cdf_ugaussian_P (d1);
	cdf_neg_d1 = gsl_cdf_ugaussian_P (-d1);
	cdf_d2 = gsl_cdf_ugaussian_P (d2);
	cdf_neg_d2 = gsl_cdf_ugaussian_P (-d2);

	Call_T=initial_stock_price*exp(-dividend_yield*maturity_time)*cdf_d1-
			strike_price*exp(-return_rate*maturity_time)*cdf_d2;

	Put_T=strike_price*exp(-return_rate*maturity_time)*cdf_neg_d2-
			initial_stock_price*exp(-dividend_yield*maturity_time)*cdf_neg_d1;

	cout << "Call price is   " << Call_T << endl;
	cout << "Put price is   " << Put_T << endl;
}


void monte_carlo_pricing::exact_solution() {

	double Call_T=0, Put_T=0, wiener_t=0, Price_path_T=0;
	int paths=0;

	// Preparing gsl to generate pseudo random numbers
	const gsl_rng_type * R;
	gsl_rng * r;
	gsl_rng_env_setup();
	R = gsl_rng_default;
	r = gsl_rng_alloc(R);
	//

	for (paths=0; paths<number_of_paths ; paths++) {
		wiener_t=gsl_ran_gaussian(r, 1);
		Price_path_T=initial_stock_price*exp((return_rate-dividend_yield-0.5*pow(volatility,2))+
				volatility*sqrt(maturity_time)*wiener_t)-strike_price;
		if (Price_path_T > 0) {
			Call_T+= exp(-(return_rate-dividend_yield))*Price_path_T/number_of_paths;
		}
		else {
			Put_T+= exp(-(return_rate-dividend_yield))*(-Price_path_T)/number_of_paths ;
		}
	}
	cout << "Call price " << Call_T << endl;
	cout << "Put price  " << Put_T << endl;
}


void monte_carlo_pricing::euler_solver(int log_euler_flag) {

	double Call_T=0, Put_T=0, wiener_t=0, Stock_T=0, log_Stock_T=0, Price_path_T=0;
	int time_counter=0, paths=0;

	// Preparing gsl to generate pseudo random numbers
	const gsl_rng_type * R;
	gsl_rng * r;
	gsl_rng_env_setup();
	R = gsl_rng_default;
	r = gsl_rng_alloc(R);
	//

	for (paths=0; paths<number_of_paths ; paths++) {
		if (log_euler_flag==0) {  // If the flag =1 it uses log_S_T for the dynamics, otherwise, S_T

			Stock_T=initial_stock_price;
			for (time_counter = 0; time_counter<time_divisions ; time_counter++) {
				wiener_t=gsl_ran_gaussian(r, 1);
				Stock_T+=Stock_T*((return_rate-dividend_yield)*(maturity_time/time_divisions)+
						sqrt(maturity_time/time_divisions)*volatility*wiener_t);
			}
			Price_path_T=Stock_T-strike_price;
		}

		else {
			log_Stock_T=log(initial_stock_price);
				for (time_counter = 0; time_counter<time_divisions ; time_counter++) {
					wiener_t=gsl_ran_gaussian(r, 1);
					log_Stock_T+=((return_rate-dividend_yield-pow(volatility,2)*0.5)*
							(maturity_time/time_divisions)+sqrt(maturity_time/time_divisions)*volatility*wiener_t);
				}
			Price_path_T=exp(log_Stock_T)-strike_price;
		}

		if (Price_path_T > 0) {
			Call_T+= exp(-(return_rate-dividend_yield))*Price_path_T/number_of_paths;
		}
		else {
			Put_T+=exp(-(return_rate-dividend_yield))*(-Price_path_T)/number_of_paths;
		}
	}
	cout << "Call price " << Call_T << endl;
	cout << "Put price " << Put_T << endl;
}


void monte_carlo_pricing::milstein() {

	double Call_T=0, Put_T=0, wiener_t=0, Stock_T=0, Price_path_T=0;
	int time_counter=0, paths=0;

	// Preparing gsl to generate pseudo random numbers
	const gsl_rng_type * R;
	gsl_rng * r;
	gsl_rng_env_setup();
	R = gsl_rng_default;
	r = gsl_rng_alloc(R);
	//

	for (paths=0; paths<number_of_paths ; paths++) {

		Stock_T=initial_stock_price;
		for (time_counter = 0; time_counter<time_divisions ; time_counter++) {
			wiener_t=gsl_ran_gaussian(r, 1);
			Stock_T+=Stock_T*((return_rate-dividend_yield)*(maturity_time/time_divisions)+
					sqrt(maturity_time/time_divisions)*volatility*wiener_t+
						0.5*volatility*(pow(wiener_t,2)-1)*(maturity_time/time_divisions));
		}
		Price_path_T=Stock_T-strike_price;
		if (Price_path_T > 0) {
			Call_T+= exp(-(return_rate-dividend_yield))*Price_path_T/number_of_paths;
		}
		else {
			Put_T+=exp(-(return_rate-dividend_yield))*(-Price_path_T)/number_of_paths;
		}
	}
	cout << "Call price " << Call_T << endl;
	cout << "Put price " << Put_T << endl;
}
