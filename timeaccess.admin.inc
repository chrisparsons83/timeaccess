<?php

/**
 * @file
 * Administration pages for the Time Access module. 
 */

/**
 * Builds list of rulesets for administration page.
 */
function timeaccess_list_rulesets($query = array(), $conditions = array()) {
  // Initialize the query array.
  $query += array(
    'conditions' => array(),
    'args' => array(),
    'limit' => 0,
  );

  // Set up the header.
  $header = array(
    'name' => array(
      'data' => t('Ruleset'),
      'field' => 'name',
      'sort' => 'asc'),
    'operations' => array(
      'data' => t('Operations')),
  );

  // Build the SQL query for the rows.
  $sql = 'SELECT taid, name FROM {timeaccess_rulesets}';
  if ($query['conditions']) {
    $sql .= ' WHERE (' . implode(') AND (', $query['conditions']). ')';
  }
  $sql .= tablesort_sql($header);
  if ($query['limit']) {
    $query = pager_query($sql, $query['limit'], 0, NULL, $query['args']);
  }
  else {
    $query = db_query($sql, $query['args']);
  }

  // Convert to array for theming
  $rows = array();
  while ($row = db_fetch_array($query)) {
    // Grab taid for URLs, and unset from table.
    $temp_taid = $row['taid'];
    unset($row['taid']);

    // Create operations links.
    if (isset($header['operations'])) {
      $operations = array();
      $operations['edit'] = array(
        'title' => t('Edit'),
        'href' => 'admin/build/timeaccess/edit/' . $temp_taid,
      );
      $operations['delete'] = array(
        'title' => t('Delete'),
        'href' => 'admin/build/timeaccess/delete/' . $temp_taid,
      );
      $row['operations'] = theme('links', $operations, array('class' => 'links inline nowrap'));
    }
    $rows[(string) $temp_taid] = $row;
  }


  // Give a message if there are no rulesets.
  if (empty($rows)) {
    $rows[] = array(array(
      'data' => t('No Rulesets Available.'),
      'colspan' => count($header),
      'class' => 'empty',
    ));
  }

  // Return the output as a table.
  return theme('table', $header, $rows);
}

/**
 * Add new ruleset.
 */
function timeaccess_ruleset_edit_form(&$form_state) {
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#description' => t("Enter in the name of the ruleset.  This is used for administrative purposes."),
    '#size' => 42,
    '#maxlength' => 255,
    '#required' => TRUE,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

/**
 * Save the ruleset to the database.
 */
function timeaccess_ruleset_edit_form_submit($form, &$form_state) {
  timeaccess_ruleset_save($form_state['values']);
  drupal_set_message(t('The ruleset has been saved.'));
  $form_state['redirect'] = 'admin/build/timeaccess';
}

/**
 * Save the ruleset to the database.
 */
function timeaccess_ruleset_save($ruleset) {
  dpm($ruleset);

  // Write to database
  if(empty($ruleset['taid'])) {
    drupal_write_record('timeaccess_rulesets', $ruleset);
  }
  else {
    drupal_write_record('timeaccess_rulesets', $ruleset, array('taid'));
  }

  return $ruleset;
}
