#include <Utils.hpp>

namespace Utils
{

	OstreamListener::OstreamListener(std::ostream& listenedStream):
		_listenedStream{listenedStream},
		_streamBuffer{_listenedStream.rdbuf()}
	{
		_listenedStream.rdbuf(_localStream.rdbuf());
	}

	OstreamListener::~OstreamListener()
	{
		_listenedStream.rdbuf(_streamBuffer);
	}

	std::string OstreamListener::getOutput() const
	{
		return _localStream.str();
	}

}
