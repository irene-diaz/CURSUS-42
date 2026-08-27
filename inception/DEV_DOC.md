# Developer Documentation

## Introduction

This document explains how to set up, build, run and manage the Inception project from a development environment.

The project uses Docker Compose to create three services:

```text
NGINX
  |
  v
WordPress + PHP-FPM
  |
  v
MariaDB
```

All services communicate through the Docker network `inception`.

## Prerequisites

The development environment requires:

* Docker
* Docker Compose
* Git
* A Linux environment capable of running Docker

The project was developed using Debian.

## Project Structure

The main project structure is:

```text
inception/
├── README.md
├── USER_DOC.md
├── DEV_DOC.md
├── Makefile
├── secrets/
│   ├── db_root_password.txt
│   └── db_password.txt
└── srcs/
    ├── .env
    ├── docker-compose.yml
    └── requirements/
        ├── mariadb/
        │   ├── Dockerfile
        │   ├── conf/
        │   │   └── 50-server.cnf
        │   └── tools/
        │       └── entrypoint.sh
        │
        ├── wordpress/
        │   ├── Dockerfile
        │   └── tools/
        │       └── entrypoint.sh
        │
        └── nginx/
            ├── Dockerfile
            ├── conf/
            │   └── nginx.conf
            └── tools/
                └── entrypoint.sh
```

## Configuration

### Environment Variables

The main non-sensitive configuration is stored in:

```text
srcs/.env
```

The current configuration contains:

```text
DOMAIN_NAME=idiaz-ca.42.fr
MYSQL_DATABASE=wordpress
MYSQL_USER=wpuser
```

These values are used by Docker Compose and the service entrypoints.

### Docker Secrets

Database passwords are stored outside the `.env` file:

```text
secrets/db_root_password.txt
secrets/db_password.txt
```

Docker Compose mounts them inside the appropriate containers under:

```text
/run/secrets/
```

The MariaDB entrypoint uses both secrets, while the WordPress entrypoint uses the database password.

Passwords must not be committed to the repository.

## Building the Project

Go to the `srcs` directory:

```bash
cd ~/inception/srcs
```

Build all Docker images:

```bash
docker-compose build
```

Individual services can also be rebuilt:

```bash
docker-compose build mariadb
docker-compose build wordpress
docker-compose build nginx
```

## Launching the Project

The complete stack can be started with:

```bash
docker-compose up -d
```

Check the status:

```bash
docker-compose ps
```

The expected services are:

```text
mariadb
wordpress
nginx
```

The NGINX container exposes port `443` on the host.

## Makefile

The project can also be managed through the Makefile located at the repository root.

The Makefile is intended to provide convenient commands for building, starting and stopping the infrastructure without having to type the complete Docker Compose commands manually.

The exact Makefile targets should be checked with:

```bash
make
```

or by inspecting:

```bash
cat Makefile
```

## Container Management

List running containers:

```bash
docker ps
```

List all containers:

```bash
docker ps -a
```

View the Compose services:

```bash
docker-compose ps
```

View logs:

```bash
docker-compose logs
```

View logs for one service:

```bash
docker-compose logs nginx
docker-compose logs wordpress
docker-compose logs mariadb
```

Enter a running container:

```bash
docker exec -it wordpress bash
```

If Bash is not available, use:

```bash
docker exec -it wordpress sh
```

## Docker Network

The services are connected to the Compose network:

```text
srcs_inception
```

Inspect it with:

```bash
docker network inspect srcs_inception
```

The network allows the services to communicate using their service names.

For example:

```text
wordpress -> mariadb
nginx     -> wordpress
```

WordPress connects to MariaDB using:

```text
mariadb
```

NGINX connects to PHP-FPM using:

```text
wordpress:9000
```

## Volumes and Persistent Data

The project uses two persistent storage areas.

### MariaDB

The MariaDB data is stored on the host at:

```text
/home/idiaz-ca/data/database
```

It is mounted into the MariaDB container as:

```text
/var/lib/mysql
```

The Docker volume configuration uses a bind mount so that the database data is stored at the required host location.

### WordPress

WordPress uses the Docker volume:

```text
srcs_wordpress_data
```

which is mounted into:

```text
/var/www/html
```

NGINX also mounts this volume read-only:

```text
wordpress_data:/var/www/html:ro
```

This allows NGINX to access the WordPress files without modifying them.

## Volume Management

List Docker volumes:

```bash
docker volume ls
```

Inspect a volume:

```bash
docker volume inspect srcs_wordpress_data
```

or:

```bash
docker volume inspect srcs_mariadb_data
```

Persistent volumes should not be removed unless the intention is to delete the stored project data.

## Rebuilding the Infrastructure

After changing a Dockerfile or service configuration, rebuild the affected image:

```bash
docker-compose build <service>
```

For example:

```bash
docker-compose build nginx
```

Then recreate/start the service:

```bash
docker-compose up -d nginx
```

To rebuild and recreate the complete stack:

```bash
docker-compose up -d --build
```

## Stopping the Infrastructure

Stop and remove the containers:

```bash
docker-compose down
```

The persistent volumes are not removed by this command.

To restart the project:

```bash
docker-compose up -d
```

## Data Persistence

The project is designed so that container recreation does not automatically delete application data.

MariaDB data is persisted through:

```text
/home/idiaz-ca/data/database
```

WordPress files are persisted through:

```text
srcs_wordpress_data
```

Therefore, running:

```bash
docker-compose down
```

and subsequently:

```bash
docker-compose up -d
```

does not normally require reinstalling WordPress or recreating the database.

## Useful Validation Commands

Validate the Docker Compose configuration:

```bash
docker-compose config
```

Test the NGINX configuration:

```bash
docker exec nginx nginx -t
```

Check that WordPress can resolve MariaDB:

```bash
docker exec wordpress getent hosts mariadb
```

Check the PHP-FPM process:

```bash
docker exec wordpress ps aux
```

Check the PHP-FPM listening configuration:

```bash
docker exec wordpress grep "^listen" /etc/php/8.2/fpm/pool.d/www.conf
```

Check the NGINX SSL configuration:

```bash
docker exec nginx nginx -T | grep -E "listen|ssl_certificate"
```

Check the network:

```bash
docker network inspect srcs_inception
```

These commands are useful when debugging communication or configuration problems between the services.
