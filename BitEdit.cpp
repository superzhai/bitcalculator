#include "BitEdit.h"


void BitEdit::mouseReleaseEvent(QMouseEvent * event) {
		asserted^=1;
		update();

		if (bitPos!=-1) {
			emit valueChanged((unsigned long int)asserted << bitPos, (unsigned long int )1<<bitPos);
		}
}

void BitEdit::update(void) {
//		this->text() = (asserted? "1":"0");
		asserted?setStyleSheet("QLineEdit { background-color : red; color : white;}"):
				setStyleSheet("QLineEdit{ background-color : yellow; color : black;}");
		this->setText(asserted? QString("1"): QString("0"));

}

