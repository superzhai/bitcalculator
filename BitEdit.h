#ifndef BITEDIT_H
#define BITEDIT_H
#include <QtGui>
#include <stdio.h>
#include <QtDebug>
#include <QObject>
#include <QLineEdit>


class BitEdit : public QLineEdit {


	Q_OBJECT
public:
	bool asserted;
	int bitPos;

signals:
	void valueChanged(unsigned long int newValue, unsigned long int mask);

public:

	BitEdit():asserted(false), bitPos(-1) {
		setAlignment(Qt::AlignCenter);
		setReadOnly(true);
		setFocusPolicy(Qt::NoFocus);
		setMaxLength(1);
		setMinimumWidth(20);
		setMaximumWidth(25);
		update();
	}

	void mouseReleaseEvent(QMouseEvent * event);
	void update(void);

};
#endif
