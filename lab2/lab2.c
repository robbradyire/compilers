#include "lab2.h"

// this table holds all the transistions from state to state, as [current_state][input]
int state_table[10][8] = {
    {zeroes,        octal,      base10,     hex,       hex,       STATE_ERR, got_sign,  STATE_ERR},// empty
    {zeroes,        octal,      base10,     hex,       octal_b,   got_h,     STATE_ERR, ACCEPT},   // zeroes
    {octal,         octal,      base10,     hex,       octal_b,   got_h,     STATE_ERR, ACCEPT},   // octal
    {base10,        base10,     base10,     hex,       hex,       got_h,     STATE_ERR, ACCEPT},   // base10
    {hex,           hex,        hex,        hex,       hex,       got_h,     STATE_ERR, STATE_ERR},// hex
    {hex,           hex,        hex,        hex,       hex,       got_h,     STATE_ERR, ACCEPT},   // octal_b
    {STATE_ERR,     STATE_ERR,  STATE_ERR,  STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, ACCEPT},   // got_h
    {signed_zeroes, signed_num, signed_num, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR},// got_sign
    {signed_zeroes, signed_num, signed_num, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, ACCEPT},   // signed_zeroes
    {signed_num,    signed_num, signed_num, STATE_ERR, STATE_ERR, STATE_ERR, STATE_ERR, ACCEPT}    // signed_num
};

/* update_state(char, State)
 *
 * This function updates the state depending on the input char and the current state
 */
int update_state(char c, State * state)
{
    StateName current_state = state->state_name;
    InputType input_type = char_type(c);
    StateName next_state = state_table[current_state][input_type];

    if (next_state == zeroes)
    {
        state->count++;
        state->index_start++;
    }
    else if (next_state == octal)
    {
        state->count++;
        state->isZero = 0;
    }
    else if (next_state == base10)
    {
        state->count++;
        state->isZero = 0;
        state->base = 10;
    }
    else if (next_state == hex)
    {
        if (current_state == octal_b)
        {
            state->count++;
        }
        state->count++;
        state->base = 16;
        state->isZero = 0;
    }
    else if (next_state == octal_b)
    {
        state->base = 8;
    }
    else if (next_state == got_h)
    {
        if (current_state == octal_b)
        {
            state->count++;
            state->isZero = 0;
        }
        state->base = 16;
    }
    else if (next_state == got_sign)
    {
        state->count++;
        state->index_start++;
        state->base = 10;
        if (c == '-')
        {
            state->sign = -1;
        }
    }
    else if (next_state == signed_zeroes)
    {
        state->count++;
        state->index_start++;
    }
    else if (next_state == signed_num)
    {
        state->count++;
        state->isZero = 0;
    }
    else if (next_state == ACCEPT && current_state == octal)
    {
        state->base = 10;
    }
    state->state_name = next_state;
    return next_state;
}

int main(int argc, char * argv[])
{
    if (argc == 1)
    {
        printf("You forgot to give an argument");
    }

    int arg_count, isValid, isFinished, i;
    State * state;
    char c;

    // Loop through each argument
    for (arg_count = 1; arg_count < argc; arg_count++)
    {
        state = new_state();
        isValid = 1;
        isFinished = 0;
        i = 0;
        // Loop through each character
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
                if (update_state(c, state) == STATE_ERR)
                {
                    isValid = 0;
                    isFinished = 1;
                }
                else if (state->state_name == ACCEPT)
                {
                    isValid = 1;
                    isFinished = 1;
                }
            }
        }
        if (!isValid)
        {
            printf("%s is not a valid input\n", argv[arg_count]);
        }
        else
        {
            sum(argv[arg_count], state);
        }
    }
    delete_state(state);
    printf("Program finished\n");
    return 0;
}
