#include <stdio.h>
#include <stdlib.h>


struct persoon{
    char naam[30];
    int leeftijd;
};

int main()
{
    struct persoon persoon;
    int index = 1;
    int i;
    int ans;
    int totalSize;
    int oldSize;
    struct persoon *newptr;
    struct persoon *pp;
    struct persoon *ptr;

    ptr = malloc(sizeof(persoon));
    //ptr = (struct persoon *)malloc(sizeof(struct persoon));
    while (ans = 1){

        newptr = ptr;
        newptr += (index-1);

        printf("Naam student: ");
        scanf("%s", newptr->naam);

        printf("Uw leeftijd: ");
        scanf("%d", &newptr->leeftijd);

        printf("\n");

        pp = ptr;
        for (i = 0; i < index; i++){
            //printf("Volgorde nummer = %i\n", i);
            //printf("index nummer = %i\n", index);
            printf("De naam van student = %s\n", pp->naam); 
            printf("Zijn leeftijd = %i\n", pp->leeftijd);
            pp++;
            totalSize += (index * sizeof(struct persoon));    
        }
            //printf("ptr bedraagt: %d\n", ptr);

        ptr=(struct persoon *)realloc(ptr, totalSize);
        
        //ptr = (struct persoon *) realloc (ptr, index * sizeof(struct persoon));
        if (ptr == NULL)
        {
            perror("error");
            exit(-1);
        }

    }
    free(ptr);
    return 0;
    }
