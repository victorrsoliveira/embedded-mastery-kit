/**
 * @file test_fsm.c
 * @author Victor Oliveira (victor.rsoliveira@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-03-10
 *
 */

#include <assert.h>
#include <stdio.h>

#include "fsm.h"

// Tracking variables for callbacks
static int on_state_entry_calls = 0;
static int on_state_run_calls   = 0;
static int on_state_exit_calls  = 0;

static int off_state_entry_calls = 0;
static int off_state_run_calls   = 0;
static int off_state_exit_calls  = 0;

uint32_t          on_state_on_entry(struct fsm *fsm);
struct fsm_state *on_state_on_run(struct fsm             *fsm,
                                  const struct fsm_event *event);
uint32_t          on_state_on_exit(struct fsm *fsm);

uint32_t          off_state_on_entry(struct fsm *fsm);
struct fsm_state *off_state_on_run(struct fsm             *fsm,
                                   const struct fsm_event *event);
uint32_t          off_state_on_exit(struct fsm *fsm);

struct fsm_state on_state  = {.on_entry = on_state_on_entry,
                              .on_run   = on_state_on_run,
                              .on_exit  = on_state_on_exit};
struct fsm_state off_state = {.on_entry = off_state_on_entry,
                              .on_run   = off_state_on_run,
                              .on_exit  = off_state_on_exit};

void reset_counters()
{
    on_state_entry_calls  = 0;
    on_state_run_calls    = 0;
    on_state_exit_calls   = 0;
    off_state_entry_calls = 0;
    off_state_run_calls   = 0;
    off_state_exit_calls  = 0;
}

void test_fsm_init()
{
    struct fsm fsm;
    int        context = 42;

    assert(fsm_init(&fsm, &on_state, &context) == 0);
    // current_state is internal bootstrap_state, so we check initial_state
    assert(fsm.initial_state == &on_state);
    assert(fsm.context == &context);

    // Error cases
    assert(fsm_init(NULL, &on_state, NULL) == -1);
    assert(fsm_init(&fsm, NULL, NULL) == -1);

    printf("test_fsm_init passed\n");
}

void test_fsm_dispatch_null()
{
    struct fsm fsm;
    fsm_init(&fsm, &on_state, NULL);

    assert(fsm_dispatch(NULL, FSM_RUN_EVENT) == -1);
    assert(fsm_dispatch(&fsm, NULL) == -1);

    printf("test_fsm_dispatch_null passed\n");
}

void test_fsm_bootstrap_and_transitions()
{
    struct fsm fsm;
    reset_counters();

    // 1. Init
    fsm_init(&fsm, &on_state, NULL);
    assert(on_state_entry_calls == 0);

    // 2. First dispatch: triggers transition from bootstrap to 'on_state'
    // This calls on_state_on_entry, but NOT on_state_on_run
    fsm_dispatch(&fsm, FSM_RUN_EVENT);
    assert(fsm.current_state == &on_state);
    assert(on_state_entry_calls == 1);
    assert(on_state_run_calls == 0);

    // 3. Second dispatch: executes 'on_state_on_run', which transitions to 'off_state'
    fsm_dispatch(&fsm, FSM_RUN_EVENT);
    assert(on_state_run_calls == 1);
    assert(on_state_exit_calls == 1);
    assert(fsm.current_state == &off_state);
    assert(off_state_entry_calls == 1);

    // 4. Third dispatch: executes 'off_state_on_run', which transitions back to 'on_state'
    fsm_dispatch(&fsm, FSM_RUN_EVENT);
    assert(off_state_run_calls == 1);
    assert(off_state_exit_calls == 1);
    assert(fsm.current_state == &on_state);
    assert(on_state_entry_calls == 2);

    printf("test_fsm_bootstrap_and_transitions passed\n");
}

void test_fsm_self_transition()
{
    struct fsm             fsm;
    struct fsm_event self_event = {.id = 100, .data = NULL};
    reset_counters();

    fsm_init(&fsm, &on_state, NULL);

    // First dispatch to enter on_state
    fsm_dispatch(&fsm, FSM_RUN_EVENT);
    assert(on_state_entry_calls == 1);
    assert(on_state_run_calls == 0);

    // Trigger self-transition
    fsm_dispatch(&fsm, &self_event);

    assert(on_state_run_calls == 1);
    assert(on_state_exit_calls == 1);
    assert(on_state_entry_calls == 2);
    assert(fsm.current_state == &on_state);

    printf("test_fsm_self_transition passed\n");
}

void test_fsm_transition_null()
{
    fsm_transition(NULL, NULL);
    struct fsm fsm;
    fsm_transition(&fsm, NULL);
    fsm_transition(NULL, &on_state);
    printf("test_fsm_transition_null passed\n");
}

int main()
{
    test_fsm_init();
    test_fsm_dispatch_null();
    test_fsm_bootstrap_and_transitions();
    test_fsm_self_transition();
    test_fsm_transition_null();

    printf("All tests passed!\n");

    return 0;
}

uint32_t on_state_on_entry(struct fsm *fsm)
{
    on_state_entry_calls++;
    return 0;
}

struct fsm_state *on_state_on_run(struct fsm             *fsm,
                                  const struct fsm_event *event)
{
    on_state_run_calls++;
    struct fsm_state *next_state = NULL;

    switch (event->id)
    {
    case FSM_RUN_EVENT_ID:
        next_state = &off_state;
        break;

    case 100:
        next_state = &on_state;
        break;

    default:
        break;
    }
    return next_state;
}

uint32_t on_state_on_exit(struct fsm *fsm)
{
    on_state_exit_calls++;
    return 0;
}

uint32_t off_state_on_entry(struct fsm *fsm)
{
    off_state_entry_calls++;
    return 0;
}

struct fsm_state *off_state_on_run(struct fsm             *fsm,
                                   const struct fsm_event *event)
{
    off_state_run_calls++;
    struct fsm_state *next_state = NULL;

    switch (event->id)
    {
    case FSM_RUN_EVENT_ID:
        next_state = &on_state;
        break;

    default:
        break;
    }
    return next_state;
}

uint32_t off_state_on_exit(struct fsm *fsm)
{
    off_state_exit_calls++;
    return 0;
}
