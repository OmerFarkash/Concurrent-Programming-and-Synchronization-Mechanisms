/* Omer Farkash
   211466362 */

#include "Producer.h"

Producer::Producer(int id, int num_of_productions, Bounded_Buffer* buffer) {
    this->id = id;
    this->num_of_productions = num_of_productions;
    this->buffer = buffer;
}

Producer::~Producer() {
    delete buffer;
}

void Producer::produce() {
    int s = 0;
    int n = 0;
    int w = 0;
    int random;
    std::string type;
    std::string output;
    for (int i = 0; i < num_of_productions; i++) {
        // take a random number between 1 and 3
        random = rand() % 3 + 1;
        if (random == 1) {
            type = "SPORTS ";
            output = "Producer " + std::to_string(id) + " " + type + std::to_string(s);
            s++;
        } else if (random == 2) {
            type = "NEWS ";
            output = "Producer " + std::to_string(id) + " " + type + std::to_string(n);
            n++;
        } else {
            type = "WEATHER ";
            output = "Producer " + std::to_string(id) + " " + type + std::to_string(w);
            w++;
        }
        buffer->insert(output);
    }
    buffer->insert("DONE");
}