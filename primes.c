#include <stdlib.h>
#include <stdio.h>

unsigned sqrt(unsigned val) {
    unsigned a = val, valDigits = 0;
    do{
        valDigits++;
        a /= 10;
    }
    while(a != 0);
    a = pow(10, valDigits/2);
    for (int i=0; i<5; i++)
    {
        a = (a+val/a) /2;
    }
    return a;
}

typedef struct Element Element;
struct Element
{
    long number;
    Element *next;
};
typedef struct Tab Tab;
struct Tab
{
    Element *first;
};

Tab *init(long nb)
{
    Tab *tab = malloc(sizeof(Tab));
    Element *element = malloc(sizeof(Element));
    if (tab == NULL || element == NULL)
        exit(EXIT_FAILURE);
    element->number = nb;
    element->next = NULL;
    tab->first = element;
    return tab;
}

void insertTab(Tab *tab, long nb)
{
    Element *currentAddress = tab->first;
    while (currentAddress->next != NULL) {
        currentAddress = currentAddress->next;
    }
    Element *newElement = malloc(sizeof(Element));
    if (newElement == NULL)
        exit(EXIT_FAILURE);
    newElement->number = nb;
    newElement->next = NULL;
    currentAddress->next = newElement;
}

int scanTab(Tab *tab, long nb)
{
    Element *currentElement = tab->first;
    long squareRoot = sqrt(nb);
    for (long i=1; i<squareRoot; i++)
    {
        if (nb%currentElement->number == 0) {
            return 0;
        }
        currentElement = currentElement->next;
    }
    return 1;
}

int main(int argc, char *argv[])
{
    Tab *primes = init(2);
    for (long i=3; i<500000; i++)
    {
        if (scanTab(primes, i) == 1)
        {
            insertTab(primes, i);
        }
    }

    FILE *file = NULL;
    file = fopen("primes.txt","w");
    Element *currentElement = primes->first;
    while (currentElement->next != NULL)
    {
        fprintf(file,"%li;",currentElement->number);
        currentElement = currentElement->next;
    }
    fprintf(file,"%li",currentElement->number);
    fclose(file);
    return 0;
}
