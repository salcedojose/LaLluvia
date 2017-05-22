#!/bin/bash 

# Instalar php en conjunto con apache y mysql para servidor.
apt-get install lamp-server^
apt-get install php mysql-server apache2 libapache2-mod-php
# Instalar paquetes necesarios para python y python+mysql.
apt-get install python-pip python-mysqldb

# Dar derechos de escritura y de lectura a todos los usuarios.
# (Peligroso para produccion, NO HAGAN ESTO SEGUIDO).
chmod -R 777 /var/www/

# Crear archivo de prueba para php y abrir.
ARCHIVO="/var/www/html/info.php"
echo "<?php phpinfo(); ?>" > $ARCHIVO
service apache2 restart

# Instalar libreria necesaria de python para comunicacion serial.
pip install pyserial
