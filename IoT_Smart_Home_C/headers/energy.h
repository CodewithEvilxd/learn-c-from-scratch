/*
 * IoT Smart Home - Energy Monitoring Header
 * Energy consumption tracking and optimization
 */

#ifndef ENERGY_H
#define ENERGY_H

#include <time.h>
#include <stdbool.h>
#include "device.h"

// Energy Units
typedef enum {
    UNIT_WATT,
    UNIT_KILOWATT,
    UNIT_KILOWATT_HOUR,
    UNIT_VOLT,
    UNIT_AMPERE,
    UNIT_OHM
} EnergyUnit;

// Time Periods
typedef enum {
    PERIOD_MINUTE,
    PERIOD_HOUR,
    PERIOD_DAY,
    PERIOD_WEEK,
    PERIOD_MONTH,
    PERIOD_YEAR
} TimePeriod;

// Energy Reading Structure
typedef struct {
    time_t timestamp;
    int device_id;
    float value;
    EnergyUnit unit;
    char device_name[50];
    char location[50];
} EnergyReading;

// Energy Usage Statistics
typedef struct {
    float current_usage;      // Current power consumption (W)
    float daily_usage;        // Today's usage (kWh)
    float monthly_usage;      // This month's usage (kWh)
    float yearly_usage;       // This year's usage (kWh)
    float average_daily;      // Average daily usage (kWh)
    float peak_usage;         // Peak usage (W)
    time_t peak_time;         // When peak occurred
    float cost_estimate;      // Estimated cost
} EnergyStats;

// Energy Threshold
typedef struct {
    int device_id;
    float warning_threshold;
    float critical_threshold;
    EnergyUnit unit;
    bool enabled;
    time_t last_triggered;
} EnergyThreshold;

// Energy Manager
typedef struct {
    EnergyReading* readings;
    int reading_count;
    int max_readings;
    EnergyThreshold* thresholds;
    int threshold_count;
    int max_thresholds;
    EnergyStats global_stats;
    float cost_per_kwh;       // Electricity cost
    char currency[5];         // Currency symbol
} EnergyManager;

// Function Prototypes

// Energy Manager
EnergyManager* energy_manager_create(int max_readings, int max_thresholds);
void energy_manager_destroy(EnergyManager* manager);

// Reading Management
int energy_add_reading(EnergyManager* manager, int device_id,
                      float value, EnergyUnit unit);
EnergyReading* energy_get_readings(EnergyManager* manager, int device_id,
                                  time_t start_time, time_t end_time, int* count);
int energy_get_latest_reading(EnergyManager* manager, int device_id,
                             EnergyReading* reading);

// Statistics Calculation
int energy_calculate_stats(EnergyManager* manager, int device_id,
                          TimePeriod period, EnergyStats* stats);
int energy_get_global_stats(EnergyManager* manager, EnergyStats* stats);
int energy_predict_usage(EnergyManager* manager, int device_id,
                        TimePeriod period, float* prediction);

// Threshold Management
int energy_add_threshold(EnergyManager* manager, int device_id,
                        float warning, float critical, EnergyUnit unit);
int energy_remove_threshold(EnergyManager* manager, int device_id);
int energy_check_thresholds(EnergyManager* manager, DeviceManager* devices);

// Cost Calculation
int energy_set_cost_rate(EnergyManager* manager, float cost_per_kwh,
                        const char* currency);
float energy_calculate_cost(EnergyManager* manager, float kwh_usage);
float energy_estimate_monthly_cost(EnergyManager* manager);

// Optimization
int energy_find_inefficient_devices(EnergyManager* manager,
                                   int** device_ids, int* count);
int energy_suggest_optimizations(EnergyManager* manager,
                                char** suggestions, int* count);
int energy_auto_optimize(EnergyManager* manager, DeviceManager* devices);

// Data Analysis
int energy_get_usage_patterns(EnergyManager* manager, int device_id,
                             TimePeriod period, float** pattern, int* count);
int energy_compare_periods(EnergyManager* manager, time_t period1_start,
                          time_t period1_end, time_t period2_start,
                          time_t period2_end, float* difference_percent);

// Reporting
int energy_generate_report(EnergyManager* manager, const char* filename,
                          time_t start_date, time_t end_date);
int energy_export_data(EnergyManager* manager, const char* filename,
                      const char* format); // CSV, JSON, XML

// Utility Functions
const char* energy_unit_to_string(EnergyUnit unit);
EnergyUnit string_to_energy_unit(const char* str);
float energy_convert_units(float value, EnergyUnit from, EnergyUnit to);
time_t energy_get_period_start(TimePeriod period, time_t current_time);

// Data Persistence
int energy_save_readings(EnergyManager* manager, const char* filename);
int energy_load_readings(EnergyManager* manager, const char* filename);
int energy_save_thresholds(EnergyManager* manager, const char* filename);
int energy_load_thresholds(EnergyManager* manager, const char* filename);

// Integration with Devices
int energy_monitor_device(EnergyManager* manager, Device* device);
int energy_update_device_reading(EnergyManager* manager, Device* device);

// Error Handling
typedef enum {
    ENERGY_SUCCESS = 0,
    ENERGY_ERROR_INVALID_DEVICE = -1,
    ENERGY_ERROR_INVALID_READING = -2,
    ENERGY_ERROR_NO_DATA = -3,
    ENERGY_ERROR_MEMORY = -4,
    ENERGY_ERROR_FILE_IO = -5,
    ENERGY_ERROR_INVALID_PARAMS = -6
} EnergyError;

const char* energy_error_to_string(EnergyError error);

#endif // ENERGY_H