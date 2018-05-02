
#include "QtClass.h"



bool S::operator< (const S &P) {

	if (P.yz < yz) {

		return true;
	}
	else if (P.xz < xz && P.yz == yz) {

		return true;
	}
	else if (P.w < w && P.xz == xz && P.yz == yz) {

		return true;
	}
	else return false;

}


QtClass::QtClass(QWidget *parent)
	: QWidget(parent) {
	vyber_farby();
}

QtClass::~QtClass()
{
}

void QtClass::vyber_farby() {
	QMessageBox msgBox;
	msgBox.setText(QStringLiteral("Zadaj farbu svetla "));
	msgBox.exec();
	colorS = QColorDialog::getColor(Qt::red, this);

	msgBox.setText(QStringLiteral("Zadaj farbu telese "));
	msgBox.exec();
	colorT = QColorDialog::getColor(Qt::blue, this);
	
}

void QtClass::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	QRect area = event->rect();
	painter.drawImage(area, *img, area);
}

void QtClass::newImage(int x, int y) {
	img = new QImage(x, y, QImage::Format_ARGB32);
	img->fill(Qt::white);
	this->setMinimumSize(img->size());

	update();
}

void QtClass::initImage() {
	this->resize(img->size());
	this->setMinimumSize(img->size());

	row = img->bytesPerLine() / 4;
	data = (QRgb *)img->bits();
}

void QtClass::setPixel(int x, int y, QColor color) {
	data[x + y * row] = color.rgb();
}
void QtClass::DDA1(QVector3D A, QVector3D B, QColor color) {
	double m, x, y, z;
	QVector3D C;

	m = (B.y() - A.y()) / (double)(B.x() - A.x());

	if ((fabs(m)) <= 1) {
		if (A.x() > B.x()) {
			C.setX(B.x());
			C.setY(B.y());
			C.setZ(B.z());
			B.setX(A.x());
			B.setY(A.y());
			B.setZ(A.z());
			A.setX(C.x());
			A.setY(C.y());
			A.setZ(C.z());
		}
		x = A.x();
		y = A.y();
		for (int i = A.x(); i < B.x(); i++) {
			x = x + 1;
			y = y + m;
			setPixel(x, y, color);
		}

	}
	else {
		if (A.y() > B.y()) {
			C.setX(B.x());
			C.setY(B.y());
			C.setZ(B.z());
			B.setX(A.x());
			B.setY(A.y());
			B.setZ(A.z());
			A.setX(C.x());
			A.setY(C.y());
			A.setZ(C.z());
		}
		x = A.x();
		y = A.y();
		for (int i = A.y(); i < B.y(); i++) {
			x = x + 1 / m;
			y = y + 1;
			setPixel(x,y, color);
		}

	}
	update();
}

void QtClass::DDA(QVector3D A, QVector3D B) {
	double m, x, y,z;
	QVector3D C;

	m = (B.y() - A.y()) / (double)(B.x() - A.x());

	if ((fabs(m)) <= 1) {
		if (A.x() > B.x()) {
			C.setX(B.x());
			C.setY(B.y());
			C.setZ(B.z());
			B.setX(A.x());
			B.setY(A.y());
			B.setZ(A.z());
			A.setX(C.x());
			A.setY(C.y());
			A.setZ(C.z());
		}
		x = A.x();
		y = A.y();
		for (int i = A.x(); i < B.x(); i++) {
			x = x + 1;
			y = y + m;
			z = (A.z() + B.z()) / 2;
			zBuffer(z, Qt::black, round(x), round(y));
		}

	}
	else {
		if (A.y() > B.y()) {
			C.setX(B.x());
			C.setY(B.y());
			C.setZ(B.z());
			B.setX(A.x());
			B.setY(A.y());
			B.setZ(A.z());
			A.setX(C.x());
			A.setY(C.y());
			A.setZ(C.z());
		}
		x = A.x();
		y = A.y();
		for (int i = A.y(); i < B.y(); i++) {
			x = x + 1 / m;
			y = y + 1;
			z = (A.z() + B.z()) / 2;
			zBuffer(z, Qt::black, round(x), round(y));
		}

	}
	update();
}

void QtClass::scanLine(int typt){
	QVector3D P[3],Q[3];
	S s;
	QColor color;
	int pom;
	for (int i = 0; i < indexy_bodov.size(); i++) {

		double priemerZ = (newPoint[indexy_bodov[i].x()].z() + newPoint[indexy_bodov[i].y()].z() + newPoint[indexy_bodov[i].z()].z()+600) / 3;
		normalaVypocet(i);

		Q[0].setX(newPoint[indexy_bodov[i].x()].x()+200);
		Q[0].setY(newPoint[indexy_bodov[i].x()].y() + 200);
		Q[0].setZ(newPoint[indexy_bodov[i].x()].z() + 200);
		nastavVektory(Q[0]);
		color1 = Phong(Q[0]);
		P[0] = Q[0];

		Q[1].setX(newPoint[indexy_bodov[i].y()].x() + 200);
		Q[1].setY(newPoint[indexy_bodov[i].y()].y() + 200);
		Q[1].setZ(newPoint[indexy_bodov[i].y()].z() + 200);
		nastavVektory(Q[1]);
		color2 = Phong(Q[1]);
		P[1] = Q[1];

		Q[2].setX(newPoint[indexy_bodov[i].z()].x() + 200);
		Q[2].setY(newPoint[indexy_bodov[i].z()].y() + 200);
		Q[2].setZ(newPoint[indexy_bodov[i].z()].z() + 200); 
		nastavVektory(Q[2]);
		color3 = Phong(Q[2]);
		P[2] = Q[2];

		for (int j = 0; j < 3; j++) {
			if (j == 2) {
				if (Point[0].y() == Point[j].y()) {
					
				}
				else if (P[0].y() < P[j].y()) {
					s.w = (P[j].x() - P[0].x()) / (double)(P[j].y() - P[0].y());
					if (s.w < -1 && s.w>1) {

					}
					else if (s.w > -1 && s.w<1)  {
						s.xz = P[j].x();
						s.yz = P[j].y();
						s.yk = P[0].y() - 1;
						s.w = (P[j].x() - P[0].x()) / (double)(P[j].y() - P[0].y());
						TH.push_back(s);
					}
				}
				else if (P[0].y() > P[j].y()) {
					s.w = (P[0].x() - P[j].x()) / (double)(P[0].y() - P[j].y());
					if (s.w < -1 && s.w>1) {

					}
					else if (s.w > -1 && s.w<1) {
						s.xz = P[0].x();
						s.yz = P[0].y();
						s.yk = P[j].y() - 1;
						TH.push_back(s);
					}
				}
			}
			else {
				if (Point[j].y() == Point[j + 1].y()) {
					
				}
				else if (P[j].y() < P[j + 1].y()) {
					s.w = (P[j + 1].x() - P[j].x()) / (double)(P[j + 1].y() - P[j].y());
					if (s.w < -1 && s.w>1) {

					}
					else if (s.w > -1 && s.w<1) {
						s.xz = P[j + 1].x();
						s.yz = P[j + 1].y();
						s.yk = P[j].y() - 1;
						TH.push_back(s);
					}
				}
				else if (P[j].y() > P[j + 1].y()) {
					s.w = (P[j + 1].x() - P[j].x()) / (double)(P[j + 1].y() - P[j].y());
					if (s.w < -1 && s.w>1) {

					}
					else if (s.w > -1 && s.w<1) {
						s.xz = P[j].x();
						s.yz = P[j].y();
						s.yk = P[j + 1].y() - 1;
						TH.push_back(s);
					}
				}
			}
			
		}
		std::sort(TH.begin(), TH.end());
		
		ymin = 500;
		ymax = 0;

		for (int j = 0; j < TH.size(); j++) {
			if (TH[j].yz > ymax) {
				ymax = TH[j].yz;
			}
			if (TH[j].yk < ymin) {
				ymin = TH[j].yk;
			}
		}
		aktivneH H;
		QVector<int> spoj;

		for (int j = ymin; j <= ymax; j++) {
			for (int k = 0; k < TH.size(); k++) {
				if ((TH[k].yz >= j && TH[k].yk <= j) || (TH[k].yk >= j && TH[k].yz <= j)) {
					H.riadok = j;
					H.hrana = k;
					TAH.push_back(H);
				}

			}
		}
		for (int j = ymin; j <= ymax; j++) {
			for (int k = 0; k < TAH.size(); k++) {
				if (TAH[k].riadok == j) {
					spoj.push_back(k);
				}
			}
		}
		for (int j = ymin; j <= ymax; j++) {
			double *xn = new double[spoj.size()];

			for (int o = 0; o < spoj.size(); o++) {
				xn[o] = TH[TAH[spoj[o]].hrana].xz + (TH[TAH[spoj[o]].hrana].w*(j - TH[TAH[spoj[o]].hrana].yz));
				
			}

			for (int k = 0; k < spoj.size()-1; k += 2) {
				if (xn[k] < xn[k + 1]) {
					for (int x = xn[k]; x < xn[k + 1]; x++) {
						if (typt == 0) {
							zBuffer(priemerZ, NearestN(Q[0], Q[1], Q[2], QPoint((int)(x), j)), x, j);
						}
						else {
							zBuffer(priemerZ, Barycentric(Q[0],Q[1],Q[2], QPoint((int)(x), j)), x, j);
						}
					}
				}
				else {
					for (int x = xn[k + 1]; x < xn[k]; x++) {

						if (typt == 0)
							zBuffer(priemerZ, NearestN(Q[0], Q[1], Q[2], QPoint((int)(x), j)), x, j);
						else
							zBuffer(priemerZ, Barycentric(Q[0], Q[1], Q[2], QPoint((int)(x), j)), x, j);

					}
				}
			}


			delete[] xn;

			DDA(P[0], P[1]);
			DDA(P[1], P[2]);
			DDA(P[0], P[2]);
			
		}
		spoj.clear();
		ymin = 500;
		ymax = 0;
		TH.clear();
		TAH.clear();
	}

	for (int l = 0; l < 469; l++) {
		for (int t = 0; t < 449; t++) {
			setPixel(l, t, farby[l][t]);
		}
	}
	update();

}


void QtClass::kresli_body() {
	QPoint X;
	for (int i = 0; i < newPoint.size(); i++) {
		X.setX(newPoint[i].x() + 200);
		X.setY(newPoint[i].y() + 200);
		setPixel(X.x() , X.y() , Qt::black);
	}

	update();
}

void QtClass::kresli_spoje() {
	QVector3D X[3];
	for (int i = 0; i < indexy_bodov.size(); i++) {
		X[0].setX(newPoint[indexy_bodov[i].x()].x()+200);
		X[0].setY(newPoint[indexy_bodov[i].x()].y()+200);
		X[0].setZ(newPoint[indexy_bodov[i].x()].z());

		X[1].setX(newPoint[indexy_bodov[i].y()].x()+200);
		X[1].setY(newPoint[indexy_bodov[i].y()].y()+200);
		X[1].setZ(newPoint[indexy_bodov[i].y()].z());


		X[2].setX(newPoint[indexy_bodov[i].z()].x()+200);
		X[2].setY(newPoint[indexy_bodov[i].z()].y()+200);
		X[2].setZ(newPoint[indexy_bodov[i].z()].z());

		DDA1(X[0],X[1],Qt::black);
		DDA1(X[0],X[2], Qt::black);
		DDA1(X[1],X[2], Qt::black);
	}
	update();
}


void QtClass::nacitanie_dat_sfera() {
	QVector3D p;
	QVector3D spoj;
	QString fileName = "sphere_1.vtk";
	QFile file(fileName);
	
	if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		int n = 0, i = 0;
		QTextStream stream(&file);
		QString line;
		QStringList list;

		do {
			line = stream.readLine();
			n++;
		} while (n != 4);

		n = 0;
		line = stream.readLine();
		list = line.split(' ');

		pocetPointov = list.at(1).toInt();
		typ = list.at(2);
		
		
			do {

			line = stream.readLine();
			list = line.split(' ');
			p.setX(list.at(0).toDouble() * 100);
			p.setY(list.at(1).toDouble() * 100);
			p.setZ(list.at(2).toDouble() * 100);
			Point.push_back(p);
			i++;

		} while (i != pocetPointov);
		
		line = stream.readLine();

		line = stream.readLine();
		list = line.split(' ');
		pocetS = list.at(1).toInt();

		i = 0;
		do {
			line = stream.readLine();
			list = line.split(' ');
			pocty_spojov.push_back(list.at(0).toInt());
			spoj.setX(list.at(1).toInt());
			spoj.setY(list.at(2).toInt());
			spoj.setZ(list.at(3).toInt());
			indexy_bodov.push_back(spoj);
			i++;
		} while (i != pocetS);

		file.close();
	}
	else {
		qDebug() << "Unable to open";
	}

}


void QtClass::sustava(int tetha1, int fi1) {
	double tetha, fi;

	tetha = tetha1 / 180. * M_PI;
	fi = fi1 / 180. * M_PI;

	normala.setX(qSin(tetha)*qCos(fi));
	normala.setY(qSin(tetha)*qSin(fi));
	normala.setZ(qCos(tetha));

	osX.setX(qSin(tetha + M_PI / 2)*qCos(fi));
	osX.setY(qSin(tetha + M_PI / 2)*qSin(fi));
	osX.setZ(qCos(tetha + M_PI / 2));

	osY.setX(normala.y()*osX.z() - normala.z()*osX.y());
	osY.setY(osX.x()*normala.z() - normala.x()*osX.z());
	osY.setZ(normala.x()*osX.y() - normala.y()*osX.x());

}


void QtClass::transformacia_rovnobezna() {
	float x, y, z;
	QVector3D NEW;
	newPoint.clear();

	for (int i = 0; i <pocetPointov; i++) {
		x = Point[i].x()*osX.x() + Point[i].y()*osX.y() + Point[i].z()*osX.z();
		y = Point[i].x()*osY.x() + Point[i].y()*osY.y() + Point[i].z()*osY.z();
		z = Point[i].x()*normala.x() + Point[i].y()*normala.y() + Point[i].z()*normala.z();
		NEW.setX(x);
		NEW.setY(y);
		NEW.setZ(z);
		newPoint.push_back(NEW);
	}

}

void QtClass::transformacia_distancia(int d) {
	float x, y, z;
	QVector3D NEW;
	newPoint.clear();

	for (int i = 0; i < pocetPointov; i++) {
		x = Point[i].x()*osX.x() + Point[i].y()*osX.y() + Point[i].z()*osX.z();
		y = Point[i].x()*osY.x() + Point[i].y()*osY.y() + Point[i].z()*osY.z();
		z = Point[i].x()*normala.x() + Point[i].y()*normala.y() + Point[i].z()*normala.z();

		x = (d * x) / (d - z);
		y = (d * y) / (d - z);
		z = d;

		NEW.setX(x);
		NEW.setY(y);
		NEW.setZ(z);
		newPoint.push_back(NEW);
	}
}


void QtClass::koefPZ(int pozorovatelz, int zdrojx, int zdrojy,int zdrojz ) {
	pozorovatel.setX(200);
	pozorovatel.setY(200);
	pozorovatel.setZ(pozorovatelz);

	zdroj.setX(zdrojx);
	zdroj.setY(zdrojy);
	zdroj.setZ(zdrojz);
}

void QtClass::odrazova(double odrazivost,double odlesk ,int farba) {
	double l;
	if (farba = 0) {
		l = colorS.red();
	}
	else if (farba = 1) {
		l = colorS.green();
	}
	else {
		l = colorS.blue();
	}

	R = l*odlesk* odrazivost*(vectL.x()*vectR.x()+ vectL.y()*vectR.y()+ vectL.z()*vectR.z());

	if (R > 255)
		R = 255;
	else R = R;
}

void QtClass::difuzna(double difuzia,int farba) {
	double f,l;
	if (farba = 0) {
		f = colorT.red();
		l = colorS.red();
	}
	else if (farba = 1) {
		f = colorT.green();
		l = colorS.green();
	}
	else  {
		f = colorT.blue();
		l = colorS.blue();
	}
	

	D = l *difuzia* f*(vectN.x()*vectL.x()+ vectN.y()*vectL.y()+ vectN.z()*vectL.z());

	if (D > 255)
		D = 255;
	else D = D;
}

void QtClass::ambientna(double zlozkaFarby, double koeficientAO) {
	
	A = koeficientAO * zlozkaFarby;

	if (A > 255)
		A = 255;
	else A = A;
}

void  QtClass::POM(	double orred, double orgreen, double orblue,double dored, double dogreen, double doblue,
	double ddred, double ddgreen, double ddblue,double dared, double dagreen, double dablue,double arred, double argreen, double arblue ) {

	this->orred = orred * 255;
	this->orgreen = orgreen * 255;
	this->orblue = orblue * 255;

	this->dored = dored * 255;
	this->dogreen = dogreen * 255;
	this->doblue = doblue * 255;


	this->ddred = ddred * 255;
	this->ddgreen = ddgreen * 255;
	this->ddblue = ddblue * 255;

	this->dared = dared * 255;
	this->dagreen = dagreen * 255;
	this->dablue = dablue * 255;

	this->arred = arred * 255;
	this->argreen = argreen * 255;
	this->arblue = arblue * 255;
}

void QtClass::nastavVektory(QVector3D P) {

	vectL.setX(zdroj.x() - P.x());
	vectL.setY(zdroj.y() - P.y());
	vectL.setZ(zdroj.z() - P.z());

	vectV.setX(pozorovatel.x() - P.x());
	vectV.setY(pozorovatel.y() - P.y());
	vectV.setZ(pozorovatel.z() - P.z());

	vectL = vectL.normalized();
	vectV = vectV.normalized();
	vectR = 2 * (vectL*vectN)*vectN - vectL;
	vectR.normalized();
}

QColor QtClass::Phong(QVector3D P) {
	double r, d, a;
	QColor color;

	odrazova(dored,orred,0);
	r = R;
	difuzna(ddred,0);
	d = D;
	ambientna(arred, dared);
	a = A;

	Red = r + d + a;
	if (Red > 255)
		Red = 255;
	else Red = Red;

	color.setRed(fabs(Red));


	odrazova(dogreen, orgreen, 1);
	r = R;
	difuzna(ddgreen,1);
	d = D;
	ambientna(argreen, dagreen);
	a = A;

	Green = r + d + a;
	if (Green > 255)
		Green = 255;
	else Green = Green;

	color.setGreen(fabs(Green));

	odrazova(doblue, orblue, 2);
	r = R;
	difuzna(ddblue,2);
	d =D;
	ambientna(arblue, dablue);
	a = A;

	Blue = r + d + a;
	if (Blue > 255)
		Blue = 255;
	else Blue = Blue;

	color.setBlue(fabs(Blue));

	return color;
}



QColor QtClass::Barycentric(QVector3D A, QVector3D B, QVector3D C, QPoint P) {
	QVector3D v, w, u,k,l;
	int red, green, blue;
	double Sv,Sw,Su,obsahCely,perc1,perc2,perc3;

	k.setX(B.x() -A.x());
	k.setY(B.y() - A.y());

	l.setX(C.x() - A.x());
	l.setY(C.y() - A.y());


	obsahCely= (fabs(k.x()* l.y()-l.x()* k.y())) / 2;

	w.setX(P.x()-B.x());
	w.setY(P.y()-B.y());

	
	u.setX(P.x()-C.x());
	u.setY(P.y()-C.y());  

	Sv = (fabs(u.x()* l.y() - l.x()* u.y())) / 2;
	Sw = (fabs(k.x()* w.y() - w.x()* k.y())) / 2;
	Su = (fabs(w.x()* u.y() - u.x()* w.y())) / 2;
	 

	perc1 = Sv/ obsahCely;
	perc2 = Sw/ obsahCely;
	perc3 = Su/ obsahCely;

	red = color1.red()* perc1+ color2.red()* perc2+ color3.red()* perc3;
	green = color1.green()*perc1+ color2.green()*perc2+ color3.green()*perc3;
	blue = color1.blue()*perc1+ color2.blue()*perc2+ color3.blue()*perc3;
	
	if (red>255) {
		red = 255;
	}
	if (green>255) {
		green = 255;
	}
	if (blue>255) {
		blue = 255;
	}

	return QColor(red,green,blue);
}

QColor QtClass::NearestN(QVector3D A, QVector3D B, QVector3D C, QPoint P) {
	double d1, d2, d3;
	
	d1 = sqrt(fabs(A.x() - P.x()) *fabs(A.x() - P.x()) + fabs(A.y() - P.y()) * fabs(A.y() - P.y()));
	d2 = sqrt(fabs(B.x() - P.x()) *fabs(B.x() - P.x()) + fabs(B.y() - P.y()) * fabs(B.y() - P.y()));
	d3 = sqrt(fabs(C.x() - P.x()) *fabs(C.x() - P.x()) + fabs(C.y() - P.y()) * fabs(C.y() - P.y()));
	if (d1 > d2) {
		if (d2 > d3) {
			return color3;
		}
		return color2;
	}
	else {
		return color1;
	}
}

void QtClass::zBuffer1() {
	farby = new QColor*[469];
	hlbka = new double*[469];

	for (int i = 0; i<469; i++) {
		farby[i] = new QColor[449];
		hlbka[i] = new double[449];
	} 

	for (int i = 0; i < 469; i++) {
		for (int j = 0; j < 449; j++) {
			farby[i][j] = Qt::white;
			hlbka[i][j] = -INFINITY;
		}
	}
}

void QtClass::zBuffer(double z, QColor color, int i, int j) {

	if (z > hlbka[i][j]) {
		hlbka[i][j] = z;
		farby[i][j] = color;
	}

}

void QtClass::normalaVypocet(int i) {
	norm1.setX(newPoint[indexy_bodov[i].x()].x() - newPoint[indexy_bodov[i].y()].x());
	norm1.setY(newPoint[indexy_bodov[i].x()].y() - newPoint[indexy_bodov[i].y()].y());
	norm1.setZ(newPoint[indexy_bodov[i].x()].z() - newPoint[indexy_bodov[i].y()].z());

	norm2.setX(newPoint[indexy_bodov[i].y()].x() - newPoint[indexy_bodov[i].z()].x());
	norm2.setY(newPoint[indexy_bodov[i].y()].y() - newPoint[indexy_bodov[i].z()].y());
	norm2.setZ(newPoint[indexy_bodov[i].y()].z() - newPoint[indexy_bodov[i].z()].z());

	Normala.setX(osX.y()*osY.z() - osX.z()*osY.y());
	Normala.setY(osX.z()*osY.x() - osX.x()*osY.z());
	Normala.setZ(osX.x()*osY.y() - osX.y()*osY.x());
}

void QtClass::vymaz() {
	for (int i = 0; i<469; i++) {
		for (int j = 0; j<449; j++) {
			farby[i][j] = Qt::white;
			hlbka[i][j] = -INFINITY;
		}
	}

}