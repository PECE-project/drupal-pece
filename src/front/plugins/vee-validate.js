import { extend } from 'vee-validate'
import { confirmed, email, max, min, numeric, required } from 'vee-validate/dist/rules'

extend('email', email)
extend('max', max)
extend('min', min)
extend('numeric', numeric)
extend('required', required)
extend('confirmed', confirmed)
