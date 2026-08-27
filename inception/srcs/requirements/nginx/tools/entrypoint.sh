#!/bin/sh

mkdir -p /etc/nginx/ssl

if [ ! -f /etc/nginx/ssl/inception.crt ]; then
    echo "Generating SSL certificate..."

    openssl req -x509 -nodes -days 365 \
        -newkey rsa:2048 \
        -keyout /etc/nginx/ssl/inception.key \
        -out /etc/nginx/ssl/inception.crt \
        -subj "/C=ES/ST=Madrid/L=Madrid/O=42/OU=Inception/CN=idiaz-ca.42.fr"
fi

exec nginx -g "daemon off;"
