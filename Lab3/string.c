#include <stdio.h>

int main()
{
    // This is our array of chars
    char s[10];
    int t;
    
    // Input the char values
    for(int i = 0; i < 9; i++){
        scanf("%d", &t); // scan the int 
        s[i] = t;        // save in the char 
    }
    
    s[9] = 0; // Set the NULL character
    
    // Output the array as a C-string
    printf("%s", s);

    printf("\n\nHex representation:\n");
    for(int i=0; i<9; i++){
        if(i==9){
            printf("%x", s[i]);
        }else{
            printf("%x, ", s[i]);
        }
    }


    return 0;
}
