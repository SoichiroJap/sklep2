#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QCheckBox>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QListWidget *shoppingList;
    QLineEdit *inputField;
    QPushButton *addButton;
    QPushButton *removeButton;
    QPushButton *saveButton;
    QPushButton *loadButton;
    QPushButton *shopButton;
    QCheckBox *darkModeCheckBox;
    void onAddItem();
    void onRemoveItems();
    void onSaveToFile();
    void onLoadFromFile();


    void setupUI();
};

#endif // MAINWINDOW_H
