#include <stdio.h>
#include "regression.h"

float predict(Model model, float x)
{
    return (model.w)*x + model.b;
}

float compute_loss(Model model, float *x, float *y, int n)
{
    float loss = 0.0f;
    for(int i=0;i<n;i++)
    {
        float y_pred = predict(model,x[i]);
        float diff = y_pred - y[i];
        loss += diff*diff;
    }
    return loss/n;
}
void train(Model *model,float *x,float *y,int n,float lr,int epochs)
{
    for(int e=0;e<epochs;e++)
    {
        float dw = 0.0f,db =0.0f;
        for(int i = 0;i<n;i++)
        {
            float y_pred = predict(*model,x[i]);
            float error = y_pred-y[i];
            dw += error * x[i];
            dw += error;
        }
        dw /= n;
        db /= n;
        model->w-=lr*dw;
        model->b-=lr*db;
        if(e%100==0){
            float loss=compute_loss(*model,x,y,n);
            printf("Epoch %d | Loss: %.4f | w: %.4f | b: %.4f\n", e, loss, model->w, model->b);
        }
    }
}
