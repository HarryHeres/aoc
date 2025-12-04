#include <_stdio.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char **graph;
  ssize_t line_len;
  size_t line_count;

} Graph;

typedef struct {
  size_t row;
  size_t col;
} Point;

void free_graph(Graph *graph) {
  if (graph == NULL) {
    return;
  }

  if (graph->graph != NULL) {
    for (size_t i = 0; i < graph->line_count; ++i) {
      free(graph->graph[i]);
    }
    free(graph->graph);
  }

  free(graph);
}

size_t part_two(Graph *graph) {
  if (graph == NULL) {
    return 0;
  }

  size_t rv = 0;
  size_t row = 0, col = 0;
  uint8_t curr_count = 0;
  size_t removed = 0;

  do {
    removed = 0;
    for (size_t i = 0; i < graph->line_count * graph->line_len; ++i) {
      row = i / graph->line_len;
      col = i % graph->line_len;
      curr_count = 0;

      if (graph->graph[row][col] == '@') {
        if (row == 0) {
          if (col == 0) {
            curr_count += graph->graph[row][col + 1] == '@' ? 1 : 0;
            curr_count += graph->graph[row + 1][col] == '@' ? 1 : 0;
            curr_count += graph->graph[row + 1][col + 1] == '@' ? 1 : 0;
          } else if (col == graph->line_len - 2) {
            curr_count += graph->graph[row][col - 1] == '@' ? 1 : 0;
            curr_count += graph->graph[row + 1][col] == '@' ? 1 : 0;
            curr_count += graph->graph[row + 1][col - 1] == '@' ? 1 : 0;
          } else {
            curr_count += graph->graph[row][col - 1] == '@' ? 1 : 0;
            curr_count += graph->graph[row][col + 1] == '@' ? 1 : 0;
            curr_count += graph->graph[row + 1][col - 1] == '@' ? 1 : 0;
            curr_count += graph->graph[row + 1][col] == '@' ? 1 : 0;
            curr_count += graph->graph[row + 1][col + 1] == '@' ? 1 : 0;
          }
        } else if (row == graph->line_count - 1) {
          if (col == 0) {
            curr_count += graph->graph[row][col + 1] == '@' ? 1 : 0;
            curr_count += graph->graph[row - 1][col] == '@' ? 1 : 0;
            curr_count += graph->graph[row - 1][col + 1] == '@' ? 1 : 0;
          } else if (col == graph->line_len - 2) {
            curr_count += graph->graph[row][col - 1] == '@' ? 1 : 0;
            curr_count += graph->graph[row - 1][col] == '@' ? 1 : 0;
            curr_count += graph->graph[row - 1][col - 1] == '@' ? 1 : 0;
          } else {
            curr_count += graph->graph[row][col - 1] == '@' ? 1 : 0;
            curr_count += graph->graph[row][col + 1] == '@' ? 1 : 0;
            curr_count += graph->graph[row - 1][col - 1] == '@' ? 1 : 0;
            curr_count += graph->graph[row - 1][col] == '@' ? 1 : 0;
            curr_count += graph->graph[row - 1][col + 1] == '@' ? 1 : 0;
          }
        } else {
          if (col == 0) {
            curr_count += graph->graph[row - 1][col] == '@' ? 1 : 0;
            curr_count += graph->graph[row - 1][col + 1] == '@' ? 1 : 0;
            curr_count += graph->graph[row][col + 1] == '@' ? 1 : 0;
            curr_count += graph->graph[row + 1][col] == '@' ? 1 : 0;
            curr_count += graph->graph[row + 1][col + 1] == '@' ? 1 : 0;
          } else if (col == graph->line_len - 2) {
            curr_count += graph->graph[row - 1][col] == '@' ? 1 : 0;
            curr_count += graph->graph[row - 1][col - 1] == '@' ? 1 : 0;
            curr_count += graph->graph[row][col - 1] == '@' ? 1 : 0;
            curr_count += graph->graph[row + 1][col] == '@' ? 1 : 0;
            curr_count += graph->graph[row + 1][col - 1] == '@' ? 1 : 0;
          } else {
            curr_count += graph->graph[row - 1][col - 1] == '@' ? 1 : 0;
            curr_count += graph->graph[row - 1][col] == '@' ? 1 : 0;
            curr_count += graph->graph[row - 1][col + 1] == '@' ? 1 : 0;
            curr_count += graph->graph[row][col - 1] == '@' ? 1 : 0;
            curr_count += graph->graph[row][col + 1] == '@' ? 1 : 0;
            curr_count += graph->graph[row + 1][col - 1] == '@' ? 1 : 0;
            curr_count += graph->graph[row + 1][col] == '@' ? 1 : 0;
            curr_count += graph->graph[row + 1][col + 1] == '@' ? 1 : 0;
          }
        }

        if (curr_count < 4) {
          graph->graph[row][col] = 'x';
          ++removed;
          ++rv;
        }
      }
    }
  } while (removed > 0);

  return rv;
}

size_t part_one(Graph *graph) {
  if (graph == NULL) {
    return 0;
  }

  size_t rv = 0;
  size_t row = 0, col = 0;
  uint8_t curr_count = 0;

  char *graph_copy =
      (char *)malloc(graph->line_count * graph->line_len * sizeof(char));

  for (size_t i = 0; i < graph->line_count * graph->line_len; ++i) {
    row = i / graph->line_len;
    col = i % graph->line_len;
    curr_count = 0;

    graph_copy[row * graph->line_len + col] = graph->graph[row][col];

    if (graph->graph[row][col] == '@') {
      if (row == 0) {
        if (col == 0) {
          curr_count += graph->graph[row][col + 1] == '@' ? 1 : 0;
          curr_count += graph->graph[row + 1][col] == '@' ? 1 : 0;
          curr_count += graph->graph[row + 1][col + 1] == '@' ? 1 : 0;
        } else if (col == graph->line_len - 2) {
          curr_count += graph->graph[row][col - 1] == '@' ? 1 : 0;
          curr_count += graph->graph[row + 1][col] == '@' ? 1 : 0;
          curr_count += graph->graph[row + 1][col - 1] == '@' ? 1 : 0;
        } else {
          curr_count += graph->graph[row][col - 1] == '@' ? 1 : 0;
          curr_count += graph->graph[row][col + 1] == '@' ? 1 : 0;
          curr_count += graph->graph[row + 1][col - 1] == '@' ? 1 : 0;
          curr_count += graph->graph[row + 1][col] == '@' ? 1 : 0;
          curr_count += graph->graph[row + 1][col + 1] == '@' ? 1 : 0;
        }
      } else if (row == graph->line_count - 1) {
        if (col == 0) {
          curr_count += graph->graph[row][col + 1] == '@' ? 1 : 0;
          curr_count += graph->graph[row - 1][col] == '@' ? 1 : 0;
          curr_count += graph->graph[row - 1][col + 1] == '@' ? 1 : 0;
        } else if (col == graph->line_len - 2) {
          curr_count += graph->graph[row][col - 1] == '@' ? 1 : 0;
          curr_count += graph->graph[row - 1][col] == '@' ? 1 : 0;
          curr_count += graph->graph[row - 1][col - 1] == '@' ? 1 : 0;
        } else {
          curr_count += graph->graph[row][col - 1] == '@' ? 1 : 0;
          curr_count += graph->graph[row][col + 1] == '@' ? 1 : 0;
          curr_count += graph->graph[row - 1][col - 1] == '@' ? 1 : 0;
          curr_count += graph->graph[row - 1][col] == '@' ? 1 : 0;
          curr_count += graph->graph[row - 1][col + 1] == '@' ? 1 : 0;
        }
      } else {
        if (col == 0) {
          curr_count += graph->graph[row - 1][col] == '@' ? 1 : 0;
          curr_count += graph->graph[row - 1][col + 1] == '@' ? 1 : 0;
          curr_count += graph->graph[row][col + 1] == '@' ? 1 : 0;
          curr_count += graph->graph[row + 1][col] == '@' ? 1 : 0;
          curr_count += graph->graph[row + 1][col + 1] == '@' ? 1 : 0;
        } else if (col == graph->line_len - 2) {
          curr_count += graph->graph[row - 1][col] == '@' ? 1 : 0;
          curr_count += graph->graph[row - 1][col - 1] == '@' ? 1 : 0;
          curr_count += graph->graph[row][col - 1] == '@' ? 1 : 0;
          curr_count += graph->graph[row + 1][col] == '@' ? 1 : 0;
          curr_count += graph->graph[row + 1][col - 1] == '@' ? 1 : 0;
        } else {
          curr_count += graph->graph[row - 1][col - 1] == '@' ? 1 : 0;
          curr_count += graph->graph[row - 1][col] == '@' ? 1 : 0;
          curr_count += graph->graph[row - 1][col + 1] == '@' ? 1 : 0;
          curr_count += graph->graph[row][col - 1] == '@' ? 1 : 0;
          curr_count += graph->graph[row][col + 1] == '@' ? 1 : 0;
          curr_count += graph->graph[row + 1][col - 1] == '@' ? 1 : 0;
          curr_count += graph->graph[row + 1][col] == '@' ? 1 : 0;
          curr_count += graph->graph[row + 1][col + 1] == '@' ? 1 : 0;
        }
      }

      if (curr_count < 4) {
        graph_copy[row * graph->line_len + col] = 'x';
        ++rv;
      }
    }
  }

  for (size_t i = 0; i < graph->line_count * graph->line_len; ++i) {
    printf("%c", graph_copy[i]);
  }

  free(graph_copy);

  return rv;
}

Graph *parse_input(FILE *input) {
  if (input == NULL) {
    return NULL;
  }

  fseek(input, 0, SEEK_END);
  const long file_size = ftell(input);
  fseek(input, 0, 0);

  char *line = NULL;
  size_t allocated = 0;
  ssize_t read = getline(&line, &allocated, input);

  Graph *rv = (Graph *)malloc(sizeof(Graph));
  rv->line_len = read;
  rv->line_count = file_size / read;

  char **graph = (char **)malloc(rv->line_len * sizeof(char *));
  rv->graph = graph;

  size_t curr_idx = 0;
  while (read > 0) {
    graph[curr_idx++] = line;
    line = NULL;
    read = getline(&line, &allocated, input);
  }

  return rv;
}

int main() {
  // FILE *input = fopen("data/test.txt", "r");
  FILE *input = fopen("data/input.txt", "r");

  Graph *graph = parse_input(input);
  printf("Part one: %ld\n", part_one(graph));
  printf("Part two: %ld\n", part_two(graph));

  free_graph(graph);
  return EXIT_SUCCESS;
}
