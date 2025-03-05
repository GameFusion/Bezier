# Bezier Curve Library

An ultra-lightweight Bezier curve library for multiple programming languages, enabling precise curve evaluations and manipulations.

Welcome to the **Bezier Curve Library**, an efficient ultra-lightweight library designed to provide accurate Bezier curve evaluations and manipulations for various programming languages, including **C++**, **C#**, **JavaScript**, and **TypeScript**. 

This library is focused exclusively on **Bezier math** and has been used extensively for **3D animation**, **game development**, and **websites** over the past 20 years. With features such as **point evaluation on curves**, **curve intersection calculations**, and the ability to **manipulate curves using handles**, this library is a trusted tool for professionals in animation, gaming, and software development.

## Key Features:
- **Point Evaluation**: Evaluate specific points on a Bezier curve.
- **Curve Intersection**: Calculate intersections between Bezier curves.
- **Handle Manipulation**: Use Bezier handles for intuitive curve editing.
- **Multi-Language Support**: Available for C++, C#, JavaScript, and TypeScript.
- **Efficient**: Optimized for performance with minimal footprint.
- **20+ Years of Use**: Proven and trusted in production systems for two decades.

## Installation

To install and use the Bezier Curve Library in your project, follow the instructions based on the language you're working with.

### For C++:
1. Download the library or clone the repository.
2. Include the Bezier header files in your project.
3. Link the library with your C++ project.

### For C#:
1. Add a reference to the Bezier namespace in your C# project.

### For JavaScript / TypeScript:
1. Import the library into your JavaScript/TypeScript code:
   ```javascript
   import Bezier from 'bezier-library';
   ```

## Usage Example

```cpp
// Example in C++
BezierCurve curve({Point(0, 0), Point(1, 2), Point(3, 5)});
auto point = curve.evaluate(0.5);  // Evaluate point at t=0.5
```

```csharp
// Example in C#
BezierCurve curve = new BezierCurve(new Point[] { new Point(0, 0), new Point(1, 2), new Point(3, 5) });
var point = curve.Evaluate(0.5);  // Evaluate point at t=0.5
```

```javascript
// Example in JavaScript
const curve = new Bezier([new Point(0, 0), new Point(1, 2), new Point(3, 5)]);
let point = curve.evaluate(0.5);  // Evaluate point at t=0.5
```

## Documentation

- [JavaScript Bezier Library](docs/javascript.md)

## License

This project is licensed under the **MIT License**. See the [LICENSE](LICENSE) file for details.

---

### **Directory Structure for the Project**

```
/bezier-library
│
├── /cpp                          # C++ implementation
│   ├── BezierPath.cpp            # BezierPath implementation in C++
│   ├── BezierPath.h              # Header for BezierPath in C++
│   ├── BezierHandle.cpp          # BezierHandle implementation in C++
│   ├── BezierHandle.h            # Header for BezierHandle in C++
│   ├── Math3D.cpp                # Math3D related functions for C++
│   ├── Math3D.h                  # Header for Math3D
│   ├── Vector3D.cpp              # Vector3D implementation in C++
│   ├── Vector3D.h                # Header for Vector3D
│   ├── List.cpp                  # List container implementation in C++
│   ├── List.h                    # Header for List container
│   ├── Array.cpp                 # Array container implementation in C++
│   └── Array.h                   # Header for Array container
│
├── /csharp                       # C# implementation
│   ├── Bezier.cs                 # BezierCurve class in C#
│   ├── BezierPath.cs             # BezierPath in C#
│   ├── BezierHandle.cs           # BezierHandle in C#
│   ├── Math3D.cs                 # Math3D related functions in C#
│   ├── Vector3D.cs               # Vector3D class in C#
│   ├── List.cs                   # List container in C#
│   └── Array.cs                  # Array container in C#
│
├── /typescript                   # TypeScript implementation
│   └── Bezier.ts                 # Bezier curve class in TypeScript
│
├── /javascript                   # JavaScript implementation
│   └── Bezier.js                 # Bezier curve class in JavaScript
│
├── /tests                        # Unit tests for the library
│   ├── test_bezier_curve.cpp     # C++ test cases
│   ├── test_bezier_curve.cs      # C# test cases
│   ├── test_bezier_curve.js      # JavaScript test cases
│   └── test_bezier_curve.ts      # TypeScript test cases
│
├── /docs                         # Documentation
│   ├── usage.md                  # Usage examples for different languages
│   └── javascript.md             # Javascript documentation details
│
├── /examples                     # Example usage code
│   ├── example_cpp.cpp           # Example usage in C++
│   ├── example_csharp.cs         # Example usage in C#
│   ├── example_js.js             # Example usage in JavaScript
│   └── example_ts.ts             # Example usage in TypeScript
│
├── LICENSE                       # MIT License file
├── README.md                     # Project README file
└── /build                        # Build and configuration files
```
