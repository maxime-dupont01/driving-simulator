//
// Created by rmarques on 01/03/2022.
//

#include "Circuit.h"
#include "library.h"
#define RATIO 1

class Circuit {
    Circuit(double x_rename, double y_rename) {
        std::array<double, 2> p1, p2, p3, p4;

        //first portion of the road
        p1[0] = (0.0 + x_rename) * RATIO; p1[1] = (200.0 + y_rename) * RATIO;
        p2[0] = (0.0 + x_rename) * RATIO; p2[1] = (200.0 + y_rename) * RATIO;
        p3[0] = (0.0 + x_rename) * RATIO; p3[1] = (200.0 + y_rename) * RATIO;
        p4[0] = (0.0 + x_rename) * RATIO; p4[1] =  (-200.0 + y_rename) * RATIO;

        drawRoadBezier(p1, p2, p3, p4);

        //second portion of the road
        p1[0] = (0.0 + x_rename) * RATIO; p1[1] = (-200.0 + y_rename) * RATIO;
        p2[0] = (0.0 + x_rename) * RATIO; p2[1] = (-400.0 + y_rename) * RATIO;
        p3[0] = (400.0 + x_rename) * RATIO; p3[1] = (-400.0 + y_rename) * RATIO;
        p4[0] = (400.0 + x_rename) * RATIO; p4[1] = (-600.0 + y_rename) * RATIO;

        drawRoadBezier(p1, p2, p3, p4);

        //third portion of the road
        p1[0] = (400.0 + x_rename) * RATIO; p1[1] = (-600.0 + y_rename) * RATIO;
        p2[0] = (400.0 + x_rename) * RATIO; p2[1] = (-960.0 + y_rename) * RATIO;
        p3[0] = (760.0 + x_rename) * RATIO; p3[1] = (-960.0 + y_rename) * RATIO;
        p4[0] = (760.0 + x_rename) * RATIO; p4[1] = (-700.0 + y_rename) * RATIO;

        drawRoadBezier(p1, p2, p3, p4);

        //fourth portion of the road
        p1[0] = (760.0 + x_rename) * RATIO; p1[1] = (-700.0 + y_rename) * RATIO;
        p2[0] = (630.0 + x_rename) * RATIO; p2[1] = (-400.0 + y_rename) * RATIO;
        p3[0] = (1200.0 + x_rename) * RATIO; p3[1] = (-500.0 + y_rename) * RATIO;
        p4[0] = (1100.0 + x_rename) * RATIO; p4[1] = (-200.0 + y_rename) * RATIO;

        drawRoadBezier(p1, p2, p3, p4);

        //fifth portion of the road
        p1[0] = (1100.0 + x_rename) * RATIO; p1[1] = (-210.0 + y_rename) * RATIO;
        p2[0] = (800.0 + x_rename) * RATIO; p2[1] = (400.0 + y_rename) * RATIO;
        p3[0] = (1200.0 + x_rename) * RATIO; p3[1] = (-70.0 + y_rename) * RATIO;
        p4[0] = (1130.0 + x_rename) * RATIO; p4[1] = (300.0 + y_rename) * RATIO;

        drawRoadBezier(p1, p2, p3, p4);

        //sixth portion of the road
        p1[0] = (1130.0 + x_rename) * RATIO; p1[1] = (290.0 + y_rename) * RATIO;
        p2[0] = (1000.0 + x_rename) * RATIO; p2[1] = (840.0 + y_rename) * RATIO;
        p3[0] = (800.0 + x_rename) * RATIO; p3[1] = (840.0 + y_rename) * RATIO;
        p4[0] = (700.0 + x_rename) * RATIO; p4[1] = (700.0 + y_rename) * RATIO;

        drawRoadBezier(p1, p2, p3, p4);

        //seventh portion of the road
        p1[0] = (700.0 + x_rename) * RATIO; p1[1] = (710.0 + y_rename) * RATIO;
        p2[0] = (600.0 + x_rename) * RATIO; p2[1] = (400.0 + y_rename) * RATIO;
        p3[0] = (400.0 + x_rename) * RATIO; p3[1] = (600.0 + y_rename) * RATIO;
        p4[0] = (300.0 + x_rename) * RATIO; p4[1] = (600.0 + y_rename) * RATIO;

        //seventh portion of the road
        p1[0] = (700.0 + x_rename) * RATIO; p1[1] = (710.0 + y_rename) * RATIO;
        p2[0] = (600.0 + x_rename) * RATIO; p2[1] = (400.0 + y_rename) * RATIO;
        p3[0] = (400.0 + x_rename) * RATIO; p3[1] = (600.0 + y_rename) * RATIO;
        p4[0] = (300.0 + x_rename) * RATIO; p4[1] = (600.0 + y_rename) * RATIO;

        drawRoadBezier(p1, p2, p3, p4);

        //eighth portion of the road
        p1[0] = (310.0 + x_rename) * RATIO; p1[1] = (600.0 + y_rename) * RATIO;
        p2[0] = (300.0 + x_rename) * RATIO; p2[1] = (600.0 + y_rename) * RATIO;
        p3[0] = (300.0 + x_rename) * RATIO; p3[1] = (600.0 + y_rename) * RATIO;
        p4[0] = (-900.0 + x_rename) * RATIO; p4[1] = (600.0 + y_rename) * RATIO;

        drawRoadBezier(p1, p2, p3, p4);

        //ninth portion of the road
        p1[0] = (-890.0 + x_rename) * RATIO; p1[1] = (600.0 + y_rename) * RATIO;
        p2[0] = (-1200.0 + x_rename) * RATIO; p2[1] = (600.0 + y_rename) * RATIO;
        p3[0] = (-1200.0 + x_rename) * RATIO; p3[1] = (350.0 + y_rename) * RATIO;
        p4[0] = (-900.0 + x_rename) * RATIO; p4[1] = (350.0 + y_rename) * RATIO;

        drawRoadBezier(p1, p2, p3, p4);

        //tenth portion of the road
        p1[0] = (-910.0 + x_rename) * RATIO; p1[1] = (350.0 + y_rename) * RATIO;
        p2[0] = (-900.0 + x_rename) * RATIO; p2[1] = (350.0 + y_rename) * RATIO;
        p3[0] = (-900.0 + x_rename) * RATIO; p3[1] = (350.0 + y_rename) * RATIO;
        p4[0] = (0.0 + x_rename) * RATIO; p4[1] = (350.0 + y_rename) * RATIO;

        drawRoadBezier(p1, p2, p3, p4);

        //eleventh portion of the road
        p1[0] = (-10.0 + x_rename) * RATIO; p1[1] = (350.0 + y_rename) * RATIO;
        p2[0] = (150.0 + x_rename) * RATIO; p2[1] = (290.0 + y_rename) * RATIO;
        p3[0] = (-40.0 + x_rename) * RATIO; p3[1] = (250.0 + y_rename) * RATIO;
        p4[0] = (0.0 + x_rename) * RATIO; p4[1] = (200.0 + y_rename) * RATIO;

        drawRoadBezier(p1, p2, p3, p4);

    }
};
