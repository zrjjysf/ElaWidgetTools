#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ElaWindow.h"

class AlphaMainPage;
class ElaContentDialog;
class ElaSuggestBox;
class T_About;

class MainWindow : public ElaWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

private:
    void initWindow();
    void initEdgeLayout();
    void initContent();

    ElaContentDialog* _closeDialog{nullptr};
    ElaSuggestBox* _windowSuggestBox{nullptr};
    AlphaMainPage* _alphaPage{nullptr};
    T_About* _aboutPage{nullptr};
    QString _aboutKey;
};

#endif // MAINWINDOW_H
