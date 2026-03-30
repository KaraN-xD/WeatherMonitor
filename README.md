## Weather Monitoring System

A simple C program that simulates and records weather data for different cities. The program stores the weather information in a file for future analysis.

## Features

-> Check current weather for any city (simulated data)
-> View weather history for a specific city
-> Automatic data storage with timestamp
-> Records temperature, humidity, wind speed, and weather conditions

## Weather Data Storage

The weather data is stored in a file named `weather_data.txt` in the following format:
``` YYYY-MM-DD HH:MM:SS | City | Temperature: XX.X°C | Humidity: XX.X% | Wind Speed: XX.X km/h | Condition: XXXXX ```

## Usage

1. When you run the program, you'll see a menu with three options:
   -> Check weather for a city
   -> View weather history
   -> Exit

2. To check weather for a city:
   -> Select option 1
   -> Enter the city name
   -> The program will display current (simulated) weather data and save it to the file

3. To view weather history:
   -> Select option 2
   -> Enter the city name
   -> The program will display all recorded weather data for that city 
      - (if the data is not found it will show \\No data available for "following city"\\ )

4. To exit:
   -> Select option 3

## conclusion 

This is a program made in c tells the random weather data genereted for any particular city.