// shm_words.h
#define TEXT_SZ 100

struct shared_data {
    int written;
    char text[TEXT_SZ];
};

