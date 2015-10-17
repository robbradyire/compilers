#include <stdio.h>
#include <stdlib.h>

int MAX_INT = 2147483647;
int MIN_INT = -2147483648;
int END_OF_STRING = -2;
int ERR = -1;
int plus = '+';
int minus = '-';

char over[] = "Overflow";
char valid[] = "Valid";

/* State
 *
 * contains the state number, the base (8, 10 or 16)
 * and the sign (-1 or 1)
 */
typedef struct {
    int state_num;
    int base;
    int sign;
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
    state->state_num = 0;
    state->base = 10;
    state->sign = 1;
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

/* get_val(char)
 *
 * returns the value of a character
 * '0'-'9' returns 0-9
 * 'a'/'A' - 'f'/'F' returns 10-15
 * 'h'/'H' returns 16
 * '+' and '-' return their own values 
 * null returns end_of _string
 * anything else returns -1
 */
int get_val(char c)
{
    if (c >= '0' && c <= '9')
    {
        return c - 48;
    }
    else if (c >= 'A' && c <= 'H')
    {
        return c - 55;
    }
    else if (c >= 'a' && c <= 'h')
    {
        return c - 87;
    }
    else if (c == '+' || c == '-')
    {
        return c;
    }
    else if (c == 0)
    {
        return END_OF_STRING;
    }
    else
    {
        return ERR;
    } 
}

/* will_overflow(int, int)
 *
 * checks whether two numbers will overflow when multiplied
 * returns: 1 if the result will overflow, 0 otherwise
 */
int will_overflow(int sum, int multiplicand)
{ 
    if (sum > 0 && MAX_INT / sum < multiplicand)
    {
        return 1;
    }
    else if (sum < 0 && MIN_INT / sum < multiplicand)
    {
        return 1;
    }
    return 0;
}

/* sum(string, *State)
 *
 * converts the string to its integer value
 */
char * sum(char *input, State *state)
{
    int total = 0;
    int sign = state->sign;
    int base = state->base;
    int count = state->count;
    int val;

    int i;
    for (i = 0; i < count; i++)
    {
        val = get_val(input[i]);
        if (val != plus || val != minus)
        {
            if (!will_overflow(total, val))
            {
                total = total * base + get_val(input[i]);
                if (i == 0)
                {
                    total = sign * total;
                }
            }    
            else
            {
                return over;
            }
        }
    }
    return valid;
}
