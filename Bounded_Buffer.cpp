/* Omer Farkash
   211466362 */

#include "Bounded_Buffer.h"
#include <stdexcept>
#include <iostream>

Bounded_Buffer::Bounded_Buffer(int max_size) : Unbounded_Buffer(), max_size(max_size) {
    if (sem_init(&not_full, 0, max_size) != 0) { // Initially, the buffer has space for max_size elements
        throw std::runtime_error("Failed to initialize semaphore");
    }
}

Bounded_Buffer::~Bounded_Buffer() {
    sem_destroy(&not_full);
    Unbounded_Buffer::~Unbounded_Buffer();
}

void Bounded_Buffer::insert(std::string s) {
    // Wait until there is space in the buffer
    sem_wait(&not_full);
    Unbounded_Buffer::insert(s); // Insert the item
}

std::string Bounded_Buffer::remove() {
    std::string s = Unbounded_Buffer::remove(); // Remove the item
    // If an item was removed, signal that the buffer has space
    sem_post(&not_full);
    return s;
}