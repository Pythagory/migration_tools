<?php

/**
 * @file
 * Defines migration classes for the Western District of New York.
 */

/**
 * Migrates .html files from /usao-wdny to page nodes.
 *
 * @package doj_migration
 * @subpackage usao-wdny
 */
class UsaoWdnyPageMigration extends JusticeHtmlToPageMigration {

  /**
   * {@inheritdoc}
   */
  public function __construct($arguments) {

    // Define source directories.
    $source_dirs = array(
      0 => 'usao/nyw',
    );

    $arguments['source_parser_class'] = "DistrictsSourceParser";

    $options = array('recurse' => FALSE);

    // Parent constructor will set $this->source, $this->destination, and
    // $this->map.
    parent::__construct($arguments, $source_dirs, NULL, $options);
    $this->dependencies = array('UsaoDistrict');
    $this->description = t('Migrates pages from the Western District of New York.');
    $this->addFieldMapping('og_group_ref')
      ->defaultValue('usao-wdny')
      ->sourceMigration('UsaoDistrict');
  }

  /**
   * {@inheritdoc}
   */
  public function prepareRow($row) {
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }
    module_load_include("inc", "doj_migration", "includes/doj_migration");

    $skip_these = array(
      'usao/nyw/usao-header.html',
      'usao/nyw/usao-rightCol.html',
      'usao/nyw/usao-footer.html',
    );

    return doj_migration_check_skip_this($row->legacy_path, $skip_these);
  }
}


/**
 * Migrates files (*.pdf) from /usao-wdny.
 *
 * @package doj_migration
 * @subpackage usao-wdny
 */
class UsaoWdnyFileMigration extends JusticeDeployableBinaryFileMigration {

  /**
   * {@inheritdoc}
   */
  public function __construct($arguments) {
    $this->description = t('Migrates non-image files from the usao-wdny subdirectory.');
    $this->dependencies = array('UsaoDistrict');

    // Match .pdf files only.
    $source_dirs = array(
      0 => 'usao/nyw',
      1 => 'usao/nyw/nyw_document',
      2 => 'usao/nyw/lecc',
      3 => 'usao/nyw/press/press_releases',
    );

    $regex = '/.*\.(pdf|txt|rtf|doc|docx|xls|xlsx|csv|mp3|mp4|wpd|wp|qpw|xml|ppt|pptx)/';
    $dest_dir = 'public:///usao-wdny/docs';

    $options = array('recurse' => FALSE);

    // This will setup $this->map, $this->destination, and $this->source.
    // It will also add field mappings for file location and redirects, which
    // relies on prepareRow() defining $row->filepath and $row->legacy_path.
    parent::__construct($arguments, $source_dirs, $dest_dir, $regex, $options);
  }

  /**
   * {@inheritdoc}
   */
  public function prepareRow($row) {
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }

  }

  /**
   * {@inheritdoc}
   */
  public function getOrganizationAbbreviation() {
    return "usao-wdny";
  }
}