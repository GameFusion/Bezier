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

## License

This project is licensed under the **MIT License**. See the [LICENSE](LICENSE) file for details.

---

### **Directory Structure for the Project**

```
/bezier-library
│
├── /src                          # Core library source code
│   ├── bezier_curve.cpp          # C++ implementation for Bezier curve calculations
│   ├── bezier_curve.h            # Header file for C++ implementation
│   ├── bezier_curve.cs           # C# implementation for Bezier curve calculations
│   ├── bezier_curve.js           # JavaScript implementation for Bezier curve calculations
│   └── bezier_curve.ts           # TypeScript implementation for Bezier curve calculations
│
├── /tests                        # Unit tests for the library
│   ├── test_bezier_curve.cpp     # C++ test cases
│   ├── test_bezier_curve.cs      # C# test cases
│   ├── test_bezier_curve.js      # JavaScript test cases
│   └── test_bezier_curve.ts      # TypeScript test cases
│
├── /docs                         # Documentation
│   ├── installation.md           # Installation guide
│   ├── usage.md                  # Usage examples for different languages
│   └── contributing.md           # Contribution guidelines
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

This structure separates the code for each language and includes tests, documentation, and examples, making it easy to navigate and contribute to the project.

Let me know if you'd like further adjustments or additions!
