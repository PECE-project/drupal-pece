<script>
import * as timeago from 'timeago.js'
import { pt_BR as ptBR } from 'timeago.js/lib/lang'
timeago.register('pt_BR', ptBR)

export default {
  name: 'TimeAgo',
  props: {
    date: {
      type: [Date, String],
      default () {
        return new Date()
      }
    },
    locale: {
      type: String,
      default: 'en'
    }
  },
  data () {
    return {
      langs: {
        en: 'en_US',
        pt: 'pt_BR'
      },
      result: null
    }
  },
  created () {
    this.result = timeago.format(this.date, this.langs[this.locale])
  },
  render () {
    return this.$scopedSlots.default({
      time: this.result
    })
  }
}
</script>
