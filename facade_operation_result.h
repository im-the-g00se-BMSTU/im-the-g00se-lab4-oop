#ifndef FACADEOPERATIONRESULT_H
#define FACADEOPERATIONRESULT_H

#include <string>

class FacadeOperationResult {
public:
    enum class OperationResult {
        success,
        invalidFile,
        invalidData,
        invalidParams,
        drawError,
        translationLimit,
        scaleLimit
    };

    FacadeOperationResult(OperationResult result, std::string errorMessage) : result(result), message(errorMessage) {}

    bool isSuccess() const {
        return result == OperationResult::success;
    }

    OperationResult getResult() const {
        return result;
    }

    std::string getMessage() const {
        return message;
    }

    static FacadeOperationResult drawError() {
        return FacadeOperationResult(OperationResult::drawError, "Scene rendering error");
    }

    static FacadeOperationResult success() {
        return FacadeOperationResult(OperationResult::success, "Success");
    }

    static FacadeOperationResult invalidFile() {
        return FacadeOperationResult(OperationResult::invalidFile, "File reading error");
    }

    static FacadeOperationResult invalidData() {
        return FacadeOperationResult(OperationResult::invalidData, "Data reading error");
    }

    static FacadeOperationResult invalidParams() {
        return FacadeOperationResult(OperationResult::invalidParams, "Invalid loading parameters");
    }

    static FacadeOperationResult translationLimit() {
        return FacadeOperationResult(OperationResult::translationLimit, "Translation limit reached");
    }

    static FacadeOperationResult scaleLimit() {
        return FacadeOperationResult(OperationResult::scaleLimit, "Scale limit reached");
    }
private:
    OperationResult result;
    std::string message;
};

#endif // FACADEOPERATIONRESULT_H
