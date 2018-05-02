#pragma once

#include <QWidget>
#include <QImage>
#include <QColor>
#include <QtWidgets>

struct S {
	double xz;
	double yz;
	double yk;
	double w;

	bool operator <(const S& P);
};

struct aktivneH {
	int riadok;
	int hrana;
};


class QtClass : public QWidget
{
	Q_OBJECT

protected:
	void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
	QImage *obrazok;
	QString typ;
	int	pocetPointov;
	QVector<QVector3D> Point;
	QVector<QVector3D> newPoint;
	int pocetS;
	QVector<int> pocty_spojov;
	QVector<QVector3D> indexy_bodov;
	QVector3D Eye;
	QVector3D Normala,normala, norm1,norm2;
	QVector3D osX;
	QVector3D osY;

	QVector<S> TH;
	QVector<aktivneH> TAH;
	int ymin, ymax;


	QColor colorT, colorS;
	QImage *img;
	int row;
	QRgb* data;
	double R, A, D;
	double C1, C2, C3;
	double Red, Green, Blue;

	QColor **farby;
	double **hlbka;
	QVector3D vectN, vectL, vectR, vectV;

	QColor color1, color2, color3;
	QVector3D pozorovatel, zdroj;
	double orred, orgreen, orblue;
	double dored, dogreen, doblue;
	double ddred, ddgreen, ddblue;
	double dared, dagreen, dablue;
	double arred, argreen, arblue;

public:
	QtClass(QWidget *parent = Q_NULLPTR);
	~QtClass();
	void newImage(int x, int y);
	void kresli_body();
	void kresli_spoje();
	void vyber_farby();
	void initImage();

	void setPixel(int x, int y, QColor color);
	void DDA(QVector3D A, QVector3D B);
	void DDA1(QVector3D A, QVector3D B, QColor color);
	void scanLine(int typt);

	void sustava(int tetha, int pi);
	void transformacia_rovnobezna();
	void transformacia_distancia(int d);
	void koefPZ(int z, int zdrojx, int zdrojy, int zdrojz);
	void normalaVypocet(int i);
	void nastavVektory(QVector3D P);


	void nacitanie_dat_sfera();
	void odrazova(double odrazivost, double odlesk, int farba);
	void difuzna(double difuzia, int farba);
	void ambientna(double zlozka, double koeficientAO);
	QColor Phong( QVector3D P);
	void POM(double orred, double orgreen, double orblue, double dored, double dogreen, double doblue,
		double ddred, double ddgreen, double ddblue, double dared, double dagreen, double dablue, double arred, double argreen, double arblue);
	QColor Barycentric(QVector3D A, QVector3D B, QVector3D C, QPoint P);
	QColor NearestN(QVector3D A, QVector3D B, QVector3D C, QPoint P);
	void zBuffer1();
	void zBuffer(double z, QColor color, int i, int j);

	void vymaz();
};

