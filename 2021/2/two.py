import sys

class PlannedCourse:
    """
    Day 2: Dive!

    Part 1
    """
    def __init__(self, input_file=''):
        self.filename = input_file
    
    def multiply(self) -> int:
        values = self.getCourseReadings()

        return values[0] * values[1]

    def getCourseReadings(self) -> tuple:
        """
        Produce a tuple which holds the forward
        movement and height data of the final
        resting position of the submarine.

        Returns:
            tuple: Horizontal and vertical height pair to multiply together for final output
        """
        h_pos = 0
        depth = 0

        if self.filename:
            try:
                with open(self.filename, 'r') as navigation_instructions:
                    for instruction in navigation_instructions:
                        parts = instruction.rstrip().split(' ')
                        """Remove any unwanted whitspace or trailing newline characters for clean parsing of navigation data."""

                        if parts and parts[0] in self.validInstructions():
                            if 'forward' == parts[0]:
                                h_pos += int(parts[1])
                            elif 'down' == parts[0]:
                                depth += int(parts[1])
                            elif 'up' == parts[0]:
                                depth -= int(parts[1])

            except OSError as ex:
                """Terminate if an invalid path has been provided."""
                sys.stdout.write(ex.strerror + '\n')
                sys.exit()

        return (h_pos, depth)

    def validInstructions(self) -> list:
        return [
            'forward',
            'down',
            'up'
        ]

print(PlannedCourse('input.txt').multiply())
"""P1."""
