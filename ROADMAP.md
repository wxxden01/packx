# PACKX - Package Manager (Roadmap)

## Phase 0 — Base CLI (fondations)
- [x] Parser les arguments (`argc`, `argv`)
- [x] Gérer une commande simple (`rex test`)
- [x] Créer une struct `command_packx`
- [x] Implémenter un système de routing des commandes
- [x] Séparer `commands.c` / `commands.h`
- [x] Organiser le projet (`src/`, `include/`, `build/`)
- [x] Makefile fonctionnel

---

## Phase 1 — Commandes essentielles
- [x] Ajouter `packx help` (liste des commandes)
- [x] Ajouter `packx version`
- [x] Ajouter `pacck search` (fair la fonction de vérif indépendamment pour l'utiliser dans d'autre fonction)
- [x] Ajouter gestion des erreurs propre
- [x] Ajouter descriptions dans `commands[]`
- [x] Améliorer les messages CLI

---

## Phase 2 — Gestion de paquets
- [ ] Implémenter  `packx install <pkg>` ([ROADMAP](/src/cmd/install.md))
- [ ] Implémenter `packx remove <pkg>`
- [ ] Implémenter `packx list`
- [x] Créer une base locale (fichier `.packx/db`)
- [x] Stocker les paquets installés `.packx/pkgs`

---

## Phase 3 — Système de stockage
- [x] Créer dossier `~/.packx/`
- [x] Créer fichier `installed.json` ou `.db`
- [x] Créer `init.c` check de l'arborescence
- [x] Lire/écrire des fichiers en C
- [x] Parser les données de la db

---

## Phase 4 — Résolution de dépendances
- [ ] Ajouter les dépendances entre paquets
- [ ] Installer les dépendances automatiquement
- [ ] Détecter les conflits

---

## Phase 5 — Qualité & robustesse
- [ ] Gestion des erreurs complète
- [ ] Logs
- [ ] Tests unitaires

---

## Phase 6 — UX & CLI avancé
- [ ] Flags (`--help`, `--force`, `--yes`)
- [ ] Couleurs dans le terminal
- [ ] Barre de progression
- [ ] Auto-complétion bash

---

## Phase 7 — Architecture avancée
- [ ] Modulariser chaque commande (`cmd/*.c`)
- [ ] Système de plugins
- [ ] Chargement dynamique des commandes

---

## Phase 8 — Packaging
- [ ] Installer `packx` dans `/usr/bin`
- [ ] Créer un `.deb` ou `.pkg`
- [ ] Script d’installation

---

## Bonus
- [ ] Multi-threading (install parallèle)

# Pas besoin d'IA, un cerveau suffit!