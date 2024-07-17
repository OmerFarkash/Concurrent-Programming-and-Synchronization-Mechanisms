/* Omer Farkash
   211466362 */

#ifndef Unbounded_Buffer_h
#define Unbounded_Buffer_h

#include <queue>
#include <semaphore.h>
#include <string>

class Unbounded_Buffer {
protected:
    std::queue<std::string> buffer;
    sem_t mutex; // Binary semaphore for mutual exclusion
    sem_t is_empty; // Binary semaphore to indicate if the buffer is empty

public:
    Unbounded_Buffer();
    virtual ~Unbounded_Buffer();
    
    virtual void insert(std::string s);
    virtual std::string remove();
};

#endif // Unbounded_Buffer_h
