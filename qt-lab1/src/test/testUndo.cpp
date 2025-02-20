#include <QtTest>
#include <QSignalSpy>
#include "../ui/MainWindow.h"
#include "../ui/OperationWidget.h"
#include "../core/Game.h"

class TestUndo : public QObject
{
    Q_OBJECT

private slots:
    void testUndoMove();
};

void TestUndo::testUndoMove()
{
    MainWindow mainWindow;
    std::shared_ptr<Game> game = mainWindow.getGame();
    QVERIFY(game != nullptr);

    std::shared_ptr<OperationWidget> operationWidget = mainWindow.getOperationWidget();
    QVERIFY(operationWidget != nullptr);

    // 开始游戏
    emit operationWidget->startGameRequested();

    // 模拟下棋
    game->makeMove(7, 7);  // 黑子
    game->makeMove(8, 8);  // 白子
    game->makeMove(7, 8);  // 黑子

    // 记录当前棋盘状态
    QVector<QVector<QString>> initialBoard(15, QVector<QString>(15, ""));
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            auto piece = game->getBoard()->getPiece(i, j);
            if (piece) {
                initialBoard[i][j] = QString::fromStdString(piece->getColor());
            }
        }
    }

    // 模拟点击悔棋按钮
    QSignalSpy undoSpy(operationWidget.get(), SIGNAL(undoRequested()));
    emit operationWidget->undoRequested();

    // 验证信号是否被发射
    QCOMPARE(undoSpy.count(), 1);

    // 验证棋盘状态
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            auto piece = game->getBoard()->getPiece(i, j);
            if (i == 7 && j == 8) {
                QVERIFY(piece == nullptr);  // 最后一步应该被撤销
            } else {
                if (piece) {
                    QCOMPARE(QString::fromStdString(piece->getColor()), initialBoard[i][j]);
                } else {
                    QVERIFY(initialBoard[i][j].isEmpty());
                }
            }
        }
    }

    // 验证当前玩家
    QCOMPARE(game->getCurrentPlayer()->getColor(), "Black");

    // 模拟点击悔棋按钮
    emit operationWidget->undoRequested();

    // 验证信号是否被发射
    QCOMPARE(undoSpy.count(), 2);

    // 验证棋盘状态
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            auto piece = game->getBoard()->getPiece(i, j);
            if (i == 7 && j == 8) {
                QVERIFY(piece == nullptr);  // 最后两步应该被撤销
            } 
            else if (i == 8 && j == 8) {
                QVERIFY(piece == nullptr);  // 最后两步应该被撤销
            }
            else {
                if (piece) {
                    QCOMPARE(QString::fromStdString(piece->getColor()), initialBoard[i][j]);
                } else {
                    QVERIFY(initialBoard[i][j].isEmpty());
                }
            }
        }
    }

    // 验证当前玩家
    QCOMPARE(game->getCurrentPlayer()->getColor(), "White");

    // 模拟点击悔棋按钮
    emit operationWidget->undoRequested();

    // 验证信号是否被发射
    QCOMPARE(undoSpy.count(), 3);

    // 验证棋盘状态
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            auto piece = game->getBoard()->getPiece(i, j);
            QVERIFY(piece == nullptr); // 全部被撤销
        }
    }

    // 验证当前玩家
    QCOMPARE(game->getCurrentPlayer()->getColor(), "Black");

    // 模拟点击悔棋按钮
    emit operationWidget->undoRequested();

    // 验证信号是否被发射
    QCOMPARE(undoSpy.count(), 4);

    // 验证棋盘状态
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            auto piece = game->getBoard()->getPiece(i, j);
            QVERIFY(piece == nullptr); // 全部被撤销
        }
    }

    // 验证当前玩家
    QCOMPARE(game->getCurrentPlayer()->getColor(), "Black"); // 棋盘为空的时候，当前玩家应该是黑棋

    // 模拟下棋
    game->makeMove(7, 7);  // 黑子
    game->makeMove(8, 8);  // 白子
    game->makeMove(7, 8);  // 黑子

    // 验证棋盘状态
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            auto piece = game->getBoard()->getPiece(i, j);
            if (piece) {
                QCOMPARE(QString::fromStdString(piece->getColor()), initialBoard[i][j]);
            } else {
                QVERIFY(initialBoard[i][j].isEmpty());
            }
        }
    }

    // 验证当前玩家
    QCOMPARE(game->getCurrentPlayer()->getColor(), "White");
}

QTEST_MAIN(TestUndo)
#include "testUndo.moc"