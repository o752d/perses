#!/usr/bin/env python3

import os
import unittest
import tempfile
import check_copyright


TINY_COPYRIGHT = ["This is a sample message.\n"] *3
TINY_COPYRIGHT_CMTBLK = "/*\n" + " * This is a sample message.\n" *3 + ' */\n'


class TestCheckCopyright(unittest.TestCase):

    temp_dir = None
    java_temp_file = None
    copyright_checker = check_copyright.CopyrightChecker(TINY_COPYRIGHT)

    def setUp(self):
        self.temp_dir = tempfile.mkdtemp()
        with tempfile.NamedTemporaryFile(suffix='.java', dir=self.temp_dir, delete=False) as self.java_temp_file:
            self.java_temp_file.write(b"import java.util.*;")


    def tearDown(self):
        os.unlink(self.java_temp_file.name)
        os.rmdir(self.temp_dir)


    def test_check_copyright(self):
        self.assertFalse(self.copyright_checker.check_copyright(self.java_temp_file.name))
        with open(self.java_temp_file.name, 'r+') as java_file:
            old_content = java_file.read()
            new_content = TINY_COPYRIGHT_CMTBLK + old_content
            java_file.write(new_content)
        self.assertTrue(self.copyright_checker.check_copyright(self.java_temp_file.name))


    def test_check_folder(self):
        missing_list = self.copyright_checker.check_folder(self.temp_dir, 'java')
        self.assertEqual(missing_list, [self.java_temp_file.name])
        missing_list = self.copyright_checker.check_folder(self.temp_dir, 'cpp')
        self.assertEqual(missing_list, [])


    def test_update_files(self):
        with open(self.java_temp_file.name) as java_file:
            old_content = java_file.read()
        self.copyright_checker.update_files([self.java_temp_file.name])
        with open(self.java_temp_file.name) as java_file:
            new_content = java_file.read()
        self.assertEqual(new_content, TINY_COPYRIGHT_CMTBLK + old_content)


if __name__ == '__main__':

    unittest.main()
