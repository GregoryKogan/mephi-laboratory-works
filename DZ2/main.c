#include <stdio.h>
#include <math.h>


double calc_epsilon(int precision);
double iterative_sin(double x, double epsilon);
int get_user_input(double* x, int* precision);


int main() {
    double x;
    int precision;
    int status = get_user_input(&x, &precision);
    if (status != 0) return status;

    printf("epsilon         = %.*f\n", precision, calc_epsilon(precision));
    double sin_x = iterative_sin(x, calc_epsilon(precision));
    double math_sin_x = sin(x);
    printf("math.h's sin(x) = %.*f\n", precision, math_sin_x);
    printf("my sin(x)       = %.*f\n", precision, sin_x);
    printf("Error: %.*f\n", precision, fabs(sin_x - math_sin_x));

    return 0;
}


double calc_epsilon(int precision) {
    return 1 / pow(10.0, (double)precision);
}

double iterative_sin(double x, double epsilon) {
    double result = 0;
    double term = 0, next_term = x;
    int n = 1;
    do {
        n++;
        term = next_term;
        result += term;
        next_term = (term * (-1) * x * x) / ((2 * n - 2) * (2 * n - 1));
    } while (fabs(term - next_term) > epsilon);
    return result;
}

int get_user_input(double* x, int* precision) {
    printf("Input x: ");
    if (scanf("%lf", x) != 1) {
        printf("Error: Invalid input\n");
        return 1;
    }

    printf("How many decimal places do you need?\nInput precision [0, 14]: ");
    if (scanf("%d", precision) != 1) {
        printf("Error: Invalid input\n");
        return 1;
    }
    if (*precision < 0) {
        printf("Error: Precision should be at least 0\n");
        return 2;
    } else if (*precision > 14) {
        printf("Error: Precision above 14 may lead to unpredictable results\n");
        return 2;
    }

    while (*x > 2 * M_PI) {*x -= 2 * M_PI; }
    while (*x < (-2) * M_PI) {*x += 2 * M_PI; }

    return 0;
}

