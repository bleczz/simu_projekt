#ifndef SIMU_PROJEKT_VECTOR_HPP
#define SIMU_PROJEKT_VECTOR_HPP

#include <iostream>
#include <cstdlib> // for malloc and free

// Definition of the Vector class
class Vector {
private:
    int size;     // size of the vector
    float* data;  // pointer to store vector data

    // Method to create the vector data structure
    void create() {
        data = (float*)malloc(sizeof(float) * size);  // allocate memory for vector data
    }

public:
    // Default constructor
    Vector() : size(0), data(nullptr) {}

    // Constructor that initializes the vector with a number of elements
    Vector(int data_qty) : size(data_qty), data(nullptr) {
        create();  // create the vector data structure
    }

    // Destructor to free allocated memory
    ~Vector() {
        if (data != nullptr) {
            free(data);  // free the memory allocated for vector data
        }
    }

    // Method to initialize the vector with zeros
    void init() {
        for (int i = 0; i < size; i++)
            data[i] = 0;  // assign zero to each element of the vector
    }

    // Method to set the size of the vector and create the data structure
    void set_size(int num_values) {
        if (data != nullptr) {
            free(data);
        }
        size = num_values;  // assign the size of the vector
        create();  // create the vector data structure
    }

    // Method to get the size of the vector
    int get_size() const {
        return size;  // return the size of the vector
    }

    // Method to set the value of an element at a given position
    void set(float value, int position) {
        data[position] = value;  // assign the value at the given position
    }

    // Method to add a value to an element at a given position
    void add(float value, int position) {
        data[position] += value;  // add the value to the element at the given position
    }

    // Method to get the value of an element at a given position
    float get(int position) const {
        return data[position];
    }

    // Method to remove an element from the vector
    void remove_row(int row) {
        int neo_index = 0;
        float* neo_data = (float*)malloc(sizeof(float) * (size - 1));
        for (int i = 0; i < size; i++)
            if (i != row) {
                neo_data[neo_index] = data[i];
                neo_index++;
            }
        free(data);
        data = neo_data;
        size--;
    }

    // Method to display the vector
    void show() const {
        std::cout << "[ " << data[0];
        for (int i = 1; i < size; i++)
            std::cout << "; " << data[i];
        std::cout << " ]\n\n";
    }
};

#endif  // SIMU_PROJEKT_VECTOR_HPP

