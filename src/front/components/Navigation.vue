<template>
  <nav>
    <ul class="flex">
      <li
        v-for="menu in menuHeader"
        :key="menu.label"
        class="p-6 py-5 cursor-pointer hover:text-accent"
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
