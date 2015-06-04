nodejs-app
==========

This Ansible role sets up a Node.js application.

Role Variables
--------------

    nodejs_app:
      autostart: false
      service: nodejs-app
      repo: git@github.com:username/repository.git
      version: master
      dir: /opt/nodejs-app
      logdir: /var/log
      port: 5000
      workers: 1
      env:
        NODE_ENV: development


License
-------

BSD

Author Information
------------------

George Miroshnykov <george.miroshnykov@gmail.com>
