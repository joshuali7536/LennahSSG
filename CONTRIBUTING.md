# LENNAH SSG Contributing Guide

## Environment Setup

## Clang-Format
You can set up Clang to be used in the command line or through a Visual Studio Extension.

### Command Line:
1. Install Clang-Format from [here](https://llvm.org/builds/)

    ![image](https://user-images.githubusercontent.com/49960519/140454745-859a9bed-e809-4b35-b0a6-e19fe5e5295c.png)
1. Then when you install make sure to allow a new PATH to be created for Clang

    ![image](https://user-images.githubusercontent.com/49960519/140510707-8ca0c68e-737e-400f-8109-d271897849af.png)
3. To run clang-format open the terminal and use the following command in the project folder:
```sh
$ clang-format -style=file LennahSSG/*.cpp LennahSSG/*.h
```

### Extension:
1. Install Clang by following the instructions [here](https://clangpowertools.com/blog/get-started-with-clang-power-tools.html).
1. Turn on "Format on save" in the settings.

    ![image](https://user-images.githubusercontent.com/49960519/140451001-b1ebf533-f74f-4c68-bcf0-daaea0adbe01.png)
Now files should automatically format upon saving.
1. You can also format by clicking the format button(Alt+M) in Visual Studio:

    ![image](https://user-images.githubusercontent.com/49960519/140455055-dded7859-8c2b-4a09-bc7e-f2d02a5bbcbf.png)

## Clang-Tidy
You can set up Clang to be used in the command line or through a Visual Studio Extension.

### Command Line:
1. Clang-Tidy is included in the same package as Clang-Format. Follow the same instructions as Clang-Format if not already done.
1. To run clang-tidy open the terminal and use the following command in the project folder:
```sh
$ clang-tidy --config="" LennahSSG/*.cpp LennahSSG/*.h --extra-arg=-std=c++17 --extra-arg=-xc++ --
```
This will display the lint that needs fixing in errors.

### Extension:
1. Follow the same installation as for the extension for Clang-Format if not already done.
1. Turn on "Format after Tidy" and "Tidy on save"

    ![image](https://user-images.githubusercontent.com/49960519/140455540-7c606b0f-9c3a-4a0f-8118-18b7ce0585d6.png)
1. You can Lint the current file by clicking the Tidy button(Alt+Y) in Visual Studio:

    ![image](https://user-images.githubusercontent.com/49960519/140455702-b7e2f2f9-6e50-4617-bc5b-6e6930b8e6b8.png)
1. Then you can view the lint that needs fixing in the warnings area below.
1. You can also make a quick fix by pressing the drop down beside the Tidy button or pressing Alt+X

## Testing
To run the testing checks for the application it is really simple, just run the application like normally but add `--test` or `-t` as an argument when running. Then it will run the Unit Testing feature of LENNAH making checks with each function and end with a E2E test.

```sh
$ C:\Users\User\LennahSSG\Debug\LennahSSG.exe --test
```