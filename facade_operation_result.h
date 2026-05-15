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
        return FacadeOperationResult(OperationResult::drawError, "Ошибка при отрисовке сцены");
    }

    static FacadeOperationResult success() {
        return FacadeOperationResult(OperationResult::success, "Успех");
    }

    static FacadeOperationResult invalidFile() {
        return FacadeOperationResult(OperationResult::invalidFile, "Ошибка при чтении файла");
    }

    static FacadeOperationResult invalidData() {
        return FacadeOperationResult(OperationResult::invalidData, "Ошибка при чтении данных");
    }

    static FacadeOperationResult invalidParams() {
        return FacadeOperationResult(OperationResult::invalidParams, "Некорректные параметры загрузки");
    }

    static FacadeOperationResult translationLimit() {
        return FacadeOperationResult(OperationResult::translationLimit, "Достигнут предел сдвига");
    }

    static FacadeOperationResult scaleLimit() {
        return FacadeOperationResult(OperationResult::scaleLimit, "Достигнут предел масштабирования");
    }
private:
    OperationResult result;
    std::string message;
};

#endif // FACADEOPERATIONRESULT_H
