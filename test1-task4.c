#include <stdio.h>
#include <stdlib.h>

int main() {
    int power2OfSum = 0;
    int sumOfPower2 = 0;
    const int n = 100;
    sumOfPower2 = (n * (n + 1) * (2 * n + 1))/6;
    power2OfSum = ((n * (n + 1))/2) * ((n * (n + 1))/2);
    printf("%d \n", (power2OfSum - sumOfPower2));
    system("pause");
    return 0;
}