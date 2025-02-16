#pragma once

#include "r2bix_component_Component.h"
#include "r2bix_component_ComponentStaticID.h"

#include "r2bix_input_Listener4Keyboard.h"

#include "p2048_GameProcessor.h"
#include "p2048_Stage.h"

#include "r2_Direction4Sequential.h"

namespace p2048
{
	class StageViewComponent;

	class GameComponent : public r2bix_component::Component<GameComponent>
	{
	private:
		enum class eStep
		{
			GameReset,
			GameReady,
			GameStart,
			GameUpdate,
			GameEnd,
			GameClear,
			GameStop,
		};

	public:
		GameComponent( r2bix::Director& director, r2bix_node::Node& owner_node );



		//
		//
		//
	private:
		void activateProcess() override;
		void deactivateProcess() override;



		//
		//
		//
	public:
		void updateProcess( const float delta_time ) override;

		const Stage& GetStage() const { return mStage; }

		void SetStageViewComponent( p2048::StageViewComponent* const stage_view_component ) { mStageViewComponent = stage_view_component; }
		void SetStageViewComponent4History( p2048::StageViewComponent* const stage_view_component ) { mStageViewComponent4History = stage_view_component; }
		void SetMaxNumberLabel( r2bix_node::Node* const node ) { mMaxNumberLabel = node; }
		void SetTotalScoreLabel( r2bix_node::Node* const node ) { mTotalScoreLabel = node; }
		void SetRecentScoreLabel( r2bix_node::Node* const node ) { mRecentScoreLabel = node; }
		void SetYouWinNode( r2bix_node::Node* const node ) { mYouWinNode = node; }
		void SetGameOverNode( r2bix_node::Node* const node ) { mGameOverNode = node; }

	private:
		bool MoveNumber( const r2::Direction4Sequential::eState move_direction );

	private:
		eStep mStep;
		Stage mStage;
		GameProcessor mGameProcessor;

		p2048::StageViewComponent* mStageViewComponent;
		p2048::StageViewComponent* mStageViewComponent4History;
		r2bix_node::Node* mMaxNumberLabel;
		r2bix_node::Node* mTotalScoreLabel;
		r2bix_node::Node* mRecentScoreLabel;

		r2bix_node::Node* mYouWinNode;
		r2bix_node::Node* mGameOverNode;

		r2bix_input::Listener4Keyboard mKeyboardListener;
	};
}