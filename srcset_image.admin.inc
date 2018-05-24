<?php
/**
 * @file
 * Administrative page callbacks for the srcset Image module.
 */

/**
 * List image sets.
 */
function srcset_image_sets_list() {
  $image_sets = config_get('srcset_image.sets');

  $rows = array();
  foreach ($image_sets as $image_set) {
    $row = array();

    $row[] = check_plain($image_set['name']);
    $row[] = check_plain(implode(', ', $image_set['image_styles']));
    $row[] = array(
      'data' => array(
        '#type' => 'operations',
        '#links' => array(
          'configure' => array(
            'title' => t('Configure'),
            'href' => 'admin/config/media/srcset-image/' . $image_set['machine_name'],
          ),
          'delete' => array(
            'title' => t('Delete'),
            'href' => 'admin/config/media/srcset-image/' . $image_set['machine_name'] . '/delete',
          ),
        ),
      ),
    );

    $rows[] = $row;
  }

  $table = array(
    'header' => array(
      'Name',
      'Image styles',
      'Operations',
    ),
    'rows' => $rows,
    'empty' => t('No srcset Image sets found.'),
  );

  return theme('table', $table);
}

/**
 * Add/edit form for image sets.
 */
function srcset_image_sets_form($form, &$form_state, $image_set = array()) {
  // Add default values for new image sets.
  $image_set += array(
    'name' => '',
    'machine_name' => '',
    'image_styles' => array(),
  );

  // Get image styles as options for checkboxes.
  $options = array();
  foreach (image_styles() as $image_style) {
    $options[$image_style['name']] = $image_style['label'];
  }

  // Add form fields.
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#default_value' => $image_set['name'],
    '#required' => TRUE,
  );
  $form['machine_name'] = array(
    '#type' => 'machine_name',
    '#default_value' => $image_set['machine_name'],
    '#machine_name' => array(
      'exists' => '_srcset_image_set_name_exists',
    ),
  );
  $form['image_styles'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Image styles'),
    '#description' => t('Select the image styles that make up this image set.'),
    '#options' => $options,
    '#default_value' => $image_set['image_styles'],
    '#required' => TRUE,
  );

  $form['actions'] = array(
    '#type' => 'actions',
    'submit' => array(
      '#type' => 'submit',
      '#value' => t('Save image set'),
    ),
  );

  return $form;
}

/**
 * Determines whether an image set machine name already exists.
 */
function _srcset_image_set_name_exists($machine_name) {
  return (bool) srcset_image_set_load($machine_name);
}

/**
 * Submit image set add/edit form.
 */
function srcset_image_sets_form_submit($form, &$form_state) {
  $values = $form_state['values'];

  // Save image set to config.
  config_set('srcset_image.sets', $values['machine_name'], array(
    'name' => $values['name'],
    'machine_name' => $values['machine_name'],
    'image_styles' => array_keys(array_filter($values['image_styles'])),
  ));

  // Show confirmation message and redirect to list page.
  backdrop_set_message(t('The image set %name has been saved.', array('%name' => $values['name'])));
  $form_state['redirect'] = 'admin/config/media/srcset-image';
}

/**
 * Delete form for image sets.
 */
function srcset_image_sets_form_delete($form, &$form_state, $image_set) {
  $form['image_set'] = array(
    '#type' => 'value',
    '#value' => $image_set,
  );

  $question = t('Are you sure you want to delete the image set %name?', array('%name' => $image_set['name']));
  $path = 'admin/config/media/srcset-image';
  return confirm_form($form, $question, $path);
}

/**
 * Submit image set delete form.
 */
function srcset_image_sets_form_delete_submit($form, &$form_state) {
  $image_set = $form['image_set']['#value'];

  // Remove image set from config.
  config_clear('srcset_image.sets', $image_set['machine_name']);

  // Show confirmation message and redirect to list page.
  backdrop_set_message(t('The image set %name has been deleted.', array('%name' => $image_set['name'])));
  $form_state['redirect'] = 'admin/config/media/srcset-image';
}

