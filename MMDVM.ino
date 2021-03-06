/*
 *   Copyright (C) 2015 by Jonathan Naylor G4KLX
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include "Config.h"
#include "Globals.h"

// Global variables
MMDVM_STATE m_modemState = STATE_IDLE;

bool m_dstarEnable = true;
bool m_dmrEnable   = true;
bool m_ysfEnable   = true;

bool m_tx = false;

CDStarRX   dstarRX;
CDStarTX   dstarTX;

CDMRIdleRX dmrIdleRX;
CDMRRX     dmrRX;
CDMRTX     dmrTX;

CYSFRX     ysfRX;
CYSFTX     ysfTX;

CCalRX     calRX;
CCalTX     calTX;

CSerialPort serial;
CIO io;

void setup()
{
  serial.start();
}

void loop()
{
  serial.process();
  
  io.process();

  // The following is for transmitting
  if (m_dstarEnable && m_modemState == STATE_DSTAR)
    dstarTX.process();

  if (m_dmrEnable && m_modemState == STATE_DMR)
    dmrTX.process();

  if (m_ysfEnable && m_modemState == STATE_YSF)
    ysfTX.process();

  if (m_modemState == STATE_CALIBRATE)
    calTX.process();
}

