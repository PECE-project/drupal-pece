/**
 * @file
 * Defines the behavior of the Drupal administration navbar.
 */

(function ($, Backbone, Drupal) {

"use strict";

/**
 * Registers tabs with the navbar.
 *
 * The Drupal navbar allows modules to register top-level tabs. These may point
 * directly to a resource or toggle the visibility of a tray.
 *
 * Modules register tabs with hook_navbar().
 */
Drupal.behaviors.navbar = {
  attach: function (context) {
    var defaults = this.defaults;
    $(context).find('#navbar-administration').once('navbar', function () {
      // Create a reference to the defaults in this function scope.
      var options = $.extend(defaults, Drupal.settings.navbar);
      // Set up switching between the vertical and horizontal presentation
      // of the navbar trays based on a breakpoint.
      var mql = window.matchMedia(options.breakpoints['wide']);
      var model = new Drupal.navbar.Model({
        locked: JSON.parse(localStorage.getItem('Drupal.navbar.trayVerticalLocked')) || false,
        activeTab: document.getElementById(JSON.parse(localStorage.getItem('Drupal.navbar.activeTabID'))),
        mqMatches: mql.matches
      });

      // Update the model when matchMedia fires.
      mql.addListener(function (mql) {
        model.set('mqMatches', mql.matches);
      });

      // Respond to viewport offset dimension changes.
      $(document)
        .bind('drupalViewportOffsetChange.navbar', function (event, offsets) {
          model.set('offsets', {
            top: offsets.top,
            right: offsets.right,
            bottom: offsets.bottom,
            left: offsets.left
          });
          // Alter the padding on the top of the body element.
          $('body').css('padding-top', offsets.top);
        });

      // Respond to navbar events.
      $(document)
        .bind('drupalNavbarOrientationChange.navbar', Drupal.navbar.orientationChangeHandler)
        .bind('drupalNavbarTrayChange.navbar', Drupal.navbar.trayChangeHandler);

      // Broadcast model changes to other modules.
      model
        .bind('change:orientation', function (model, orientation) {
          $(document).trigger('drupalNavbarOrientationChange', orientation);
        })
        .bind('change:activeTab', function (model, tab) {
          $(document).trigger('drupalNavbarTabChange', tab);
        })
        .bind('change:activeTray', function (model, tray) {
          $(document).trigger('drupalNavbarTrayChange', tray);
        });

      // Build the navbar view and assign it to the closure variable reference.
      var view = new Drupal.navbar.View({
        el: this,
        model: model,
        strings: options.strings
      });

      // Render collapsible menus.
      var menuModel = new Drupal.navbar.MenuModel();
      var menuView = new Drupal.navbar.MenuView({
        el: $(this).find('.navbar-menu-administration').get(0),
        model: menuModel
      });
      // Handle the resolution of Drupal.navbar.setSubtrees().
      // This is handled with a deferred so that the function may be invoked
      // asynchronously.
      Drupal.navbar.setSubtrees.done(function (subtrees) {
        menuModel.set('subtrees', subtrees);
      });
      // Call displace to get the initial placement of offset elements.
      Drupal.displace();
    });
  },
  // Default options.
  defaults: {
    breakpoints: {
      'wide': ''
    },
    strings: {
      opened: Drupal.t('opened'),
      horizontal: Drupal.t('Horizontal orientation'),
      vertical: Drupal.t('Vertical orientation')
    }
  }
};

/**
 * Navbar methods of Backbone objects.
 */
Drupal.navbar = Drupal.navbar || {
  /**
   * Accepts a list of subtree menu elements.
   *
   * A deferred object that is resolved by an inlined JavaScript callback.
   *
   * JSONP callback.
   * @see navbar_subtrees_jsonp().
   *
   * Let's build our own $.Deferred()!
   */
  setSubtrees: (function () {
    return {
      resolve: function (subtrees) {
        this.callback.call(null, subtrees);
      },
      done: function (callback) {
        this.callback = callback;
      }
    };
  }()),

  /**
   * Responds to drupalNavbarOrientationChange.
   *
   * Applies classes to the body element that reflect the current orientation
   * of the active navbar.
   *
   * @param jQuery.Event event
   * @param String orientation
   *   The value can be either 'horizontal' or 'vertical'.
   */
  orientationChangeHandler: function (event, orientation) {
    $('body')
      .toggleClass('navbar-vertical', orientation === 'vertical')
      .toggleClass('navbar-horizontal', orientation === 'horizontal');
  },

  /**
   * Responds to drupalNavbarTrayChange.
   *
   * Toggles the navbar-tray-open class on the body elment. The class is applied
   * when a navbar tray is active.
   *
   * @param jQuery.Event event
   * @param DOM tray
   *   The currently active tray DOM element.
   */
  trayChangeHandler: function (event, tray) {
    $('body')
      .toggleClass('navbar-tray-open', !!tray);
  },

  /**
   * Backbone model for the navbar.
   */
  Model: Backbone.Model.extend({
    defaults: {
      // The active navbar item. All other items should be inactive under
      // normal circumstances. It will remain active across page loads. The active
      // item is stored as a DOM element, not a jQuery set.
      activeTab: null,
      // Represents whether a tray is open or not. Stored as a DOM element, not a
      // jQuery set.
      activeTray: null,
      // The orientation of the active tray.
      orientation: 'horizontal',
      // A tray is locked if a user toggled it to vertical. Otherwise a tray
      // will switch between vertical and horizontal orientation based on the
      // configured breakpoints. The locked state will be maintained across page
      // loads.
      locked: false,
      // Indicates whether the media query matches or not.
      mqMatches: null,
      // The height of the navbar.
      height: null,
      // The current viewport offsets determined by Drupal.displace(). The offsets
      // suggest how a module might position is components relative to the
      // viewport.
      offsets: {
        top: 0,
        right: 0,
        bottom: 0,
        left: 0
      }
    }
  }),

  /**
   * Backbone view for the navbar element.
   */
  View: Backbone.View.extend({
    events: {
      'click .navbar-bar .navbar-tab': 'onTabClick',
      'click .navbar-toggle-orientation button': 'onOrientationToggleClick'
    },

    /**
     * Implements Backbone.View.prototype.initialize().
     */
    initialize: function (options) {
      this.strings = options.strings;

      this.model.bind('change:activeTab', this.render, this);
      this.model.bind('change:orientation', this.render, this);
      this.model.bind('change:mqMatches', this.onMediaQueryChange, this);
      this.model.bind('change:offsets', this.adjustPlacement, this);

      // Add the tray orientation toggles.
      this.$el.find('.navbar-tray')
        .find('.navbar-lining')
        .append(Drupal.theme('navbarOrientationToggle'));

      // Trigger an activeTab change so that listening scripts can respond on
      // page load. This will call render.
      this.model.trigger('change:activeTab');

      // Update the tray orientation.
      var orientation = this._checkOrientationLock(this._getTrayOrientation(this.model.get('mqMatches')));
      this.model.set('orientation', orientation);

      // Invoke Drupal.displace() to get the current viewport offset values.
      Drupal.displace();
    },

    /**
     * Implements Backbone.View.prototype.render().
     *
     * @return Backbone.View
     */
    render: function () {
      // Update the display of the tabs.
      this.refreshTabs();
      // Adjust the orientation of the active tray.
      this.setOrientation();
      // Adjust the height of the navbar.
      this.model.set('dimensionsAreValid', false);

      return this;
    },

    /**
     * Responds to a navbar tab click.
     *
     * @param jQuery.Event event
     */
    onTabClick: function (event) {
      // The polyfilled on and off events on the jQuery fn obect are not working
      // perfectly with Backbone views. All click events within the view's el
      // are being delegated, so we need to check here that we have the right
      // element before acting with it.
      if ($(event.target).is('.navbar-tab')) {
        var tab = this.model.get('activeTab');

        // Set the event target as the active item if it is not already.
        this.model.set('activeTab', (!tab || event.target !== tab) ? event.target : null);

        event.preventDefault();
        event.stopPropagation();
      }
    },

    /**
     * Toggles the orientation of a navbar tray.
     *
     * @param jQuery.Event event
     */
    onOrientationToggleClick: function (event) {
      // The polyfilled on and off events on the jQuery fn obect are not working
      // perfectly with Backbone views. All click events within the view's el
      // are being delegated, so we need to check here that we have the right
      // element before acting with it.
      if ($(event.target).is('.navbar-toggle-orientation button')) {
        var orientation = this.model.get('orientation');
        // Determine the toggle-to orientation.
        var antiOrientation = (orientation === 'vertical') ? 'horizontal' : 'vertical';
        var locked = (antiOrientation === 'vertical') ? true : false;
        // Remember the locked state.
        if (locked) {
          localStorage.setItem('Drupal.navbar.trayVerticalLocked', 'true');
        }
        else {
          localStorage.removeItem('Drupal.navbar.trayVerticalLocked');
        }
        // Update the model.
        this.model.set({
          locked: locked,
          orientation: antiOrientation
        });

        event.preventDefault();
        event.stopPropagation();
      }
    },

    /**
     * Responds to change:orientation event when window.matchMedia fires.
     *
     * @param Backbone.Model model
     * @param Boolean mqMatches
     *   The matches property of a MediaQueryList object.
     */
    onMediaQueryChange: function (model, mqMatches) {
      this.model.set('orientation', this._checkOrientationLock(this._getTrayOrientation(mqMatches)));
    },

    /**
     * Gets the tray orientation depending on whether the media query matches.
     *
     * @param Boolean mqMatches
     *   The matches property of a MediaQueryList object.
     * @return String
     *   The orientation, either 'horizontal' or 'vertical'.
     */
    _getTrayOrientation: function (mqMatches) {
      return mqMatches ? 'horizontal' : 'vertical';
    },

    /**
     * Toggles a navbar tab and the associated tray.
     *
     * @param jQuery.Event event
     */
    refreshTabs: function (event) {
      var $tab = $(this.model.get('activeTab'));
      var $tray = $();
      // Activate the selected tab.
      if ($tab.length > 0) {
        $tab.addClass('active');
        var name = $tab.attr('data-navbar-tray');
        // Mark the tab as pressed.
        $tab.attr('aria-pressed', 'true');
        // Store the active tab name or remove the setting.
        var id = $tab.get(0).id;
        if (id) {
          localStorage.setItem('Drupal.navbar.activeTabID', JSON.stringify(id));
        }
        // Activate the associated tray.
        $tray = this.$el.find('[data-navbar-tray="' + name + '"].navbar-tray');
        if ($tray.length) {
          $tray.addClass('active');
          this.model.set('activeTray', $tray.get(0));
          // Announce that a tray has been opened.
          // @todo implement the D8 Drupal.announce method in D7.
          // Drupal.announce(Drupal.t('@tray tray @state', {
          //   '@tray': name,
          //   '@state': this.strings.opened
          // }));
        }
        else {
          // There is no active tray.
          this.model.set('activeTray', null);
        }
      }
      else {
        // There is no active tray.
        this.model.set('activeTray', null);
        localStorage.removeItem('Drupal.navbar.activeTabID');
      }
      // Disable non-selected tabs.
      this.$el.find('.navbar-bar .navbar-tab')
        .not($tab)
        .removeClass('active')
        .attr('aria-pressed', 'false');
      // Disable non-selected trays.
      this.$el.find('.navbar-tray')
        .not($tray)
        .removeClass('active');
    },

    /**
     * Change the orientation of the tray between vertical and horizontal.
     */
    setOrientation: function () {
      var orientation = this._checkOrientationLock(this.model.get('orientation'));
      // The antiOrientation is used to render the view of action buttons like
      // the tray orientation toggle.
      var antiOrientation = (orientation === 'vertical') ? 'horizontal' : 'vertical';
      // Update the orientation of the trays.
      var $trays = this.$el.find('.navbar-tray')
        .removeClass('navbar-tray-horizontal navbar-tray-vertical')
        .addClass('navbar-tray-' + orientation);

      // Update the tray orientation toggle button.
      var iconClass = 'navbar-icon-toggle-' + orientation;
      var iconAntiClass = 'navbar-icon-toggle-' + antiOrientation;
      this.$el.find('.navbar-toggle-orientation button')
        .val(antiOrientation)
        .text(this.strings[antiOrientation])
        .removeClass(iconClass)
        .addClass(iconAntiClass);

      var dir = document.documentElement.dir;
      var edge = (dir === 'rtl') ? 'right' : 'left';
      // Remove data-offset attributes from the trays so they can be refreshed.
      $trays.removeAttr('data-offset-left').removeAttr('data-offset-right').removeAttr('data-offset-top');
      // If an active vertical tray exists, mark it as an offset element.
      $trays.filter('.navbar-tray-vertical.active').attr('data-offset-' + edge, '');
      // If an active horizontal tray exists, mark it as an offset element.
      $trays.filter('.navbar-tray-horizontal.active').attr('data-offset-top', '');
      // Trigger a recalculation of viewport displacing elements.
      Drupal.displace();

      // Append a message that the tray orientation has been changed.
      // @todo implement the D8 Drupal.announce method in D7.
      // Drupal.announce(Drupal.t('Tray orientation changed to @orientation.', {
      //   '@orientation': orientation
      // }));
    },

    /**
     * Returns an orientation based on the orientation lock.
     *
     * Orientation is locked to the vertical position when a user changes a
     * horizontal tray to a vertical try using the tray orientation toggle button.
     *
     * @param String orientation
     *   The value can be either 'horizontal' or 'vertical'.
     * @return String
     *   The orientation, either 'horizontal' or 'vertical'.
     */
    _checkOrientationLock: function (orientation) {
      var locked = this.model.get('locked');
      // Set the orientation of the tray.
      // If the tray is locked to vertical in localStorage, persist the vertical
      // presentation. If the tray is not locked to vertical, let the media
      // query application decide the orientation.
      return (locked) ? 'vertical' : orientation;
    },

    /**
     * Sets the tops of the trays so that they align with the bottom of the bar.
     */
    adjustPlacement: function () {
      // Set the top of the all the trays to the height of the bar.
      var barHeight = this.$el.find('.navbar-bar').outerHeight();
      var height = barHeight;
      var bhpx =  barHeight + 'px';
      var $trays = this.$el.find('.navbar-tray');
      var tray;
      for (var i = 0, il = $trays.length; i < il; i++) {
        tray = $trays[i];
        if (!tray.style.top.length || (tray.style.top !== bhpx)) {
          tray.style.top = bhpx;
        }
      }
    }
  }),

  /**
   * Backbone Model for collapsible menus.
   */
  MenuModel: Backbone.Model.extend({
    defaults: {
      subtrees: {}
    }
  }),

  /**
   * Backbone View for collapsible menus.
   */
  MenuView: Backbone.View.extend({

    /**
     * Implements Backbone.View.prototype.initialize().
     */
    initialize: function () {
      // @todo, when subtree optimization is put in to place, render when the
      // subtrees are delivered. Until then, just render right away.
      // this.model.bind('change:subtrees', this.render, this);
      this.render();
    },

    /**
     * Implements Backbone.View.prototype.render().
     */
    render: function () {
      var subtrees = this.model.get('subtrees');
      // Add subtrees.
      // @todo Optimize this to delay adding each subtree to the DOM until it is
      //   needed; however, take into account screen readers for determining
      //   when the DOM elements are needed.
      for (var id in subtrees) {
        if (subtrees.hasOwnProperty(id)) {
          this.$el
            .find('#navbar-link-' + id)
            .once('navbar-subtrees')
            .after(subtrees[id]);
        }
      }
      // Render the main menu as a nested, collapsible accordion.
      if ('drupalNavbarMenu' in $.fn) {
        this.$el
          .find('> .menu')
          .drupalNavbarMenu();
      }
    }
  })
};

/**
 * Theme function for the navbar orientation toggle.
 *
 * @return
 *   The corresponding HTML.
 */
Drupal.theme.navbarOrientationToggle = function () {
  return '<div class="navbar-toggle-orientation"><div class="navbar-lining">' +
    '<button class="navbar-icon" type="button"></button>' +
    '</div></div>';
};

}(jQuery, Backbone, Drupal));
