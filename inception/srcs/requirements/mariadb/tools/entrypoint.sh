#!/bin/sh

mkdir -p /run/mysqld
chown mysql:mysql /run/mysqld

if [ ! -d "/var/lib/mysql/mysql" ]; then
    echo "Initializing MariaDB..."

    mariadb-install-db --user=mysql --datadir=/var/lib/mysql

    ROOT_PASSWORD=$(cat /run/secrets/db_root_password)
    DB_PASSWORD=$(cat /run/secrets/db_password)

    mariadbd --user=mysql --skip-networking --socket=/run/mysqld/mysqld.sock &
    pid="$!"

    until mariadb-admin --socket=/run/mysqld/mysqld.sock ping --silent; do
        sleep 1
    done

    mariadb --socket=/run/mysqld/mysqld.sock <<-EOSQL
        ALTER USER 'root'@'localhost' IDENTIFIED BY '${ROOT_PASSWORD}';
        CREATE DATABASE IF NOT EXISTS \`${MYSQL_DATABASE}\`;
        CREATE USER IF NOT EXISTS '${MYSQL_USER}'@'%' IDENTIFIED BY '${DB_PASSWORD}';
        GRANT ALL PRIVILEGES ON \`${MYSQL_DATABASE}\`.* TO '${MYSQL_USER}'@'%';
        FLUSH PRIVILEGES;
EOSQL

    mariadb-admin --socket=/run/mysqld/mysqld.sock -u root -p"${ROOT_PASSWORD}" shutdown

    wait "$pid"
fi

exec mariadbd --user=mysql --console
