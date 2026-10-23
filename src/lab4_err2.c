#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int id;
  char *message;
  char *timestamp;
	
} LogEntry;

LogEntry *create_entry(int id, const char *msg, const char *time) {
  LogEntry *entry = (LogEntry *)malloc(sizeof(LogEntry));
  if (!entry) return NULL;

  entry->id = id;
  entry->message = strdup(msg);
  entry->timestamp = strdup(time);
    
  //entry->timestamp = strdup("00:00:00");
  // Запис нового таймштампу перекриває  попередній, і він залишиться висіти в пам'яті
  // (Функція strdup робить копію рядка виділяючи пам'ять у купі) 
  return entry;
}

void free_entry(LogEntry *entry) {
    if (!entry) return;

    free(entry->message);
    free(entry->timestamp);
    // free(entry->message);
	// Подвійне звільнення 
    free(entry);
}
void format_log_header(const char *title) {
    char header_buffer[128]; //Було 16, збільшено через недостатню кількість байтів для рядка.
    // strcpy(header_buffer, title);
    // strcpy старий метод, не перевіряє перевищення буфера при копіюванні.
    // більш сучасний та безпечний варіант через strNcpy
    strncpy(header_buffer, title, sizeof(header_buffer) - 1); // -1 від header_buffer, через те що необхідно додати \0.  
	header_buffer[sizeof(header_buffer) - 1] = '\0';
	
    printf("Header: %s\n", header_buffer);
}

int main()
{

  printf("--- Запуск програми журналу подій ---\n");

  // 1. Тест заголовочного буфера f
  format_log_header("Цей заголовок є занадто довгим для 16 байт");

  // 2. Тест створення запису

  LogEntry *entry = create_entry(101, "Системна помилка підключення", "12:45:30");

  if (entry) {

    printf("3anuc [%d] [%s]: %s\n", entry->id, entry->timestamp,
    entry->message);
    free_entry(entry);
  }
  return 0;

}