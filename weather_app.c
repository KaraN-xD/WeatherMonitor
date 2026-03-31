#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_CITY_LENGTH 50
#define DATA_FILE "weather_data.txt"

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
    
    // Simulate random weather data
    data.temperature = (float)(rand() % 40) + (float)(rand() % 10) / 10.0f; // 0 to 40 degrees
    data.humidity = (float)(rand() % 100) + (float)(rand() % 10) / 10.0f;   // 0 to 100%
    data.wind_speed = (float)(rand() % 30) + (float)(rand() % 10) / 10.0f;  // 0 to 30 km/h
    
    // Random weather condition
    const char* conditions[] = {"Sunny", "Cloudy", "Rainy", "Windy", "Clear"};
    strcpy(data.weather_condition, conditions[rand() % 5]);
    
    return data;
}

// Function to save weather data to file
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

// Function to display weather history for a city
void display_weather_history(const char* city) {
    FILE* file = fopen(DATA_FILE, "r");
    if (file == NULL) {
        printf("No weather history available.\n");
        return;
    }
    
    char line[256];
    printf("\nWeather History for %s:\n", city);
    printf("----------------------------------------\n");
    
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, city) != NULL) {
            printf("%s", line);
        }
    }
    
    fclose(file);
}

int main() {
    srand(time(NULL));  // Initialize random seed
    char city[MAX_CITY_LENGTH];
    int choice;
    
    while (1) {
        printf("\nWeather Monitoring System\n");
        printf("1. Check weather for a city\n");
        printf("2. View weather history\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // Clear input buffer
        
        switch (choice) {
            case 1:
                printf("Enter city name: ");
                fgets(city, MAX_CITY_LENGTH, stdin);
                city[strcspn(city, "\n")] = 0;  // Remove newline
                
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
                city[strcspn(city, "\n")] = 0;  // Remove newline
                display_weather_history(city);
                break;
                
            case 3:
                printf("Thank you for using the Weather Monitoring System!\n");
                return 0;
                
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    
    return 0;
} 