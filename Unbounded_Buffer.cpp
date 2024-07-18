/* Omer Farkash
   211466362 */

#include "Unbounded_Buffer.h"
#include <stdexcept>

Unbounded_Buffer::Unbounded_Buffer() {
    buffer = std::queue<std::string>();
    if (sem_init(&mutex, 0, 1) != 0) {
        throw std::runtime_error("Failed to initialize mutex semaphore");
    }
    if (sem_init(&is_empty, 0, 0) != 0) { // Initially empty
        throw std::runtime_error("Failed to initialize is_empty semaphore");
    }
}

Unbounded_Buffer::~Unbounded_Buffer() {
    sem_destroy(&mutex);
    sem_destroy(&is_empty);
}

void Unbounded_Buffer::insert(std::string s) {
    if (sem_wait(&mutex) != 0) {
        throw std::runtime_error("Failed to lock mutex");
    }
    buffer.push(s);
    sem_post(&is_empty); // Signal that the buffer is not empty
    sem_post(&mutex); // Exit critical section
}

std::string Unbounded_Buffer::remove() {
    if (sem_trywait(&is_empty) != 0) {
        return ""; // Buffer is empty, return NULL equivalent for std::string
    }
    if (sem_trywait(&mutex) != 0) {
        sem_post(&is_empty); // Release is_empty if we fail to lock mutex
        return ""; // Failed to acquire mutex, return NULL equivalent for std::string
    }
    
    std::string s = buffer.front();
    buffer.pop();
    
    sem_post(&mutex); // Exit critical section

    return s;
}
