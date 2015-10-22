#include "lab2.h"

// this table holds all the transistions from state to state, as [current_state][input]
int state_table[8][8] = {
    {leading_zero,   got_1_to_7,     got_8_9,        got_hex,  STATE_ERR,  STATE_ERR, got_sign, STATE_ERR}, // state: leading_zero
    {got_1_to_7,     got_1_to_7,     got_8_9,        got_hex,  got_b,      got_h,     STATE_ERR, VALID}, // state: got_1_to_7
    {got_8_9,        got_8_9,        got_8_9,        got_hex,  got_hex,    got_h,     STATE_ERR, VALID}, // state: got_8_9
    {got_hex,        got_hex,        got_hex,        got_hex,  got_hex,    got_h,     STATE_ERR, STATE_ERR}, // state: got_hex
    {got_hex,        got_hex,        got_hex,        got_hex,  got_hex,    got_h,     STATE_ERR, VALID}, // state: got_b
    {STATE_ERR,      STATE_ERR,      STATE_ERR,      STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, VALID}, // state: got_h
    {got_sign,       num_after_sign, num_after_sign, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR}, // got_sign
    {num_after_sign, num_after_sign, num_after_sign, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, VALID} // num_after_sign
};

/* update_state(char, State)
 *
 * This function updates the state depending on the input char and the current state
 */
int update_state(char c, State * state)
{
    StateName err_state = STATE_ERR;
    
    printf("Current state: %d Input: %c ", state->state_name, c);

    StateName last_state = state->state_name;
    state->state_name = state_table[state->state_name][char_type(c)];
    printf("new state: %d\n", state->state_name);
    if (state->state_name == err_state)
    {
        return invalid_input;
    }
    else if (state->state_name == leading_zero || state->state_name == got_sign)
    {
        state->start_index++;
        if (c == minus)
        {
            state->sign = -1;
        }
    }
    switch (state->state_name)
    {
        case got_1_to_7:
            state->base = 8;
            break;
        case got_8_9:
        case got_sign:
            state->base = 10;
            break;
        case got_hex:
        case got_h:
            state->base = 16;
            break;
        default:
            break;
    }
    state->count++;
    return no_error;
}

int main(int argc, char * argv[])
{
    if (argc == 1)
    {
        printf("You forgot to give an argument");
    }

    int arg_count, isValid, isFinished, i;
    InputType input;
    State * state;
    char c;

    for (arg_count = 1; arg_count < argc; arg_count++)
    {
        state = new_state();
        isValid = 1;
        isFinished = 0;
        i = 0;
        for (i = 0; isFinished != 1; i++)
        {
            c = argv[arg_count][i];
            if (char_type(c) == INPUT_ERR)
            {
                isValid = 0;
                isFinished = 1;
            }
            else
            {
                if (update_state(c, state) == invalid_input)
                {
                    isValid = 0;
                    isFinished = 1;
                }
                else if (state->state_name == VALID)
                {
                    isValid = 1;
                    isFinished = 1;
                    StateName prev = state->prev_state;
                    if (prev == got_1_to_7)
                    {
                        state->base = 8;
                    }
                    else if (prev == got_8_9 || prev == num_after_sign)
                    {
                        state->base = 10;
                    }
                    else if (prev == got_hex || prev == got_h)
                    {
                        state->base = 16;
                    }
                }
            }
        }
        if (!isValid)
        {
            printf("Not a valid input\n");
        }
        else
        {
            printf("base: %d\n", state->base);
            sum(argv[arg_count], state);
        }
    }
    printf("Program finished\n");
    return 0;
}
