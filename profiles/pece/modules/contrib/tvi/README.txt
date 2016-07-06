--------------------------------------------------------------------------------
TVI Overview

The TVI (Taxonomy View Integrator) module allows selective overriding of 
taxonomy terms and/or vocabulary with the view of your choice. 

Using views and taxonomy alone, one can already override a taxonomy term, or 
even all terms in all vocabulary.   But a view that overrides just the terms in 
vocabulary 3 is not possible without TVI.

--------------------------------------------------------------------------------
Usage scenarios:

Lets say you have a vocabulary defined for events, news items, and blogs.  If 
you want to have a calendar view for all term displays in events, one view for 
all news item terms, and you want to have standard taxonomy displays for blogs, 
this is where TVI shines.


--------------------------------------------------------------------------------
How do you use it:

1: Enable TVI module (requires taxonomy and views)

2: [optional] Define a new view or clone taxonomy/term/* view. 
		 
3: After you know what view you want to use on a vocab or term, simply visit 
   the term or vocabulary edit page that the view should be applied to, select 
   the view that you wish to use using the drop-down select list, select the 
   view plugin, and save your changes.

--------------------------------------------------------------------------------
Theming

As of Beta4, there are 2 theme functions included in TVI: 
theme_tvi_breadcrumb() and theme_tvi_title().

--------------------------------------------------------------------------------
The nitty-gritty:

1: TVI cannot currently deal with multiple term displays. 
   ex. taxonomy/term/4+6+7 and will pass these requests to non-TVI views if 
   they exist, or taxonomy if all else fails.

2: TVI does not care what your view does however TVI will pass the term id and 
   term id with depth modifier to the view as arguments.  To make use of these, 
   simply add the following arguments to the view you plan to use on your term
   or vocabulary:
   
   A1: Taxonomy: Term ID (with depth)
   A2: Taxonomy: Term ID depth modifier
   
3: TVI has an order of precedence mechanism:

   1: TVI term view override  
   2: TVI vocabulary view override
   3: view path: taxonomy/term/tid(s) (exact match) +
   4: view path: taxonomy/term/* +
   5: taxonomy: taxonomy/term/tid(s) ++

4: You may clone the default taxonomy/term/* view to create your TVI views as 
	 their arguments are identical. However, it is a good idea to give all TVI 
	 views that provide page displays a path other than the default 
	 taxonomy/term/*. Alternatively, you may remove the page displays and simply 
	 use a block view for TVI views: this is recommended.
	 
5: TVI uses hook_menu_alter to replace the taxonomy/term/* callback. Unlike 
   the re-direct method, which causes your server to be queried 2 or more 
   times for each request, the hook_menu_alter method conserves your server 
   resources.  However TVI is imperfect as well; Since it usurps the callback 
   request, page titles and breadcrumbs must be generated internally to TVI.  
   TVI gets this information from data found in the View being used, as well 
   as drupal_get_breadcrumb().  
   
--------------------------------------------------------------------------------
+ If there are no views specified to be used on the viewed term or vocabulary, 
  TVI will seek to find a view defined for the requested path.
  
++ In the case that TVI finds no views (TVI active or otherwise) for this term 
   display, TVI will pass the buck to taxonomy for the regular display.

   
