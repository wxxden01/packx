# INSTALL COMMANDE ROADMAP!


## Prérequis:

### 1 - Avoir accés à un miroir
    - Le setup si besoin
    - Ajouter l'url du mirroir dans le fichier ~/.packx/mirror.txt

    - Sur le mirroir:
        - Fichier `repo.db`, format : test|8.6.2|test-8.6.2.tar.xz|HASH|SIZE

    Arbo:
    /x86_64/
    ├── repo.db
    └── pkgs/
        ├── nano-8.6.2.tar.xz
        ├── htop-3.4.1.tar.xz
        └── ...

### 2 - POUR CHAQUE PAQUET:
    - Télécharger l'archive
    - Créer le fichier YAML (packx.yml)
    - Reconstruire l'archive
    - Upload sur le miroir
    - Créer la signature 

---

## Phase 1:
- [x] Vérifier que le paquet n'est pas déjà installé
- [x] Ajouter ~/.packx/cache, ~/.packx/pkgs
- [x] Vérifier que l'archive est sur le mirroir
- [ ] Download depuis le miroir
- [ ] Vérifier avant tout le hash
- [ ] Faire l'installation
- [ ] l'inscrire dans le fichier ~/.packx/installed.db (format : nom|version|size)
---

## Comportement de la commande:
``` bash
packx install test
        │
        ▼
récupérer repo.db
        │
        ▼
trouver test
        │
        ▼
récupérer test-8.6.2.tar.xz
        │
        ▼
récupérer test-8.6.2.tar.xz.sig
        │
        ▼
vérifier la signature
        │
        ├── ❌ invalide → STOP
        │
        ▼
extraire
        │
        ▼
lire packx.yml
        │
        ▼
installer
        │
        ▼
installed.db```