#ifndef FADERWIDGET_H
#define FADERWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QColor>

class FaderWidget: public QWidget
{
	Q_OBJECT
public:
	FaderWidget(QWidget* parent=0);
	void start();
protected:
	void paintEvent(QPaintEvent* event);
private:
	QTimer *timer ;
	int currentAlpha ;
	QColor startColor ;
	int duration ;
};
#endif
