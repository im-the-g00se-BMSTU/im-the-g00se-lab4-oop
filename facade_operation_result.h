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
    FacadeOperationResult(OperationResult result, std::string errorMessage);
    bool isSuccess() const;
    OperationResult getResult() const;
    std::string getMessage() const;
    static FacadeOperationResult drawError();
    static FacadeOperationResult success();
    static FacadeOperationResult invalidFile();
    static FacadeOperationResult invalidData();
    static FacadeOperationResult invalidParams();
    static FacadeOperationResult translationLimit();
    static FacadeOperationResult scaleLimit();
private:
    OperationResult result;
    std::string message;
};

#endif // FACADEOPERATIONRESULT_H
