# Nom du binaire
NAME = packx

# Dossiers d'installation
DESTDIR ?=
PREFIX ?= /usr/local
BINDIR = $(DESTDIR)$(PREFIX)/bin
SYSCONFDIR = $(DESTDIR)/etc/packx
DATADIR = $(DESTDIR)/usr/share/packx
STATEDIR = $(DESTDIR)/var/lib/packx
CACHEDIR = $(DESTDIR)/var/cache/packx

# Dossiers de build
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
SRC_DIR = src
BIN = $(BUILD_DIR)/$(NAME)

# Compilateur et Flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude -g $(shell pkg-config --cflags gpgme)
LDLIBS = -lcurl -lcrypto $(shell pkg-config --libs gpgme)

# Outils système
INSTALL = install
INSTALL_DIR = $(INSTALL) -m 755 -d
INSTALL_DATA = $(INSTALL) -m 644
INSTALL_BIN = $(INSTALL) -m 755

# Sources et Objets
SRCS = $(shell find $(SRC_DIR) -name "*.c")
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

.PHONY: all clean fclean re run install uninstall

all: $(BIN)

# Link
$(BIN): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(OBJS) -o $(BIN) $(LDLIBS)

# Compilation
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Installation
install: all
	# Arborescence
	$(INSTALL_DIR) $(SYSCONFDIR)/certs
	$(INSTALL_DIR) $(DATADIR)/keyrings
	$(INSTALL_DIR) $(STATEDIR)
	$(INSTALL) -m 1777 -d $(CACHEDIR)
	$(INSTALL_DIR) $(BINDIR)

	# Fichiers de configuration et données
	$(INSTALL_DATA) ./config_packx/mirror/mirror.txt $(SYSCONFDIR)/mirror.conf
	if [ -d ./config_packx/certificates ] && [ $$(ls -A ./config_packx/certificates 2>/dev/null) ]; then \
		$(INSTALL_DATA) ./config_packx/certificates/* $(SYSCONFDIR)/certs/ ; \
	fi
	$(INSTALL_DATA) ./config_packx/local_db/installed.db $(STATEDIR)/

	# Importation de la clé GPG
	gpg --homedir $(DATADIR)/keyrings --batch --yes --import ./config_packx/keys/packx-public-key.asc

	# Binaire
	$(INSTALL_BIN) $(BIN) $(BINDIR)/$(NAME)

# Désinstallation
uninstall:
	rm -f $(BINDIR)/$(NAME)
	rm -rf $(SYSCONFDIR)
	rm -rf $(DATADIR)
	rm -rf $(STATEDIR)
	rm -rf $(CACHEDIR)

# Nettoyage
clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(BUILD_DIR)

re: fclean all

run: all
	./$(BIN)