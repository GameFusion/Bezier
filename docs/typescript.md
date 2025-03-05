# Bezier Curve Library (TypeScript)

This library provides utilities to work with cubic Bezier curves. It includes functions to create coordinates, calculate points on a Bezier curve, subdivide the curve, and retrieve y-values at specific x-coordinates. The library is designed to be lightweight and efficient, making it suitable for various applications such as animations, graphics, and more.

## Features

- **Coordinate Management**: Functions to create, add, and multiply coordinates.
- **Bezier Basis Functions**: Functions to calculate the influence of each control point at a given parameter `t`.
- **Point Calculation on Bezier Curve**: Function to get a specific point on the Bezier curve using control points and a parameter `t`.
- **Subdivision for Precision**: Recursive subdivision to find a point on the curve at a given x-coordinate with high precision.
- **Y-Value Retrieval**: Function to retrieve the y-value of the curve at a specific x-coordinate.

## Key Functions

### Coordinate Management

#### `coord(x?: number, y?: number): Coord`
Creates a coordinate object with given `x` and `y` values. If no arguments are provided, defaults to `(0, 0)`.

- **Parameters**:
  - `x` (number, optional): The x-coordinate.
  - `y` (number, optional): The y-coordinate.
- **Returns**:
  - `{Coord}`: A coordinate object.

#### `addCoords(a: Coord, b: Coord): Coord`
Adds two coordinates together.

- **Parameters**:
  - `a` (`Coord`): The first coordinate.
  - `b` (`Coord`): The second coordinate.
- **Returns**:
  - `{Coord}`: A new coordinate representing the sum of `a` and `b`.

#### `multiplyCoordScalar(c: Coord, s: number): Coord`
Multiplies a coordinate by a scalar value.

- **Parameters**:
  - `c` (`Coord`): The coordinate to multiply.
  - `s` (number): The scalar value.
- **Returns**:
  - `{Coord}`: A new coordinate representing the multiplication of `c` by `s`.

### Bezier Basis Functions

These functions are used internally and are not exported. They calculate the influence of each control point at a given parameter `t`.

- `B1(t: number): number`: Bezier basis function for the first control point.
- `B2(t: number): number`: Bezier basis function for the second control point.
- `B3(t: number): number`: Bezier basis function for the third control point.
- `B4(t: number): number`: Bezier basis function for the fourth control point.

### Point Calculation on Bezier Curve

#### `getBezier(percent: number, C1: Coord, C2: Coord, C3: Coord, C4: Coord): Coord`
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

#### `subdivide(x: number, p1: Coord, p2: Coord, p3: Coord, p4: Coord, level: number): number`
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

#### `getValue(x: number, curve: Coord[]): number`
Retrieves the y-value of a Bezier curve at a specific x-coordinate by subdividing each segment of the curve.

- **Parameters**:
  - `x` (number): The x-coordinate to intersect with.
  - `curve` (`Coord[]`): An array of control points defining the Bezier curve.
- **Returns**:
  - (number): The y-coordinate of the point on the curve at x. Returns `0.0` if the curve is not defined or if no segment contains the x-coordinate.

## Examples

### Example 1: Calculating a Point on a Bezier Curve

```typescript
// Define control points
const C1 = coord(0, 0);
const C2 = coord(1, 3);
const C3 = coord(4, 5);
const C4 = coord(5, 7);

// Calculate a point on the Bezier curve at t = 0.5
const point = getBezier(0.5, C1, C2, C3, C4);
console.log(point); // Output: {x: 2.625, y: 3.8125}
```

### Example 2: Retrieving a Y-Value at a Specific X-Coordinate

```typescript
// Define control points
const curve = [
    coord(0, 0),
    coord(1, 3),
    coord(4, 5),
    coord(5, 7)
];

// Retrieve the y-value at x = 2.5
const yValue = getValue(2.5, curve);
console.log(yValue); // Output: 3.6875
```

### Example 3: Handling an Undefined Curve

```typescript
// Define an empty curve
const emptyCurve: Coord[] = [];

// Retrieve the y-value at x = 1
const yValue = getValue(1, emptyCurve);
console.log(yValue); // Output: 0.0
```

