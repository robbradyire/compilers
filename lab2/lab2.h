#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * MAX_INT = "2147483647";
char * MIN_INT = "2147483648";
int ERR = -1;
int plus = '+';
int minus = '-';

typedef enum {
    zero,
    one_to_seven,
    eight_nine,
    hex,
    bB,
    hH,
    sign,
    end_string,
    INPUT_ERR
} InputType;

typedef enum {
    leading_zero,
    got_1_to_7,
    got_8_9,
    got_hex,
    got_b,
    got_h,
    got_sign,
    num_after_sign,
    VALID,
    STATE_ERR
} StateName;

typedef enum {
    no_error,
    overflow,
    invalid_input
} ErrorType;

/* State
 *
 * contains the state number, the base (8, 10 or 16)
 * and the sign (-1 or 1)
 */
typedef struct {
    StateName state_name;
    int base;
    int sign;
    int start_index;
    int count;
} State;

/* new_state()
 *
 * Creates and initializes a State
 */
State * new_state()
{
    State * state;
    state = malloc(sizeof(State));
    state->state_name = leading_zero;
    state->base = 10;
    state->sign = 1;
    state->start_index = 0;
    state->count = 0;
    return state; 
}

/* delete_state(*State)
 *
 * Frees the space allocated for a State
 */
void delete_state(State * state)
{
    free(state);
}

char over[] = "Overflow";
char valid[] = "Valid";

/* char_type(char)
 *
 * returns the type of character(num, hex etc.)
 */
int char_type(char c)
{
    InputType type;
    if (c == 0)
    {
        type = end_string;
    }
    else if (c == '0')
    {
        type = zero;
    }
    else if (c >= '1' && c <= '7')
    {
        type = one_to_seven;
    }
    else if (c == '8' || c == '9')
    {
        type = eight_nine;
    }
    else if (c == 'b' || c ==  'B')
    {
        type = bB;
    }
    else if ((c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'))
    {
        type = hex;
    }
    else if (c == 'h' || c == 'H')
    {
        type = hH;
    }
    else if (c == '+' || c == '-')
    {
        type = sign;
    }
    else
    {
        type = INPUT_ERR;
    }
    return type;
}

/* get_val(char)
 *
 * returns the value of a character
 * '0'-'9' returns 0-9
 * 'a'/'A' - 'f'/'F' returns 10-15
 * '+' and '-' return their own values 
 * anything else returns -1
 */
int get_val(char c)
{
    if (c >= '0' && c <= '9')
    {
        return c - 48;
    }
    else if (c >= 'A' && c <= 'F')
    {
        return c - 55;
    }
    else if (c >= 'a' && c <= 'f')
    {
        return c - 87;
    }
    else if (c == '+' || c == '-')
    {
        return c;
    }
    else
    {
        return ERR;
    } 
}

/* will_overflow(str, State)
 *
 * checks whether a string will overflow
 * returns: 1 if the will overflow, 0 otherwise
 */
int will_overflow(char* number, State * state)
{
    int len = state->count - state->start_index;
    if (state->base == 8 && len <= 11)
    {
        if (len == 11 && number[state->start_index] > '3')
        {
            return 1;
        }
    }
    else if (state->base == 10 && len <= 10)
    {
        if (len == 10 && strcmp(number + state->start_index, MAX_INT) > 0)
        {
            if (state->sign == 1 && strcmp(number + state->start_index, MAX_INT) > 0)
            {
                return 1;
            }
            else if(strcmp(number + state->start_index, MIN_INT) > 0)
            {
                return 1;
            }
        }
    }
    else if (state->base == 16 && len > 8)
    {
        return 1;
    }
    return 0;
}

void set_sign(char * number, State * state)
{
    if (state->base == 8 && (state->count - state->start_index) == 11)
    {
        if (number[state->start_index] > '1')
        {
            state->sign = -1;
        }
    }
    else if(state->base == 16 && (state->count - state->start_index) == 8)
    {
        if (number[state->start_index] > '7')
        {
            state->sign = -1;
        }
    }
}

/* sum(string, *State)
 *
 * converts the string to its integer value
 */
void sum(char *input, State *state)
{
    if (will_overflow(input, state))
    {
        printf("%s\n", over);
    }
    else
    {
        set_sign(input, state);
        int total = 0;
        int sign = state->sign;
        int base = state->base;
        int count = state->count;
        int val;
        int i;

        if (base == 10)
        {
            for (i = state->start_index; i < count; i++)
            {
                val = get_val(input[i]);
                if (val != plus && val != minus)
                {
                    total = total * base + sign * get_val(input[i]);
                }
            }
            printf("%d\n", total);
        }
        else
        {
            if (state->sign == 1)
            {
                total = 0;
                for (i = state->start_index; i < count; i++)
                {
                    val = get_val(input[i]);
                    total = total * base + val;
                }
                printf("%d\n", total);
            }
            else
            {
                total = -1;
                for (i = state->start_index; i < count; i++)
                {
                    val = get_val(input[i]);
                    total = total * base + (val = base);
                }
                total--;
                printf("%d\n", total);
            }
        }
    }
}

