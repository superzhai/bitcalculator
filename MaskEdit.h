#ifndef MASKEDIT_H
#define MASKEDIT_H

#include <QtGui>
#include <stdio.h>
#include <QtDebug>
#include <QObject>
#include "HexEdit.h"


class MaskEdit: public QLineEdit {
	Q_OBJECT
public slots:
	void editingFinishedA();

signals:
	void maskChanged(unsigned long int mask);
	void maskRestore(void);
public:
	MaskEdit();


	void focusOutEvent(QFocusEvent * event) {
		(void) event;
		QLineEdit::focusOutEvent(event);
		this->deselect();
	}

};
#endif
