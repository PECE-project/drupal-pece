-- SUMMARY --

The Total Control Admin Dashboard creates a default panel page with useful 
administration panes right out of the box. Several overview panes are included 
for site stats and quick reference. Administration view panes are provided with 
'more' links to more comprehensive versions of the views. Each View pane is 
customizable via pane config, or override the defaults provided to suit your 
own needs.  

For a full description of the module, visit the project page:
  http://drupal.org/project/total_control

To submit bug reports and feature suggestions, or to track changes:
  http://drupal.org/project/issues/total_control


-- REQUIREMENTS --

Chaos Tools 1.x
Panels 3.x 
Views 2.x
Views Bulk Operations
Search (core)
Statistics (core)


-- INSTALLATION --

* Install as usual, see http://drupal.org/node/70151 for further information.

  If for any reason the panel page is not installed for you automatically, you can import
  the code provided in total_control/includes/total_control.default_page.inc. Go to 
  Admin > Site building > Pages click the "Import page" tab, and copy / paste the code 
  between the comments.


-- CONFIGURATION --

* Configure user permissions in Administer >> User management >> Access control
  >> total_control module:

  - have total control

    Users in roles with the "have total control" permission will see
    the administration dashboard and all included view pages.
    
  - administer total control
  
    Users in roles with the "administer total control" permission will be
    able to visit the settings page where they can determine weather links
    will appear on the panes to "configure" content types.
    

-- CUSTOMIZATION --

* To override the default views on the dashboard, you have two options:
  
  - edit the settings on the panel pane:
  
    TODO: instructions
  
  - override the default views provided with the total_control module:
  
    TODO: instructions