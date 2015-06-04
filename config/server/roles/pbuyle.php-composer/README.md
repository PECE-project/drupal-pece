Ansible php-composer
====================

Ansible role to install Composer and global packages.

Example usage:

    - role: php-composer
      composer_json:
        require:
          "psy/psysh": "*"
          "behat/behat": "2.4.*@stable"

Requirements
------------

* PHP-CLI
* Curl

Role Variables
--------------

* **composer_user**: The user for which composer pakcages are to be installed globally. Defaults to 'vagrant'.
* **composer_user_home**: The home folder of that user. Defaults to '/home/vagrant'.
* **composer_json**: The content of the global composer.json file.

License
-------

BSD

Author Information
------------------

Pierre Buyle <buyle@pheromone.ca>
