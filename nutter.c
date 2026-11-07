#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

const char* RU_ALPHABET = {
    " ", "а", "б", "в", "г", "д", "е", "ё", "ж", "з", "и", 
    "й", "к", "л", "м", "н", "о", "п", "р", "с", "т", "у", 
    "ф", "х", "ц", "ч", "ш", "щ", "ъ", "ы", "ь", "э", "ю", "я"
};

const char* EN_ALPHABET = {
    " ", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", 
    "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", 
    "v", "w", "x", "y", "z"
};

void trim(char* str) {
    char* p = str;
    int l = strlen(p);
    while (l > 0 && isspace((unsigned char)p[l - 1])) p[--l] = 0;
    while (*p && isspace((unsigned char)*p)) ++p, --l;
    memmove(str, p, l + 1);
}

// РЕЖИМ 1: Интерактивный терминал (REPL)
void run_shell() {
    char line;
    int current_lang = 0; // 0 - RU, 1 - EN
    printf("=== Nutter Interactive Shell v1.3 ===\n");
    printf("Пиши команды в реальном времени. Для выхода введи 'exit'.\n\n");

    while (1) {
        printf("nut> ");
        fflush(stdout);
        if (!fgets(line, sizeof(line), stdin)) break;
        trim(line);
        if (strlen(line) == 0) continue;
        if (strcmp(line, "exit") == 0) {
            printf("Пока, нутер!\n");
            break;
        }
        if (strncmp(line, "language:", 9) == 0) {
            char* lang_part = line + 9;
            while (*lang_part == ' ') lang_part++;
            if (strncmp(lang_part, "RU", 2) == 0) {
                current_lang = 0;
                printf("[Система]: Переключено на русский язык\n");
            } else if (strncmp(lang_part, "EN", 2) == 0) {
                current_lang = 1;
                printf("[System]: Switched to English mode\n");
            } else {
                printf("Ошибка: Неизвестный язык\n");
            }
            continue;
        }
        if (strcmp(line, "enter") == 0) {
            printf("\n");
            continue;
        }
        if (strncmp(line, "erno", 4) == 0) {
            char* start = strchr(line, '[');
            char* end = strchr(line, ']');
            if (!start || !end || end < start) {
                printf("Ошибка синтаксиса: Проверь скобки\n");
                continue;
            }
            char* inner = strndup(start + 1, end - start - 1);
            char* token = strtok(inner, ", ");
            while (token != NULL) {
                int num = atoi(token);
                if (num == 60) printf("!");
                else if (current_lang == 0 && num >= 0 && num <= 33) printf("%s", RU_ALPHABET[num]);
                else if (current_lang == 1 && num >= 0 && num <= 26) printf("%s", EN_ALPHABET[num]);
                token = strtok(NULL, ", ");
            }
            free(inner);
            printf("\n");
            continue;
        }
        printf("Ошибка синтаксиса: '%s'\n", line);
    }
}

// РЕЖИМ 2: Сверхбыстрое выполнение файлов
void run_file(const char* filename) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        write(1, "Критическая ошибка: Файл не найден\n", 64);
        return;
    }
    struct stat sb;
    fstat(fd, &sb);
    if (sb.st_size == 0) { close(fd); return; }
    char* file_in_memory = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    close(fd);
    if (file_in_memory == MAP_FAILED) return;

    char* output_buffer = malloc(sb.st_size * 4); 
    size_t out_idx = 0;
    char* cursor = file_in_memory;
    char* file_end = file_in_memory + sb.st_size;
    int current_lang = 0;

    while (cursor < file_end) {
        while (cursor < file_end && (*cursor == ' ' || *cursor == '\n' || *cursor == '\r')) cursor++;
        if (cursor >= file_end) break;

        if (strncmp(cursor, "language:", 9) == 0) {
            cursor += 9;
            while (cursor < file_end && *cursor == ' ') cursor++;
            if (strncmp(cursor, "RU", 2) == 0) { current_lang = 0; cursor += 2; }
            else if (strncmp(cursor, "EN", 2) == 0) { current_lang = 1; cursor += 2; }
            else goto error;
            continue;
        }
        if (strncmp(cursor, "enter", 5) == 0) {
            output_buffer[out_idx++] = '\n';
            cursor += 5;
            continue;
        }
        if (strncmp(cursor, "erno", 4) == 0) {
            while (cursor < file_end && *cursor != '[') cursor++;
            cursor++;
            while (cursor < file_end && *cursor != ']') {
                while (cursor < file_end && (*cursor == ' ' || *cursor == ',')) cursor++;
                if (*cursor == ']') break;
                int num = 0;
                while (cursor < file_end && *cursor >= '0' && *cursor <= '9') {
                    num = num * 10 + (*cursor - '0');
                    cursor++;
                }
                const char* letter = "";
                if (num == 60) letter = "!";
                else if (current_lang == 0 && num >= 0 && num <= 33) letter = RU_ALPHABET[num];
                else if (current_lang == 1 && num >= 0 && num <= 26) letter = EN_ALPHABET[num];
                size_t len = strlen(letter);
                if (len > 0) { memcpy(&output_buffer[out_idx], letter, len); out_idx += len; }
            }
            cursor++;
            continue;
        }
    error:
        write(1, "Системный сбой Nutter: Ошибка синтаксиса\n", 71);
        munmap(file_in_memory, sb.st_size); free(output_buffer); return;
    }
    output_buffer[out_idx++] = '\n';
    write(1, output_buffer, out_idx);
    munmap(file_in_memory, sb.st_size); free(output_buffer);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        run_shell(); // Без файлов — запускаем терминал
    } else {
        run_file(argv[1]); // С аргументом — выполняем код
    }
    return 0;
}
