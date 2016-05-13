# PECE-DOCKER
Drupal Pece with Docker

---------------------
## Requirements
  * [GIT](https://git-scm.com/)
  * [Docker Compose](https://docs.docker.com/compose/)

---------------------
Clone project
```sh
$ git clone https://github.com/PECE-project/drupal-pece.git
$ cd drupal-pece/
```

---------------------
Pull image of drupal-pece
```sh
$ docker pull taller/pece
```

---------------------
Up virtual machine to work
```sh
$ docker-compose run --rm -p 8080:80 dev_pece
```

  * Access url [http://localhost:8080](http://localhost:8080)
  * Database configurations:
      - *Host:* pece-db
      - *Database:* pece
      - *User:* pece
      - *Pece Password:* ZwTuVZzQO90qwYzA
      - *Root Password:* Sk82jxYqqpx02jxT
