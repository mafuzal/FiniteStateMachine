#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "fsm.h"

/*
****************************************************************************
*Create a new FSM
****************************************************************************
*/
fsm_t *create_new_fsm(const char *fsm_name)
{
    fsm_t *fsm = calloc(1, sizeof(fsm_t));
    strncpy(fsm->fsm_name, fsm_name, MAX_FSM_NAME_SIZE - 1);
    fsm->fsm_name[MAX_FSM_NAME_SIZE - 1] = '\0';
    return fsm;
}

/*
****************************************************************************
*Create a new state
****************************************************************************
*/
state_t *create_new_state(char *state_name, fsm_bool_t is_final)
{
    assert(state_name);
    state_t *state = calloc(1, sizeof(state_t));
    strncpy(state->state_name, state_name, MAX_STATE_NAME_SIZE - 1);
    state->state_name[MAX_STATE_NAME_SIZE - 1] = '\0';
    state->is_final = is_final;

    return state;
}
/*
****************************************************************************
*Which state is initial?
****************************************************************************
*/
void set_fsm_initial_state(fsm_t *fsm, state_t *state)
{
    assert(!fsm->initial_state);
    fsm->initial_state = state;
}
/*
****************************************************************************
*Insert new Transition Table entry into a Given State
****************************************************************************
*/
tt_entry_t *create_and_insert_new_tt_entry(tt_t *trans_table,
                                           char *transition_key,
                                           unsigned int sizeof_key,
                                           state_t *next_state)
{
    assert(sizeof_key < MAX_TRANSITION_KEY_SIZE);
    tt_entry_t *tt_entry_ptr = get_next_empty_tt_entry(trans_table);
    if (!tt_entry_ptr)
    {
        printf("FATAL : Transiiton Table is Full\n");
        return;
    }

    memcpy(tt_entry_ptr->transition_key, transition_key, sizeof_key);
    tt_entry_ptr->transition_key[sizeof_key] = '\0';
    tt_entry_ptr->transition_key_size = sizeof_key;
    tt_entry_ptr->next_state = next_state;
}

/*
****************************************************************************
*Execute FSM
****************************************************************************
*/
fsm_error_t execute_fsm(fsm_t *fsm,
                        char *input_buffer,
                        unsigned int size,
                        fsm_bool_t *fsm_result)
{
    state_t *initial_state = fsm->initial_state;
    assert(initial_state);
    state_t *current_state = initial_state;
    state_t *next_state = NULL;

    fsm->input_buffer_cursor = 0;
    unsigned int length_read = 0;
    unsigned int input_buffer_len = 0;
    char *buffer_to_parse;

    if (fsm_result)
    {
        *fsm_result = FSM_FALSE;
    }

    /* Use Application Supplied Buffer */
    if (input_buffer && size)
    {
        buffer_to_parse = input_buffer;
        input_buffer_len = size;
    }
    else
    {
        /* Use FSM buffer set by the application.*/
        buffer_to_parse = fsm->input_buffer;
        input_buffer_len = fsm->input_buffer_size;
    }

    /*
     * If application has not supplied output buffer,
     * Use FSM's internal output buffer
     */
    if (!output_buffer)
    {
        output_buffer = &fsm->fsm_output_buff;
    }
}

void fsm_register_input_matching_fn_cb(fsm_t *fsm,
                                       input_matching_fn input_matching_fn_cb)
{
    fsm->input_matching_fn_cb = input_matching_fn_cb;
}

void init_fsm_output_buffer(fsm_output_buff_t *fsm_output_buff)
{
    memset(fsm_output_buff->output_buffer, 0, MAX_OUP_BUFFER_LEN);
    fsm_output_buff->curr_pos = 0;
}

void register_input_matching_tt_entry_cb(tt_entry_t *tt_entry,
                                         input_matching_fn input_matching_fn_cb)
{
    unsigned int i = 0;
    for (; i < MAX_TT_ENTRY_CALLBACKS; i++)
    {
        if (tt_entry->input_matching_fn_cb[i])
            continue;
        tt_entry->input_matching_fn_cb[i] = input_matching_fn_cb;
        return;
    }
    assert(0);
}