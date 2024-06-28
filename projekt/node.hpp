#ifndef SIMU_PROJEKT_NODE_HPP
#define SIMU_PROJEKT_NODE_HPP

class Node {
private:
    int ID;              // identificador del nodo
    float x_coordinate;  // coordenada x del nodo
    float y_coordinate;  // coordenada y del nodo
    float z_coordinate;  // coordenada z del nodo

public:
    // Constructor que inicializa el nodo con un identificador y coordenadas
    Node(int identifier, float x_value, float y_value, float z_value)
        : ID(identifier), x_coordinate(x_value), y_coordinate(y_value), z_coordinate(z_value) {}

    // Metodo para establecer el identificador del nodo
    void set_ID(int identifier) { ID = identifier; }

    // Metodo para obtener el identificador del nodo
    int get_ID() const { return ID; }

    // Metodo para establecer la coordenada x del nodo
    void set_x_coordinate(float x_value) { x_coordinate = x_value; }

    // Metodo para obtener la coordenada x del nodo
    float get_x_coordinate() const { return x_coordinate; }

    // Metodo para establecer la coordenada y del nodo
    void set_y_coordinate(float y_value) { y_coordinate = y_value; }

    // Metodo para obtener la coordenada y del nodo
    float get_y_coordinate() const { return y_coordinate; }

    // Metodo para establecer la coordenada z del nodo
    void set_z_coordinate(float z_value) { z_coordinate = z_value; }

    // Metodo para obtener la coordenada z del nodo
    float get_z_coordinate() const { return z_coordinate; }
};

#endif  // SIMU_PROJEKT_NODE_HPP