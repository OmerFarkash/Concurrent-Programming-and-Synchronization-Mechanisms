/* Omer Farkash
   211466362 */

#ifndef Screen_Manager_h
#define Screen_Manager_h

#include <iostream>
#include "Bounded_Buffer.h"

class Screen_Manager
{
private:
   Bounded_Buffer * shared_queue;
   int done = 3;
public:
   Screen_Manager(Bounded_Buffer * shared);
   ~Screen_Manager();
   void display();
};

#endif // Screen_Manager_h