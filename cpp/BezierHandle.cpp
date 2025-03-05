//
// C++ Implementation: BezierHandle
//
// Description:
//
//
// Author: Andreas J. Carlen <carlen.andreas@neuf.fr>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "BezierHandle.h"

namespace GameFusion
{

	BezierHandle::BezierHandle()
	{
	}

	BezierHandle::BezierHandle( const Vector3D &position, const Vector3D &leftTangent, const Vector3D &rightTangent )
	{
		m_position = position;
		m_leftTangent = leftTangent;
		m_rightTangent = rightTangent;
	}

	BezierHandle::~BezierHandle()
	{
	}

	Vector3D &BezierHandle::position()
	{
		return m_position;
	}

	Vector3D &BezierHandle::leftTangent()
	{
		return m_leftTangent;
	}

	Vector3D &BezierHandle::rightTangent()
	{
		return m_rightTangent;
	}

	Vector3D &BezierHandle::tangentNormal()
	{
		return m_tangentNormal;
	}

	Vector3D &BezierHandle::sideNormal()
	{
		return m_sideNormal;
	}

}
