#include <stdio.h>

void cubeByRef(float*);

int main()
{
    float diameter;
    printf("Diameter:");
    scanf("%f", &diameter);
	cubeByRef(&diameter);
	printf("result = %f ",diameter);
	return(0);
}

void cubeByRef(float *diameterPtr)
{
   *diameterPtr =  *diameterPtr * 3.14159265359;
}
