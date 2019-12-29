<template>
  <nav aria-labelledby="mainmenu">
    <h2 id="mainmenu" class="sr-only">
      Main menu
    </h2>
    <ul class="flex">
      <li
        v-for="menu in menuHeader"
        :key="menu.label"
        class="p-6 py-5 md:px-4 lg:px-6 cursor-pointer hover:text-accent"
        data-pece="menuHeader-items"
      >
        <a :href="menu.link">
          {{ menu.label }}
        </a>
      </li>
    </ul>
  </nav>
</template>

<script>
import { menuHeader } from '@/utils/fake'

export default {
  name: 'Navigation',
  setup () {
    return {
      menuHeader
    }
  }
}
</script>

<style lang="scss"></style>
