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
    ├── repo.db.sig
    └── pkgs/
        ├── test1-8.6.2.tar.xz
        ├── example2-3.4.1.tar.xz
        └── ...

### 2 - POUR CHAQUE PAQUET:
    - Télécharger l'archive
    - Créer le fichier YAML (packx.yml)
    - Reconstruire l'archive
    - Upload sur le miroir
    - Ajouter l'archive dans le fichier `repo.db`
    - Recréer la signature de `repo.db`

---

## Phase 1:
- [x] Vérifier que le paquet n'est pas déjà installé
- [x] Ajouter ~/.packx/cache, ~/.packx/pkgs
- [x] Vérifier que l'archive est sur le mirroir
- [ ] Download depuis le miroir
- [ ] Vérifier la signature de la db
- [ ] Vérifier avant tout le hash
- [ ] Faire l'installation
- [ ] l'inscrire dans le fichier ~/.packx/installed.db (format : nom|version|nom-v.tar.xz|HASH|size)
---

## Comportement de la commande:
``` bash
packx install test
        │
        ▼
récupérer repo.db et repo.db.sig
        │
        ▼
vérifier la signature
        │
        ├── ❌ invalide → STOP
        │
        ▼
trouver test
        │
        ▼
récupérer test-8.6.2.tar.xz
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
installed.db
```