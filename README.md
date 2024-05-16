<div align="center">
  <h1>Latin Script</h1>
</div>

<p align="center">
  <img src="https://github.com/hheghine/LatinScript/assets/119530584/0adb13ad-78fe-47a4-8461-816ca6392e9c" />
  <i><br>Interpreter written in C++ that can process and execute Latin-based scripting language code</i><br><br>
</p>


```
//
//  README
//  Latin Script
//
//  05/05/2024
//

==================
 1.0 Introduction
==================

This application implements a parser and executor for the toy language
"latin script". The general layout and program flow is described below:

|==============|       |==============|        |==============|
| Input file   |       | Parser       |  --->  | Executor     |
|              |  ---> |              |        |              |
|              |       |              |  <---  |              |
|==============|       |==============|        |==============|

All output is written to stdout.


==================
 2.0 Usage
==================

To compile the application from source, you must have the g++ GNU C++ compiler
installed on your system, with all standard libraries installed.

A GNU Makefile is included for ease of compilation of this project.

>  make
>  ./latin-script <filename.ls>

```
