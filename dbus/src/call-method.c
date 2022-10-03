#define DBUS_API_SUBJECT_TO_CHANGE
#include <dbus/dbus.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "example.h"

const char* client_object_name = "example.client";

int main(int argc, char** argv) {
  DBusMessage* msg;
  DBusMessageIter args;
  DBusConnection* conn;
  DBusError err;
  DBusPendingCall* pending;
  int ret;
  bool stat;
  dbus_uint32_t level;
  char* method_arg = "stringArg";

  printf("Calling remote method with: %s\n", method_arg);

  dbus_error_init(&err);

  // connect to the system bus and check for errors
  conn = dbus_bus_get(DBUS_BUS_SESSION, &err);
  if (dbus_error_is_set(&err)) { 
    fprintf(stderr, "Connection Error (%s)\n", err.message); 
    dbus_error_free(&err);
  }
  if (conn == NULL) { 
    exit(1); 
  }

  // request our name on the bus
  ret = dbus_bus_request_name(conn,
                              client_object_name,
                              DBUS_NAME_FLAG_REPLACE_EXISTING,
                              &err);

  if (dbus_error_is_set(&err)) { 
    fprintf(stderr, "Name Error (%s)\n", err.message); 
    dbus_error_free(&err);
  }

  if (DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER != ret) { 
    exit(1);
  }

  // create a new method call and check for errors
  msg = dbus_message_new_method_call(server_object_name,      // target for the method call
                                     "/test/method/Object", // object to call on
                                     interface_type,
                                     interface_member);
  if (msg == NULL) { 
    fprintf(stderr, "Message Null\n");
    exit(1);
  }

  printf("msg desination: %s\n", dbus_message_get_destination(msg));
  printf("msg interface: %s\n", dbus_message_get_interface(msg));
  printf("msg member: %s\n", dbus_message_get_member(msg));

  // Append arguments to msg
  dbus_message_iter_init_append(msg, &args);

  // Add the method argument:
  if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_STRING, &method_arg)) {
    fprintf(stderr, "Out Of Memory!\n"); 
    exit(1);
  }
   
  // send message and get a handle for a reply
  if (!dbus_connection_send_with_reply (conn, msg, &pending, -1)) {
    fprintf(stderr, "Out Of Memory!\n"); 
    exit(1);
  }
  if (pending == NULL) { 
    fprintf(stderr, "Pending Call Null\n"); 
    exit(1); 
  }
  dbus_connection_flush(conn);
   
  printf("Request Sent\n");
   
  // free message
  dbus_message_unref(msg);
   
  // block until we recieve a reply
  dbus_pending_call_block(pending);

  // get the reply message
  msg = dbus_pending_call_steal_reply(pending);
  if (msg == NULL) {
    fprintf(stderr, "Reply Null\n"); 
    exit(1); 
  }
  // free the pending message handle
  dbus_pending_call_unref(pending);

  // read the parameters
  if (!dbus_message_iter_init(msg, &args)) {
    fprintf(stderr, "Message has no arguments!\n"); 
  } else if (DBUS_TYPE_BOOLEAN != dbus_message_iter_get_arg_type(&args)) {
    fprintf(stderr, "Argument is not boolean!\n"); 
  } else {
    dbus_message_iter_get_basic(&args, &stat);
  }

  if (!dbus_message_iter_next(&args)) {
    fprintf(stderr, "Message has too few arguments!\n"); 
  } else if (DBUS_TYPE_UINT32 != dbus_message_iter_get_arg_type(&args)) {
    fprintf(stderr, "Argument is not int!\n"); 
  } else {
    dbus_message_iter_get_basic(&args, &level);
  }

  printf("Got Reply: %d, %d\n", stat, level);
   
  // free reply and close connection
  dbus_message_unref(msg);   

  return 0;
}

