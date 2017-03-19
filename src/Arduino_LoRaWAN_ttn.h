/* Arduino_LoRaWAN_ttn.h	Mon Oct 31 2016 15:44:49 tmm */

/*

Module:  Arduino_LoRaWAN_ttn.h

Function:
	LoRaWAN-variants for The Things Network.

Version:
	V0.2.0	Mon Oct 31 2016 15:44:49 tmm	Edit level 1

Copyright notice:
	This file copyright (C) 2016 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	An unpublished work.  All rights reserved.
	
	This file is proprietary information, and may not be disclosed or
	copied without the prior permission of MCCI Corporation.
 
Author:
	Terry Moore, MCCI Corporation	October 2016

Revision history:
   0.2.0  Mon Oct 31 2016 15:44:49  tmm
	Module created.

*/

#ifndef _ARDUINO_LORAWAN_TTN_H_		/* prevent multiple includes */
#define _ARDUINO_LORAWAN_TTN_H_

#ifndef _ARDUNIO_LORAWAN_H_
# include <Arduino_LoRaWAN.h>
#endif

#ifndef _MCCIADK_ENV_H_
# include <mcciadk_env.h>
#endif

/* this is a bit of a hack, but... */
/* make sure we have the config variables in scope */
#include "../../arduino-lmic/project_config/lmic_project_config.h"

class Arduino_LoRaWAN_ttn_base :  public Arduino_LoRaWAN
	{
public:
	Arduino_LoRaWAN_ttn_base() {};
        using Super = Arduino_LoRaWAN;
        Arduino_LoRaWAN_ttn_base(const lmic_pinmap & pinmap) : Super(pinmap) {};

protected:
	// the netjoin function does any post-join work -- at present
	// this can be shared by all networks.
	virtual void NetJoin();

private:
	};

class Arduino_LoRaWAN_ttn_eu868 : public Arduino_LoRaWAN_ttn_base
	{
public:
        using Super = Arduino_LoRaWAN_ttn_base;
	Arduino_LoRaWAN_ttn_eu868() {};
        Arduino_LoRaWAN_ttn_eu868(const lmic_pinmap & pinmap) : Super(pinmap) {};

private:
	};

class Arduino_LoRaWAN_ttn_us915 : public Arduino_LoRaWAN_ttn_base
	{
public:
        using Super = Arduino_LoRaWAN_ttn_base;
        Arduino_LoRaWAN_ttn_us915() {};
        Arduino_LoRaWAN_ttn_us915(const lmic_pinmap & pinmap) : Super(pinmap) {};

protected:
	// the NetBegin() function does specific work when starting
	// up. For ttn we need to turn off the link check mode, and
	// select the subband.
	bool NetBegin();

	// Implement the NetJoin() operations for US915
	virtual void NetJoin();

private:
	};

class Arduino_LoRaWAN_ttn_as923 : public Arduino_LoRaWAN_ttn_base
	{
public:
        using Super = Arduino_LoRaWAN_ttn_base;
        Arduino_LoRaWAN_ttn_as923() {};
        Arduino_LoRaWAN_ttn_as923(const lmic_pinmap & pinmap) : Super(pinmap) {};

private:
	};

#if CFG_eu868
# define Arduino_LoRaWAN_REGION_TAG eu868
#elif CFG_us915
# define Arduino_LoRaWAN_REGION_TAG us915
#elif defined(CFG_as923) && CFG_as923
# define Arduino_LoRaWAN_REGION_TAG as923
#else
# error "Can't define Arduino_LoRaWAN_REGION_TAG"
#endif

#define Arduino_LoRaWAN_ttn_LOCAL_(Region)		\
	Arduino_LoRaWAN_ttn_ ## Region

#define Arduino_LoRaWAN_ttn_LOCAL(Region)		\
	Arduino_LoRaWAN_ttn_LOCAL_(Region)

class Arduino_LoRaWAN_ttn : public Arduino_LoRaWAN_ttn_LOCAL(Arduino_LoRaWAN_REGION_TAG)
	{
public:
        using Super = Arduino_LoRaWAN_ttn_LOCAL(Arduino_LoRaWAN_REGION_TAG);
        Arduino_LoRaWAN_ttn() {};
        Arduino_LoRaWAN_ttn(const lmic_pinmap & pinmap) : Super(pinmap) {};

private:
	};


/**** end of Arduino_LoRaWAN_ttn.h ****/
#endif /* _ARDUINO_LORAWAN_TTN_H_ */