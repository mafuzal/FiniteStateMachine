#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "fsm.h"

typedef struct bit_counter_
{
    unsigned int count_1;
    unsigned int count_0;
} bit_counter_t;

void bit_flipper_fn_gen(state_t *from, state_t *to,
                        char *input_buff,
                        unsigned int input_buff_size,
                        fsm_output_buff_t *fsm_output_buff)
{
    char out;
    if (fsm_output_buff->curr_pos == 0)
    {
        fsm_output_buff->curr_pos = sizeof(bit_counter_t);
    }

    bit_counter_t *stats_space = (bit_counter_t *)fsm_output_buff->output_buffer;

    if (*input_buff == '1')
    {
        out = '0';
        stats_space->count_1++;
    }
    else
    {
        out = '1';
        stats_space->count_0++;
    }

    fsm_output_buff->curr_pos += snprintf(fsm_output_buff->output_buffer +
                                              fsm_output_buff->curr_pos,
                                          (MAX_FSM_OUTPUT_BUFFER - fsm_output_buff->curr_pos - 1),
                                          "%s-->%c|-->%s\n",
                                          from->state_name, *input_buff, out,
                                          to->state_name);
}
int main(int argc, char **argv)
{
    fsm_t *fsm = create_new_fsm("Bit Flipper");
    state_t *state_S0 = create_new_state("S0",FSM_TRUE);
}