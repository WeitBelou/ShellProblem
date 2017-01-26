##Shell problem

###Introduction
Shell problem is a simple program that solves both heat 
conduction and elasticity problems using deal.II library.

###How to build

1) Download and install deal.II library from
[site](https://dealii.org) or
[github](https://github.com/dealii/dealii).

2) Download source:
```
$ git clone https://github.com/WeitBelou/ShellProblem.git
```
3) Build
```
$ cd ShellProblem
$ mkdir build
$ cd build
$ export DEAL_II_DIR=path/to/dealii/installation/root
$ cmake .. 
$ make
```

###Usage
CMake will create in ShellProblem directory `bin`.
In this directory you will find `ShellProblem`
executable.

1) Run program with one task...
```
$ ShellProblem --task=<task-name> --out=<output-dir>
```
2) ... or several tasks
```
$ python run_directory.py <executable> <dir_with_tasks> <output_dir>
```
In this case output  files will be written in
`<output_dir>/<name_of_task>`

3) You can generate mesh for every .geo file in directory with
```
python generate_meshes.py <dir_with_geo_files>
```