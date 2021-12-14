#include <stdio.h>

struct student{
    char voornaam[20];
    int leeftijd;

struct course{
    char voornaam[20];
    int instroomjaar;
        } course;
    };


int main()
{
    int i;
    int aantal = 10;

    printf("Aantal studenten: ");
    scanf("%i", &aantal);

    struct student list[10];
    if (aantal > 10){
    printf("De max aantal is 10 invoer is: %d\n", aantal);
    return 0;
    }
    else if (aantal >= 2){
    printf("De gegevens van de %d studenten\n", aantal);   
    }
    else if (aantal == 1){
    printf("De gegevens van %d student\n", aantal);  
    }
    else if (aantal == 0){
    printf("Er zullen %d worden toegevoegd... ", aantal);
    }
    else{
    printf("Vul een positieve waarde in, negatief is niet goed.");
    return 0;
    }

    for (i = 0; i < aantal; i++){

        printf("Vul voornaam van student in: ");
        scanf("%s", list[i].voornaam);
        printf("Vul leeftijd student in: ");
        scanf("%d", &list[i].leeftijd);
        printf("Vul voornaam course in: ");
        scanf("%s", list[i].course.voornaam);
        printf("Vul het instroomjaar in: ");
        scanf("%d", &list[i].course.instroomjaar);
        printf("\n");
    }
    for (i = 0; i < aantal; i++)
    {
        printf("voornaam student: %s\nLeeftijd student: %d\ncourse: %s\nInstroomjaar: %d\n\n", list[i].voornaam, list[i].leeftijd, list[i].course.naam, list[i].course.instroomjaar);
    }

    return 0;
}
