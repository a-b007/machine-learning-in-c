#ifndef FILEIO_H
#define FILEIO_H

#include "regression.h"

void load_data(const char* filename, float*x,float*y,int*n );
void load_weights(const char* filename, Model *model);
void save_weights(const char* filename,Model model);




#endif