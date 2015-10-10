#!/bin/bash
(
  cd ../../
  ansible-playbook -vvvv playbook.yml -c ssh -i providers/dev/inventory -t "drupal-kw"
)
