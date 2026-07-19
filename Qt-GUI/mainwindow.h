#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// Qt Headers
#include <QString>

// Tumhari Header Files
#include "Compressor.h"
#include "Decompressor.h"
#include "HuffmanTree.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_btnBrowse_clicked();

    void on_btnCompress_clicked();

    void on_btnDecompress_clicked();

private:
    Ui::MainWindow *ui;

    // Huffman Objects
    Compressor compressor;
    Decompressor decompressor;
    HuffmanTree tree;

    QString inputFile;
    QString outputFile;
};

#endif // MAINWINDOW_H