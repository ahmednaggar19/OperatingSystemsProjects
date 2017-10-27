#include <pthread.h>
#include <stdio.h>
#include "caltrain.h"



void
station_init(struct station *station)
{
    // station variables
    station->free_seats = 0;
    station->waiting_passengers = 0;
    station->boarding_passengers = 0;

    // station mutex
    pthread_mutex_init(&station->station_mutex, NULL);

    // station condition variables
    pthread_cond_init(&station->train_available, NULL);
    pthread_cond_init(&station->all_passengers_boarded, NULL);
}

void
station_load_train(struct station *station, int count)
{
    //if (count == 0) {return;} // no free seats available on train
    pthread_mutex_lock(&station->station_mutex);
    station->free_seats = count;  // set free seats to count of free seats on train
    while (station->free_seats > 0 && station->waiting_passengers > 0)
    {
        // notify all passengers with train arrival
        pthread_cond_broadcast(&station->train_available);
        // wait for all passengers to board
        pthread_cond_wait(&station->all_passengers_boarded,&station->station_mutex);
        if (station->boarding_passengers > 0) {
            // to make sure all passengers called station_on_board()
            continue;
        }
    }
    // reset
    station->free_seats = 0;
    station->boarding_passengers = 0;
    printf("Count : %d -- Waiting : %d -- Boarding : %d\n", count, station->waiting_passengers, station->boarding_passengers);
    pthread_mutex_unlock(&station->station_mutex);
}

void
station_wait_for_train(struct station *station)
{
    pthread_mutex_lock(&station->station_mutex);
    station->waiting_passengers++;   // passenger is in [ waiting ] state now
    while (station->free_seats == station->boarding_passengers) {
        pthread_cond_wait(&station->train_available, &station->station_mutex);
    }
    station->waiting_passengers--;  // change of state
    station->boarding_passengers++; // passenger is now [ boarding ] and NO longer [ waiting ]
    pthread_mutex_unlock(&station->station_mutex);
}

void
station_on_board(struct station *station)
{
    pthread_mutex_lock(&station->station_mutex);
    station->boarding_passengers--; // now passenger is boarded and no longer boarding
    station->free_seats--;  // passenger has taken his seat in the train
    if (station->free_seats == 0 ||
            (station->boarding_passengers == 0 && station->waiting_passengers == 0) ) { // check if train should leave
        pthread_cond_signal(&station->all_passengers_boarded);
    }
    pthread_mutex_unlock(&station->station_mutex);
}
