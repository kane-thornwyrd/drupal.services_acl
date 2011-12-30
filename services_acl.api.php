<?php

/**
 * @file
 * Hooks provided by Services ACL.
 */
/**
 * @addtogroup hooks
 * @{
 */

/**
 * Allow Developers to implement a way to understand what's the resource's type we have deal with.
 * Increase testability too.
 *
 * @param array $method
 *   Usually the table containing the calling method of the resource, as we have in a authenticate_call
 *   callback from a hook_services_authentication_info() implementation.
 *
 * @return string
 *   The resource identifier that match this method.
 */
function hook_services_resources_analyser(array $method) {

}

/**
 * Allow to provide a "better" resource type than those already found.
 *
 * @param string $resource_type_name
 *   The resource type name in a array, you'll have to do this to get it :
 *   $resource_type_name = $resource_type_name[0];
 *
 * @param array $method
 *   The method object, useful to determine the resource type. /!\ CAUTION /!\ passed by reference !
 */
function hook_services_resources_analysed_alter(array $resource_type_name,
  array &$method) {

}

/**
 * @}
 */
// Here's true examples, because that's the default implementation in use !

/**
 * Implements hook_services_resources_analyser().
 */
function services_acl_services_resources_analyser(array $method) {
  $resources = module_invoke_all('services_resources');
  $resource = NULL;

  if (isset($method['file']['name']) && preg_match('#resources/(?P<resource>\w+)_resource#',
      $method['file']['name'], $m)) {
    $resource = $m['resource'];
  }
  if (
    isset($method['file']['module'])
    && $method['file']['module'] === 'services_views'
  ) {
    $resource = 'views';
  }
    return $resource;
}

// I don't need this example for now, but in case you didn't get how to implement it.
/**
 * Implements hook_services_resources_analysed_alter().
 */
//function services_acl_services_resources_analysed_alter(array $resource_type_name, array &$method) {
//  $resource_type_name = $resource_type_name[0];
//  dd(func_get_args());
//}

