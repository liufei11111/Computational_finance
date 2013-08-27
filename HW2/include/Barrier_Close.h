#ifndef __BARRIER_CLOSE_H__
#define __BARRIER_CLOSE_H__
#include <cmath>
struct Option {double Strike; double Expiry; double Rate; double Vol;double Barrier;double spot;};
double d(Option);
double value(Option);
#endif