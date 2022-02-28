#pragma once

#include <list>
#include <memory>

#include "r2base_iComponent.h"

//
// # 2022.02.28 by R2Road
//
// 컴포넌트 기반 시스템을 써본 경험은 있으나 만들어 본 경험이 없으니 여기서 해본다.
//
// 노드와 컴포넌트를 조합하여 특정 기능을 가진 표준 노드를 제작한다.
// 사용자 정의 노드의 제작은 가급적 없도록 노력하자.
//

namespace r2base
{
	class Director;

	using NodeUp = std::unique_ptr<class iNode>;
	class iNode
	{
	protected:
		using ComponentT = iComponent;
		using ComponentContainerT = std::list<ComponentT*>;

		using ChildContainerT = std::list<r2base::NodeUp>;

		iNode( Director& director ) : mDirector( director ), mComponentContainer(), mChildContainer() {}
	public:
		virtual ~iNode() {}

	public:
		virtual bool Init() = 0;
		virtual void Update() = 0;

		void AddChild( r2base::NodeUp child_node )
		{
			mChildContainer.push_back( std::move( child_node ) );
		}

	protected:
		Director& mDirector;
		ComponentContainerT mComponentContainer;
		ChildContainerT mChildContainer;
	};
}