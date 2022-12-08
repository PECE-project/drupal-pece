## Depedencies
- Docker
- Docker Compose
- Make
- Composer

# Installing the project

1- create a new ssh key on your github profile, settings, ssh and gpg keys, copying your /home/[user]/.ssh/id_rsa.pub content. If you does not have a ssh key (and id_rsa.pub):
`mkdir –p $HOME/.ssh`
`chmod 0700 $HOME/.ssh`
`ssh-keygen`

2- clone the project using 
`git clone git@github.com:PECE-project/drupal-pece.git --branch pece2.0`

3- enter in the project
`cd drupal-pece`

4- Rename .env.example to .env and if necessary, change the variables.
`cp .env.example .env`

5- Rename docker-compose.override.yml.example to docker-compose.override.yml
`cp docker-compose.override.yml.example docker-compose.override.yml`

6-(ONLY FOR MAC USERS) 
Update this lines

.env file

`Change PHP_TAG to use macos images.`

In docker-compose.override.yml, search for `For macOS users` comment.

More information: https://wodby.com/docs/stacks/drupal/local/#docker-for-mac for you choice between cache or docker-sync

7- Add on your /etc/hosts the line:
127.0.0.1       portainer.pece.local v1.pece.local pece.local admin.pece.local analytics.v1.pece.local analytics.pece.local

...

8- Run command `make up`

9- When the command above finished, verify and wait if the composer is executing:
`make logs composer`

10- In your browser, access admin.pece.local/