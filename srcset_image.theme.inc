<?php
/**
 * @file
 * Theme functions for the srcset Image module.
 */

/**
 * Returns HTML for a srcset Image field formatter.
 *
 * @param array $variables
 *   An associative array which contains:
 *   - item: An array of image field values.
 *   - image_set: An array representing the srcset image preset.
 *   - original: Whether or not the original image should be included.
 *   - sizes: The value of the srcset image size setting.
 *   - link: An array of settings to generate a link.
 *   - image_load: Whether the image should be loaded 'eager', 'lazy' or
 *     'default'.
 */
function theme_srcset_image_formatter(array $variables) {
  object_log('theme_srcset_image_formatter:$variables', $variables);
  $item = $variables['item'];

  // Do not output an empty 'title' attribute.
  if (empty($item['title'])) {
    unset($item['title']);
  }

  // Prepare srcset attribute.
  if (!empty($variables['image_set']['image_styles'])) {
    $srcset = array();
    $srcset_max_width = 0;
    // Get image style URL and width of each image style.
    foreach ($variables['image_set']['image_styles'] as $image_style) {
      if (!empty($image_style)) {
        // Generate the image style derivative.
        $style = image_style_load($image_style);
        $style_uri = image_style_path($image_style, $item['uri']);
        $success = file_exists($style_uri) || image_style_create_derivative($style, $item['uri'], $style_uri);

        if ($success) {
          image_style_remove_allowed_uri($style_uri);

          // Get the image size.
          $style_url = image_style_url($image_style, $item['uri']);
          $image_size = getimagesize($style_uri);
          if (!empty($image_size)) {
            $image_width = $image_size[0];
            if ($image_width > $srcset_max_width) {
              $srcset_max_width = $image_width;
              $srcset_largest_uri = $style_uri;
            }
            $srcset[] = $style_url . ' ' . $image_width . 'w';
          }
        }
      }
    }

    // Add original image.
    if ($variables['original']) {
      $srcset[] = file_create_url($item['uri']) . ' ' . $item['width'] . 'w';
    }
    else {
      // Replace the item URI with the largest style URI so that original file
      // is not used.
      $item['uri'] = $srcset_largest_uri;
    }

    $item['attributes']['srcset'] = implode(', ', $srcset);

    // Prepare sizes attribute.
    if (!empty($variables['sizes'])) {
      $item['attributes']['sizes'] = $variables['sizes'];
    }

    // Add the loading attribute if not 'default'.
    if ($variables['image_load'] != 'default') {
      $item['attributes']['loading'] = $variables['image_load'];
    }
  }

  // Output a themed image.
  $output = theme('image', $item);

  // Add an optional link to the image.
  if (!empty($variables['link']['path'])) {
    $path = $variables['link']['path'];
    $options = !empty($variables['link']['options']) ? $variables['link']['options'] : array();
    $options['html'] = TRUE;
    $output = l($output, $path, $options);
  }

  return $output;
}
