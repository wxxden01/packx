#!/bin/bash
# Créer les dossiers système
mkdir -p /etc/packx/certs
mkdir -p /usr/share/packx/keyrings
mkdir -p /var/lib/packx
mkdir -p /var/cache/packx

# Copier les fichiers de config depuis le projet
cp ./config_packx/mirror/mirror.txt /etc/packx/mirror.conf
cp -r ./config_packx/certificates/* /etc/packx/certs/
cp ./config_packx/local_db/installed.db /var/lib/packx/

# Importer la clé GPG dans le dossier partagé
gpg --homedir /usr/share/packx/keyrings --batch --yes --import ./config_packx/keys/packx-public-key.asc

# Donner les bonnes permissions
chmod 755 /etc/packx
chmod 755 /usr/share/packx/keyrings
chmod 755 /var/lib/packx
chmod 1777 /var/cache/packx

# Installer le binaire
cp build/packx /usr/local/bin/packx
chmod 755 /usr/local/bin/packx