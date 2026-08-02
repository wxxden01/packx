# 🦖 PACKX - Package Manager (Roadmap)

## 📌 Phase 0 — Base CLI (fondations)
- [x] Parser les arguments (`argc`, `argv`)
- [x] Gérer une commande simple (`rex test`)
- [x] Créer une struct `command_packx`
- [x] Implémenter un système de routing des commandes
- [x] Séparer `commands.c` / `commands.h`
- [x] Organiser le projet (`src/`, `include/`, `build/`)
- [x] Makefile fonctionnel

---

## ⚙️ Phase 1 — Commandes essentielles
- [x] Ajouter `packx help` (liste des commandes)
- [ ] Ajouter `packx version`
<!-- manque la structure des paquets de Packx dans lequel on aura cette info ainsi que d'autres -->
- [x] Ajouter `pacck search` (fair la fonction de vérif indépendamment pour l'utiliser dans d'autre fonction)
- [x] Ajouter gestion des erreurs propre
- [x] Ajouter descriptions dans `commands[]`
- [x] Améliorer les messages CLI

---

## 📦 Phase 2 — Gestion de paquets (simulation)
- [ ] Implémenter `packx install <pkg>`
- [ ] Implémenter `packx remove <pkg>`
- [ ] Implémenter `packx list`
- [ ] Créer une base locale (fichier `.packx/db`)
- [ ] Stocker les paquets installés

---

## 🗂️ Phase 3 — Système de stockage
- [ ] Créer dossier `~/.packx/`
- [ ] Créer fichier `installed.json` ou `.db`
- [ ] Lire/écrire des fichiers en C
- [ ] Parser données (JSON ou format simple)

---

## 🌐 Phase 4 — Sources & téléchargement
- [ ] Ajouter notion de "repo"
- [ ] Télécharger un fichier (libcurl ou wget)
- [ ] Parser une liste de paquets distante
- [ ] Implémenter `packx update`

---

## 🔍 Phase 5 — Résolution de dépendances
- [ ] Ajouter dépendances entre paquets
- [ ] Vérifier si un paquet est déjà installé
- [ ] Installer dépendances automatiquement
- [ ] Détecter conflits

---

## 🧪 Phase 6 — Qualité & robustesse
- [ ] Gestion des erreurs complète
- [ ] Codes de retour cohérents
- [ ] Logs
- [ ] Tests unitaires

---

## 🚀 Phase 7 — UX & CLI avancé
- [ ] Flags (`--help`, `--force`, `--yes`)
- [ ] Couleurs dans le terminal
- [ ] Barre de progression
- [ ] Auto-complétion bash

---

## 🔌 Phase 8 — Architecture avancée
- [ ] Modulariser chaque commande (`cmd/*.c`)
- [ ] Système de plugins
- [ ] Chargement dynamique des commandes

---

## 📦 Phase 9 — Packaging
- [ ] Installer `packx` dans `/usr/bin`
- [ ] Créer un `.deb` ou `.pkg`
- [ ] Script d’installation

---

## 🧠 Bonus (niveau expert)
- [ ] Multi-threading (install parallèle)
- [ ] Cache local
- [ ] Vérification d’intégrité (hash)
- [ ] Signature des paquets