#include "CommonStatusDisplayWidget.h"
#include "ui_CommonStatusDisplayWidget.h"

#include <InvokeInEventLoop.h>

#include <QDateTime>

CommonStatusDisplayWidget::CommonStatusDisplayWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::CommonStatusDisplayWidget)
{
	ui->setupUi(this);
}

CommonStatusDisplayWidget::~CommonStatusDisplayWidget()
{
	delete ui;
}

void CommonStatusDisplayWidget::update(StatusPayload status)
{
	callFnDeferredAsync(this, [=]() mutable
	{
		ui->chargeStatus->setText(QString::number(status.chargeStatus()));
		ui->linePosition->setText(QString::number(status.linePosition));
		ui->lineWidth->setText(QString::number(status.lineWidth()));
		ui->voltage->setText(QString::number(status.voltage()));
		ui->current->setText(QString::number(status.current()));

		ui->lastUpdate->setText(QDateTime::currentDateTime().toString());
	});
}
