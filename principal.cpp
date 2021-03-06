#include "principal.h"
#include "ui_principal.h"

Principal::Principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Principal)
{
    ui->setupUi(this);
    lienzo = QPixmap(500,500);
    this->dibujar();

}

Principal::~Principal()
{
    delete ui;
}
 // Llamamos al evento
void Principal::paintEvent(QPaintEvent *event)
{
    ui->outCuadro->setPixmap(lienzo);
    event;
}


void Principal::dibujar()
{
    lienzo.fill(Qt::white);

    QPainter painter(&lienzo);
/* Inicializamos los valores de nuestro lienzo
 * El cual nos permitira sobre el*/

    int x = 0;
    int y = 0;

    /* Creamos un pincel para graficar los bordes del diagrama*/

    QPen pincel;
    pincel.setWidth(1);
    pincel.setColor(Qt::black);
    pincel.setJoinStyle(Qt::MiterJoin);

    QColor colorRelleno(100,100,100);

    // Seleccionamos el color que quremos de relleno
    painter.setBrush(colorRelleno);

    // Establecer el pincel al "pintor"
    painter.setPen(pincel);

    //Extraemos los datos para graficar la primera barra
    int nota1 = ui->inNota1->value();
    int altoN1 = this->getAlto(nota1);
    int incYN1 = this->incY(altoN1);

    //Extraemos los datos para graficar la segunda barra
    int nota2 = ui->inNota2->value();
    int altoN2 = this->getAlto(nota2);
    int incYN2 = this->incY(altoN2);

    //Extraemos los datos para graficar la tercer barra
    int nota3 = ui->inNota3->value();
    int altoN3 = this->getAlto(nota3);
    int incYN3 = this->incY(altoN3);

    /*Para dobujar la primera barra llamamos a nuesrto painter
     * Luego ejecutamos el .drawRect y, con los valores extraidos se establecen los parametros*/
    painter.drawRect(80, y+50+incYN1,100,altoN1-1);

    // Establecer el color de rellno
    QColor colorRelleno1(100,200,100);
    // Establecer el color del borde
    QColor colorBorde(78,3,48);

    // Cambiar el color del pincel
    pincel.setColor(colorBorde);

    // Volver a establecer el pincel al "pintor"
    painter.setPen(pincel);

    // Establecer el color de rellno
    painter.setBrush(colorRelleno1);

    /*Para dobujar la segunda barra llamamos a nuesrto painter
     * Luego ejecutamos el .drawRect y, con los valores extraidos se establecen los parametros*/
    painter.drawRect(200, y+50+incYN2, 100, altoN2-1);

    // Establecemos los colores de la tercera barra (relleno y bordes)
    QColor cRellenoBarra3(255, 100, 100);
    QColor cBordeBarra3(100, 200, 200);

    // Estableciendo colores al puncel y al painter
    pincel.setColor(cBordeBarra3);
    painter.setPen(pincel);
    painter.setBrush(cRellenoBarra3);

    // Dibujar tercera barra
    painter.drawRect(320,y+50+incYN3,100,altoN3-1);

    // Con este codigo nosotros podemos escribir un texto en pantalla
    // En este caso esto va a acentuar que se trata de un diagrama de barras
    painter.setPen(Qt::red);
    painter.setFont(QFont("Arial",12));
    painter.drawText(200,25,"Diagrama de Barras (Promedios)");

    // Promedio
    QColor line(106,38,111);
    pincel.setColor(line);
    pincel.setWidth(4);
    painter.setPen(pincel);

    float promedio = (nota1 + nota2 + nota3) / 3;
    int prom = this->getAlto(promedio);

    painter.drawLine(x+50,y+450-prom,443,y+450-prom);

    QColor eje(0,0,0);
    pincel.setColor(eje);
    pincel.setWidth(3);
    painter.setPen(pincel);
    painter.drawLine(50,480,50,30); //y
    painter.drawLine(10,450,455,450); //x

    painter.setPen(Qt::red);
    painter.setFont(QFont("Arial",15));
    painter.drawText(460,455,"x");
    painter.drawText(45,25,"y");

    // Divisiones barras

    painter.drawText(120,472,"N1");
    painter.drawText(240,472,"N2");
    painter.drawText(360,472,"N3");

    // Divisiones numeros

    painter.setFont(QFont("Calibri",10));


    painter.drawText(28,432,"5 -------------------");
    painter.drawText(28,412,"10 ----------------");
    painter.drawText(28,392,"15 ----------------");
    painter.drawText(28,372,"20 ----------------");
    painter.drawText(28,352,"25 ----------------");
    painter.drawText(28,252,"50 ----------------");
    painter.drawText(28,152,"75 ----------------");
    painter.drawText(28,57,"99 ----------------");

}
int Principal::getAlto(int valor)
{
    return 4 * valor;
}

int Principal::incY(int alto)
{
    return 400 - alto;
}


void Principal::on_actionGuardar_triggered()
{
    QString nombreArchivo = QFileDialog::getSaveFileName(
                this,"Guardar imagen",QString(),"Imagenes (*.png)");
    if (!nombreArchivo.isEmpty()){
        if (lienzo.save(nombreArchivo))
            QMessageBox::information(this,"Guardar imagen","Archivo guarado en: " + nombreArchivo);
        else
            QMessageBox::warning(this,"Guardar imagen","No se pudo guardar el archivo");
    }
}

void Principal::on_inNota1_valueChanged(int arg1)
{
    dibujar();
}

void Principal::on_inNota2_valueChanged(int arg1)
{
    dibujar();
}

void Principal::on_inNota3_valueChanged(int arg1)
{
    dibujar();
}
