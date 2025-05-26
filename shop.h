#ifndef SHOP_H
#define SHOP_H

#include <QDialog>
#include <QTableWidget>

class ShopDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShopDialog(QWidget *parent = nullptr);

private:
    QTableWidget *productTable;
    QPushButton *addToCartButton;

    void onAddToCartClicked();
};

#endif // SHOP_H
