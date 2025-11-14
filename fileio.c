#include <stdio.h>
#include <fileio.h>

void load_data(const char*filename, float* x,float* y,int* n)
{
    FILE *file = filename;
    if(!file)
    {
        printf("Error: Could not open data file.\n");
        return;
    }

    *n =0;
    while(fscanf(file, "%f %f", &x[*n],&y[*n]) == 2)
    {
        *n++;
    }
    fclose(file);
}

void load_weights(const char*filename,Model* model)
{
    FILE *file = filename;
    if(!file)
    {
        printf("Weights file not found, initializing random weights.\n");
        model->w = 0.0f;
        model->b = 0.0f;
        return;
    }
    fscanf(file,"%f %f",&model->w,&model->b);
    fclose(file);
}

void save_weights(const char*filename,Model model)
{
    FILE* file = filename;
    if(!file)
    {
        printf("Error: Could not open weights file for writing.\n");
        return;
    }
    fprintf(file,"%f %f\n",model.w,model.b);
}