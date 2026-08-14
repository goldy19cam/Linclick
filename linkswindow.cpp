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
    QToolButton *boutonSocadel = new QToolButton(this);
    boutonSocadel->setAutoRaise(true);//enleve les bordures des boutons
    boutonSocadel->setText("SOCADEL");
    boutonSocadel->setFixedSize(160,160);//taille du bouton
    boutonSocadel->setIcon(QIcon(":/images/SOCADEL.png"));
    boutonSocadel->setIconSize(QSize(100,80));//taille de l'icone
    boutonSocadel->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);//pour positionner l'icone au dessus du nom de l'application
    connect(boutonSocadel, &QToolButton::clicked, this, [](){
        QDesktopServices::openUrl(QUrl("https://my.socadel.cm/"));
    });

    QToolButton *boutonTelegram = new QToolButton(this);
    boutonTelegram->setAutoRaise(true);
    boutonTelegram->setFixedSize(160,160);
    boutonTelegram->setText("TELEGRAM");
    boutonTelegram->setIcon(QIcon(":/images/Telegram-icon.png"));
    boutonTelegram->setIconSize(QSize(80,80));
    boutonTelegram->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    connect(boutonTelegram, &QToolButton::clicked, this, [](){
        QDesktopServices::openUrl(QUrl("https://www.bing.com/ck/a?!&&p=cf7a7337d8314d326d8bfc0732504f0bc9465ed2c50591eb0ae196a1f93871bdJmltdHM9MTc4NjA2MDgwMA&ptn=3&ver=2&hsh=4&fclid=2be59cb9-d541-6720-3a29-8b17d499665e&psq=telegram&u=a1aHR0cHM6Ly9kZXNrdG9wLnRlbGVncmFtLm9yZy8"));
    });

    QToolButton *boutonGmap = new QToolButton(this);
    boutonGmap->setAutoRaise(true);
    boutonGmap->setFixedSize(160,160);
    boutonGmap->setText("GOOGLE MAPS");
    boutonGmap->setIcon(QIcon(":/images/Maps-icon.png"));
    boutonGmap->setIconSize(QSize(80,80));
    boutonGmap->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    connect(boutonGmap, &QToolButton::clicked, this, [](){
        QDesktopServices::openUrl(QUrl("https://www.bing.com/ck/a?!&&p=6bfca3c64c38d0dcfabc5b90be20f38237d3b16b78820ff67f9038417ce27943JmltdHM9MTc4NTk3NDQwMA&ptn=3&ver=2&hsh=4&fclid=380fe9a4-9b62-69ec-3f1c-fe099a2f68bf&psq=google+maps&u=a1aHR0cHM6Ly9tYXBzLmdvb2dsZS5jb20v"));
    });

    QToolButton *boutonYango = new QToolButton(this);
    boutonYango->setAutoRaise(true);
    boutonYango->setFixedSize(160,160);
    boutonYango->setText("YANGO");
    boutonYango->setIcon(QIcon(":/images/Yango-icon.jpg"));
    boutonYango->setIconSize(QSize(80,80));
    boutonYango->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    connect(boutonYango, &QToolButton::clicked, this, [](){
        QDesktopServices::openUrl(QUrl("https://www.bing.com/ck/a?!&&p=2ff650cd2ceed99cb4737fc6ff8910c2d1324c5bc69d3f28070907e5db2c0483JmltdHM9MTc4NTk3NDQwMA&ptn=3&ver=2&hsh=4&fclid=380fe9a4-9b62-69ec-3f1c-fe099a2f68bf&psq=yango&u=a1aHR0cHM6Ly95YW5nby5jb20vZnJfY20v"));
    });

    QToolButton *boutonEdge = new QToolButton(this);
    boutonEdge->setAutoRaise(true);
    boutonEdge->setFixedSize(160,160);
    boutonEdge->setText("MICROSOFT EDGE");
    boutonEdge->setIcon(QIcon(":/images/Edge-icon.jpg"));
    boutonEdge->setIconSize(QSize(80,80));
    boutonEdge->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    connect(boutonEdge, &QToolButton::clicked, this, [](){
        QProcess::startDetached("C:/Program Files (x86)/Microsoft/Edge/Application/msedge.exe");
    });

    QToolButton *boutonChrome = new QToolButton(this);
    boutonChrome->setAutoRaise(true);
    boutonChrome->setFixedSize(160,160);
    boutonChrome->setText("CHROME");
    boutonChrome->setIcon(QIcon(":/images/Chrome-icon.png"));
    boutonChrome->setIconSize(QSize(80,80));
    boutonChrome->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    connect(boutonChrome, &QToolButton::clicked, this, [](){
        QProcess::startDetached("C:/Program Files (x86)/Google/Chrome/Application/chrome.exe");
    });

    QToolButton *boutonVlc = new QToolButton(this);
    boutonVlc->setAutoRaise(true);
    boutonVlc->setFixedSize(160,160);
    boutonVlc->setText("VLC");
    boutonVlc->setIcon(QIcon(":/images/VLC_icon.png"));
    boutonVlc->setIconSize(QSize(80,80));
    boutonVlc->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    connect(boutonVlc, &QToolButton::clicked, this, [](){
        QProcess::startDetached("C:/Program Files (x86)/VideoLAN/VLC/vlc.exe");
    });

    QToolButton *boutonVscode = new QToolButton(this);
    boutonVscode->setAutoRaise(true);
    boutonVscode->setFixedSize(160,160);
    boutonVscode->setText("VS CODE");
    boutonVscode->setIcon(QIcon(":/images/VSCode-icon.png"));
    boutonVscode->setIconSize(QSize(80,80));
    boutonVscode->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    connect(boutonVscode, &QToolButton::clicked, this, [](){
        QProcess::startDetached("C:/Users/user/AppData/Local/Programs/Microsoft VS Code/Code.exe");
    });

    //pour alliner les boutons cliquables d'applications de maniere horizontale
    QHBoxLayout *boutons = new QHBoxLayout(this);
    boutons->addStretch();
    boutons->addWidget(boutonSocadel, 0);
    boutons->addWidget(boutonTelegram, 0);
    boutons->addWidget(boutonGmap, 0);
    boutons->addWidget(boutonYango, 0);
    boutons->addStretch();

    QHBoxLayout *boutons2 = new QHBoxLayout(this);
    boutons2->addStretch();
    boutons2->addWidget(boutonEdge, 0);
    boutons2->addWidget(boutonChrome, 0);
    boutons2->addWidget(boutonVlc, 0);
    boutons2->addWidget(boutonVscode, 0);
    boutons2->addStretch();

    //permet d'empiler verticalement les elements en ordre d'arrivee dans le layout de la frame
    QVBoxLayout *frameLayout = new QVBoxLayout(monCadre);
    frameLayout->addWidget(logoLabel);
    frameLayout->addSpacing(20);
    frameLayout->addWidget(paragraphe);
    frameLayout->addSpacing(30);
    frameLayout->addLayout(boutons2);
    frameLayout->addSpacing(10);
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