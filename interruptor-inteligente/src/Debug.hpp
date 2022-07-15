#define ENABLE_DEBUG

#define DEBUG_BAUD_RATE 115200
#ifdef ENABLE_DEBUG

#define DBG_BEGIN(DEBUG_BAUD_RATE)  Serial.begin(DEBUG_BAUD_RATE);
#define DBG_PRINT(x)                Serial.print(x);
#define DBG_PRINTLN(x)              Serial.println(x);
#define DBG_TIQUE(x)                long debug_time=millis(); Serial.println(x);
#define DBG_TAQUE()                 debug_time=millis()-debug_time; \
                                    Serial.print(" time: "); Serial.println(debug_time);

#else

#define DBG_BEGIN(DEBUG_BAUD_RATE)
#define DBG_PRINT(x)
#define DBG_PRINTLN(x)
#define DBG_TIQUE(x)
#define DBG_TAQUE()

#endif
