#ifndef WORDWIZARD_H
#define WORDWIZARD_H

#include <QtGui>
#include <stdio.h>
#include <QtDebug>
#include <QObject>
#include <QSystemTrayIcon>
#include <QVBoxLayout>
#include <QLabel>
#include <QApplication>
#include <QMenu>
#include <QAction>

#include "BitEdit.h"
#include "FloatingHexEdit.h"
#include "HexEdit.h"
#include "MaskEdit.h"
#include "DecEdit.h"



class BitCalculator: public QWidget {


	Q_OBJECT

	QSystemTrayIcon trayIcon;
	QMenu contextMenu;
	QAction exitAction;

	QRect selectedRect;
	QVBoxLayout windowLayout;
	QHBoxLayout labelLayout;
	QHBoxLayout bitEditLayout;
	QHBoxLayout floatingHexEditLayout;
	QHBoxLayout summaryEditLayout;
	BitEdit bitEdit[32];
	QLabel hexLabel;
	QLabel decLabel;
	QLabel maskLabel;
	HexEdit hexEdit;
	DecEdit decEdit;
	MaskEdit maskEdit;
	FloatingHexEdit floatingHexEdit;
	QLabel bitLabel[32];
	QLabel hint;
	QPoint currentPos;

	unsigned long int reg;
	unsigned long int mask;

public slots:
	void valueChanged(unsigned long int value, unsigned long int valueMask);
	void maskChanged(unsigned long int mask);
	void maskRestore(void);
	void iconActivated(QSystemTrayIcon::ActivationReason);
	void setTrayIcon(void);

public:
	void paintEvent(QPaintEvent *);


	BitCalculator();

	void mousePressEvent(QMouseEvent * event);
	void mouseMoveEvent(QMouseEvent * event);
	void mouseReleaseEvent(QMouseEvent * event);
	void closeEvent(QCloseEvent * event) {
		currentPos = this->pos();
		this->hide();
		event->ignore();
	}

	void resizeEvent(QResizeEvent * event) {
		this->maskRestore();
	}


};
#endif
