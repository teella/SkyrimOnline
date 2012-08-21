#include <stdafx.h>
#include <Logic/States/InGame.hpp>
#include <SkyrimOnline.h>

namespace Skyrim
{
	namespace Logic
	{
		namespace State
		{
			//--------------------------------------------------------------------------------
			InGame::InGame()
			{
				mChat = boost::make_shared<Overlay::Chat>(SkyrimOnline::GetInstance().GetInterface().GetGui());
				mChat->Hide();

				mFriendList = boost::make_shared<Overlay::FriendList>(SkyrimOnline::GetInstance().GetInterface().GetGui());
				mFriendList->Hide();

				mChat->OnSendChatMessage.connect(boost::bind(&InGame::OnChatMessage, this, _1));
				SkyrimOnline::GetInstance().GetPlayerWatcher().OnRegion.connect(boost::bind(&InGame::OnEnterRegion, this, _1));

			}
			//--------------------------------------------------------------------------------
			InGame::~InGame()
			{

			}
			//--------------------------------------------------------------------------------
			void InGame::OnEnter()
			{
				mChat->Show();
				//mFriendList->Show();

				SkyrimOnline::GetInstance().SetMode(true);

				SkyrimOnline::GetInstance().GetSession()->OnChatMessage.connect(boost::bind(&InGame::OnRemoteChatMessage, this, _1));
				SkyrimOnline::GetInstance().GetSession()->OnSpawn.connect(boost::bind(&InGame::OnRemoteSpawn, this));
			}
			//--------------------------------------------------------------------------------
			void InGame::OnLeave()
			{
				mChat->Hide();
				mFriendList->Hide();
			}
			//--------------------------------------------------------------------------------
			void InGame::OnUpdate(uint32_t pDelta)
			{
				SkyrimOnline::GetInstance().GetTimeManager().Update(pDelta);
				SkyrimOnline::GetInstance().GetWeatherManager().Update(pDelta);

				if(SkyrimOnline::GetInstance().GetSession() && !SkyrimOnline::GetInstance().GetSession()->IsOffline())
				{
					SkyrimOnline::GetInstance().GetPlayerWatcher().Update(pDelta);
					SkyrimOnline::GetInstance().GetSession()->Update(pDelta);
				}

				mChat->Update(pDelta);

				SkyrimOnline::GetInstance().GetCharacterManager().Update(pDelta);
			}
			//--------------------------------------------------------------------------------
			bool InGame::IsSwitchingAllowed()
			{
				return true;
			}
			//--------------------------------------------------------------------------------
			void InGame::OnEnterRegion(uint32_t pRegion)
			{
				std::ostringstream os;
				os << "You just entered region 0x" << std::hex << SkyrimOnline::GetInstance().GetPlayerWatcher().GetCharacter().GetLocationId();
				mChat->Log(os.str());
			}
			//--------------------------------------------------------------------------------
			void InGame::OnChatMessage(const std::string& pMessage)
			{
				Logic::Session::pointer session = SkyrimOnline::GetInstance().GetSession();
				if(!session->IsOffline())
				{
					session->SendChatMessage(pMessage);
				}
				else
				{
					mChat->Log("You are not connected !","#FF0000");
				}
			}
			//--------------------------------------------------------------------------------
			void InGame::OnRemoteChatMessage(const std::string& pMessage)
			{
				mChat->Log(pMessage,"#FFBF00");
			}
			//--------------------------------------------------------------------------------
			void InGame::OnRemoteSpawn()
			{
				mChat->Log("Spawned a player");
			}
			//--------------------------------------------------------------------------------
		}
	}
}