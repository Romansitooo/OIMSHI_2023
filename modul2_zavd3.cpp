#include <iostream>
#include <dlib/mlp.h>
#include <dlib/rand.h>
#include <dlib/svm.h>

using namespace std;
using namespace dlib;

int main() {
    // генерую чотири множини даних
    matrix<double> centers(4, 2);
    centers(0, 0) = -1; centers(0, 1) = 0;
    centers(1, 0) = 0; centers(1, 1) = 1;
    centers(2, 0) = 1; centers(2, 1) = 0;
    centers(3, 0) = 0; centers(3, 1) = -1;

    matrix<double> data;
    for (int i = 0; i < 4; ++i) {
        matrix<double> cluster = 0.2 * randn(30, 2) + repmat(centers.row(i), 30, 1);
        data = join_cols(data, cluster);
    }

    // отримую метки кластерів (0, 1, 2, 3)
    matrix<double> labels;
    for (int i = 0; i < 4; ++i) {
        labels = join_cols(labels, ones_matrix<double>(30, 1) * i);
    }

    // треную нейронну мережу для кластеризації
    typedef mlp::kernel_1a_c<mlp::tan_h> net_type;
    net_type net;
    dlib::svm_c_linear<net_type> trainer;

    trainer.set_kernel(net);
    trainer.set_c(10);
    trainer.train(data, labels);

    // класифікую дані за допомогою нейронної мережі
    matrix<double> predicted_labels = net(data);

    // виводжу результати
    cout << "Предсказані метки:\n" << predicted_labels << endl;

    return 0;
}
