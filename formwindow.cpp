//Implemantation du formulaire : cree les champs, enregistre les donnees en base et ouvre la fenetre suivante.//
#include "formwindow.h"
#include "linkswindow.h"

#include <QFormLayout>
#include <QFont>
#include <QFrame>
#include <QLabel>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QRegularExpressionValidator>
#include <QIntValidator>

FormWindow::FormWindow(QWidget *parent) : QWidget(parent)
{
    setStyleSheet("background-color: #ffffff;");
    setWindowTitle(" LINKCLICK ");
    //permet de creer la frame principale
    QFrame *monCadre = new QFrame(this);
    monCadre->setFrameStyle(QFrame::StyledPanel);
    monCadre->setFixedSize(1000,600);
    monCadre->setFrameStyle(QFrame::NoFrame);//enleve les bordures de la frame

    //permet d'inserer un logo  a partir des images contenues dans logos.qrc qui se trouve dans Resources
    QLabel *logoLabel = new QLabel(this);
    QPixmap logoPixmap(":/images/SOCADEL.png");
    logoLabel->setPixmap(logoPixmap.scaled(400, 400, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    logoLabel->setAlignment(Qt::AlignHCenter | Qt::AlignTop);

    QLabel *salut = new QLabel("<strong>BIENVENUE</strong><br><br>");
    salut->setWordWrap(true);
    QFont grandeur = salut->font();
    grandeur.setPointSize(20);
    salut->setFont(grandeur);
    salut->setAlignment(Qt::AlignHCenter);

    QLabel *introduction = new QLabel("<b>Bienvenue sur Lincklick votre plateforme de Self-Services</b><br>"
                                      "<b>Veuillez remplir vos informations puis cliquer sur <strong><u>SUIVANT</u></strong> pour continuer</b>",this);
    introduction->setWordWrap(true);
    introduction->setAlignment(Qt::AlignHCenter);

    //permet de manipuler la police du texte introductif
    QFont police = introduction->font();
    police.setPointSize(14);
    introduction->setFont(police);

    nomEdit = new QLineEdit(this);
    nomEdit->setFont(police);
    QRegularExpression nomRegex("^[A-Za-zÀ-ÖØ-öø-ÿ ]*$");//verifie que la valeur entree ne contient que des lettres
    nomEdit->setFixedSize(700,40);
    nomEdit->setPlaceholderText("Nom Complet");
    nomEdit->setValidator(new QRegularExpressionValidator(nomRegex, this));//applique la verification au champ Nom

    numeroEdit = new QLineEdit(this);
    numeroEdit->setFont(police);
    QRegularExpression numeroRegex("^[0-9+ ]*$");//verifie que la valeur entree ne contient que des chiffres
    numeroEdit->setFixedSize(700,40);
    numeroEdit->setValidator(new QRegularExpressionValidator(numeroRegex, this));//applique la verification au champ Numero
    numeroEdit->setText("+237 ");//defini le modele de numero

    dateTimeEdit = new QDateTimeEdit(this);
    dateTimeEdit->setFont(police);
    dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    dateTimeEdit->setCalendarPopup(false);
    dateTimeEdit->hide();//masque les champs pour l'utilisateur
    dateTimeEdit->setReadOnly(true);
    dateTimeEdit->setDisplayFormat("dd//MM//yyyy HH:mm:ss");
    dateTimeEdit->setButtonSymbols(QAbstractSpinBox::NoButtons);
    dateTimeEdit->setFixedSize(700,40);

    nombreDemandesSpin = new QSpinBox(this);
    nombreDemandesSpin->setFont(police);
    nombreDemandesSpin->setRange(1, 999);
    nombreDemandesSpin->setValue(1);
    nombreDemandesSpin->hide();
    nombreDemandesSpin->setReadOnly(true);//rend les champs de saisie impossible a editer
    nombreDemandesSpin->setButtonSymbols(QSpinBox::NoButtons);//supprime les boutons d'incrementation
    nombreDemandesSpin->setFixedSize(700,40);

    suivantButton = new QPushButton("SUIVANT", this);
    suivantButton->setFixedSize(120,80);
    connect(suivantButton, &QPushButton::clicked, this, &FormWindow::onSuivantClicked);

    connect(nomEdit, &QLineEdit::textChanged, this, &FormWindow::refresh);
    connect(numeroEdit, &QLineEdit::textChanged, this, &FormWindow::refresh);

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow("NOM :", nomEdit);
    formLayout->addRow("NUMERO", numeroEdit);
    formLayout->addRow("Date de la demande :", dateTimeEdit);
    formLayout->labelForField(dateTimeEdit)->hide();
    formLayout->addRow("Nombre de demandes :", nombreDemandesSpin);
    formLayout->labelForField(nombreDemandesSpin)->hide();
    formLayout->setFormAlignment(Qt::AlignCenter);

    //permet de centrer la frame principale par rapport a l'ensemble de la fenetre
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(monCadre, 0, Qt::AlignCenter);

    //Ajouter les elements dans le layout de la frame
    QVBoxLayout *frameLayout = new QVBoxLayout(monCadre);
    frameLayout->addWidget(logoLabel);
    frameLayout->addSpacing(15);
    frameLayout->addWidget(salut);
    frameLayout->addWidget(introduction);
    frameLayout->addLayout(formLayout);
    frameLayout->addSpacing(5);
    frameLayout->addWidget(suivantButton, 0, Qt::AlignHCenter | Qt::AlignBottom);

    //appliquer le layout a la frame
    monCadre->setLayout(frameLayout);
}

//fonction permettant de mettre a jour le nombre de demandes d'un meme utilisateur
void FormWindow::refresh()
{
    QString nom = nomEdit->text().trimmed();
    QString numero = numeroEdit->text().trimmed();

    //met le nombre de demande a 0 lorsque les champs ne sont pas remplis
    if (nom.isEmpty() || numero.isEmpty()){
        nombreDemandesSpin->setValue(0);
        return;
    }

    //permet de compter le nombre de demandes effectuees par une meme personne
    QSqlQuery countQuery;
    countQuery.prepare("SELECT COUNT(*) FROM demandes WHERE nom = :nom AND numero = :numero");
    countQuery.bindValue(":nom", nomEdit->text().trimmed());
    countQuery.bindValue(":numero",  numeroEdit->text().trimmed());

    if (countQuery.exec() && countQuery.next()){
        int nombreExistant = countQuery.value(0).toInt();
        nombreDemandesSpin->setValue(nombreExistant + 1);
    }else{
        nombreDemandesSpin->setValue(1);
    }
}

bool FormWindow::enregistrerDemande()
{
    if (nomEdit->text().trimmed().isEmpty() && numeroEdit->text().trimmed().isEmpty()){
        QMessageBox::warning(this, "Champs manquants", "Merci de remplir le nom et le numero.");
        return false;
    }
    if (nomEdit->text().trimmed().isEmpty()){
        QMessageBox::warning(this, "Champ manquant", "Merci de remplir le nom.");
        return false;
    }
    if (numeroEdit->text().trimmed().isEmpty()){
        QMessageBox::warning(this, "Champ manquant", "Merci de remplir le numero.");
        return false;
    }

    //cree une variable pour stocker les chiffres sans le + et ensuite verifier la longueur du numero
    QString numero = numeroEdit->text().trimmed();
    QString chiffres = numero;
    chiffres.remove('+');

    if (chiffres.length()<9){
        QMessageBox::warning(this, "Numero invalide", "Le numero doit contenir au moins 9 chiffres");
        return false;
    }

    //permet lexecution et l'envoi de notre requete SQL
    QSqlQuery query;
    query.prepare("INSERT INTO demandes (nom, numero, date_demande)"
                  "VALUES (:nom, :numero, :date)");
    query.bindValue(":nom", nomEdit->text().trimmed());
    query.bindValue(":numero", numeroEdit->text().trimmed());
    query.bindValue(":date", dateTimeEdit->dateTime().toString("yyyy-MM-dd HH:mm:ss"));

    if (!query.exec()){
        QMessageBox::critical(this, "Erreur", "Echec de l'enregistrement :" + query.lastError().text());
        return false;
    }

    //ajout de la deuxieme table
    QSqlQuery userquery;
    userquery.prepare("INSERT INTO register (nom, numero, nombre_demandes)"
                  "VALUES (:nom, :numero, :nb) "
                  "ON CONFLICT(nom, numero) DO UPDATE SET nombre_demandes = nombre_demandes + 1");//incremente le nombre de demandes si on saisit le meme nom plusieurs fois
    userquery.bindValue(":nom", nomEdit->text().trimmed());
    userquery.bindValue(":numero", numeroEdit->text().trimmed());
    userquery.bindValue(":nb", nombreDemandesSpin->value());

    if (!userquery.exec()){
        QMessageBox::critical(this, "Erreur", "Echec de l'enregistrement :" + userquery.lastError().text());
        return false;
    }
    return true;
}

void FormWindow::onSuivantClicked()
{
    if (!enregistrerDemande())
        return;

    //Ouvre la deuxieme fenetere(liens vers d'autres applis)
    LinksWindow *links = new LinksWindow();
    //libere la memoire a la fermeture
    links->setAttribute(Qt::WA_DeleteOnClose);
    links->show();

    this->close();
}