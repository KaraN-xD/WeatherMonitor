#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_CITY_LENGTH 50
#define DATA_FILE "weather_data.txt"
#define USER_FILE "users.txt"
#define MAX_USERNAME 30
#define MAX_PASSWORD 30

// Structure to hold weather information
typedef struct {
    char city[MAX_CITY_LENGTH];
    float temperature;
    float humidity;
    float wind_speed;
    char weather_condition[20];
} WeatherData;

// Function to simulate weather data
WeatherData generate_weather_data(const char* city) {
    WeatherData data;
    strcpy(data.city, city);

    data.temperature = (float)(rand() % 40) + (float)(rand() % 10) / 10.0f;
    data.humidity = (float)(rand() % 100) + (float)(rand() % 10) / 10.0f;
    data.wind_speed = (float)(rand() % 30) + (float)(rand() % 10) / 10.0f;

    const char* conditions[] = {"Sunny", "Cloudy", "Rainy", "Windy", "Clear"};
    strcpy(data.weather_condition, conditions[rand() % 5]);

    return data;
}

void save_weather_data(WeatherData data) {
    FILE* file = fopen(DATA_FILE, "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    char date_time[26];
    strftime(date_time, 26, "%Y-%m-%d %H:%M:%S", t);

    fprintf(file, "%s | %s | Temperature: %.1f°C | Humidity: %.1f%% | Wind Speed: %.1f km/h | Condition: %s\n",
            date_time, data.city, data.temperature, data.humidity, data.wind_speed, data.weather_condition);

    fclose(file);
}

void display_weather_history(const char* city) {
    FILE* file = fopen(DATA_FILE, "r");
    if (file == NULL) {
        printf("No weather history available.\n");
        return;
    }

    char line[256];
    int found = 0;
    printf("\nWeather History for %s:\n", city);
    printf("----------------------------------------\n");

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, city) != NULL) {
            printf("%s", line);
            found = 1;
        }
    }
    if (!found) {
        printf("No data available for %s.\n", city);
    }

    fclose(file);
}

// User Authentication function
int authenticate_user(const char* username, const char* password, char* role) {
    FILE* file = fopen(USER_FILE, "r");
    if (file == NULL) {
        printf("User file not found!\n");
        return 0;
    }

    char line[100], file_user[MAX_USERNAME], file_pass[MAX_PASSWORD], file_role[10];
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^,],%[^,],%s", file_user, file_pass, file_role);
        if (strcmp(username, file_user) == 0 && strcmp(password, file_pass) == 0) {
            strcpy(role, file_role);
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

// User Registration function
void register_user();

void main_menu();

void register_user() {
    char username[MAX_USERNAME], password[MAX_PASSWORD];
    printf("\nRegister New User\n");
    printf("Enter new username: ");
    fgets(username, MAX_USERNAME, stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Enter new password: ");
    fgets(password, MAX_PASSWORD, stdin);
    password[strcspn(password, "\n")] = 0;

    FILE* file = fopen(USER_FILE, "a");
    if (!file) {
        printf("Error opening user file!\n");
        return;
    }

    fprintf(file, "%s,%s,user\n", username, password);
    fclose(file);
    printf("Registration successful! You can now log in.\n");

    main_menu();
}

void admin_menu() {
    int choice;
    char city[MAX_CITY_LENGTH];
    while (1) {
        printf("\nAdmin Menu\n");
        printf("1. View weather history\n");
        printf("2. Delete weather history for a city\n");
        printf("3. Exit to login and registration page\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Enter city name: ");
                fgets(city, MAX_CITY_LENGTH, stdin);
                city[strcspn(city, "\n")] = 0;
                display_weather_history(city);
                break;

            case 2: {
                printf("Enter city name to delete history: ");
                fgets(city, MAX_CITY_LENGTH, stdin);
                city[strcspn(city, "\n")] = 0;

                FILE* original = fopen(DATA_FILE, "r");
                FILE* temp = fopen("temp.txt", "w");

                if (!original || !temp) {
                    printf("Error opening file!\n");
                    break;
                }

                char line[256];
                while (fgets(line, sizeof(line), original)) {
                    if (strstr(line, city) == NULL) {
                        fputs(line, temp);
                    }
                }

                fclose(original);
                fclose(temp);

                remove(DATA_FILE);
                rename("temp.txt", DATA_FILE);
                printf("Weather history for %s deleted.\n", city);
                break;
            }

            case 3:
                main_menu();
                return;
            default:
                printf("Invalid choice!\n");
        }
    }
}

void main_menu() {
    srand(time(NULL));
    int initial_choice;
    char username[MAX_USERNAME], password[MAX_PASSWORD], role[10];

   printf("Welcome to Weather Monitoring System\n");
    printf("1. Login\n");
    printf("2. Register\n");
    printf("3. Exit\n");
    printf("Enter choice: ");
    scanf("%d", &initial_choice);
    getchar();

    if (initial_choice == 3) {
        printf("Exiting program. Thank you!\n");
        exit(0);
    }
    if (initial_choice == 2) {
        register_user();
        return;
    }

    printf("Login\n");
    printf("Username: ");
    fgets(username, MAX_USERNAME, stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Password: ");
    fgets(password, MAX_PASSWORD, stdin);
    password[strcspn(password, "\n")] = 0;

    if (!authenticate_user(username, password, role)) {
        printf("Invalid credentials! Exiting...\n");
        return;
    }

    printf("Login successful. Welcome, %s (%s)!\n", username, role);

    if (strcmp(role, "admin") == 0) {
        admin_menu();
        return;
    }

    int choice;
    char city[MAX_CITY_LENGTH];
    while (1) {
        printf("\nWeather Monitoring System\n");
        printf("1. Check weather for a city\n");
        printf("2. View weather history\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Enter city name: ");
                fgets(city, MAX_CITY_LENGTH, stdin);
                city[strcspn(city, "\n")] = 0;
                if (strlen(city) == 0) {
                    printf("City name cannot be empty.\n");
                    break;
                }
                WeatherData current_weather = generate_weather_data(city);

                printf("\nCurrent Weather for %s:\n", city);
                printf("Temperature: %.1f°C\n", current_weather.temperature);
                printf("Humidity: %.1f%%\n", current_weather.humidity);
                printf("Wind Speed: %.1f km/h\n", current_weather.wind_speed);
                printf("Condition: %s\n", current_weather.weather_condition);

                save_weather_data(current_weather);
                printf("\nWeather data has been saved to file.\n");
                break;

            case 2:
                printf("Enter city name to view history: ");
                fgets(city, MAX_CITY_LENGTH, stdin);
                city[strcspn(city, "\n")] = 0;
                display_weather_history(city);
                break;

            case 3:
                printf("Thank you for using the Weather Monitoring System!\n");
                return;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}

int main() {
    main_menu();
    return 0;
}