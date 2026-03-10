/**
 * @file fsm.c
 * @author Victor Oliveira (victor.rsoliveira@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-03-09
 *
 */

#include "fsm.h"

const struct fsm_event _FSM_RUN_EVENT = {.id = FSM_RUN_EVENT_ID, .data = NULL};

uint32_t fsm_init(struct fsm *fsm, struct fsm_state *initial, void *context)
{
    if ((fsm == NULL) || (initial == NULL))
    {
        return -1;
    }

    fsm->current_state = initial;
    fsm->context       = context;

    return 0;
}

uint32_t fsm_dispatch(struct fsm *fsm, const struct fsm_event *event)
{
    struct fsm_state *new;
    if ((fsm == NULL) || (event == NULL))
    {
        return -1;
    }

    if (fsm->current_state->on_run)
    {
        new = fsm->current_state->on_run(fsm, event);
        fsm_transition(fsm, new);
    }
    return 0;
}

void fsm_transition(struct fsm *fsm, struct fsm_state *new)
{
    if ((fsm == NULL) || (new == NULL))
    {
        return;
    }

    if (fsm->current_state->on_exit)
    {
        fsm->current_state->on_exit(fsm);
    }

    fsm->current_state = new;

    if (fsm->current_state->on_entry)
    {
        fsm->current_state->on_entry(fsm);
    }
}