#include <stdio.h>

enum Method { GET, POST, PUT, DELETE };

typedef struct {
  enum Method method;
  union {
    struct {
      char *path;
      char *query_params;
    } get;

    struct {
      char *path;
      char *body;
      char *content_type;
    } post;

    struct {
      char *path;
      char *body;
      char *content_type;
    } put;

    struct {
      char *path;
    } delete;
  };
} Request;

void print_request(Request *req) {
  printf("HTTP Method: ");

  switch (req->method) {
  case GET:
    printf("GET\n");
    printf("Path: %s\n", req->get.path);
    if (req->get.query_params) {
      printf("Query Parameters: %s\n", req->get.query_params);
    }
    break;

  case POST:
    printf("POST\n");
    printf("Path: %s\n", req->post.path);
    printf("Content-Type: %s\n", req->post.content_type);
    printf("Body: %s\n", req->post.body);
    break;

  case PUT:
    printf("PUT\n");
    printf("Path: %s\n", req->put.path);
    printf("Content-Type: %s\n", req->put.content_type);
    printf("Body: %s\n", req->put.body);
    break;

  case DELETE:
    printf("DELETE\n");
    printf("Path: %s\n", req->delete.path);
    break;
  }
  printf("\n");
}

int main(void) {
  Request get_req = {
      .method = GET,
      .get = {.path = "/api/users", .query_params = "page=1&limit=10"}};

  Request post_req = {
      .method = POST,
      .post = {.path = "/api/users",
               .content_type = "application/json",
               .body = "{\"name\":\"John\",\"email\":\"john@example.com\"}"}};

  Request delete_req = {.method = DELETE, .delete = {.path = "/api/users/123"}};

  print_request(&get_req);
  print_request(&post_req);
  print_request(&delete_req);

  return 0;
}
