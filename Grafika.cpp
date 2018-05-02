#include "Grafika.h"

Grafika::Grafika(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.scrollArea->setWidget(&this->widgetNaKreslenie);
	ui.scrollArea->setBackgroundRole(QPalette::Dark);

	widgetNaKreslenie.newImage(469, 449);
	widgetNaKreslenie.initImage();
	widgetNaKreslenie.nacitanie_dat_sfera();
	widgetNaKreslenie.zBuffer1();

	if (ui.stredova->isChecked())
		ui.dist->setEnabled(true);
	else ui.dist->setEnabled(false);
	ui.rovnobezna->setEnabled(true);
	ui.stredova->setEnabled(true);
	ui.vymaz->setEnabled(true);
	widgetNaKreslenie.sustava(0, 0);
	widgetNaKreslenie.transformacia_rovnobezna();
	widgetNaKreslenie.kresli_body();
	widgetNaKreslenie.kresli_spoje();
	ui.kresli->setEnabled(false);
	ui.R->setEnabled(false);
	ui.G->setEnabled(false);
	ui.B->setEnabled(false);
	ui.pozorovatel->setEnabled(false);
	ui.svetlo->setEnabled(false);
}


void Grafika::on_rovnobezna_clicked() {
	ui.uhly->setEnabled(true);
	ui.dist->setEnabled(false);
}

void Grafika::on_stredova_clicked() {
	ui.uhly->setEnabled(true);
	ui.dist->setEnabled(true);
}


void Grafika::on_vymaz_clicked() {
	widgetNaKreslenie.newImage(469, 449);
	widgetNaKreslenie.initImage();
	
	widgetNaKreslenie.vymaz();
	ui.tienovanie->setEnabled(true);
}

void Grafika::transformacia_rovnobezna(int tetha, int fi){
	widgetNaKreslenie.newImage(469, 449);

	widgetNaKreslenie.initImage();
	widgetNaKreslenie.sustava(tetha, fi);
	widgetNaKreslenie.transformacia_rovnobezna();
	widgetNaKreslenie.kresli_body();
	widgetNaKreslenie.kresli_spoje();
}

void Grafika::transformacia_stredova(int tetha, int fi, double distancia){
	widgetNaKreslenie.newImage(469, 449);

	widgetNaKreslenie.initImage();
	widgetNaKreslenie.sustava(tetha, fi);
	widgetNaKreslenie.transformacia_distancia(distancia);
	widgetNaKreslenie.kresli_body();
	widgetNaKreslenie.kresli_spoje();
	
}


void Grafika::on_tetha_sliderMoved(int hodnota) {
	QString s = QString::number(hodnota);

	if (ui.rovnobezna->isChecked()) {
		transformacia_rovnobezna(ui.tetha->value(), ui.fi->value());
	}
	else if (ui.stredova->isChecked()) {
		transformacia_stredova(ui.tetha->value(), ui.fi->value(), (ui.distancia->value()));
	}

}

void Grafika::on_fi_sliderMoved(int hodnota) {
	QString s = QString::number(hodnota);
	
	if (ui.rovnobezna->isChecked()) {
		transformacia_rovnobezna(ui.tetha->value(), ui.fi->value());
	}
	else if (ui.stredova->isChecked()) {
		transformacia_stredova(ui.tetha->value(), ui.fi->value(), (ui.distancia->value()));
	}


}

void Grafika::on_kresli_clicked() {
	widgetNaKreslenie.POM( ui.orred->value(), ui.orgreen->value(), ui.orblue->value(),	ui.dored->value(), ui.dogreen->value(), ui.doblue->value(),
		ui.ddred->value(), ui.ddgreen->value(), ui.ddblue->value(), ui.dared->value(), ui.dagreen->value(), ui.dablue->value(),
		ui.arred->value(), ui.argreen->value(), ui.arblue->value());
	widgetNaKreslenie.koefPZ(ui.pozorovatelz->value(), ui.zdrojx->value(), ui.zdrojy->value(), ui.zdrojz->value());

	if (ui.konstantne->isChecked()) {
		widgetNaKreslenie.scanLine(0);
	}
	else widgetNaKreslenie.scanLine(1);


	ui.tienovanie->setEnabled(false);
	ui.kresli->setEnabled(false);
	ui.R->setEnabled(false);
	ui.G->setEnabled(false);
	ui.B->setEnabled(false);
	ui.pozorovatel->setEnabled(false);
	ui.svetlo->setEnabled(false);
}

void Grafika::on_distancia_sliderMoved(int hodnota) {
	QString s = QString::number(hodnota);

	if (ui.stredova->isChecked()) {
		transformacia_stredova(ui.tetha->value(), ui.fi->value(), (ui.distancia->value()));
	}
}

void Grafika::on_konstantne_clicked() {
	ui.kresli->setEnabled(true);
	ui.R->setEnabled(true);
	ui.G->setEnabled(true);
	ui.B->setEnabled(true);
	ui.pozorovatel->setEnabled(true);
	ui.svetlo->setEnabled(true);

}

void Grafika::on_gouradovo_clicked() {
	ui.kresli->setEnabled(true);
	ui.R->setEnabled(true);
	ui.G->setEnabled(true);
	ui.B->setEnabled(true);
	ui.pozorovatel->setEnabled(true);
	ui.svetlo->setEnabled(true);
}


