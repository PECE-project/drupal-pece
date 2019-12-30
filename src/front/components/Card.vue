<template>
  <article class="card rounded overflow-hidden shadow-pece">
    <div class="card__media">
      <img src="https://picsum.photos/320/200" alt="Description image" class="w-full block">
    </div>
    <div class="card__content p-3">
      <header class="card__header">
        <h2 class="card__title text-sm font-bold text-gray-900">
          Traces of future
        </h2>
      </header>
      <footer class="card__meta mt-1" role="contentinfo">
        <div class="card__info text-gray-600">
          <a href="#" class="card__user-link">
            <span class="underline">Mike Fortun</span>
          </a>
          <span>•</span>
          <span class="card__post-date">2 day ago</span>
        </div>
        <div class="card__tags mt-4">
          <span>#science</span>
          <span>#climatology</span>
        </div>
      </footer>
    </div>
  </article>
</template>

<script>
export default {
  name: 'Card'
}
</script>

<style lang="scss">
.card {
  &__info {
    font-size: 12px;
  }
  &__tags {
    span {
      @apply rounded-full bg-gray-100 text-gray-600 p-1 px-2 mr-1;
      font-size: 10px;
    }
  }
}
</style>
