all:
	docker compose -f srcs/docker-compose.yml up -d --build

build:
	docker compose -f srcs/docker-compose.yml build

up:
	docker compose -f srcs/docker-compose.yml up -d

down:
	docker compose -f srcs/docker-compose.yml down

restart:
	docker compose -f srcs/docker-compose.yml down
	docker compose -f srcs/docker-compose.yml up -d

clean:
	docker compose -f srcs/docker-compose.yml down

fclean:
	docker compose -f srcs/docker-compose.yml down -v
	docker system prune -af

re:
	make fclean
	make all