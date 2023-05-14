#include "texture_frame_test.h"

#include "r2cm/r2cm_Inspector.h"
#include "r2bix/r2bix_render_Texture.h"
#include "r2bix/r2bix_render_TextureFrame.h"
#include "r2cm/r2cm_ostream.h"

#include "test/test_r2bix/TextureTable4Test.h"
#include "test/Utility4Test.h"

namespace
{
	const r2bix_render::Texture& GetDummyTexture()
	{
		static const r2bix_render::Texture texture( 7,
			"1111111"
			"1222222"
			"1233333"
			"1234444"
			"1234555"
			"1234566"
			"1234567"
		);

		return texture;
	}

	void PrintRectInfo( const r2::RectInt& rect )
	{
		std::cout << r2cm::tab << "rect min, max :" << " " << rect.GetMinX() << " " << rect.GetMinY() << " " << rect.GetMaxX() << " " << rect.GetMaxY() << r2cm::linefeed;
	}
}

namespace texture_frame_test
{
	r2cm::iItem::TitleFunctionT Basic::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "TextureFrame : Basic";
		};
	}
	r2cm::iItem::DoFunctionT Basic::GetDoFunction() const
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			DECLARATION_MAIN( const r2bix_render::Texture& texture = GetDummyTexture() );

			std::cout << r2cm::linefeed;

			r2bix_helper::Printer4Texture::DrawTexture( texture );

			std::cout << r2cm::split;

			DECLARATION_MAIN( r2bix_render::TextureFrame frame( &texture ) );

			std::cout << r2cm::linefeed;

			r2bix_helper::Printer4Texture::DrawTextureFrame( frame );

			std::cout << r2cm::split;

			PrintRectInfo( frame.GetVisibleRect() );

			std::cout << r2cm::linefeed;

			EXPECT_EQ( &texture, frame.GetTexture() );

			EXPECT_EQ( texture.GetCharacter( 0, 0 ), frame.GetCharacter( 0, 0 ) );
			EXPECT_EQ( '1', frame.GetCharacter( 0, 0 ) );

			EXPECT_EQ( texture.GetCharacter( 6, 6 ), frame.GetCharacter( 6, 6 ) );
			EXPECT_EQ( '7', frame.GetCharacter( 6, 6 ) );

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT VisibleRect_1::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "TextureFrame : Visible Rect 1";
		};
	}
	r2cm::iItem::DoFunctionT VisibleRect_1::GetDoFunction() const
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			DECLARATION_MAIN( const r2bix_render::Texture& texture = GetDummyTexture() );
			DECLARATION_MAIN( r2bix_render::TextureFrame frame( &texture ) );

			std::cout << r2cm::linefeed;

			{
				std::size_t cur_x = 0;
				for( const char element : texture )
				{
					std::cout << element;

					++cur_x;
					if( texture.GetWidth() <= cur_x )
					{
						cur_x = 0u;
						std::cout << r2cm::linefeed;
					}
				}
				if( 0u != cur_x )
				{
					std::cout << r2cm::linefeed;
				}
			}

			std::cout << r2cm::split;

			{
				PrintRectInfo( frame.GetVisibleRect() );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( frame.MoveVisibleOrigin( 2, 1 ) );
				PROCESS_MAIN( frame.ChangeVisibleSize( -3, -1 ) );

				std::cout << r2cm::linefeed;

				PrintRectInfo( frame.GetVisibleRect() );

				std::cout << r2cm::linefeed;

				EXPECT_EQ( texture.GetCharacter( frame.GetMinX(), frame.GetMinY() ), frame.GetCharacter( 0, 0 ) );

				std::cout << r2cm::linefeed;

				r2bix_helper::Printer4Texture::DrawTextureFrame( frame );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT VisibleRect_2::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "TextureFrame : Visible Rect 2";
		};
	}
	r2cm::iItem::DoFunctionT VisibleRect_2::GetDoFunction() const
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			DECLARATION_MAIN( const r2bix_render::Texture& texture = GetDummyTexture() );

			std::cout << r2cm::linefeed;

			{
				std::size_t cur_x = 0;
				for( const char element : texture )
				{
					std::cout << element;

					++cur_x;
					if( texture.GetWidth() <= cur_x )
					{
						cur_x = 0u;
						std::cout << r2cm::linefeed;
					}
				}
				if( 0u != cur_x )
				{
					std::cout << r2cm::linefeed;
				}
			}

			std::cout << r2cm::split;

			DECLARATION_MAIN( r2bix_render::TextureFrame frame( &texture ) );

			std::cout << r2cm::linefeed;

			{
				PrintRectInfo( frame.GetVisibleRect() );

				std::cout << r2cm::linefeed;

				PROCESS_MAIN( frame.MoveVisibleOrigin( -3, -3 ) );
				PROCESS_MAIN( frame.ChangeVisibleSize( -1, -1 ) );

				std::cout << r2cm::linefeed;

				PrintRectInfo( frame.GetVisibleRect() );

				std::cout << r2cm::linefeed;

				EXPECT_EQ( '1', frame.GetCharacter( 0, 0 ) );

				std::cout << r2cm::linefeed;

				r2bix_helper::Printer4Texture::DrawTextureFrame( frame );
			}

			std::cout << r2cm::split;

			{
				PROCESS_MAIN( frame.MoveVisibleOrigin( 6, 6 ) );

				std::cout << r2cm::linefeed;

				PrintRectInfo( frame.GetVisibleRect() );

				std::cout << r2cm::linefeed;

				EXPECT_EQ( '4', frame.GetCharacter( 0, 0 ) );

				std::cout << r2cm::linefeed;

				r2bix_helper::Printer4Texture::DrawTextureFrame( frame );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}
}