<template>
  <div
    v-if="isLogged"
    class="sticky left-0 top-0 z-50 w-full px-4 bg-headerAdmin"
    data-nw="header-admin"
  >
    <nav class="flex h-full">
      <ul class="flex justify-start text-gray-400 text-sm">
        <li class="h-full">
          <nuxt-link
            to="/"
            class="p-4 h-full block"
          >
            <svg-icon
              name="home-run"
              width="17px"
              height="17px"
              class="text-gray-400 fill-current"
              style="margin-top: 2px;"
            />
          </nuxt-link>
        </li>
        <li class="h-full">
          <nuxt-link
            to="/"
            class="p-4 h-full block"
          >
            {{ user.username }}
          </nuxt-link>
        </li>
        <li class="h-full">
          <button
            @click="logout"
            type="button"
            class="p-4 h-full block"
            data-nw="logout"
          >
            Logout
          </button>
        </li>
      </ul>
    </nav>
  </div>
</template>

<script>
import { ref, onMounted } from '@vue/composition-api'

export default {
  name: 'TheHeaderAdmin',

  setup (_, { root }) {
    const isLogged = ref(false)
    const user = ref({})

    onMounted(() => {
      user.value = root.$store.getters['user/user']
      isLogged.value = root.$store.getters['user/getToken']
    })

    function logout () {
      root.$store.dispatch('user/logout')
    }

    return {
      user,
      logout,
      isLogged
    }
  }
}
</script>

<style lang="scss"></style>
