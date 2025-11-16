//regression.h

#ifndef REGRESSION_H
#define REGRESSION_H
typedef struct{
    float w;
    float b;
}Model;
void train(Model *model,float *x,float *y,int n,float lr,int epochs);
float predict(Model model,float x);
float compute_loss(Model model,float *x,float *y,int n);
void ascii_plot(float *x, float *y, int n, Model model);

#endif