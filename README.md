# CarND-Controls-PID

Self-Driving Car Engineer Nanodegree Program

---

## Describe the effect each of the P, I, D components had in your implementation.

### P component

This component determines the manipulated variable in proportion to the error.
In this project, since the error corresponds to cross-track error (CTE) and
the manipulated variable corresponds to the steering angle, a large P component
incleases the steering angle in propotion to CTE.

### I component

This component compensates steady-state error. In driving a car, the steady-state
error is caused by misalignment of the steering system or external force such as wind.
In this project, since the simulator is considered to be an ideal environment,
it is assumed that these factors do not exist. Thus, this component was used to
diminish CTE after P and D component was tuned.

### D component

This component determines the manipulated variable in proportion to the differential
of the error. It means that increasing CTE increases the steering angle to try
recovering the car to the trajectry and decreasing CTE decreases the steering angle
to stabilize steering.

## Describe how the final hyperparameters were chosen.

### Manual tuning

I started with adjustment of the P component by setting the I and D components
as zero. Start with a value of 0.1, I increased the P component till meandering was
observed. Then I increased the D component till the meandering was disappeared.
These two processes were repeated multiple times to obtain the P and D components.
I stopped this procedure when the car began to show abrupt behavior. After that,
I adjusted the I component to keep the car running in the middle of the lane.
As a result, I obtained the Kp, Ki and Kd as 0.25, 0.0005, 9, respectively.

### Twiddle

Based on the result of manual tuning, I used the Twiddle algorithm to fine tune PID components. The algorithm determined the Kp, Ki and Kd as , respectively.
