import unittest

from core.gbt_utils_extended import saveGBTPhaseScanResults

import os
from tempfile import mkstemp
from ctypes import c_uint32
from filecmp import cmp

class TestSaveGBTPhaseScanResults(unittest.TestCase):

    def setUp(self):
        # Fill in a result array with a known pattern
        self.phasesBlob = (c_uint32 * (24*16))()
        for idx in range(len(self.phasesBlob)):
            self.phasesBlob[idx] = idx

        self.nOfRepetitions = len(self.phasesBlob) - 1

        # Prepare a temp file
        (self.fd, self.filename) = mkstemp()

    def tearDown(self):
        # Delete the temp file
        os.close(self.fd)
        os.remove(self.filename)

    def testNewFile(self):
        """
        Test writing the GBT RX phase scan results of 1 OH to a file.
        """

        saveGBTPhaseScanResults(self.filename, 0, self.phasesBlob, self.nOfRepetitions)

        # Compare with the reference file
        referenceFile = os.path.dirname(os.path.abspath(__file__)) + "/data/test_saveGBTPhaseScanResults_NewFile.root"
        self.assertTrue(cmp(self.filename, referenceFile))

    def testAppendToFile(self):
        """
        Test writing the GBT RX phase scan results of 4 OHs to the same file.
        """

        for i in range(4):
            saveGBTPhaseScanResults(self.filename, i, self.phasesBlob, self.nOfRepetitions)

        # Compare with the reference file
        referenceFile = os.path.dirname(os.path.abspath(__file__)) + "/data/test_saveGBTPhaseScanResults_AppendToFile.root"
        self.assertTrue(cmp(self.filename, referenceFile))

    def testIncorrectHeader(self):
        """
        Test the detection of corrupted file with an incorrect header.
        """

        # Prepare a file with a corrupted header
        with open(self.filename, 'wb') as f:
            f.write("ohN/I:vfatN/")

        self.assertRaises(RuntimeError, saveGBTPhaseScanResults, self.filename, 0, self.phasesBlob, self.nOfRepetitions)

    def testMissingEOL(self):
        """
        Test the detection of corrupted file with a missing EOL.
        """

        # Prepare a results file, then delete the trailing EOL
        saveGBTPhaseScanResults(self.filename, 0, self.phasesBlob, self.nOfRepetitions)

        with open(self.filename, 'r+b') as f:
            f.seek(-1, 2) # Go to the last character
            f.truncate()

        self.assertRaises(RuntimeError, saveGBTPhaseScanResults, self.filename, 1, self.phasesBlob, self.nOfRepetitions)
