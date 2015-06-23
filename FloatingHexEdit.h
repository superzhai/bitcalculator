#ifndef FLOATINGHEXEDIT_H
#define FLOATINGHEXEDIT_H

#include <QtGui>
#include <stdio.h>
#include <QtDebug>
#include <QObject>
#include <QLineEdit>


class FloatingHexEdit: public QLineEdit {

	Q_OBJECT
public:
	unsigned long int mask;

	FloatingHexEdit();
	void updateValueWithMask(unsigned long int value);


	void focusOutEvent(QFocusEvent * event) {
		(void)event;
		QLineEdit::focusOutEvent(event);
		this->deselect();
	}

public slots:
	void editingFinishedA();

signals:
	void valueChanged(unsigned long int newValue, unsigned long int mask);
};
#endif
