#include "linkswindow.h"
#include "formwindow.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLayout>
#include <QFont>
#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QDesktopServices>
#include <QUrl>
#include <QProcess>
#include <QIcon>
#include <QSize>
#include <QToolButton>

LinksWindow::LinksWindow(QWidget *parent) : QWidget(parent)
{
    setStyleSheet("background-color: #ffffff;");
    setWindowTitle(" LINKCLICK ");
    //permet de modifier la taille de la deuxieme fenetre
    resize(750, 500);

    //permet de creer la frame principale
    QFrame *monCadre = new QFrame(this);
    monCadre->setFrameStyle(QFrame::StyledPanel);
    monCadre->setFixedSize(1000,600);
    monCadre->setFrameStyle(QFrame::NoFrame);//enleve les bordures de la frame

    //permet d'inserer un logo a partir des images dans logos.qrc situe dans Resources
    QLabel *logoLabel = new QLabel(this);
    QPixmap logoPixmap(":/images/SOCADEL.png");
    logoLabel->setPixmap(logoPixmap.scaled(400, 400, Qt::KeepAspectRatio, Qt::SmoothTransformation));//permet de redimensionner le logo//
    logoLabel->setAlignment(Qt::AlignHCenter | Qt::AlignTop);//permet d'aligner le logo

    QLabel *paragraphe = new QLabel("<strong>Veuillez maintenant selectionner une application/un site web:</strong>",this);
    paragraphe->setWordWrap(true);//pour que le texte ne depasse pas les bordures
    paragraphe->setAlignment(Qt::AlignHCenter);

    //pour changer la taille du texte introductif
    QFont police = paragraphe->font();
    //taille
    police.setPointSize(14);
    paragraphe->setFont(police);

    retourButton = new QPushButton("RETOUR", this);
    retourButton->setFixedSize(120,80);
    connect(retourButton, &QPushButton::clicked, this, &LinksWindow::onPrecedentClicked);

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(retourButton, 0, Qt::AlignTop | Qt::AlignRight);
    mainLayout->addWidget(monCadre, 0, Qt::AlignCenter);
    mainLayout->addStretch();

    //pour les boutons cliquables vers les applis de mon PC on peut aussi utiliser QPushButton mais ce sera plus difficile d'inserer les icones au dessus du nom de l'application
    QToolButton *bouton1 = new QToolButton(this);
  bouton1->setAutoRaise(true);//enleve les bordures des boutons
   bouton1->setFixedSize(160,160);//taille du bouton
   bouton1->setIcon(QIcon(":/images/SOCADEL.png"));
  bouton1->setIconSize(QSize(120,100));//taille de l'icone
   bouton1->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);//pour positionner l'icone au dessus du nom de l'application
    connect(bouton1, &QToolButton::clicked, this, [](){
        QDesktopServices::openUrl(QUrl("https://my.socadel.cm/"));
    });

    QToolButton *bouton2 = new QToolButton(this);
    bouton2->setAutoRaise(true);
    bouton2->setFixedSize(160,160);
   bouton2->setIcon(QIcon(":/images/Telegram-icon.png"));
   bouton2->setIconSize(QSize(100,100));
    bouton2->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    connect(bouton2, &QToolButton::clicked, this, [](){
        QDesktopServices::openUrl(QUrl("https://www.bing.com/ck/a?!&&p=cf7a7337d8314d326d8bfc0732504f0bc9465ed2c50591eb0ae196a1f93871bdJmltdHM9MTc4NjA2MDgwMA&ptn=3&ver=2&hsh=4&fclid=2be59cb9-d541-6720-3a29-8b17d499665e&psq=telegram&u=a1aHR0cHM6Ly9kZXNrdG9wLnRlbGVncmFtLm9yZy8"));
    });

    QToolButton *bouton3 = new QToolButton(this);
    bouton3->setAutoRaise(true);
    bouton3->setFixedSize(160,160);
    bouton3->setIcon(QIcon(":/images/Maps-icon.png"));
   bouton3->setIconSize(QSize(100,100));
    bouton3->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    connect(bouton3, &QToolButton::clicked, this, [](){
        QDesktopServices::openUrl(QUrl("https://www.bing.com/ck/a?!&&p=6bfca3c64c38d0dcfabc5b90be20f38237d3b16b78820ff67f9038417ce27943JmltdHM9MTc4NTk3NDQwMA&ptn=3&ver=2&hsh=4&fclid=380fe9a4-9b62-69ec-3f1c-fe099a2f68bf&psq=google+maps&u=a1aHR0cHM6Ly9tYXBzLmdvb2dsZS5jb20v"));
    });

    QToolButton *bouton4 = new QToolButton(this);
    bouton4 ->setAutoRaise(true);
   bouton4 ->setFixedSize(160,160);
   bouton4 ->setIcon(QIcon(":/images/Yango-icon.jpg"));
   bouton4 ->setIconSize(QSize(100,100));
    bouton4 ->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    connect(bouton4 , &QToolButton::clicked, this, [](){
        QDesktopServices::openUrl(QUrl("https://www.bing.com/ck/a?!&&p=2ff650cd2ceed99cb4737fc6ff8910c2d1324c5bc69d3f28070907e5db2c0483JmltdHM9MTc4NTk3NDQwMA&ptn=3&ver=2&hsh=4&fclid=380fe9a4-9b62-69ec-3f1c-fe099a2f68bf&psq=yango&u=a1aHR0cHM6Ly95YW5nby5jb20vZnJfY20v"));
    });

    //pour alliner les boutons cliquables d'applications de maniere horizontale
    QHBoxLayout *boutons = new QHBoxLayout(this);
    boutons->addStretch();
    boutons->addWidget(bouton1, 0);
    boutons->addWidget(bouton2, 0);
    boutons->addWidget(bouton3, 0);
    boutons->addWidget(bouton4, 0);
    boutons->addStretch();

    //permet d'empiler verticalement les elements en ordre d'arrivee dans le layout de la frame
    QVBoxLayout *frameLayout = new QVBoxLayout(monCadre);
    frameLayout->addWidget(logoLabel);
    frameLayout->addSpacing(20);
    frameLayout->addWidget(paragraphe);
    frameLayout->addSpacing(60);
    frameLayout->addLayout(boutons);
    frameLayout->addStretch();
}

void LinksWindow::onPrecedentClicked()
{

    //Revient a/Ouvre la premiere fenetere(acceuil)
    FormWindow *link = new FormWindow();
    //libere la memoire a la fermeture
    link->setAttribute(Qt::WA_DeleteOnClose);
    link->show();

    this->close();
}