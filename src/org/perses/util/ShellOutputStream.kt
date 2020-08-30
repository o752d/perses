/*
 * Copyright (C) 2018-2020 University of Waterloo.
 *
 * This file is part of Perses.
 *
 * Perses is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 3, or (at your option) any later version.
 *
 * Perses is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * Perses; see the file LICENSE.  If not see <http://www.gnu.org/licenses/>.
 */
package org.perses.util

import com.google.common.collect.ImmutableList
import java.io.ByteArrayOutputStream
import java.io.OutputStream
import java.nio.charset.StandardCharsets

class ShellOutputStream : OutputStream() {

  private var current: ByteArrayOutputStream? = ByteArrayOutputStream()
  private val builderList = ImmutableList.builder<String>()

  override fun write(b: Int) {
    current!!.write(b)
    if (b == '\n'.toInt()) {
      dumpCurrentToList()
      current!!.reset()
    }
  }

  override fun close() {
    if (current!!.size() > 0) {
      dumpCurrentToList()
    }
    current = null
    super.close()
  }

  fun toOutputStringList(): ShellOutputLines {
    check(current == null) {
      "Need to call close() before this function."
    }
    return ShellOutputLines(builderList.build())
  }

  private fun dumpCurrentToList() {
    builderList.add(current!!.toString(StandardCharsets.UTF_8.name()))
  }
}
