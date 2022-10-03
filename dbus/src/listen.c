#define DBUS_API_SUBJECT_TO_CHANGE
#include <dbus/dbus.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "example.h"

void reply_to_method_call(DBusMessage* msg, DBusConnection* conn) {
  DBusMessage* reply;
  DBusMessageIter args;
  int stat = 1;
  dbus_uint32_t level = 21614;
  dbus_uint32_t serial = 0;
  char* param = "";

  // read the arguments
  if (!dbus_message_iter_init(msg, &args)) {
    fprintf(stderr, "Message has no arguments!\n"); 
  } else if (dbus_message_iter_get_arg_type(&args) != DBUS_TYPE_STRING ) {
    fprintf(stderr, "Argument is not string!\n"); 
  } else {
    dbus_message_iter_get_basic(&args, &param);
  }

  printf("Method called with %s\n", param);

  reply = dbus_message_new_method_return(msg);

  // add the arguments to the reply
  dbus_message_iter_init_append(reply, &args);

  if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_BOOLEAN, &stat)) { 
    fprintf(stderr, "Out Of Memory!\n"); 
    exit(1);
  }

  if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_UINT32, &level)) { 
    fprintf(stderr, "Out Of Memory!\n"); 
    exit(1);
  }

  // send the reply && flush the connection
  if (!dbus_connection_send(conn, reply, &serial)) {
    fprintf(stderr, "Out Of Memory!\n"); 
    exit(1);
  }
  printf("Sent reply...\n", args);
  dbus_connection_flush(conn);

  // free the reply
  dbus_message_unref(reply);
}

int main(int argc, char** argv) {
  DBusMessage* msg;
  DBusMessage* reply;
  DBusMessageIter args;
  DBusConnection* conn;
  DBusError err;
  int ret;
  char* param;


  // initialise the error
  dbus_error_init(&err);
   
  conn = dbus_bus_get(DBUS_BUS_SESSION, &err);
  if (dbus_error_is_set(&err)) { 
    fprintf(stderr, "Connection Error (%s)\n", err.message); 
    dbus_error_free(&err); 
  }

  if (NULL == conn) {
    fprintf(stderr, "Connection Null\n"); 
    exit(1); 
  }

  char* bus_id = dbus_bus_get_id(conn, &err);
  printf("bus_id: %s\n", bus_id);
  const char* connection_name = dbus_bus_get_unique_name(conn);
  printf("connection unique_name: %s\n", connection_name);
   
  ret = dbus_bus_request_name(conn,
                              server_object_name,
                              DBUS_NAME_FLAG_REPLACE_EXISTING,
                              &err);
  if (dbus_error_is_set(&err)) { 
    fprintf(stderr, "Name Error: %s\n", err.message); 
    dbus_error_free(&err);
  }

  if (DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER != ret) { 
    fprintf(stderr, "% is not 'Primary Owner' (%d)\n", server_object_name, ret);
    exit(1); 
  }

  printf("object_name: %s is listening for method calls\n", server_object_name);
  while (true) {
    dbus_connection_read_write(conn, 0);
    msg = dbus_connection_pop_message(conn);

    if (msg == NULL) { 
      sleep(1); 
      continue; 
    }

    if (dbus_message_is_method_call(msg, interface_type, interface_member)) {
      printf("Received: msg destination: (%s)\n", dbus_message_get_destination(msg));
      reply_to_method_call(msg, conn);
    }

    dbus_message_unref(msg);
  }

  dbus_connection_close(conn);
  return 0;
}
