<?php

/**
 * @file
 * Administration pages for the Time Access module. 
 */

/**
 * Builds list of rulesets for administration page.
 */
function timeaccess_list_rulesets() {
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

  // Generate the rows
  $rows = array();
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

  if(empty($ruleset['taid'])) {
    drupal_write_record('timeaccess_rulesets', $ruleset);
  }
  else {
    drupal_write_record('timeaccess_rulesets', $ruleset, array('taid'));
  }

  return $ruleset;
}
