
Debian
====================
This directory contains files used to package BoldTechnologyCommerceUgandad/BoldTechnologyCommerceUganda-qt
for Debian-based Linux systems. If you compile BoldTechnologyCommerceUgandad/BoldTechnologyCommerceUganda-qt yourself, there are some useful files here.

## BoldTechnologyCommerceUganda: URI support ##


BoldTechnologyCommerceUganda-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install BoldTechnologyCommerceUganda-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your BoldTechnologyCommerceUganda-qt binary to `/usr/bin`
and the `../../share/pixmaps/BoldTechnologyCommerceUganda128.png` to `/usr/share/pixmaps`

BoldTechnologyCommerceUganda-qt.protocol (KDE)

