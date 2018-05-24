<?php
/**
 * @file
 * Theme functions for the srcset Image module.
 */

/**
 * Returns HTML for a srcset Image field formatter.
 */
function theme_srcset_image_formatter($variables) {
  $item = $variables['item'];

  // Do not output an empty 'title' attribute.
  if (isset($item['title']) && backdrop_strlen($item['title']) == 0) {
    unset($item['title']);
  }

  // Prepare srcset attribute.
  if ($variables['image_set'] && $variables['image_set']['image_styles']) {
    $srcset = array();

    // Get image style URL and width of each image style.
    foreach ($variables['image_set']['image_styles'] as $image_style) {
      $image_style_url = image_style_url($image_style, $item['uri']);
      $image_size = getimagesize($image_style_url);
      $srcset[] = $image_style_url . ' ' . $image_size[0] . 'w';
    }

    // Add original image.
    $srcset[] = file_create_url($item['uri']) . ' ' . $item['width'] . 'w';
    $item['attributes']['srcset'] = implode(', ', $srcset);

    // Prepare sizes attribute.
    if (!empty($variables['sizes'])) {
      $item['attributes']['sizes'] = $variables['sizes'];
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

