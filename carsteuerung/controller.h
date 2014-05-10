#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QTextEdit>
#include <set>

#include <SerialStream.h>

class Controller : public QTextEdit
{
public:
    explicit Controller(QWidget* parent);

    void setStream(LibSerial::SerialStream* serialStream);

protected:
    void keyPressEvent(QKeyEvent *e) override;
    void keyReleaseEvent(QKeyEvent *e) override;

private:
    void sendToSerialStream();

private:
    LibSerial::SerialStream* serialStream = nullptr;

    std::set<int> pressedKeys;
};

#endif // CONTROLLER_H
