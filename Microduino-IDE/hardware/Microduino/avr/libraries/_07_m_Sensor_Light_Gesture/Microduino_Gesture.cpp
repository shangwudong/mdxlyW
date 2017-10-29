/**
 * @file    SparkFun_APDS-9960.cpp
 * @brief   Library for the SparkFun APDS-9960 breakout board
 * @author  Shawn Hymel (SparkFun Electronics)
 *
 * @copyright	This code is public domain but you buy me a beer if you use
 * this and we meet someday (Beerware license).
 *
 * This library interfaces the Avago APDS-9960 to Arduino over I2C. The library
 * relies on the Arduino Wire (I2C) library. to use the library, instantiate an
 * APDS9960 object, call init(), and call the appropriate functions.
 *
 * APDS-9960 current draw tests (default parameters):
 *   Off:                   1mA
 *   Waiting for gesture:   14mA
 *   Gesture in progress:   35mA
 */
 
 #include <Arduino.h>
 #include <Wire.h>
 #include <I2Cdev.h>
 #include "Microduino_Gesture.h"
 
/**
 * @brief Constructor - Instantiates APDS9960 object
 */
Gesture::Gesture()
{
    gesture_ud_delta_ = 0;
    gesture_lr_delta_ = 0;
    
    gesture_ud_count_ = 0;
    gesture_lr_count_ = 0;
    
    gesture_near_count_ = 0;
    gesture_far_count_ = 0;
    
    gesture_state_ = 0;
    gesture_motion_ = DIR_NONE;
}
 

/**
 * @brief Configures I2C communications and initializes registers to defaults
 *
 * @return True if initialized successfully. False otherwise.
 */
bool Gesture::begin()
{
    uint8_t id;

    /* Initialize I2C */
    Wire.begin();
     
    /* Read ID register and check against known values for APDS-9960 */
    if(I2Cdev::readByte(APDS9960_I2C_ADDR, APDS9960_ID, &id) == -1 ) {
        return false;
    }
    if( !(id == APDS9960_ID_1 || id == APDS9960_ID_2) ) {
        return false;
    }
     
    /* Set ENABLE register to 0 (disable all features) */
    if( !setMode(ALL, OFF) ) {
        return false;
    }
    
    /* Set default values for ambient light and proximity registers */
    if( !I2Cdev::writeByte(APDS9960_I2C_ADDR, APDS9960_ATIME, DEFAULT_ATIME) ) {
        return false;
    }
    if( !I2Cdev::writeByte(APDS9960_I2C_ADDR, APDS9960_WTIME, DEFAULT_WTIME) ) {
        return false;
    }
    if( !I2Cdev::writeByte(APDS9960_I2C_ADDR, APDS9960_PPULSE, DEFAULT_PROX_PPULSE) ) {
        return false;
    }
    if( !I2Cdev::writeByte(APDS9960_I2C_ADDR, APDS9960_POFFSET_UR, DEFAULT_POFFSET_UR) ) {
        return false;
    }
    if( !I2Cdev::writeByte(APDS9960_I2C_ADDR, APDS9960_POFFSET_DL, DEFAULT_POFFSET_DL) ) {
        return false;
    }
    if( !I2Cdev::writeByte(APDS9960_I2C_ADDR, APDS9960_CONFIG1, DEFAULT_CONFIG1) ) {
        return false;
    }
    if( !setLEDDrive(DEFAULT_LDRIVE) ) {
        return false;
    }
    if( !setProximityGain(DEFAULT_PGAIN) ) {
        return false;
    }
    if( !setAmbientLightGain(DEFAULT_AGAIN) ) {
        return false;
    }
    if( !setProxIntLowThresh(DEFAULT_PILT) ) {
        return false;
    }
    if( !setProxIntHighThresh(DEFAULT_PIHT) ) {
        return false;
    }
    if( !setLightIntLowThreshold(DEFAULT_AILT) ) {
        return false;
    }
    if( !setLightIntHighThreshold(DEFAULT_AIHT) ) {
        return false;
    }
    if( !I2Cdev::writeByte(APDS9960_I2C_ADDR, APDS9960_PERS, DEFAULT_PERS) ) {
        return false;
    }
    if( !I2Cdev::writeByte(APDS9960_I2C_ADDR, APDS9960_CONFIG2, DEFAULT_CONFIG2) ) {
        return false;
    }
    if( !I2Cdev::writeByte(APDS9960_I2C_ADDR, APDS9960_CONFIG3, DEFAULT_CONFIG3) ) {
        return false;
    }
 
    /* Set default values for gesture sense registers */
    if( !setGestureEnterThresh(DEFAULT_GPENTH) ) {
        return false;
    }
    if( !setGestureExitThresh(DEFAULT_GEXTH) ) {
        return false;
    }
    if( !I2Cdev::writeByte(APDS9960_I2C_ADDR, APDS9960_GCONF1, DEFAULT_GCONF1)   ) {
        return false;
    }
    if( !setGestureGain(DEFAULT_GGAIN) ) {
        return false;
    }
    if( !setGestureLEDDrive(DEFAULT_GLDRIVE) ) {
        return false;
    }
    if( !setGestureWaitTime(DEFAULT_GWTIME) ) {
        return false;
    }
    if( !I2Cdev::writeByte(APDS9960_I2C_ADDR, APDS9960_GOFFSET_U, DEFAULT_GOFFSET) ) {
        return false;
    }
    if( !I2Cdev::writeByte(APDS9960_I2C_ADDR, APDS9960_GOFFSET_D, DEFAULT_GOFFSET) ) {
        return false;
    }
    if( !I2Cdev::writeByte(APDS9960_I2C_ADDR, APDS9960_GOFFSET_L, DEFAULT_GOFFSET) ) {
        return false;
    }
    if( !I2Cdev::writeByte(APDS9960_I2C_ADDR, APDS9960_GOFFSET_R, DEFAULT_GOFFSET) ) {
        return false;
    }
    if( !I2Cdev::writeByte(APDS9960_I2C_ADDR, APDS9960_GPULSE, DEFAULT_GPULSE) ) {
        return false;
    }
    if( !I2Cdev::writeByte(APDS9960_I2C_ADDR, APDS9960_GCONF3, DEFAULT_GCONF3) ) {
        return false;
    }
    if( !setGestureIntEnable(DEFAULT_GIEN) ) {
        return false;
    }
    return true;
}

/*******************************************************************************
 * Public methods for controlling the APDS-9960
 ******************************************************************************/

/**
 * @brief Reads and returns the contents of the ENABLE register
 *
 * @return Contents of the ENABLE register. 0xFF if error.
 */
uint8_t Gesture::getMode()
{
    uint8_t value;
    /* Read current ENABLE register */
	if(I2Cdev::readByte(APDS9960_I2C_ADDR, APDS9960_ENABLE, &value) == -1){
		return ERROR;
		
	}
    return value;
}

/**
 * @brief Enables or disables a feature in the APDS-9960
 *
 * @param[in] mode which feature to enable
 * @param[in] enable ON (1) or OFF (0)
 * @return True if operation success. False otherwise.
 */
bool Gesture::setMode(uint8_t _mode, uint8_t _enable)
{
    uint8_t regVal;

    /* Read current ENABLE register */
    regVal = getMode();
    if( regVal == ERROR ) {
        return false;
    }
    
    /* Change bit(s) in ENABLE register */
    _enable = _enable & 0x01;
    if( _mode >= 0 && _mode <= 6 ) {
        if (_enable) {
            regVal |= (1 << _mode);
        } else {
            regVal &= ~(1 << _mode);
        }
    } else if( _mode == ALL ) {
        if (_enable) {
            regVal = 0x7F;
        } else {
            regVal = 0x00;
        }
    }
        
    /* Write value back to ENABLE register */
	return I2Cdev::writeByte(APDS9960_I2C_ADDR, APDS9960_ENABLE, regVal);
}

/**
 * @brief Starts the light (R/G/B/Ambient) sensor on the APDS-9960
 *
 * @param[in] interrupts true to enable hardware interrupt on high or low light
 * @return True if sensor enabled correctly. False on error.
 */
bool Gesture::enableLightSensor(bool interrupts)
{   
    /* Set default gain, interrupts, enable power, and enable sensor */
    if( !setAmbientLightGain(DEFAULT_AGAIN) ) {
        return false;
    }
    if( interrupts ) {
        if( !setAmbientLightIntEnable(1) ) {
            return false;
        }
    } else {
        if( !setAmbientLightIntEnable(0) ) {
            return false;
        }
    }
    if( !enablePower() ){
        return false;
    }
    if( !setMode(AMBIENT_LIGHT, 1) ) {
        return false;
    }
    
    return true;

}

/**
 * @brief Ends the light sensor on the APDS-9960
 *
 * @return True if sensor disabled correctly. False on error.
 */
bool Gesture::disableLightSensor()
{
    if( !setAmbientLightIntEnable(0) ) {
        return false;
    }
    if( !setMode(AMBIENT_LIGHT, 0) ) {
        return false;
    }
    
    return true;
}

/**
 * @brief Starts the proximity sensor on the APDS-9960
 *
 * @param[in] interrupts true to enable hardware external interrupt on proximity
 * @return True if sensor enabled correctly. False on error.
 */
bool Gesture::enableProximitySensor(bool interrupts)
{
    /* Set default gain, LED, interrupts, enable power, and enable sensor */
    if( !setProximityGain(DEFAULT_PGAIN) ) {
        return false;
    }
    if( !setLEDDrive(DEFAULT_LDRIVE) ) {
        return false;
    }
    if( interrupts ) {
        if( !setProximityIntEnable(1) ) {
            return false;
        }
    } else {
        if( !setProximityIntEnable(0) ) {
            return false;
        }
    }
    if( !enablePower() ){
        return false;
    }
    if( !setMode(PROXIMITY, 1) ) {
        return false;
    }
    
    return true;
}

/**
 * @brief Ends the proximity sensor on the APDS-9960
 *
 * @return True if sensor disabled correctly. False on error.
 */
bool Gesture::disableProximitySensor()
{
	if( !setProximityIntEnable(0) ) {
		return false;
	}
	if( !setMode(PROXIMITY, 0) ) {
		return false;
	}
	return true;
}

/**
 * @brief Starts the gesture recognition engine on the APDS-9960
 *
 * @param[in] interrupts true to enable hardware external interrupt on gesture
 * @return True if engine enabled correctly. False on error.
 */
bool Gesture::enableGestureSensor(bool interrupts)
{    
    /* Enable gesture mode
       Set ENABLE to 0 (power off)
       Set WTIME to 0xFF
       Set AUX to LED_BOOST_300
       Enable PON, WEN, PEN, GEN in ENABLE 
    */
    resetGestureParameters();	
    if( !I2Cdev::writeByte(APDS9960_I2C_ADDR, APDS9960_WTIME, 0xFF) ) {
        return false;
    }
    if( !I2Cdev::writeByte(APDS9960_I2C_ADDR, APDS9960_PPULSE, DEFAULT_GESTURE_PPULSE) ) {
        return false;
    }
    if( !setLEDBoost(LED_BOOST_300) ) {
        return false;
    }
    if( interrupts ) {
        if( !setGestureIntEnable(1) ) {
            return false;
        }
    } else {
        if( !setGestureIntEnable(0) ) {
            return false;
        }
    }
    if( !setGestureMode(1) ) {
        return false;
    }
    if( !enablePower() ){
        return false;
    }
    if( !setMode(WAIT, 1) ) {
        return false;
    }
    if( !setMode(PROXIMITY, 1) ) {
        return false;
    }
    if( !setMode(GESTURE, 1) ) {
        return false;
    }
    
    return true;
}

/**
 * @brief Ends the gesture recognition engine on the APDS-9960
 *
 * @return True if engine disabled correctly. False on error.
 */
bool Gesture::disableGestureSensor()
{
    resetGestureParameters();
    if( !setGestureIntEnable(0) ) {
        return false;
    }
    if( !setGestureMode(0) ) {
        return false;
    }
    if( !setMode(GESTURE, 0) ) {
        return false;
    }  
    return true;
}

/**
 * @brief Determines if there is a gesture available for reading
 *
 * @return True if gesture available. False otherwise.
 */
bool Gesture::isGestureAvailable()
{
    uint8_t value;   
    /* Read value from GSTATUS register */
    if(I2Cdev::readByte(APDS9960_I2C_ADDR, APDS9960_GSTATUS, &value) == -1 ) {
        return ERROR;
    }    
    value &= APDS9960_GVALID;
    return value;
}

/**
 * @brief Processes a gesture event and returns best guessed gesture
 *
 * @return Number corresponding to gesture. -1 on error.
 */
int Gesture::readGesture()
{
    uint8_t fifo_level = 0;
    uint8_t bytes_read = 0;
    uint8_t fifo_data[128];
    uint8_t gstatus;
    int motion;
    int i;
    
    /* Make sure that power and gesture is on and data is valid */
    if( !isGestureAvailable() || !(getMode() & 0b01000001) ) {
        return DIR_NONE;
    }
    
    /* Keep looping as long as gesture data is valid */
    while(1) {
    
        /* Wait some time to collect next batch of FIFO data */
        delay(FIFO_PAUSE_TIME);
        
        /* Get the contents of the STATUS register. Is data still valid? */
        if(I2Cdev::readByte(APDS9960_I2C_ADDR, APDS9960_GSTATUS, &gstatus) == -1 ) {
            return ERROR;
        }
        
        /* If we have valid data, read in FIFO */
        if( (gstatus & APDS9960_GVALID) == APDS9960_GVALID ) {
        
            /* Read the current FIFO level */
            if(I2Cdev::readByte(APDS9960_I2C_ADDR, APDS9960_GFLVL, &fifo_level) == -1 ) {
                return ERROR;
            }

#if DEBUG
            Serial.print("FIFO Level: ");
            Serial.println(fifo_level);
#endif

            /* If there's stuff in the FIFO, read it into our data block */
            if( fifo_level > 0) {

                bytes_read = I2Cdev::readBytes(APDS9960_I2C_ADDR, APDS9960_GFIFO_U, (fifo_level * 4), fifo_data);
                if( bytes_read == -1 ) {
                    return ERROR;
                }
#if DEBUG
                Serial.print("FIFO Dump: ");
                for ( i = 0; i < bytes_read; i++ ) {
                    Serial.print(fifo_data[i]);
                    Serial.print(" ");
                }
                Serial.println();
#endif

                /* If at least 1 set of data, sort the data into U/D/L/R */
                if( bytes_read >= 4 ) {
                    for( i = 0; i < bytes_read; i += 4 ) {
                        gesture_data_.u_data[gesture_data_.index] = \
                                                            fifo_data[i + 0];
                        gesture_data_.d_data[gesture_data_.index] = \
                                                            fifo_data[i + 1];
                        gesture_data_.l_data[gesture_data_.index] = \
                                                            fifo_data[i + 2];
                        gesture_data_.r_data[gesture_data_.index] = \
                                                            fifo_data[i + 3];
                        gesture_data_.index++;
                        gesture_data_.total_gestures++;
                    }
                    
#if DEBUG
                Serial.print("Up Data: ");
                for ( i = 0; i < gesture_data_.total_gestures; i++ ) {
                    Serial.print(gesture_data_.u_data[i]);
                    Serial.print(" ");
                }
                Serial.println();
#endif

                    /* Filter and process gesture data. Decode near/far state */
                    if( processGestureData() ) {
                        if( decodeGesture() ) {
                            //***TODO: U-Turn Gestures
#if DEBUG
                            //Serial.println(gesture_motion_);
#endif
                        }
                    }
                    
                    /* Reset data */
                    gesture_data_.index = 0;
                    gesture_data_.total_gestures = 0;
                }
            }
        } else {
    
            /* Determine best guessed gesture and clean up */
            delay(FIFO_PAUSE_TIME);
            decodeGesture();
            motion = gesture_motion_;
#if DEBUG
            Serial.print("END: ");
            Serial.println(gesture_motion_);
#endif
            resetGestureParameters();
            return motion;
        }
    }
}

/**
 * Turn the APDS-9960 on
 *
 * @return True if operation successful. False otherwise.
 */
bool Gesture::enablePower()
{
    if( !setMode(POWER, 1) ) {
        return false;
    }   
    return true;
}

/**
 * Turn the APDS-9960 off
 *
 * @return True if operation successful. False otherwise.
 */
bool Gesture::disablePower()
{
    if( !setMode(POWER, 0) ) {
        return false;
    }   
    return true;
}

/*******************************************************************************
 * Ambient light and color sensor controls
 ******************************************************************************/

/**
 * @brief Reads the ambient (clear) light level as a 16-bit value
 *
 * @param[out] val value of the light sensor.
 * @return True if operation successful. False otherwise.
 */
uint16_t Gesture::readAmbientLight()
{
    uint8_t buf[2];
	I2Cdev::readBytes(APDS9960_I2C_ADDR, APDS9960_CDATAL, 2, buf);
	return (uint16_t)buf[1] << 8 | buf[0];
}

/**
 * @brief Reads the red light level as a 16-bit value
 *
 * @param[out] val value of the light sensor.
 * @return True if operation successful. False otherwise.
 */
uint16_t Gesture::readRedLight()
{
    uint8_t buf[2];
	I2Cdev::readBytes(APDS9960_I2C_ADDR, APDS9960_RDATAL, 2, buf);
	return (uint16_t)buf[1] << 8 | buf[0]; 
}
 
/**
 * @brief Reads the green light level as a 16-bit value
 *
 * @param[out] val value of the light sensor.
 * @return True if operation successful. False otherwise.
 */
uint16_t Gesture::readGreenLight()
{
    uint8_t buf[2];
	I2Cdev::readBytes(APDS9960_I2C_ADDR, APDS9960_GDATAL, 2, buf);
	return (uint16_t)buf[1] << 8 | buf[0];
}

/**
 * @brief Reads the red light level as a 16-bit value
 *
 * @param[out] val value of the light sensor.
 * @return True if operation successful. False otherwise.
 */
uint16_t Gesture::readBlueLight()
{
    uint8_t buf[2];
	I2Cdev::readBytes(APDS9960_I2C_ADDR, APDS9960_BDATAL, 2, buf);
	return (uint16_t)buf[1] << 8 | buf[0]; 
}

/*******************************************************************************
 * Proximity sensor controls
 ******************************************************************************/

/**
 * @brief Reads the proximity level as an 8-bit value
 *
 * @param[out] val value of the proximity sensor.
 * @return True if operation successful. False otherwise.
 */
uint8_t Gesture::readProximity()
{
	uint8_t value;
	I2Cdev::readByte(APDS9960_I2C_ADDR, APDS9960_PDATA, &value);
	return value;
}

/*******************************************************************************
 * High-level gesture controls
 ******************************************************************************/

/**
 * @brief Resets all the parameters in the gesture data member
 */
void Gesture::resetGestureParameters()
{
    gesture_data_.index = 0;
    gesture_data_.total_gestures = 0;
    
    gesture_ud_delta_ = 0;
    gesture_lr_delta_ = 0;
    
    gesture_ud_count_ = 0;
    gesture_lr_count_ = 0;
    
    gesture_near_count_ = 0;
    gesture_far_count_ = 0;
    
    gesture_state_ = 0;
    gesture_motion_ = DIR_NONE;
}

/**
 * @brief Processes the raw gesture data to determine swipe direction
 *
 * @return True if near or far state seen. False otherwise.
 */
bool Gesture::processGestureData()
{
    uint8_t u_first = 0;
    uint8_t d_first = 0;
    uint8_t l_first = 0;
    uint8_t r_first = 0;
    uint8_t u_last = 0;
    uint8_t d_last = 0;
    uint8_t l_last = 0;
    uint8_t r_last = 0;
    int ud_ratio_first;
    int lr_ratio_first;
    int ud_ratio_last;
    int lr_ratio_last;
    int ud_delta;
    int lr_delta;
    int i;

    /* If we have less than 4 total gestures, that's not enough */
    if( gesture_data_.total_gestures <= 4 ) {
        return false;
    }
    
    /* Check to make sure our data isn't out of bounds */
    if( (gesture_data_.total_gestures <= 32) && \
        (gesture_data_.total_gestures > 0) ) {
        
        /* Find the first value in U/D/L/R above the threshold */
        for( i = 0; i < gesture_data_.total_gestures; i++ ) {
            if( (gesture_data_.u_data[i] > GESTURE_THRESHOLD_OUT) &&
                (gesture_data_.d_data[i] > GESTURE_THRESHOLD_OUT) &&
                (gesture_data_.l_data[i] > GESTURE_THRESHOLD_OUT) &&
                (gesture_data_.r_data[i] > GESTURE_THRESHOLD_OUT) ) {
                
                u_first = gesture_data_.u_data[i];
                d_first = gesture_data_.d_data[i];
                l_first = gesture_data_.l_data[i];
                r_first = gesture_data_.r_data[i];
                break;
            }
        }
        
        /* If one of the _first values is 0, then there is no good data */
        if( (u_first == 0) || (d_first == 0) || \
            (l_first == 0) || (r_first == 0) ) {
            
            return false;
        }
        /* Find the last value in U/D/L/R above the threshold */
        for( i = gesture_data_.total_gestures - 1; i >= 0; i-- ) {
#if DEBUG
            Serial.print(F("Finding last: "));
            Serial.print(F("U:"));
            Serial.print(gesture_data_.u_data[i]);
            Serial.print(F(" D:"));
            Serial.print(gesture_data_.d_data[i]);
            Serial.print(F(" L:"));
            Serial.print(gesture_data_.l_data[i]);
            Serial.print(F(" R:"));
            Serial.println(gesture_data_.r_data[i]);
#endif
            if( (gesture_data_.u_data[i] > GESTURE_THRESHOLD_OUT) &&
                (gesture_data_.d_data[i] > GESTURE_THRESHOLD_OUT) &&
                (gesture_data_.l_data[i] > GESTURE_THRESHOLD_OUT) &&
                (gesture_data_.r_data[i] > GESTURE_THRESHOLD_OUT) ) {
                
                u_last = gesture_data_.u_data[i];
                d_last = gesture_data_.d_data[i];
                l_last = gesture_data_.l_data[i];
                r_last = gesture_data_.r_data[i];
                break;
            }
        }
    }
    
    /* Calculate the first vs. last ratio of up/down and left/right */
    ud_ratio_first = ((u_first - d_first) * 100) / (u_first + d_first);
    lr_ratio_first = ((l_first - r_first) * 100) / (l_first + r_first);
    ud_ratio_last = ((u_last - d_last) * 100) / (u_last + d_last);
    lr_ratio_last = ((l_last - r_last) * 100) / (l_last + r_last);
       
#if DEBUG
    Serial.print(F("Last Values: "));
    Serial.print(F("U:"));
    Serial.print(u_last);
    Serial.print(F(" D:"));
    Serial.print(d_last);
    Serial.print(F(" L:"));
    Serial.print(l_last);
    Serial.print(F(" R:"));
    Serial.println(r_last);

    Serial.print(F("Ratios: "));
    Serial.print(F("UD Fi: "));
    Serial.print(ud_ratio_first);
    Serial.print(F(" UD La: "));
    Serial.print(ud_ratio_last);
    Serial.print(F(" LR Fi: "));
    Serial.print(lr_ratio_first);
    Serial.print(F(" LR La: "));
    Serial.println(lr_ratio_last);
#endif
       
    /* Determine the difference between the first and last ratios */
    ud_delta = ud_ratio_last - ud_ratio_first;
    lr_delta = lr_ratio_last - lr_ratio_first;
    
#if DEBUG
    Serial.print("Deltas: ");
    Serial.print("UD: ");
    Serial.print(ud_delta);
    Serial.print(" LR: ");
    Serial.println(lr_delta);
#endif

    /* Accumulate the UD and LR delta values */
    gesture_ud_delta_ += ud_delta;
    gesture_lr_delta_ += lr_delta;
    
#if DEBUG
    Serial.print("Accumulations: ");
    Serial.print("UD: ");
    Serial.print(gesture_ud_delta_);
    Serial.print(" LR: ");
    Serial.println(gesture_lr_delta_);
#endif
    
    /* Determine U/D gesture */
    if( gesture_ud_delta_ >= GESTURE_SENSITIVITY_1 ) {
        gesture_ud_count_ = 1;
    } else if( gesture_ud_delta_ <= -GESTURE_SENSITIVITY_1 ) {
        gesture_ud_count_ = -1;
    } else {
        gesture_ud_count_ = 0;
    }
    
    /* Determine L/R gesture */
    if( gesture_lr_delta_ >= GESTURE_SENSITIVITY_1 ) {
        gesture_lr_count_ = 1;
    } else if( gesture_lr_delta_ <= -GESTURE_SENSITIVITY_1 ) {
        gesture_lr_count_ = -1;
    } else {
        gesture_lr_count_ = 0;
    }
    
    /* Determine Near/Far gesture */
    if( (gesture_ud_count_ == 0) && (gesture_lr_count_ == 0) ) {
        if( (abs(ud_delta) < GESTURE_SENSITIVITY_2) && \
            (abs(lr_delta) < GESTURE_SENSITIVITY_2) ) {
            
            if( (ud_delta == 0) && (lr_delta == 0) ) {
                gesture_near_count_++;
            } else if( (ud_delta != 0) || (lr_delta != 0) ) {
                gesture_far_count_++;
            }
            
            if( (gesture_near_count_ >= 10) && (gesture_far_count_ >= 2) ) {
                if( (ud_delta == 0) && (lr_delta == 0) ) {
                    gesture_state_ = NEAR_STATE;
                } else if( (ud_delta != 0) && (lr_delta != 0) ) {
                    gesture_state_ = FAR_STATE;
                }
                return true;
            }
        }
    } else {
        if( (abs(ud_delta) < GESTURE_SENSITIVITY_2) && \
            (abs(lr_delta) < GESTURE_SENSITIVITY_2) ) {
                
            if( (ud_delta == 0) && (lr_delta == 0) ) {
                gesture_near_count_++;
            }
            
            if( gesture_near_count_ >= 10 ) {
                gesture_ud_count_ = 0;
                gesture_lr_count_ = 0;
                gesture_ud_delta_ = 0;
                gesture_lr_delta_ = 0;
            }
        }
    }
    
#if DEBUG
    Serial.print("UD_CT: ");
    Serial.print(gesture_ud_count_);
    Serial.print(" LR_CT: ");
    Serial.print(gesture_lr_count_);
    Serial.print(" NEAR_CT: ");
    Serial.print(gesture_near_count_);
    Serial.print(" FAR_CT: ");
    Serial.println(gesture_far_count_);
    Serial.println("----------");
#endif
    
    return false;
}

/**
 * @brief Determines swipe direction or near/far state
 *
 * @return True if near/far event. False otherwise.
 */
bool Gesture::decodeGesture()
{
    /* Return if near or far event is detected */
    if( gesture_state_ == NEAR_STATE ) {
        gesture_motion_ = DIR_NEAR;
        return true;
    } else if ( gesture_state_ == FAR_STATE ) {
        gesture_motion_ = DIR_FAR;
        return true;
    }
    
    /* Determine swipe direction */
    if( (gesture_ud_count_ == -1) && (gesture_lr_count_ == 0) ) {
        gesture_motion_ = DIR_UP;
    } else if( (gesture_ud_count_ == 1) && (gesture_lr_count_ == 0) ) {
        gesture_motion_ = DIR_DOWN;
    } else if( (gesture_ud_count_ == 0) && (gesture_lr_count_ == 1) ) {
        gesture_motion_ = DIR_RIGHT;
    } else if( (gesture_ud_count_ == 0) && (gesture_lr_count_ == -1) ) {
        gesture_motion_ = DIR_LEFT;
    } else if( (gesture_ud_count_ == -1) && (gesture_lr_count_ == 1) ) {
        if( abs(gesture_ud_delta_) > abs(gesture_lr_delta_) ) {
            gesture_motion_ = DIR_UP;
        } else {
            gesture_motion_ = DIR_RIGHT;
        }
    } else if( (gesture_ud_count_ == 1) && (gesture_lr_count_ == -1) ) {
        if( abs(gesture_ud_delta_) > abs(gesture_lr_delta_) ) {
            gesture_motion_ = DIR_DOWN;
        } else {
            gesture_motion_ = DIR_LEFT;
        }
    } else if( (gesture_ud_count_ == -1) && (gesture_lr_count_ == -1) ) {
        if( abs(gesture_ud_delta_) > abs(gesture_lr_delta_) ) {
            gesture_motion_ = DIR_UP;
        } else {
            gesture_motion_ = DIR_LEFT;
        }
    } else if( (gesture_ud_count_ == 1) && (gesture_lr_count_ == 1) ) {
        if( abs(gesture_ud_delta_) > abs(gesture_lr_delta_) ) {
            gesture_motion_ = DIR_DOWN;
        } else {
            gesture_motion_ = DIR_RIGHT;
        }
    } else {
        return false;
    }
    
    return true;
}

/*******************************************************************************
 * Getters and setters for register values
 ******************************************************************************/

/**
 * @brief Returns the lower threshold for proximity detection
 *
 * @return lower threshold
 */
uint8_t Gesture::getProxIntLowThresh()
{
	uint8_t value;
	I2Cdev::readByte(APDS9960_I2C_ADDR, APDS9960_PILT, &value);
	return value;
}

/**
 * @brief Sets the lower threshold for proximity detection
 *
 * @param[in] threshold the lower proximity threshold
 * @return True if operation successful. False otherwise.
 */
bool Gesture::setProxIntLowThresh(uint8_t threshold)
{
	return I2Cdev::writeByte(APDS9960_I2C_ADDR, APDS9960_PILT, threshold);
}

/**
 * @brief Returns the high threshold for proximity detection
 *
 * @return high threshold
 */
uint8_t Gesture::getProxIntHighThresh()
{
	uint8_t value;
	I2Cdev::readByte(APDS9960_I2C_ADDR, APDS9960_PIHT, &value);
	return value; 
}

/**
 * @brief Sets the high threshold for proximity detection
 *
 * @param[in] threshold the high proximity threshold
 * @return True if operation successful. False otherwise.
 */
bool Gesture::setProxIntHighThresh(uint8_t threshold)
{
    return I2Cdev::writeByte(APDS9960_I2C_ADDR, APDS9960_PIHT, threshold);
}

/**
 * @brief Returns LED drive strength for proximity and ALS
 *
 * Value    LED Current
 *   0        100 mA
 *   1         50 mA
 *   2         25 mA
 *   3         12.5 mA
 *
 * @return the value of the LED drive strength. 0xFF on failure.
 */
uint8_t Gesture::getLEDDrive()
{
    uint8_t value;
	I2Cdev::readByte(APDS9960_I2C_ADDR, APDS9960_CONTROL, &value);
    /* Shift and mask out LED drive bits */
    return ((value >> 6) & 0b00000011);
}

/**
 * @brief Sets the LED drive strength for proximity and ALS
 *
 * Value    LED Current
 *   0        100 mA
 *   1         50 mA
 *   2         25 mA
 *   3         12.5 mA
 *
 * @param[in] drive the value (0-3) for the LED drive strength
 * @return True if operation successful. False otherwise.
 */
bool Gesture::setLEDDrive(uint8_t drive)
{	
	uint8_t value;
	I2Cdev::readByte(APDS9960_I2C_ADDR, APDS9960_CONTROL, &value);
    
    /* Set bits in register to given value */
    drive &= 0b00000011;
    drive = drive << 6;
    value &= 0b00111111;
    value |= drive;
    
	return I2Cdev::writeByte(APDS9960_I2C_ADDR, APDS9960_CONTROL, value);
}

/**
 * @brief Returns receiver gain for proximity detection
 *
 * Value    Gain
 *   0       1x
 *   1       2x
 *   2       4x
 *   3       8x
 *
 * @return the value of the proximity gain. 0xFF on failure.
 */
uint8_t Gesture::getProximityGain()
{	
	uint8_t value;
	I2Cdev::readByte(APDS9960_I2C_ADDR, APDS9960_CONTROL, &value);   
    /* Shift and mask out PDRIVE bits */
    return ((value >> 2) & 0b00000011);
}

/**
 * @brief Sets the receiver gain for proximity detection
 *
 * Value    Gain
 *   0       1x
 *   1       2x
 *   2       4x
 *   3       8x
 *
 * @param[in] drive the value (0-3) for the gain
 * @return True if operation successful. False otherwise.
 */
bool Gesture::setProximityGain(uint8_t drive)
{
	uint8_t value;
	I2Cdev::readByte(APDS9960_I2C_ADDR, APDS9960_CONTROL, &value);
    
    /* Set bits in register to given value */
    drive &= 0b00000011;
    drive = drive << 2;
    value &= 0b11110011;
    value |= drive;
 
	return I2Cdev::writeByte(APDS9960_I2C_ADDR, APDS9960_CONTROL, value);
}

/**
 * @brief Returns receiver gain for the ambient light sensor (ALS)
 *
 * Value    Gain
 *   0        1x
 *   1        4x
 *   2       16x
 *   3       64x
 *
 * @return the value of the ALS gain. 0xFF on failure.
 */
uint8_t Gesture::getAmbientLightGain()
{
	uint8_t value;
	I2Cdev::readByte(APDS9960_I2C_ADDR, APDS9960_CONTROL, &value);   
    /* Shift and mask out ADRIVE bits */
    return (value&0b00000011);
}

/**
 * @brief Sets the receiver gain for the ambient light sensor (ALS)
 *
 * Value    Gain
 *   0        1x
 *   1        4x
 *   2       16x
 *   3       64x
 *
 * @param[in] drive the value (0-3) for the gain
 * @return True if operation successful. False otherwise.
 */
bool Gesture::setAmbientLightGain(uint8_t drive)
{
	uint8_t value;
	I2Cdev::readByte(APDS9960_I2C_ADDR, APDS9960_CONTROL, &value);   
    
    /* Set bits in register to given value */
    drive &= 0b00000011;
    value &= 0b11111100;
    value |= drive;

	return I2Cdev::writeByte(APDS9960_I2C_ADDR, APDS9960_CONTROL, value);
}

/**
 * @brief Get the current LED boost value
 * 
 * Value  Boost Current
 *   0        100%
 *   1        150%
 *   2        200%
 *   3        300%
 *
 * @return The LED boost value. 0xFF on failure.
 */
uint8_t Gesture::getLEDBoost()
{
	uint8_t value;
	I2Cdev::readByte(APDS9960_I2C_ADDR, APDS9960_CONFIG2, &value);  	
    
    /* Shift and mask out LED_BOOST bits */
    return ((value >> 4) & 0b00000011);
}

/**
 * @brief Sets the LED current boost value
 *
 * Value  Boost Current
 *   0        100%
 *   1        150%
 *   2        200%
 *   3        300%
 *
 * @param[in] drive the value (0-3) for current boost (100-300%)
 * @return True if operation successful. False otherwise.
 */
bool Gesture::setLEDBoost(uint8_t boost)
{
	uint8_t value;
	I2Cdev::readByte(APDS9960_I2C_ADDR, APDS9960_CONFIG2, &value);  	
    
    /* Set bits in register to given value */
    boost &= 0b00000011;
    boost = boost << 4;
    value &= 0b11001111;
    value |= boost;
    
	return I2Cdev::writeByte(APDS9960_I2C_ADDR, APDS9960_CONFIG2, value);
}    
   
/**
 * @brief Gets proximity gain compensation enable
 *
 * @return 1 if compensation is enabled. 0 if not. 0xFF on error.
 */
uint8_t Gesture::getProxGainCompEnable()
{
	uint8_t value;
	I2Cdev::readByte(APDS9960_I2C_ADDR, APDS9960_CONFIG3, &value);  	
    
    /* Shift and mask out PCMP bits */
    return ((value >> 5) & 0b00000001);
}

/**
 * @brief Sets the proximity gain compensation enable
 *
 * @param[in] enable 1 to enable compensation. 0 to disable compensation.
 * @return True if operation successful. False otherwise.
 */
 bool Gesture::setProxGainCompEnable(uint8_t enable)
{
	uint8_t value;
	I2Cdev::readByte(APDS9960_I2C_ADDR, APDS9960_CONFIG3, &value);  
    
    /* Set bits in register to given value */
    enable &= 0b00000001;
    enable = enable << 5;
    value &= 0b11011111;
    value |= enable;
    
	return I2Cdev::writeByte(APDS9960_I2C_ADDR, APDS9960_CONFIG3, value);
}

/**
 * @brief Gets the current mask for enabled/disabled proximity photodiodes
 *
 * 1 = disabled, 0 = enabled
 * Bit    Photodiode
 *  3       UP
 *  2       DOWN
 *  1       LEFT
 *  0       RIGHT
 *
 * @return Current proximity mask for photodiodes. 0xFF on error.
 */
uint8_t Gesture::getProxPhotoMask()
{
	uint8_t value;
	I2Cdev::readByte(APDS9960_I2C_ADDR, APDS9960_CONFIG3, &value);  
    
    /* Mask out photodiode enable mask bits */
    return (value & 0b00001111);
}

/**
 * @brief Sets the mask for enabling/disabling proximity photodiodes
 *
 * 1 = disabled, 0 = enabled
 * Bit    Photodiode
 *  3       UP
 *  2       DOWN
 *  1       LEFT
 *  0       RIGHT
 *
 * @param[in] mask 4-bit mask value
 * @return True if operation successful. False otherwise.
 */
bool Gesture::setProxPhotoMask(uint8_t mask)
{
	uint8_t value;
	I2Cdev::readByte(APDS9960_I2C_ADDR, APDS9960_CONFIG3, &value);   
 
    /* Set bits in register to given value */
    mask &= 0b00001111;
    value &= 0b11110000;
    value |= mask;
    
	return I2Cdev::writeByte(APDS9960_I2C_ADDR, APDS9960_CONFIG3, value);
}

/**
 * @brief Gets the entry proximity threshold for gesture sensing
 *
 * @return Current entry proximity threshold.
 */
uint8_t Gesture::getGestureEnterThresh()
{
	uint8_t value;
	I2Cdev::readByte(APDS9960_I2C_ADDR, APDS9960_GPENTH, &value);      
    return value;
}

/**
 * @brief Sets the entry proximity threshold for gesture sensing
 *
 * @param[in] threshold proximity value needed to start gesture mode
 * @return True if operation successful. False otherwise.
 */
bool Gesture::setGestureEnterThresh(uint8_t threshold)
{
	return I2Cdev::writeByte(APDS9960_I2C_ADDR, APDS9960_GPENTH, threshold);
}

/**
 * @brief Gets the exit proximity threshold for gesture sensing
 *
 * @return Current exit proximity threshold.
 */
uint8_t Gesture::getGestureExitThresh()
{
	uint8_t value;
	I2Cdev::readByte(APDS9960_I2C_ADDR, APDS9960_GEXTH, &value);      
    return value;
}

/**
 * @brief Sets the exit proximity threshold for gesture sensing
 *
 * @param[in] threshold proximity value needed to end gesture mode
 * @return True if operation successful. False otherwise.
 */
bool Gesture::setGestureExitThresh(uint8_t threshold)
{
	return I2Cdev::writeByte(APDS9960_I2C_ADDR, APDS9960_GEXTH, threshold);
}

/**
 * @brief Gets the gain of the photodiode during gesture mode
 *
 * Value    Gain
 *   0       1x
 *   1       2x
 *   2       4x
 *   3       8x
 *
 * @return the current photodiode gain. 0xFF on error.
 */
uint8_t Gesture::getGestureGain()
{
	uint8_t value;
	I2Cdev::readByte(APDS9960_I2C_ADDR, APDS9960_GCONF2, &value);      
	    
    /* Shift and mask out GGAIN bits */
    return ((value >> 5) & 0b00000011);
}

/**
 * @brief Sets the gain of the photodiode during gesture mode
 *
 * Value    Gain
 *   0       1x
 *   1       2x
 *   2       4x
 *   3       8x
 *
 * @param[in] gain the value for the photodiode gain
 * @return True if operation successful. False otherwise.
 */
bool Gesture::setGestureGain(uint8_t gain)
{
	uint8_t value;
	I2Cdev::readByte(APDS9960_I2C_ADDR, APDS9960_GCONF2, &value);      
    
    /* Set bits in register to given value */
    gain &= 0b00000011;
    gain = gain << 5;
    value &= 0b10011111;
    value |= gain;
    
	return I2Cdev::writeByte(APDS9960_I2C_ADDR, APDS9960_GCONF2, value);
}

/**
 * @brief Gets the drive current of the LED during gesture mode
 *
 * Value    LED Current
 *   0        100 mA
 *   1         50 mA
 *   2         25 mA
 *   3         12.5 mA
 *
 * @return the LED drive current value. 0xFF on error.
 */
uint8_t Gesture::getGestureLEDDrive()
{
	uint8_t value;
	I2Cdev::readByte(APDS9960_I2C_ADDR, APDS9960_GCONF2, &value);     
    
    /* Shift and mask out GLDRIVE bits */
    return ((value >> 3) & 0b00000011);
}

/**
 * @brief Sets the LED drive current during gesture mode
 *
 * Value    LED Current
 *   0        100 mA
 *   1         50 mA
 *   2         25 mA
 *   3         12.5 mA
 *
 * @param[in] drive the value for the LED drive current
 * @return True if operation successful. False otherwise.
 */
bool Gesture::setGestureLEDDrive(uint8_t drive)
{
	uint8_t value;
	I2Cdev::readByte(APDS9960_I2C_ADDR, APDS9960_GCONF2, &value);  
    
    /* Set bits in register to given value */
    drive &= 0b00000011;
    drive = drive << 3;
    value &= 0b11100111;
    value |= drive;
    
	return I2Cdev::writeByte(APDS9960_I2C_ADDR, APDS9960_GCONF2, value);
}

/**
 * @brief Gets the time in low power mode between gesture detections
 *
 * Value    Wait time
 *   0          0 ms
 *   1          2.8 ms
 *   2          5.6 ms
 *   3          8.4 ms
 *   4         14.0 ms
 *   5         22.4 ms
 *   6         30.8 ms
 *   7         39.2 ms
 *
 * @return the current wait time between gestures. 0xFF on error.
 */
uint8_t Gesture::getGestureWaitTime()
{
	uint8_t value;
	I2Cdev::readByte(APDS9960_I2C_ADDR, APDS9960_GCONF2, &value);  
    
    /* Mask out GWTIME bits */
    return (value & 0b00000111);
}

/**
 * @brief Sets the time in low power mode between gesture detections
 *
 * Value    Wait time
 *   0          0 ms
 *   1          2.8 ms
 *   2          5.6 ms
 *   3          8.4 ms
 *   4         14.0 ms
 *   5         22.4 ms
 *   6         30.8 ms
 *   7         39.2 ms
 *
 * @param[in] the value for the wait time
 * @return True if operation successful. False otherwise.
 */
bool Gesture::setGestureWaitTime(uint8_t time)
{
	uint8_t value;
	I2Cdev::readByte(APDS9960_I2C_ADDR, APDS9960_GCONF2, &value); 
    
    /* Set bits in register to given value */
    time &= 0b00000111;
    value &= 0b11111000;
    value |= time;
    
	return I2Cdev::writeByte(APDS9960_I2C_ADDR, APDS9960_GCONF2, value);
}

/**
 * @brief Gets the low threshold for ambient light interrupts
 *
 * @param[out] threshold current low threshold stored on the APDS-9960
 * @return True if operation successful. False otherwise.
 */
uint16_t Gesture::getLightIntLowThreshold()
{
    uint8_t buf[2];
	I2Cdev::readBytes(APDS9960_I2C_ADDR, APDS9960_AILTL, 2, buf);
	return (uint16_t)buf[1] << 8 | buf[0]; 
}

/**
 * @brief Sets the low threshold for ambient light interrupts
 *
 * @param[in] threshold low threshold value for interrupt to trigger
 * @return True if operation successful. False otherwise.
 */
bool Gesture::setLightIntLowThreshold(uint16_t threshold)
{
    uint8_t buf[2];  
    /* Break 16-bit threshold into 2 8-bit values */
    buf[0] = threshold & 0x00FF;
    buf[1] = (threshold & 0xFF00) >> 8;
    
	return I2Cdev::writeBytes(APDS9960_I2C_ADDR, APDS9960_AILTL, 2, buf);
}

/**
 * @brief Gets the high threshold for ambient light interrupts
 *
 * @param[out] threshold current low threshold stored on the APDS-9960
 * @return True if operation successful. False otherwise.
 */
uint16_t Gesture::getLightIntHighThreshold()
{
	uint8_t buf[2];
	I2Cdev::readBytes(APDS9960_I2C_ADDR, APDS9960_AIHTL, 2, buf);
	return (uint16_t)buf[1] << 8 | buf[0]; 
}

/**
 * @brief Sets the high threshold for ambient light interrupts
 *
 * @param[in] threshold high threshold value for interrupt to trigger
 * @return True if operation successful. False otherwise.
 */
bool Gesture::setLightIntHighThreshold(uint16_t threshold)
{
    uint8_t buf[2];  
    /* Break 16-bit threshold into 2 8-bit values */
    buf[0] = threshold & 0x00FF;
    buf[1] = (threshold & 0xFF00) >> 8;
    
	return I2Cdev::writeBytes(APDS9960_I2C_ADDR, APDS9960_AIHTL, 2, buf);
}

/**
 * @brief Gets the low threshold for proximity interrupts
 *
 * @param[out] threshold current low threshold stored on the APDS-9960
 * @return True if operation successful. False otherwise.
 */
uint8_t Gesture::getProximityIntLowThreshold()
{
	uint8_t value;
	I2Cdev::readByte(APDS9960_I2C_ADDR, APDS9960_PILT, &value);
	return value;
}

/**
 * @brief Sets the low threshold for proximity interrupts
 *
 * @param[in] threshold low threshold value for interrupt to trigger
 * @return True if operation successful. False otherwise.
 */
bool Gesture::setProximityIntLowThreshold(uint8_t threshold)
{
	return I2Cdev::writeByte(APDS9960_I2C_ADDR, APDS9960_PILT, threshold);
}
    
/**
 * @brief Gets the high threshold for proximity interrupts
 *
 * @param[out] threshold current low threshold stored on the APDS-9960
 * @return True if operation successful. False otherwise.
 */
uint8_t Gesture::getProximityIntHighThreshold()
{
	uint8_t value;
	I2Cdev::readByte(APDS9960_I2C_ADDR, APDS9960_PIHT, &value);
	return value;
}

/**
 * @brief Sets the high threshold for proximity interrupts
 *
 * @param[in] threshold high threshold value for interrupt to trigger
 * @return True if operation successful. False otherwise.
 */
bool Gesture::setProximityIntHighThreshold(uint8_t threshold)
{
	return I2Cdev::writeByte(APDS9960_I2C_ADDR, APDS9960_PIHT, threshold);    
}

/**
 * @brief Gets if ambient light interrupts are enabled or not
 *
 * @return 1 if interrupts are enabled, 0 if not. 0xFF on error.
 */
uint8_t Gesture::getAmbientLightIntEnable()
{
	uint8_t value;
	I2Cdev::readByte(APDS9960_I2C_ADDR, APDS9960_ENABLE, &value);
 
    /* Shift and mask out AIEN bit */
    return ((value >> 4) & 0b00000001);
}

/**
 * @brief Turns ambient light interrupts on or off
 *
 * @param[in] enable 1 to enable interrupts, 0 to turn them off
 * @return True if operation successful. False otherwise.
 */
bool Gesture::setAmbientLightIntEnable(uint8_t enable)
{
	uint8_t value;
	I2Cdev::readByte(APDS9960_I2C_ADDR, APDS9960_ENABLE, &value);
    
    /* Set bits in register to given value */
    enable &= 0b00000001;
    enable = enable << 4;
    value &= 0b11101111;
    value |= enable;
    
	return I2Cdev::writeByte(APDS9960_I2C_ADDR, APDS9960_ENABLE, value);
}

/**
 * @brief Gets if proximity interrupts are enabled or not
 *
 * @return 1 if interrupts are enabled, 0 if not. 0xFF on error.
 */
uint8_t Gesture::getProximityIntEnable()
{
	uint8_t value;
	I2Cdev::readByte(APDS9960_I2C_ADDR, APDS9960_ENABLE, &value);
    
    /* Shift and mask out PIEN bit */
    return ((value >> 5) & 0b00000001);
}

/**
 * @brief Turns proximity interrupts on or off
 *
 * @param[in] enable 1 to enable interrupts, 0 to turn them off
 * @return True if operation successful. False otherwise.
 */
bool Gesture::setProximityIntEnable(uint8_t enable)
{	
	uint8_t value;
	I2Cdev::readByte(APDS9960_I2C_ADDR, APDS9960_ENABLE, &value);
	   
    /* Set bits in register to given value */
    enable &= 0b00000001;
    enable = enable << 5;
    value &= 0b11011111;
    value |= enable;
    
	return I2Cdev::writeByte(APDS9960_I2C_ADDR, APDS9960_ENABLE, value);
}

/**
 * @brief Gets if gesture interrupts are enabled or not
 *
 * @return 1 if interrupts are enabled, 0 if not. 0xFF on error.
 */
uint8_t Gesture::getGestureIntEnable()
{
	uint8_t value;
	I2Cdev::readByte(APDS9960_I2C_ADDR, APDS9960_GCONF4, &value);
	  
    /* Shift and mask out GIEN bit */
    return ((value >> 1) & 0b00000001);
}

/**
 * @brief Turns gesture-related interrupts on or off
 *
 * @param[in] enable 1 to enable interrupts, 0 to turn them off
 * @return True if operation successful. False otherwise.
 */
bool Gesture::setGestureIntEnable(uint8_t enable)
{
	uint8_t value;
	I2Cdev::readByte(APDS9960_I2C_ADDR, APDS9960_GCONF4, &value);
    
    /* Set bits in register to given value */
    enable &= 0b00000001;
    enable = enable << 1;
    value &= 0b11111101;
    value |= enable;
    
	return I2Cdev::writeByte(APDS9960_I2C_ADDR, APDS9960_GCONF4, value); 
}

/**
 * @brief Clears the ambient light interrupt
 *
 * @return True if operation completed successfully. False otherwise.
 */
bool Gesture::clearAmbientLightInt()
{
    uint8_t throwaway;	
    if(I2Cdev::readByte(APDS9960_I2C_ADDR, APDS9960_AICLEAR, &throwaway) == -1) {
        return false;
    }   
    return true;
}

/**
 * @brief Clears the proximity interrupt
 *
 * @return True if operation completed successfully. False otherwise.
 */
bool Gesture::clearProximityInt()
{
    uint8_t throwaway;
    if(I2Cdev::readByte(APDS9960_I2C_ADDR, APDS9960_PICLEAR, &throwaway) == -1 ) {
        return false;
    }
    return true;
}

/**
 * @brief Tells if the gesture state machine is currently running
 *
 * @return 1 if gesture state machine is running, 0 if not. 0xFF on error.
 */
uint8_t Gesture::getGestureMode()
{
	uint8_t value;
	I2Cdev::readByte(APDS9960_I2C_ADDR, APDS9960_GCONF4, &value);
    
    /* Mask out GMODE bit */
    return (value & 0b00000001);
}

/**
 * @brief Tells the state machine to either enter or exit gesture state machine
 *
 * @param[in] mode 1 to enter gesture state machine, 0 to exit.
 * @return True if operation successful. False otherwise.
 */
bool Gesture::setGestureMode(uint8_t mode)
{	
	uint8_t value;
	I2Cdev::readByte(APDS9960_I2C_ADDR, APDS9960_GCONF4, &value);
    
    /* Set bits in register to given value */
    mode &= 0b00000001;
    value &= 0b11111110;
    value |= mode;
    
	return I2Cdev::writeByte(APDS9960_I2C_ADDR, APDS9960_GCONF4, value); 
}
