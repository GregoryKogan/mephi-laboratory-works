#include <stdio.h>
#include <math.h>


float iterative_asinh(float x, int iters);
int get_user_input(float* x, int* iters);


int main() {
    float x;
    int iters;
    int status = get_user_input(&x, &iters);
    if (status != 0) return status;

    float asinh_x = iterative_asinh(x, iters);
    float math_asinh_x = asinh(x);
    printf("math.h's asinh(x) = %f\n", math_asinh_x);
    printf("my asinh(x)       = %f\n", asinh_x);
    printf("Error: %.f\n", fabs(asinh_x - math_asinh_x));

    return 0;
}


float iterative_asinh(float x, int iters) {
    float result = 0;
    float term = 0, next_term = x;
    for (int n = 1; n <= iters; ++n) {
        term = next_term;
        result += term;
        next_term = term * (-1) * (2 * n - 1) * (2 * n) 
                    / 4 / (n * n) * (2 * (n - 1) + 1) / (2 * n + 1) * x * x;
    }
    return result;
}

int get_user_input(float* x, int* iters) {
    printf("Input x (-1, 1): ");
    if (scanf("%f", x) != 1) {
        printf("Error: Invalid input\n");
        return 1;
    }

    if (!(fabs(*x) < 1)) {
        printf("x should be between -1 and 1!\n");
        return 2;
    }

    printf("How many caclucaltion iterations do you need?: ");
    if (scanf("%d", iters) != 1) {
        printf("Error: Invalid input\n");
        return 1;
    }
    if (*iters < 0) {
        printf("Error: There should be at least 0 iterations\n");
        return 2;
    }

    return 0;
}
