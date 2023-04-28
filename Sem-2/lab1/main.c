#include <time.h>
#include "libs/matrix.h"
#include "libs/IO/logger.h"
#include "libs/UI/menus.h"

int main() {
    srand((unsigned int)time(NULL));

    error* err = error_ctor();

    int action = 0;
    while (action != 1) {
        if (err->raised) {
            log_error(err);
            error_clear(err);
            go_back();
        }
        switch (action) {
            case 0:
                action = main_menu();
                break;
            case 2:
                transpose_menu(err);
                action = 0;
                break;
            case 3:
                add_matrix_to_matrix_menu(err);
                action = 0;
                break;
            case 4:
                add_scalar_to_matrix_menu(err);
                action = 0;
                break;
            case 5:
                multiply_matrices_menu(err);
                action = 0;
                break;
            case 6:
                multiply_matrix_by_scalar_menu(err);
                action = 0;
                break;
            case 7:
                linear_combination_of_rows_menu(err);
                action = 0;
                break;
            default:
                log_red("invalid action!\n");
                action = 0;
                break;
        }
    }

    error_dtor(err);

    return 0;
}
