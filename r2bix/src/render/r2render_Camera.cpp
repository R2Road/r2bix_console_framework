#include "pch.h"
#include "r2render_Camera.h"

namespace r2render
{
	Camera::Camera( const r2::RectInt::MyPointT& position, const r2::RectInt::MySizeT& size ) :
		mPosition( position )
		, mWorldSpaceRect()
	{
		buildRect( mPosition, size );
	}

	void Camera::SetPoint( const r2::RectInt::MyPointT& point )
	{
		mPosition = point;

		buildRect( mPosition, mWorldSpaceRect.GetSize() );
	}
	void Camera::SetPoint( const int x, const int y )
	{
		mPosition.Set( x, y );

		buildRect( mPosition, mWorldSpaceRect.GetSize() );
	}

	void Camera::buildRect( const r2::RectInt::MyPointT& position, const r2::RectInt::MySizeT& size )
	{
		const int min_x = position.GetX() - ( size.GetWidth() / 2 );
		const int min_y = position.GetY() - ( size.GetHeight() / 2 );
		mWorldSpaceRect.Set( min_x, min_y, size.GetWidth(), size.GetHeight() );
	}
}