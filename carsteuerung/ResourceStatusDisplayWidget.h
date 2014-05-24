#ifndef RESOURCESTATUSDISPLAYWIDGET_H
#define RESOURCESTATUSDISPLAYWIDGET_H

#include <QWidget>

#include <Payload.h>

namespace Ui {
class ResourceStatusDisplayWidget;
}

class ResourceStatusDisplayWidget : public QWidget
{
	Q_OBJECT

public:
	explicit ResourceStatusDisplayWidget(QWidget *parent = 0);
	~ResourceStatusDisplayWidget();

	void update(ResourcePayload status);

private:
	Ui::ResourceStatusDisplayWidget *ui;
};

#endif // RESOURCESTATUSDISPLAYWIDGET_H
