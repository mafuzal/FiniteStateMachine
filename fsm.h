#ifndef __FSM__
#define __FSM__

typedef struct fsm_ fsm_t;
typedef struct state_ state_t;

#define MAX_INP_BUFFER_LEN 128
#define MAX_TRANSITION_TABLE_SIZE 128
#define MAX_STATE_NAME_SIZE 32
#define MAX_FSM_NAME_SIZE 32
#define MAX_TRANSITION_KEY_SIZE 64 
#define MAX_FSM_OUTPUT_BUFFER 1024


typedef enum{
    FSM_FALSE,
    FSM_TRUE
}fsm_bool_t;

typedef fsm_bool_t (*input_matching_fn)(
    char* data1,
    unsigned int size,
    char* data2,
    unsigned int user_data_len,
    unsigned int* length_read);

typedef struct fsm_output_buff_{
    char output_buffer[MAX_FSM_OUTPUT_BUFFER];
    unsigned int curr_pos;
}fsm_output_buff_t;


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
    /* If FSM need to produce some output, the output data shall be stored in this buffer.*/
    fsm_output_buff_t fsm_output_buff; 
    /* A generic function to match the input string with the key of transition table.*/
    input_matching_fn input_matching_fn_cb;
    
};

typedef enum{
    FSM_NO_TRANSITION,
    FSM_NO_ERROR
}fsm_error_t;


fsm_error_t execute_fsm(fsm_t* fsm, 
                        char* input_buffer, 
                        unsigned int size, 
                        fsm_bool_t* fsm_result);

#endif