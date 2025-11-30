#include "MI_Ball.h"

Ball::Ball(double m, double R) {
    this->m = m;
    this->R = R;
}

string Ball::name_body() {
    return "ball";
}

vector<double> Ball::get_data() {
    return { m, R };
}

istream& operator >> (istream& stream, Ball& ball) {
    while (true) {
        cout << "m = ";
        stream >> ball.m;
        if (!valid_input(stream)) {
            continue;
        }
        break;
    }

    while (true) {
        cout << "R = ";
        stream >> ball.R;
        if (!valid_input(stream)) {
            continue;
        }
        break;
    }
    return stream;
}
