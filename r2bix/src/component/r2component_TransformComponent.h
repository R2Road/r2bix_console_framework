#pragma once

#include "base/r2base_Component.h"
#include "base/r2base_ComponentStaticID.h"

#include "r2/r2_PointInt.h"

namespace r2component
{
	class TransformComponent : public r2base::Component
	{
	private:
		TransformComponent( r2base::Node& owner_node );

	public:
		int GetStaticID() const override { return r2base::ComponentStaticID<TransformComponent>::Get(); }
		static std::unique_ptr<TransformComponent> Create( r2base::Node& owner_node );

		//
		//
		//
		r2::PointInt GetPosition() const
		{
			return mPosition;
		}
		void SetPosition( const int new_x, const int new_y )
		{
			mPosition.Set( new_x, new_y );
		}
		void SetPosition( const float new_x, const float new_y )
		{
			mPosition.Set( static_cast<int>( new_x ), static_cast<int>( new_y ) );
		}

	private:
		r2::PointInt mPosition;
	};
}