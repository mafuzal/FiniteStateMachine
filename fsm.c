#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "fsm.h"


/*
****************************************************************************
*Create a new FSM
****************************************************************************
*/
fsm_t* create_new_fsm(const char* fsm_name)
{
    fsm_t* fsm = calloc(1,sizeof(fsm_t));
    strncpy(fsm->fsm_name, fsm_name, MAX_FSM_NAME_SIZE -1);
    fsm->fsm_name[MAX_FSM_NAME_SIZE -1] = '\0';
    return fsm;
}

/*
****************************************************************************
*Create a new state 
****************************************************************************
*/
state_t* create_new_state(char* state_name, fsm_bool_t is_final)
{
    assert(state_name);
    state_t* state = calloc(1,sizeof(state_t));
    strncpy(state->state_name, state_name, MAX_STATE_NAME_SIZE-1);
    state->state_name[MAX_STATE_NAME_SIZE -1]='\0';
    state->is_final = is_final;

    return state; 
}
/*
****************************************************************************
*Which state is initial?
****************************************************************************
*/
void set_fsm_initial_state(fsm_t* fsm, state_t* state)
{
    assert(!fsm->initial_state);
    fsm->initial_state = state;

}
/*
****************************************************************************
*Insert new Transition Table entry into a Given State 
****************************************************************************
*/
tt_entry_t* create_and_insert_new_tt_entry(tt_t* trans_table,
                                           char* transition_key,
                                           unsigned int sizeof_key,
                                           state_t* next_state)
{
    assert(sizeof_key < MAX_TRANSITION_KEY_SIZE);
    tt_entry_t* tt_entry_ptr = get_next_empty_tt_entry(trans_table);
    if(!tt_entry_ptr)
    {
        printf("FATAL : Transiiton Table is Full\n");
        return;
    }
    
    memcpy(tt_entry_ptr->transition_key, transition_key, sizeof_key);
    tt_entry_ptr->transition_key[sizeof_key] = '\0';
    tt_entry_ptr->transition_key_size = sizeof_key;
    tt_entry_ptr->next_state = next_state;
}

            