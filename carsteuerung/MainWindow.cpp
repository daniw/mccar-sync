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
	serialStream.Open(ui->serialPort->text().toStdString());
	if (serialStream.IsOpen())
    {
		//Set Config afterwards!!!
		serialStream.SetBaudRate(LibSerial::SerialStreamBuf::BAUD_115200);
		serialStream.SetNumOfStopBits(0);
		serialStream.SetParity(LibSerial::SerialStreamBuf::PARITY_NONE);
		serialStream.SetCharSize(LibSerial::SerialStreamBuf::CHAR_SIZE_8);

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

				uint16_t bufferNo = data.payload.bufferNoHigh << 8 | data.payload.bufferNoLow;
				uint16_t offset = data.payload.offsetHigh << 8 | data.payload.offsetLow;
				printLog(QString("receiving data for buffer ") + QString::number(bufferNo) + " (offset: " + QString::number(offset) + ") ...");
				if (offset != m_swapCache[bufferNo].size())
                {
					m_swapCache[bufferNo].clear();
                }

                for (auto entry : data.payload.data)
                {
					m_swapCache[bufferNo].push_back(entry);
                }
            }
            else if (cmd == RequestDataPayload::cmd_id)
            {
                RequestDataPacket<RequestDataPayload> data;
                serialStream >> data;

				uint16_t bufferNo = data.payload.bufferNoHigh << 8 | data.payload.bufferNoLow;
				const auto& relevantCache = m_swapCache[bufferNo];
                uint8_t i = 0;
                while (i < relevantCache.size())
                {
                    HandleRequestedDataPayload payload;
					payload.bufferNoHigh = data.payload.bufferNoHigh;
					payload.bufferNoLow = data.payload.bufferNoLow;
                    for (uint8_t j = 0; j < sizeof(payload.data) && i < relevantCache.size(); ++i, ++j)
                    {
                        payload.data[j] = relevantCache[i];
                    }
					printLog(QString("sending buffer no ") + QString::number(bufferNo) + "...");
					serialStream << RequestDataPacket<HandleRequestedDataPayload>(payload);
                }
                printLog(QString("...buffer sent"));
            }
			else if (cmd == StatusPayload::cmd_id)
			{
				RequestDataPacket<StatusPayload> data;
				serialStream >> data;

				ui->statusDisplay->update(data.payload);
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
	//serialStream << RequestDataPacket<NotifyVersionPayload>(NotifyVersionPayload{1});
	printLog(QString() + "Start sending...");
	for (int i = 0; i < 20; ++i)
	{
		QApplication::processEvents();
		serialStream << RequestDataPacket<NotifyVersionPayload>(NotifyVersionPayload{1});

	}
	printLog(QString() + "...sent");
}
