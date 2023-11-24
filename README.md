srcset Image
============

Provides a field formatter that outputs responsive images utilising the `srcset`
image attribute.

`srcset` lets you specify different image variants which the browser chooses
between based on the screen size. For example, you can specify a large, medium
and small variant of a particular image; then, depending on the user's screen
size, the browser will automatically load the appropriately-sized image. No more
displaying 1000+ pixel images on mobile devices!  
You can read more about the `srcset` and `sizes` image attributes here:
https://css-tricks.com/responsive-images-youre-just-changing-resolutions-use-srcset/

This module integrates with Backdrop's image styles to automatically create the
image variants you select. Simply upload a full-size image, and the different
variants are created automatically. You can also edit the value of the `sizes`
attribute for more fine-grained control.

Installation
------------

- Install the [Preset](https://github.com/backdrop-contrib/preset) module.

- Install this module using the official Backdrop CMS instructions at
  https://backdropcms.org/guide/modules.

- Visit the Image Styles configuration page under Administration >
  Configuration > Media > Image Styles (admin/config/media/image-styles) and
  create different image styles corresponding to the image variants you want.  
  For example, you could create image styles named '1200w', '600w' and '300w'
  which each include a 'Scale' effect that resizes images to the respective
  widths.

- Visit the srcset Image configuration page under Administration >
  Configuration > Media > srcset Image (admin/config/media/srcset-image) and add
  an Image Set that references the different image styles you created above.

- Add an Image field to a content type, configure it, then visit the Manage
  Display page under Administration > Structure > Content Types > [Content Type
  Name] > Manage Displays (admin/structure/types/manage/[content-type]/display).
  Choose a Display Mode to edit, then set the Format of your Image field to
  'srcset Image' and configure it to use the Image Set you created above.
  Optionally edit the Sizes field and specify a link for the image.

Issues
------

Bugs and Feature requests should be reported in the Issue Queue:
https://github.com/backdrop-contrib/srcset_image/issues.

Current Maintainers
-------------------

- [Martin Price](https://github.com/yorkshire-pudding) - [System Horizons Ltd](https://www.systemhorizons.co.uk)
- Collaboration and co-maintainers welcome!

Credits
-------

- Developed for Backdrop CMS by [Peter Anderson](https://github.com/BWPanda).

License
-------

This project is GPL v2 software. See the LICENSE.txt file in this directory for
complete text.

