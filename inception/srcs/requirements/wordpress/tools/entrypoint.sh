#!/bin/sh

mkdir -p /var/www/html

if [ ! -f /var/www/html/wp-config.php ]; then
    echo "Preparing WordPress..."

    cd /tmp
    curl -O https://wordpress.org/latest.tar.gz
    tar -xzf latest.tar.gz
    cp -a wordpress/. /var/www/html/
    rm -rf wordpress latest.tar.gz

    DB_PASSWORD=$(cat /run/secrets/db_password)

    cp /var/www/html/wp-config-sample.php /var/www/html/wp-config.php

    sed -i "s/database_name_here/${MYSQL_DATABASE}/" /var/www/html/wp-config.php
    sed -i "s/username_here/${MYSQL_USER}/" /var/www/html/wp-config.php
    sed -i "s/password_here/${DB_PASSWORD}/" /var/www/html/wp-config.php
    sed -i "s/localhost/mariadb/" /var/www/html/wp-config.php
fi

exec php-fpm8.2 -F
