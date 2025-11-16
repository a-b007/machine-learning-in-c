#include <stdio.h>
#include "regression.h"

#define WIDTH 90
#define HEIGHT 30

void ascii_plot(float *x, float *y, int n, Model model)
{
    char grid[HEIGHT][WIDTH];

    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
            grid[i][j] = ' ';

    float min_x = x[0], max_x = x[0];
    float min_y = y[0], max_y = y[0];

    for (int i = 1; i < n; i++) {
        if (x[i] < min_x) min_x = x[i];
        if (x[i] > max_x) max_x = x[i];
        if (y[i] < min_y) min_y = y[i];
        if (y[i] > max_y) max_y = y[i];
    }

    float x_range = (max_x - min_x) * 1.1f;
    float y_range = (max_y - min_y) * 1.1f;

    
    for (int i = 0; i < n; i++) {
        int col = (int)((x[i] - min_x) / x_range * (WIDTH - 1));
        int row = (int)((y[i] - min_y) / y_range * (HEIGHT - 1));
        row = HEIGHT - 1 - row; 

        if (row >= 0 && row < HEIGHT && col >= 0 && col < WIDTH)
            grid[row][col] = '*';
    }

    
    for (int col = 0; col < WIDTH; col++) {
    
        float x_val = min_x + (col / (float)(WIDTH - 1)) * x_range;
        float y_pred = model.w * x_val + model.b;

        int row = (int)((y_pred - min_y) / y_range * (HEIGHT - 1));
        row = HEIGHT - 1 - row;

        if (row >= 0 && row < HEIGHT && grid[row][col] == ' ')
            grid[row][col] = '-';
    }


    for (int i = 0; i < HEIGHT; i++) {
    printf("| ");
    for (int j = 0; j < WIDTH; j++) {

        if (grid[i][j] == '*') {
            
            printf("\033[33m*\033[0m");
        }
        else if (grid[i][j] == '-') {
            
            printf("\033[36m-\033[0m");
        }
        else {
            // Background
            printf(" ");
        }
    }
    printf(" |\n");
}

}

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
            db += error;
        }
        dw /= n;
        db /= n;
        model->w-=lr*dw;
        model->b-=lr*db;
        if(e%100==0){
            float loss=compute_loss(*model,x,y,n);
            printf("Epoch %d | Loss: %.4f | w: %.4f | b: %.4f\n", e, loss, model->w, model->b);
        }
        if (e % 400 == 0)
        {
            printf("\nEpoch %d plot:\n", e);
            ascii_plot(x, y, n, *model);
        }

    }
}
