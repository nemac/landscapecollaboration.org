<?php

/**
 * @file
 * Contains the theme function override for 'field'.
 */

/**
 * Returns HTML for a field.
 *
 * @ingroup themeable
 */
function wflc_field__field_workflow_guide($variables) {
  $terms = _get_workflow_terms();
  $items = $variables['items'];
  $size = sizeof($items);

  $output = '';

  // Render the label, if it's not hidden.
  if (!$variables['label_hidden']) {
    $output .= '<div class="field__label"' . $variables['title_attributes'] . '>' . $variables['label'] . ':&nbsp;</div>';
  }

  // Render the items.
  $output .= '<div class="field__items"' . $variables['content_attributes'] . '>';
  foreach ($terms as $delta => $term) {
    $classes = 'field__item ' . ($delta % 2 ? 'odd' : 'even');
    for ($i = 0; $i < $size; $i++) {
        $item_name = '';
        if (array_key_exists('#markup', $items[$i])) {
            $item_name = $items[$i]['#markup'];
        } elseif (array_key_exists('#title', $items[$i])) {
            $item_name = $items[$i]['#title'];
        }

        if ($term->name === $item_name) {
            $classes .= ' active';
            break;
        }
    }

    $output .= '<div class="' . $classes . '">' . $term->name . '</div>';
  }
  $output .= '</div>';

  // Render the top-level DIV.
  $output = '<div class="' . $variables['classes'] . '"' . $variables['attributes'] . '>' . $output . '</div>';

  return $output;
}

function _get_workflow_terms() {
    $WORKFLOW_MACHINE_NAME = 'workflow_guide';

    $vid = taxonomy_vocabulary_machine_name_load($WORKFLOW_MACHINE_NAME)->vid;
    $terms = taxonomy_get_tree($vid);

    return $terms;
}
