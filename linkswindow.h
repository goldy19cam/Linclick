//Declaration de la fenetre de liens/applis(ecran 2), affichees apres validation du formulaire.
#ifndef LINKSWINDOW_H
#define LINKSWINDOW_H

#include <QWidget>
#include <QPushButton>

class LinksWindow: public QWidget
{
    //facultatif, elle permet de lier ma classe linksWindow aux autres objets ,toujours l'utiliser lorsqu'on inclut QWidget ou QObject
    Q_OBJECT
public:
    explicit LinksWindow(QWidget*parent = nullptr);
private slots:
    void onPrecedentClicked();
private:
    QPushButton*retourButton;
};

#endif // LINKSWINDOW_H