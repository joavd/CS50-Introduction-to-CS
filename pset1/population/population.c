#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int init_pop = 0;
    int end_pop = 0;
    int current_pop;
    int year = 0;

    // Ask for the initial population, until it's bigger or equal than 9
    while (init_pop < 9)
    {
        init_pop = get_int("Start size:");
    }

    // Ask for the ending population, until it's bigger than the inital one
    while (end_pop < init_pop)
    {
        end_pop = get_int("End size:");
    }

    // Calculate number of years until we reach threshold
    current_pop = init_pop;
    while (current_pop < end_pop)
    {
        int born = current_pop / 3;
        int dead = current_pop / 4;
        current_pop += born - dead;
        year++;
    }

    // Print number of years
    printf("Years: %i", year);
}
