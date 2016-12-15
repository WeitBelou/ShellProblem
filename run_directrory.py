import subprocess
import sys
from pathlib import Path


def main():
    directory = Path(sys.argv[1])
    command_base = ['bin/ShellProblem']

    for filename in sorted(list(directory.iterdir())):
        task = filename
        output_dir = (Path('out/') / filename.name.split('.')[0])
        if not output_dir.exists():
            output_dir.mkdir()
        command = command_base + [f'--out={output_dir}', f'--task={task}']
        subprocess.run(command)


if __name__ == '__main__':
    main()
