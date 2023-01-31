#include <stdlib.h>
#include <stdio.h>

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

Tab *init(int firstElementValue)
{
    Tab *tab = malloc(sizeof(Tab));
    Element *element = malloc(sizeof(Element));
    if (tab == NULL || element == NULL)
        exit(EXIT_FAILURE);
    element->number = firstElementValue;
    element->next = NULL;
    tab->first = element;
    return tab;
}

void insertTab(Tab* tab, long nb)
{
    Element *newElement = malloc(sizeof(Element));
    if (newElement == NULL || tab == NULL)
        exit(EXIT_FAILURE);
    newElement->number = nb;
    newElement->next = tab->first;
    tab->first = newElement;
}

int scanTab(Tab *tab, long nb)
{
    Element *currentElement = tab->first;
    while (currentElement != NULL)
    {
        long rem = nb%(currentElement->number);
        if (rem == 0)
        {
            currentElement = NULL;
            return 0;
        }
        currentElement = currentElement->next;
    }
    currentElement = NULL;
    return 1;
}

int main(int argc, char *argv[])
{
    Tab *primes = init(2);
    long nb = 2;

    for (long i=3; i<500000; i+=2)
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
        fprintf(file,"%d;",currentElement->number);
        currentElement = currentElement->next;
    }
    fprintf(file,"%d",currentElement->number);
    fclose(file);
    return 0;
}
