#include "ParsePlan.h"

PostOnline::PostOnline(ExecuteOfflineCommand Execute)
{
    commandExecution = Execute;
}

void PostOnline::CreatePlanTimer(byte PlanNumber, unsigned long intervals[])
{
    char PlanTimerName[11] = "PlanTimer";
    for (int i = 0; i < PlanNumber; i++)
    {
        PlanTimerName[9] = (char)(i + 48 - 10 * (i / 10)); // convert int to char (0-9)

        // IDK if this block of code is needed to be in the loop or not
        PlanTimerArgs.callback = &PlanCallback;
        PlanTimerArgs.arg = &commandExecution;
        PlanTimerArgs.name = PlanTimerName;

        esp_timer_create(&PlanTimerArgs, &PlanTimer[i]);
    }
    for (int i = 0; i < PlanNumber; i++)
    {
        esp_timer_start_periodic(PlanTimer[i], intervals[i] * 1000000);
    }
}

void PostOnline::PlanCallback(void *arg)
{
    ExecuteOfflineCommand *_commandExecution = (ExecuteOfflineCommand *)arg;
    _commandExecution->InitExecution();
}