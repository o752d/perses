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
package org.perses.program

import com.google.common.base.Joiner
import com.google.common.collect.ImmutableList
import com.google.common.io.Files
import com.google.common.truth.Truth.assertThat
import org.junit.Assert
import org.junit.Test
import org.junit.runner.RunWith
import org.junit.runners.JUnit4
import org.perses.TestUtility
import org.perses.grammar.c.LanguageC
import java.io.File
import java.nio.charset.StandardCharsets
import java.util.stream.Collectors

@RunWith(JUnit4::class)
class TokenizedProgramTest {
  @Test
  fun testCodeFormatRemains() {
    testCodeFormatRemains("test_data/java_helloworld/t.java")
    testCodeFormatRemains("test_data/parentheses/t.c")
  }

  @Test
  fun testPrintCodeInLines() {
    testTokenEquivalence("test_data/java_helloworld/t.java")
    testTokenEquivalence("test_data/parentheses/t.c")
  }

  @Test
  fun testSourceCodeIsCached() {
    val filepath = "test_data/java_helloworld/t.java"
    val p = TestUtility.createTokenizedProgramFromFile(filepath)
    assertThat(p.toSourceCodeInOrigFormatWithBlankLines())
      .isSameInstanceAs(p.toSourceCodeInOrigFormatWithBlankLines())
  }

  @Test
  fun testCompactSourceCode() {
    val sourceCode =
      """int a = 0;
      |
      |int b = 0;
      |
      |int c = 0;
    """.trimMargin()
    val program = TestUtility.createTokenizedProgramFromString(sourceCode, LanguageC)
    assertThat(program.toSourceCodeInOrigFormatWithBlankLines().trim())
      .isEqualTo(sourceCode.trim())
    assertThat(program.toCompactSourceCode().trim()).isEqualTo(
      """int a = 0;
      |int b = 0;
      |int c = 0;
      """.trimMargin()
    )
  }

  @Test
  fun testFormattedPrintingShouldCrashOnSkewedTokens() {
    val sourceCode = "int a, long_var;"
    val program = TestUtility.createTokenizedProgramFromString(sourceCode, LanguageC)
    val first = program.tokens[0]
    val third = program.tokens[2]
    val fourth = program.tokens[3]

    val newProgram = TokenizedProgram(ImmutableList.of(first, fourth, third, fourth))
    Assert.assertThrows(IllegalStateException::class.java) {
      newProgram.toCompactSourceCode()
    }
    Assert.assertThrows(java.lang.IllegalStateException::class.java) {
      newProgram.toSourceCodeInOrigFormatWithBlankLines()
    }
  }

  private fun testTokenEquivalence(filepath: String) {
    val program = Joiner.on("")
      .join(
        TestUtility.createTokenizedProgramFromFile(filepath).tokens.stream()
          .map { obj: PersesToken -> obj.text }
          .map { s: String -> s.replace("\\s|\n".toRegex(), "") }
          .collect(Collectors.toList<String>())
      )
    val text = Files.asCharSource(File(filepath), StandardCharsets.UTF_8)
      .read()
      .replace("\\s|\n".toRegex(), "")
    assertThat(program).isEqualTo(text)
  }

  private fun testCodeFormatRemains(filepath: String) {
    val program = TestUtility.createTokenizedProgramFromFile(filepath)
    assertThat(program.toSourceCodeInOrigFormatWithBlankLines().trim())
      .isEqualTo(Files.asCharSource(File(filepath), StandardCharsets.UTF_8).read().trim())
  }
}
