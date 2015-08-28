#include "retard_neurone.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>   

double phi(double z){
  double result = 1. + pow(2.7183,-z);
    result = 1. / result;
    return result;
}


int * expected(int n){
  int * result = malloc(2 * sizeof(int));
  if(n % 2){
    result[0] = 0;
    result[1] = 1;
  }
  else{
    result[0] = 1;
    result[1] = 0;
  }
  return result;
}


double * output(struct network network, int n){
  double * result = malloc(sizeof(double) * (HIDDEN + OUTPUT));

  for(int i=0;i < HIDDEN;i++){
    result[i] = phi(network.hidden_neurones[i] * n);
  }

  for(int i = 0; i < OUTPUT;i++){
    double sum = 0;
    for(int j = 0;j < HIDDEN;j++){
      sum += result[j] * network.output_neurones[i].weight[j];
    }
    result[HIDDEN + i] = phi(sum);
  }
  return result;
}


void adjust(struct network * network, double * output, int * expected, int n){
  
  double delta_output[OUTPUT];
  double delta_hidden[HIDDEN];
  
  /* compute errors */
  for(int i = 0;i < OUTPUT;i++){
    double o = output[HIDDEN + i];
    delta_output[i] = o * (1 - o) * (((double) expected[i]) - o);
  }

  for(int i = 0;i < HIDDEN;i++){
    double h = output[i];
    double sum = 0;
    for(int j = 0;j < OUTPUT;j++){
      sum += delta_output[j] * network->output_neurones[j].weight[i];
    }
    // printf("h:%f sum:%f\n",h,sum);
    delta_hidden[i] = h * (1 - h) * sum;
  }

  /* change weights in network */
  for(int i = 0;i < OUTPUT;i++){
    for(int j = 0;j < HIDDEN;j++){
      network->output_neurones[i].weight[j] += ETA * delta_output[i] * output[j];
    }
  }
  
  for(int j = 0;j < HIDDEN;j++){
    network->hidden_neurones[j] += ETA * delta_hidden[j] * n;
  }

}
 

void network_ini(struct network * network){
  srand(time(NULL));
  network->hidden_neurones = malloc(HIDDEN * sizeof(double));
  network->output_neurones = malloc(OUTPUT * sizeof(struct neurone));
  for(int i=0;i < HIDDEN;i++){
    double r = rand() % 10000 / 20000.0;
    if(rand() % 2)
      r = -r;
    network->hidden_neurones[i] = r;
  }
  
  for(int j=0;j < OUTPUT;j++){
    for(int i=0;i < HIDDEN;i++){
      double r = rand() % 10000 / 20000.0;
      if(rand() % 2)
	r = -r;
      network->output_neurones[j].weight[i] = r;
    }

  }


}
void network_print(struct network * network){

  printf("HIDDEN:\n");
  for(int i = 0; i < HIDDEN;i++){
    printf("weight: %f\n",network->hidden_neurones[i]);
  }
  printf("OUTPUT\n");
  for(int i = 0; i < OUTPUT;i++){
    printf("\tnum: %d\n", i);
    for(int j = 0; j < HIDDEN;j++){
      printf("\t\tweight: %f\n",network->output_neurones[i].weight[j]);
    }
  }

}


int main(int argc, char ** argv){
  struct network network;
  network_ini(&network);
  int n;
  double * out;
  int * expect;

   printf("BEFORE TRAINING\n");
  network_print(&network);
  /* training phase */

  for(int i = 0;i < TRAINING;i++){
    n = rand() %100;
    out = output(network,n);
    expect = expected(n);
    adjust(&network, out, expect, n);
    free(out);
    free(expect);
  }

  printf("AFTER TRAINING\n");
  network_print(&network);
  
  /* demonstration of the bot wonderful skills */

  /*for(int i = 0;i < 100;i++){
    out = output(network,i);
    if(out[HIDDEN] > out[HIDDEN + 1]){
      printf("%d number is even\n",i);
    }
    else{
      printf("%d is odd\n",i);
    }
    free(out);


    }*/
  
    while(1){

    printf("PLEASE ENTER A NUMBER:\n");

    scanf("%d\n",&n);
    out = output(network,n);
    if(out[HIDDEN] > out[HIDDEN + 1]){
      printf("Your number is even\n");
    }
    else{
      printf("Your number is odd\n");
    }
    free(out);
    }
  return 0;
}



