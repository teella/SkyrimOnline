#pragma once

#define _WIN32_WINNT 0x0502 

#pragma warning( disable : 4251 )
#pragma warning( disable : 4244 )
#pragma warning( disable : 4996 )
#pragma warning( disable : 4355 )
#pragma warning( disable : 4995 )

#include <tchar.h>

// Boost
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/signal.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/timer.hpp>
#include <boost/tokenizer.hpp>

// Framework
#include <System/Log.h>
#include <Crypt/RSA.h>
#include <Crypt/Cipher.h>
#include <Network/IoServicePool.h>
#include <Network/HttpClient.h>
#include <Network/NinjatoStrategy.h>
#include <Network/Packet.h>
#include <Network/TcpConnection.h>
#include <Game/MassiveMessageManager.hpp>
#include <Game/GOMServer.hpp>
#include <Game/GOMVariable.hpp>
#include <Game/GameServer.hpp>
#include <Serialization/Serialization.hpp>

// STL
#include <list>
#include <vector>
#include <ctime>
#include <fstream>
#include <deque>
#include <concurrent_queue.h>
#include <unordered_map>
#include <random>

#include <Winuser.h>

// papyrus common
#include <common/enums.h>

// Crypto++
#include <cryptopp/md5.h>
#include <cryptopp/hex.h>

#include <StrSafe.h>
#include <dbghelp.h>
#include <shellapi.h>
#include <shlobj.h>

// Project code
#include <Opcodes.h>
#include <Script/Script.h>
#include <Game/data.h>

#include <FreeScript/FreeScript.hpp>

using namespace Framework;

#define _trace Framework::System::Log::Debug(std::string("Call trace : ") + std::string(__FUNCSIG__)); Framework::System::Log::Flush();