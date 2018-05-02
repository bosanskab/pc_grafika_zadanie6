#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Grafika.h"
#include <QDebug>
#include "QtClass.h"

class Grafika : public QMainWindow
{
	Q_OBJECT

public:
	Grafika(QWidget *parent = Q_NULLPTR);
	public slots:
	void on_vymaz_clicked();
	void on_rovnobezna_clicked();
	void on_stredova_clicked();
	void on_tetha_sliderMoved(int);
	void on_fi_sliderMoved(int);
	void on_distancia_sliderMoved(int);
	void transformacia_rovnobezna(int tetha, int fi);
	void transformacia_stredova(int tetha, int fi, double distancia);
	void on_gouradovo_clicked();
	void on_konstantne_clicked();
	void on_kresli_clicked();
private:
	Ui::GrafikaClass ui;
	QtClass widgetNaKreslenie;
};