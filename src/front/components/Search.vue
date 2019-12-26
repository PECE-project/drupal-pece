<template>
  <form name="search" role="search">
    <label
      class="relative block h-12"
      for="search"
    >
      <span class="sr-only">Search content in PECE project site</span>
      <input
        id="search"
        class="shadow-search p-3 pr-12 bg-gray"
        placeholder="Search"
        type="text"
        name="search"
      >
      <button class="absolute p-2 px-4 right-0 inset-y-0 flex items-center justify-center">
        <span class="sr-only">Submit search</span>
        <svg
          class="fill-current text-gray-600"
          xmlns="http://www.w3.org/2000/svg"
          width="16.832"
          height="17.434"
          viewBox="0 0 16.832 17.434"
        >
          <path d="M17.56,15.88l-4.149-4.316a7.036,7.036,0,1,0-5.388,2.514A6.964,6.964,0,0,0,12.056,12.8l4.181,4.348A.918.918,0,1,0,17.56,15.88ZM8.023,1.836a5.2,5.2,0,1,1-5.2,5.2A5.209,5.209,0,0,1,8.023,1.836Z" transform="translate(-0.984)" />
        </svg>
      </button>
    </label>
  </form>
</template>

<script>
export default {
  name: 'Search'
}
</script>

<style lang="scss"></style>
