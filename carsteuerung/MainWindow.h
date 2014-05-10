#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <SerialStream.h>
#include <boost/thread.hpp>
#include <atomic>

namespace Ui {
class MainWindow;
}

enum class ProgramState
{
	Disconnected,
	Connected
};

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void on_connectButton_clicked();
	void on_echoTestButton_clicked();

private:
    void printLog(QString text);
	void updateUi();
    void worker();
    void sendWorker();

private:
	Ui::MainWindow *ui;

	ProgramState programState;
	LibSerial::SerialStream serialStream;

    std::map<uint8_t, std::vector<uint8_t>> m_swapCache;

    boost::thread receiveThread;
    boost::thread sendThread;
    std::atomic_uint_fast64_t byteCounter{0};
};

#endif // MAINWINDOW_H
