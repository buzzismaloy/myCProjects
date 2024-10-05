#include <stdio.h>
#include <math.h>

typedef struct {
    double real;
    double imag;
} Complex;

Complex add(Complex* a, Complex* b){
    Complex res;
    res.real = a->real + b->real;
    res.imag = a->imag + b->imag;

    return res;
}

Complex subtract(Complex* a, Complex* b){
    Complex res;
    res.real = a->real - b->real;
    res.imag = a->imag - b->imag;

    return res;
}

Complex multiply(Complex* a, Complex* b){
    Complex res;
    res.real = a->real * b->real - a->imag * b->imag;
    res.imag = a->real * b->imag + a->imag * b->real;

    return res;
}

Complex divide(Complex* a, Complex* b){
    Complex res;
    double denominator = b->real * b->real  + b->imag * b->imag;

    if(denominator == 0){
        printf("Error: Division by zero.\n");
        res.real = 0;
        res.imag = 0;
    }
    else{
        res.real = (a->real * b->real + a->imag * b->imag) / denominator;
        res.imag = (a->imag * b->real - a->real * b->imag) / denominator;
    }

    return res;
}

double get_modulus(Complex* a){
    return sqrt(a->real * a->real + a->imag * a->imag);
}

double get_argument(Complex* a){
    return atan2(a->imag, a->real);
}

Complex get_conjugate(Complex* a){
    Complex res;
    res.real = a->real;
    res.imag = -a->imag;

    return res;
}

void print_complex(Complex* numb){
    printf("Result: ");
    if(numb->imag >= 0) printf("%.2lf + %2.lfi\n\n", numb->real, numb->imag);
    else printf("%.2lf - %.2lfi\n\n", numb->real, numb->imag);
}

void clear_input(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

void scan_complex_numb(Complex* numb){
    int result = 0;
    while(1){
        result = scanf("%lf %lf", &numb->real, &numb->imag);
        
        if(result == 2) break;
        else {
            clear_input();
            printf("Wrong input type\n\n");
        }
    }
}

void scan_operation(char* operation){
    clear_input();
    while(1){
        *operation = getchar();
        switch(*operation){
            case '+':
            case '-':
            case '*':
            case '/':
            case '#':
            case '^':
            case '&':
                return;
            default:
                clear_input();
                printf("Invalid operator\n\n");
                break;
        }
    }
    
}

int main(){
    Complex num1, num2, res;
    char operation;

    printf("Enter first complex number(format: real imag):\n");
    scan_complex_numb(&num1);

    printf("Enter first complex number(format: real imag):\n");
    scan_complex_numb(&num2);

    printf("Enter an operator(+, -, *, /, #, ^, &):\n");
    scan_operation(&operation);

    switch(operation){
        case '+':
            res = add(&num1, &num2);
            print_complex(&res);
            break;
        case '-':
            res = subtract(&num1, &num2);
            print_complex(&res);
            break;
        case '*':
            res = multiply(&num1, &num2);
            print_complex(&res);
            break;
        case '/':
            res = divide(&num1, &num2);
            print_complex(&res);
            break;
        case '#':
            printf("The modulus of first complex number: %lf\n", get_modulus(&num1));
            printf("The modulus of second complex number: %lf\n", get_modulus(&num2));
            break;
        case '^':
            printf("The argument of first complex number: %lf\n", get_argument(&num1));
            printf("The argument of second complex number: %lf\n", get_argument(&num2));
            break;
        case '&':
            res = get_conjugate(&num1);
            printf("The conjugate of first complex number: %.2lf %.2lfi", res.real, res.imag);
            res = get_conjugate(&num2);
            printf("\nThe conjugate of second complex number: %.2lf %.2lfi", res.real, res.imag);
            break;
    }
               
    return 0;
}