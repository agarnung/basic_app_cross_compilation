#include <QtWidgets>
#include <QImage>
#include <QtStateMachine/QStateMachine>
#include <QtStateMachine/QState>

#include <opencv4/opencv2/opencv.hpp>

#include "assets/lena_inv.h"

// Hexadecimal Lena generated as $ xxd -i lena.png > lena.h

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    app.setApplicationName("Naive app");

    QImage img_on(":/assets/lena.png");
    if (img_on.isNull())
    {
        qDebug() << "Error: No se pudo cargar lena.png";
        return -1;
    }

    std::vector<uchar> inv_data(lena_inv_png, lena_inv_png + lena_inv_png_len);
    cv::Mat cvimg_off = cv::imdecode(inv_data, cv::IMREAD_COLOR);
    if (cvimg_off.empty())
    {
        qDebug() << "Error: No se pudo decodificar lena_inv.png";
        return -1;
    }
    QImage img_off(cvimg_off.data, cvimg_off.cols, cvimg_off.rows, cvimg_off.step, QImage::Format_BGR888);

    QLabel label;
    label.setAlignment(Qt::AlignCenter);
    label.setPixmap(QPixmap::fromImage(QImage::fromData(inv_data.data(), inv_data.size())));

    QPushButton button;

    QVBoxLayout layout;
    QWidget window;
    layout.addWidget(&label);
    layout.addWidget(&button);
    window.setLayout(&layout);
    window.setMinimumSize(QSize(400, 400));
    window.show();

    QStateMachine machine;

    QState* off = new QState();
    off->assignProperty(&button, "text", "Switch ON lights");
    QObject::connect(off, &QState::entered, [&]() {
        label.setPixmap(QPixmap::fromImage(img_off));
    });

    QState* on = new QState();
    on->assignProperty(&button, "text", "Switch OFF lights");
    QObject::connect(on, &QState::entered, [&]() {
        label.setPixmap(QPixmap::fromImage(img_on));
    });

    off->addTransition(&button, &QPushButton::clicked, on);
    on->addTransition(&button, &QPushButton::clicked, off);

    machine.addState(off);
    machine.addState(on);
    machine.setInitialState(on);
    machine.start();

    return app.exec();
}
