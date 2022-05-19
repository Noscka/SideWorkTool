[![Workflow CodeQL Scan](https://github.com/Ruski1/SWT--Side-Working-Tool/actions/workflows/main.yml/badge.svg?branch=main)](https://github.com/Ruski1/SWT--Side-Working-Tool/actions/workflows/main.yml)
# SWT
Ever wanted to double the value lenght of a box but you had to go to google and type in the equation? well SWT (Side Working Tool) is made just for this and (in the future) many more small but annoying problems while working. it is a simple program made to assist when working on projects. While it was aimed at programming projects, it can be used with anything else that has writable text.

The program uses many clever (at least in my eyes) tricks such as [dynamic array size function](https://github.com/Ruski1/Dynamic-Array-size-Function-Test), [two dimensional dynamic size array](https://github.com/Ruski1/Two-Dimensional-Char-Pointer-Dynamic-Size-Array), [Low Level keyboard hook](https://github.com/Ruski1/LowLevelKeyboardhook-Tutorial), Hot keys and more!

## Features
 - ### Value Calculations
      THIS MODE WILL BLOCK `0-9`, `+`, `-`, `*`, `/`, `=`, `.`, `{backspace}`, `{enter}` WHEN ENABLED FROM ENTERING INTO NORMAL PROGRAMS
    
    Currently this is the only feature which allows for easy calculations for values (such as form lenght and width or array size). To enable this "mode" you need to press `ctrl` + `alt` + `shift` + `k`.
    
    To use it enter a equation (Example, 1024*4) and hit `{enter}` or `=` for the output to write where the cursor is. The follow inputs are currently working: `0-9`, `+`, `-`, `*`, `/`, `=`, `.`, `{backspace}`, `{enter}`. once you hit `{enter}` program will exit out of the mode so you will be able to write normally again.

- ### Auto Select (Needs better Name)
  THIS MODE WILL BLOCK `0-9`, `{backspace}`, `{enter}` WHEN ENABLED FROM ENTERING INTO NORMAL PROGRAMS
  
  The feature will make the cursor/caret (the magical blinking thing from which text appears) go specified amount of times in the direction selected. to run the feature, press `ctrl` + `alt` + `shift` + `L`.
