#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

int main() {
    // Задаємо дані
    int n = 16;
    VectorXd Y(n);
    VectorXd T(n);

    Y << 10, 7, 4, 9, 16, 6, 8, 7, 14, 10, 5, 11, 16, 7, 6, 9;
    T << 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009, 2010, 2011, 2012, 2013, 2014, 2015, 2016;

    // Формуємо матрицю A та вектор B для системи рівнянь
    MatrixXd A(n, 2);
    A.col(0) = VectorXd::Ones(n);
    A.col(1) = T;
    VectorXd B = Y;

    // Розв'язуємо систему рівнянь
    VectorXd coefficients = A.householderQr().solve(B);

    // Отримуємо коефіцієнти регресії
    double b0 = coefficients(0);
    double b1 = coefficients(1);

    // Виводимо результат
    cout << "Рівняння лінійної регресії: Y = " << b0 << " + " << b1 << " * T" << endl;

    return 0;
}
