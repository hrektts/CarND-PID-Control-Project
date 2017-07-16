#ifndef PID_H
#define PID_H

class PID {
public:
  /*
  * Errors
  */
  double p_error;
  double i_error;
  double d_error;

  /*
  * Coefficients
  */
  double Kp;
  double Ki;
  double Kd;

  /*
   * Twiddle
   */
  int it;
  int counter;
  int max_count;
  int step;
  bool finished;
  double best_err;
  double dKp;
  double dKi;
  double dKd;
  double total_err;
  double alpha;

  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double Kp, double Ki, double Kd, int count_per_round);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  /*
  * Calculate the total PID error.
  */
  double TotalError();

  void Twiddle(double tol=0.002);
};

#endif /* PID_H */
