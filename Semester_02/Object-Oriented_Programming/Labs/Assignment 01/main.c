#include <stdio.h>
#include <stdbool.h>
/// task number 6

long long get_product(long long product) {
    product = 1;
    int x = 1;
    while (x != 0) {
        printf("Enter a number for task 1: ");
        scanf("%d", &x);
        if (x != 0) product *= x;
    }
    return product;
}

void number_of_zero_digits_in_product(long long product) {
    int count = 0;
    while (product != 0) {
        if (product % 10 == 0) {
            count++;
        }
        product /= 10;
    }
    printf("The number of zero digits in the product is: %d", count);
}

bool isPrime(int n){
    if (n == 2) return true;
    if (n <= 1 || n % 2 == 0) return false;
    for (int i = 3; i*i <= n; i+=2) {
        if (n % i == 0)
            return false;
    }
    return true;
}

void longest_prime_sum_subsequence(int* arr, int n) {
    int maxLength = 0;
    int startIndex = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            bool allSumsArePrime = true;
            for (int k = i; k < j; k++) {
                if (!isPrime(arr[k] + arr[k + 1])) {
                    allSumsArePrime = false;
                    break;
                }
            }
            if (allSumsArePrime && (j - i + 1) > maxLength) {
                maxLength = j - i + 1;
                startIndex = i;
            }
        }
    }
    printf("Longest subsequence: ");
    for (int i = startIndex; i < startIndex + maxLength; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    char task;
    printf("Enter the task you want to test: ");
    scanf("%c", &task);
    if (task == 'a'){
        long long product = 1;
        product = get_product(product);
        number_of_zero_digits_in_product(product);
    }
    else{
        int n, arr[101]={0};
        printf("Enter the size of the array: ");
        scanf("%d", &n);
        printf("Enter the elements of the array: ");
        for (int i = 0; i < n; ++i) {
            scanf("%d", &arr[i]);
        }
        longest_prime_sum_subsequence(arr, n);
    }
    return 0;
}