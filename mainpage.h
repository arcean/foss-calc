#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <MApplicationPage>
#include <MDialog>
#include <QColor>
#include <MAction>
#include <MWidgetAction>
#include <MLabel>
#include <MBanner>

/* To enable debug msgs: */
/* -output-level debug */

#define MAX_NUM 12
#define DISPLAY_SIZE_1 120 // 3
#define DISPLAY_SIZE_2 102 // 1
#define DISPLAY_SIZE_3 76 // 2
#define DISPLAY_SIZE_4 58 // 1
#define DISPLAY_SIZE_5 42 // 2
#define DISPLAY_SIZE_6 38 // 1
#define DISPLAY_SIZE_7 30 // 2
#define DISPLAY_SIZE_8 26 // 2

#define NUM_0P_BUTTONS 7
#define MAX_NUM 12



class MainPage : public MApplicationPage {
    Q_OBJECT
public:
    MainPage(QGraphicsItem *parent = 0);

protected:
    virtual void createContent();

public slots:

private slots:
    void digitClicked();
    void additiveOperatorClicked();
    void multiplicativeOperatorClicked();
    void unaryOperatorClicked();
    void equalClicked();
    void pointClicked();
    void changeSignClicked();
    void backspaceClicked();
    void clear();
    void clearAll();
    void clearMemory();
    void readMemory();
    void setMemory();
    void addToMemory();
    void subFromMemory();
    void abortOperation();
    void getPi();
    void getRandom();
    void computeFactorial();

    void setSelectedButton0();

    // About page
    void showAboutDialog();

    // Orientation change
    void orientationChanged();

private:
    bool calculate(double rightOperand, const QString &pendingOperator);
    QString insertEmptyFields(QString text);
    void setDisplayText(QString text);
    QString getDisplayText();
    void setDisplayStyle(int number);
    void throwError(const QString &text);

    MLabel *display;
    /* Op buttons */
    MButton *opButtons[7];
    /* Info banner */
    MBanner *infoBanner;

    enum operationType {add, sub, multi, div};
    int nextOperation;

    int displayStyleNumber;

    double sumInMemory;
    double sumSoFar;
    double factorSoFar;
    QString pendingAdditiveOperator;
    QString pendingMultiplicativeOperator;
    bool waitingForOperand;
    bool waitWithCalculating;

};

#endif // MAINPAGE_H
