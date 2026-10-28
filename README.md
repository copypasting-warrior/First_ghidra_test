
# First_Ghidra_Test

Testing reverse engineering with Ghidra on a simple C program that checks if a variable is a certain value and prints access granted or denied based on it.

## The Program

A simple C file that creates an integer variable called `code` with value `1234` and then passes it through a function `checkc` that returns `0` or `1` based on the result. We then print `"Access Granted"` or `"Access Denied"` based on the output of `checkc` being true or false.

## Building the Program

To build:

Open a command prompt console and type:

```bash
gcc -O0 -g hello.c -o hello.exe
```

- `-O0` flag is used to specify GCC to not optimize output.
- `-g` flag is used to specify GCC to leave debugging info.

## Opening Ghidra

We download and run `ghidra_12.2_PUBLIC` for Windows. It can be downloaded from [Ghidra on GitHub](https://github.com/NationalSecurityAgency/ghidra).

After downloading, we run the `ghidraRun.bat` file in the folder to open Ghidra.

## Creating a Project

After Ghidra launches, we create a project by selecting **New Project** in the File toolbar.

1. Select **Non-Shared Project**.
2. Select **Next**.
3. Specify project directory location, i.e., where you want it to be stored.
4. Enter project name. I chose `"Analyzing the hello.c file again"`.
5. Click **Finish**.

After this, you should see a menu like this:

<img width="1180" height="886" alt="image" src="https://github.com/user-attachments/assets/a0662016-709f-4f7e-9e56-2fa88e50e03f" />

## Importing the Executable

We want to drag the built EXE into this window, and you will be shown this menu:

<img width="750" height="369" alt="image" src="https://github.com/user-attachments/assets/4bd14990-036a-466d-835f-3ab85504f497" />

Click **OK** to continue.

You will be shown a summary of the file's metadata:

<img width="1201" height="1282" alt="image" src="https://github.com/user-attachments/assets/490a5df4-a466-4d01-b2b3-d4ab23c0d85a" />

## Opening the Executable in CodeBrowser

Double-click the file which is now shown under your project to open it via CodeBrowser and click **Yes** when asked to analyze.

<img width="646" height="213" alt="image" src="https://github.com/user-attachments/assets/58592c1c-1ab3-454b-9cb1-112a5670fa3e" />

When prompted with this menu, use the default selection and click **Analyze**.

<img width="1470" height="871" alt="image" src="https://github.com/user-attachments/assets/7b0f88eb-f645-4e9e-9115-012f33fdcfcf" />

After this, you will be brought to the CodeBrowser and shown the de-compiled C code on the right panel and X86 code in the center panel:

<img width="2556" height="1530" alt="image" src="https://github.com/user-attachments/assets/8a693a5d-b9eb-4aca-9993-9758325d3147" />

## Analyzing the Decompiled Code

We can see the de-compiled program has the following:

### 1. Decompiled Variables

Three decompiled variables:

- `iVar1`: "result of checkc"
- `in_stack_ffffffffffffffc8`: "A value Ghidra believes is located at a stack-relative address."
- `int code`: A variable Ghidra found but did not use in the pseudo code.

<img width="637" height="108" alt="image" src="https://github.com/user-attachments/assets/d9469650-601f-4ea4-8f75-2d7481f8c356" />

### 2. The Main Function

A main function that checks if the value of `var1` is `0` or not, and if it is `0` it prints `"Access Denied"` or else it prints `"Access Granted"`.

<img width="489" height="291" alt="image" src="https://github.com/user-attachments/assets/a34aaaed-0b6e-4397-b47f-13279575f2d5" />

This is very close to our original logic that checks if the output of `checkc` for the input `code` is `1`, for which it prints `"Access Granted"`, and if it's not, it prints `"Access Denied"`.

## Analyzing the `checkc` Function

We can further explore the program by double-clicking the `checkc` function highlighted in pink to find the respective X86 and decompiled C function.

<img width="2191" height="1068" alt="image" src="https://github.com/user-attachments/assets/203c3c09-809a-4d51-8780-488d3b7fe8ac" />

Here we see the function uses the previous variable `code` as input and then creates an integer variable called `in_ECX`, which Ghidra thought is check to get the output.

<img width="486" height="325" alt="image" src="https://github.com/user-attachments/assets/a905f833-0d6d-45a3-b866-ae118fc93b58" />

We also observe that the returned variable is the result of the equation:

```c
in_ECX == 0x4d2
```

We can convert `0x4d2` from hexadecimal to decimal to see that it equals our original check of the value `1234`.

<img width="747" height="660" alt="image" src="https://github.com/user-attachments/assets/af67a901-1c13-431a-bb5c-e87c19ffced2" />

**Website to convert hexadecimal to decimal:** [RapidTables — Hex to Decimal Converter](https://www.rapidtables.com/convert/number/hex-to-decimal.html?x=4D2)

## Visualizing the Program with a Function Graph

We can select the option **Display Function Graph** from the toolbar to see a visual representation of the de-compiled program.

<img width="742" height="127" alt="image" src="https://github.com/user-attachments/assets/b2068fab-87e4-4eb9-a4ea-08366e18c239" />

The result obtained is:

<img width="1485" height="1435" alt="image" src="https://github.com/user-attachments/assets/0bc86e52-d542-4a36-9a75-5f7cb359354d" />

## Result

This helps give us a basic understanding on how to perform static analysis of a simple C program executable with Ghidra.
