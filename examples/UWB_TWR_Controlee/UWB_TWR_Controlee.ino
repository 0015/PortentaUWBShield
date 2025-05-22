

#include <PortentaUWBShield.h>

// handler for ranging notifications
void rangingHandler(UWBRangingData &rangingData) {
  Serial.print("GOT RANGING DATA - Type: "  );
  Serial.println(rangingData.measureType());
  if(rangingData.measureType()==(uint8_t)uwb::MeasurementType::TWO_WAY)
  {
    
    RangingMeasures twr=rangingData.twoWayRangingMeasure();
    for(int j=0;j<rangingData.available();j++)
    {

      if(twr[j].status==0 && twr[j].distance!=0xFFFF)
      {
        Serial.print("Distance: ");
        Serial.println(twr[j].distance);  
      }
    }
   
  }
  
}

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);

#if defined(ARDUINO_PORTENTA_C33)
  /* Only the Portenta C33 has an RGB LED. */
  pinMode(LEDR, OUTPUT);
  digitalWrite(LEDR, LOW);
#endif

  uint8_t devAddr[]={0x22,0x22};
  uint8_t destination[]={0x11,0x11};
  UWBMacAddress srcAddr(UWBMacAddress::Size::SHORT,devAddr);
  UWBMacAddress dstAddr(UWBMacAddress::Size::SHORT,destination);
  
  UWB.registerRangingCallback(rangingHandler);
  UWB.begin();
  Serial.println("Starting UWB ...");
  while(UWB.state()!=0)
    delay(10);

  Serial.println("Starting session ...");
  UWBSession session1;
  session1.sessionID(0x11223344);
  session1.sessionType(uwb::SessionType::RANGING);
    
  if(!session1.appParams.addOrUpdateParam(AppConfigId::NO_OF_CONTROLEES,1))
    Serial.println("could not add to app params");
  if(!session1.appParams.destinationMacAddr(dstAddr))
    Serial.println("could not add to app params");;
    
  session1.applyDefaults(); //apply default values for measurement repetition rate and antenna config

  session1.rangingParams.deviceMacAddr(srcAddr);
  session1.rangingParams.deviceRole(uwb::DeviceRole::RESPONDER);
  session1.rangingParams.deviceType(uwb::DeviceType::Controlee);
  session1.rangingParams.multiNodeMode(uwb::MultiNodeMode::UNICAST);
  session1.rangingParams.rangingRoundUsage(uwb::RangingMethod::DS_TWR);
  session1.rangingParams.scheduledMode(uwb::ScheduledMode::TIME_SCHEDULED);
  
  //add the session to the session manager, in case you want to manage multiple connections
  UWBSessionManager.addSession(session1);

  session1.init(); //apply the config params defined above

  session1.start(); //start the session

}

void loop()
{
#if defined(ARDUINO_PORTENTA_C33)
  /* Only the Portenta C33 has an RGB LED. */
  digitalWrite(LEDR, !digitalRead(LEDR));
#else
  Serial.println(millis());
#endif
  vTaskDelay(configTICK_RATE_HZ/4);

}

