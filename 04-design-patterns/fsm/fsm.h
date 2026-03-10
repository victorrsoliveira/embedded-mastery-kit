/**
 * @file fsm.h
 * @author Victor Oliveira (victor.rsoliveira@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-03-09
 *
 */

#ifndef FSM_H
#define FSM_H

#include <stddef.h>
#include <stdint.h>

#define FSM_RUN_EVENT_ID 1U
#define FSM_RUN_EVENT    &_FSM_RUN_EVENT

extern const struct fsm_event _FSM_RUN_EVENT;

struct fsm_event
{
    uint32_t id;
    void    *data;
};

// NOTE: Forward declaration for the fsm_action_fn_t
struct fsm;

// NOTE: Forward declaration for the struct fsm_state itself
struct fsm_state;

struct fsm_state
{
    uint32_t (*on_entry)(struct fsm *fsm);
    struct fsm_state *(*on_run)(struct fsm *fsm, const struct fsm_event *event);
    uint32_t (*on_exit)(struct fsm *fsm);
    //? QUESTION: state context variable?
};

struct fsm
{
    struct fsm_state *current_state;
    void             *context;
};

uint32_t fsm_init(struct fsm *fsm, struct fsm_state *initial, void *context);

uint32_t fsm_dispatch(struct fsm *fsm, const struct fsm_event *event);

void fsm_transition(struct fsm *fsm, struct fsm_state *new);

#endif  // FSM_H
