#include "controller.h"

#include <Payload.h>

#include <QKeyEvent>

#include <map>
#include <iostream>

Controller::Controller(QWidget *parent)
    : QTextEdit(parent)
{
}

void Controller::setStream(LibSerial::SerialStream *serialStream)
{
    this->serialStream = serialStream;
}

void Controller::keyPressEvent(QKeyEvent *e)
{
    if (!e->isAutoRepeat())
    {
        pressedKeys.insert(e->key());
        sendToSerialStream();
    }
}

void Controller::keyReleaseEvent(QKeyEvent *e)
{
    if (!e->isAutoRepeat())
    {
        e->accept();
        pressedKeys.erase(e->key());
        sendToSerialStream();
    }
}

void Controller::sendToSerialStream()
{
    if (serialStream)
    {
        static std::map<Qt::Key, uint8_t> mapping = {
            { Qt::Key_Up,   1   },
            { Qt::Key_Down, 4   },
            { Qt::Key_Left, 8   },
            { Qt::Key_Right,2   },
            { Qt::Key_A,    16  },
            { Qt::Key_D,    32  },
            { Qt::Key_W,    64  },
            { Qt::Key_S,    128 }
        };

        uint8_t cmd = 0;
        for (auto keyMapping : mapping)
        {
            if (pressedKeys.find(keyMapping.first) != pressedKeys.end())
            {
                cmd |= keyMapping.second;
            }
        }

        *serialStream << RequestDataPacket<MovePayload>(MovePayload{cmd});

        setText(QString::number(cmd));
    }
}
