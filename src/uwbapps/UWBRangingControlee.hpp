// SPDX-License-Identifier: MIT
// Copyright (c) 2025 Truesense Srl

#ifndef UWBRANGINGCONTROLEE_HPP
#define UWBRANGINGCONTROLEE_HPP

#include "UWB.hpp"
#include "UWBSession.hpp"

class  UWBRangingControlee:public UWBSession {

public: 
	    
	UWBRangingControlee(uint32_t session_ID, UWBMacAddress srcAddr, UWBMacAddress dstAddr)
	{
		sessionID(session_ID);
		sessionType(uwb::SessionType::RANGING);
		rangingParams.deviceRole(uwb::DeviceRole::RESPONDER);
		rangingParams.deviceType(uwb::DeviceType::CONTROLEE);
		rangingParams.multiNodeMode(uwb::MultiNodeMode::UNICAST);
		rangingParams.rangingRoundUsage(uwb::RangingMethod::DS_TWR);
		rangingParams.scheduledMode(uwb::ScheduledMode::TIME_SCHEDULED);
		rangingParams.macAddrMode((uint8_t)uwb::MacAddressMode::SHORT);
		rangingParams.deviceMacAddr(srcAddr);
		
		
		
	    appParams.destinationMacAddr(dstAddr);
	    appParams.frameConfig(uwb::RfFrameConfig::SP3);
		appParams.slotPerRR(25);
		appParams.rangingDuration(200);
		appParams.stsConfig(uwb::StsConfig::StaticSts);
		appParams.stsSegments(1);
		appParams.sfdId(2);
		appParams.preambleCodeIndex(10);	
		
   
	}
	
};

#endif
