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
function timeaccess_add_ruleset() {
  return $output;
}
