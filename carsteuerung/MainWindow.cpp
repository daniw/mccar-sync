#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "InvokeInEventLoop.h"
#include <Payload.h>

#include <boost/algorithm/string.hpp>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
    ui(new Ui::MainWindow),
    receiveThread(std::bind(&MainWindow::worker, this))
{
	ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    serialStream.Close();
    receiveThread.interrupt();
    if (!receiveThread.timed_join(boost::posix_time::seconds(1)))
    {
        abort();
    }
	delete ui;
}

void MainWindow::printLog(QString text)
{
    callFnDeferredSync(this, [=]
    {
        ui->log->appendPlainText(QString::number(byteCounter.load()) + ", " + QDateTime::currentDateTime().toString("hh:mm:ss.zzz") + ": " + text);
    });
}

void MainWindow::on_connectButton_clicked()
{
    serialStream.SetBaudRate(LibSerial::SerialStreamBuf::BAUD_9600);
    serialStream.SetNumOfStopBits(0);
    serialStream.SetParity(LibSerial::SerialStreamBuf::PARITY_NONE);
    serialStream.SetCharSize(LibSerial::SerialStreamBuf::CHAR_SIZE_8);

	serialStream.Open(ui->serialPort->text().toStdString());
	if (serialStream.IsOpen())
    {
        ui->log->appendPlainText("Successfully opened serial port " + ui->serialPort->text());
        programState = ProgramState::Connected;
	}
	else
	{
		ui->log->appendPlainText("Failed to open serial port " + ui->serialPort->text());
        programState = ProgramState::Disconnected;
	}
    updateUi();
}

void MainWindow::updateUi()
{
	switch (programState)
	{
	case ProgramState::Disconnected:
        ui->connectButton->setEnabled(true);
        ui->control->setStream(nullptr);
		break;

	case ProgramState::Connected:
		ui->connectButton->setEnabled(false);
        ui->control->setStream(&serialStream);
		break;
    }
}

void MainWindow::worker()
{
    for (;;)
    {
        RestoreFlagsCheckpointContext savedFlags{serialStream};
        serialStream.unsetf(std::ios_base::skipws);
        if (serialStream.IsOpen())
        {
            uint8_t cmd;
            serialStream >> cmd;
            if (cmd == NotifyVersionPayload::cmd_id)
            {
                RequestDataPacket<NotifyVersionPayload> data;
                serialStream >> data;
                printLog(QString("MC version: ") + QString::number(data.payload.version));
            }
            else if (cmd == WriteDataPayload::cmd_id)
            {
                RequestDataPacket<WriteDataPayload> data;
                serialStream >> data;

                printLog(QString("receiving data for buffer ") + QString::number(data.payload.bufferNo) + " (offset: " + QString::number(data.payload.offset) + ") ...");
                if (data.payload.offset != m_swapCache[data.payload.bufferNo].size())
                {
                    m_swapCache[data.payload.bufferNo].clear();
                }

                for (auto entry : data.payload.data)
                {
                    m_swapCache[data.payload.bufferNo].push_back(entry);
                }
            }
            else if (cmd == RequestDataPayload::cmd_id)
            {
                RequestDataPacket<RequestDataPayload> data;
                serialStream >> data;

                printLog(QString("sending buffer no ") + QString::number(data.payload.bufferNo) + "...");
                const auto& relevantCache = m_swapCache[data.payload.bufferNo];
                uint8_t i = 0;
                while (i < relevantCache.size())
                {
                    HandleRequestedDataPayload payload;
                    payload.bufferNo = data.payload.bufferNo;
                    for (uint8_t j = 0; j < sizeof(payload.data) && i < relevantCache.size(); ++i, ++j)
                    {
                        payload.data[j] = relevantCache[i];
                    }
                    serialStream << RequestDataPacket<HandleRequestedDataPayload>(payload);
                }
                printLog(QString("...buffer sent"));
            }
            else
            {
                std::vector<std::string> unknownData(getPayloadSize());
                for (size_t i = 0; i < getPayloadSize(); ++i)
                {
                    uint8_t val;
                    serialStream >> val;
                    unknownData[i] = std::to_string(uint32_t(val));
                }
                uint8_t crc;
                serialStream >> crc;
                std::string unknownDataString = boost::algorithm::join(unknownData, " ");
                printLog(QString("unknown command received: " + QString::number(cmd) + " [") + QString::fromStdString(unknownDataString) + "] crc: " + QString::number(crc));
            }
            byteCounter += 8;
        }
        else
        {
            boost::this_thread::sleep(boost::posix_time::seconds(2));
        }
    }
}

void MainWindow::on_echoTestButton_clicked()
{
    serialStream << RequestDataPacket<NotifyVersionPayload>(NotifyVersionPayload{1});
//    printLog(QString() + "Start sending...");
//    for (int i = 0; i < 80; ++i)
//    {
//        QApplication::processEvents();
//        printLog(QString() + "on");
//        serialStream << RequestDataPacket<MovePayload>(MovePayload{1 + 8 + 64 + 128});

//        QApplication::processEvents();
//        printLog(QString() + "off");
//        serialStream << RequestDataPacket<MovePayload>(MovePayload{0});

//    }
//    printLog(QString() + "...sent");
}
