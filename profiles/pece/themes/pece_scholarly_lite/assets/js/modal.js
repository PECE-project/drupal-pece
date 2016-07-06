// /**
//  * @file
//  * Custom scripts for theme.
//  */
//
// (function (window, document, $, undefined) {
//
// Drupal.behaviors.peceModal = {
//   attach: function (context, settings) {
//     $.each(settings.peceModal || {}, function (selector, config) {
//       $(selector, context).each(function () {
//         var $modal = $(this);
//         var modal;
//
//         // Let other scripts - such as sliders - perform their operations before
//         // building the modal.
//         setTimeout(initialize, 2000);
//
//         function initialize() {
//           // modal = $modal.remodal(config.remodal);
//         }
//       });
//     });
//   }
// };
//
// })(window, document, jQuery);
