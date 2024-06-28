#ifndef SIMU_PROJEKT_INPUT_OUTPUT_HPP
#define SIMU_PROJEKT_INPUT_OUTPUT_HPP

#include <fstream>
#include <iostream>
#include <string>
#include "mesh.hpp"
#include "vector.hpp"

// Metodo para leer los datos de entrada desde un archivo y poblar el objeto Mesh
void read_input(const std::string& filename, Mesh* M) {
    std::string line;
    float k, Q, T_bar, T_hat;
    int num_nodes, num_elements, num_dirichlet, num_neumann;
    std::ifstream dat_file(filename + ".dat");  // abrir archivo de datos en modo lectura

    if (!dat_file) {
        std::cerr << "Error opening file: " << filename << ".dat\n";
        return;
    }

    // Leer los datos desde archivo
    dat_file >> k >> Q >> T_bar >> T_hat >> num_nodes >> num_elements >> num_dirichlet >> num_neumann;

    M->set_problem_data(k, Q);  // Establecer los datos del problema
    M->set_quantities(num_nodes, num_elements, num_dirichlet, num_neumann);  // Establecer las cantidades
    M->init_arrays();  // Inicializar los arreglos

    dat_file >> line;

    // Insertar nodos en el arreglo de nodos
    for (int i = 0; i < num_nodes; i++) {
        int id;
        float x, y, z;
        dat_file >> id >> x >> y >> z;
        M->insert_node(new Node(id, x, y, z), i);
    }

    dat_file >> line;

    // Insertar elementos en el arreglo de elementos
    for (int i = 0; i < num_elements; i++) {
        int id, node1_id, node2_id, node3_id, node4_id;
        dat_file >> id >> node1_id >> node2_id >> node3_id >> node4_id;

        // Ensure nodes are initialized before using them
        Node* node1 = M->get_node(node1_id - 1);
        Node* node2 = M->get_node(node2_id - 1);
        Node* node3 = M->get_node(node3_id - 1);
        Node* node4 = M->get_node(node4_id - 1);

        if (node1 && node2 && node3 && node4) {
            M->insert_element(new Element(id, node1, node2, node3, node4), i);
        }
        else {
            std::cerr << "Error: One or more nodes for element " << id << " are not initialized\n";
        }
    }

    dat_file >> line;

    // Insertar condiciones de Dirichlet en el arreglo de condiciones de Dirichlet
    for (int i = 0; i < num_dirichlet; i++) {
        int id;
        dat_file >> id;
        M->insert_dirichlet_condition(new Condition(M->get_node(id - 1), T_bar), i);
    }

    dat_file >> line;

    // Insertar condiciones de Neumann en el arreglo de condiciones de Neumann
    for (int i = 0; i < num_neumann; i++) {
        int id;
        dat_file >> id;
        M->insert_neumann_condition(new Condition(M->get_node(id - 1), T_hat), i);
    }

    dat_file.close();  // Cerrar archivo
}

// Metodo para escribir los resultados en un archivo de salida
void write_output(const std::string& filename, Vector* T) {
    std::string full_filename = filename + ".post.res";
    std::ofstream res_file(full_filename);  // Abrir archivo de resultados en modo escritura

    if (!res_file) {
        std::cerr << "Error opening file: " << full_filename << "\n";
        return;
    }

    res_file << "GiD Post Results File 1.0\n";  // Escribir encabezado del archivo de resultados

    int n = T->get_size();

    res_file << R"(Result "Temperature" "Load Case 1" )" << 1 << R"( Scalar OnNodes\n)";
    res_file << "ComponentNames \"T\"\n";  // Nombre genérico de la variable
    res_file << "Values\n";

    for (int i = 0; i < n; i++)
        res_file << i + 1 << "     " << T->get(i) << "\n";

    res_file << "End values\n";
    res_file.close();  // Cerrar el archivo

    // Print the location of the file
    std::cout << "File written to: " << full_filename << "\n";
}

#endif  // SIMU_PROJEKT_INPUT_OUTPUT_HPP