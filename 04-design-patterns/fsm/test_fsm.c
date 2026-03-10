/**
 * @file test_fsm.c
 * @author Victor Oliveira (victor.rsoliveira@gmail.com)
 * @brief
 * @version 0.1
 * @date 2026-03-10
 *
 */

#include <stdio.h>

#include "fsm.h"

uint32_t          on_state_on_entry(struct fsm *fsm);
struct fsm_state *on_state_on_run(struct fsm             *fsm,
                                  const struct fsm_event *event);
uint32_t          on_state_on_exit(struct fsm *fsm);

uint32_t          off_state_on_entry(struct fsm *fsm);
struct fsm_state *off_state_on_run(struct fsm             *fsm,
                                   const struct fsm_event *event);
uint32_t          off_state_on_exit(struct fsm *fsm);

struct fsm_state on_state  = {.on_entry = NULL,
                              .on_run   = on_state_on_run,
                              .on_exit  = NULL};
struct fsm_state off_state = {.on_entry = NULL,
                              .on_run   = off_state_on_run,
                              .on_exit  = NULL};

int main()
{
    struct fsm fsm;

    fsm_init(&fsm, &on_state, NULL);

    for (int i = 0; i < 6; i++)
    {
        fsm_dispatch(&fsm, FSM_RUN_EVENT);
    }

    return 0;
}

uint32_t on_state_on_entry(struct fsm *fsm)
{
    return 0;
}

struct fsm_state *on_state_on_run(struct fsm             *fsm,
                                  const struct fsm_event *event)
{
    struct fsm_state *next_state = NULL;

    switch (event->id)
    {
    case FSM_RUN_EVENT_ID:
        printf("ON\n");
        next_state = &off_state;
        break;

    default:
        break;
    }
    return next_state;
}

uint32_t on_state_on_exit(struct fsm *fsm)
{
    return 0;
}

uint32_t off_state_on_entry(struct fsm *fsm)
{
    return 0;
}
struct fsm_state *off_state_on_run(struct fsm             *fsm,
                                   const struct fsm_event *event)
{
    struct fsm_state *next_state = NULL;

    switch (event->id)
    {
    case FSM_RUN_EVENT_ID:
        printf("OFF\n");
        next_state = &on_state;
        break;

    default:
        break;
    }
    return next_state;
}
uint32_t off_state_on_exit(struct fsm *fsm)
{
    return 0;
}