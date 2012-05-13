#include <MLinearLayoutPolicy>
#include <QGraphicsLinearLayout>
#include <MButton>
#include <MLayout>
#include <MToolBar>
#include <MAction>
#include <MTextEdit>
#include <MSceneWindow>
#include <QDebug>
#include <MApplication>
#include <MOnDisplayChangeEvent>
#include <MApplicationWindow>
#include <MTheme>
#include <QGraphicsGridLayout>
#include <MGridLayoutPolicy>
#include <MImageWidget>
#include <MPannableViewport>
#include <MSeparator>
#include <QGraphicsItem>
#include <math.h>

#include "mainpage.h"

MainPage::MainPage(QGraphicsItem *parent)
    : MApplicationPage(parent)
{

}

void MainPage::createContent()
{
    applicationWindow()->setStyleName("CommonApplicationWindowInverted");
    setStyleName("CommonApplicationPageInverted");
    MLayout *layout = new MLayout(this);
    MTheme *theme = MTheme::instance();
    QLocale locales;
    theme->loadCSS("/opt/calc-mtf/style/calc-mtf.css");

    MLinearLayoutPolicy *portraitPolicy = new MLinearLayoutPolicy(layout, Qt::Vertical);
    MLinearLayoutPolicy *landscapePolicy = new MLinearLayoutPolicy(layout, Qt::Vertical);
    layout->setPortraitPolicy(portraitPolicy);
    layout->setLandscapePolicy(landscapePolicy);

    /* Fix: lock page content */
    setPannable(false);
    MPannableViewport *viewport = this->pannableViewport();
    viewport->setAutoRange(false);
    viewport->setRange(QRectF(0,0,0,0));

    //////////////////////////////// CREATE BUTTONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

    opButtons[0] = new MButton("C");
    opButtons[0]->setObjectName("calc_mtf_buttonClear");
    opButtons[1] = new MButton("\367");
    opButtons[1]->setObjectName("calc_mtf_buttonO");
    opButtons[2] = new MButton("\327");
    opButtons[2]->setObjectName("calc_mtf_buttonO");
    opButtons[3] = new MButton("\261");
    opButtons[3]->setObjectName("calc_mtf_buttonSign");
    opButtons[4] = new MButton("-");
    opButtons[4]->setObjectName("calc_mtf_buttonSub");
    opButtons[5] = new MButton("+");
    opButtons[5]->setObjectName("calc_mtf_buttonO");
    opButtons[6] = new MButton(locales.decimalPoint());
    opButtons[6]->setObjectName("calc_mtf_buttonDot");

    /* Clear button */
    connect(opButtons[0], SIGNAL(clicked()), this, SLOT(clearAll()));
    /* Div button */
    connect(opButtons[1], SIGNAL(clicked()), this, SLOT(setSelectedButton0()));
    connect(opButtons[1], SIGNAL(clicked()), this, SLOT(multiplicativeOperatorClicked()));
    /* Mutli button */
    connect(opButtons[2], SIGNAL(clicked()), this, SLOT(setSelectedButton0()));
    connect(opButtons[2], SIGNAL(clicked()), this, SLOT(multiplicativeOperatorClicked()));
    /* Add button */
    connect(opButtons[5], SIGNAL(clicked()), this, SLOT(setSelectedButton0()));
    connect(opButtons[5], SIGNAL(clicked()), this, SLOT(additiveOperatorClicked()));
    /* Sub button */
    connect(opButtons[4], SIGNAL(clicked()), this, SLOT(setSelectedButton0()));
    connect(opButtons[4], SIGNAL(clicked()), this, SLOT(additiveOperatorClicked()));
    /* Sign button */
    connect(opButtons[3], SIGNAL(clicked()), this, SLOT(changeSignClicked()));
    /* Point button */
    connect(opButtons[6], SIGNAL(clicked()), this, SLOT(pointClicked()));

    /* Num buttons */
    MButton *numButton0 = new MButton("0");
    numButton0->setObjectName("calc_mtf_buttonNum");
    MButton *numButton1 = new MButton("1");
    numButton1->setObjectName("calc_mtf_buttonNum");
    MButton *numButton2 = new MButton("2");
    numButton2->setObjectName("calc_mtf_buttonNum");
    MButton *numButton3 = new MButton("3");
    numButton3->setObjectName("calc_mtf_buttonNum");
    MButton *numButton4 = new MButton("4");
    numButton4->setObjectName("calc_mtf_buttonNum");
    MButton *numButton5 = new MButton("5");
    numButton5->setObjectName("calc_mtf_buttonNum");
    MButton *numButton6 = new MButton("6");
    numButton6->setObjectName("calc_mtf_buttonNum");
    MButton *numButton7 = new MButton("7");
    numButton7->setObjectName("calc_mtf_buttonNum");
    MButton *numButton8 = new MButton("8");
    numButton8->setObjectName("calc_mtf_buttonNum");
    MButton *numButton9 = new MButton("9");
    numButton9->setObjectName("calc_mtf_buttonNum");
    MButton *numButtonEqual = new MButton("=");
    numButtonEqual->setObjectName("calc_mtf_buttonEqual");

    connect(numButton0, SIGNAL(clicked()), this, SLOT(digitClicked()));
    connect(numButton1, SIGNAL(clicked()), this, SLOT(digitClicked()));
    connect(numButton2, SIGNAL(clicked()), this, SLOT(digitClicked()));
    connect(numButton3, SIGNAL(clicked()), this, SLOT(digitClicked()));
    connect(numButton4, SIGNAL(clicked()), this, SLOT(digitClicked()));
    connect(numButton5, SIGNAL(clicked()), this, SLOT(digitClicked()));
    connect(numButton6, SIGNAL(clicked()), this, SLOT(digitClicked()));
    connect(numButton7, SIGNAL(clicked()), this, SLOT(digitClicked()));
    connect(numButton8, SIGNAL(clicked()), this, SLOT(digitClicked()));
    connect(numButton9, SIGNAL(clicked()), this, SLOT(digitClicked()));
    connect(numButtonEqual, SIGNAL(clicked()), this, SLOT(equalClicked()));

//////////////////////////////// ADDITIONAL LANDSCAPE BUTTONS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

    /* MC M+ M- MR buttons */
    MButton *mcButton = new MButton("MC");
    mcButton->setObjectName("calc_mtf_buttonMem");
    MButton *maButton = new MButton("M+");
    maButton->setObjectName("calc_mtf_buttonMem");
    MButton *msButton = new MButton("M-");
    msButton->setObjectName("calc_mtf_buttonMem");
    MButton *mrButton = new MButton("MR");
    mrButton->setObjectName("calc_mtf_buttonMem");

    connect(mcButton, SIGNAL(clicked()), this, SLOT(clearMemory()));
    connect(maButton, SIGNAL(clicked()), this, SLOT(addToMemory()));
    connect(msButton, SIGNAL(clicked()), this, SLOT(subFromMemory()));
    connect(mrButton, SIGNAL(clicked()), this, SLOT(readMemory()));

    /* Other landscape buttons */
    MButton *invButton = new MButton("1/x");
    invButton->setObjectName("calc_mtf_buttonMem");
    MButton *rtButton = new MButton("x\262");
    rtButton->setObjectName("calc_mtf_buttonMem");
    MButton *sqrtButton = new MButton(QChar(0x221A));
    sqrtButton->setObjectName("calc_mtf_buttonMem");
    MButton *piButton = new MButton(QChar(0x03C0));
    piButton->setObjectName("calc_mtf_buttonMem");
    MButton *factorialButton = new MButton("?");
    factorialButton->setObjectName("calc_mtf_buttonEqual");
    MButton *randButton = new MButton("Rand");
    randButton->setObjectName("calc_mtf_buttonRand");

    connect(invButton, SIGNAL(clicked()), this, SLOT(unaryOperatorClicked()));
    connect(rtButton, SIGNAL(clicked()), this, SLOT(unaryOperatorClicked()));
    connect(sqrtButton, SIGNAL(clicked()), this, SLOT(unaryOperatorClicked()));
    connect(piButton, SIGNAL(clicked()), this, SLOT(getPi()));
    connect(factorialButton, SIGNAL(clicked()), this, SLOT(showAboutDialog()));
    connect(randButton, SIGNAL(clicked()), this, SLOT(getRandom()));

//////////////////////////////// DISPLAY LAYOUT \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

    display = new MLabel("0");
    display->setAlignment(Qt::AlignRight);
    /* Set display layout. */
    display->setObjectName("calc_mtf_displayLabel1");
    displayStyleNumber = 1;

    MButton *buttonClearDisplay = new MButton("");
    buttonClearDisplay->setObjectName("calc_mtf_backspace");
    connect(buttonClearDisplay, SIGNAL(clicked()), this, SLOT(backspaceClicked()));

    MSeparator *separator = new MSeparator();
    separator->setObjectName("calc_mtf_displaySeparator");

    QGraphicsLinearLayout *displayLayout = new QGraphicsLinearLayout(Qt::Horizontal);
    QGraphicsLinearLayout *displayLayoutSeparator = new QGraphicsLinearLayout(Qt::Vertical);

    displayLayout->addItem(display);
    displayLayout->addItem(buttonClearDisplay);
    displayLayoutSeparator->addItem(displayLayout);
    displayLayoutSeparator->addItem(separator);

//////////////////////////////// Op BUTTONS LAYOUT \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

    MLayout *opLayoutMain = new MLayout;
    MGridLayoutPolicy *opLayout = new MGridLayoutPolicy(opLayoutMain);
    MGridLayoutPolicy *opLayoutLandscape = new MGridLayoutPolicy(opLayoutMain);
    opLayoutMain->setPortraitPolicy(opLayout);
    opLayoutMain->setLandscapePolicy(opLayoutLandscape);
    opLayout->setContentsMargins(0, 0, 0, 0);
    opLayoutLandscape->setContentsMargins(0, 0, 0, 0);

    opLayoutLandscape->addItem(opButtons[0], 0, 0);
    opLayoutLandscape->addItem(opButtons[1], 0, 1);
    opLayoutLandscape->addItem(opButtons[2], 0, 2);
    opLayoutLandscape->addItem(opButtons[3], 1, 0);
    opLayoutLandscape->addItem(opButtons[4], 1, 1);
    opLayoutLandscape->addItem(opButtons[5], 1, 2);
    opLayoutLandscape->addItem(mcButton, 0, 3);
    opLayoutLandscape->addItem(maButton, 1, 3);
    opLayoutLandscape->addItem(msButton, 2, 3);
    opLayoutLandscape->addItem(mrButton, 3, 3);
    opLayoutLandscape->addItem(invButton, 2, 0);
    opLayoutLandscape->addItem(rtButton, 2, 1);
    opLayoutLandscape->addItem(sqrtButton, 2, 2);
    opLayoutLandscape->addItem(factorialButton, 3, 0);
    opLayoutLandscape->addItem(randButton, 3, 1);
    opLayoutLandscape->addItem(piButton, 3, 2);
    opLayoutLandscape->setColumnSpacing(0, 0);
    opLayoutLandscape->setColumnSpacing(1, 0);
    opLayoutLandscape->setColumnSpacing(2, 0);
    opLayoutLandscape->setColumnSpacing(3, 0);
    opLayoutLandscape->setRowFixedHeight(0, 90);
    opLayoutLandscape->setRowFixedHeight(1, 90);
    opLayoutLandscape->setRowFixedHeight(2, 90);
    opLayoutLandscape->setRowFixedHeight(3, 90);
    opLayoutLandscape->setRowSpacing(0, 0);
    opLayoutLandscape->setRowSpacing(1, 0);
    opLayoutLandscape->setRowSpacing(2, 0);
    opLayoutLandscape->setRowSpacing(3, 0);
    opLayoutLandscape->setVerticalSpacing(0);

    opLayout->addItem(opButtons[0], 0, 0);
    opLayout->addItem(opButtons[1], 0, 1);
    opLayout->addItem(opButtons[2], 0, 2);
    opLayout->addItem(opButtons[3], 1, 0);
    opLayout->addItem(opButtons[4], 1, 1);
    opLayout->addItem(opButtons[5], 1, 2);
    opLayout->setColumnSpacing(0, 30);
    opLayout->setColumnSpacing(1, 30);
    opLayout->setColumnSpacing(2, 30);
    opLayout->setRowFixedHeight(0, 90);
    opLayout->setRowFixedHeight(1, 90);
    opLayout->setRowSpacing(0, 0);
    opLayout->setRowSpacing(1, 0);
    opLayout->setVerticalSpacing(0);
    /* Spacing between opLayout and numLayout */
    opLayout->setRowFixedHeight(2, 30);

//////////////////////////////// DIGIT BUTTONS LAYOUT \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

    MLayout *numLayoutMain = new MLayout;
    MGridLayoutPolicy *numLayoutLandscape = new MGridLayoutPolicy(numLayoutMain);
    MGridLayoutPolicy *numLayout = new MGridLayoutPolicy(numLayoutMain);
    numLayoutMain->setPortraitPolicy(numLayout);
    numLayoutMain->setLandscapePolicy(numLayoutLandscape);
    numLayout->setContentsMargins(0, 0, 0, 0);
    numLayoutLandscape->setContentsMargins(50, 0, 0, 0);

    numLayoutLandscape->addItem(numButton7, 0, 0);
    numLayoutLandscape->addItem(numButton8, 0, 1);
    numLayoutLandscape->addItem(numButton9, 0, 2);
    numLayoutLandscape->addItem(numButton4, 1, 0);
    numLayoutLandscape->addItem(numButton5, 1, 1);
    numLayoutLandscape->addItem(numButton6, 1, 2);
    numLayoutLandscape->addItem(numButton1, 2, 0);
    numLayoutLandscape->addItem(numButton2, 2, 1);
    numLayoutLandscape->addItem(numButton3, 2, 2);
    numLayoutLandscape->addItem(numButton0, 3, 0);
    numLayoutLandscape->addItem(opButtons[6], 3, 1);
    numLayoutLandscape->addItem(numButtonEqual, 3, 2);
    numLayoutLandscape->setColumnSpacing(0, 0);
    numLayoutLandscape->setColumnSpacing(1, 0);
    numLayoutLandscape->setColumnSpacing(2, 0);
    numLayoutLandscape->setColumnSpacing(3, 0);
    numLayoutLandscape->setRowSpacing(0, 0);
    numLayoutLandscape->setRowSpacing(1, 0);
    numLayoutLandscape->setRowSpacing(2, 0);
    numLayoutLandscape->setRowSpacing(3, 0);

    numLayout->addItem(numButton7, 0, 0);
    numLayout->addItem(numButton8, 0, 1);
    numLayout->addItem(numButton9, 0, 2);
    numLayout->addItem(numButton4, 1, 0);
    numLayout->addItem(numButton5, 1, 1);
    numLayout->addItem(numButton6, 1, 2);
    numLayout->addItem(numButton1, 2, 0);
    numLayout->addItem(numButton2, 2, 1);
    numLayout->addItem(numButton3, 2, 2);
    numLayout->addItem(numButton0, 3, 0);
    numLayout->addItem(opButtons[6], 3, 1);
    numLayout->addItem(numButtonEqual, 3, 2);
    numLayout->setColumnSpacing(0, 30);
    numLayout->setColumnSpacing(1, 30);
    numLayout->setColumnSpacing(2, 30);
    numLayout->setRowSpacing(0, 0);
    numLayout->setRowSpacing(1, 0);
    numLayout->setRowSpacing(2, 0);
    numLayout->setRowSpacing(3, 0);

    //////////////////////////////// SEPARATE LAYOUTS FOR PORTRAIT AND LANDSCAPE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

    portraitPolicy->addItem(displayLayoutSeparator);
    portraitPolicy->addItem(opLayoutMain);
    portraitPolicy->addItem(numLayoutMain);
    portraitPolicy->setObjectName("calc_mtf_layout");

    MLayout *horizontalLayout = new MLayout;
    MLinearLayoutPolicy *horizontalLayoutPolicy = new MLinearLayoutPolicy(horizontalLayout, Qt::Horizontal);
    horizontalLayout->setPolicy(horizontalLayoutPolicy);
    horizontalLayoutPolicy->setContentsMargins(0, 0, 0, 0);
    horizontalLayoutPolicy->addItem(opLayoutMain);
    horizontalLayoutPolicy->addItem(numLayoutMain);

    landscapePolicy->setObjectName("calc_mtf_layout");
    landscapePolicy->addItem(displayLayoutSeparator);
    // use horizontalLayout
    landscapePolicy->addItem(horizontalLayout);

    centralWidget()->setLayout(layout);

    waitWithCalculating = true;

    /* Create info banner. */
    infoBanner = new MBanner();
    setDisplayText("0");

    /* Set calc variables. */
    sumInMemory = 0;

    connect(this->applicationWindow(), SIGNAL(orientationChanged(M::Orientation)), this, SLOT(orientationChanged()));
}

void MainPage::keyPressEvent(QKeyEvent *event)
{
    qDebug()  << "KBD";
    switch (event->key()) {
    case Qt::Key_0:
        //numButton0->click();
        break;
    }
}

void MainPage::orientationChanged()
{
    setDisplayText(getDisplayText());
}

void MainPage::setSelectedButton0()
{
    MButton *clickedButton = qobject_cast<MButton *>(sender());
    qDebug() << "text: " << clickedButton->text();
    if (clickedButton->text().compare("\367") == 0) {
        opButtons[1]->setObjectName("calc_mtf_buttonOPressed");
        opButtons[2]->setObjectName("calc_mtf_buttonO");
        opButtons[4]->setObjectName("calc_mtf_buttonSub");
        opButtons[5]->setObjectName("calc_mtf_buttonO");
        opButtons[3]->setEnabled(false);
    }
    else if (clickedButton->text().compare("\327") == 0) {
        opButtons[1]->setObjectName("calc_mtf_buttonO");
        opButtons[2]->setObjectName("calc_mtf_buttonOPressed");
        opButtons[4]->setObjectName("calc_mtf_buttonSub");
        opButtons[5]->setObjectName("calc_mtf_buttonO");
        opButtons[3]->setEnabled(false);
    }
    else if (clickedButton->text().compare("-") == 0) {
        opButtons[1]->setObjectName("calc_mtf_buttonO");
        opButtons[2]->setObjectName("calc_mtf_buttonO");
        opButtons[4]->setObjectName("calc_mtf_buttonSubPressed");
        opButtons[5]->setObjectName("calc_mtf_buttonO");
        opButtons[3]->setEnabled(false);
    }
    else if (clickedButton->text().compare("+") == 0){
        opButtons[1]->setObjectName("calc_mtf_buttonO");
        opButtons[2]->setObjectName("calc_mtf_buttonO");
        opButtons[4]->setObjectName("calc_mtf_buttonSub");
        opButtons[5]->setObjectName("calc_mtf_buttonOPressed");
        opButtons[3]->setEnabled(false);
    }
    else {
        opButtons[1]->setObjectName("calc_mtf_buttonO");
        opButtons[2]->setObjectName("calc_mtf_buttonO");
        opButtons[4]->setObjectName("calc_mtf_buttonSub");
        opButtons[5]->setObjectName("calc_mtf_buttonO");
        opButtons[3]->setEnabled(true);
    }
}

QString MainPage::parseString(double value)
{
    QString text;
    QString tempText = QString::number(value, 'g', 12);
    int length = tempText.length();
    qDebug() << "length:" << length;

    if (tempText.contains("e")) {
        // Count (e+xx) as one sign.
        tempText.indexOf("e");
        qDebug() << "normal length" << tempText.length();
        qDebug() << "e pos" << tempText.indexOf("e");
        qDebug() << "length e" << tempText.length() - 1;
        qDebug() << "delta e" << tempText.length() - tempText.indexOf("e");
        qDebug() << "tempValue" << tempText;
        // precision = 12 - e+xx
        int precision = 12 - (tempText.length() - tempText.indexOf("e"));
        if (precision < 1)
            precision = 1;
        text = QString::number(value, 'g', precision);
        qDebug() << "New text" << text;
    }
    return text;
}

void MainPage::setDisplayText(QString text)
{
    if (text.isNull() || text.isEmpty())
        return;

    QLocale locales;
    int length;
    QString valueTempLength;
    int boundValue = 270; // Default for portrait mode

    QStringList subtext = text.split(".");
    text = insertEmptyFields(subtext[0]);

    if (subtext.length() == 2) {
        /* Float point */
        text.append(".");
        text.append(subtext[1]);
    }

    /* Show approperiate character based on locales. */
    text.replace(".", locales.decimalPoint());

    QString tempText = text;
    tempText.replace(" ", "");
    length = tempText.length();
    qDebug() << "length:" << length;

    /* Set bound value. */
    if (this->geometry().width() > this->geometry().height())
        boundValue = 737; // According to stylesheet

    if (text.contains(locales.decimalPoint())) {
        bool fontSizeReady = false;

        while(!fontSizeReady) {
            QFont myFont = display->font();
            QFontMetrics fm( myFont );
            /* 270 = max text width             */
            /* 120 = max text height (not used) */
            QRect bound = fm.boundingRect(0,0, boundValue, 120, Qt::AlignRight | Qt::AlignVCenter, text);

            qDebug() << "bound width:" << bound.width();
            qDebug() << "is bound.width > 270:" << (bound.width() > boundValue);

            if (bound.width() > boundValue) {
                if (displayStyleNumber + 1 > 7)
                    break;
                setDisplayStyle(displayStyleNumber + 1);
            }
            else
                fontSizeReady = true;
            qDebug() << "font size" << "displayStyleNumber + 1";
            qDebug() << "text: " << text;
        }
    }
    else {
        if (length < 4) {
            display->setObjectName("calc_mtf_displayLabel1");
            displayStyleNumber = 1;
        }
        else if (length == 4) {
            display->setObjectName("calc_mtf_displayLabel2");
            displayStyleNumber = 2;
        }
        else if (length > 4 && length < 7) {
            display->setObjectName("calc_mtf_displayLabel3");
            displayStyleNumber = 3;
        }
        else if (length == 7) {
            display->setObjectName("calc_mtf_displayLabel4");
            displayStyleNumber = 4;
        }
        else if (length > 7 && length < 10) {
            display->setObjectName("calc_mtf_displayLabel5");
            displayStyleNumber = 5;
        }
        else if (length == 10) {
            display->setObjectName("calc_mtf_displayLabel6");
            displayStyleNumber = 6;
        }
        else { //(length > 10 && length < 13)
            display->setObjectName("calc_mtf_displayLabel7");
            displayStyleNumber = 7;
        }
    }

    display->setText(text);
    display->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
}

void MainPage::setDisplayStyle(int number)
{
    switch (number) {
    case 1:
        display->setObjectName("calc_mtf_displayLabel1");
        break;
    case 2:
        display->setObjectName("calc_mtf_displayLabel2");
        break;
    case 3:
        display->setObjectName("calc_mtf_displayLabel3");
        break;
    case 4:
        display->setObjectName("calc_mtf_displayLabel4");
        break;
    case 5:
        display->setObjectName("calc_mtf_displayLabel5");
        break;
    case 6:
        display->setObjectName("calc_mtf_displayLabel6");
        break;
    case 7:
        display->setObjectName("calc_mtf_displayLabel7");
        break;
    default:
        display->setObjectName("calc_mtf_displayLabel7");
    }

    displayStyleNumber = number;

    if (displayStyleNumber > 7)
        displayStyleNumber = 7;
    else if (displayStyleNumber < 1)
        displayStyleNumber = 1;
}

QString MainPage::insertEmptyFields(QString text)
{
    int additionalField = 0;
    int length = text.length();

  //  qDebug() << "Received:" << text;

    if (QString("-").compare(text.at(0)) == 0)
        additionalField = 1;

    int spaces = ((length - additionalField) / 3);
    if ((length - additionalField) % 3 == 0)
        spaces--;

  //  qDebug() << "Spaces:" << spaces;

    for (int i = 1; i <= spaces; i++) {
        int pos = length - (3 * i);
  //      qDebug() << "Pos:" << pos << "at i:" << i;
        text.insert(pos, " ");
    }

    return text;
}

QString MainPage::getDisplayText()
{
    return display->text().replace(" ", "").replace(",", ".");
}

void MainPage::digitClicked()
{
    MButton *clickedButton = qobject_cast<MButton *>(sender());
    int digitValue = clickedButton->text().toInt();
    QString text = getDisplayText();
    int maxLength = 12;
    waitWithCalculating = false;
    setSelectedButton0();

    if (getDisplayText() == "0" && digitValue == 0.0)
        return;

    if (text.length() == 12 && text.at(0) == '-')
        maxLength = 13;

    if ((getDisplayText().replace(".", "").length() >= maxLength) && !waitingForOperand) {
        throwError("Too many digits");
        return;
    }

    if (waitingForOperand) {
        setDisplayText("0");
        waitingForOperand = false;
    }

    if (getDisplayText().compare("0") == 0)
        //setDisplayText(QString::number(digitValue));
        setDisplayText(QString::number(digitValue));
    else
        setDisplayText(getDisplayText() + QString::number(digitValue));
}

void MainPage::unaryOperatorClicked()
{
    MButton *clickedButton = qobject_cast<MButton *>(sender());
    QString clickedOperator = clickedButton->text();
    double operand = getDisplayText().toDouble();
    double result = 0.0;

    if (clickedOperator == QChar(0x221A)) {
        if (operand < 0.0) {
            abortOperation();
            return;
        }
        result = sqrt(operand);
    } else if (clickedOperator == tr("x\262")) {
        result = pow(operand, 2.0);
    } else if (clickedOperator == tr("1/x")) {
        if (operand == 0.0) {
            abortOperation();
            return;
        }
        result = 1.0 / operand;
    }
    setDisplayText(QString::number(result, 'g', 12));
    waitingForOperand = true;
    clickedButton->setSelected(true);
}

void MainPage::additiveOperatorClicked()
{
    MButton *clickedButton = qobject_cast<MButton *>(sender());
    setSelectedButton0();
    QString clickedOperator = clickedButton->text();
    double operand = getDisplayText().toDouble();

    if (!pendingMultiplicativeOperator.isEmpty() && !waitWithCalculating) {
        if (!calculate(operand, pendingMultiplicativeOperator)) {
            abortOperation();
            return;
        }
        setDisplayText(QString::number(factorSoFar, 'g', 12));
        operand = factorSoFar;
        factorSoFar = 0.0;
        pendingMultiplicativeOperator.clear();
    }

    if (!pendingAdditiveOperator.isEmpty() && !waitWithCalculating) {
        if (!calculate(operand, pendingAdditiveOperator)) {
            abortOperation();
            return;
        }
        setDisplayText(QString::number(sumSoFar, 'g', 12));
    } else {
        sumSoFar = operand;
    }

    pendingAdditiveOperator = clickedOperator;
    pendingMultiplicativeOperator.clear();
    waitingForOperand = true;
    waitWithCalculating = true;
}

void MainPage::multiplicativeOperatorClicked()
{
    MButton *clickedButton = qobject_cast<MButton *>(sender());
    setSelectedButton0();
    QString clickedOperator = clickedButton->text();
    double operand = getDisplayText().toDouble();

    if (!pendingAdditiveOperator.isEmpty() && !waitWithCalculating) {
        if (!calculate(operand, pendingAdditiveOperator)) {
            abortOperation();
            return;
        }

        //setDisplayText(QString::number(sumSoFar, 'g', 12));
        setDisplayText(parseString(sumSoFar));

        operand = sumSoFar;
        sumSoFar = 0.0;
        pendingAdditiveOperator.clear();
    }

    if (!pendingMultiplicativeOperator.isEmpty() && !waitWithCalculating) {
        if (!calculate(operand, pendingMultiplicativeOperator)) {
            abortOperation();
            return;
        }
        //setDisplayText(QString::number(factorSoFar, 'g', 12));
        setDisplayText(parseString(factorSoFar));
    } else {
        factorSoFar = operand;
    }

    pendingMultiplicativeOperator = clickedOperator;
    pendingAdditiveOperator.clear();
    waitingForOperand = true;
    waitWithCalculating = true;
}

void MainPage::equalClicked()
{
    double operand = getDisplayText().toDouble();

    if (!pendingMultiplicativeOperator.isEmpty()) {
        if (!calculate(operand, pendingMultiplicativeOperator)) {
            abortOperation();
            return;
        }
        operand = factorSoFar;
        factorSoFar = 0.0;
        pendingMultiplicativeOperator.clear();
    }
    if (!pendingAdditiveOperator.isEmpty()) {
        if (!calculate(operand, pendingAdditiveOperator)) {
            abortOperation();
            return;
        }
        pendingAdditiveOperator.clear();
    } else {
        sumSoFar = operand;
    }

    //setDisplayText(QString::number(sumSoFar, 'g', 12));
    setDisplayText(parseString(sumSoFar));
    sumSoFar = 0.0;
    waitingForOperand = true;
    setSelectedButton0();
}

void MainPage::pointClicked()
{
    QLocale locales;
    QString text = getDisplayText();
    bool stop = false;

    setSelectedButton0();

    if (waitingForOperand)
        setDisplayText("0");

    if ((text.length() == 12 && text.at(0) != '-')
            || text.length() > 12)
        stop = true;

    if (!display->text().contains(locales.decimalPoint()) && !stop)
        setDisplayText(getDisplayText() + tr("."));

    waitingForOperand = false;
}

void MainPage::changeSignClicked()
{
    QString text = getDisplayText();
    double value = text.toDouble();

    if (value > 0.0) {
        text.prepend(tr("-"));
    } else if (value < 0.0) {
        text.remove(0, 1);
    }
    setDisplayText(text);
}

void MainPage::backspaceClicked()
{
    /* Check if there's an operator button selected. */
    if (!opButtons[3]->isEnabled()) {
        /* changeSign button is disabled.                      */
        /* We can assume, that an operator button is selected. */
        pendingMultiplicativeOperator.clear();
        pendingAdditiveOperator.clear();
        waitingForOperand = false;
        waitWithCalculating = true;
        setSelectedButton0();
        return;
    }

    QString text = getDisplayText();
    text.chop(1);
    if (text.isEmpty()) {
        text = "0";
        waitingForOperand = true;
    }
    setDisplayText(text);
}

void MainPage::clear()
{
    if (waitingForOperand)
        return;

    display->setText("0");
    waitingForOperand = true;
    waitWithCalculating = true;
}

void MainPage::clearAll()
{
    setSelectedButton0();
    sumSoFar = 0.0;
    factorSoFar = 0.0;
    pendingAdditiveOperator.clear();
    pendingMultiplicativeOperator.clear();
    setDisplayText("0");
    waitingForOperand = true;
    waitWithCalculating = true;
}

void MainPage::getPi()
{
    // Hardcoded Pi value
    double pi = 3.14159265358;

    // Display value
    setDisplayText(QString::number(pi, 'g', 12));
    waitingForOperand = true;
}

void MainPage::getRandom()
{
    // Initialize random seed
    srand(time(NULL));

    // Get random value and parse it
    double value = (rand() % 1000000);
    value = value / 1000000;

    // Display value
    setDisplayText(QString::number(value, 'g', 12));
    waitingForOperand = true;
}

void MainPage::computeFactorial()
{
    int display = getDisplayText().toInt();
    // Initial value for factorial
    double value = 1;

    if (display < 0) {
        // Throw error
        throwError("Value has to be equal or higer than 0");
    }
    else if (display == 0) {
        setDisplayText(QString::number(value));
        waitingForOperand = true;
    }
    else {
        // Compute factorial
        for (int i = 0; i < display; i++)
            value = value + value * i;
        waitingForOperand = true;
        setDisplayText(QString::number(value, 'g', 11));
    }
}

void MainPage::clearMemory()
{
    sumInMemory = 0.0;
}

void MainPage::readMemory()
{
    setDisplayText(QString::number(sumInMemory, 'g', 12));
    waitingForOperand = true;
}

void MainPage::setMemory()
{
    equalClicked();
    sumInMemory = getDisplayText().toDouble();
    qDebug() << "Set" << sumInMemory;
}

void MainPage::addToMemory()
{
    equalClicked();
    sumInMemory += getDisplayText().toDouble();
    qDebug() << "Add" << sumInMemory;
}

void MainPage::subFromMemory()
{
    equalClicked();
    sumInMemory -= getDisplayText().toDouble();
    qDebug() << "Remove" << sumInMemory;
}

void MainPage::abortOperation()
{
    clearAll();
    throwError("Can not calculate");
}

bool MainPage::calculate(double rightOperand, const QString &pendingOperator)
{
    qDebug() << "Data to calculate:" << rightOperand;
    qDebug() << "SumSoFar:" << sumSoFar;
    qDebug() << "factorSoFar:" << factorSoFar;
    if (pendingOperator == tr("+")) {
        qDebug() << "calculate: sum";
        sumSoFar += rightOperand;
    } else if (pendingOperator == tr("-")) {
        qDebug() << "calculate: sub";
        sumSoFar -= rightOperand;
    } else if (pendingOperator == tr("\327")) {
        qDebug() << "calculate: multi";
        factorSoFar *= rightOperand;
    } else if (pendingOperator == tr("\367")) {
        qDebug() << "calculate: div";
        if (rightOperand == 0.0)
            return false;
        factorSoFar /= rightOperand;
    }
    return true;
}

void MainPage::throwError(const QString &text)
{
    infoBanner->setStyleName(MBannerType::InformationBanner);
    infoBanner->setTitle(text);
    infoBanner->appear(scene(), MSceneWindow::KeepWhenDone);
}

void MainPage::showAboutDialog()
{
    MDialog *dialog = new MDialog("", M::CloseButton);

    const QChar CopyrightSymbol(0x00a9);

    QString text(qtTrId("Open source calculator for MeeGo 1.2 Harmattan.\n"));
    QString copyright_string(QString(CopyrightSymbol) + QString::fromUtf8(" 2012 Tomasz Pieniążek"));

    MLabel *textSystemModal= new MLabel(text + copyright_string);
    textSystemModal->setStyleName("CommonBodyTextInverted");
    textSystemModal->setAlignment(Qt::AlignCenter);
    textSystemModal->setWordWrap(true);
    textSystemModal->setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);

    MLabel *title= new MLabel(qtTrId("FOSS-calc 0.1"));
    title->setStyleName("title_label");
    title->setAlignment(Qt::AlignCenter);
    title->setWordWrap(true);
    title->setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);

    QGraphicsLinearLayout *layoutDesc = new QGraphicsLinearLayout(Qt::Horizontal);
    layoutDesc->addStretch();
    layoutDesc->addItem(textSystemModal);
    layoutDesc->addStretch();

    QGraphicsLinearLayout *layoutTitle = new QGraphicsLinearLayout(Qt::Horizontal);
    layoutTitle->addStretch();
    layoutTitle->addItem(title);
    layoutTitle->addStretch();

    //MImageWidget *image = new MImageWidget(new QPixmap("/usr/share/icons/hicolor/80x80/apps/videozoom.png"));
    MImageWidget *image = new MImageWidget("icon-l-calculator");

    QGraphicsLinearLayout *layout1 = new QGraphicsLinearLayout(Qt::Vertical);
    layout1->addItem(image);
    layout1->addItem(layoutTitle);
    layout1->addItem(layoutDesc);
    layout1->addStretch();

    dialog->centralWidget()->setLayout(layout1);
    dialog->setObjectName("about_dialog");

    dialog->appear(MSceneWindow::DestroyWhenDone);
}
