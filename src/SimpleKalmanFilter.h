
#ifndef KF_H
#define KF_H


class SimpleKalmanFilter {
  float q;  // process noise
  float r;  // measurement noise
  float x;  // estimated value
  float p;  // estimation error
  float k;  // Kalman gain

public:
  SimpleKalmanFilter(float processNoise, float measurementNoise, float estimationError, float initialValue) {
    q = processNoise;
    r = measurementNoise;
    p = estimationError;
    x = initialValue;
  }

  float update(float measurement) {
    // Prediction update
    p = p + q;

    // Measurement update
    k = p / (p + r);
    x = x + k * (measurement - x);
    p = (1 - k) * p;

    return x;
  }
};

#endif