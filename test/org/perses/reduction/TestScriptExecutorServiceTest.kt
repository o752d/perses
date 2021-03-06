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
package org.perses.reduction

import com.google.common.base.Stopwatch
import com.google.common.io.MoreFiles
import com.google.common.io.RecursiveDeleteOption
import com.google.common.truth.Truth.assertThat
import org.junit.After
import org.junit.Before
import org.junit.Test
import org.junit.runner.RunWith
import org.junit.runners.JUnit4
import org.perses.TestUtility
import org.perses.grammar.c.LanguageC
import org.perses.program.EnumFormatControl.ORIG_FORMAT
import org.perses.program.ScriptFile
import org.perses.program.SourceFile
import org.perses.reduction.TestScriptExecutorService.Companion.ALWAYS_TRUE_PRECHECK
import org.perses.util.TimeUtil
import java.io.ByteArrayOutputStream
import java.io.File
import java.io.PrintStream
import java.nio.charset.StandardCharsets
import java.util.ArrayList
import java.util.concurrent.Future
import java.util.concurrent.TimeUnit
import java.util.function.Consumer

/** Test for [TestScriptExecutorService]  */
@RunWith(JUnit4::class)
class TestScriptExecutorServiceTest {
  companion object {
    private const val FOLDER = "test_data/delta_1/"
  }

  private val sourceFile = SourceFile(File(FOLDER, "t.c"), LanguageC)
  private val invalidSourceFile = SourceFile(File("test_data/misc/t1.c"), LanguageC)
  private val testScript = ScriptFile(File(FOLDER, "r.sh"))
  private val slowTestScript = ScriptFile(File(FOLDER, "slow_r.sh"))
  private val program = TestUtility.createSparTreeFromFile(sourceFile.file).programSnapshot

  private var workingDirectory: File? = null

  @Before
  fun setup() {
    workingDirectory =
      TestUtility.createCleanWorkingDirectory(TestScriptExecutorServiceTest::class.java)
  }

  @After
  fun teardown() {
    if (workingDirectory!!.exists()) {
      // Just to make sure to release the resources.
      MoreFiles.deleteRecursively(workingDirectory!!.toPath(), RecursiveDeleteOption.ALLOW_INSECURE)
    }
    workingDirectory = null
  }

  @Test
  fun testThreadCount_1() {
    testTestScriptExecutor(threadCount = 1)
  }

  @Test
  fun testThreadCount_4() {
    testTestScriptExecutor(threadCount = 4)
  }

  @Test
  fun test_testScriptExecutionMonitor() {
    val oldSysout = System.out
    val oldSyserr = System.err
    val byteArrayOutputStream = ByteArrayOutputStream()
    val newOut = PrintStream(
      byteArrayOutputStream,
      /*auto_flush=*/true,
      StandardCharsets.UTF_8.name()
    )
    System.setOut(newOut)
    System.setErr(newOut)
    try {
      TestScriptExecutorService(
        workingDirectory!!,
        1,
        slowTestScript,
        sourceFile.file.name,
        scriptExecutionMonitorIntervalMillis = TimeUtil.toMillisFromSeconds(1)
      ).use {
        it.testProgramAsync(ALWAYS_TRUE_PRECHECK, program!!, ORIG_FORMAT).get()
      }
      newOut.flush()
      val stdout = byteArrayOutputStream.toString(StandardCharsets.UTF_8.name())
      assertThat(stdout).contains(TestScriptExecutorService.MSG_SCRAIPT_RUN_TOO_LONG)
    } finally {
      System.setOut(oldSysout)
      System.setErr(oldSyserr)
    }
  }

//  private fun createConfiguration(
//    threadCount: Int,
//    testScript: ScriptFile = this.testScript
//  ) = ReductionConfiguration(
//    workingFolder = workingDirectory!!,
//    testScript = testScript,
//    fileToReduce = sourceFile,
//    bestResultFile = sourceFile.file,
//    statisticsFile = null,
//    progressDumpFile = null,
//    programFormatControl = ORIG_FORMAT,
//    fixpointReduction = true,
//    enableTestScriptExecutionCaching = true,
//    useRealDeltaDebugger = false,
//    numOfReductionThreads = threadCount
//  )

  private fun testTestScriptExecutor(threadCount: Int) {
    val stopwatch = Stopwatch.createStarted()
    TestScriptExecutorService(
      workingDirectory!!,
      threadCount,
      testScript,
      sourceFile.file.name,
      scriptExecutionMonitorIntervalMillis = TimeUtil.toMillisFromMinutes(4)
    ).use {
      // TODO: refine this test.
      testPassing(it)
      testFailing(it)
      testPrecheckFailing(it)
      stopwatch.stop()
      println(
        "#threads=" + threadCount + ": time=" + stopwatch.elapsed(TimeUnit.SECONDS) + " seconds"
      )
    }
  }

  private fun testPrecheckFailing(it: TestScriptExecutorService) {
    val invalidProgram = TestUtility.createSparTreeFromFile(invalidSourceFile.file)
      .programSnapshot
    val futureList: MutableList<Future<TestScript.TestResult>> = ArrayList()
    for (i in 0..49) {
      futureList.add(
        it.testProgramAsync(
          { TestScript.TestResult(exitCode = 1, elapsedMilliseconds = 1) },
          invalidProgram,
          ORIG_FORMAT
        )
      )
    }
    futureList.forEach(
      Consumer {
        try {
          assertThat(it.get().isPass).isFalse()
        } catch (e: Throwable) {
          throw AssertionError(e)
        }
      }
    )
  }

  private fun testFailing(it: TestScriptExecutorService) {
    val invalidProgram = TestUtility.createSparTreeFromFile(invalidSourceFile.file)
      .programSnapshot
    val futureList: MutableList<Future<TestScript.TestResult>> = ArrayList()
    for (i in 0..49) {
      futureList.add(
        it.testProgramAsync(
          ALWAYS_TRUE_PRECHECK,
          invalidProgram,
          ORIG_FORMAT
        )
      )
    }
    futureList.forEach(
      Consumer {
        try {
          assertThat(it.get().isPass).isFalse()
        } catch (e: Throwable) {
          throw AssertionError(e)
        }
      }
    )
  }

  private fun testPassing(service: TestScriptExecutorService) {
    val futureList: MutableList<Future<TestScript.TestResult>> = ArrayList()
    for (i in 0..49) {
      futureList.add(
        service.testProgramAsync(
          ALWAYS_TRUE_PRECHECK,
          program!!,
          ORIG_FORMAT
        )
      )
    }
    futureList.forEach(
      Consumer {
        try {
          assertThat(it.get().isPass).isTrue()
        } catch (e: Throwable) {
          throw AssertionError(e)
        }
      }
    )
  }
}
