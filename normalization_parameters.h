#ifndef NORMALIZATION_PARAMETERS_H
#define NORMALIZATION_PARAMETERS_H

class NormalizationParameters {
public:
    double max;
    double min;
    double dxStep;
    double dyStep;
    NormalizationParameters(double max, double min, double step) : max(max), min(min), dxStep(step), dyStep(step) {};
    NormalizationParameters(double max, double min, double dxStep, double dyStep) : max(max), min(min), dxStep(dxStep), dyStep(dyStep) {};
};

#endif // NORMALIZATION_PARAMETERS_H
