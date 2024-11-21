#pragma once
#include <QMainWindow>
#include "GameWidget.h"
#include "ScoreBoard.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void startNewGame();
    void showAbout();

private:
    GameWidget *gameWidget;
    ScoreBoard *scoreBoard;
    
    void setupUI();
    void createMenus();
    void createDockWidgets();
};