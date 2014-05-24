#ifndef COMMONSTATUSDISPLAYWIDGET_H
#define COMMONSTATUSDISPLAYWIDGET_H

#include <QWidget>

#include <Payload.h>

namespace Ui {
class CommonStatusDisplayWidget;
}

class CommonStatusDisplayWidget : public QWidget
{
	Q_OBJECT

public:
	explicit CommonStatusDisplayWidget(QWidget *parent = 0);
	~CommonStatusDisplayWidget();

	void update(StatusPayload status);

private:
	Ui::CommonStatusDisplayWidget *ui;
};

#endif // COMMONSTATUSDISPLAYWIDGET_H
