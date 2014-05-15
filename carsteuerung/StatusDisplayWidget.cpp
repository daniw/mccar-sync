#include "StatusDisplayWidget.h"
#include "ui_StatusDisplayWidget.h"

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
