#ifndef __FSM__
#define __FSM__

typedef struct fsm_ fsm_t;
typedef struct state_ state_t;

#define MAX_INP_BUFFER_LEN 128
#define MAX_TRANSITION_TABLE_SIZE 128
#define MAX_STATE_NAME_SIZE 32
#define MAX_FSM_NAME_SIZE 32
#define MAX_TRANSITION_KEY_SIZE 64 


typedef enum{
    FSM_FALSE,
    FSM_TRUE
}fsm_bool_t;


typedef struct tt_entry_ {
    char transition_key[MAX_TRANSITION_KEY_SIZE];
    unsigned int transition_key_size; 
    state_t* next_state; 
}tt_entry_t;

typedef struct tt_{
    tt_entry_t tt_entry[MAX_TRANSITION_TABLE_SIZE];

}tt_t;

struct state_{
    char state_name[MAX_STATE_NAME_SIZE]; /*Name of the state must be unique within the FSM */
    tt_t state_trans_table; /* Transition Table of the state */
    fsm_bool_t is_final; /* Boolean if the state is final or not*/
};

struct fsm_{
    state_t* initial_state;     /*Initial state of FSM to start with */
    char fsm_name[MAX_FSM_NAME_SIZE]; /* Name of FSM */
    char input_buffer[MAX_INP_BUFFER_LEN]; /* Application provided input data to parse by FSM  */
    unsigned int input_buffer_size; /* Length of input buffer */
    unsigned int input_buffer_cursor; /* Cursor to read the above input_buffer in continuation */
};

#endif