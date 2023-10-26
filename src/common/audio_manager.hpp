#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <cmath>

#include "../../libs/RtAudio.h"

using StreamParameters = RtAudio::StreamParameters;

class AudioManager
{
public:
	AudioManager(uint32_t sample_late_, uint32_t buffer_size_);

	[[nodiscard]] std::vector<std::string> getDeviceList() const;

	void
	openStream(StreamParameters *output_param_, StreamParameters *input_param_, RtAudioCallback callback_, void *data_);

	void startStream();

	void stopStream();

	~AudioManager();

private:
	const uint32_t m_sample_late;
	uint32_t m_buffer_size;

	RtAudio *m_rt_audio;
};
