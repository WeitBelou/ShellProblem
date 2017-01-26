import subprocess
from pathlib import Path
from sys import argv

class MeshGenerator:
    def __init__(self):
        self.directory = Path(argv[1])

    def run(self):
        for task in sorted(list(self.directory.iterdir())):
            print('Generating mesh from: {0}'.format(task.name))
            self.generate(task)

    @staticmethod
    def generate(name: Path):
        command = ['gmsh',
                   '-1', '-2', '-3',
                   '{0}'.format(name)]
        subprocess.run(command)


def main():
    mesher = MeshGenerator()
    mesher.run()


if __name__ == '__main__':
    main()
