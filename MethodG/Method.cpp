#include <iostream>
#include <vector>
#define _CRT_SECURE_NO_WARNINGS
#include "GaussException.h"

using namespace std;

using ValueType = double;
constexpr int MAX_SIZE = 10;

void forwardPass(vector<vector<ValueType>>& coefficientMatrix, vector<ValueType>& solutions) {
    const int size = coefficientMatrix.size();
    for (int k = 0; k < size; k++) {
        for (int i = k + 1; i < size; i++) {
            if (coefficientMatrix[k][k] == 0) {
                throw GaussException("Error: Division by zero. Unable to continue.");
            }
            ValueType coefficient = coefficientMatrix[i][k] / coefficientMatrix[k][k];
            for (int j = k + 1; j < size; j++) {
                coefficientMatrix[i][j] -= coefficientMatrix[k][j] * coefficient;
            }
            coefficientMatrix[i][k] = 0;
            solutions[i] -= coefficient * solutions[k];
        }
    }
}

void ÑheckAndBack(vector<vector<ValueType>>& coefficientMatrix, vector<ValueType>& solutions) {
    const int size = coefficientMatrix.size();
    vector<ValueType> sample(size, 0);
    if (coefficientMatrix[size - 1][size - 1] == 0) {
        if (solutions[size - 1] == 0) {
            cout << "There will be many solutions" << endl;
            sample[size - 1] = 1;
        }
        else {
            cout << "No solutions" << endl;
            return;
        }
    }
    else {
        sample[size - 1] = solutions[size - 1] / coefficientMatrix[size - 1][size - 1];
    }

    for (int i = size - 1; i >= 0; i--) {
        ValueType s = solutions[i];
        for (int j = i + 1; j < size; j++) {
            s += -coefficientMatrix[i][j] * sample[j];
        }
        if (coefficientMatrix[i][i] == 0) {
            if (s == 0) {
                sample[i] = 1;
            }
            else {
                cout << "No solutions" << endl;
                return;
            }
        }
        else {
            sample[i] = s / coefficientMatrix[i][i];
        }
    }

    cout << "Sample solution:" << endl;
    for (int i = 0; i < size; i++) {
        cout << sample[i] << " ";
    }
    cout << endl;
}


int main() {
    int size;
    cout << "Enter system size:" << endl;
    cin >> size;

    if (size <= 0) {
        cout << "Error: Invalid system size. Exiting." << endl;
        return 1; // ×òîáû âûéòè èç ïðîãðàììû ñ êîäîì îøèáêè
    }

    cout << "Enter size coefficient matrix:" << endl;
    vector<vector<ValueType>> coefficientMatrix(size, vector<ValueType>(size));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << "Enter element [" << i << "][" << j << "]: ";
            cin >> coefficientMatrix[i][j];
        }
    }

    cout << "Enter solution vector:" << endl;
    vector<ValueType> solutions(size);
    for (int i = 0; i < size; i++) {
        cout << "Enter value for solution vector[" << i << "]: ";
        cin >> solutions[i];
    }

    forwardPass(coefficientMatrix, solutions);
    ÑheckAndBack(coefficientMatrix, solutions);

    return 0;
}
