# WinProMo

WinProMo is an MFC extension DLL to support diagram modeling.

To this aim, WinProMo represents a diagram as a hierarchical graph, allowing to represent both connected and nested blocks.

By doing so, WinProMo can:

* Keep the structure of the diagram (model) separate from its visual representation (view).

* Keep edges connected to blocks when blocks are moved or resized.

* Move nested elements when the parent block is moved or resized.

In addition, WinProMo can:

* Support drag-and-drop operations to (dis)connect edges to blocks and to (un)nest elements.

* Automatically resize blocks to fit child elements.

* Automatically resize blocks to fit text labels.

* Represent nested blocks either as internal to the parent block, or as attached to the boundary of the parent block.

* Define hierarchical custom properties for each model element.

* Define custom labels for each block or edge element, as well as their default position with respect to the element.

* Customize the visual appearance of blocks, edges, and labels.

* Break edges into multiple segments, each controllable by the user.

* Render the diagram either as raster (Windows Bitmap) or vector (Windows Metafile) graphics.

* Be extended to quickly build plugins for WinProMo-Editor: https://github.com/meronig/WinProMo-Editor

To see what WinProMo can do, please check out the following plugins:

* A demo plugin showcasing WinProMo capabilities: https://github.com/meronig/WinProMo-DemoPlugin

* A simple Petri Net editor plugin: https://github.com/meronig/WinProMo-PNPlugin

# Compiling

To compile WinProMo, you will need Microsoft (R) Visual C++, the Microsoft Foundation Classes library, and Microsoft Windows SDK. The freely available Community version of Visual Studio can satisfy these dependencies.

A Microsoft Visual C++ 2022 project file (WinProMo.vcxproj) is included in this repository. For older versions of Microsoft Visual C++, you will have to create your own project file. WinProMo can be compiled with Microsoft Visual C++ 4.0 onwards (really!). Depending on the version of Microsoft Visual C++ being used, the resulting DLL can run under Microsoft Windows 95/NT 3.51 up to Windows 11, on any supported target architecture. However, WinProMo has been extensively tested only under Microsoft Windows 10/11 x64.

# Acknowledgements

Copyright © 2025 Technical University of Denmark

This computer program makes use of the CDiagramEditor public domain souce code by Johan Rosengren, Abstrakt Mekanik AB: http://www.abstraktmekanik.se/freebies.html https://www.codeproject.com/articles/CDiagramEditor-DIY-vector-and-dialog-editor

Microsoft Visual Studio, Microsoft Visual C++, Microsoft Foundation Classes (MFC) and Microsoft Windows are trademarks of the Microsoft group of companies.