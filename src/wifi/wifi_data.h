#ifndef __WIFI_DATA_H__
#define __WIFI_DATA_H__

/*
 *  Project 41-mqtt_00 - Austral - EAM
 *
 *  wifi_data.h
 *      Data configuration for WiFi connection
 */

#if (WIFI==0)                   //  Home settings
    #define MY_SSID "edumel2.4"
    #define MY_PASS "geheim1943"
#elif (WIFI==1)                 //  University settings
    #define MY_SSID "UA-Alumnos"
    #define MY_PASS "41umn05WLC"
#elif (WIFI==2)                 //  Other place settings
    #define MY_SSID "3112@campus"
    #define MY_PASS "campus3112"
#elif (WIFI==3)
    #define MY_SSID "Marcos (2)"
    #define MY_PASS "Elefante"
#else
    #error  "WIFI symbol out of range"
#endif

//  wifi_data.h ends
#endif


