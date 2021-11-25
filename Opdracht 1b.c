//
//  Opdracht 1.c
//  Operating Systems
//
//  Created by Tim Messchendorp on 25/11/2021.
//

#include <stdio.h>
void print_function( char letter );
int ctr;
int repeat;
int main( void )
{
char star = '*';
char dash = '-';
for (ctr = 0 ; ctr < 10; ctr++ )
{
    for(repeat = 0 ; repeat < 10; repeat++ )
    {
        print_function( star );
        print_function( dash );
        printf("\n");\
    }
}
return 0;
}
void print_function ( char letter )
{
for ( ctr = 0; ctr < 9; ctr++)
{
printf("%c", letter);
}
}
