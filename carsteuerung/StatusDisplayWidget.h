#ifndef STATUSDISPLAYWIDGET_H
#define STATUSDISPLAYWIDGET_H

#include <QWidget>

namespace Ui {
class StatusDisplayWidget;
}

class StatusDisplayWidget : public QWidget
{
	Q_OBJECT

public:
	explicit StatusDisplayWidget(QWidget *parent = 0);
	~StatusDisplayWidget();

private:
	Ui::StatusDisplayWidget *ui;
};

#endif // STATUSDISPLAYWIDGET_H