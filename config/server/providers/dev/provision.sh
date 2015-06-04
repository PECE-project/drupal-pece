#!/bin/bash
(
	cd ../../
	ansible-playbook playbook.yml -c ssh -i providers/dev/inventory
)
