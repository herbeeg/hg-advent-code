import sys

class DepthScan:
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

print(DepthScan('input.txt').measure())