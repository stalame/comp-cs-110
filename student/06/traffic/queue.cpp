#include "queue.hh"
#include <iostream>

using namespace std;

Queue::Queue(unsigned int cycle)
    : cycle_(cycle)
{
}

void Queue::enqueue(const std::string& reg)
{
    if (is_green_) {
        // Vehicle does not stop, passes directly
        std::cout << "GREEN: The vehicle " << reg << " need not stop to wait" << std::endl;
        return;
    }

    // Red light: add to queue
    auto new_vehicle = std::make_shared<Vehicle>();
    new_vehicle->reg_num = reg;
    new_vehicle->next = nullptr;

    if (!first_) {
        first_ = last_ = new_vehicle;
    } else {
        last_->next = new_vehicle;
        last_ = new_vehicle;
    }
}

bool Queue::dequeue(string& reg)
{
    if (!first_)
        return false;

    reg = first_->reg_num;
    first_ = first_->next;

    if (!first_)
        last_ = nullptr;

    return true;
}

void Queue::switch_light()
{
    if (!is_green_) {
        // Switching red -> green
        if (!first_) {
            // Queue empty, nothing passes
            std::cout << "GREEN: No vehicles waiting in traffic lights" << std::endl;
        } else {
            std::cout << "GREEN: Vehicle(s)";
            unsigned int count = 0;
            while (count < cycle_ && first_) {
                std::cout << " " << first_->reg_num;
                first_ = first_->next;
                ++count;
            }
            std::cout << " can go on" << std::endl;

            // Update last_ if queue is empty now
            if (!first_) last_ = nullptr;
        }

        // Automatically switch back to red
        is_green_ = false;
    } else {
        // Switching green -> red
        is_green_ = false;

        if (!first_) {
            std::cout << "RED: No vehicles waiting in traffic lights" << std::endl;
        } else {
            std::cout << "RED: Vehicle(s)";
            auto curr = first_;
            while (curr) {
                std::cout << " " << curr->reg_num;
                curr = curr->next;
            }
            std::cout << " waiting in traffic lights" << std::endl;
        }
    }
}

void Queue::reset_cycle(unsigned int cycle)
{
    cycle_ = cycle;
}

void Queue::print() const
{
    cout << (is_green_ ? "GREEN" : "RED") << ": ";

    if (!first_) {
        cout << "No vehicles waiting in traffic lights" << endl;
        return;
    }

    cout << "Vehicle(s) ";
    auto curr = first_;
    while (curr) {
        cout << curr->reg_num;
        if (curr->next)
            cout << " ";
        curr = curr->next;
    }
    cout << " waiting in traffic lights" << endl;
}
