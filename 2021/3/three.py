import sys

class BinaryDiagnostic:
    """
    Day 3: Binary Diagnostic.

    Part 1.
    """
    def __init__(self, input_file=''):
        self.filename = input_file

        self.report = self.parseInput()

    def parseInput(self) -> list:
        binary_counts = []

        if self.filename:
            try:
                with open(self.filename, 'r') as diagnostic_report:
                    for reading in diagnostic_report:
                        stripped = reading.rstrip()
                        """Take out newline chars for accurate string length."""

                        if not binary_counts:
                            binary_counts = [{'zeroes': 0, 'ones': 0} for char in stripped]
                            """Pre-populate list counts one time only so we can reference indexes on continuation."""

                        for index, binary in enumerate(str(stripped)):
                            """Track the enumerator for access to correct column bit."""
                            if '0' == binary:
                                binary_counts[index]['zeroes'] += 1
                            elif '1' == binary:
                                binary_counts[index]['ones'] += 1

            except OSError as ex:
                """Terminate if an invalid path has been provided."""
                sys.stdout.write(ex.strerror + '\n')
                sys.exit()

        return binary_counts

    def consumption(self) -> int:
        common_bits = ''

        if self.report:
            for column in self.report:
                if column['zeroes'] < column['ones']:
                    common_bits += '1'
                else:
                    common_bits += '0'

        gamma = int(common_bits, 2)
        """Binary string to decimal conversion."""
        epsilon = int(self.flipBits(common_bits), 2)
        """Flip binary values for second epsilon reading."""

        return gamma * epsilon

    def flipBits(self, bits='') -> str:
        new_bits = ''

        if bits:
            for bit in bits:
                if '1' == bit:
                    new_bits += '0'
                elif '0' == bit:
                    new_bits += '1'

        return new_bits

print(BinaryDiagnostic('input.txt').consumption())
"""P1."""
