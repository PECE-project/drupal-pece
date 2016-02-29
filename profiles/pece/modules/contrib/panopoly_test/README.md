Behat tests
===========

Quick setup
-----------

 
 1. Install Composer

    php -r "eval('?>'.file_get_contents('https://getcomposer.org/installer'));"
 
 2. Install Behat and dependencies via Composer

    php composer.phar install

 3. Copy behat.template.yml to behat.yml and modify

    mv behat.template.yml behat.yml
 
 4. Enable the panopoly_test module

    drush en panopoly_test

 5. Run Behat and examine test results!
 
    bin/behat

Profiles
-----------

Some of the tests need to run on Chrome due to issues in the Selenium Firefox 
driver. To run the tests tagged with @chrome, you need to run Behat using the 
Chrome profile:

    bin/behat --profile chrome

More information
----------------

For detailed instructions, see:

  https://drupal.org/node/2271009

