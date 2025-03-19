import { describe, it, expect } from '@jest/globals';
import { coord, addCoords, multiplyCoordScalar, getBezier, getValue } from 'Bezier';

// Test suite for coord utility functions
describe('Coord Utility Functions', () => {
  it('should create a coordinate with default values (0,0)', () => {
    expect(coord()).toEqual({ x: 0, y: 0 });
  });

  it('should create a coordinate with given values', () => {
    expect(coord(10, 20)).toEqual({ x: 10, y: 20 });
  });

  it('should add two coordinates correctly', () => {
    expect(addCoords(coord(10, 20), coord(30, 40))).toEqual({ x: 40, y: 60 });
  });

  it('should multiply a coordinate by a scalar', () => {
    expect(multiplyCoordScalar(coord(10, 20), 3)).toEqual({ x: 30, y: 60 });
  });
});

// Test suite for Bezier curve functions
describe('Bezier Curve Functions', () => {
  it('should compute correct Bezier point at t=0', () => {
    const C1 = coord(0, 0);
    const C2 = coord(1, 2);
    const C3 = coord(2, 3);
    const C4 = coord(3, 0);
    expect(getBezier(0, C1, C2, C3, C4)).toEqual(C1);
  });

  it('should compute correct Bezier point at t=1', () => {
    const C1 = coord(0, 0);
    const C2 = coord(1, 2);
    const C3 = coord(2, 3);
    const C4 = coord(3, 0);
    expect(getBezier(1, C1, C2, C3, C4)).toEqual(C4);
  });

  it('should compute correct Bezier point at t=0.5', () => {
    const C1 = coord(0, 0);
    const C2 = coord(1, 2);
    const C3 = coord(2, 3);
    const C4 = coord(3, 0);
    const point = getBezier(0.5, C1, C2, C3, C4);
    expect(point.x).toBeCloseTo(1.5, 3);
    expect(point.y).toBeCloseTo(1.875, 3);
  });
});

// Test suite for getValue function
describe('getValue function', () => {
  it('should return 0 if curve array is empty', () => {
    expect(getValue(1, [])).toBe(0.0);
  });

  it('should return y of the closest control point when x is out of bounds', () => {
    const curve = [coord(0, 0), coord(1, 2), coord(2, 3), coord(3, 4)];
    expect(getValue(-1, curve)).toBe(0);
    expect(getValue(4, curve)).toBe(4);
  });
});
