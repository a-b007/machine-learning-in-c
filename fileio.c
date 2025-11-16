#include <stdio.h>
#include "fileio.h"

void load_data(const char*filename, float* x,float* y,int* n)
{
    FILE *file = fopen(filename, "r");
    if(!file)
    {
        printf("Error: Could not open data file.\n");
        return;
    }

    *n =0;
    while(fscanf(file, "%f %f", &x[*n],&y[*n]) == 2)
    {
        (*n)++;
    }
    if (n == 0) 
    {
        printf("No training data loaded. Exiting.\n");
        return;
    }
    fclose(file);
}

void load_weights(const char*filename, Model* model)
{
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Weights file not found. Initializing to zero.\n");
        model->w = 0.0f;
        model->b = 0.0f;
        return;
    }

    if (fscanf(file, "%f %f", &model->w, &model->b) != 2) {
        printf("Weights file error. Resetting intial weight and bias.\n");
        model->w = 0.0f;
        model->b = 0.0f;
    }

    fclose(file);
}


void save_weights(const char*filename,Model model)
{
    FILE* file = fopen(filename,"w");
    if(!file)
    {
        printf("Error: Could not open weights file for writing.\n");
        return;
    }
    fprintf(file,"%f %f\n",model.w,model.b);
    fclose(file);
}

