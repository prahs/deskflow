/*
 * Deskflow -- mouse and keyboard sharing utility
 * Copyright (C) 2012-2016 Symless Ltd.
 * Copyright (C) 2004 Chris Schoeneman
 *
 * This package is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * found in the file LICENSE that should have accompanied this file.
 *
 * This package is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "io/StreamBuffer.h"
#include "io/StreamFilter.h"
#include "mt/Mutex.h"

class IEventQueue;

//! Packetizing stream filter
/*!
Filters a stream to read and write packets.
*/
class PacketStreamFilter : public StreamFilter
{
public:
  PacketStreamFilter(IEventQueue *events, deskflow::IStream *stream, bool adoptStream = true);
  ~PacketStreamFilter();

  // IStream overrides
  virtual void close();
  virtual uint32_t read(void *buffer, uint32_t n);
  virtual void write(const void *buffer, uint32_t n);
  virtual void shutdownInput();
  virtual bool isReady() const;
  virtual uint32_t getSize() const;

protected:
  // StreamFilter overrides
  virtual void filterEvent(const Event &);

private:
  bool isReadyNoLock() const;
  bool readPacketSize();
  bool readMore();

private:
  Mutex m_mutex;
  uint32_t m_size;
  StreamBuffer m_buffer;
  bool m_inputShutdown;
  IEventQueue *m_events;
};
