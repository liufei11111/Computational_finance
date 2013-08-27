/*
 * main.cpp
 *
 *  Created on: Sep 13, 2012
 *      Author: Carlos J Arguello - Columbia University - cja2119
 *  Homework 1 Computational Finance. Pricing options using simple Monte Carlo
 */

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "options_menu.h"
#include "pricing.h"

using namespace std;

int selection(closed_formula_pricing european_option_CF, monte_carlo_pricing european_option_MC) {
	cout<<"Selection menu:  ="<< "\n" << endl;
	char opt;
	while ((opt = menu()) != 'q') {
    	switch (opt) {
     		case 'c' : { cout<<"Option price using closed-form formula ="<<endl;
				european_option_CF.black_scholes_formula_pricing();
				cout << string(2, '\n');
				break;
						}
      		case 's' : { cout<<"Option price using single-step exact SDE solution ="<<endl;
				european_option_MC.exact_solution();
				cout << string(2, '\n');
				break;
						}
      		case 'e' : { cout<<"Option price using Euler numerical solution of SDE for spot =" <<endl;
				int log_euler_flag=0;
				european_option_MC.euler_solver(log_euler_flag);
				cout << string(2, '\n');
				break;
						}
      		case 'l' : { cout<<"Option price using Euler numerical solution of SDE for log spot =" <<endl;
				int log_euler_flag=1;
				european_option_MC.euler_solver(log_euler_flag);
				cout << string(2, '\n');
				break;
						}
      		case 'm' : { cout<<"Option price using Milstein numerical solution of SDE for spot =" <<endl;
				european_option_MC.milstein();
				cout << string(2, '\n');
				break;
						}
      		case 'q': {
				return 0; }
      		default: cout<<"Invalid option"<<endl; cout << string(2, '\n'); break;
    	}
	}
}


int main() {
	closed_formula_pricing european_option_CF;  // Define object of class "closed_formula_pricing"
	monte_carlo_pricing european_option_MC;     // Define object of class "monte_carlo_pricing"
	double volatility, dividend_yield, initial_stock_price, return_rate, strike_price, maturity_time;
	int time_divisions, number_of_paths;
	cout << " HW1 Solution Computational Finance" << endl;
	cout << " Please input parameters" << endl;
	cout << "Volatility? " << endl;
	cin >> volatility;
	cout << "dividend yield? " << endl;
	cin >> dividend_yield;
	cout << "initial stock price? " << endl;
	cin >> initial_stock_price;
	cout << "return rate? " << endl;
	cin >> return_rate;
	cout << "strike price? " << endl;
	cin >> strike_price;
	cout << "Maturity time (years)? " << endl;
	cin >> maturity_time;

	cout << "Monte Carlo parameters " << endl;
	cout << "Number of paths? " << endl;
	cin >> number_of_paths;
	cout << "Time divisions? " << endl;
	cin >> time_divisions;
	european_option_CF.volatility=volatility;
	european_option_CF.dividend_yield=dividend_yield;
	european_option_CF.initial_stock_price=initial_stock_price;
	european_option_CF.return_rate=return_rate;
	european_option_CF.strike_price=strike_price;
	european_option_CF.maturity_time=maturity_time;
	////
	european_option_MC.number_of_paths=number_of_paths;
	european_option_MC.time_divisions=time_divisions;
	european_option_MC.volatility=volatility;
	european_option_MC.dividend_yield=dividend_yield;
	european_option_MC.initial_stock_price=initial_stock_price;
	european_option_MC.return_rate=return_rate;
	european_option_MC.strike_price=strike_price;
	european_option_MC.maturity_time=maturity_time;
	////
	selection(european_option_CF, european_option_MC); // Show selection menu, and calculate!
	return 0;
}

