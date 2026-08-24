//Point d'entree du programme: initialise l'application , la base de donnees et affiche la fenetere du formulaire
#include <QApplication>
#include <QIcon>
#include <QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QWidget>
#include "formwindow.h"

//initialise la connection SQLite et cree la table si elle n'existe pas
bool initDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    //fichier cree automatiquement a cote de l'executable
    db.setDatabaseName("demandes.db");
    if (!db.open()){
        QMessageBox::critical(nullptr, "Erreur base de donnees", "Impossible d'ouvrir la base :" + db.lastError().text());
        return false ;
    }

    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS demandes ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "nom TEXT NONT NULL COLLATE NOCASE,"
               "numero TEXT NOT NULL,"
               "date_demande TEXT NOT NULL)");

    //ajout de la deuxieme table
    query.exec("CREATE TABLE IF NOT EXISTS register("
               "nom TEXT NOT NULL COLLATE NOCASE,"
               "numero TEXT NOT NULL,"
              "nombre_demandes INTEGER NOT NULL,"
               "unique(nom, numero))");

    return true;
}
int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/images/linkclick_icon_1024.png"));

    if(!initDatabase())
        return -1;

    FormWindow window;
    window.setWindowTitle("LINKCLICK");
    //permet de modifier la taille de la fenetre principale
    window.resize(750, 500);
    window.show();

    return app.exec();
}