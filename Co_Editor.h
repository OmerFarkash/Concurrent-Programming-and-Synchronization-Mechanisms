/* Omer Farkash
   211466362 */

#ifndef Co_Editor_h
#define Co_Editor_h


#include <thread>
#include "Unbounded_Buffer.h"
#include "Bounded_Buffer.h"


class Co_Editor
{
private:
   Bounded_Buffer * shared_queue;
   Unbounded_Buffer * type;
public:
   Co_Editor(Bounded_Buffer * shared, Unbounded_Buffer * type);
   ~Co_Editor();
   void edit();
};

#endif // Co_Editor_h