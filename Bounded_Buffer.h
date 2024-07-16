/* Omer Farkash
   211466362 */

#ifndef Bounded_Buffer_h
#define Bounded_Buffer_h

class Bounded_Buffer
{
private:
    int size;

public:
    Bounded_Buffer(int size);
    ~Bounded_Buffer();
    
    void insert(void* s);
    char* remove();
};

#endif // Bounded_Buffer_h
