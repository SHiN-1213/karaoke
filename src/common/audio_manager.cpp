#include "audio_manager.hpp"

AudioManager::AudioManager(uint32_t sample_late_, uint32_t buffer_size_):
		m_sample_late(sample_late_),
		m_buffer_size(buffer_size_),
//		m_rt_audio(new RtAudio(RtAudio::WINDOWS_ASIO))
		m_rt_audio(new RtAudio(RtAudio::WINDOWS_WASAPI))
{

}

std::vector<std::string> AudioManager::getDeviceList() const
{
	std::vector<std::string> device_lists = {};

	for (const auto id: m_rt_audio->getDeviceIds())
	{
		RtAudio::DeviceInfo info = m_rt_audio->getDeviceInfo(id);
		device_lists.push_back(std::to_string(info.ID) + info.name);
	}

	return device_lists;
}

void AudioManager::openStream(StreamParameters output_param_, StreamParameters input_param_, RtAudioCallback callback_)
{
	try
	{
		m_rt_audio->openStream(&output_param_, &input_param_, RTAUDIO_FLOAT32, m_sample_late, &m_buffer_size, callback_);
	}
	catch (RtAudioErrorType &e)
	{
		std::cerr << "Error: " << e << std::endl;
	}
}

void AudioManager::startStream()
{
	m_rt_audio->startStream();
}

void AudioManager::stopStream()
{
	m_rt_audio->stopStream();
}

AudioManager::~AudioManager()
{
	if (m_rt_audio->isStreamOpen())
		m_rt_audio->closeStream();
	delete (m_rt_audio);
}
