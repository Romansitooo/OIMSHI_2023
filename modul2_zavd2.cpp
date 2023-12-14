#include <iostream>
#include <armadillo>
#include <ControlSystemToolbox.h>

int main() {
    // задаю передавальну функцію об'єкта керування
    double k = 1.0;
    arma::vec numerator = { k };
    arma::vec denominator = { 81, 18, 1 };

    // задаю передавальну функцію контролера (ПІД)
    double Kp = 1.0;  // коефіцієнт пропорціональності
    double Ki = 0.1;  // коефіцієнт інтегральності
    double Kd = 0.01; // коефіцієнт диференціальності

    // створюю об'єкти TransferFunction
    ctl::TransferFunction plantTF(numerator, denominator);
    ctl::TransferFunction controllerTF({ Kd, Kp, Ki }, { 1, 0 });

    // створюю відкритий та закритий ланцюги
    auto openLoopTF = plantTF * controllerTF;
    auto closedLoopTF = ctl::feedback(openLoopTF);

    // генерую вхідний сигнал (синусоїду)
    arma::vec time = arma::linspace(0, 10, 1000);
    arma::vec inputSignal = arma::sin(2 * M_PI * 0.5 * time);

    // Отримуємо вихідні дані для вхідного сигналу
    auto response = ctl::lsim(closedLoopTF, inputSignal, time);

    // Виводимо результат
    std::cout << "Вхідний сигнал:\n" << inputSignal.t() << "\n\n";
    std::cout << "Вихідний сигнал:\n" << response.t() << "\n";

    return 0;
}
