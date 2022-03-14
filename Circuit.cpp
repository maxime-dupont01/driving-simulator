#include "Circuit.h"
#include "library.h"
#define RATIO 1.7

void Circuit::generate_circuit(int number) {
    switch(number) {
        case 1: Circuit::circuit1();
            break;
        case 2: Circuit::circuit2();
            break;
        case 3: Circuit::circuit3();
            break;
        default:;
    }
}

void Circuit::print() {
    for (auto i : Circuit::roads) {
        std::cout << "x : " << i.first << ", y : " << i.second << "\n";
    }
}

bool Circuit::isLapPassed() {
    auto first_x = roads[0].first;
    auto first_y = roads[0].second;
    auto second_x = roads[1].first;
    auto second_y = roads[1].second;
    int precision = 30;

    return (abs((first_x+second_x)/2 + (first_y + second_y/2)) < 75 + precision)
            && (first_x < 500);
}

bool Circuit::isOnTheRoad(){
    int precision = 80;
    for (auto & middle_road : middle_roads) {
        if ((abs(middle_road.first) + abs(middle_road.second)) / 2 < 75 + precision)
            return true;
    }
    return false;
}
void Circuit::circuit1() {
    std::array<double, 2> p1, p2, p3, p4, g1, g2, g3, g4;
    int x_rename = 0;
    int y_rename = 0;

    //first portion of the road
    p1[0] = (100.0 + x_rename) * RATIO; p1[1] = (0.0 + y_rename) * RATIO;
    p2[0] = (100.0 + x_rename) * RATIO; p2[1] = (0.0 + y_rename) * RATIO;
    p3[0] = (100.0 + x_rename) * RATIO; p3[1] = (0.0 + y_rename) * RATIO;
    p4[0] = (100.0 + x_rename) * RATIO; p4[1] = (-800.0 + y_rename) * RATIO;

    g1[0] = (-100.0 + x_rename) * RATIO; g1[1] = (0.0 + y_rename) * RATIO;
    g2[0] = (-100.0 + x_rename) * RATIO; g2[1] = (0.0 + y_rename) * RATIO;
    g3[0] = (-100.0 + x_rename) * RATIO; g3[1] = (0.0 + y_rename) * RATIO;
    g4[0] = (-100.0 + x_rename) * RATIO; g4[1] = (-800.0 + y_rename) * RATIO;

    drawRoadBezier(p1, p2, p3, p4, g1, g2, g3, g4, Circuit::roads, Circuit::middle_roads);

    //second portion of the road
    p1[0] = (100.0 + x_rename) * RATIO; p1[1] = (-800.0  + y_rename) * RATIO;
    p2[0] = (100.0 + x_rename) * RATIO; p2[1] = (-2000.0 + y_rename) * RATIO;
    p3[0] = (700.0 + x_rename) * RATIO; p3[1] = (-2000.0 + y_rename) * RATIO;
    p4[0] = (700.0 + x_rename) * RATIO; p4[1] = (-800.0  + y_rename) * RATIO;

    g1[0] = (-100.0 + x_rename) * RATIO; g1[1] = (-800.0  + y_rename) * RATIO;
    g2[0] = (-100.0 + x_rename) * RATIO; g2[1] = (-2200.0 + y_rename) * RATIO;
    g3[0] = ( 900.0 + x_rename) * RATIO; g3[1] = (-2200.0 + y_rename) * RATIO;
    g4[0] = ( 900.0 + x_rename) * RATIO; g4[1] = (-800.0  + y_rename) * RATIO;

    drawRoadBezier(p1, p2, p3, p4, g1, g2, g3, g4, Circuit::roads, Circuit::middle_roads);

    //third portion of the road
    p1[0] = (700.0 + x_rename) * RATIO; p1[1] = (-800.0  + y_rename) * RATIO;
    p2[0] = (700.0 + x_rename) * RATIO; p2[1] = (0.0 + y_rename) * RATIO;
    p3[0] = (700.0 + x_rename) * RATIO; p3[1] = (0.0 + y_rename) * RATIO;
    p4[0] = (700.0 + x_rename) * RATIO; p4[1] = (0.0  + y_rename) * RATIO;

    g1[0] = (900.0 + x_rename) * RATIO; g1[1] = (-800.0  + y_rename) * RATIO;
    g2[0] = (900.0 + x_rename) * RATIO; g2[1] = (0.0 + y_rename) * RATIO;
    g3[0] = (900.0 + x_rename) * RATIO; g3[1] = (0.0 + y_rename) * RATIO;
    g4[0] = (900.0 + x_rename) * RATIO; g4[1] = (0.0 + y_rename) * RATIO;

    drawRoadBezier(p1, p2, p3, p4, g1, g2, g3, g4, Circuit::roads, Circuit::middle_roads);

    //fourth portion of the road
    p1[0] = (700.0 + x_rename) * RATIO; p1[1] = (0.0  + y_rename) * RATIO;
    p2[0] = (700.0 + x_rename) * RATIO; p2[1] = (1400.0 + y_rename) * RATIO;
    p3[0] = (100.0 + x_rename) * RATIO; p3[1] = (1400.0 + y_rename) * RATIO;
    p4[0] = (100.0 + x_rename) * RATIO; p4[1] = (-200.0  + y_rename) * RATIO;

    g1[0] = (900.0 + x_rename) * RATIO; g1[1] = (0.0  + y_rename) * RATIO;
    g2[0] = (900.0 + x_rename) * RATIO; g2[1] = (1600.0 + y_rename) * RATIO;
    g3[0] = (-100.0 + x_rename) * RATIO; g3[1] = (1600.0 + y_rename) * RATIO;
    g4[0] = (-100.0 + x_rename) * RATIO; g4[1] = (-200.0 + y_rename) * RATIO;

    drawRoadBezier(p1, p2, p3, p4, g1, g2, g3, g4, Circuit::roads, Circuit::middle_roads);

}

void Circuit::circuit2() {
    std::array<double, 2> p1, p2, p3, p4, g1, g2, g3, g4;
    int x_rename = 0;
    int y_rename = 0;

    //first portion of the road
    p1[0] = (100.0 + x_rename) * RATIO; p1[1] = (0.0 + y_rename) * RATIO;
    p2[0] = (100.0 + x_rename) * RATIO; p2[1] = (0.0 + y_rename) * RATIO;
    p3[0] = (100.0 + x_rename) * RATIO; p3[1] = (0.0 + y_rename) * RATIO;
    p4[0] = (100.0 + x_rename) * RATIO; p4[1] = (-1200.0 + y_rename) * RATIO;

    g1[0] = (-100.0 + x_rename) * RATIO; g1[1] = (0.0 + y_rename) * RATIO;
    g2[0] = (-100.0 + x_rename) * RATIO; g2[1] = (0.0 + y_rename) * RATIO;
    g3[0] = (-100.0 + x_rename) * RATIO; g3[1] = (0.0 + y_rename) * RATIO;
    g4[0] = (-100.0 + x_rename) * RATIO; g4[1] = (-1200.0 + y_rename) * RATIO;

    drawRoadBezier(p1, p2, p3, p4, g1, g2, g3, g4, Circuit::roads, Circuit::middle_roads);

    //second portion of the road
    p1[0] = (100.0 + x_rename) * RATIO; p1[1] = (-1200.0 + y_rename) * RATIO;
    p2[0] = (100.0 + x_rename) * RATIO; p2[1] = (-1700.0 + y_rename) * RATIO;
    p3[0] = (-500.0 + x_rename) * RATIO; p3[1] = (-1650.0 + y_rename) * RATIO;
    p4[0] = (-400.0 + x_rename) * RATIO; p4[1] = (-1800.0 + y_rename) * RATIO;

    g1[0] = (-100.0 + x_rename) * RATIO; g1[1] = (-1200.0 + y_rename) * RATIO;
    g2[0] = (-100.0 + x_rename) * RATIO; g2[1] = (-1600.0 + y_rename) * RATIO;
    g3[0] = (-700.0 + x_rename) * RATIO; g3[1] = (-1550.0 + y_rename) * RATIO;
    g4[0] = (-600.0 + x_rename) * RATIO; g4[1] = (-1800.0 + y_rename) * RATIO;

    drawRoadBezier(p1, p2, p3, p4, g1, g2, g3, g4, Circuit::roads, Circuit::middle_roads);

    //third portion of the road
    p1[0] = (-400.0 + x_rename) * RATIO; p1[1] = (-1800.0 + y_rename) * RATIO;
    p2[0] = (-400.0 + x_rename) * RATIO; p2[1] = (-1800.0 + y_rename) * RATIO;
    p3[0] = (-400.0 + x_rename) * RATIO; p3[1] = (-1800.0 + y_rename) * RATIO;
    p4[0] = (800.0 + x_rename) * RATIO; p4[1] = (-3200.0 + y_rename) * RATIO;

    g1[0] = (-600.0 + x_rename) * RATIO; g1[1] = (-1800.0 + y_rename) * RATIO;
    g2[0] = (-600.0 + x_rename) * RATIO; g2[1] = (-1800.0 + y_rename) * RATIO;
    g3[0] = (-600.0 + x_rename) * RATIO; g3[1] = (-1800.0 + y_rename) * RATIO;
    g4[0] = (600.0 + x_rename) * RATIO; g4[1] = (-3200.0 + y_rename) * RATIO;

    drawRoadBezier(p1, p2, p3, p4, g1, g2, g3, g4, Circuit::roads, Circuit::middle_roads);

    //fourth portion of the road
    p1[0] = (800.0 + x_rename) * RATIO; p1[1] = (-3200.0 + y_rename) * RATIO;
    p2[0] = (920.0 + x_rename) * RATIO; p2[1] = (-4050.0 + y_rename) * RATIO;
    p3[0] = (1300.0 + x_rename) * RATIO; p3[1] = (-3750.0 + y_rename) * RATIO;
    p4[0] = (1200.0 + x_rename) * RATIO; p4[1] = (-1500.0 + y_rename) * RATIO;

    g1[0] = (600.0 + x_rename) * RATIO; g1[1] = (-3200.0 + y_rename) * RATIO;
    g2[0] = (900.0 + x_rename) * RATIO; g2[1] = (-4200.0 + y_rename) * RATIO;
    g3[0] = (1400.0 + x_rename) * RATIO; g3[1] = (-3900.0 + y_rename) * RATIO;
    g4[0] = (1400.0 + x_rename) * RATIO; g4[1] = (-1500.0 + y_rename) * RATIO;

    drawRoadBezier(p1, p2, p3, p4, g1, g2, g3, g4, Circuit::roads, Circuit::middle_roads);

    //fifth portion of the road
    p1[0] = (1200.0 + x_rename) * RATIO; p1[1] = (-1500.0 + y_rename) * RATIO;
    p2[0] = (1200.0 + x_rename) * RATIO; p2[1] = (-1100.0 + y_rename) * RATIO;
    p3[0] = (700.0 + x_rename) * RATIO; p3[1] = (-1100.0 + y_rename) * RATIO;
    p4[0] = (700.0 + x_rename) * RATIO; p4[1] = (0.0 + y_rename) * RATIO;

    g1[0] = (1400.0 + x_rename) * RATIO; g1[1] = (-1500.0 + y_rename) * RATIO;
    g2[0] = (1400.0 + x_rename) * RATIO; g2[1] = (-1100.0 + y_rename) * RATIO;
    g3[0] = (900.0 + x_rename) * RATIO; g3[1] = (-1100.0 + y_rename) * RATIO;
    g4[0] = (900.0 + x_rename) * RATIO; g4[1] = (0.0 + y_rename) * RATIO;

    drawRoadBezier(p1, p2, p3, p4, g1, g2, g3, g4, Circuit::roads, Circuit::middle_roads);

    //sixth portion of the road
    p1[0] = (700.0 + x_rename) * RATIO; p1[1] = (0.0 + y_rename) * RATIO;
    p2[0] = (700.0 + x_rename) * RATIO; p2[1] = (1100.0 + y_rename) * RATIO;
    p3[0] = (1100.0 + x_rename) * RATIO; p3[1] = (1400.0 + y_rename) * RATIO;
    p4[0] = (800.0 + x_rename) * RATIO; p4[1] = (1700.0 + y_rename) * RATIO;

    g1[0] = (900.0 + x_rename) * RATIO; g1[1] = (0.0 + y_rename) * RATIO;
    g2[0] = (900.0 + x_rename) * RATIO; g2[1] = (1100.0 + y_rename) * RATIO;
    g3[0] = (1300.0 + x_rename) * RATIO; g3[1] = (1400.0 + y_rename) * RATIO;
    g4[0] = (1000.0 + x_rename) * RATIO; g4[1] = (1700.0 + y_rename) * RATIO;

    drawRoadBezier(p1, p2, p3, p4, g1, g2, g3, g4, Circuit::roads, Circuit::middle_roads);

    //seventh portion of the road
    p1[0] = (800.0 + x_rename) * RATIO; p1[1] = (1700.0 + y_rename) * RATIO;
    p2[0] = (700.0 + x_rename) * RATIO; p2[1] = (2200.0 + y_rename) * RATIO;
    p3[0] = (150.0 + x_rename) * RATIO; p3[1] = (1700.0 + y_rename) * RATIO;
    p4[0] = (85.0 + x_rename) * RATIO; p4[1] = (-230.0 + y_rename) * RATIO;

    g1[0] = (1000.0 + x_rename) * RATIO; g1[1] = (1700.0 + y_rename) * RATIO;
    g2[0] = (850.0 + x_rename) * RATIO; g2[1] = (2500.0 + y_rename) * RATIO;
    g3[0] = (0.0 + x_rename) * RATIO; g3[1] = (1900.0 + y_rename) * RATIO;
    g4[0] = (-115.0 + x_rename) * RATIO; g4[1] = (-256.0 + y_rename) * RATIO;

    drawRoadBezier(p1, p2, p3, p4, g1, g2, g3, g4, Circuit::roads, Circuit::middle_roads);

}

void Circuit::circuit3() {
    std::array<double, 2> p1, p2, p3, p4, g1, g2, g3, g4;
    int x_rename = 0;
    int y_rename = 0;

    //first portion of the road
    p1[0] = (100.0 + x_rename) * RATIO; p1[1] = (0.0 + y_rename) * RATIO;
    p2[0] = (100.0 + x_rename) * RATIO; p2[1] = (-900.0 + y_rename) * RATIO;
    p3[0] = (100.0 + x_rename) * RATIO; p3[1] = (-900.0 + y_rename) * RATIO;
    p4[0] = (-700.0 + x_rename) * RATIO; p4[1] = (-900.0 + y_rename) * RATIO;

    g1[0] = (-100.0 + x_rename) * RATIO; g1[1] = (0.0 + y_rename) * RATIO;
    g2[0] = (-80.0 + x_rename) * RATIO; g2[1] = (-750.0 + y_rename) * RATIO;
    g3[0] = (-80.0 + x_rename) * RATIO; g3[1] = (-750.0 + y_rename) * RATIO;
    g4[0] = (-700.0 + x_rename) * RATIO; g4[1] = (-700.0 + y_rename) * RATIO;

    drawRoadBezier(p1, p2, p3, p4, g1, g2, g3, g4, Circuit::roads, Circuit::middle_roads);

    //second portion of the road
    p1[0] = (-700.0 + x_rename) * RATIO; p1[1] = (-900.0 + y_rename) * RATIO;
    p2[0] = (-1400.0 + x_rename) * RATIO; p2[1] = (-900.0 + y_rename) * RATIO;
    p3[0] = (-1400.0 + x_rename) * RATIO; p3[1] = (-1600.0 + y_rename) * RATIO;
    p4[0] = (-700.0 + x_rename) * RATIO; p4[1] = (-1600.0 + y_rename) * RATIO;

    g1[0] = (-700.0 + x_rename) * RATIO; g1[1] = (-700.0 + y_rename) * RATIO;
    g2[0] = (-1500.0 + x_rename) * RATIO; g2[1] = (-700.0 + y_rename) * RATIO;
    g3[0] = (-1500.0 + x_rename) * RATIO; g3[1] = (-1800.0 + y_rename) * RATIO;
    g4[0] = (-700.0 + x_rename) * RATIO; g4[1] = (-1800.0 + y_rename) * RATIO;

    drawRoadBezier(p1, p2, p3, p4, g1, g2, g3, g4, Circuit::roads, Circuit::middle_roads);

    //third portion of the road
    p1[0] = (-700.0 + x_rename) * RATIO; p1[1] = (-1600.0 + y_rename) * RATIO;
    p2[0] = (75.0 + x_rename) * RATIO; p2[1] = (-2300.0 + y_rename) * RATIO;
    p3[0] = (1625.0 + x_rename) * RATIO; p3[1] = (-700.0 + y_rename) * RATIO;
    p4[0] = (2400.0 + x_rename) * RATIO; p4[1] = (-1600.0 + y_rename) * RATIO;

    g1[0] = (-700.0 + x_rename) * RATIO; g1[1] = (-1800.0 + y_rename) * RATIO;
    g2[0] = (75.0 + x_rename) * RATIO; g2[1] = (-2500.0 + y_rename) * RATIO;
    g3[0] = (1625.0 + x_rename) * RATIO; g3[1] = (-900.0 + y_rename) * RATIO;
    g4[0] = (2400.0 + x_rename) * RATIO; g4[1] = (-1800.0 + y_rename) * RATIO;

    drawRoadBezier(p1, p2, p3, p4, g1, g2, g3, g4, Circuit::roads, Circuit::middle_roads);

    //fourth portion of the road
    p1[0] = (2400.0 + x_rename) * RATIO; p1[1] = (-1600.0 + y_rename) * RATIO;
    p2[0] = (3500.0 + x_rename) * RATIO; p2[1] = (-1700.0 + y_rename) * RATIO;
    p3[0] = (3500.0 + x_rename) * RATIO; p3[1] = (-900.0 + y_rename) * RATIO;
    p4[0] = (2000.0 + x_rename) * RATIO; p4[1] = (-1300.0 + y_rename) * RATIO;

    g1[0] = (2400.0 + x_rename) * RATIO; g1[1] = (-1800.0 + y_rename) * RATIO;
    g2[0] = (3700.0 + x_rename) * RATIO; g2[1] = (-1900.0 + y_rename) * RATIO;
    g3[0] = (3700.0 + x_rename) * RATIO; g3[1] = (-700.0 + y_rename) * RATIO;
    g4[0] = (2000.0 + x_rename) * RATIO; g4[1] = (-1100.0 + y_rename) * RATIO;

    drawRoadBezier(p1, p2, p3, p4, g1, g2, g3, g4, Circuit::roads, Circuit::middle_roads);

    //fifth portion of the road
    p1[0] = (2000.0 + x_rename) * RATIO; p1[1] = (-1300.0 + y_rename) * RATIO;
    p2[0] = (1300.0 + x_rename) * RATIO; p2[1] = (-1000.0 + y_rename) * RATIO;
    p3[0] = (500.0 + x_rename) * RATIO; p3[1] = (-200.0 + y_rename) * RATIO;
    p4[0] = (500.0 + x_rename) * RATIO; p4[1] = (500.0 + y_rename) * RATIO;

    g1[0] = (2000.0 + x_rename) * RATIO; g1[1] = (-1100.0 + y_rename) * RATIO;
    g2[0] = (1400.0 + x_rename) * RATIO; g2[1] = (-850.0 + y_rename) * RATIO;
    g3[0] = (700.0 + x_rename) * RATIO; g3[1] = (-100.0 + y_rename) * RATIO;
    g4[0] = (700.0 + x_rename) * RATIO; g4[1] = (500.0 + y_rename) * RATIO;

    drawRoadBezier(p1, p2, p3, p4, g1, g2, g3, g4, Circuit::roads, Circuit::middle_roads);

    //sixth portion of the road
    p1[0] = (500.0 + x_rename) * RATIO; p1[1] = (500.0 + y_rename) * RATIO;
    p2[0] = (500.0 + x_rename) * RATIO; p2[1] = (1200.0 + y_rename) * RATIO;
    p3[0] = (100.0 + x_rename) * RATIO; p3[1] = (1200.0 + y_rename) * RATIO;
    p4[0] = (88.0 + x_rename) * RATIO; p4[1] = (-230.0 + y_rename) * RATIO;

    g1[0] = (700.0 + x_rename) * RATIO; g1[1] = (500.0 + y_rename) * RATIO;
    g2[0] = (700.0 + x_rename) * RATIO; g2[1] = (1400.0 + y_rename) * RATIO;
    g3[0] = (-100.0 + x_rename) * RATIO; g3[1] = (1400.0 + y_rename) * RATIO;
    g4[0] = (-108.0 + x_rename) * RATIO; g4[1] = (-256.0 + y_rename) * RATIO;

    drawRoadBezier(p1, p2, p3, p4, g1, g2, g3, g4, Circuit::roads, Circuit::middle_roads);
}

std::pair<double, double> Circuit::rotate(double x, double y, float teta) {
    double newX = x*cos(teta)+y*sin(teta);
    double newY = x*sin(teta)-y*cos(teta);
    return {newX, newY};
}

void Circuit::shiftCircuit(double speed, const char* dir = "up") {

        if (dir == "up") {
            for (int i = 0; i < Circuit::roads.size(); ++i) {
                Circuit::roads[i].second += speed;
                Circuit::middle_roads[i].second += speed;
            }
            return;
        }
        if (dir == "down") {
            for (int i = 0; i < Circuit::roads.size(); ++i) {
                Circuit::roads[i].second -= speed;
                Circuit::middle_roads[i].second -= speed;
            }
            return;
        }
        if (dir == "left") {
            for (int i = 0; i < Circuit::roads.size(); ++i) {
                Circuit::roads[i].first -= speed;
                Circuit::middle_roads[i].first -= speed;
            }
            return;
        }
        if (dir == "right") {
            for (int i = 0; i < Circuit::roads.size(); ++i) {
                Circuit::roads[i].first += speed;
                Circuit::middle_roads[i].first += speed;
            }
            return;
        }
    }

void Circuit::rotateCircuit(float teta) {

    for (auto & road : Circuit::roads) {
        auto p = rotate(road.first, road.second, teta);
        road.first = p.first;
        road.second = p.second;
    }

    for (auto & middle_road : Circuit::middle_roads) {
        auto p = rotate(middle_road.first, middle_road.second, teta);
        middle_road.first = p.first;
        middle_road.second = p.second;
    }
}
