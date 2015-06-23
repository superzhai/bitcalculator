#include "HexEdit.h"
#include <QString>

void HexEdit::editingFinishedA() {
	bool ok=false;
	unsigned long long val=0;

	val=text().toULongLong(&ok,16);

	if (ok) {
		val &= 0xffffffff;
		emit valueChanged(val, (unsigned long int )0xffffffff);
	} else {
		emit valueChanged(0, (unsigned long int )0x0);
	}
	this->selectAll();
}
