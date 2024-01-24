#include <stdio.h>

int main()
{

    // This is our char being converted
    int n;
    printf("Input how many variables you would like to convert: ");
    scanf("%d", &n);

    printf("Please enter your %d charaters with no spaces (enter when done): ", n);

    n++;

    unsigned char c[n];
    unsigned char temp[n];
    for(int i=0; i<n; i++){
        scanf("%c", &c[i]);
    }
    for(int i=0; i<n; i++){
        temp[i] = c[i];
    }
    
    // You'll also need an array to store the bit string,
    // either chars or ints will work
    int x[n][8];

    for(int j=0; j<n; j++){
        for(int i=7; i>=0; i--){
            if(c[j]%2 == 1){
                x[j][i] = 1;
            }else{
                x[j][i] = 0;
            }
            c[j] = c[j]/2;
        }
    }

    // Print out the resulting binary number
    for(int j=1; j<n; j++){
        printf("%c: ", temp[j]);
        for(int i=0; i<8; i++){
            printf("%d", x[j][i]);
        }
        printf("\n");
    }

    return 0;
}
