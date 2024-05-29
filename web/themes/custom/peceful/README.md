# Peceful

## A Bulma subtheme

For example, using the inspector you will find that menu items have their radius set with the variable `--bulma-menu-item-radius`.  That is a CSS variable which can be overridden directly from CSS, which is the approach we can take for quick changes for specific sites, but to make the change in the default skin's SCSS, we can take that CSS variable name and derive the Bulma Sass variable name by dreplacing the `--bulma-` with `$`, so to remove the rounding of the buttons in `skins/default/scss/main.scss` add `$menu-item-radius: 0,` into the `@use "../../../node_modules/bulma/sass" with (` section.

### Compile SCSS into CSS

```
npm run build-bulma
```
