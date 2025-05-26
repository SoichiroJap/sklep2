#include "shop.h"
#include <QVBoxLayout>

ShopDialog::ShopDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Sklep");
    resize(400, 300);

    QVBoxLayout *layout = new QVBoxLayout(this);
    setLayout(layout);
}
