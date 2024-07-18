/* Omer Farkash
   211466362 */

#ifndef Producer_h
#define Producer_h

#include "Bounded_Buffer.h"
#include <random>
class Producer
{
private:
    int id;
    int num_of_productions;
    Bounded_Buffer* buffer;
    
public:
    Producer(int id, int num_of_productions, Bounded_Buffer* buffer);
    ~Producer();

    void produce();
}; 

#endif /* Producer_h */ 

