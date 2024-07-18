/* Omer Farkash
   211466362 */

#ifndef Dispatcher_h
#define Dispatcher_h

#include <string>
#include <list>
#include <array>
#include "Bounded_Buffer.h"

class Dispatcher
{
private:
   int done_counter;
   std::list<Bounded_Buffer*> * producers_queues;
   std::array<Unbounded_Buffer*, 3> Dispatcher_queues; // Remove the asterisk (*) before Dispatcher_queues
public:
   Dispatcher(int num_of_producers, std::list<Bounded_Buffer*> * producers_queues, std::array<Unbounded_Buffer*, 3> Dispatcher_queues);
   void handle_products();
};

#endif // DISPATCHER_H