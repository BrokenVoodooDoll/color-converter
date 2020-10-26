#include "mainwindow.h"
#include "color_converter.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QRegExpValidator>
//#include <QDebug>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(setupRgb(), 0, 0);
    mainLayout->addWidget(setupHsv(), 0, 1);
    mainLayout->addWidget(setupHex(), 1, 0);
    mainLayout->addWidget(setupVba(), 1, 1);
    mainLayout->addWidget(setupColorWidget(), 2, 0, 1, 2);

    QWidget *centralWidget = new QWidget;
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
}

QGroupBox* MainWindow::setupRgb()
{
    QGroupBox *rgbBox = new QGroupBox("RGB");
    QLabel *rLabel = new QLabel("R");
    m_r = new QSpinBox;
    m_r->setRange(0, 255);

    QLabel *gLabel = new QLabel("G");
    m_g = new QSpinBox;
    m_g->setRange(0, 255);

    QLabel *bLabel = new QLabel("B");
    m_b = new QSpinBox;
    m_b->setRange(0, 255);

    connect(m_r, &QSpinBox::textChanged, this, &MainWindow::slotColorChanged);
    connect(m_g, &QSpinBox::textChanged, this, &MainWindow::slotColorChanged);
    connect(m_b, &QSpinBox::textChanged, this, &MainWindow::slotColorChanged);

    QHBoxLayout *rgbLayout = new QHBoxLayout;
    rgbLayout->addWidget(rLabel);
    rgbLayout->addWidget(m_r, 1);
    rgbLayout->addWidget(gLabel);
    rgbLayout->addWidget(m_g, 1);
    rgbLayout->addWidget(bLabel);
    rgbLayout->addWidget(m_b, 1);

    rgbBox->setLayout(rgbLayout);
    return rgbBox;
}

QGroupBox* MainWindow::setupHsv()
{
    QGroupBox *hsvBox = new QGroupBox("HSV");
    QLabel *hLabel = new QLabel("H");
    m_h = new QSpinBox;
    m_h->setRange(-1, 359);

    QLabel *sLabel = new QLabel("S");
    m_s = new QSpinBox;
    m_s->setRange(0, 100);

    QLabel *vLabel = new QLabel("V");
    m_v = new QSpinBox;
    m_v->setRange(0, 100);

    connect(m_h, &QSpinBox::textChanged, this, &MainWindow::slotColorChanged);
    connect(m_s, &QSpinBox::textChanged, this, &MainWindow::slotColorChanged);
    connect(m_v, &QSpinBox::textChanged, this, &MainWindow::slotColorChanged);

    QHBoxLayout *hsvLayout = new QHBoxLayout;
    hsvLayout->addWidget(hLabel);
    hsvLayout->addWidget(m_h, 1);
    hsvLayout->addWidget(sLabel);
    hsvLayout->addWidget(m_s, 1);
    hsvLayout->addWidget(vLabel);
    hsvLayout->addWidget(m_v, 1);

    hsvBox->setLayout(hsvLayout);
    return hsvBox;
}

QGroupBox* MainWindow::setupHex()
{
    QGroupBox *hexBox = new QGroupBox("HEX");
    QRegExp regExp("#[0-9A-F]{6}", Qt::CaseInsensitive);
    QRegExpValidator *validator = new QRegExpValidator(regExp);
    m_hex = new QLineEdit;
    m_hex->setText("#000000");
    m_hex->setValidator(validator);

    connect(m_hex, &QLineEdit::textEdited, this, &MainWindow::slotColorChanged);

    QHBoxLayout *hsvLayout = new QHBoxLayout;
    hsvLayout->addWidget(m_hex, 1);

    hexBox->setLayout(hsvLayout);
    return hexBox;
}

QGroupBox *MainWindow::setupVba()
{
    QGroupBox *vbaBox = new QGroupBox("VBA");
    m_vba = new QSpinBox;
    m_vba->setRange(0, 16777215); /*255 * (1 + 256 + 256 ^ 2)*/

    connect(m_vba, &QSpinBox::textChanged, this, &MainWindow::slotColorChanged);

    QHBoxLayout *vbaLayout = new QHBoxLayout;
    vbaLayout->addWidget(m_vba, 1);

    vbaBox->setLayout(vbaLayout);
    return vbaBox;
}

QGroupBox *MainWindow::setupColorWidget()
{
    QGroupBox *colorBox = new QGroupBox("Color");
    m_colorWidget = new ColorWidget;
    connect(this, &MainWindow::colorChanged, m_colorWidget, &ColorWidget::colorChanged);

    QHBoxLayout *colorLayout = new QHBoxLayout;
    colorLayout->addWidget(m_colorWidget);
    colorBox->setLayout(colorLayout);
    return colorBox;
}

void MainWindow::blockAllSignals(bool b)
{
    m_r->blockSignals(b);
    m_g->blockSignals(b);
    m_b->blockSignals(b);
    m_h->blockSignals(b);
    m_s->blockSignals(b);
    m_v->blockSignals(b);
    m_hex->blockSignals(b);
    m_vba->blockSignals(b);
}

MainWindow::~MainWindow()
{}

void MainWindow::slotColorChanged(const QString& /*value*/)
{
    blockAllSignals(true);

    QColor color;
    if (sender() == m_r
            || sender() == m_g
            || sender() == m_b) {
        color = QColor(m_r->value(), m_g->value(), m_b->value());
    }
    if (sender() == m_h
            || sender() == m_s
            || sender() == m_v) {
        color = QColor::fromHsv(m_h->value(), m_s->value() * 255. / 100., m_v->value() * 255. / 100.);
    }
    if (sender() == m_hex)
        color = QColor(m_hex->text());
    if (sender() == m_vba) {
        int value = m_vba->value();
        int red = value % 256;
        int green = (value / 256) % 256;
        int blue = (value / 256 / 256) % 256;
        color = QColor(red, green, blue);
    }


    if (!(sender() == m_r
            || sender() == m_g
            || sender() == m_b)) {
        m_r->setValue(color.red());
        m_g->setValue(color.green());
        m_b->setValue(color.blue());
    }

    if (!(sender() == m_h
            || sender() == m_s
            || sender() == m_v)) {
        m_h->setValue(color.hsvHue());
        m_s->setValue(color.hsvSaturationF() * 100);
        m_v->setValue(color.valueF() * 100);
    }

    if (sender() != m_hex)
        m_hex->setText(color.name());

    if (sender() != m_vba) {
        int value = color.red() + color.green() * 0x100 + color.blue() * 0x10000;
        m_vba->setValue(value);
    }

    blockAllSignals(false);
    emit colorChanged(color);
}

void ColorWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setPen(QPen(QBrush(Qt::transparent), 0));
    painter.setBrush(m_color);
    painter.drawRect(rect());
}

ColorWidget::ColorWidget(QWidget *parent)
    : QWidget(parent)
    , m_color(0, 0, 0)
{
    setAutoFillBackground(true);
    setMinimumHeight(50);
}

void ColorWidget::colorChanged(const QColor &color)
{
    m_color = color;
    repaint();
}
