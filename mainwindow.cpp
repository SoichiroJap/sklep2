#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFile>
#include <QTextStream>

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
