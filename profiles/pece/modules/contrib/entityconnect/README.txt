Entityconnect expands the entity reference auto-complete field
by adding a add new content and edit current content button.

The "add a new button" will allowed a new entity to be added
via an add form and then return the user to the original form.

The edit button will take the user to the edit form of the referenced entity,
and return them when they are done editing.

Original concept and piece of code based on NodeConnect.

List of working entities on form:
  - Node
  - User

Installation
------------
1. Copy entityconnect into your modules directory and then enable on the admin
modules page
2. Define permissions on admin/people/permissions page
3. Define default parameters in administration page admin/config/content/entityconnect
4.1 If you set default button visibility to ON
  4.1.a Go to a form (add or edit form) which contain an entityreference field and you should see an add (+) and/or
  edit (pencil) button after your field.
4.2 If you set default button visibility to OFF
  4.2.a Go to fields administration for the entity you want to alter (eg: admin/structure/types/manage/page/fields)
  4.2.b Edit an entityreference field and active it for that field (Display Entity Connect "edit" button / Display Entity Connect "add" button)

FAQ
---
Q. I have define "see add button" permissions but can't see the add button
on my entityreference which point on an content type.
A. When only one content type is defined on entityreference field, module
also check if user has the permission to "create N content" where N is
the content type or has the permission "administer nodes".

Q. I don't see any buttons on my form
A. Please check if your field have entityconnect buttons activated. By default, there are disable.

Q. I have already a lot of entityreference fields and I don't want to them manually. What can I do?
A. You can change default parameters in admin/config/content/entityconnect page and set buttons visibility to "On".
That will activate buttons for all your fields.
Of course, you can always override parameters on your field instance.

Q. I don't want the default CSS icons to be display?
I want to display the help text after the icon?
A. You can change default parameters in admin/config/content/entityconnect page and set icons visibility to "Text only" or "Icons + Text".

Next steps
----------

7.x-1.x-RC or Stable will come when all core entities will be supports.

Release 7.x-2.x goals are:
- Add Ctools support,
- Add Commerce Entities and reference fields for product reference fields,
- Add compatibility with Entites UI like
  1. ECK (Entity Construction Kit)(http://drupal.org/project/eck),
  2. Model Entities (http://drupal.org/project/model)
