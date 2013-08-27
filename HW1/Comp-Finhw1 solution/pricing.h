/*
 * pricing.h
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
#ifndef PRICING_H_
#define PRICING_H_

using namespace std;

class monte_carlo_pricing {
	public:
		int number_of_paths;
		int time_divisions;
		double volatility;
		double initial_stock_price;
		double return_rate;
		double dividend_yield;
		double strike_price;
		double maturity_time;
		void exact_solution();
		void euler_solver(int);
		void milstein();
};

class closed_formula_pricing {
	public:
		double volatility;
		double initial_stock_price;
		double return_rate;
		double dividend_yield;
		double strike_price;
		double maturity_time;
		void black_scholes_formula_pricing();
};
#endif /* PRICING_H_ */
