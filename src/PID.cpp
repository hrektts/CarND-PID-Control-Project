#include "PID.h"
#include <iostream>
#include <limits>

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd, int count_per_round) {
    p_error = 0.;
    i_error = 0.;
    d_error = 0.;
    this->Kp = Kp;
    this->Ki = Ki;
    this->Kd = Kd;
    it = 0;
    counter = 0;
    max_count = count_per_round;
    step = 0;
    finished = false;
    best_err = std::numeric_limits<double>::max();
    dKp = 0.01;
    dKi = 0.01;
    dKd = 0.01;
    total_err = 0.;
    alpha = 0.2;
}

void PID::UpdateError(double cte) {
    d_error = cte - p_error;
    p_error = cte;
    i_error += cte;
}

double PID::TotalError() {
    return -Kp * p_error - Kd * d_error - Ki * i_error;
}

void PID::Twiddle(double tol) {
    if (finished) {
        std::cout << "Twiddle has finished: Kp: " << Kp << ", Ki: " << Ki << ", Kd: " << Kd << std::endl;
        return;
    } else if (counter < max_count) {
        counter += 1;
        total_err += p_error * p_error;
        //std::cout << "count: " << counter << "/" << max_count << std::endl;
    } else {
        it += 1;
        counter = 0;
        double err = total_err / max_count;
        total_err = 0;

        if (dKp + dKi + dKd > tol) {
            std::cout << "Twiddle: iteration " << it << ", step " << step << ", error " << err << std::endl;
            switch (step) {
                case 0: {
                    Kp += dKp;
                    Ki += dKi;
                    Kd += dKd;
                    break;
                }
                case 1: {
                    if (err < best_err) {
                        best_err = err;
                        dKp *= 1.1;
                        dKi *= 1.1;
                        dKd *= 1.1;
                    } else {
                        Kp -= 2. * dKp;
                        Ki -= 2. * dKi;
                        Kd -= 2. * dKd;
                    }
                    break;
                }
                case 2: {
                    if (err < best_err) {
                        best_err = err;
                        dKp *= 1.1;
                        dKi *= 1.1;
                        dKd *= 1.1;
                    } else {
                        Kp += dKp;
                        dKp *= 0.9;
                        Ki += dKi;
                        dKi *= 0.9;
                        Kd += dKd;
                        dKd *= 0.9;
                    }
                    break;
                }
                default: {
                    break;
                }
            }
        } else {
            finished = true;
        }
        step += 1;
        if (step == 3) {
            step = 0;
        }
        std::cout << "Kp: " << Kp << ", Ki: " << Ki << ", Kd: " << Kd << std::endl;
    }
}
