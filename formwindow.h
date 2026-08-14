//Declaration de la fenetre du formulaire (Ecran 1): saisie du nom, numero, date et nombres de demandes.
#ifndef FORMWINDOW_H
#define FORMWINDOW_H
#include <QWidget>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QSpinBox>
#include <QPushButton>
class FormWindow: public QWidget
{
    Q_OBJECT
public :
    explicit FormWindow(QWidget *parent = nullptr);
private slots:
    void onSuivantClicked();
    void refresh();
private:
    QLineEdit*nomEdit;
    QLineEdit*numeroEdit;
    QDateTimeEdit*dateTimeEdit;
    QSpinBox*nombreDemandesSpin;
    QPushButton*suivantButton;
    bool enregistrerDemande();
};

#endif // FORMWINDOW_H
