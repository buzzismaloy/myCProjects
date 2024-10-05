#include <stdio.h>
#include <stdlib.h>

void add();
void subtract();
void matrix_mult();
void mult_by_scalar();
void print_transposed();
void print_inverse();
void print_determinant();
void print_matrix_trace();
void quit();

void print_matrix(int rows, int cols, double* matrix);
void read_matrix(int rows, int cols, double* matrix);
void clear_input();
void print_menu();
void process_choice(int choice);
void read_matrix_size(int* rows, int* cols);
double* allocate_memory(int rows, int cols);
void get_minor_matrix(double* matrix, double* temp, int row, int col, int size);
double get_determinant(double* matrix, int size);
void make_transposed(double* matrix, double* matrix_T, int rows, int cols);
void get_cofactor_matrix(double* matrix, double* cofactor, int size);
double get_matrix_trace(double* matrix, int size);

int main(){
    int choice = 0;
    while(1){
        print_menu();
        int result = scanf("%d", &choice);
        if(result == 1){
            process_choice(choice);
        }
        else{
            printf("Wrong input type!\n\n");
            clear_input();
        }
    }
    return 0;
}

void quit(){
    printf("\x1b[2JGoodbye!\n\n");
    exit(0);
}

double* allocate_memory(int rows, int cols){
    double* matrix = (double*)malloc(rows * cols * sizeof(double));
    if(matrix == NULL){
        printf("Failed to allocate memory!\n");
        exit(1);
    }

    return matrix;
}

void read_matrix_size(int* rows, int* cols){
    printf("Enter the number of rows:\n");
    while(scanf("%d", rows) != 1 || *rows <= 0){
        clear_input();
        printf("Invalid input!\n\n");
    }
    clear_input();

    printf("Enter the number of columns:\n");
    while(scanf("%d", cols) != 1 || *cols <= 0){
        clear_input();
        printf("Invalid input!\n\n");
    }
    clear_input();
}

void read_matrix(int rows, int cols, double* matrix){
    printf("Please, fill in the matrix:\n");
    printf("Enter a matrix %d*%d in the following format: numb_1 numb_2 and so on\n\n", rows, cols);
    for(int i = 0; i < rows; ++i){
        for(int j = 0; j < cols; ++j){
            while(scanf("%lf", &matrix[i * cols + j]) != 1){
                printf("Wrong input!\n\n");
                clear_input();
            }     
        }
    }

    clear_input();
    printf("\n");
}

void print_matrix(int rows, int cols, double* matrix){
    for(int i = 0; i < rows; ++i){
        for(int j = 0; j < cols; ++j){
            printf("%6.1lf ", matrix[i * cols + j]);
        }
        printf("\n");
    }
}

void print_menu(){
    printf("Choose one of these operations with matrices by entering the number of operation:\n");
    printf("1)Adding\n2)Subtraction\n3)Matrix multiplication\n4)Multiplying a matrix by a scalar\n");
    printf("5)Matrix transposition\n6)Print matrix determinant\n7)Print inverted matrix\n8)Print matrix trace\n");
    printf("0)Quit\n\n");
}

void clear_input(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

void process_choice(int choice){
    switch(choice){
        case 1:
            add();
            break;
        case 2:
            subtract();
            break;
        case 3:
            matrix_mult();
            break;
        case 4:
            mult_by_scalar();
            break;
        case 5:
            print_transposed();
            break;
        case 6:
            print_determinant();
            break;
        case 7:
            print_inverse();
            break;
        case 8:
            print_matrix_trace();
            break;
        case 0:
            quit();
            break;
        default:
            printf("Choose only suggested options!\n\n");   
    }
}

void add(){
    int rows, cols;
    read_matrix_size(&rows, &cols);

    double* a = allocate_memory(rows, cols);
    double* b = allocate_memory(rows, cols);
    double* result = allocate_memory(rows, cols);

    read_matrix(rows, cols, a);
    read_matrix(rows, cols, b);

    for(int i = 0; i < rows; ++i){
        for(int j = 0; j < cols; ++j){
            result[i * cols + j] = a[i * cols + j] + b[i * cols + j];
        }
    }

    printf("\n\nMatrix A:\n\n");
    print_matrix(rows, cols, a);
    printf("\n\nMatrix B:\n\n");
    print_matrix(rows, cols, b);
    printf("\n\nResult matrix:\n\n");
    print_matrix(rows, cols, result);
    printf("\n\n");

    free(a);
    free(b);
    free(result);
}

void subtract(){
    int rows, cols;
    read_matrix_size(&rows, &cols);

    double* a = allocate_memory(rows, cols);
    double* b = allocate_memory(rows, cols);
    double* result = allocate_memory(rows, cols);

    read_matrix(rows, cols, a);
    read_matrix(rows, cols, b);

    for(int i = 0; i < rows; ++i){
        for(int j = 0; j < cols; ++j){
            result[i * cols + j] = a[i * cols + j] - b[i * cols + j];
        }
    }

    printf("\n\nMatrix A:\n\n");
    print_matrix(rows, cols, a);
    printf("\n\nMatrix B:\n\n");
    print_matrix(rows, cols, b);
    printf("\n\nResult matrix:\n\n");
    print_matrix(rows, cols, result);
    printf("\n\n");

    free(a);
    free(b);
    free(result);
}

void matrix_mult(){
    int rows_1, cols_1;
    int rows_2, cols_2;

    printf("Please enter sizes of the first matrix:\n");
    read_matrix_size(&rows_1, &cols_1);
    printf("Please enter sizes of the second matrix:\n");
    read_matrix_size(&rows_2, &cols_2);

    if(cols_1 != rows_2){
        printf("Multiplication is not possible\n\n");
        return;
    }

    double* a = allocate_memory(rows_1, cols_1);
    double* b = allocate_memory(rows_2, cols_2);
    double* result = allocate_memory(rows_1, cols_2);

    read_matrix(rows_1, cols_1, a);
    read_matrix(rows_2, cols_2, b);

    for(int i = 0; i < rows_1; ++i){
        for(int j = 0; j < cols_2; ++j){
            result[i * cols_2 + j] = 0.0;
        }
    }

    for(int i = 0; i < rows_1; ++i){
        for(int j = 0; j < cols_2; ++j){
            for(int k = 0; k <  cols_1; ++k){
                result[i * cols_2 + j] += a[i * cols_1 + k] * b[k * cols_2 + j];
            }
        }
    }

    printf("\n\nMatrix A:\n\n");
    print_matrix(rows_1, cols_1, a);
    printf("\n\nMatrix B:\n\n");
    print_matrix(rows_2, cols_2, b);
    printf("\n\nResult matrix:\n\n");
    print_matrix(rows_1, cols_2, result);
    printf("\n\n");
    
    free(a);
    free(b);
    free(result);
}

void mult_by_scalar(){
    int rows, cols, result;
    double scalar;
    read_matrix_size(&rows, &cols);

    printf("Please, enter the number by which you want to multiply the matrix:\n");
    result = scanf("%lf", &scalar);
    if(!result){
        printf("Invalid input!\n\n");
        clear_input();
        return;
    }

    double* matrix = allocate_memory(rows, cols);
    read_matrix(rows, cols, matrix);

    printf("\n\nOriginal matrix:\n\n");
    print_matrix(rows, cols, matrix);

    for(int i = 0; i < rows; ++i){
        for(int j = 0; j < cols; ++j){
            matrix[i * cols + j] = matrix[i * cols + j] * scalar;
        }
    }
    
    printf("\n\nMatrix multiplied by %.1lf:\n\n", scalar);
    print_matrix(rows, cols, matrix);
    printf("\n\n");

    free(matrix);
}

void make_transposed(double* matrix, double* matrix_T, int rows, int cols){
        for(int i = 0; i < rows; ++i){
        for(int j = 0; j < cols; ++j){
            matrix_T[j * rows + i] = matrix[i * cols + j];
        }
    }
}

void print_transposed(){
    int rows, cols;
    read_matrix_size(&rows, &cols);

    double* a = allocate_memory(rows, cols);
    double* a_T = allocate_memory(cols, rows);
    
    read_matrix(rows, cols, a);
    make_transposed(a, a_T, rows, cols);

    printf("The original matrix:\n\n");
    print_matrix(rows, cols, a);
    printf("\n\nTransposed matrix:\n\n");
    print_matrix(cols, rows, a_T);
    printf("\n\n");

    free(a);
    free(a_T);
}

void get_minor_matrix(double* matrix, double* temp, int row, int col, int size){
    int p = 0, q = 0;

    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(i != row && j != col){
                temp[p * (size - 1) + q++] = matrix[i * size + j];
                if(q == size - 1){
                    q = 0;
                    p++;
                }
            }
        }
    }
}

double get_determinant(double* matrix, int size){
    if(size == 1)
        return matrix[0];
    
    double det = 0;
    int sign = 1;
    double* temp = allocate_memory(size - 1, size - 1);

    for(int f = 0; f < size; ++f){
        get_minor_matrix(matrix, temp, 0, f, size);
        det += sign * matrix[0 * size + f] * get_determinant(temp, size - 1);
        sign = -sign;
    }

    free(temp);

    return det;
}

void print_determinant(){
    int dimension, result;
    printf("Please, enter the dimension of the matrix:\n");
    result = scanf("%d", &dimension);
    if(!result || dimension <= 0){
        printf("Invalid input!\n\n");
        clear_input();
        return;
    }

    double* matrix = allocate_memory(dimension, dimension);
    read_matrix(dimension, dimension, matrix);

    printf("Your matrix:\n\n");
    print_matrix(dimension, dimension, matrix);
    printf("\n\n");

    double det = get_determinant(matrix, dimension);
    printf("Matrix determinant equals to %6.2lf\n\n", det);

    free(matrix);  
}

void get_cofactor_matrix(double* matrix, double* cofactor, int size){
    double* minor = allocate_memory(size - 1, size - 1);

    for(int i = 0; i < size; ++i){
        for(int j = 0; j < size; ++j){
            get_minor_matrix(matrix, minor, i, j, size);
             cofactor[i * size + j] = ((i + j) % 2 == 0 ? 1 : -1) * get_determinant(minor, size - 1);
        }
    }

    free(minor);
}

void print_inverse(){
    int dimension, result;
    printf("Please, enter the dimension of the matrix:\n");
    result = scanf("%d", &dimension);
    if(!result || dimension <= 0){
        printf("Invalid input!\n\n");
        clear_input();
        return;
    }

    double* matrix = allocate_memory(dimension, dimension);
    read_matrix(dimension, dimension, matrix);

    double det = get_determinant(matrix, dimension);
    if(det == 0){
        printf("The matrix is singular and doesn't have an inverse.\n");
        free(matrix);
        return;
    }
    
    double* cofactor = allocate_memory(dimension, dimension);
    get_cofactor_matrix(matrix, cofactor, dimension);

    double* transposed = allocate_memory(dimension, dimension);
    make_transposed(cofactor, transposed, dimension, dimension);

    double* inverse = allocate_memory(dimension, dimension);

    for(int i = 0; i < dimension; ++i){
        for(int j = 0; j < dimension; ++j){
            inverse[i * dimension + j] = transposed[i * dimension + j] / det;
        }
    }
    
    printf("\nOriginal matrix:\n\n");
    print_matrix(dimension, dimension, matrix);
    printf("\n\nInversed matrix:\n\n");
    print_matrix(dimension, dimension, inverse);
    printf("\n\n");

    free(matrix);
    free(cofactor);
    free(transposed);
    free(inverse);
}

double get_matrix_trace(double* matrix, int size){
    double trace = 0.0;
    
    for(int i = 0; i < size; ++i){
        trace += matrix[i * size + i];
    }

    return trace;
}

void print_matrix_trace(){
    int size, result;
    printf("Please, enter the dimension of the matrix:\n");
    result = scanf("%d", &size);
    if(!result || size <= 0 ){
        printf("Invalid input!\n\n");
        clear_input();
        return;
    }

    double* matrix = allocate_memory(size, size);
    read_matrix(size, size, matrix);

    double trace = get_matrix_trace(matrix, size);

    printf("Your matrix:\n\n");
    print_matrix(size, size, matrix);
    printf("\n\n");

    printf("Matrix trace equals to %6.2lf\n\n", trace);

    free(matrix);
}