#include <stdio.h>
#include "spacing.c"

int main()
{
    int a, b;
	char star = '*';
	char dash = '-';
    printf("Maak keuze:");
    scanf("%d", &a);
    
	if (a = 2)
	{
		for (b= 0 ; b < 10; b++ )
		{
			print_function ( star );
			print_function( dash );
			printf("\n");
		}
	}

	else if (a > 0)
	{
		printf("%d", a);	
	}

    else if (a < 0) 
	{
		return 0;
	}
    //c = a + b;
    //printf("%d + %d = %d\n", a, b, c);
    return 0;
}
