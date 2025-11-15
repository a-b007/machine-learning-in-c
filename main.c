#include <stdio.h>
#include "regression.h"
#include "fileio.h"

#define max 100

int main() {
    float x[max], y[max];
    int n = 0;
    Model model;
    float learning_rate = 0.01f;
    int epochs = 1000;

    load_data("data.txt", x, y, &n);
    load_weights("weights.txt", &model);

    printf("Starting training with initial weight=%.2f, bias=%.2f\n", model.w, model.b);
    train(&model, x, y, n, learning_rate, epochs);

    save_weights("weights.txt", model);
    printf("\nTraining complete. Saved weights: weight=%.4f, bias=%.4f\n", model.w, model.b);

    float test_x;
    printf("\nEnter a value of x to predict y: ");
    scanf("%f", &test_x);
    printf("Predicted y = %.2f\n", predict(model, test_x));

    return 0;
}