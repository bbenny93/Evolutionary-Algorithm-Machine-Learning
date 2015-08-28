#include <stdio.h>
#include <stdlib.h>
#define TRAINING 1000
#define HIDDEN 3
#define OUTPUT 2
#define ETA 42
#define BIAS 20


struct neurone{
  double weight[HIDDEN];
};


struct network{
  double * hidden_neurones;
  struct neurone  * output_neurones;
};


double phi(double z);
int * expected(int n);
double * output(struct network network, int n);
void adjust(struct network * network, double * output, int * expected, int n);
