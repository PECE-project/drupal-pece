# protractor-drupal-framework
A test automation framework for Drupal apps, written using Protractor and the PageObjects pattern.

**Pre-requisites:**
- NodeJS (greater than v0.10.0)
- Java Development Kit (JDK) - for the selenium server

**Setup:**

To install protractor globally, use:

`npm install -g protractor`

After installing protractor, you will need to update the webdriver-manager. Use:

`webdriver-manager update`

To start the selenium server, use:

`webdriver-manager start`

**Running tests:**

For running the protractor tests, execute the below command in the path where the protractor configuration file is located:

`protractor`
