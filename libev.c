#include <ev.h>
#include <stdio.h>

ev_timer timeout_watcher;

static void timeout_cb(EV_P_ ev_timer* w, int revents) {
  printf("timeout");
  ev_break (EV_A_ EVBREAK_ONE);
}

int main(int argc, char** argv) {
  printf("libev example using version %d.%d\n", ev_version_major(), ev_version_minor());
  struct ev_loop* loop = EV_DEFAULT;

  ev_timer_init(&timeout_watcher, timeout_cb, 5.0, 0.);
  ev_timer_start(loop, &timeout_watcher);

  ev_run (loop, 0);

  return 0;
}
