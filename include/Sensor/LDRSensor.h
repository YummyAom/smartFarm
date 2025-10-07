#ifndef LDR_SENSOR_H
#define LDR_SENSOR_H

#include <Arduino.h>
#include <Adafruit_ADS1X15.h>

enum FilterType { FILTER_NONE, FILTER_MOVING_AVG, FILTER_MEDIAN, FILTER_EMA, FILTER_MEDIAN_EMA };

class LDRSensor {
public:
  LDRSensor(uint8_t ch, Adafruit_ADS1115 &ads);
  void begin();
  float getVolteLDR();           // raw
  float getFilteredVoltage();    // filtered
  int claculateLux();

  // filter config
  void setFilterType(FilterType t);
  void setMovingWindowSize(size_t n);
  void setEMAAlpha(float a);

private:
  uint8_t channel;
  Adafruit_ADS1115 &ads;

  // moving window
  size_t windowSize = 5;
  float *windowBuffer = nullptr;
  size_t windowIndex = 0;
  float windowSum = 0.0;

  // median buffer (we can reuse same buffer for median if needed)
  float *medianBuffer = nullptr;

  // EMA
  float emaAlpha = 0.2;
  bool emaInitialized = false;
  float emaValue = 0.0;

  FilterType filterType = FILTER_MEDIAN_EMA;

  // helper
  void ensureBuffers();
  float computeMovingAvg(float newVal);
  float computeMedian(float newVal);
  float computeEMA(float newVal);
};
#endif 