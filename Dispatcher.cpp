/* Omer Farkash
   211466362 */

#include "Dispatcher.h"


Dispatcher::Dispatcher(int num_of_producers, std::list<Bounded_Buffer*> * producers_queues, std::array<Bounded_Buffer*, 3> Dispatcher_queues)
{
   done_counter = num_of_producers;
   this->producers_queues = producers_queues;
   this->Dispatcher_queues = Dispatcher_queues;
}

Dispatcher::~Dispatcher()
{
   for (std::list<Bounded_Buffer*>::iterator it = producers_queues->begin(); it != producers_queues->end(); it++) {
      delete *it;
   }
   for (int i = 0; i < 3; i++) {
      delete Dispatcher_queues[i];
   }
}

void Dispatcher::handle_products()
{
   std::string product;
   while (done_counter > 0) {
      for (std::list<Bounded_Buffer*>::iterator it = producers_queues->begin(); it != producers_queues->end(); it++) {   
         product = (*it)->remove();
         if (product.find("SPORTS") != std::string::npos) {
            Dispatcher_queues[0]->insert(product);
         }
         else if (product.find("WEATHER") != std::string::npos) {
            Dispatcher_queues[1]->insert(product);
         }
         else if (product.find("NEWS") != std::string::npos) {
            Dispatcher_queues[2]->insert(product);
         }
         else if (product.find("DONE") != std::string::npos) {
            done_counter--;
            // remove this bounded buffer from the list
            producers_queues->remove(*it);
         }
         else if (product.find("") != std::string::npos) {
            // move on to the next producer - buffer is empty / mutex not acquired.
            // come back to this producer later
            continue;
         }
      }
   }
   // insert "DONE" to the Dispatcher queues
   for (int i = 0; i < 3; i++) {
      Dispatcher_queues[i]->insert("DONE");
   }

   return;
}
