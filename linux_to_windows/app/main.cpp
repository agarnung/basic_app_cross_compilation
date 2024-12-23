#include <QtWidgets>

#include <QtStateMachine/QStateMachine>
#include <QtStateMachine/QState>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    app.setApplicationName("Naive app");

    QPushButton button;
    QStateMachine machine;

    QState* off = new QState();
    off->assignProperty(&button, "text", "Off");
    off->setObjectName("off");

    QState* on = new QState();
    on->setObjectName("on");
    on->assignProperty(&button, "text", "On");

    off->addTransition(&button, &QPushButton::clicked, on);
    on->addTransition(&button, &QAbstractButton::clicked, off);

    machine.addState(off);
    machine.addState(on);

    machine.setInitialState(off);
    machine.start();

    button.setMinimumSize(QSize(150, 50));
    button.show();

    return app.exec();
}
