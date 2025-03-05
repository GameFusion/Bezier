// frontend/src/bezier.ts

/**
 * Interface representing a coordinate point with x and y properties.
 *
 * @typedef {Object} Coord
 * @property {number} x - The x-coordinate of the point.
 * @property {number} y - The y-coordinate of the point.
 */
export interface Coord {
    x: number;
    y: number;
}

/**
 * Function to create a coordinate object. If no values are provided, defaults to (0, 0).
 *
 * @param {number} [x=0] - The x-coordinate of the point.
 * @param {number} [y=0] - The y-coordinate of the point.
 * @returns {Coord} A new Coord object with the specified or default coordinates.
 *
 * @example
 * const point = coord(10, 20);
 * console.log(point); // { x: 10, y: 20 }
 */
function coord(x?: number, y?: number): Coord {
    if (!x) x = 0;
    if (!y) y = 0;
    return { x, y };
}

/**
 * Function to add two coordinates.
 *
 * @param {Coord} a - The first coordinate point.
 * @param {Coord} b - The second coordinate point.
 * @returns {Coord} A new Coord object representing the sum of the two input coordinates.
 *
 * @example
 * const point1 = coord(10, 20);
 * const point2 = coord(30, 40);
 * const result = addCoords(point1, point2);
 * console.log(result); // { x: 40, y: 60 }
 */
function addCoords(a: Coord, b: Coord): Coord {
    return coord(a.x + b.x, a.y + b.y);
}

/**
 * Function to multiply a coordinate by a scalar.
 *
 * @param {Coord} c - The coordinate point to be multiplied.
 * @param {number} s - The scalar value to multiply the coordinate by.
 * @returns {Coord} A new Coord object representing the product of the input coordinate and scalar.
 *
 * @example
 * const point = coord(10, 20);
 * const result = multiplyCoordScalar(point, 3);
 * console.log(result); // { x: 30, y: 60 }
 */
function multiplyCoordScalar(c: Coord, s: number): Coord {
    return coord(c.x * s, c.y * s);
}

//////////////////////////////////////////
// Bezier basis functions
//////////////////////////////////////////

/**
 * Bezier basis function for t^3.
 *
 * @param {number} t - The parameter value between 0 and 1.
 * @returns {number} The result of the B4 basis function.
 */
const B4 = (t: number): number => t * t * t;

/**
 * Bezier basis function for 3*t^2*(1-t).
 *
 * @param {number} t - The parameter value between 0 and 1.
 * @returns {number} The result of the B3 basis function.
 */
const B3 = (t: number): number => 3 * t * t * (1 - t);

/**
 * Bezier basis function for 3*t*(1-t)^2.
 *
 * @param {number} t - The parameter value between 0 and 1.
 * @returns {number} The result of the B2 basis function.
 */
const B2 = (t: number): number => 3 * t * (1 - t) * (1 - t);

/**
 * Bezier basis function for (1-t)^3.
 *
 * @param {number} t - The parameter value between 0 and 1.
 * @returns {number} The result of the B1 basis function.
 */
const B1 = (t: number): number => (1 - t) * (1 - t) * (1 - t);

/**
 * Function to get a point on the Bezier curve at a specified percentage.
 *
 * @param {number} percent - The parameter value between 0 and 1 specifying the position on the curve.
 * @param {Coord} C1 - The first control point of the Bezier curve.
 * @param {Coord} C2 - The second control point of the Bezier curve.
 * @param {Coord} C3 - The third control point of the Bezier curve.
 * @param {Coord} C4 - The fourth control point of the Bezier curve.
 * @returns {Coord} A new Coord object representing the point on the Bezier curve at the specified percentage.
 *
 * @example
 * const point = getBezier(0.5, coord(0, 0), coord(1, 1), coord(2, 2), coord(3, 3));
 * console.log(point); // { x: 1.5, y: 1.5 }
 */
function getBezier(percent: number, C1: Coord, C2: Coord, C3: Coord, C4: Coord): Coord {
    const pos = coord();
    pos.x = C1.x * B1(percent) + C2.x * B2(percent) + C3.x * B3(percent) + C4.x * B4(percent);
    pos.y = C1.y * B1(percent) + C2.y * B2(percent) + C3.y * B3(percent) + C4.y * B4(percent);
    return pos;
}

/**
 * Constants for subdivision of the Bezier curve.
 *
 * @constant {number} maxLevel - The maximum recursion level to prevent infinite loops.
 * @constant {number} precision - The precision threshold for subdividing the curve.
 */
const maxLevel = 250;
const precision = 0.001;

/**
 * Function to subdivide the Bezier curve at a specific point.
 *
 * @param {number} x - The x-coordinate value to subdivide the curve at.
 * @param {Coord} p1 - The first control point of the Bezier segment.
 * @param {Coord} p2 - The second control point of the Bezier segment.
 * @param {Coord} p3 - The third control point of the Bezier segment.
 * @param {Coord} p4 - The fourth control point of the Bezier segment.
 * @param {number} level - The current recursion level to prevent exceeding maxLevel.
 * @returns {number} The y-coordinate value at the specified x after subdivision.
 *
 * @example
 * const y = subdivide(0.5, coord(0, 0), coord(1, 1), coord(2, 2), coord(3, 3), 0);
 * console.log(y); // Some calculated y-coordinate value
 */
function subdivide(x: number, p1: Coord, p2: Coord, p3: Coord, p4: Coord, level: number): number {
    const p12 = multiplyCoordScalar(addCoords(p1, p2), 0.5);
    const p23 = multiplyCoordScalar(addCoords(p2, p3), 0.5);
    const p34 = multiplyCoordScalar(addCoords(p3, p4), 0.5);

    const p234 = multiplyCoordScalar(addCoords(p23, p34), 0.5);
    const p123 = multiplyCoordScalar(addCoords(p12, p23), 0.5);

    const p1234 = multiplyCoordScalar(addCoords(p123, p234), 0.5);

    level++;

    if (level > maxLevel) {
        return p1234.y;
    }

    const p1DiffX = Math.abs(p1.x - x);
    if (p1DiffX < precision) {
        return p1.y;
    }

    const p4DiffX = Math.abs(p4.x - x);
    if (p4DiffX < precision) {
        return p4.y;
    }

    if (x > p1234.x) {
        return subdivide(x, p1234, p234, p34, p4, level);
    } else {
        return subdivide(x, p1, p12, p123, p1234, level);
    }
}

/**
 * Function to get the value at a specific x on the Bezier curve.
 *
 * @param {number} x - The x-coordinate value to evaluate on the curve.
 * @param {Coord[]} curve - An array of Coord objects representing the control points of the Bezier curve.
 * @returns {number} The y-coordinate value at the specified x on the Bezier curve, or 0.0 if the curve is not defined.
 *
 * @example
 * const curve = [coord(0, 0), coord(1, 1), coord(2, 2), coord(3, 3)];
 * const y = getValue(0.5, curve);
 * console.log(y); // Some calculated y-coordinate value
 */
function getValue(x: number, curve: Coord[]): number {
    if (!curve || curve.length === 0) {
        return 0.0;
    }

    for (let i = 0; i + 3 < curve.length; i += 4) { // Ensure safe access to i, i+1, i+2, i+3
        const p0 = curve[i];
        const p1 = curve[i + 1];
        const p2 = curve[i + 2];
        const p3 = curve[i + 3];

        if (!p0 || !p1 || !p2 || !p3) continue; // Ensure all points exist

        if (x < p0.x) {
            return p0.y;
        }
        if (x > p3.x) {
            continue;
        }
        return subdivide(x, p0, p1, p2, p3, 0);
    }

    return curve[curve.length - 1]?.y ?? 0.0; // Safe fallback for the last value
}

/**
 * Exports utility functions for working with Bezier curves.
 *
 * @exports {Object}
 * @property {Function} coord - Function to create a coordinate object.
 * @property {Function} addCoords - Function to add two coordinates.
 * @property {Function} multiplyCoordScalar - Function to multiply a coordinate by a scalar.
 * @property {Function} getBezier - Function to get a point on the Bezier curve at a specified percentage.
 * @property {Function} subdivide - Function to subdivide the Bezier curve at a specific point.
 * @property {Function} getValue - Function to get the value at a specific x on the Bezier curve.
 */
export { coord, addCoords, multiplyCoordScalar, getBezier, subdivide, getValue };
