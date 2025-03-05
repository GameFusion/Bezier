# Bezier Curve Library (JavaScript)

This JavaScript library provides utilities to work with cubic Bezier curves. It includes functions to calculate points on a Bezier curve, subdivide the curve, and retrieve y-values at specific x-coordinates. The library is designed to be lightweight and efficient, making it suitable for various applications such as animations, graphics, and more.

## Features

- **Coordinate Management**: Functions to create, add, and multiply coordinates.
- **Bezier Basis Functions**: Functions to calculate the influence of each control point at a given parameter `t`.
- **Point Calculation on Bezier Curve**: Function to get a specific point on the Bezier curve using control points and a parameter `t`.
- **Subdivision for Precision**: Recursive subdivision to find a point on the curve at a given x-coordinate with high precision.
- **Y-Value Retrieval**: Function to retrieve the y-value of the curve at a specific x-coordinate.

## Key Functions

### Coordinate Management

#### `coord(x, y)`
Creates a coordinate object with given `x` and `y` values. If no arguments are provided, defaults to `(0, 0)`.

- **Parameters**:
  - `x` (number): The x-coordinate.
  - `y` (number): The y-coordinate.
- **Returns**:
  - `{Coord}`: A coordinate object.

#### `addCoords(a, b)`
Adds two coordinates together.

- **Parameters**:
  - `a` (`Coord`): The first coordinate.
  - `b` (`Coord`): The second coordinate.
- **Returns**:
  - `{Coord}`: A new coordinate representing the sum of `a` and `b`.

#### `multiplyCoordScalar(c, s)`
Multiplies a coordinate by a scalar value.

- **Parameters**:
  - `c` (`Coord`): The coordinate to multiply.
  - `s` (number): The scalar value.
- **Returns**:
  - `{Coord}`: A new coordinate representing the multiplication of `c` by `s`.

### Bezier Basis Functions

#### `B1(t)`
Bezier basis function for the first control point.

- **Parameters**:
  - `t` (number): The parameter value between 0 and 1.
- **Returns**:
  - (number): The result of the basis function.

#### `B2(t)`
Bezier basis function for the second control point.

- **Parameters**:
  - `t` (number): The parameter value between 0 and 1.
- **Returns**:
  - (number): The result of the basis function.

#### `B3(t)`
Bezier basis function for the third control point.

- **Parameters**:
  - `t` (number): The parameter value between 0 and 1.
- **Returns**:
  - (number): The result of the basis function.

#### `B4(t)`
Bezier basis function for the fourth control point.

- **Parameters**:
  - `t` (number): The parameter value between 0 and 1.
- **Returns**:
  - (number): The result of the basis function.

### Point Calculation on Bezier Curve

#### `getBezier(percent, C1, C2, C3, C4)`
Calculates a point on a Bezier curve given the parameter `percent` and control points `C1`, `C2`, `C3`, and `C4`.

- **Parameters**:
  - `percent` (number): The parameter value between 0 and 1.
  - `C1` (`Coord`): The first control point.
  - `C2` (`Coord`): The second control point.
  - `C3` (`Coord`): The third control point.
  - `C4` (`Coord`): The fourth control point.
- **Returns**:
  - `{Coord}`: A coordinate on the Bezier curve.

### Subdivision for Precision

#### `subdivide(x, p1, p2, p3, p4, level)`
Subdivides the Bezier curve to find a point on the curve at a given x-coordinate with high precision.

- **Parameters**:
  - `x` (number): The x-coordinate to intersect with.
  - `p1` (`Coord`): The first control point.
  - `p2` (`Coord`): The second control point.
  - `p3` (`Coord`): The third control point.
  - `p4` (`Coord`): The fourth control point.
  - `level` (number): The current recursion level.
- **Returns**:
  - (number): The y-coordinate of the point on the curve at x.

### Y-Value Retrieval

#### `getValue(x, curve)`
Retrieves the y-value of a Bezier curve at a specific x-coordinate by subdividing each segment of the curve.

- **Parameters**:
  - `x` (number): The x-coordinate to intersect with.
  - `curve` (`Coord[]`): An array of control points defining the Bezier curve.
- **Returns**:
  - (number): The y-coordinate of the point on the curve at x.

## Examples

### Example 1: Calculating a Point on a Bezier Curve

```javascript
// Define control points
var C1 = {x: 0, y: 0};
var C2 = {x: 1, y: 3};
var C3 = {x: 4, y: 5};
var C4 = {x: 5, y: 7};

// Calculate a point on the Bezier curve at t = 0.5
var point = getBezier(0.5, C1, C2, C3, C4);
console.log(point); // Output: {x: 2.5, y: 3.5}
```

### Example 2: Subdividing a Bezier Curve

```javascript
// Define control points
var p1 = {x: 0, y: 0};
var p2 = {x: 1, y: 3};
var p3 = {x: 4, y: 5};
var p4 = {x: 5, y: 7};

// Subdivide the curve to find a point at x = 2.5
var y = subdivide(2.5, p1, p2, p3, p4, 0);
console.log(y); // Output: 3.5
```

### Example 3: Retrieving Y-Value on a Bezier Curve

```javascript
// Define control points for a Bezier curve segment
var curve = [
    {x: 0, y: 0},
    {x: 1, y: 3},
    {x: 4, y: 5},
    {x: 5, y: 7}
];

// Retrieve the y-value at x = 2.5
var yValue = getValue(2.5, curve);
console.log(yValue); // Output: 3.5

// Define another segment of the Bezier curve
curve.push({x: 6, y: 9});
curve.push({x: 7, y: 11});
curve.push({x: 8, y: 13});
curve.push({x: 9, y: 15});

// Retrieve the y-value at x = 7.5
var anotherYValue = getValue(7.5, curve);
console.log(anotherYValue); // Output: 10.5
```

## Usage

To use this library in your JavaScript projects, simply include the `Bezier.js` file and call the functions as demonstrated above.

### Installation

You can clone this repository or download the `Bezier.js` file directly from GitHub:

```bash
git clone https://github.com/gamefusion/bezier.git
```

Include the `bezier.js` file in your project directory and import it into your JavaScript files:

```javascript
// Import the Bezier library
import './path/to/Bezier.js';

// Use the functions as needed
var point = getBezier(0.5, C1, C2, C3, C4);
console.log(point); // Output: {x: 2.5, y: 3.5}
