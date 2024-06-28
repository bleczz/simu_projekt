#ifndef SIMU_PROJEKT_MESH_HPP
#define SIMU_PROJEKT_MESH_HPP

#include <iostream>
#include <cstdlib> // for malloc and free

#include "condition.hpp"
#include "element.hpp"
#include "node.hpp"

// Enumeraciones para los parametros y cantidades del problema
enum parameter { THERMAL_CONDUCTIVITY, HEAT_SOURCE };
enum quantity { NUM_NODES, NUM_ELEMENTS, NUM_DIRICHLET, NUM_NEUMANN };

class Mesh {
private:
    float problem_data[2];             // Datos del problema
    int quantities[4];                 // Cantidades del problema
    Node** nodes;                      // Arreglo de nodos
    Element** elements;                // Arreglo de elementos
    Condition** dirichlet_conditions;  // Arreglo de condiciones de dirichlet
    Condition** neumann_conditions;    // Arreglo de condiciones de neumann

public:
    Mesh() : nodes(nullptr), elements(nullptr), dirichlet_conditions(nullptr), neumann_conditions(nullptr) {}  // Constructor

    ~Mesh() { // Destructor para liberar memoria
        for (int i = 0; i < quantities[NUM_NODES]; ++i) delete nodes[i];
        for (int i = 0; i < quantities[NUM_ELEMENTS]; ++i) delete elements[i];
        for (int i = 0; i < quantities[NUM_DIRICHLET]; ++i) delete dirichlet_conditions[i];
        for (int i = 0; i < quantities[NUM_NEUMANN]; ++i) delete neumann_conditions[i];

        delete[] nodes;
        delete[] elements;
        delete[] dirichlet_conditions;
        delete[] neumann_conditions;
    }

    void set_problem_data(float k, float Q) {
        problem_data[THERMAL_CONDUCTIVITY] = k;
        problem_data[HEAT_SOURCE] = Q;
    }

    float get_problem_data(parameter position) const {
        return problem_data[position];
    }

    void set_quantities(int num_nodes, int num_elements, int num_dirichlet, int num_neumann) {
        quantities[NUM_NODES] = num_nodes;
        quantities[NUM_ELEMENTS] = num_elements;
        quantities[NUM_DIRICHLET] = num_dirichlet;
        quantities[NUM_NEUMANN] = num_neumann;
    }

    int get_quantity(quantity position) const {
        return quantities[position];
    }

    void init_arrays() {
        nodes = new Node * [quantities[NUM_NODES]]();
        elements = new Element * [quantities[NUM_ELEMENTS]]();
        dirichlet_conditions = new Condition * [quantities[NUM_DIRICHLET]]();
        neumann_conditions = new Condition * [quantities[NUM_NEUMANN]]();
    }

    void insert_node(Node* node, int position) {
        if (position >= 0 && position < quantities[NUM_NODES]) {
            nodes[position] = node;
        }
        else {
            std::cerr << "Error: Node position out of bounds\n";
        }
    }

    Node* get_node(int position) const {
        if (position >= 0 && position < quantities[NUM_NODES]) {
            return nodes[position];
        }
        else {
            std::cerr << "Error: Node position out of bounds\n";
            return nullptr;
        }
    }

    void insert_element(Element* element, int position) {
        if (position >= 0 && position < quantities[NUM_ELEMENTS]) {
            elements[position] = element;
        }
        else {
            std::cerr << "Error: Element position out of bounds\n";
        }
    }

    Element* get_element(int position) const {
        if (position >= 0 && position < quantities[NUM_ELEMENTS]) {
            return elements[position];
        }
        else {
            std::cerr << "Error: Element position out of bounds\n";
            return nullptr;
        }
    }

    void insert_dirichlet_condition(Condition* dirichlet_condition, int position) {
        if (position >= 0 && position < quantities[NUM_DIRICHLET]) {
            dirichlet_conditions[position] = dirichlet_condition;
        }
        else {
            std::cerr << "Error: Dirichlet condition position out of bounds\n";
        }
    }

    Condition* get_dirichlet_condition(int position) const {
        if (position >= 0 && position < quantities[NUM_DIRICHLET]) {
            return dirichlet_conditions[position];
        }
        else {
            std::cerr << "Error: Dirichlet condition position out of bounds\n";
            return nullptr;
        }
    }

    bool does_node_have_dirichlet_condition(int id) const {
        for (int i = 0; i < quantities[NUM_DIRICHLET]; ++i) {
            if (dirichlet_conditions[i]->get_node()->get_ID() == id) {
                return true;
            }
        }
        return false;
    }

    void insert_neumann_condition(Condition* neumann_condition, int position) {
        if (position >= 0 && position < quantities[NUM_NEUMANN]) {
            neumann_conditions[position] = neumann_condition;
        }
        else {
            std::cerr << "Error: Neumann condition position out of bounds\n";
        }
    }

    Condition* get_neumann_condition(int position) const {
        if (position >= 0 && position < quantities[NUM_NEUMANN]) {
            return neumann_conditions[position];
        }
        else {
            std::cerr << "Error: Neumann condition position out of bounds\n";
            return nullptr;
        }
    }

    void report() const {
        std::cout << "Problem Data\n**********************\n";
        std::cout << "Thermal Conductivity: " << problem_data[THERMAL_CONDUCTIVITY] << "\n";
        std::cout << "Heat Source: " << problem_data[HEAT_SOURCE] << "\n\n";
        std::cout << "Quantities\n***********************\n";
        std::cout << "Number of nodes: " << quantities[NUM_NODES] << "\n";
        std::cout << "Number of elements: " << quantities[NUM_ELEMENTS] << "\n";
        std::cout << "Number of Dirichlet boundary conditions: " << quantities[NUM_DIRICHLET] << "\n";
        std::cout << "Number of Neumann boundary conditions: " << quantities[NUM_NEUMANN] << "\n\n";

        std::cout << "List of nodes\n**********************\n";
        for (int i = 0; i < quantities[NUM_NODES]; ++i) {
            std::cout << "Node: " << nodes[i]->get_ID() << ", x= " << nodes[i]->get_x_coordinate() << ", y= " << nodes[i]->get_y_coordinate() << "\n";
        }

        std::cout << "\nList of elements\n**********************\n";
        for (int i = 0; i < quantities[NUM_ELEMENTS]; ++i) {
            std::cout << "Element: " << elements[i]->get_ID() << ", Node 1= " << elements[i]->get_node1()->get_ID();
            std::cout << ", Node 2= " << elements[i]->get_node2()->get_ID() << ", Node 3= " << elements[i]->get_node3()->get_ID() << ", Node 4= " << elements[i]->get_node4()->get_ID() << "\n";
        }

        std::cout << "\nList of Dirichlet boundary conditions\n**********************\n";
        for (int i = 0; i < quantities[NUM_DIRICHLET]; ++i) {
            std::cout << "Condition " << i + 1 << ": " << dirichlet_conditions[i]->get_node()->get_ID() << ", Value= " << dirichlet_conditions[i]->get_value() << "\n";
        }

        std::cout << "\nList of Neumann boundary conditions\n**********************\n";
        for (int i = 0; i < quantities[NUM_NEUMANN]; ++i) {
            std::cout << "Condition " << i + 1 << ": " << neumann_conditions[i]->get_node()->get_ID() << ", Value= " << neumann_conditions[i]->get_value() << "\n";
        }

        std::cout << "\n";
    }
};

#endif // SIMU_PROJEKT_MESH_HPP