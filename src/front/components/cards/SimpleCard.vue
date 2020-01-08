<template>
  <div class="simple-card rounded overflow-hidden shadow-pece flex flex-wrap flex-col h-full">
    <div :class="{ 'flex-auto': !data.image }" class="card__media">
      <nuxt-link :to="{ name: `group___${$i18n.locale}`, params: { slug: data.slug } }">
        <img v-if="data.image" :src="data.image.url" :alt="data.image.alt" class="w-full h-full object-cover">
        <div v-else class="bg-accent w-full h-full flex justify-center items-center py-2">
          <svg-icon
            v-if="data.__typename"
            :name="icons[data.__typename]"
            class="text-gray-100 fill-current"
            width="30px"
            height="30px"
          />
        </div>
      </nuxt-link>
    </div>
    <div class="card__content p-3 pb-4 min-h-12">
      <!-- eslint-disable-next-line vue/require-component-is -->
      <component :is="heading" class="card__title text-sm font-bold text-gray-900 leading-tight">
        <nuxt-link :to="{ name: `group___${$i18n.locale}`, params: { slug: data.slug } }">
          {{ data.title }}
        </nuxt-link>
      </component>
    </div>
  </div>
</template>

<script>
export default {
  name: 'SimpleCard',
  props: {
    data: {
      type: Object,
      required: true
    },
    heading: {
      type: String,
      default: 'h2'
    }
  },
  setup () {
    // Temp code for change icon
    const icons = {
      ArtifactAudioConnection: 'audio',
      ArtifactBundleConnection: 'bundle',
      ArtifactImageConnection: 'photo',
      ArtifactPDFDocumentConnection: 'pdf-file',
      ArtifactTextConnection: 'text',
      ArtifactVideoConnection: 'video',
      ArtifactWebsiteConnection: 'web',
      GroupConnection: 'group',
      MemoConnection: 'memo',
      PeceEssayConnection: 'essay',
      PhotoEssayConnection: 'photo',
      TimelineEssayConnection: 'timeline'
    }
    return {
      icons
    }
  }
}
</script>

<style lang="scss">
.card {
  &__media {
    @screen sm {
      min-height: 130px;
    }
  }
}
</style>
