#include <stdio.h>
#include "regression.h"


#define WIDTH 90
#define HEIGHT 30


#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"
#define RESET   "\033[0m"

void ascii_plot(float *x, float *y, int n, Model model)
{
    char grid[HEIGHT][WIDTH];

   
    // 1. Fill with spaces
    for (int r = 0; r < HEIGHT; r++)
        for (int c = 0; c < WIDTH; c++)
            grid[r][c] = ' ';

    // 2. Compute bounds
    float min_x = x[0], max_x = x[0];
    float min_y = y[0], max_y = y[0];

    for (int i = 1; i < n; i++) {
        if (x[i] < min_x) min_x = x[i];
        if (x[i] > max_x) max_x = x[i];
        if (y[i] < min_y) min_y = y[i];
        if (y[i] > max_y) max_y = y[i];
    }

    float x_range = max_x - min_x;
    float y_range = max_y - min_y;

    if (x_range == 0) x_range = 1.0f;
    if (y_range == 0) y_range = 1.0f;

    x_range *= 1.1f;
    y_range *= 1.1f;

    // 3. Plot data points first
    for (int i = 0; i < n; i++) {
        int col = (int)((x[i] - min_x) / x_range * (WIDTH - 1));
        int row = (int)((y[i] - min_y) / y_range * (HEIGHT - 1));
        row = HEIGHT - 1 - row;

        if (row >= 0 && row < HEIGHT && col >= 0 && col < WIDTH)
            grid[row][col] = 'P';   // data point
    }

    // 4. Plot regression line 
    //    Loop over rows, compute y, invert to X using model: x = (y - b)/w
    for (int row = 0; row < HEIGHT; row++) {

        // Convert the row to y value in data coords
        float y_val = min_y + ((HEIGHT - 1 - row) / (float)(HEIGHT - 1)) * y_range;

        // Compute x on the regression line: y = wx + b → x = (y - b)/w
        float x_val;

        if ((model.w > -0.000001f) && (model.w < 0.000001f))
         {
            continue;
        }
         else {
            x_val = (y_val - model.b) / model.w;
        }

        int col = (int)((x_val - min_x) / x_range * (WIDTH - 1));

        if (col >= 0 && col < WIDTH) {
            if (grid[row][col] == ' ')
                grid[row][col] = 'L';
        }
    }

    // 5. Print grid
    printf("\nRegression Plot:\n");

    for (int r = 0; r < HEIGHT; r++) {
        printf("| ");
        for (int c = 0; c < WIDTH; c++) {

            char cell = grid[r][c];

            if (cell == 'P') {
                printf(YELLOW "*" RESET);
            }
            else if (cell == 'L') {
                printf(CYAN "*" RESET);
            }
            else {
                putchar(' ');
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
