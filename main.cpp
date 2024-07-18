/* Omer Farkash
   211466362 */

#include <fstream>

#include "Bounded_Buffer.h"
#include "Unbounded_Buffer.h"
#include "Co_Editor.h"
#include "Dispatcher.h"
#include "Producer.h"
#include "Screen_Manager.h"

int main(int argc, char *argv[]) {
    std::string filename = argv[1];
    std::list<Producer*> producers;
    std::list<Bounded_Buffer*> producers_queues;
    Dispatcher* dispatcher = nullptr;
    std::array<Unbounded_Buffer*, 3> dispatcher_queues = {nullptr, nullptr, nullptr};
    std::array<Co_Editor*, 3> co_editors = {nullptr, nullptr, nullptr};
    Bounded_Buffer* shared_queue = nullptr;   
    Screen_Manager* screen_manager = nullptr;

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return -1;
    }

    // Parse config file
    std::string line;
    while (std::getline(file, line)) {
        if (line.find("PRODUCER") != std::string::npos) {
            int producerNumber;
            size_t pos = line.find(' ');
            producerNumber = std::stoi(line.substr(pos + 1));

            if (!std::getline(file, line)) break;
            int numberOfProducts = std::stoi(line);

            if (!std::getline(file, line)) break;
            pos = line.find('=');
            int queueSize = std::stoi(line.substr(pos + 1));

            // create producer queue
            Bounded_Buffer* producerQueue = new (std::nothrow) Bounded_Buffer(queueSize);
            if (!producerQueue) {
                std::cerr << "Failed to allocate memory for producerQueue" << std::endl;
                return -1;
            }
            producers_queues.push_back(producerQueue);

            // create producer
            Producer* producer = new Producer(producerNumber, numberOfProducts, producerQueue);
            producers.push_back(producer);
        } else if (line.find("Co-Editor queue size") != std::string::npos) {
            size_t pos = line.find('=');
            int queueSize = std::stoi(line.substr(pos + 1));
            shared_queue = new Bounded_Buffer(queueSize);
        }
    }
    file.close();

    // create dispatcher queues
    for (int i = 0; i < 3; i++) {
        dispatcher_queues[i] = new Unbounded_Buffer();
    }

    // Create dispatcher
    dispatcher = new Dispatcher(producers.size(), &producers_queues, dispatcher_queues);

    // Create co-editors
    for (int i = 0; i < 3; i++) {
        co_editors[i] = new Co_Editor(shared_queue, dispatcher_queues[i]);
    }    
    
    // Create screen manager
    screen_manager = new Screen_Manager(shared_queue);

    // Run
    // Create threads for producers for thier "produce" function
    for (auto producer : producers) {
        std::thread t(&Producer::produce, producer);
        t.detach();
    }

    // Create thread for dispatcher
    std::thread t(&Dispatcher::handle_products, dispatcher);
    t.detach();

    // Create threads for co-editors
    for (int i = 0; i < 3; i++) {
        std::thread t(&Co_Editor::edit, co_editors[i]);
        t.detach();
    }

    // Create thread for screen manager
    std::thread sm(&Screen_Manager::display, screen_manager);    
    sm.join();

    // Cleanup

    return 0;
}