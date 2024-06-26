#define Regist
#ifdef Regist
#define Mains_UA                          0
#define Mains_UB                          1
#define Mains_UC                          2
#define Mains_UAB                         3
#define Mains_UBC                         4
#define Mains_UCA                         5
#define Mains_Frequency                   6
#define Gen_UA                            7
#define Gen_UB                            8
#define Gen_UC                            9
#define Gen_UAB                           10
#define Gen_UBC                           11
#define Gen_UCA                           12
#define Gen_Frequency                     13
#define A_Phase_Current                   14
#define B_Phase_Current                   15
#define C_Phase_Current                   16
#define Water_Temperature_Value           17
#define Water_Temp_Resistance_Value       18
#define Oil_Pressure_Value                19
#define OP_Resistance_Value               20
#define Level_Value                       21
#define Level_Resistance_Value            22
#define Speed                             23
#define Battery_Voltage                   24
#define D_Voltage                         25
#define Active_Power                      26
#define Reactive_Power                    27
#define Apparent_Power                    28
#define Power_Factor                      29
#define Maintenance_Countdown_h           30
#define Maintenance_Countdown_min         31
#define Reserve                           32
#define Reserve                           33
#define Controller_Running_Status         34
#define Delay                             35
#define Auto_Running_Status               36        //0 Start 1 Stop 2 No Delay
#define Delay                             37
#define ATS_Running_Status                38// 0 No Delay 1 Transfer Rest
#define Delay                             39
#define Mains_Status                      40      //0 Normal 1 Abnormal 2 No Delay
#define Delay                             41
#define Oil_Engine_Run_Accum_Time_h_MSB   42
#define Oil_Engine_Run_Accum_Time_h_LSB   43
#define Oil_Engine_Run_Accum_Time_min     44
#define Oil_Engine_Run_Accum_Time_s       45
#define Accum_Start_Times_MSB             46
#define Accum_Start_Times_LSB             47
#define Accum_Energy_MSB                  48
#define Accum_Energy_LSB                  49
#define Software_Version                  50
#define Hardware_Version                  51
#define A_Phase_Active_Power              52
#define B_Phase_Active_Power              53
#define C_Phase_Active_Power              54
#define Load_Output_Percentage            55
#define Air_fuel_Ratio                    56
#define Throttle_Percentage               57
#define Coolant_Level                     58
#define Oil_Temperature                   59
#define Coolant_Pressure                  60
#define Fuel_Pressure                     61
#define Fuel_Temperature                  62
#define Inlet_emperature                  63
#define Exhaust_Temperature               64
#define Turbo_Pressure                    65
#define Fuel_Consumption                  66
#define Inlet_Pressure                    67
#define Accum_Fuel_Consumption            68
#define Accum_Fuel_Consumption            69
#define SCM_Internal_Temperature          70
#define Controller_Model                  71
#define Controller_Time_Year              72
#define Controller_Time_Month             73
#define Controller_Time_Day               74
#define Controller_Time_Week              75
#define Controller_Time_Hour              76
#define Controller_Time_Minute            77
#define Controller_Time_Second            78
#define Release_Year                      79
#define Release_Month                     80
#define Release_Day                       81
#define Ignition_Speed                    82
#define Urea_Level                        83
#define ECU_Temperature                   84
#define Environment_Pressure              85
#define ECU_Running_Time                  86
#define ECU_Running_Time                  87
#define MTU_FC                            88
#define MTU_Droop                         89
#define MTU_Demand_Source                 90
#define MTU_SSD                           91
#define Gen_UA_Phase                      92
#define Gen_UB_Phase                      93
#define Gen_UC_Phase                      94
#define Mains_UA_Phase                    95
#define Mains_UB_Phase                    96
#define Mains_UC_Phase                    97
#define DM1_Alarm                         98
#define DM2_Alarm                         108
#define ECU_Alarm_Numbers                 118
#define ECU_Warn_Numbers                  119
#define Instaneous_Oil_Consumption        120
#define Gas_Pressure                      121
#define Exhaust_Oxygen_Content            122
#define Turbo_Temperature                 123
#define Fuel_Valve_Position               124

#endif

#define Coils_1
#ifdef Coils_1
#define Common_Alarm                          0
#define Common_Warning_Alarm                  1
#define Common_Shutdown_Alarm                 2
#define Remote_Mode                           3
#define Remote_Lock                           4
#define Reserve_____________                  5
#define Mains_with_Load                       6
#define Gen_with_Load                         7
#define Emergency_Stop                        8
#define Overspeed_Alarm_Shutdown              9
#define Underspeed_Alarm_Shutdown             10
#define Speed_Signal_Loss_Shutdown            11
#define Overfrequency_Shutdown                12
#define Underfrequency_Shutdown               13
#define Overvoltage_Shutdown                  14
#define Undervoltage_Shutdown                 15
#define Gen_Overcurrent_Shutdown              16
#define Crank_Failure                         17
#define High_Temperature_Shutdown             18
#define Low_Oil_Pressure_Shutdown             19
#define Frequency_Loss_Alarm                  20
#define Input_Port_Shutdown_Alarm             21
#define Low_Fuel_Level_Shutdown_Alarm         22
#define Low_Coolant_Level_Shutdown_Alarm      23
#define High_Water_Temperature_Warn_Alarm     24
#define Low_Oil_Pressure_Warn_Alarm           25
#define Gen_Overcurrent_Warn_Alarm            26
#define Stop_Failure_Warn                     27
#define Low_Oil_Level_Warn                    28
#define Charge_Failure_Warn                   29
#define Battery_Volt_Low_Warn_Alarm           30
#define Battery_Volt_High_Warn_Alarm          31
#define Input_Port_Warn_Alarm                 32
#define Speed_Signal_Loss_Warn                33
#define Low_Coolant_Level_Warn                34
#define Temp_Sensor_Open_Warn                 35
#define Oil_Pressure_Sensor_Open_Warn         36
#define Maintenance_Due_Warn                  37
#define Charger_Fails_to_Charge_Warnn         38
#define Over_Power_Warn                       39
#define Test_Mode                             40
#define Auto_Mode                             41
#define Manual_Mode                           42
#define Stop_Mode                             43
#define Temp_Sensor_Open_Shutdown             44
#define Oil_Pressure_Sensor_Open_Shutdown     45
#define Maintenance_Due_Shutdown_Alarm        46
#define Over_Power_Shutdown_Alarm             47
#define Emergency_Stop_Input                  48
#define Aux_Input_1                           49
#define Aux_Input_2                           50
#define Aux_Input_3                           51
#define Aux_Input_4                           52
#define Aux_Input_5                           53
#define Gen_Switch_Failure_Warn               54
#define Mains_Switch_Failure_Warn             55
#define Start_Relay_Output                    56
#define Fuel_Relay_Output                     57
#define Aux_Output_1                          58
#define Aux_Output_2                          59
#define Aux_Output_3                          60
#define Aux_Output_4                          61
#define Reserve_____________                  62
#define Reserve_____________                  63
#define Mains_Fault                           64
#define Mains_Normal                          65
#define Mains_Overvoltage                     66
#define Mains_Undervoltage                    67
#define Mains_Loss_of_Phase                   68
#define Mains_Blackout                        69
#define Reserve_____________                  70
#define Reserve_____________                  71
#define Gen_Normal                            72
#define Gen_Overvoltage                       73
#define Gen_Undervoltage                      74
#define Gen_Overfrequency                     75
#define Gen_Underfrequency                    76
#define Gen_Overcurrent_Warn                  77
#define In_Scheduled_Not_Run                  78
#define ECU_Warn                              79
#define ECU_Shutdown_Alarm                    80
#define ECU_Comm_Failure_Alarm                81
#endif
