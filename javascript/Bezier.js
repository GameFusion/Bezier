
/**
 * @typedef {Object} Coord
 * @property {number} x - The x-coordinate.
 * @property {number} y - The y-coordinate.
 */

/**
 * Creates a coordinate object with given x and y values.
 * If no arguments are provided, defaults to (0, 0).
 *
 * @param {number} [x=0] - The x-coordinate.
 * @param {number} [y=0] - The y-coordinate.
 * @returns {Coord} A coordinate object.
 */
coord = function (x,y) { 
	if(!x) var x=0; if(!y) var y=0; 
	return {x: x, y: y}; 
};
	
/**
 * Adds two coordinates together.
 *
 * @param {Coord} a - The first coordinate.
 * @param {Coord} b - The second coordinate.
 * @returns {Coord} A new coordinate representing the sum of `a` and `b`.
 */
function addCoords ( a, b ) {

	return coord ( a.x + b.x, a.y + b.y );
}

/**
 * Multiplies a coordinate by a scalar value.
 *
 * @param {Coord} c - The coordinate to be multiplied.
 * @param {number} s - The scalar value.
 * @returns {Coord} A new coordinate representing the product of `c` and `s`.
 */
function multiplyCoordScalar ( c, s ) {
	return coord( c.x * s, c.y * s);

}

/**
 * Bezier basis function B4(t) = t^3.
 *
 * @param {number} t - The parameter value between 0 and 1.
 * @returns {number} The result of the basis function.
 */
B4 = function(t) { return (t*t*t); }

/**
 * Bezier basis function B3(t) = 3t^2(1-t).
 *
 * @param {number} t - The parameter value between 0 and 1.
 * @returns {number} The result of the basis function.
 */
B3 = function(t) { return (3*t*t*(1-t)); }

/**
 * Bezier basis function B2(t) = 3t(1-t)^2.
 *
 * @param {number} t - The parameter value between 0 and 1.
 * @returns {number} The result of the basis function.
 */
B2 = function(t) { return (3*t*(1-t)*(1-t)); }

/**
 * Bezier basis function B1(t) = (1-t)^3.
 *
 * @param {number} t - The parameter value between 0 and 1.
 * @returns {number} The result of the basis function.
 */
B1 = function(t) { return ((1-t)*(1-t)*(1-t)); }

/**
 * Calculates a point on a Bezier curve given the parameter `t` and control points `C1`, `C2`, `C3`, and `C4`.
 *
 * @param {number} percent - The parameter value between 0 and 1.
 * @param {Coord} C1 - The first control point.
 * @param {Coord} C2 - The second control point.
 * @param {Coord} C3 - The third control point.
 * @param {Coord} C4 - The fourth control point.
 * @returns {Coord} A coordinate on the Bezier curve.
 */
function getBezier(percent,C1,C2,C3,C4) {
	var pos = new coord(0, 0);
	pos.x = C1.x * B1(percent) + C2.x * B2(percent) +C3.x * B3(percent) + C4.x * B4(percent);
	pos.y = C1.y * B1(percent) + C2.y * B2(percent) + C3.y * B3(percent) + C4.y * B4(percent);
	return pos; 
}

/**
 * Maximum recursion level for subdivision.
 */
var maxLevel = 250;

/**
 * Precision threshold for subdivision.
 */
var precision = 0.001;

/**
 * Subdivides the Bezier curve to find a point on the curve at a given x-coordinate.
 *
 * @param {number} x - The x-coordinate to intersect with.
 * @param {Coord} p1 - The first control point.
 * @param {Coord} p2 - The second control point.
 * @param {Coord} p3 - The third control point.
 * @param {Coord} p4 - The fourth control point.
 * @param {number} level - The current recursion level.
 * @returns {number} The y-coordinate of the point on the curve at x.
 */
function subdivide(x, p1, p2, p3, p4, level)
{
	// Calculate midpoints
	p12 = multiplyCoordScalar( addCoords(p1, p2), 0.5);
	p23 = multiplyCoordScalar( addCoords(p2, p3), 0.5);
	p34 = multiplyCoordScalar( addCoords(p3, p4), 0.5);
	
	p234 = multiplyCoordScalar( addCoords(p23, p34), 0.5);
	p123 = multiplyCoordScalar( addCoords(p12, p23), 0.5);
	
	p1234 = multiplyCoordScalar( addCoords(p123, p234), 0.5);
	
	// Increment recursion level
	level ++;
	
	// Check if maximum recursion level is reached
	if(level > maxLevel)
		return p1234.y;

	// Calculate differences from x-coordinate
	p1DiffX = Math.abs( p1.x - x );
	
	// If point at p1 is within precision, return p1 y-coordinate
	if(p1DiffX < precision)
			return p1.y;
	
	// Calculate differences from x-coordinate
	p4DiffX = Math.abs( p4.x - x );
	
	// If point at p4 is within precision, return p4 y-coordinate
	if(p4DiffX < precision)
			return p4.y;
	
	// Subdivision branch based on x-coordinate
	if(x > p1234.x)
		return subdivide(x, p1234, p234, p34, p4, level);
	else
		return subdivide(x, p1, p12, p123, p1234, level);
}

/**
 * Retrieves the y-value of a Bezier curve at a given x-coordinate.
 *
 * @param {number} x - The x-coordinate to intersect with.
 * @param {Coord[]} curve - An array of control points defining the Bezier curve.
 * @returns {number} The y-coordinate of the point on the curve at x.
 */
function getValue(x, curve)
{
	if(!curve || !curve.length)
		return 0.0;
		
	for(var i=0; i<curve.length; i+=4)
	{
		// If x is less than the first point's x-coordinate, return y
		if(x < curve[i].x)
			return curve[i].y;

		// If x is greater than the fourth point's x-coordinate, continue to next segment
		if(x > curve[i+3].x)
			continue;
		
		// Otherwise, subdivide the curve segment and return y
		return subdivide(x, curve[i], curve[i+1], curve[i+2], curve[i+3], 0);
	}
	
	// If x is not within any segment, return the last point's y-coordinate
	return curve[curve.length-1].y;
}
