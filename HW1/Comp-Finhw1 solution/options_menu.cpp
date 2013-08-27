/*
 * options_menu.cpp
 *
 *  Created on: Sep 13, 2012
 *      Author: Carlos J Arguello - Columbia University - cja2119
 */

#include <iostream>

using namespace std;

char menu()
{
  const char *options[] = {
    "(c) closed formula pricing",
    "(s) single step SDE pricing",
    "(e) Euler pricing",
    "(l) Euler log spot pricing",
    "(m) Milstein pricing",
    "(q) quit",
    0
  };
  char ret;

  for (const char **p = options; *p != 0; p++)
  cout<< *p <<'\n';
  cout<<"Selection: ";
  cin >> ret;
  cin.ignore(cin.rdbuf()->in_avail());
  return ret;

  }
