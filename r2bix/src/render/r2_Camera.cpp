#include "pch.h"
#include "r2_Camera.h"

namespace r2
{
	Camera::Camera( const RectInt::MyPointT& position, const r2::RectInt::MySizeT& size ) :
		mPosition( position )
		, mRect()
	{
		BuildRect( mPosition, size );
	}

	void Camera::SetPoint( const r2::RectInt::MyPointT& point )
	{
		mPosition = point;

		BuildRect( mPosition, mRect.GetSize() );
	}
	void Camera::SetPoint( const int x, const int y )
	{
		mPosition.Set( x, y );

		BuildRect( mPosition, mRect.GetSize() );
	}

	void Camera::BuildRect( const RectInt::MyPointT& position, const r2::RectInt::MySizeT& size )
	{
		const int min_x = position.GetX() - ( size.GetWidth() / 2 );
		const int min_y = position.GetY() - ( size.GetHeight() / 2 );
		mRect.Set( min_x, min_y, size.GetWidth(), size.GetHeight() );
	}
}