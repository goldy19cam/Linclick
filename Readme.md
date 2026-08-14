# Documentation LINKCLICK

**Projet :** LINKCLICK
**Client :** SOCADEL
**Technologie :** Qt / C++
**Base de données :** SQLite
**Auteur :** Tami Nana Savionault Goldy
**Date :** Août 2026

---

## Sommaire

1. [Présentation générale](#1-présentation-générale)
2. [Guide utilisateur](#2-guide-utilisateur)
3. [Documentation technique](#3-documentation-technique)
4. [Base de données](#4-base-de-données)
5. [Installation et compilation](#5-installation-et-compilation)
6. [Évolutions possibles](#6-évolutions-possibles)

---

## 1. Présentation générale

LINKCLICK est une application de bureau développée en **Qt/C++** pour le compte de **SOCADEL**. Elle permet à un utilisateur de :

- S'inscrire via un formulaire de demande (nom, téléphone, etc.) ;
- Enregistrer ses informations dans une base de données **SQLite** locale ;
- Accéder à une fenêtre **portail de liens** une fois inscrit.

L'application est composée de deux fenêtres principales :

| Fenêtre | Rôle |
|---|---|
| **Formulaire d'inscription** | Saisie et validation des données utilisateur |
| **Portail de liens** | Accès aux liens/ressources après inscription |

---

## 2. Guide utilisateur

### 2.1 Lancer l'application

Double-cliquer sur l'exécutable `LINKCLICK.exe` (ou lancer le binaire compilé selon l'OS).

### 2.2 Remplir le formulaire d'inscription

1. Ouvrir l'application : la fenêtre d'inscription s'affiche en premier.
2. Renseigner les champs demandés :
   - **Nom** : lettres uniquement (validé automatiquement).
   - **Téléphone** : format numérique validé automatiquement.
   - **Date/Heure** : horodatage de la demande (rempli automatiquement).
3. Cliquer sur **SUIVANT**.
4. Si un champ est incorrect, un message d'erreur s'affiche et le champ concerné est mis en évidence.

> ⚠️ Les champs Nom et Téléphone utilisent une validation stricte (regex). Toute entrée non conforme est bloquée avant l'enregistrement.

### 2.3 Accéder au portail de liens

Une fois  les données enregistrées en base et le formulaire validé, l'application ouvre automatiquement la fenêtre **Portail de liens**, listant les ressources disponibles pour l'utilisateur.

### 2.4 Erreurs courantes

| Problème | Cause probable | Solution |
|---|---|---|
| Le formulaire ne se valide pas | Champ Téléphone mal formaté | Vérifier que la longueur minimale du numero (sans le `+`) est de 9 chiffres  |
| Rien ne s'enregistre en base | Connexion SQLite échouée | Vérifier que le fichier `.db` existe et est accessible en écriture |
| L'icône de l'app ne s'affiche pas | Ressource `.qrc` mal liée | Voir section technique 3.4 |

---

## 3. Documentation technique

### 3.1 Architecture générale

```
LINKCLICK/
├── LINKCLICK.pro
├── main.cpp
├── formulaire/
│   ├── formwindow.h
│   ├── formwindow.cpp
│   └── mainwindow.ui (si Qt Designer utilisé)
├── portail/
│   ├── linkswindow.h
│   └── linkswindow.cpp
├── database/
│   └── db.sqlite
├── resources/
│   ├── ressources.qrc
```

### 3.2 Interface du formulaire

- **Layout** : `QFormLayout` pour l'alignement label/champ, imbriqué dans un `QVBoxLayout` global et des `QHBoxLayout` pour les boutons.
- **Centrage** : le formulaire est centré dans la fenêtre via des espaceurs (`addStretch()`) ou un layout englobant.
- **Validation des champs** :
  - Nom : `QRegularExpressionValidator` avec une expression du type `^[A-Za-zÀ-ÖØ-öø-ÿ ]*$`.
  - Téléphone : `QRegularExpressionValidator` avec une expression du type `^[0-9+ ]*$`.
- **Horodatage** : `QDateTimeEdit` utilisé pour capturer la date/heure de la demande.

### 3.3 Style (QSS)

L'application utilise une feuille de style QSS pour un fond de couleur blanche;

Exemple de structure QSS utilisée :
```css
QWidget {
    setStyleSheet("background-color: #ffffff;");
}
```

### 3.4 Icônes et ressources (.qrc)

Les icônes sont intégrées via un fichier `.qrc` référencé dans le fichier projet `.pro`. Point de vigilance : **éviter les références dupliquées** du même `.qrc` dans le `.pro`, source d'erreurs de compilation rencontrées durant le développement.

```qmake
RESOURCES += \resources.qrc
```

### 3.5 Connexion à la base de données

La connexion SQLite est initialisée au démarrage de l'application via `QSqlDatabase`, puis les insertions/lectures se font via `QSqlQuery`.

```cpp
 QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("demandes.db");
    if (!db.open()){
        QMessageBox::critical(nullptr, "Erreur base de donnees", "Impossible d'ouvrir la base :" + db.lastError().text());
        return false ;
    }
```

**Point de vigilance qmake** : le module SQL Qt doit être explicitement ajouté dans le fichier `.pro` pour éviter les erreurs de linkage :

```qmake
QT +=  core gui sql widgets
```

---

## 4. Base de données

### 4.1 Table principale (exemple)

| Champ | Type | Description |
|---|---|---|
| `id` | INTEGER PRIMARY KEY AUTOINCREMENT | Identifiant unique |
| `nom` | TEXT | Nom de l'utilisateur |
| `telephone` | TEXT | Numéro de téléphone |
| `date_demande` | DATETIME | Horodatage de la demande |
|`nombre_demandes` | INTEGER | nombre total de demandes |

### 4.2 Requête d'insertion type

```cpp
QSqlQuery query;
    query.prepare("INSERT INTO demandes (nom, numero, date_demande, nombre_demandes)"
                  "VALUES (:nom, :numero, :date, :nb)");
    query.bindValue(":nom", nomEdit->text().trimmed());
    query.bindValue(":numero", numeroEdit->text().trimmed());
    query.bindValue(":date", dateTimeEdit->dateTime().toString("yyyy-MM-dd HH:mm:ss"));
    query.bindValue(":nb", nombreDemandesSpin->value());
query.exec();
```

---

## 5. Installation et compilation

### Prérequis
- Qt 6.x (Widgets, SQL)
- qmake (fourni avec Qt)
- Compilateur C++ compatible C++17

### Étapes

Le projet est versionné sur Git. Pour le récupérer et le compiler :

```bash
git clone <url_du_repo_linkclick>
cd LINKCLICK
qmake LINKCLICK.pro
make
```

Sous Qt Creator, il suffit d'ouvrir directement le fichier `LINKCLICK.pro` et de lancer la build+execute (Ctrl+R).

L'exécutable est généré dans le dossier de build configuré par Qt Creator (ex. `build-LINKCLICK-Desktop-Debug/`).

---

## 6. Évolutions possibles

- Ajout d'une authentification (login/mot de passe) avant l'accès au portail.
- Export des demandes enregistrées (CSV/PDF).
- Passage à une base de données distante (MySQL/PostgreSQL) pour un usage multi-poste.

---

*Document généré pour le projet LINKCLICK — à mettre à jour au fil de l'avancement du développement.*