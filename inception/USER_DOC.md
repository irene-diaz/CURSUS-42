# User Documentation

## Introduction

This document explains how to use and administer the Inception infrastructure.

The project provides a small web stack composed of three services:

* **NGINX**: receives HTTPS requests and serves as the entry point to the website.
* **WordPress**: provides the website and its administration interface.
* **MariaDB**: stores the WordPress database.

The services communicate through a private Docker network.

## Starting the Project

Open a terminal and go to the project's `srcs` directory:

```bash
cd ~/inception/srcs
```

Start all services in the background:

```bash
docker-compose up -d
```

Check that the services are running:

```bash
docker-compose ps
```

The `mariadb`, `wordpress` and `nginx` containers should have a running status.

## Stopping the Project

To stop the containers:

```bash
docker-compose down
```

This stops and removes the containers but does not remove the persistent data stored in the volumes.

The project can be started again with:

```bash
docker-compose up -d
```

## Accessing the Website

The website is available through HTTPS at:

```text
https://idiaz-ca.42.fr
```

NGINX listens on port `443` and forwards PHP requests to the WordPress container.

The project uses a self-signed SSL certificate, so the browser may display a security warning when accessing the website.

For local testing, the certificate can be accepted in the browser.

## Accessing the Administration Panel

The WordPress administration panel is available at:

```text
https://idiaz-ca.42.fr/wp-admin
```

The administrator must use the WordPress administrator account created during the WordPress installation.

## Credentials

The project uses different types of configuration and credentials.

Non-sensitive configuration is stored in:

```text
srcs/.env
```

It contains values such as:

```text
DOMAIN_NAME
MYSQL_DATABASE
MYSQL_USER
```

Database passwords are stored separately as Docker Secrets:

```text
secrets/db_root_password.txt
secrets/db_password.txt
```

These files are not stored directly in the Docker Compose configuration.

Inside the containers, Docker makes the secrets available under:

```text
/run/secrets/
```

For security reasons, passwords should not be committed to the Git repository.

## Checking the Services

To check whether all containers are running:

```bash
docker-compose ps
```

To check the NGINX configuration:

```bash
docker exec nginx nginx -t
```

To inspect the Docker network:

```bash
docker network inspect srcs_inception
```

The three services should appear as connected containers:

```text
mariadb
wordpress
nginx
```

To check the WordPress PHP-FPM process:

```bash
docker exec wordpress ps aux
```

PHP-FPM should be running and listening on port `9000`.

To check the NGINX SSL configuration:

```bash
docker exec nginx nginx -T | grep -E "listen|ssl_certificate"
```

The configuration should contain the HTTPS listener and the SSL certificate paths.

## Checking Persistent Data

The project's Docker volumes can be listed with:

```bash
docker volume ls
```

The project uses:

* `srcs_wordpress_data` for WordPress files.
* `srcs_mariadb_data` for MariaDB data.

The MariaDB volume uses the host directory:

```text
/home/idiaz-ca/data/database
```

The data remains available after the containers are stopped or recreated.

## Troubleshooting

If a service is not running, check its status:

```bash
docker-compose ps
```

Then inspect its logs:

```bash
docker-compose logs <service>
```

For example:

```bash
docker-compose logs nginx
docker-compose logs wordpress
docker-compose logs mariadb
```

If NGINX reports a configuration problem:

```bash
docker exec nginx nginx -t
```

If WordPress cannot connect to MariaDB, first verify that both containers are running and connected to the same Docker network:

```bash
docker network inspect srcs_inception
```

The WordPress container should be able to resolve the MariaDB service name:

```bash
docker exec wordpress getent hosts mariadb
```
