#include "texture_table_test.h"

#include "r2bix_helper/r2bix_helper_Printer4Texture.h"

#include "r2cm/r2cm_Inspector.h"
#include "r2cm/r2cm_ostream.h"

#include "test/test_r2bix/TextureTable4Test.h"

namespace texture_table_test
{
	r2cm::iItem::TitleFunctionT TextureTable_1::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Texture Table : GetTexture";
		};
	}
	r2cm::iItem::DoFunctionT TextureTable_1::GetDoFunction() const
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			PROCESS_MAIN( TextureTable4Test::GetInstance().Load() );

			std::cout << r2cm::split;

			{
				DECLARATION_MAIN( auto texture = TextureTable4Test::GetInstance().GetTexture( "blablabla" ) );
				r2bix_helper::Printer4Texture::DrawTexture( *texture );
			}

			std::cout << r2cm::split;

			{
				DECLARATION_MAIN( auto texture = TextureTable4Test::GetInstance().GetTexture( "test_texture_001" ) );
				r2bix_helper::Printer4Texture::DrawTexture( *texture );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT TextureTable_2::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Texture Table : GetTextureFrame";
		};
	}
	r2cm::iItem::DoFunctionT TextureTable_2::GetDoFunction() const
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			PROCESS_MAIN( TextureTable4Test::GetInstance().Load() );

			std::cout << r2cm::split;

			{
				DECLARATION_MAIN( auto texture = TextureTable4Test::GetInstance().GetTexture( "test_texture_001" ) );

				std::cout << r2cm::linefeed;

				r2bix_helper::Printer4Texture::DrawTexture( *texture );
			}

			std::cout << r2cm::split;

			{
				DECLARATION_MAIN( auto frame = TextureTable4Test::GetInstance().GetTextureFrame( "dguy_walk_1" ) );

				std::cout << r2cm::linefeed;

				r2bix_helper::Printer4Texture::DrawTextureFrame( *frame );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}



	r2cm::iItem::TitleFunctionT TextureTable_3::GetTitleFunction() const
	{
		return []()->const char*
		{
			return "Texture Table : Add Texture, Remove Texture";
		};
	}
	r2cm::iItem::DoFunctionT TextureTable_3::GetDoFunction() const
	{
		return []()->r2cm::eItemLeaveAction
		{
			std::cout << r2cm::split;

			{
				EXPECT_TRUE( TextureTable4Test::GetInstance().AddTexture( "TextureTable_3", 10, 4, 'S' ) );
			}

			std::cout << r2cm::split;
				
			{
				DECLARATION_MAIN( auto texture = TextureTable4Test::GetInstance().GetTexture( "TextureTable_3" ) );

				std::cout << r2cm::linefeed;

				r2bix_helper::Printer4Texture::DrawTexture( *texture );
			}

			std::cout << r2cm::split;

			{
				EXPECT_FALSE( TextureTable4Test::GetInstance().AddTexture( "TextureTable_3", 10, 4, 'S' ) );
			}

			std::cout << r2cm::split;

			{
				EXPECT_TRUE( TextureTable4Test::GetInstance().RemoveTexture( "TextureTable_3" ) );
			}

			std::cout << r2cm::split;

			{
				DECLARATION_MAIN( auto texture = TextureTable4Test::GetInstance().GetTexture( "TextureTable_3" ) );

				std::cout << r2cm::linefeed;

				r2bix_helper::Printer4Texture::DrawTexture( *texture );
			}

			std::cout << r2cm::split;

			return r2cm::eItemLeaveAction::Pause;
		};
	}
}