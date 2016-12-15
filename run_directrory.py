from pathlib import Path
import subprocess
from sys import argv
from time import time


class TaskRunner:
    def __init__(self):
        self.executable = Path(argv[1])
        self.directory = Path(argv[2])
        self.out = Path(argv[3])

    def run(self):
        for task in sorted(list(self.directory.iterdir())):
            print('Start task: {0}'.format(task.name))
            start_time = time()
            self.run_task(task)
            print('Task: {0} takes \n'.format(task.name), time() - start_time)

    def run_task(self, task: Path):
        output_dir = self.create_and_return_output_dir(task)
        command = [str(self.executable),
                   '--out={0}'.format(output_dir),
                   '--task={0}'.format(task)]
        subprocess.run(command)

    def create_and_return_output_dir(self, task: Path):
        output_dir = (self.out / TaskRunner.get_name_we(task))
        if not output_dir.exists():
            output_dir.mkdir()
        return output_dir

    @staticmethod
    def get_name_we(path: Path):
        """
        :param path:
        :return: name without last extension
        """
        return path.name.split('.')[0]


def main():
    runner = TaskRunner()
    runner.run()


if __name__ == '__main__':
    main()
