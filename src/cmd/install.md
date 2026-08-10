# INSTALL COMMANDE ROADMAP!


## Prérequis:

### 1 - Avoir accés un miroir
    - Le setup si besoin
    - Ajouter l'url du mirroir dans le fichier ~/.packx/mirror.txt
### 2 - POUR CHAQUE PAQUET:
- Télécharger l'archive + le hash
- Créer le fichier YAML (packx.yml)
- Reconstruire l'archive
- Upload sur le miroir

---

## Phase 1:
- [ ] Vérifier que le paquet n'est pas déjà installé
- [ ] Ajouter ~/.packx/cache, ~/.packx/pkgs
- [ ] Download depuis le miroir
- [ ] Vérifier avant tout le hash
- [ ] Faire l'installation
- [ ] l'inscrire dans le fichier ~/.packx/installed.db (format : nom|version|size)