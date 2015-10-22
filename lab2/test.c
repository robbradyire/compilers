#include "lab2.h"

int main()
{
    State * state = new_state();
    state->count = 8;
    state->base = 16;
    state->start_index = 0;

    sum("F0F01234", state);
}
