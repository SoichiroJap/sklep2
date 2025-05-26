#include "shop.h"
#include <QVBoxLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QPushButton>

ShopDialog::ShopDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Sklep");
    resize(600, 500);

    QVBoxLayout *layout = new QVBoxLayout(this);
    productTable = new QTableWidget(this);
    productTable->setColumnCount(3);
    productTable->setHorizontalHeaderLabels(QStringList() << "Produkt" << "Cena (zł)" << "Kup");

    productTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    productTable->verticalHeader()->setVisible(false);
    productTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    productTable->setSelectionMode(QAbstractItemView::NoSelection);

    layout->addWidget(productTable);
    setLayout(layout);

    const QList<QPair<QString, double>> products = {
        {"Ser Cheddar (200g)", 8.50},
        {"Jogurt naturalny (1L)", 5.00},
        {"Śmietana 18% (300ml)", 3.80},
        {"Ser kozi (150g)", 10.00},
        {"Mleko bez laktozy 1L", 4.50},
        {"Filet z kurczaka (1kg)", 18.00},
        {"Mielona wołowina (500g)", 12.00},
        {"Kiełbasa śląska (1kg)", 16.00},
        {"Boczek wędzony (200g)", 8.00},
        {"Indyk piersi (1kg)", 20.00},
        {"Jabłka (1kg)", 4.00},
        {"Pomarańcze (1kg)", 5.50},
        {"Winogrono (1kg)", 7.00},
        {"Truskawki (500g)", 6.00},
        {"Maliny (150g)", 5.00},
        {"Marchew (1kg)", 2.50},
        {"Ziemniaki (5kg)", 10.00},
        {"Cebula (1kg)", 3.00},
        {"Czosnek (100g)", 3.50},
        {"Sałata lodowa", 3.00},
        {"Bułki kajzerki (6 szt.)", 4.50},
        {"Croissant", 3.50},
        {"Bagietka francuska", 3.00},
        {"Chleb razowy (500g)", 6.00},
        {"Bułki grahamki (4 szt.)", 5.00},
        {"Tuńczyk w puszce (150g)", 6.00},
        {"Fasola czerwona w puszce (400g)", 4.00},
        {"Kukurydza konserwowa (340g)", 3.50},
        {"Pomidory w puszce (400g)", 5.00},
        {"Zupa pomidorowa (400ml)", 6.50},
        {"Chipsy solone (150g)", 5.50},
        {"Orzechy włoskie (200g)", 10.00},
        {"Migdały (200g)", 12.00},
        {"Paluszki słone (200g)", 4.00},
        {"Popcorn naturalny (100g)", 3.00},
        {"Woda gazowana 1.5L", 2.50},
        {"Sok jabłkowy 1L", 4.50},
        {"Kawa mielona 250g", 12.00},
        {"Herbata czarna (50 torebek)", 8.00},
        {"Napój energetyczny 250ml", 4.00},
        {"Ketchup (500ml)", 6.00},
        {"Majonez (400ml)", 7.00},
        {"Musztarda (200g)", 4.50},
        {"Sos sojowy (250ml)", 8.00},
        {"Oliwa z oliwek 500ml", 18.00},
        {"Pizza mrożona (450g)", 12.00},
        {"Mix warzyw mrożonych (1kg)", 8.00},
        {"Frytki mrożone (1kg)", 9.00},
        {"Lody waniliowe (1L)", 10.00},
        {"Szpinak mrożony (500g)", 6.00},
        {"Kasza gryczana (500g)", 5.50},
        {"Płatki owsiane (500g)", 4.00},
        {"Mąka pszenna (1kg)", 3.50},
        {"Makaron pełnoziarnisty (500g)", 6.50},
        {"Komosa ryżowa (200g)", 8.00},
        {"Sos pomidorowy (500g)", 7.00},
        {"Tortille pszenne (6 szt.)", 6.00},
        {"Mleko kokosowe (400ml)", 8.00},
        {"Ryż basmati (1kg)", 9.00},
        {"Cynamon mielony (50g)", 5.00},
        {"Miód naturalny (500g)", 15.00},
        {"Dżem truskawkowy (300g)", 6.00},
        {"Ser feta (200g)", 8.00},
        {"Oliwki zielone (200g)", 7.00},
        {"Kapary (100g)", 9.00},
        {"Jogurt grecki (150g)", 4.50},
        {"Maślanka 1L", 3.80},
        {"Szynka parmeńska (100g)", 12.00},
        {"Kiełbasa krakowska (500g)", 14.00},
        {"Gruszki (1kg)", 5.00},
        {"Kiwi (1kg)", 8.00},
        {"Papryka czerwona (1kg)", 7.00},
        {"Cukinia (1kg)", 5.00},
        {"Rogal z marmoladą", 3.50},
        {"Chleb orkiszowy (500g)", 7.00},
        {"Batonik zbożowy", 2.50},
        {"Prażynki solone", 3.00},
        {"Sok wielowarzywny 1L", 6.00},
        {"Herbata zielona (20 torebek)", 7.00},
        {"Ocet balsamiczny (250ml)", 15.00},
        {"Sos barbecue (300ml)", 9.00},
        {"Pierogi ruskie (1kg)", 12.00},
        {"Mrożone owoce jagodowe (500g)", 10.00},
        {"Kasza jaglana (500g)", 4.50},
        {"Otręby pszenne (500g)", 3.50},
        {"Hummus (200g)", 6.00},
        {"Pesto (190g)", 11.00},
        {"Żelatyna (50g)", 3.00},
        {"Drożdże świeże (100g)", 2.50},
        {"Cukier wanilinowy (50g)", 4.00}
    };

    productTable->setRowCount(products.size());

    addToCartButton = new QPushButton("Dodaj do koszyka", this);
    layout->addWidget(addToCartButton);

    connect(addToCartButton, &QPushButton::clicked, this, &ShopDialog::onAddToCartClicked);

    for (int i = 0; i < products.size(); ++i) {
        const QString &name = products[i].first;
        double price = products[i].second;

        QTableWidgetItem *nameItem = new QTableWidgetItem(name);
        QTableWidgetItem *priceItem = new QTableWidgetItem(QString::number(price, 'f', 2));
        QTableWidgetItem *checkItem = new QTableWidgetItem();
        checkItem->setCheckState(Qt::Unchecked);

        productTable->setItem(i, 0, nameItem);
        productTable->setItem(i, 1, priceItem);
        productTable->setItem(i, 2, checkItem);
    }
}

void ShopDialog::onAddToCartClicked()
{
    int selectedCount = 0;
    double totalPrice = 0.0;

    for (int i = 0; i < productTable->rowCount(); ++i) {
        QTableWidgetItem *checkItem = productTable->item(i, 2);
        if (checkItem->checkState() == Qt::Checked) {
            selectedCount++;

            bool ok;
            double price = productTable->item(i, 1)->text().toDouble(&ok);
            if (ok) {
                totalPrice += price;
            }
        }
    }

    if (selectedCount == 0) {
        QMessageBox::information(this, "Komunikat", "Nie wybrano żadnych produktów.");
        return;
    }

    QString message = QString("Dodano %1 przedmiot(ów) do koszyka.\nŁączna cena: %2 zł")
                          .arg(selectedCount)
                          .arg(QString::number(totalPrice, 'f', 2));

    QMessageBox msgBox;
    msgBox.setWindowTitle("Koszyk");
    msgBox.setText(message);

    QPushButton *buyButton = msgBox.addButton(tr("Kup"), QMessageBox::AcceptRole);
    QPushButton *continueButton = msgBox.addButton(tr("Kontynuuj zakupy"), QMessageBox::RejectRole);

    msgBox.exec();

    if (msgBox.clickedButton() == buyButton) {

    }
}
