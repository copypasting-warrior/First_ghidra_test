# First_ghidra_test
Testing reverse engineering with Ghidra on a simple c program that checks if a variable is a certain value and prints access granted or denied based on it

the program: A simple c file that creates an integer variable called code with value 1234 and then passes it through a function checkc that returns 0 or 1 based on the result. we then print "Access Granted" or "Access Denied" based on the output of checkc being true or false

to build:
open a command prompt console and type
//
gcc -O0 -g hello.c -o hello.exe
//
-O0 flag is used to specify ggc to not optimize output
-g flag is used to specify gcc to leave debugging info 

We download and run ghidra_12.2_PUBLIC for windows. Can be downloaded from https://github.com/NationalSecurityAgency/ghidra

After downloading we run the ghidraRun.bat file in the folder to open Ghidra.

After Ghidra launches we create a project by selecting new project in the File toolbar.
- Select Non-Shared project
- Select next.
- Specify project directory location ie where you want it to be store
- Enter project name. I chose "Analyzing the hello.c file again".
- Click finish.
After this you should see a menu like this:

<img width="1180" height="886" alt="image" src="https://github.com/user-attachments/assets/a0662016-709f-4f7e-9e56-2fa88e50e03f" />


We want to drag the built exe into this window and you will be shown this menu:

<img width="750" height="369" alt="image" src="https://github.com/user-attachments/assets/4bd14990-036a-466d-835f-3ab85504f497" />

Click Ok to continue.

You will be shown a summary of the files metadata:

<img width="1201" height="1282" alt="image" src="https://github.com/user-attachments/assets/490a5df4-a466-4d01-b2b3-d4ab23c0d85a" />

Double click the file which is now shown under your project to open it via CodeBrowser and click yes when asked to analyze.

<img width="646" height="213" alt="image" src="https://github.com/user-attachments/assets/58592c1c-1ab3-454b-9cb1-112a5670fa3e" />

When prompted with this menu use the default selection and click Analyze

<img width="1470" height="871" alt="image" src="https://github.com/user-attachments/assets/7b0f88eb-f645-4e9e-9115-012f33fdcfcf" />

After this you will be brought to the CodeBrowser and shown the de-compiled C code on the right panel and X86 code in the center panel:

<img width="2556" height="1530" alt="image" src="https://github.com/user-attachments/assets/8a693a5d-b9eb-4aca-9993-9758325d3147" />

We can see the de-compiled program has the following:
-3 decompiled variables that are :
iVar1:"result of checkc"
in_stack_ffffffffffffffc8:"A a value Ghidra believes is located at a stack-relative address."
int code: A variable Ghidra found but did not use in the pseudo code.

<img width="637" height="108" alt="image" src="https://github.com/user-attachments/assets/d9469650-601f-4ea4-8f75-2d7481f8c356" />

-A main funciton that checks if the value of var1 is 0 or not and if it is 0 it prints "Access Denied" or else it prints "Access Granted"

<img width="489" height="291" alt="image" src="https://github.com/user-attachments/assets/a34aaaed-0b6e-4397-b47f-13279575f2d5" />

This is very close to our original logic that checks if the output of checkc for the input code is 1 for which it prints "Access Granted" and if it's not it prints "Access Denied".

We can further explore the program by double clicking the "checkc" function highlighted in pink to find the respective X86 and decompiled C function.

<img width="2191" height="1068" alt="image" src="https://github.com/user-attachments/assets/203c3c09-809a-4d51-8780-488d3b7fe8ac" />

Here we see the function uses the previous variable code as input and then creates an integer variable called in_ECX which ghidra thought is check to get the output.

<img width="486" height="325" alt="image" src="https://github.com/user-attachments/assets/a905f833-0d6d-45a3-b866-ae118fc93b58" />

We also observe that the returned variable is the result of the equation in_ECX == 0x4d2 . We can convert 0x4d2 from hexadecimal to decimal to see that it equals our original check of the value 1234.

<img width="747" height="660" alt="image" src="https://github.com/user-attachments/assets/af67a901-1c13-431a-bb5c-e87c19ffced2" />

Website to convert hexadecimal  to Decimal: https://www.rapidtables.com/convert/number/hex-to-decimal.html?x=4D2


We can select the option "Display function graph" from the tool bar to see a visual representation of the de-compiled program.
<img width="742" height="127" alt="image" src="https://github.com/user-attachments/assets/b2068fab-87e4-4eb9-a4ea-08366e18c239" />

The result obtained is:
<img width="1485" height="1435" alt="image" src="https://github.com/user-attachments/assets/0bc86e52-d542-4a36-9a75-5f7cb359354d" />

Result:This helps give us a basic understanding on how to perform static analysis of a simple c program executable with Ghidra
