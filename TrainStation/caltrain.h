#ifndef TRAINSTATION_CALTRAIN_H
#define TRAINSTATION_CALTRAIN_H

#include <pthread.h>

struct station {
    int free_seats;
    int waiting_passengers;
    int boarding_passengers;
    pthread_mutex_t station_mutex;
    pthread_cond_t train_available;
    pthread_cond_t all_passengers_boarded;
};

void station_init(struct station *station);

void station_load_train(struct station *station, int count);

void station_wait_for_train(struct station *station);

void station_on_board(struct station *station);

#endif //TRAINSTATION_CALTRAIN_H
