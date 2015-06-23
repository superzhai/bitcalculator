#include "FloatingHexEdit.h"
#include <string.h>


FloatingHexEdit::FloatingHexEdit():mask(0)
{

	setAlignment(Qt::AlignCenter);
	setMaxLength(10);
	connect(this, SIGNAL(editingFinished()), this,
			SLOT(editingFinishedA()));

	setContextMenuPolicy(Qt::PreventContextMenu);
}

void FloatingHexEdit::updateValueWithMask(unsigned long int value)
{
	char buf[100];

	unsigned long int tmask=mask;
	int editLength = 3;


	while (tmask && !(tmask&1 ))
		tmask>>=1;

	while (tmask && (tmask>>4)) {
		tmask >>= 4;
		editLength++;
	}

	tmask = mask;

	QString tmp;
	value&=tmask;
	while (tmask && !(tmask&1)) {
		value >>= 1;
		tmask >>= 1;
	}

	sprintf(buf, "0x%%0%dX", editLength-2);


	tmp.sprintf(buf, (unsigned int)value);
	this->setMaxLength(editLength);
	this->setText(tmp);
}

void FloatingHexEdit::editingFinishedA() {


	bool ok=false;
	unsigned long long val=0;
	unsigned long tmp=mask;

	val=text().toULongLong(&ok,16);

	if (ok) {
		while (tmp&& !(tmp&1)) { 
			val <<=1;
			tmp >>=1;
		}
		emit valueChanged((unsigned long int)val, (unsigned long int )mask);
	} else
		emit valueChanged(0, (unsigned long int )0);

	this->selectAll();

}
