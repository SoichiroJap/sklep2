#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();
}

MainWindow::~MainWindow() {}

void MainWindow::setupUI()
{
    QWidget *central = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout;

    inputField = new QLineEdit(this);
    addButton = new QPushButton("Dodaj", this);
    removeButton = new QPushButton("Usuń", this);
    saveButton = new QPushButton("Zapisz", this);
    loadButton = new QPushButton("Wczytaj", this);
    shopButton = new QPushButton("Sklep", this);
    darkModeCheckBox = new QCheckBox("Tryb ciemny", this);
    shoppingList = new QListWidget(this);

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(inputField);
    topLayout->addWidget(addButton);

    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->addWidget(removeButton);
    bottomLayout->addWidget(saveButton);
    bottomLayout->addWidget(loadButton);
    bottomLayout->addWidget(shopButton);

    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(shoppingList);
    mainLayout->addLayout(bottomLayout);
    mainLayout->addWidget(darkModeCheckBox);

    central->setLayout(mainLayout);
    setCentralWidget(central);
    setWindowTitle("Shopping List");

    connect(addButton, &QPushButton::clicked, this, &MainWindow::onAddItem);
    connect(removeButton, &QPushButton::clicked, this, &MainWindow::onRemoveItems);
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::onSaveToFile);
    connect(loadButton, &QPushButton::clicked, this, &MainWindow::onLoadFromFile);

}

void MainWindow::onAddItem()
{
    QString text = inputField->text().trimmed();
    if (!text.isEmpty()) {
        QListWidgetItem *item = new QListWidgetItem(text);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Unchecked);
        shoppingList->addItem(item);
        inputField->clear();
    }
}

void MainWindow::onRemoveItems()
{
    for (int i = shoppingList->count() - 1; i >= 0; --i) {
        QListWidgetItem *item = shoppingList->item(i);
        if (item->checkState() == Qt::Checked) {
            delete shoppingList->takeItem(i);
        }
    }
}

void MainWindow::onSaveToFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Zapisz listę zakupów", "", "Pliki tekstowe (*.txt)");
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }

    QTextStream out(&file);
    int index = 1;
    for (int i = 0; i < shoppingList->count(); ++i) {
        QListWidgetItem *item = shoppingList->item(i);
        out << index++ << ". " << item->text() << "\n";
    }

    file.close();
}

void MainWindow::onLoadFromFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Wczytaj listę zakupów", "", "Pliki tekstowe (*.txt)");
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QTextStream in(&file);
    shoppingList->clear();

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (!line.isEmpty()) {
            QRegularExpression regex("^\\d+\\.\\s*");
            QString productName = line.remove(regex);

            QListWidgetItem *item = new QListWidgetItem(productName);
            item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
            item->setCheckState(Qt::Unchecked);
            shoppingList->addItem(item);
        }
    }

    file.close();
}
