/* Omer Farkash
   211466362 */

#include "Dispatcher.h"


Dispatcher::Dispatcher(int num_of_producers, std::list<Bounded_Buffer*> * producers_queues, std::array<Unbounded_Buffer*, 3> Dispatcher_queues)
{
   done_counter = num_of_producers;
   this->producers_queues = producers_queues;
   this->Dispatcher_queues = Dispatcher_queues;
}

void Dispatcher::handle_products() {
   std::string product;
   while (done_counter > 0) {
      for (auto it = producers_queues->begin(); it != producers_queues->end();) {
         product = (*it)->remove();
         if (product.find("DONE") != std::string::npos) {
            done_counter--;
            it = producers_queues->erase(it); // Remove and advance iterator
         } else {
            if (!product.empty()) {
                  if (product.find("SPORTS") != std::string::npos) {
                     Dispatcher_queues[0]->insert(product);
                  } else if (product.find("WEATHER") != std::string::npos) {
                     Dispatcher_queues[1]->insert(product);
                  } else if (product.find("NEWS") != std::string::npos) {
                     Dispatcher_queues[2]->insert(product);
                  }
            }
            ++it; // Advance iterator
         }
      }
   }
   // insert "DONE" to the Dispatcher queues
   for (int i = 0; i < 3; i++) {
      Dispatcher_queues[i]->insert("DONE");
   }
   return;
}