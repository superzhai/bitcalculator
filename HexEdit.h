#ifndef HEXEDIT_H
#define HEXEDIT_H
#include <QtGui>
#include <stdio.h>
#include <QtDebug>
#include <QObject>
#include <QLineEdit>

class HexEdit: public QLineEdit {

	Q_OBJECT

public:
	HexEdit() {
		setAlignment(Qt::AlignCenter);
		this->setMaxLength(10);
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
