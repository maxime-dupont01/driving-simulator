#ifndef CIRCUIT_H
#define CIRCUIT_H

#include <vector>

class Circuit {
    public:
        void generate_circuit(int number);
        void print();
        static std::pair<double, double> rotate(double x,double y,float teta);
        bool isLapPassed();
        bool isOnTheRoad();
        void rotateCircuit(float teta);
        std::vector<std::pair<double,double>> roads;
        std::vector<std::pair<double,double>> middle_roads;
        void circuit1();
        void circuit2();
        void circuit3();
        void shiftCircuit(double speed, const char *dir);
};

#endif //CIRCUIT_H

