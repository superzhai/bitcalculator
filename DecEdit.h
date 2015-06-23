#ifndef DECEDIT_H
#define DECEDIT_h
#include <QtGui>
#include <stdio.h>
#include <QtDebug>
#include <QObject>
#include <QLineEdit>

class DecEdit: public QLineEdit {
	Q_OBJECT
public:

	DecEdit(){
		setAlignment(Qt::AlignCenter);
		setMaxLength(10);
		connect(this, SIGNAL(editingFinished()), this,
			SLOT(editingFinishedA()));

		setContextMenuPolicy(Qt::PreventContextMenu);
	}
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
