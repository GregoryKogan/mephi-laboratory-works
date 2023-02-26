#include <stdio.h>
#include <math.h>


float calc_epsilon(int precision);
float iterative_asinh(float x, float epsilon, int* iters);
int get_user_input(float* x, int* precision);
float round_to_dp(float x, int dp);


int main() {
    float x;
    int precision;
    int status = get_user_input(&x, &precision);
    if (status != 0) return status;

    printf("epsilon           = %.*f\n", precision, calc_epsilon(precision));
    int iterations = 0;
    float asinh_x = iterative_asinh(x, calc_epsilon(precision), &iterations);
    float math_asinh_x = asinh(x);
    printf("math.h's asinh(x) = %.*f\n", precision, math_asinh_x);
    printf("my asinh(x)       = %.*f\n", precision, asinh_x);
    printf("Error: %.*f\n", precision, 
            fabs(round_to_dp(asinh_x, precision) - 
                    round_to_dp(math_asinh_x, precision)));
    printf("Iterations: %d\n", iterations); 

    return 0;
}


float calc_epsilon(int precision) {
    return 1 / pow(10.0, (float)precision);
}

float iterative_asinh(float x, float epsilon, int *iters) {
    float result = 0;
    float term = 0, next_term = x;
    int n = 0;
    do {
        n++;
        term = next_term;
        result += term;
        next_term = term * (-1) * (2 * n - 1) * (2 * n) 
                    / 4 / (n * n) * (2 * (n - 1) + 1) / (2 * n + 1) * x * x;
    } while (fabs(term - next_term) > epsilon);
    *iters = n;
    return result;
}

int get_user_input(float* x, int* precision) {
    printf("Input x (-1, 1): ");
    if (scanf("%f", x) != 1) {
        printf("Error: Invalid input\n");
        return 1;
    }

    if (!(fabs(*x) < 1)) {
        printf("x should be between -1 and 1!\n");
        return 2;
    }

    printf("How many decimal places do you need?\nInput precision [0, 5]: ");
    if (scanf("%d", precision) != 1) {
        printf("Error: Invalid input\n");
        return 1;
    }
    if (*precision < 0) {
        printf("Error: Precision should be at least 0\n");
        return 2;
    } else if (*precision > 5) {
        printf("Error: Precision above 5 may lead to unpredictable results\n");
        return 2;
    }

    return 0;
}

float round_to_dp(float x, int dp) {
    float power = pow(10.0, (float)dp);
    return round(x * power) / power;
}
