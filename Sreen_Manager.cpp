/* Omer Farkash
   211466362 */

#include "Screen_Manager.h"

Screen_Manager::Screen_Manager(Bounded_Buffer * shared) {
   this->shared_queue = shared;
}

Screen_Manager::~Screen_Manager() {
   delete shared_queue;
}

void Screen_Manager::display() {
   std::string product;
   while (done > 0) {
      product = shared_queue->remove();
      if (product.find("DONE") != std::string::npos) {
         done--;
      }
      else if (product.find("") != std::string::npos) {
         std::cout << product << std::endl;
      }
   }
   std::cout << "DONE" << std::endl;
   return;
}