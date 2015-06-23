#include "BitCalculator.h"
#include <unistd.h>
#include <QTimer>

void BitCalculator::mousePressEvent(QMouseEvent * event)
{

	selectedRect.setLeft(event->x());
	selectedRect.setTop(event->y());
	selectedRect.setWidth(0);
	selectedRect.setHeight(0);

}

void BitCalculator::mouseMoveEvent(QMouseEvent * event)
{


	selectedRect.setRight(event->x());
	selectedRect.setBottom(event->y());
	this->update();
}

void BitCalculator::mouseReleaseEvent(QMouseEvent * event)
{

	(void) event;

	QRect range = selectedRect.normalized();

	if (!range.isEmpty()) {

		unsigned long int bitset = 0;

		for (int i = 0; i < 32; i++) {

			QPoint point =
			    bitEdit[i].mapToParent(QPoint(0, 0));

			QRect bitEditRect;
			bitEditRect.setTopLeft(point);
			bitEditRect.setWidth(bitEdit[i].width());
			bitEditRect.setHeight(bitEdit[i].height());

			if (bitEditRect.intersects(range)) {
				bitset |= 1 << i;
			}
		}


		this->maskChanged(bitset);
	}

	selectedRect.setRect(0, 0, 0, 0);
}

void BitCalculator::maskRestore(void)
{

	maskChanged(this->mask);
}

void BitCalculator::maskChanged(unsigned long int mask)
{


	unsigned long int tmp;

	tmp = mask;

	while (tmp && !(tmp & 1)) {
		tmp >>= 1;
	}

	if (tmp == 1) {
		maskRestore();
		return;
	} else if (mask) {
		hint.setText("");
		int leftmostx = -1, rightmostx = -1;

		/* try to find the leftmost x, and rightmost y 
		 * according to the bit map. */

		for (int i = 31; i >= 0; i--) {

			if (leftmostx == -1 && (mask & (1 << i))) {
				leftmostx =
				    bitEdit[i].
				    mapToParent(QPoint(0, 0)).x();
			}

			if (leftmostx != -1 && (mask & (1 << i))) {
				rightmostx =
				    bitEdit[i].
				    mapToParent(QPoint(0, 0)).x() +
				    bitEdit[i].width();
			}
		}

		QPoint point = hint.mapToParent(QPoint(0, 0));

		QRect floatingHexEditRect;

		floatingHexEditRect.setTop(point.y());
		floatingHexEditRect.setHeight(hint.height());
		floatingHexEditRect.setLeft(leftmostx);
		floatingHexEditRect.setWidth(rightmostx - leftmostx);

		floatingHexEdit.move(floatingHexEditRect.x(),
				     floatingHexEditRect.y());

		floatingHexEdit.setFixedWidth(floatingHexEditRect.width());
		floatingHexEdit.
		    setFixedHeight(floatingHexEditRect.height());
		floatingHexEdit.raise();
		floatingHexEdit.mask = mask;
		floatingHexEdit.updateValueWithMask(reg);
		floatingHexEdit.show();


	} else {

		hint.setText("Drag select to create bitmask");
		floatingHexEdit.hide();
	}

	maskEdit.setText(QString().sprintf("0x%08X", (unsigned int) mask));

	this->mask = mask;
}


void BitCalculator::valueChanged(unsigned long int value,
				 unsigned long int valueMask)
{

	reg &= ~valueMask;
	reg |= value & valueMask;


	/* set bit edit */
	for (int i = 0; i < 32; i++) {
		bitEdit[i].asserted = (reg & (1 << i)) ? true : false;
		bitEdit[i].update();
	}

	/* set hex edit */
	QString tmp;
	tmp.sprintf("0x%08X", (unsigned int) reg);

	hexEdit.setText(tmp);

	/* set dec edit */
	tmp.sprintf("%lu", reg);
	decEdit.setText(tmp);


	floatingHexEdit.mask = mask;
	floatingHexEdit.updateValueWithMask(reg);

	maskEdit.setText(QString().sprintf("0x%08X", (unsigned int) mask));



}

void BitCalculator::iconActivated(QSystemTrayIcon::ActivationReason reason)
{

	switch (reason) {
	case QSystemTrayIcon::Trigger:
	case QSystemTrayIcon::DoubleClick:
		if (this->isVisible())
			currentPos = this->pos();
		this->setVisible(!this->isVisible());

		if (this->isVisible())
			this->move(currentPos);
	default:
		break;
	}

}


void BitCalculator::paintEvent(QPaintEvent *)
{

	QPainter paint(this);

	if (!selectedRect.normalized().isEmpty()) {
		paint.drawRect(selectedRect.normalized());
		this->update();
	}
}


BitCalculator::BitCalculator():windowLayout(this), hint("Drag select to create bitmask"), hexLabel("HEX"),
decLabel("DEC"), maskLabel("Current mask"), reg(0), mask(0),
trayIcon(this), contextMenu(this), exitAction(tr("Exit"), this)
{

	hint.setAlignment(Qt::AlignCenter);

	/* At the beginning, all of bitEdit should belong to 
	 * bitGroupLayout[0] */

	for (int i = 0; i < 32; i++) {
		QString tmp;
		tmp.sprintf("%d", 31 - i);
		bitLabel[31 - i].setText(tmp);
		bitLabel[31 - i].setAlignment(Qt::AlignCenter);
		labelLayout.addWidget(&bitLabel[31 - i]);
		bitEditLayout.addWidget(&bitEdit[31 - i]);
		bitEdit[31 - i].bitPos = 31 - i;
		connect(&bitEdit[31 - i],
			SIGNAL(valueChanged
			       (unsigned long int, unsigned long int)),
			this,
			SLOT(valueChanged
			     (unsigned long int, unsigned long int)));
	}

	connect(&floatingHexEdit,
		SIGNAL(valueChanged(unsigned long int, unsigned long int)),
		this,
		SLOT(valueChanged(unsigned long int, unsigned long int)));

	connect(&hexEdit,
		SIGNAL(valueChanged(unsigned long int, unsigned long int)),
		this,
		SLOT(valueChanged(unsigned long int, unsigned long int)));

	connect(&decEdit,
		SIGNAL(valueChanged(unsigned long int, unsigned long int)),
		this,
		SLOT(valueChanged(unsigned long int, unsigned long int)));


	connect(&maskEdit, SIGNAL(maskChanged(unsigned long int)),
		this, SLOT(maskChanged(unsigned long int)));


	connect(&maskEdit, SIGNAL(maskRestore(void)),
		this, SLOT(maskRestore(void)));

	connect(&trayIcon,
		SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this,
		SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));


	connect(&exitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

	contextMenu.addAction(&exitAction);
	trayIcon.setContextMenu(&contextMenu);

	hint.setFixedHeight(22);

	floatingHexEditLayout.addWidget(&hint);
	floatingHexEdit.hide();
	floatingHexEdit.setParent(this);



	summaryEditLayout.addWidget(&hexLabel);
	summaryEditLayout.addWidget(&hexEdit);

	summaryEditLayout.addWidget(&decLabel);
	summaryEditLayout.addWidget(&decEdit);
	summaryEditLayout.addWidget(&maskLabel);
	summaryEditLayout.addWidget(&maskEdit);

	windowLayout.addLayout(&labelLayout);
	windowLayout.addLayout(&bitEditLayout);
	windowLayout.addLayout(&floatingHexEditLayout);
	windowLayout.addLayout(&summaryEditLayout);

	setWindowTitle(QApplication::translate
		       ("BitCalculator", "BitCalculator"));
	setLayout(&windowLayout);

	setWindowIcon(QIcon(":images/appIcon.png"));

	if (!QSystemTrayIcon::isSystemTrayAvailable())
		QTimer::singleShot(3000, this, SLOT(setTrayIcon()));
	else
		setTrayIcon();


	valueChanged(reg, 0xffffffff);

}

void BitCalculator::setTrayIcon(void)
{

	int count = 10;
	while (count-- && !QSystemTrayIcon::isSystemTrayAvailable()) {
		sleep(1);
	}

	if (!QSystemTrayIcon::isSystemTrayAvailable()) {
		this->show();
	} else {
		trayIcon.setIcon(QIcon(":images/trayIcon.png"));
		trayIcon.show();
		this->hide();
	}

}
