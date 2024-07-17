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
   Unbounded_Buffer * shared_queue;
   Bounded_Buffer * type;
public:
   Co_Editor(Unbounded_Buffer * shared, Bounded_Buffer * type);
   ~Co_Editor();
   void edit();
};

#endif // Co_Editor_h