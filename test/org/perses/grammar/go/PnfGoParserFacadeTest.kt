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
package org.perses.grammar.go

import com.google.common.truth.Truth
import org.junit.Test
import org.junit.runner.RunWith
import org.junit.runners.JUnit4
import org.perses.TestUtility
import java.io.File

@RunWith(JUnit4::class)
class PnfGoParserFacadeTest {
  val facade = PnfGoParserFacade()

  // Collection for keeping track of the shards of tests we need to run
  private companion object testData {
    val shard1 = mutableListOf<File>()
    val shard2 = mutableListOf<File>()
    val shard3 = mutableListOf<File>()
    val shard4 = mutableListOf<File>()
    val shard5 = mutableListOf<File>()
    val shard6 = mutableListOf<File>()

    init {
      var counter = 0
      val files = listOf(shard1, shard2, shard3, shard4, shard5, shard6)
      for (file in TestUtility.getGolangTestFiles()) {
        files.get(counter % files.size).add(file)
        counter += 1
      }
    }
  }

  fun testString(program: String, name: String) {
    val parseTreeFromOrigParser = facade.parseWithOrigGoParser(program, name)
    val tokensByOrigParser = TestUtility.extractTokens(parseTreeFromOrigParser.tree)

    val parseTreeWithPnfParser = facade.parseString(program, name)
    val tokensByPnfParser = TestUtility.extractTokens(parseTreeWithPnfParser.tree)

    Truth.assertThat(tokensByPnfParser).containsExactlyElementsIn(tokensByOrigParser).inOrder()
  }

  fun testSingleFile(file: File) {
    try {
      System.err.println("Testing file ${file.getAbsolutePath()}")
      val check = file.readText()
      // Skip files that contain ERROR in them, as they may not parse properly.
      if (check.contains("ERROR") || check.contains("ignored")) {
        return
      }
      // Skip bad files (using nil as an identifier, which is technically allowed,
      //  but causes a lot of headaches for the grammar)
      if (file.getAbsolutePath().contains("issue4252.dir") ||
        file.getAbsolutePath().contains("rename.go")
      ) {
        return
      }
      // Skip fancy literals (for now) -- need to fix lexer for this.
      if (file.getAbsolutePath().contains("literal2.go")) {
        return
      }

      testString(check, file.toString())
    } catch (err: java.io.FileNotFoundException) {
      // Suppress missing files (there's some strangeness with java and Unicode file names).
    }
  }

  @Test
  fun testShard1() {
    for (file in testData.shard1) {
      testSingleFile(file)
    }
  }

  @Test
  fun testShard2() {
    for (file in testData.shard2) {
      testSingleFile(file)
    }
  }

  @Test
  fun testShard3() {
    for (file in testData.shard3) {
      testSingleFile(file)
    }
  }

  @Test
  fun testShard4() {
    for (file in testData.shard4) {
      testSingleFile(file)
    }
  }

  @Test
  fun testShard5() {
    for (file in testData.shard5) {
      testSingleFile(file)
    }
  }

  @Test
  fun testShard6() {
    for (file in testData.shard6) {
      testSingleFile(file)
    }
  }

  @Test
  fun basicTest() {
    val program =
      """
      |package main
      |import "fmt"
      |type Uint64 struct {
      |   hi	uint32
      |   lo	uint32
      |}
      |
      |
      |func main() {
      |    fmt.Println("go" + "lang")
      |    fmt.Println("go" + "lang" + "2")
      |    *(*int)(f) = 0
      |    *f = 5
      |
      |    assert(0 == complex(0, 12))
      |}
    """.trimMargin()

    testString(program, "<in memory>")
  }
}
