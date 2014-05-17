#include "StatusDisplayWidget.h"
#include "ui_StatusDisplayWidget.h"

#include "InvokeInEventLoop.h"

#include <QDateTime>

StatusDisplayWidget::StatusDisplayWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::StatusDisplayWidget)
{
	ui->setupUi(this);
}

StatusDisplayWidget::~StatusDisplayWidget()
{
	delete ui;
}

void StatusDisplayWidget::update(StatusPayload status)
{
	callFnDeferredAsync(this, [=]
	{
		ui->freePages->setText(QString::number(status.freePages) + " (" + QString::number(status.freePages * status.pageSize) + " Bytes)");
		ui->usedPages->setText(QString::number(status.usedPages) + " (" + QString::number(status.usedPages * status.pageSize) + " Bytes)");
		ui->pageSize->setText(QString::number(status.pageSize) + " Bytes");
		ui->taskQueueLoad->setText(QString::number(status.taskQueueLoad) + " Tasks");
		ui->lastUpdate->setText(QDateTime::currentDateTime().toString());

		ui->barTaskQueueLoad->setMaximum(256);
		ui->barTaskQueueLoad->setValue(status.taskQueueLoad);

		ui->barUsedPagesProgressBar->setMaximum(status.usedPages + status.freePages);
		ui->barUsedPagesProgressBar->setValue(status.usedPages);
	});
}
