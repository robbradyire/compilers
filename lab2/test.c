#include "lab2.h"

int main()
{
    State * state = new_state();
    state->count = 11;
    state->base = 8;
    state->start_index = 1;
    state->sign = 1;

    sum("37777777777", state);
}
