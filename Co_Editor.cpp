/* Omer Farkash
   211466362 */

#include "Co_Editor.h"

Co_Editor::Co_Editor(Unbounded_Buffer * shared, Bounded_Buffer * type) {
   this->shared_queue = shared;
   this->type = type;
}

Co_Editor::~Co_Editor() {
   delete shared_queue;
   delete type;
}

void Co_Editor::edit() {
   std::string product;
   while (true) {
      product = type->remove();
      if (product.find("DONE") != std::string::npos) {
         shared_queue->insert("DONE");
         break;
      }
      else {
         // sleep for 0.1 seconds
         std::this_thread::sleep_for(std::chrono::milliseconds(100));
         shared_queue->insert(product);
      }
   }
   return;
}