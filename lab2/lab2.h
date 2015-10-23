#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char * MAX_INT_STR = "2147483647";
char * MIN_INT_STR = "2147483648";
char valid[] = "Valid";
int ERR = -1;

typedef enum {
    zero,
    one_to_seven,
    eight_nine,
    input_hex,
    bB,
    hH,
    sign,
    end_string,
    INPUT_ERR
} InputType;

typedef enum {
    empty,
    zeroes,
    octal,
    base10,
    hex,
    octal_b,
    got_h,
    got_sign,
    signed_zeroes,
    signed_num,
    ACCEPT,
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
    int index_start;
    int count;
    int isZero;
} State;

/* new_state()
 *
 * Creates and initializes a State
 */
State * new_state()
{
    State * state;
    state = malloc(sizeof(State));
    state->state_name = empty;
    state->base = 8;
    state->sign = 1;
    state->index_start = 0;
    state->count = 0;
    state->isZero = 1;
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

/* char_type(char)
 *
 * returns the type of character(num, hex etc.)
 */
int char_type(char c)
{
    InputType type;
    char low_char = tolower(c);
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
    else if (low_char == 'b')
    {
        type = bB;
    }
    else if (low_char >= 'a' && low_char <= 'f')
    {
        type = input_hex;
    }
    else if (low_char == 'h')
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
    char low_char = tolower(c);
    if (c >= '0' && c <= '9')
    {
        return c - '0';
    }
    else if (low_char >= 'a' && low_char <= 'f')
    {
        return low_char - 'a' + 10;
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
    int len = state->count - state->index_start;
    if (state->base == 8 && len <= 11)
    {
        if (len == 11 && number[state->index_start] > '3')
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (state->base == 10 && len <= 10)
    {
        if (len == 10)
        {
            if (state->sign == 1 && strcmp(number + state->index_start, MAX_INT_STR) > 0)
            {
                return 1;
            }
            else if(strcmp(number + state->index_start, MIN_INT_STR) > 0)
            {
                return 1;
            }
        }
        else
        {
            return 0;
        }
    }
    else if (state->base == 16 && len > 8)
    {
        return 1;
    }
    return 0;
}


/* sum(string, *State)
 *
 * converts the string to its integer value
 */
void sum(char *input, State *state)
{
    if (will_overflow(input, state))
    {
        printf("%s is too large, overflow will occur\n", input);
    }
    else
    {
        int32_t total = 0;
        int sign = state->sign;
        int base = state->base;
        int index_start = state->index_start;
        int count = state->count;
        int val;
        int i;

        if (state->isZero)
        {
            total = 0;
        }
        else
        {
            if (base == 10)
            {
                for (i = index_start; i < count; i++)
                {
                    total = total * base + sign * get_val(input[i]);
                }
            }
            else if (base == 8)
            {
                for (i = index_start; i < count; i++)
                {
                    total = (total << 3) + get_val(input[i]);
                }
                total *= sign;
            }
            else
            {
                for (i = index_start; i < count; i++)
                {
                    total = (total << 4) + get_val(input[i]);
                }
                total *= sign;
            }
        }
        printf("%s is valid. It is equal to %d in decimal\n", input, total);
    }
}

