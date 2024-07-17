/* Omer Farkash
   211466362 */

#ifndef Bounded_Buffer_h
#define Bounded_Buffer_h

#include "Unbounded_Buffer.h"

class Bounded_Buffer : public Unbounded_Buffer {
private:
    int max_size;
    sem_t not_full; // Binary semaphore to indicate if the buffer is not full

public:
    Bounded_Buffer(int size);
    ~Bounded_Buffer();
    
    void insert(std::string s) override;
    std::string remove() override;
};

#endif // Bounded_Buffer_h
