#include "pch.h"
#include "framebuffer_test.h"

#include "base/r2base_eTestEndAction.h"

#include "renderer/r2_FrameBuffer.h"

namespace framebuffer_test
{
	r2base::iTest::TitleFunc Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Frame Buffer : Basic";
		};
	}
	r2base::iTest::DoFunc Basic::GetDoFunction()
	{
		return []()->r2base::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			{
				r2::FrameBuffer frame_buffer( 15, 15 );
				frame_buffer.FillAll( 'c' );

				for( const auto v : frame_buffer )
				{
					std::cout << v;
				}
			}

			std::cout << r2::split;

			return r2base::eTestEndAction::Pause;
		};
	}



	r2base::iTest::TitleFunc DrawAtOnce::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Frame Buffer : Draw At Once";
		};
	}
	r2base::iTest::DoFunc DrawAtOnce::GetDoFunction()
	{
		return []()->r2base::eTestEndAction
		{
			std::cout << "# " << GetInstance().GetTitleFunction()( ) << " #" << r2::linefeed;

			std::cout << r2::split;

			{
				r2::FrameBuffer frame_buffer( 25, 25 );
				frame_buffer.FillAll( 'c' );

				std::cout << &( *frame_buffer.begin() );
			}

			std::cout << r2::split;

			return r2base::eTestEndAction::Pause;
		};
	}
}