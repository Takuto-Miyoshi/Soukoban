
#include <windows.h>
#include <fstream>

#include "GameManager.h"
#include "../Definition.h"

GameManager::GameManager() : turn( 0 ), timeSec( 0 ), timeMin( 0 ), selectStageNum( 0 ){

}

GameManager::~GameManager(){

}

void GameManager::GetTxtFileInFolder(){

	{
		WIN32_FIND_DATA fileData;

		HANDLE handle = FindFirstFile( "Stage/*.txt", &fileData );

		// ファイルがない場合は終了
		if( handle == INVALID_HANDLE_VALUE ) return;

		do{
			// ファイルリストに登録
			fileList.push_back( { } );
			fileList.back().fileName = fileData.cFileName;
			fileList.back().mapData.resize( STAGE_HEIGHT, std::vector<int>( STAGE_WIDTH ) );
			fileList.back().fileName.insert( 0, "Stage/" );
		} while( FindNextFile( handle, &fileData ) == TRUE );

		// 検索終了
		FindClose( handle );
	}

	// 読み込み
	for( int i = 0; i < fileList.size(); i++ ){
		std::ifstream file( fileList.at( i ).fileName );
		std::string lineTemp;
		bool readMode = false;
		int y = 0;
		fileList.at( i ).stageTitle = fileList.at( i ).fileName;

		std::getline( file, lineTemp );
		if( lineTemp.find( "/souko" ) != -1 ){
			while( std::getline( file, lineTemp ) ){

				if( lineTemp.find( "//" ) != -1 );
				else if( lineTemp.find( "/start" ) != -1 ){
					readMode = true;
				}
				else if( lineTemp.find( "/end" ) != -1 ){
					break;
				}
				else if( lineTemp.find( "/title" ) != -1 ){
					lineTemp.erase( 0, 7 );
					fileList.at( i ).stageTitle = lineTemp;
				}
				else if( readMode == true ){
					for( int x = 0; x < STAGE_WIDTH; x++ ){
						if( lineTemp.at( x ) == ',' ) break;

						if( lineTemp.at( x ) >= 48 && lineTemp.at( x ) <= 52 ){

							fileList.at( i ).mapData.at( y ).at( x ) = lineTemp.at( x ) - 48;
							if( fileList.at( i ).mapData.at( y ).at( x ) > ObjectType::Obj_UnsetCrate ||
								fileList.at( i ).mapData.at( y ).at( x ) < ObjectType::Obj_Ground ){
								fileList.at( i ).mapData.at( y ).at( x ) = 0;
							}
						}
					}
					y++;
					if( y == STAGE_HEIGHT ) break;
				}
			}
		}
	}
}
