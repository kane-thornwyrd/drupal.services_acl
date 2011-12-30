<?php

/**
 * @file
 * Include file for services_acl module.
 */

/**
 * Allow or deny request depending on roles allowed.
 *
 * @param array $settings
 *  The settings for the authentication module.
 * @param array $method
 *  The method that's being called
 * @param array $args
 *  The arguments that are being used to call the method
 * @return void|string
 *  Returns nothing, or a error message if authentication fails
 */
function _services_acl_authenticate_call($settings, $method, $args) {
  global $user;
  $user = services_get_server_info('original_user');


  dd($method);
  $resource_type = _services_acl_determine_type($method);
  $resources = module_invoke_all('services_resources');
  foreach($user->roles as $key => $name) {

  }

  return FALSE;

}

/**
 * Provide a logical way to determine what's the resource type we deal with.
 * Call the hook_services_resources_analyser() and hook_services_resources_analysed_alter().
 *
 * @param array $method
 *   the method array provided by services when the resource is called.
 *
 * @return string
 *   the typename of the resource called.
 */
function _services_acl_determine_type(array $method) {
  module_load_include('api.php', 'services_acl');
  $resource = module_invoke_all('services_resources_analyser', $method);
  drupal_alter('services_resources_analysed', $resource, $method);
  return $resource[0];
}

/**
 * Function returning the form used for the settings of this auth type for each service.
 *
 * @param array $settings
 *   Settings provided by services module.
 *
 * @return array
 *   The form array for the setting panel of each Service.
 */
function _services_acl_security_settings($settings) {

  drupal_add_css(drupal_get_path('module', 'services_acl') . '/services_acl.main.css', array('type' => 'file'));

  // Retrieve role names for columns.
  $role_names = user_roles();
  $resources = module_invoke_all('services_resources');

//  dpm($settings);
  // Store $role_names for use when saving the data.
  foreach ($role_names as $rid => $role_name) {
    $form[$rid] = array(
      '#title' => $role_name,
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#attributes' => array(
        'class' => array('services-acl-block')
      )
    );
    foreach ($resources as $resource_name => $resource_data) {
      $form[$rid][$resource_name] = array(
        '#title' => $resource_name,
        '#type' => 'checkboxes',
        '#default_value' => $settings[$rid][$resource_name],
      );
      foreach ($resource_data as $action => $datas) {
        if ($action == 'actions') {
          foreach ($datas as $subaction => $subdata) {
            $form[$rid][$resource_name]['#options'][$subaction] = $subaction;
          }
        }
        else {
          $form[$rid][$resource_name]['#options'][$action] = $action;
        }
      }
    }
  }



  return theme('resources_roles_permissions',
      array('form' => $form, 'resources' => $resources, 'roles' => $role_names));
}

//TODO Turn this into a permission's page look-a-like table !
/**
 * Implements template_preprocess_HOOK().
 * For the resources roles permission admin tab.
 * My first will was to have a permission's page look-a-like table, but I'm too whacked for now to do it
 * properly.
 * So I prefered to comment this whole bunch of crapy code.
 */
function template_preprocess_resources_roles_permissions(&$vars) {
//  foreach ($vars as $key => $value) {
//    ${$key} = $value;
//  }
//  $headers = array();
//  $rows = array();
//  $headers[] = '';
//  foreach (element_children($form) as $rid) {
//    $headers[] = $roles[$rid];
//    foreach (element_children($form[$rid]) as $resource_name) {
//      $rows[$resource_name] = array(
//        'data' => array($resource_name),
//        'class' => array('resource'),
//        'colspan' => count($form) + 1
//      );
//      foreach ($form[$rid][$resource_name]['#options'] as $action_name) {
//        if (!isset($rows[$resource_name . '-' . $action_name]) || !is_array($rows[$resource_name . '-' . $action_name])) {
//          $rows[$resource_name . '-' . $action_name] = array($action_name);
//        }
//        $rows[$resource_name . '-' . $action_name] = array_merge_recursive($rows[$resource_name . '-' . $action_name],
//          array(
//          'data' => array('0' => $action_name),
//          'class' => array('checkbox')
//          ));
//      }
//    }
//  }
//  $vars['form']['table'] = array(
//    '#markup' => theme(
//      'table', array(
//      'header' => $headers,
//      'rows' => $rows,
//      )
//    ),
//  );
}

/**
 * Theme function for the resources roles permission admin tab.
 *
 * @param type $vars
 *
 * @return type
 */
function theme_resources_roles_permissions($vars) {
  return $vars['form'];
}
