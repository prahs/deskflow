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

#include "platform/XWindowsClipboard.h"

//! Convert to/from some text encoding
class XWindowsClipboardAnyBitmapConverter : public IXWindowsClipboardConverter
{
public:
  XWindowsClipboardAnyBitmapConverter();
  virtual ~XWindowsClipboardAnyBitmapConverter();

  // IXWindowsClipboardConverter overrides
  virtual IClipboard::EFormat getFormat() const;
  virtual Atom getAtom() const = 0;
  virtual int getDataSize() const;
  virtual std::string fromIClipboard(const std::string &) const;
  virtual std::string toIClipboard(const std::string &) const;

protected:
  //! Convert from IClipboard format
  /*!
  Convert raw BGR pixel data to another image format.
  */
  virtual std::string doBGRFromIClipboard(const uint8_t *bgrData, uint32_t w, uint32_t h) const = 0;

  //! Convert from IClipboard format
  /*!
  Convert raw BGRA pixel data to another image format.
  */
  virtual std::string doBGRAFromIClipboard(const uint8_t *bgrData, uint32_t w, uint32_t h) const = 0;

  //! Convert to IClipboard format
  /*!
  Convert an image into raw BGR or BGRA image data and store the
  width, height, and image depth (24 or 32).
  */
  virtual std::string doToIClipboard(const std::string &, uint32_t &w, uint32_t &h, uint32_t &depth) const = 0;
};
