import sys

from functools import reduce

class DepthScan:
    """
    Day 1: Sonar Sweep

    Part 1
    """
    def __init__(self, input_file=''):
        self.filename = input_file

    def measure(self) -> int:
        increases = 0
        buffer_previous = 0

        if self.filename:
            try:
                with open(self.filename, 'r') as depth_readings:
                    for reading in depth_readings:
                        if 0 >= buffer_previous:
                            buffer_previous = int(reading)
                        else:
                            if buffer_previous < int(reading):
                                increases += 1

                            buffer_previous = int(reading)
            except OSError as ex:
                """Terminate if an invalid path has been provided."""
                sys.stdout.write(ex.strerror + '\n')
                sys.exit()

        return increases

class TripleDepthScan:
    """
    Day 1: Sonar Sweep

    Part 2
    """
    def __init__(self, input_file=''):
        self.filename = input_file

    def measure(self):
        increases = 0
        previous = 0

        buffer = [
            -1,
            -1,
            -1
        ]
        """Pre-populating the buffer so that we don't have to verify the length at any point."""

        if self.filename:
            try:
                with open(self.filename, 'r') as triple_depth_readings:
                    for reading in triple_depth_readings:
                        buffer.pop(0)
                        buffer.append(int(reading))

                        if -1 not in buffer:
                            """Only begin once previously populated values have been replaced."""
                            triple = reduce(lambda x, y: x+y, buffer)
                            """Reduce triplets down to a sum of all integer list elements."""

                            if 0 < previous:
                                """Start once we have an existing triple."""
                                if previous < triple:
                                    increases += 1

                            previous = triple
            except OSError as ex:
                """Terminate if an invalid path has been provided."""
                sys.stdout.write(ex.strerror + '\n')
                sys.exit()

        return increases

print(DepthScan('input.txt').measure())
"""P1."""
print(TripleDepthScan('input.txt').measure())
"""P2."""
