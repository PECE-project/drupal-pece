.PHONY: run stop clean distro

run:
	docker-compose run --rm -p 8080:80 dev_pece

stop:
	docker-compose stop

clean:
	docker-compose down
	rm -rf ./node_modules
	rm -rf ./cnf
	rm -rf ./builds
	rm -rf ./build

distro: clean
	docker-compose run --rm production gulp pack-distro
