#include "MaskEdit.h"

#include <QString>


MaskEdit::MaskEdit() {

	setAlignment(Qt::AlignCenter);
	this->setMaxLength(10);

	connect(this, SIGNAL(editingFinished()), this,
			SLOT(editingFinishedA()));

	setContextMenuPolicy(Qt::PreventContextMenu);

}

void MaskEdit::editingFinishedA() {

	bool ok=false;
	
	/* TODO: use more specific like uint32, uint64 */
	unsigned long long val=0;
	unsigned long tmp=0;
	int leftc, rightc;


	val=text().toULongLong(&ok,16);



	if (ok) {
		val &= 0xffffffff;

	/* too make sure all bit 1 are contiguous */
	leftc = 0;
	rightc = 0;

	if (val) {
	tmp = val;
	while (tmp && !(tmp&1)) {
		tmp>>=1;
		rightc++;
	}

	tmp= val;
	while (tmp && !(tmp &0x80000000)) {
		tmp<<=1;
		leftc++;
	}

	tmp = 0xffffffff;

	tmp <<=leftc;
	tmp >>=leftc;
	tmp >>=rightc;
	tmp <<=rightc;

	val = tmp;
	}

		emit maskChanged((unsigned long int)val);
	} else {
		emit maskRestore();
	}

	this->selectAll();
}
