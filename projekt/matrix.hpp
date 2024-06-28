#ifndef SIMU_PROJEKT_MATRIX_HPP
#define SIMU_PROJEKT_MATRIX_HPP

#include <iostream>
#include <cstdlib> // for malloc and free

class Matrix {
private:
    int nrows, ncols; // number of rows and columns in the matrix
    float** data;     // double pointer to store matrix data

    // method to create the matrix data structure
    void create() {
        data = (float**)malloc(sizeof(float*) * nrows); // allocate memory for rows
        for (int r = 0; r < nrows; r++)
            data[r] = (float*)malloc(sizeof(float) * ncols); // allocate memory for columns
    }

public:
    // default constructor
    Matrix() : nrows(0), ncols(0), data(nullptr) {}

    // constructor to initialize matrix with given number of rows and columns
    Matrix(int rows, int cols) : nrows(rows), ncols(cols), data(nullptr) {
        create(); // create the data structure
    }

    // destructor to free allocated memory
    ~Matrix() {
        if (data != nullptr) {
            for (int r = 0; r < nrows; r++)
                if (data[r] != nullptr)
                    free(data[r]); // free memory for each row
            free(data); // free memory for row pointers
        }
    }

    // method to initialize the matrix with zeros
    void init() {
        for (int r = 0; r < nrows; r++)
            for (int c = 0; c < ncols; c++)
                data[r][c] = 0; // set each element to zero
    }

    // method to set the size of the matrix and create the data structure
    void set_size(int rows, int cols) {
        if (data != nullptr) {
            for (int r = 0; r < nrows; r++)
                free(data[r]);
            free(data);
        }
        nrows = rows;
        ncols = cols;
        create();
    }

    // method to get the number of rows in the matrix
    int get_nrows() const {
        return nrows;
    }

    // method to get the number of columns in the matrix
    int get_ncols() const {
        return ncols;
    }

    // method to set the value of an element in the matrix
    void set(float value, int row, int col) {
        data[row][col] = value;
    }

    // method to add a value to an element in the matrix
    void add(float value, int row, int col) {
        data[row][col] += value;
    }

    // method to get the value of an element in the matrix
    float get(int row, int col) const {
        return data[row][col];
    }

    // method to remove a row from the matrix
    void remove_row(int row) {
        int neo_index = 0;
        auto** neo_data = (float**)malloc(sizeof(float*) * (nrows - 1));
        for (int i = 0; i < nrows; i++)
            if (i != row) {
                neo_data[neo_index] = data[i];
                neo_index++;
            }
        free(data[row]);
        free(data);
        data = neo_data;
        nrows--;
    }

    // method to remove a column from the matrix
    void remove_column(int col) {
        int neo_index = 0;
        auto** neo_data = (float**)malloc(sizeof(float*) * nrows);
        for (int r = 0; r < nrows; r++)
            neo_data[r] = (float*)malloc(sizeof(float) * (ncols - 1));

        for (int r = 0; r < nrows; r++) {
            for (int c = 0; c < ncols; c++)
                if (c != col) {
                    neo_data[r][neo_index] = data[r][c];
                    neo_index++;
                }
            neo_index = 0;
        }

        for (int r = 0; r < nrows; r++)
            free(data[r]);
        free(data);
        data = neo_data;
        ncols--;
    }

    // method to clone a matrix
    void clone(Matrix* other) const {
        for (int r = 0; r < nrows; r++)
            for (int c = 0; c < ncols; c++)
                other->set(data[r][c], r, c);
    }

    // method to display the matrix
    void show() const {
        std::cout << "[ ";
        for (int r = 0; r < nrows; r++) {
            std::cout << "[ " << data[r][0];
            for (int c = 1; c < ncols; c++) {
                std::cout << ", " << data[r][c];
            }
            std::cout << " ] ";
        }
        std::cout << " ]\n\n";
    }
};

#endif //SIMU_PROJEKT_MATRIX_HPP
