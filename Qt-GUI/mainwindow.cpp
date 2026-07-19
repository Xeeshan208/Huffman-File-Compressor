#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Huffman File Compressor");
    setFixedSize(900,600);

    ui->txtStatus->setReadOnly(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnBrowse_clicked()
{
    ui->txtStatus->clear();

    inputFile = QFileDialog::getOpenFileName(
        this,
        "Select Input File",
        "",
        "Text Files (*.txt);;All Files (*.*)"
        );

    if(inputFile.isEmpty())
        return;

    ui->txtInput->setText(inputFile);

    outputFile = inputFile;
    outputFile.replace(".txt",".bin");

    ui->txtOutput->setText(outputFile);

    ui->txtStatus->append("======================================");
    ui->txtStatus->append("Input File Selected Successfully");
    ui->txtStatus->append(inputFile);
    ui->txtStatus->append("======================================");
}

void MainWindow::on_btnCompress_clicked()
{
    if(inputFile.isEmpty())
    {
        QMessageBox::warning(this,"Warning","Please Select Input File First.");
        return;
    }

    // Read File
    string text = compressor.readFile(inputFile.toStdString());

    // Build Huffman Tree
    tree.buildTree(text);
    tree.buildCodes();

    // Encode
    string encoded = compressor.encodeText(text,tree.huffmanCodes);

    // Save Binary
    compressor.saveCompressedBinary(outputFile.toStdString(),encoded);

    double originalSize = text.size()*8;
    double compressedSize = encoded.size();

    double ratio = (1-compressedSize/originalSize)*100;

    ui->txtStatus->append("");
    ui->txtStatus->append("Compression Completed Successfully");
    ui->txtStatus->append("--------------------------------------");
    ui->txtStatus->append("Compressed File:");
    ui->txtStatus->append(outputFile);
    ui->txtStatus->append("");

    ui->txtStatus->append("Original Size : "
                          + QString::number(originalSize/8.0,'f',2)
                          + " Bytes");

    ui->txtStatus->append("Compressed Size : "
                          + QString::number(compressedSize/8.0,'f',2)
                          + " Bytes");

    ui->txtStatus->append("Compression Ratio : "
                          + QString::number(ratio,'f',2)
                          + " %");

    QMessageBox::information(this,
                             "Success",
                             "File Compressed Successfully.");
}

void MainWindow::on_btnDecompress_clicked()
{
    if(outputFile.isEmpty())
    {
        QMessageBox::warning(this,
                             "Warning",
                             "Please Compress File First.");
        return;
    }

    string binaryData =
        decompressor.readCompressedBinary(outputFile.toStdString());

    string decoded =
        decompressor.decodeText(binaryData,tree.root);

    QString decompressedFile = outputFile;
    decompressedFile.replace(".bin","_decompressed.txt");

    ofstream out(decompressedFile.toStdString());
    out<<decoded;
    out.close();

    ui->txtStatus->append("");
    ui->txtStatus->append("Decompression Completed Successfully");
    ui->txtStatus->append("--------------------------------------");
    ui->txtStatus->append("Output File:");
    ui->txtStatus->append(decompressedFile);

    QMessageBox::information(this,
                             "Success",
                             "File Decompressed Successfully.");
}