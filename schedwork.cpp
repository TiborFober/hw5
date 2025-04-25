#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool scheduleHelper(
    const AvailabilityMatrix& avail,
    size_t dailyNeed,
    size_t maxShifts,
    DailySchedule& sched,
    vector<int>& shifts,
    size_t day,
    size_t slot );

bool alreadyScheduledToday(const vector<Worker_T>& daySchedule, Worker_T worker)
{
    return find(daySchedule.begin(), daySchedule.end(), worker) != daySchedule.end();
}

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0){
        return false;
    }
    sched.clear();
    // Add your code below

    size_t n = avail.size();
    size_t k = avail[0].size();

    sched.resize(n, vector<Worker_T>(dailyNeed, -1));

    vector<int> shifts(k, 0);

    return scheduleHelper(avail, dailyNeed, maxShifts, sched, shifts, 0, 0);
}

bool scheduleHelper(
    const AvailabilityMatrix& avail,
    size_t dailyNeed,
    size_t maxShifts,
    DailySchedule& sched,
    vector<int>& shifts,
    size_t day,
    size_t slot )
{
    if(day == sched.size())
    {
        return true;
    }

    if(slot == dailyNeed)
    {
        return scheduleHelper(avail, dailyNeed, maxShifts, sched, shifts, day + 1, 0);
    }

    for(size_t worker = 0; worker < avail[0].size(); ++worker)
    {
        if(avail[day][worker] && shifts[worker] < maxShifts && !alreadyScheduledToday(sched[day], worker))
        {
            sched[day][slot] = worker;
            shifts[worker]++;

            if(scheduleHelper(avail, dailyNeed, maxShifts, sched, shifts, day, slot + 1 ))
            {
                return true;
            }

            shifts[worker]--;
            sched[day][slot] = -1;
            
        }
    }

    return false;
}

