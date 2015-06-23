#include "DecEdit.h"
#include <QDebug>


void DecEdit::editingFinishedA() {

	bool ok;
	int val = text().toULong(&ok, 10);

	if (ok)
		emit valueChanged(val, 0xffffffff);
	else
		emit valueChanged(0, 0);

	this->selectAll();
}
