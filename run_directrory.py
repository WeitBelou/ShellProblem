from sys import argv
from subprocess import run
from pathlib import Path
from time import time


def main():
    directory = Path(argv[1])
    command_base = ['bin/ShellProblem']

    for task in sorted(list(directory.iterdir())):
        start_time = time()
        output_dir = (Path('out/') / task.name.split('.')[0])
        if not output_dir.exists():
            output_dir.mkdir()
        command = command_base + [f'--out={output_dir}', f'--task={task}']
        run(command)

        print(f'Task: {task.name} takes ', time() - start_time)


if __name__ == '__main__':
    main()
