//
// C++ Implementation: BezierPath
//
// Description:
//
//
// Author: Andreas J. Carlen <carlen.andreas@neuf.fr>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "BezierPath.h"
#include <math.h>

namespace GameFusion
{

	//static BezierPath s_smoothPath(0.f, 1.f, 0.f, 1.f, 0.5f, 0.5f);

	BezierPath BezierPath::SmoothPath(0.f, 1.f, 0.f, 1.f, 0.5f, 0.5f);

	BezierPath::BezierPath()
	{
		m_maxLevels = BEZIER_PATH_MAX_RECURSION;
		m_precision = BEZIER_PATH_PRECISION;
	}

	BezierPath::BezierPath(float startTime, float endTime, float startValue, float endValue, float easyIn, float easyOut)
	{
		m_maxLevels = BEZIER_PATH_MAX_RECURSION;
		m_precision = BEZIER_PATH_PRECISION;

		*this += BezierHandle(Vector3D(startTime, startValue, 0.f), Vector3D(), Vector3D(easyIn, 0.f, 0.f));
		*this += BezierHandle(Vector3D(endTime, endValue, 0.f), Vector3D(-easyOut, 0.f, 0.f), Vector3D(easyOut, 0.f, 0.f));
		*this += BezierHandle(Vector3D(endTime + (endTime - startTime), startValue, 0.f), Vector3D(-easyIn, 0.f, 0.f), Vector3D());

		assess(20, false);
	}


	BezierPath::~BezierPath()
	{
	}

	void BezierPath::operator += (BezierHandle &handle)
	{
		m_handleList += handle;
	}

	void BezierPath::operator += (const BezierHandle &handle)
	{
		BezierHandle newHandle = handle;
		m_handleList += newHandle;
	}

	void BezierPath::operator -= (int index)
	{
		m_handleList.removeByIndex(index);
	}
	
	void BezierPath::smooth(float smoothIn, float /*smoothOut*/, bool loop)
	{
		

		ListIterator <BezierHandle> li(m_handleList);

		while(!li.end())
		{
				/*
				get prior, current and nex handles, for each current set the tangents
				*/
				BezierHandle *prior = 0;
				BezierHandle &current   = *(li);
				BezierHandle *next   = 0;

				if(li.next())
					next   = &(**(li.next()));
				else if(loop)
					next = &(**(m_handleList.start()));

				if(li.prior())
					prior = &(**(li.prior()));
				else if(loop)
					prior =  &(**(m_handleList.last()));


				

				Vector3D seg1;
				Vector3D seg2;

				Vector3D midpoint1, midpoint2;

				if(prior)
				{
					seg1 =  (current.position() - prior->position());
					//midpoint1 = prior->position() + seg1 * 0.5;
					midpoint1 = prior->position();
				}
				else
					midpoint1 = current.position();

				if(next)
				{
					seg2 = (next->position() - current.position());
					//midpoint2 = current.position() +  seg2 * 0.5;
					midpoint2 = next->position();
				}
				else
					midpoint2 = current.position();

				Vector3D tangentEdge = midpoint2 - midpoint1;

				//float tangentMag = tangentEdge.magnitude();
				
				// compute proportion factor for left and right tangents
				float seg1Mag = seg1.magnitude();
				float seg2Mag = seg2.magnitude();

				//float totalMag = seg1Mag + seg2Mag;
				/*
				float factor1 = seg1Mag / totalMag;
				float factor2 = seg2Mag / totalMag;
				*/

				Vector3D tangentNormal = Vector3D::normal(tangentEdge);

				seg1.normalize();
				seg2.normalize();

				/*
				float dot1 = Vector3D::dotProduct(seg1, seg2);

				//Log::info("dot %f\n", dot1);
				float factor1 = 0.5 * (1. - SmoothPath.getValue(dot1));
				float factor2 = 0.5 * (1. - SmoothPath.getValue(dot1));

				current.leftTangent()  = -tangentNormal * (factor1 * seg1Mag);
				current.rightTangent() =  tangentNormal * (factor2 * seg2Mag);
				*/
				current.leftTangent()  = -tangentNormal * (seg1Mag*0.5f);
				current.rightTangent() =  tangentNormal * (seg2Mag*0.5f);

				
			
			li++;
		}

		//print();
		//exit(0);
		
		//smoothTangents(normal);
	}
	
	void BezierPath::smoothAuto(float /*smoothIn*/, float /*smoothOut*/, bool loop)
	{
		

		ListIterator <BezierHandle> li(m_handleList);

		while(!li.end())
		{
				/*
				get prior, current and nex handles, for each current set the tangents
				*/
				BezierHandle *prior = 0;
				BezierHandle &current   = *(li);
				BezierHandle *next   = 0;

				if(li.next())
					next   = &(**(li.next()));
				else if(loop)
					next = &(**(m_handleList.start()));

				if(li.prior())
					prior = &(**(li.prior()));
				else if(loop)
					prior =  &(**(m_handleList.last()));


				

				Vector3D seg1;
				Vector3D seg2;

				Vector3D midpoint1, midpoint2;

				if(prior)
				{
					seg1 =  (current.position() - prior->position());
					//midpoint1 = prior->position() + seg1 * 0.5;
					midpoint1 = prior->position();
				}
				else
					midpoint1 = current.position();

				if(next)
				{
					seg2 = (next->position() - current.position());
					//midpoint2 = current.position() +  seg2 * 0.5;
					midpoint2 = next->position();
				}
				else
					midpoint2 = current.position();

				
				
				

				//float tangentMag = tangentEdge.magnitude();
				
				// compute proportion factor for left and right tangents
				float seg1Mag = seg1.magnitude();
				float seg2Mag = seg2.magnitude();
				
				

				//float totalMag = seg1Mag + seg2Mag;
				/*
				float factor1 = seg1Mag / totalMag;
				float factor2 = seg2Mag / totalMag;
				*/

				

				seg1.normalize();
				seg2.normalize();
				
				
				//
				// New smppth model compute tanget normal based on the angle
				if(prior && next)
				{
					if( seg1Mag < seg2Mag)
					{
						midpoint2 = current.position() + seg2 * seg1Mag;
						seg2Mag = seg1Mag;
					}
					else if(seg1Mag > seg2Mag)
					{
						midpoint1 = current.position() - seg1 * seg2Mag;
						seg1Mag = seg2Mag;
					}
					
				}
				//
				
				Vector3D tangentEdge = midpoint2 - midpoint1;
				Vector3D tangentNormal = Vector3D::normal(tangentEdge);

				/*
				float dot1 = Vector3D::dotProduct(seg1, seg2);

				//Log::info("dot %f\n", dot1);
				float factor1 = 0.5 * (1. - SmoothPath.getValue(dot1));
				float factor2 = 0.5 * (1. - SmoothPath.getValue(dot1));

				current.leftTangent()  = -tangentNormal * (factor1 * seg1Mag);
				current.rightTangent() =  tangentNormal * (factor2 * seg2Mag);
				*/
				current.leftTangent()  = -tangentNormal * (seg1Mag*0.5f);
				current.rightTangent() =  tangentNormal * (seg2Mag*0.5f);

				
			
			li++;
		}

		//print();
		//exit(0);
		
		//smoothTangents(normal);
	}

	void BezierPath::smooth(float smoothIn, float smoothOut)
	{
		ListIterator <BezierHandle> li(m_handleList);

		while(!li.end())
		{
			//if(li.prior())
			{
				BezierHandle *prior = 0;
				BezierHandle &current   = *(li);
				BezierHandle *next   = 0;

				if(li.next())
					next   = &(**(li.next()));
				else
					next = &(**(m_handleList.start()));

				if(li.prior())
					prior = &(**(li.prior()));
				else
					prior =  &(**(m_handleList.last()));


				/*************/

				Vector3D vdistance = current.position() - prior->position();
				Vector3D vhalfD    = vdistance * 0.5;
				
				prior->leftTangent() = vhalfD * smoothIn;
				current.rightTangent() = -vhalfD * smoothOut;

				//continue;

				/**********/

				/*
			
			float distance = handle.position().x() - prior.position().x();
			float halfD = distance * 0.5;
			prior.rightTangent()[0] = -halfD * smoothIn;
			handle.leftTangent().x() = halfD * smoothOut;

			float distanceZ = handle.position().z() - prior.position().z();
			float halfDZ = distanceZ * 0.5;
			prior.rightTangent().z() = halfDZ * smoothIn;
			handle.leftTangent().z() = -halfDZ * smoothOut;
				*/
			}
			li++;
		}
		
		//smoothTangents(normal);
	}
		
	void BezierPath::smoothTangents(Vector3D upNormal)
	{

		ListIterator <BezierHandle> li(m_handleList);
		
		//Vector3D upNormal(0., 1., 0.);

		li = m_handleList.start();
		while(!li.end())
		{
			BezierHandle &current   = *(li);

			Vector3D t, b, normal;
			
			Vector3D tempSTangent;
			Vector3D tempTTangent;

			//Calculate vectors along polygon sides
			Vector3D side0 = current.leftTangent();
			Vector3D side1 = current.rightTangent();

			side0.normalize();
			side1.normalize();

			//Calculate normal
			normal = Vector3D::crossProduct(side1, side0);
			normal.normalize();
		
			float deltaT0 = 1.f;
			float deltaT1 = 1.f;

			tempSTangent = deltaT1 * side0 - deltaT0 * side1;
			tempSTangent.normalize();

			//normal = -normal;

			float dot = Vector3D::dotProduct(side0, side1);
			if(dot > 0)
			{
				//tempSTangent = -tempSTangent;
				//tempTTangent = -tempTTangent;
				//normal = -normal;
			}


			//currentNormal = currentNormal * tempSTangent;
			//currentNormal.normalize();

			//normal = Vector3D::crossProduct(currentNormal, tempSTangent);

			current.sideNormal() = Vector3D::crossProduct(upNormal, tempSTangent);
			current.sideNormal().normalize();
			current.tangentNormal() = -Vector3D::crossProduct(current.sideNormal(), tempSTangent);
			current.tangentNormal().normalize();
			current.leftTangent() = tempSTangent;
			current.rightTangent() = -(tempSTangent);

			/*printf("Point %d \n", li.index());
			current.position().print("pos");
			current.leftTangent().print("left tangent");
			current.rightTangent().print("right tangent");
			*/
			li++;
		}
		
	}

	float BezierPath::getStartValue()
	{
		if(!m_handleList.begin())
			return 0.;
	
		return (**(m_handleList.begin())).position().y_;
	}

	float BezierPath::getEndValue()
	{
		if(!m_handleList.last())
			return 0.;
	
		return (**m_handleList.last()).position().y_;
	}

	float BezierPath::start()
	{
		if(!m_handleList.begin())
			return 0.;
	
		return (**(m_handleList.begin())).position().x_;
	}

	float BezierPath::end()
	{
		if(!m_handleList.last())
			return 0.;
	
		return (**m_handleList.last()).position().x_;
	}

	float BezierPath::duration()
	{
		if(!m_handleList.last())
			return 0.;
	
		return  (**m_handleList.last()).position().x_ - (**m_handleList.begin()).position().x_;
	}

	float BezierPath::getValue(float time) /// here time represents a point on the x axis plane !!
	{
		ListIterator <BezierHandle> li(m_handleList);

		while(!li.end())
		{
			BezierHandle &h1 = *li;

			if(time < h1.position().x_)
				return h1.position().y_;

			li++;

			if(li.end())
				return h1.position().y_;

			BezierHandle &h2 = *li;

			if(h2.position().x_ < time)
			{
				//li++;
				//if(li.end())
				//	return h2.position().y_;
				continue;
			}

			Vector3D &p1 = h1.position();
			Vector3D  p2 = p1 + h1.rightTangent();
			Vector3D &p4 = h2.position();
			Vector3D  p3 = p4 + h2.leftTangent();

			float s=-1;
			int level = 0;

			//Vector3D result;
			//s = time - p1.x();
			//assessVector(result, h1, h2, time);
			
			//return result.y();
			float fval = subdivide(p1, p2, p3, p4, time, s, level);

			//Log::info("sub levels %d s %f val %f\n", level, s, fval); 
			
			return fval;
		}

		return 0.;
	}

	float BezierPath::subdivide(Vector3D &p1, Vector3D &p2, Vector3D &p3, Vector3D &p4, const float time, float &s, int &level, const float u1, const float u2)
	{
		Vector3D p12   = (p1 + p2) * 0.5;
		Vector3D p23   = (p2 + p3) * 0.5;
		Vector3D p34   = (p3 + p4) * 0.5;
		Vector3D p234  = (p23 + p34) * 0.5;
		Vector3D p123  = (p12 + p23) * 0.5;
		Vector3D p1234 = (p123 + p234) * 0.5; // here we have the mid intersection point

		s = u1 + (u1 + u2) * 0.5f;
		level ++;

		if(level >= m_maxLevels || intersect(p1234.x_, time))
			return p1234.y_;

		if(intersect(p1.x_, time))
			return p1.y_;
			
		if(intersect(p4.x_, time))
			return p4.y_;	

		if(time > p1234.x_)
			return subdivide(p1234, p234, p34, p4, time, s, level, s, u2);
		else
			return subdivide(p1, p12, p123, p1234, time, s, level, u1, s);

	}

	bool BezierPath::intersect(float p1, float p2)
	{
		if(fabsf(p1 - p2) > m_precision)
			return false;

		return true;
	}

	void BezierPath::clear()
	{
		m_handleList.clear();
	}

	void BezierPath::assessVector(Vector3D &result, BezierHandle &h1, BezierHandle &h2, const float time)
	{
		Vector3D &p1 = h1.position();
		Vector3D  p2 = p1 + h1.rightTangent();
		Vector3D &p4 = h2.position();
		Vector3D  p3 = p4 + h2.leftTangent();

		Vector3D p12  ( p1   + (p2   - p1)   * time);
		Vector3D p23  ( p2   + (p3   - p2)   * time);
		Vector3D p34  ( p3   + (p4   - p3)   * time);
		Vector3D p123 ( p12  + (p23  - p12)  * time);
		Vector3D p234 ( p23  + (p34  - p23)  * time);

		result = p123 + (p234 - p123) * time;
	}

	void BezierPath::getVector(Vector3D &result, float time)
	{
		int index = (int)time;
		float curveTime = time - index;

		if(!m_handleList.length())
			return;

		int handleIndex1 = index     % (m_handleList.length());
		int handleIndex2 = (index+1) % (m_handleList.length());

		BezierHandle &h1 = m_handleList[handleIndex1];
		BezierHandle &h2 = m_handleList[handleIndex2];

		Vector3D &p1 = h1.position();
		Vector3D  p2 = p1 + h1.rightTangent();
		Vector3D &p4 = h2.position();
		Vector3D  p3 = p4 + h2.leftTangent();

		Vector3D p12  ( p1   + (p2   - p1)   * curveTime);
		Vector3D p23  ( p2   + (p3   - p2)   * curveTime);
		Vector3D p34  ( p3   + (p4   - p3)   * curveTime);
		Vector3D p123 ( p12  + (p23  - p12)  * curveTime);
		Vector3D p234 ( p23  + (p34  - p23)  * curveTime);

		result = p123 + (p234 - p123) * curveTime;

		
	}



    void BezierPath::assess(int pointsPerSegment, bool loop)
	{
		// get the num points to be computed in vertex array
		// if we do not loop we have one pointsPerSegment less points to compute
		// hence the -1 below
        int numPoints = (loop ? m_handleList.length() : m_handleList.length() - 1)  * pointsPerSegment;

		if(!numPoints)
			return;

		if(loop)
			numPoints++;

        m_vertexArray.resize(numPoints, 0);

        int handleIndex = 1;
        int lastHandleIndex = m_handleList.length() -1;

		for(ListIterator <BezierHandle> li(m_handleList); !li.end(); li++)
		{
			BezierHandle *handleA = &(*li);
			BezierHandle *handleB = null;

			if(li.next())
				handleB = &(**(li.next()));
			else if(loop && li.index())
				handleB = &(**(m_handleList.begin()));
			
			if(!handleB)
				return;

			Vector3D v;
			float time = 0.f;
            double timeInc = 1.f/((float)(pointsPerSegment));

            double step = 1.f/((float)pointsPerSegment-1);

            //if(handleIndex < lastHandleIndex)
                for(int i=0; i<pointsPerSegment; i++)
                {
                    // this time will end before 1
                    time = i * timeInc;
                    BezierPath::assessVector(v, *handleA, *handleB, time);
                    m_vertexArray += v;
                }
            /*
            else
                for(int i=0; i<pointsPerSegment; i++)
                {

                    time = i * step; // use step on single segments and last segments
                    printf("[%d] time %f\n", i, time);
                    // to generate values from 0 to 1 inclusive
                    BezierPath::assessVector(v, *handleA, *handleB, time);
                    m_vertexArray += v;
                }
*/
            handleIndex ++;
		}
	}

	void BezierPath::print()
	{
		printf("BezierPath::dump :\n");
		printf("maxlevels %d\n", m_maxLevels);
		printf("precision %f\n", m_precision);

		printf("number handles %d\n", m_handleList.length());
		for(ListIterator <BezierHandle> li(m_handleList); !li.end(); li++)
		{
			BezierHandle &handle = *li;
			printf("handle [%.2d] \n", li.index());
			handle.position().print("   position ");
			handle.leftTangent().print("   leftTangent ");
			handle.rightTangent().print("   rightTangent ");
			handle.sideNormal().print("   sideNormal ");
			handle.tangentNormal().print("   tangentNormal ");
		}

		printf("vertex array length %d\n", m_vertexArray.length());

		for(int i=0; i<m_vertexArray.length(); i++)
		{
			printf("v [%.3d]\n", i);
			m_vertexArray[i].print();
		}

	}

	Array <Vector3D> & BezierPath::vertexArray()
	{
		return m_vertexArray;
	}
	
	void BezierPath::setPrecision(float p)
	{
		m_precision = p;
	}
	
	void BezierPath::setMaxRecursion(int r)
	{
		m_maxLevels = r;
	}
	
	BezierHandle &BezierPath::operator [] (int index)
	{
		return m_handleList[index];
	}
	
	int BezierPath::length()
	{
		return m_handleList.length();
	}
	
	List <BezierHandle> & BezierPath::handleList()
	{
		return m_handleList;
	}
	
	BezierHandle &BezierPath::insert(int index, const BezierHandle &handle)
	{
		BezierHandle newHandle = handle;
		m_handleList.insert(index, newHandle);
		return m_handleList[index];
	}

    float BezierPath::getTime(float value, float precision)  {
        if (m_handleList.length() < 2) {
            throw std::runtime_error("Not enough handles to compute time.");
        }

        float minTime = m_handleList[0].position().x();
        float maxTime = m_handleList[m_handleList.length() - 1].position().x();
		int iteration(0);

        while (std::fabs(maxTime - minTime) > precision) {
            float midTime = (minTime + maxTime) / 2.0f;
            float midValue = getValue(midTime);

            if (midValue == value || iteration >= BEZIER_PATH_MAX_RECURSION) {
                return midTime;
            } else if (midValue < value) {
                minTime = midTime;
            } else {
                maxTime = midTime;
            }
			iteration++;
        }

        // Return the closest time found
        return (minTime + maxTime) / 2.0f;
    }

    float BezierPath::GetValue(float startTime, float endTime, float startValue, float endValue, float easyIn, float easyOut, float time, float precision){
        GameFusion::BezierPath bezier;
        GameFusion::BezierHandle handle;

        bezier += BezierHandle(Vector3D(startTime, startValue, 0.f), Vector3D(), Vector3D(easyIn, 0.f, 0.f));
        bezier += BezierHandle(Vector3D(endTime, endValue, 0.f), Vector3D(easyOut, 0.f, 0.f), Vector3D());
        
        //bezier.assess(100, false);
		bezier.setPrecision(precision);
        return bezier.getValue(time);
    }

float BezierPath::GetTime(float startTime, float endTime, float startValue, float endValue, float easyIn, float easyOut, float value, float precision){
    GameFusion::BezierPath bezier;
    GameFusion::BezierHandle handle;

    bezier += BezierHandle(Vector3D(startTime, startValue, 0.f), Vector3D(), Vector3D(easyIn, 0.f, 0.f));
    bezier += BezierHandle(Vector3D(endTime, endValue, 0.f), Vector3D(easyOut, 0.f, 0.f), Vector3D());
    
    //bezier.assess(100, false);
    
    return bezier.getTime(value, precision);
}
}
